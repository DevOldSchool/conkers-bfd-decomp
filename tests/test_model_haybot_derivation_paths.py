"""Path and trust-boundary tests for the optional Haybot derivation CLI."""
import argparse
import builtins
import os
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

from scripts.model_evidence import derive_haybot_contract as derivation


class HaybotDerivationPathTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        self.capture = self.root / "capture-audit.json"
        self.packet = self.root / "packet.json"
        self.rom = self.root / "rom.z64"
        for path in (self.capture, self.packet, self.rom):
            path.write_bytes(b"preserved evidence")

    def arguments(self, **changes):
        values = dict(rom=self.rom, packet=self.packet,
                      rom_report=self.root / "rom-report.json",
                      capture_audit=self.capture, output=self.root / "contract.json")
        values.update(changes)
        return argparse.Namespace(**values)

    def cli(self, args):
        result = []
        for name in ("rom", "packet", "rom_report", "capture_audit", "output"):
            value = getattr(args, name)
            if value is not None:
                result.extend(["--" + name.replace("_", "-"), str(value)])
        return result

    def test_relative_inputs_resolve_once(self):
        previous = Path.cwd()
        try:
            os.chdir(self.root)
            args = self.arguments(rom=Path("rom.z64"), packet=Path("packet.json"),
                                  capture_audit=Path("capture-audit.json"),
                                  rom_report=Path("rom-report.json"), output=Path("contract.json"))
            derivation.validate_paths(args)
        finally:
            os.chdir(previous)
        for name in ("rom", "packet", "capture_audit", "rom_report", "output"):
            self.assertEqual(self.root, getattr(args, name).parent)
            self.assertTrue(getattr(args, name).is_absolute())

    def test_output_aliases_are_rejected_after_resolution(self):
        args = self.arguments(output=self.root / "unused" / ".." / "rom-report.json")
        with self.assertRaisesRegex(ValueError, "output paths must be distinct"):
            derivation.validate_paths(args)
        self.assertFalse(args.rom_report.exists())

    def test_existing_rom_report_and_contract_are_preserved(self):
        for name in ("rom_report", "output"):
            with self.subTest(destination=name):
                args = self.arguments()
                path = getattr(args, name)
                path.write_bytes(b"do not truncate")
                with self.assertRaisesRegex(ValueError, "must be a new file"):
                    derivation.main(self.cli(args))
                self.assertEqual(b"do not truncate", path.read_bytes())
                path.unlink()

    def test_inputs_cannot_be_used_as_either_output(self):
        for source in (self.capture, self.packet, self.rom):
            for name in ("rom_report", "output"):
                with self.subTest(source=source, destination=name):
                    with self.assertRaisesRegex(ValueError, "must be a new file"):
                        derivation.main(self.cli(self.arguments(**{name: source})))
                    self.assertEqual(b"preserved evidence", source.read_bytes())

    def test_input_alias_through_directory_symlink_is_rejected(self):
        link = self.root / "linked"
        link.symlink_to(self.root, target_is_directory=True)
        for name in ("rom_report", "output"):
            with self.subTest(destination=name), self.assertRaisesRegex(ValueError, "must be a new file"):
                derivation.validate_paths(self.arguments(**{name: link / self.capture.name}))
        self.assertEqual(b"preserved evidence", self.capture.read_bytes())

    def test_existing_and_dangling_output_symlinks_are_rejected(self):
        for target in (self.capture, self.root / "absent.json"):
            link = self.root / "output-link"
            link.symlink_to(target)
            try:
                for name in ("rom_report", "output"):
                    with self.subTest(target=target, destination=name):
                        with self.assertRaisesRegex(ValueError, "symbolic link"):
                            derivation.validate_paths(self.arguments(**{name: link}))
            finally:
                link.unlink()
        self.assertEqual(b"preserved evidence", self.capture.read_bytes())
        self.assertFalse((self.root / "absent.json").exists())

    def test_capture_and_contract_options_are_paired(self):
        for changes in ({"capture_audit": None}, {"output": None}):
            with self.subTest(changes=changes), self.assertRaisesRegex(ValueError, "supplied together"):
                derivation.validate_paths(self.arguments(**changes))

    def test_rom_only_mode_accepts_new_output_without_capture(self):
        args = self.arguments(capture_audit=None, output=None)
        derivation.validate_paths(args)
        self.assertFalse(args.rom_report.exists())

    def test_missing_output_parent_is_rejected_before_source_work(self):
        for name in ("rom_report", "output"):
            with self.subTest(destination=name), self.assertRaisesRegex(ValueError, "parent directory is missing"):
                derivation.validate_paths(self.arguments(**{name: self.root / "absent" / "new.json"}))

    def test_changed_capture_rejects_before_project_import_or_any_output(self):
        original_import = builtins.__import__
        project_imports = []

        def checked_import(name, *args, **kwargs):
            if name == "scripts" or name.startswith("scripts."):
                project_imports.append(name)
                raise AssertionError("project source imported before capture authentication")
            return original_import(name, *args, **kwargs)

        args = self.arguments()
        with patch("builtins.__import__", side_effect=checked_import):
            with self.assertRaisesRegex(ValueError, "independently reviewed capture audit changed"):
                derivation.main(self.cli(args))
        self.assertEqual([], project_imports)
        self.assertFalse(args.rom_report.exists())
        self.assertFalse(args.output.exists())

    def test_changed_packet_rejects_before_rom_work(self):
        args = self.arguments(capture_audit=None, output=None)
        with patch.object(derivation, "audit_rom") as audit:
            with self.assertRaisesRegex(ValueError, "preserved packet bytes changed"):
                derivation.main(self.cli(args))
        audit.assert_not_called()
        self.assertFalse(args.rom_report.exists())

    def test_exclusive_creation_rejects_file_added_after_validation(self):
        args = self.arguments(capture_audit=None, output=None)
        derivation.validate_paths(args)
        args.rom_report.write_bytes(b"introduced after validation")
        with self.assertRaises(FileExistsError):
            derivation.write_new(args.rom_report, b"new report")
        self.assertEqual(b"introduced after validation", args.rom_report.read_bytes())

    def test_exclusive_creation_writes_exact_bytes_once(self):
        path = self.root / "new.json"
        derivation.write_new(path, b'{"passed": true}\n')
        self.assertEqual(b'{"passed": true}\n', path.read_bytes())
        with self.assertRaises(FileExistsError):
            derivation.write_new(path, b"replacement")
        self.assertEqual(b'{"passed": true}\n', path.read_bytes())


if __name__ == "__main__":
    unittest.main()
