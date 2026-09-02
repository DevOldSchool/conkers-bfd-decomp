from __future__ import annotations

import re
import unittest
from pathlib import Path

import yaml


ROOT = Path(__file__).resolve().parent.parent
SUBSEGMENT_PATTERN = re.compile(r"\s+- \[(0x[0-9A-Fa-f]+),\s*(asm|hasm|c|lib)(?:,\s*([^\]]+))?\]")


def segment_subsegments(path: Path, name: str) -> list[tuple[int, str, str | None]]:
    lines = path.read_text(encoding="utf-8").splitlines()
    segment_start = next(
        index
        for index, line in enumerate(lines)
        if re.match(rf"  - name:\s*{re.escape(name)}\s*$", line)
    )
    subsegments = next(
        index
        for index in range(segment_start + 1, len(lines))
        if lines[index].strip() == "subsegments:"
    )
    result = []
    for line in lines[subsegments + 1 :]:
        if line.startswith("  - ") and not line.startswith("      - "):
            break
        match = SUBSEGMENT_PATTERN.fullmatch(line)
        if match:
            result.append((int(match.group(1), 16), match.group(2), match.group(3)))
    return result


class SegmentMapTests(unittest.TestCase):
    def test_production_source_tree_has_no_fixture_directory(self) -> None:
        self.assertFalse((ROOT / "src" / "fixtures").exists())

    def test_working_maps_preserve_reference_main_boundaries(self) -> None:
        expected_counts = {"us": (179, 167), "eu": (119, 119)}
        for region, (working_count, reference_count) in expected_counts.items():
            working = segment_subsegments(ROOT / "config" / "profiles" / f"{region}.yaml", "main")
            reference = segment_subsegments(ROOT / "config" / "reference" / f"{region}.yaml", "main")
            self.assertEqual(reference_count, len(reference))
            self.assertEqual(working_count, len(working))
            self.assertEqual(0x1050, working[0][0])
            self.assertEqual(sorted({offset for offset, _, _ in working}), [entry[0] for entry in working])
            working_by_offset = {entry[0]: entry for entry in working}
            for reference_entry in reference:
                working_entry = working_by_offset[reference_entry[0]]
                if working_entry[1] != "lib":
                    self.assertEqual(reference_entry, working_entry)

    def test_us_libultra_objects_keep_raw_reference_ranges(self) -> None:
        working = {
            offset: (kind, name)
            for offset, kind, name in segment_subsegments(ROOT / "config" / "profiles" / "us.yaml", "main")
        }
        reference = {
            offset: (kind, name)
            for offset, kind, name in segment_subsegments(ROOT / "config" / "reference" / "us.yaml", "main")
        }
        linked_objects = {
            0x22A30: ("setsr", "libultra/os/setsr"),
            0x22A40: ("getsr", "libultra/os/getsr"),
            0x22A50: ("setfpccsr", "libultra/os/setfpccsr"),
            0x22A60: ("startthread", "libultra/os/startthread"),
            0x22BB0: ("setthreadpri", "libultra/os/setthreadpri"),
            0x22E00: ("stopthread", "libultra/os/stopthread"),
            0x233C0: ("virtualtophysical", "libultra/os/virtualtophysical"),
            0x23440: ("recvmesg", "libultra/os/recvmesg"),
            0x23580: ("sendmesg", "libultra/os/sendmesg"),
            0x23790: ("createmesgqueue", "libultra/os/createmesgqueue"),
            0x23830: ("getthreadpri", "libultra/os/getthreadpri"),
            0x23DA0: ("spsetstat", "libultra/io/spsetstat"),
            0x24770: ("getcount", "libultra/os/getcount"),
            0x24780: ("thread", "libultra/os/thread"),
            0x24A30: ("aigetstat", "libultra/io/aigetstat"),
            0x24BA0: ("sptaskyield", "libultra/io/sptaskyield"),
            0x24F40: ("gettime", "libultra/os/gettime"),
            0x262C0: ("pigetstat", "libultra/io/pigetstat"),
            0x262D0: ("unmaptlb", "libultra/os/unmaptlb"),
            0x26530: ("sqrtf", "libultra/gu/sqrtf"),
            0x27490: ("setcompare", "libultra/os/setcompare"),
            0x274A0: ("jammesg", "libultra/os/jammesg"),
            0x27620: ("spgetstat", "libultra/io/spgetstat"),
            0x226F0: ("bzero", "libultra/libc/bzero"),
            0x22C90: ("invalicache", "libultra/os/invalicache"),
            0x22D10: ("invaldcache", "libultra/os/invaldcache"),
            0x230F0: ("xlitob", "libultra/libc/xlitob"),
            0x236D0: ("piacs", "libultra/io/piacs"),
            0x23A10: ("bcopy", "libultra/libc/bcopy"),
            0x23D20: ("writebackdcache", "libultra/os/writebackdcache"),
            0x24880: ("setintmask", "libultra/os/setintmask"),
            0x24F10: ("writebackdcacheall", "libultra/os/writebackdcacheall"),
            0x25700: ("siacs", "libultra/io/siacs"),
            0x26310: ("maptlb", "libultra/os/maptlb"),
            0x26540: ("sinf", "libultra/gu/sinf"),
            0x26800: ("ll", "libultra/libc/ll"),
            0x273D0: ("probetlb", "libultra/os/probetlb"),
        }
        for offset, (object_name, reference_name) in linked_objects.items():
            self.assertEqual(("lib", f"libultra_2_0L, {object_name}, .text"), working[offset])
            self.assertEqual(("asm", reference_name), reference[offset])

        linked_sections = {
            0x2BD30: "libultra_2_0L, xlitob, .data",
            0x2BD60: "libultra_2_0L, piacs, .data",
            0x2BE20: "libultra_2_0L, siacs, .data",
            0x2BDF0: "libultra_2_0L, thread, .data",
            0x2BE80: "libultra_2_0L, vimodempallan1, .data",
            0x2BED0: "libultra_2_0L, vimodentsclan1, .data",
            0x2C850: "libultra_2_0L, setintmask, .rodata",
            0x2C8D0: "libultra_2_0L, sinf, .rodata",
            0x2C920: "libultra_2_0L, libm_vals, .rodata",
        }
        for offset, section in linked_sections.items():
            self.assertEqual(("lib", section), working[offset])
            self.assertNotEqual("lib", reference.get(offset, (None, None))[0])

        profile = yaml.safe_load((ROOT / "config" / "profiles" / "us.yaml").read_text(encoding="utf-8"))
        main = next(segment for segment in profile["segments"] if segment.get("name") == "main")
        linked_bss = [
            entry
            for entry in main["subsegments"]
            if isinstance(entry, dict)
            and entry.get("type") == "lib"
            and entry.get("name") == "libultra_2_0L"
            and entry.get("section") == ".bss"
        ]
        self.assertEqual(
            [
                (0x800428F0, "piacs"),
                (0x80042AA0, "siacs"),
            ],
            [(entry["vram"], entry["object"]) for entry in linked_bss],
        )

    def test_us_2_0i_objects_link_from_archive_and_keep_raw_reference(self) -> None:
        expected = {
            0x22DC0: "libultra/os/interrupt",
            0x22EC0: "libultra/libc/string",
            0x22F60: "libultra/libc/ldiv",
            0x23390: "libultra/io/ai",
            0x237C0: "libultra/os/seteventmesg",
            0x23850: "libultra/io/pirawdma",
            0x23DB0: "libultra/io/spsetpc",
            0x23DF0: "libultra/io/sprawdma",
            0x23E80: "libultra/io/sp",
            0x23EB0: "libultra/os/timerintr",
            0x24410: "libultra/io/viswapcontext",
            0x247C0: "libultra/io/visetmode",
            0x24830: "libultra/io/viswapbuf",
            0x24920: "libultra/io/pidma",
            0x24A40: "libultra/os/settimer",
            0x24B20: "libultra/io/sptaskyielded",
            0x24E20: "libultra/io/vigetcurrframebuf",
            0x24E60: "libultra/io/vigetnextframebuf",
            0x24EA0: "libultra/io/visetevent",
            0x257C0: "libultra/io/sirawdma",
            0x25FD0: "libultra/io/crc",
            0x26250: "libultra/io/viblack",
            0x263D0: "libultra/io/aisetfreq",
            0x26700: "libultra/io/sirawread",
            0x26750: "libultra/io/sirawwrite",
            0x267A0: "libultra/io/pirawread",
            0x26AC0: "libultra/os/sethwinterrupt",
            0x275F0: "libultra/io/pigetcmdq",
            0x27630: "libultra/io/si",
            0x27910: "libultra/io/contpfs",
            0x28670: "libultra/io/pfschecker",
        }
        working = {
            offset: (kind, name)
            for offset, kind, name in segment_subsegments(
                ROOT / "config/profiles/us.yaml", "main"
            )
        }
        reference = {
            offset: (kind, name)
            for offset, kind, name in segment_subsegments(
                ROOT / "config/reference/us.yaml", "main"
            )
        }
        for offset, name in expected.items():
            object_name = name.rsplit("/", 1)[1]
            self.assertEqual(
                ("lib", f"libultra_2_0I, {object_name}, .text"), working[offset]
            )
            self.assertEqual(("asm", name), reference[offset])
        self.assertEqual(("asm", None), working[0x290D0])
        self.assertEqual(("asm", None), reference[0x290D0])
        self.assertNotIn(0x23060, working)
        self.assertNotIn(0x23060, reference)

        self.assertEqual(
            ("lib", "libultra_2_0I, timerintr, .data"), working[0x2BD70]
        )
        profile = yaml.safe_load(
            (ROOT / "config/profiles/us.yaml").read_text(encoding="utf-8")
        )
        main = next(segment for segment in profile["segments"] if segment.get("name") == "main")
        linked_bss = {
            entry["vram"]: (entry["name"], entry["object"])
            for entry in main["subsegments"]
            if isinstance(entry, dict) and entry.get("type") == "lib"
        }
        self.assertEqual(("libultra_2_0I", "seteventmesg"), linked_bss[0x80042910])
        self.assertEqual(("libultra_2_0I", "timerintr"), linked_bss[0x80042990])

    def test_us_libultrare_objects_link_from_archive_and_keep_raw_reference(self) -> None:
        expected = {
            0x22790: "libultrare/os/initialize",
            0x23930: "libultrare/io/epirawdma",
            0x24BC0: "libultrare/io/contreaddata",
            0x24FD0: "libultrare/io/pfsisplug",
            0x25340: "libultrare/io/controller",
            0x25870: "libultrare/io/contramwrite",
            0x25C20: "libultrare/io/contramread",
            0x26150: "libultrare/os/destroythread",
            0x26B10: "libultrare/io/leointerrupt",
            0x27660: "libultrare/io/pfsinit",
            0x27820: "libultrare/io/leodiskinit",
        }
        working = {
            offset: (kind, name)
            for offset, kind, name in segment_subsegments(
                ROOT / "config/profiles/us.yaml", "main"
            )
        }
        reference = {
            offset: (kind, name)
            for offset, kind, name in segment_subsegments(
                ROOT / "config/reference/us.yaml", "main"
            )
        }
        for offset, name in expected.items():
            object_name = name.rsplit("/", 1)[1]
            self.assertEqual(
                ("lib", f"libultrare, {object_name}, .text"), working[offset]
            )
            self.assertEqual(("asm", name), reference[offset])

        self.assertEqual(("lib", "libultrare, initialize, .data"), working[0x2BD10])
        self.assertEqual(("lib", "libultrare, controller, .data"), working[0x2BE10])
        profile = yaml.safe_load(
            (ROOT / "config/profiles/us.yaml").read_text(encoding="utf-8")
        )
        main = next(segment for segment in profile["segments"] if segment.get("name") == "main")
        linked_bss = {
            entry["vram"]: (entry["name"], entry["object"])
            for entry in main["subsegments"]
            if isinstance(entry, dict) and entry.get("type") == "lib"
        }
        self.assertEqual(("libultrare", "initialize"), linked_bss[0x800428E0])
        self.assertEqual(("libultrare", "pfsisplug"), linked_bss[0x800429D0])
        self.assertEqual(("libultrare", "controller"), linked_bss[0x80042A10])
        self.assertEqual(("libultrare", "leointerrupt"), linked_bss[0x80042AC0])
        self.assertEqual(("libultrare", "leodiskinit"), linked_bss[0x80043AC0])

    def test_game_maps_cover_all_reviewed_raw_boundaries(self) -> None:
        expected = {
            "us": (539, 0x0, 0x1F9BF0),
            "eu": (537, 0x0, 0x1FA3E0),
        }
        for region, (count, first, last) in expected.items():
            entries = segment_subsegments(ROOT / "config" / "game" / f"{region}.yaml", "game")
            offsets = [offset for offset, _, _ in entries]
            self.assertEqual(count, len(entries))
            self.assertEqual(first, offsets[0])
            self.assertEqual(last, offsets[-1])
            self.assertEqual(sorted(set(offsets)), offsets)

    def test_existing_named_us_reference_splits_are_preserved(self) -> None:
        entries = segment_subsegments(ROOT / "config" / "game" / "us.yaml", "game")
        names = {offset: name for offset, _, name in entries if name is not None}
        self.assertEqual("game_3BFD0", names[0xEB20])
        self.assertEqual("game_1765E0", names[0x149130])
        self.assertEqual("game/game_1A6300", names[0x178E50])
        self.assertEqual("game/game_1BFC70", names[0x1927C0])


if __name__ == "__main__":
    unittest.main()
