from __future__ import annotations

import hashlib
import json
from pathlib import Path
import struct
import sys
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "scripts"))
import link_game_data as game_data

BASE = 0x80082B20


def executable(entries):
    """Build a minimal linked ELF: (name, type, flags, address, payload)."""
    names = bytearray(b"\0.shstrtab\0")
    headers = [(0,) * 10]
    body = bytearray(52)
    for name, kind, flags, address, payload in entries:
        at = len(names)
        names.extend(name.encode() + b"\0")
        headers.append((at, kind, flags, address, len(body), len(payload), 0, 0, 4, 0))
        if kind != 8:
            body.extend(payload)
    strings_at = len(body)
    body.extend(names)
    headers.append((1, 3, 0, 0, strings_at, len(names), 0, 0, 1, 0))
    header_at = len(body)
    for header in headers:
        body.extend(struct.pack(">10I", *header))
    body[:52] = struct.pack(">16sHHIIIIIHHHHHH", b"\x7fELF\x01\x02\x01" + bytes(9),
                            2, 8, 1, 0, 0, header_at, 0, 52, 0, 0, 40, len(headers), len(headers) - 1)
    return bytes(body)


def mapping(name, start, size, emitted=None, selector="*game_1.o(.rodata)", mode="INFO"):
    return {"output": name, "start": start, "end": start + size, "input": ".rodata",
            "input_selector": selector, "linker_mode": mode,
            "emitted_size": size if emitted is None else emitted}


SOURCE = {"kind": "source", "object": "build/game-integrated/us/src/done/game/game_1.o",
          "source": "src/done/game/game_1.c", "object_sha256": "0" * 64}


class ComposeTests(unittest.TestCase):
    original = bytes(range(64))

    def compose(self, sections, mappings):
        return game_data.compose(executable(sections), self.original, BASE, mappings,
                                 [SOURCE] * len(mappings))

    def test_linked_payloads_and_preserved_gaps_cover_the_whole_image(self):
        payload = self.original[8:20]
        image, ranges = self.compose(
            [(".game_rodata_1", 1, 0, BASE + 8, payload + bytes(4))],
            [mapping(".game_rodata_1", BASE + 8, 12, emitted=16)])
        self.assertEqual(image, self.original)
        self.assertEqual([(r["start"] - BASE, r["end"] - BASE, r["provenance"]) for r in ranges],
                         [(0, 8, "preserved"), (8, 20, "linked"), (20, 64, "preserved")])
        linked = ranges[1]
        self.assertEqual(linked["sha256"], hashlib.sha256(payload).hexdigest())
        self.assertEqual(linked["object"], SOURCE["object"])
        self.assertEqual(sum(r["size"] for r in ranges), len(self.original))

    def test_adjacent_placements_leave_no_gap(self):
        _, ranges = self.compose(
            [(".game_rodata_a", 1, 0, BASE, self.original[:4]),
             (".game_rodata_b", 1, 0, BASE + 4, self.original[4:8])],
            [mapping(".game_rodata_a", BASE, 4), mapping(".game_rodata_b", BASE + 4, 4)])
        self.assertEqual([r["provenance"] for r in ranges], ["linked", "linked", "preserved"])

    def test_rejects_any_difference_from_the_rom(self):
        good = self.original[8:12]
        cases = {
            "missing": ([], "missing from the integrated ELF"),
            "address": ([(".game_rodata_1", 1, 0, BASE + 12, good)], "reviewed address"),
            "type": ([(".game_rodata_1", 8, 0, BASE + 8, good)], "reviewed address"),
            "extent": ([(".game_rodata_1", 1, 0, BASE + 8, good + bytes(4))], "reviewed address"),
            "bytes": ([(".game_rodata_1", 1, 0, BASE + 8, b"\xff" + good[1:])], "differs from US ROM"),
        }
        for label, (sections, message) in cases.items():
            with self.subTest(label), self.assertRaisesRegex(ValueError, message):
                self.compose(sections, [mapping(".game_rodata_1", BASE + 8, 4)])

    def test_nonzero_compiler_padding_is_rejected(self):
        with self.assertRaisesRegex(ValueError, "padding"):
            self.compose([(".game_rodata_1", 1, 0, BASE + 8, self.original[8:20] + b"\0\0\0\1")],
                         [mapping(".game_rodata_1", BASE + 8, 12, emitted=16)])


class PlacementTests(unittest.TestCase):
    def placements(self, text):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            for path in game_data.PLACEMENT_SCRIPTS:
                (root / path).parent.mkdir(parents=True, exist_ok=True)
                (root / path).write_text("SECTIONS {}\n")
            (root / game_data.PLACEMENT_SCRIPTS[0]).write_text(text)
            return game_data.placements(root, BASE, 0x100)

    @staticmethod
    def script(name, address, size, mode="INFO", selector="*game_1.o(.rodata)"):
        return (f"SECTIONS {{\n .{name} 0x{address:X} ({mode}) : SUBALIGN(4) {{ {selector} }}\n"
                f" ASSERT(SIZEOF(.{name}) == {size}, \"size\")\n}}\n")

    def test_selects_image_placements_and_skips_other_storage(self):
        text = (self.script("game_rodata_1", BASE + 0x10, 16)
                + self.script("sdk_main_data", 0x8002BE10, 16, "NOLOAD",
                              "build/game-libs/us/lib.a:controller.o(.data)")
                + self.script("sdk_pfs_bss", BASE + 0x20, 16, "NOLOAD",
                              "build/game-libs/us/lib.a:pfs.o(.bss)"))
        result = self.placements(text)
        self.assertEqual([m["output"] for m in result], [".game_rodata_1"])

    def test_noload_inside_the_image_is_rejected(self):
        with self.assertRaisesRegex(ValueError, "must be INFO"):
            self.placements(self.script("game_rodata_1", BASE + 0x10, 16, "NOLOAD"))

    def test_crossing_the_image_end_is_rejected(self):
        with self.assertRaisesRegex(ValueError, "crosses"):
            self.placements(self.script("game_rodata_1", BASE + 0xF8, 16))
        with self.assertRaisesRegex(ValueError, "crosses"):
            self.placements(self.script("game_rodata_1", BASE - 8, 16))

    def test_overlapping_payloads_are_rejected(self):
        text = self.script("game_rodata_1", BASE + 0x10, 16) + self.script("game_rodata_2", BASE + 0x18, 16)
        with self.assertRaisesRegex(ValueError, "overlap"):
            self.placements(text)


class LinkInputTests(unittest.TestCase):
    def test_source_and_sdk_selectors_name_the_actual_link_inputs(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            objects = game_data.linked_objects(root, ["src/done/game/sub/game_1.c", "src/game/game_2.c"])
            obj = objects["game_1"]
            obj.parent.mkdir(parents=True)
            obj.write_bytes(b"object")
            archive = root / "build/game-libs/us/libultrare.a"
            archive.parent.mkdir(parents=True)
            archive.write_bytes(b"archive")
            source = game_data.link_input(root, mapping(".game_rodata_1", BASE, 4), objects)
            self.assertEqual(source, {
                "kind": "source", "object": "build/game-integrated/us/src/done/game/sub/game_1.o",
                "source": "src/done/game/sub/game_1.c",
                "object_sha256": hashlib.sha256(b"object").hexdigest()})
            sdk = game_data.link_input(root, mapping(
                ".sdk_cosf_data", BASE, 4, selector="build/game-libs/us/libultrare.a:cosf.o(.data)"), objects)
            self.assertEqual(sdk["member"], "cosf.o")
            self.assertEqual(sdk["archive_sha256"], hashlib.sha256(b"archive").hexdigest())
            for selector, message in (("*game_2.o(.rodata)", "no integrated C object"),
                                      ("*game_9.o(.rodata)", "no integrated C object"),
                                      ("game_1.o(.rodata)", "unsupported selector")):
                with self.subTest(selector), self.assertRaisesRegex(ValueError, message):
                    game_data.link_input(root, mapping(".x", BASE, 4, selector=selector), objects)

    def test_duplicate_object_stems_are_ambiguous(self):
        with self.assertRaisesRegex(ValueError, "ambiguous"):
            game_data.linked_objects(ROOT, ["src/game/a/game_1.c", "src/game/b/game_1.c"])


class ManifestTests(unittest.TestCase):
    def test_build_writes_verified_image_and_stale_inputs_are_rejected(self):
        original = bytes(range(32))
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            out = root / game_data.BUILD_DIR
            obj = out / "src/done/game/game_1.o"
            obj.parent.mkdir(parents=True)
            obj.write_bytes(b"object")
            elf = out / "game.elf"
            elf.write_bytes(executable([(".game_rodata_1", 1, 0, BASE + 4, original[4:8])]))
            with patch.object(game_data.rom_span, "game_data", return_value=(original, BASE, "sha1")), \
                    patch.object(game_data, "placements",
                                 return_value=[mapping(".game_rodata_1", BASE + 4, 4)]):
                manifest = game_data.build(elf, out / "game.data.bin", out / "game.data.json",
                                           root=root, sources=["src/done/game/game_1.c"])
            self.assertEqual((out / "game.data.bin").read_bytes(), original)
            self.assertEqual((manifest["linked_bytes"], manifest["preserved_bytes"]), (4, 28))
            self.assertEqual(game_data.load_manifest(root)["elf_sha256"], manifest["elf_sha256"])
            elf.write_bytes(elf.read_bytes() + b"\0")
            with self.assertRaisesRegex(ValueError, "stale"):
                game_data.load_manifest(root)
            stored = json.loads((out / "game.data.json").read_text())
            stored["image"]["matches_rom"] = False
            (out / "game.data.json").write_text(json.dumps(stored))
            with self.assertRaisesRegex(ValueError, "failed proof"):
                game_data.load_manifest(root)


if __name__ == "__main__":
    unittest.main()
