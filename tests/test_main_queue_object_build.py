from __future__ import annotations

import os
from pathlib import Path
import shutil
import struct
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parent.parent


def compiler_object(relocation_count=7) -> tuple[bytes, int]:
    data = bytearray(52)
    data[:7] = b"\x7fELF\x01\x02\x01"
    struct.pack_into(">HHI", data, 16, 1, 8, 1)
    sections = [(0,) * 10]

    def section(kind, flags, payload, link=0, info=0, entry_size=0):
        offset = len(data)
        data.extend(payload)
        sections.append((0, kind, flags, 0, offset, len(payload), link, info, 4, entry_size))
        return offset

    section(1, 6, bytes(0x80))
    words = list(range(0x10, (relocation_count + 1) * 0x10, 0x10))
    words += [0] * (-len(words) % 4)
    table_offset = section(1, 2, struct.pack(">" + "I" * len(words), *words))
    symbols = bytes(16) + struct.pack(">IIIBBH", 0, 0, 0x80, 3, 0, 1)
    section(2, 0, symbols, info=2, entry_size=16)
    relocations = b"".join(struct.pack(">II", offset, 0x102) for offset in range(0, relocation_count * 4, 4))
    section(9, 0, relocations, link=3, info=2, entry_size=8)
    table = len(data)
    for entry in sections:
        data.extend(struct.pack(">10I", *entry))
    struct.pack_into(">I", data, 32, table)
    struct.pack_into(">HHHHHH", data, 40, 52, 0, 0, 40, len(sections), 0)
    return bytes(data), table_offset


@unittest.skipUnless(shutil.which("make"), "make is required for the object-cache regression")
class MainQueueObjectBuildTests(unittest.TestCase):
    def test_focused_check_overwrite_is_prepared_again_without_double_rebasing(self):
        self.check_object_refresh("init_2E50", 7)

    def test_selector_object_is_prepared_again_without_double_rebasing(self):
        self.check_object_refresh("init_11FA0", 5)

    def check_object_refresh(self, source_name, relocation_count):
        physical, table_offset = compiler_object(relocation_count)
        expected = bytearray(physical)
        for index, value in enumerate(range(0x10, (relocation_count + 1) * 0x10, 0x10)):
            struct.pack_into(">I", expected, table_offset + index * 4, 0x90000000 + value)

        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "scripts").mkdir()
            (root / "src/done/main").mkdir(parents=True)
            (root / "Makefile").write_bytes((ROOT / "Makefile").read_bytes())
            (root / "config/profiles").mkdir(parents=True)
            (root / "config/profiles/us.yaml").write_text("segments: []\n")
            (root / "scripts/profile_config.py").write_text(
                "import sys\nassert sys.argv[1] == 'make-original-assets'\n"
                f"print('source=src/done/main/{source_name}.c')\n")
            source = root / f"src/done/main/{source_name}.c"
            source.write_text("void queue_thread(void) {}\n")
            (root / "fixture.o").write_bytes(physical)
            # The compiler stub writes the same physical ELF produced by a focused check.
            (root / "scripts/compile_c.py").write_text(
                "import sys\nfrom pathlib import Path\n"
                "output = Path(sys.argv[sys.argv.index('--output') + 1])\n"
                "output.write_bytes(Path('fixture.o').read_bytes())\n")
            preparer = root / "scripts/prepare_main_library_object.py"
            preparer.write_bytes((ROOT / "scripts/prepare_main_library_object.py").read_bytes())
            (root / "scripts/list_integrated_sources.py").write_text(
                "import sys\n"
                "if '--overlay' in sys.argv and sys.argv[sys.argv.index('--overlay') + 1] == 'main':\n"
                f"    print('src/done/main/{source_name}.c')\n")
            # This fixture builds code only, so it has no asset bins.
            for script in ("font_splits.py", "audio_boundaries.py", "mp3_bank.py"):
                (root / "scripts" / script).write_text(
                    "import sys\n"
                    "assert sys.argv[1:] == ['list-bins']\n")
            target = f"build/us/src/done/main/{source_name}.o"
            command = [shutil.which("make"), "--no-print-directory", "--silent", target, "PROFILE=us"]
            subprocess.run(command, cwd=root, capture_output=True, text=True, check=True)
            output = root / target
            self.assertEqual(output.read_bytes(), bytes(expected))

            # A newer focused-check object must not bypass the alias preparation recipe.
            output.write_bytes(physical)
            latest = max(p.stat().st_mtime_ns for p in [source, root / "Makefile", preparer,
                                                       root / "scripts/compile_c.py"])
            os.utime(output, ns=(latest + 1_000_000_000, latest + 1_000_000_000))
            subprocess.run(command, cwd=root, capture_output=True, text=True, check=True)
            self.assertEqual(output.read_bytes(), bytes(expected))

            subprocess.run(command, cwd=root, capture_output=True, text=True, check=True)
            self.assertEqual(output.read_bytes(), bytes(expected))


if __name__ == "__main__":
    unittest.main()
