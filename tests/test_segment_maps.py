from __future__ import annotations

import json
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
    def test_main_initialized_sections_follow_linker_group_order(self) -> None:
        profile = yaml.safe_load((ROOT / "config/profiles/us.yaml").read_text())
        main = next(segment for segment in profile["segments"] if segment.get("name") == "main")
        seen_rodata = False
        for entry in main["subsegments"]:
            if isinstance(entry, dict):
                section = entry.get("linker_section_order", entry.get("section", ""))
            elif isinstance(entry, list):
                section = entry[4] if entry[1] == "lib" else f".{entry[1]}"
            else:
                continue
            if section == ".rodata":
                seen_rodata = True
            elif section == ".data":
                # Splat groups .data before .rodata regardless of map order.
                # Interleaving them moves otherwise exact archive sections.
                offset = entry["start"] if isinstance(entry, dict) else entry[0]
                self.assertFalse(seen_rodata, f"data after rodata at {offset:#x}")

    def test_production_source_tree_has_no_fixture_directory(self) -> None:
        self.assertFalse((ROOT / "src" / "fixtures").exists())

    def test_working_maps_preserve_reference_main_boundaries(self) -> None:
        # xprintf's rodata uses an explicit dictionary to preserve linker order.
        expected_counts = {"us": (204, 167), "eu": (119, 119)}
        for region, (working_count, reference_count) in expected_counts.items():
            working = segment_subsegments(ROOT / "config" / "profiles" / f"{region}.yaml", "main")
            reference = segment_subsegments(ROOT / "config" / "reference" / f"{region}.yaml", "main")
            self.assertEqual(reference_count, len(reference))
            self.assertEqual(working_count, len(working))
            self.assertEqual(0x1050, working[0][0])
            self.assertEqual(sorted({offset for offset, _, _ in working}), [entry[0] for entry in working])
            working_by_offset = {entry[0]: entry for entry in working}
            for reference_entry in reference:
                if region == "us" and reference_entry[0] == 0x17C00:
                    # The raw navigation split lies inside the complete,
                    # independently reconstructed channel-control object.
                    self.assertEqual(
                        ("lib", "libultrare, n_cspchan, .text"),
                        working_by_offset[0x17AF0][1:],
                    )
                    self.assertEqual((0x17C00, "asm", None), reference_entry)
                    continue
                if region == "us" and reference_entry[0] == 0x292F0:
                    # The historical CPU split is inside a complete RSP payload.
                    self.assertEqual((0x292F0, "data", None), reference_entry)
                    self.assertEqual(("lib", "librsp, asp_overlay0, .text"),
                                     working_by_offset[0x291A0][1:])
                    self.assertIn(0x2A110, working_by_offset)
                    continue
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
        self.assertEqual(("lib", "librsp, rspboot, .text"), working[0x290D0])
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
            if isinstance(entry, dict) and entry.get("type") == "lib" and entry.get("section") == ".bss"
        }
        self.assertEqual(("libultra_2_0I", "seteventmesg"), linked_bss[0x80042910])
        self.assertEqual(("libultra_2_0I", "timerintr"), linked_bss[0x80042990])

    def test_us_debug_audio_objects_link_from_archive_and_keep_raw_reference(self) -> None:
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
        linked_text = {
            0x17A80: "cspgetstate",
            0x17EC0: "cspgettempo",
            0x19AB0: "cents2ratio",
        }
        for offset, object_name in linked_text.items():
            self.assertEqual(
                ("lib", f"libultra_2_0L_d, {object_name}, .text"),
                working[offset],
            )
            self.assertEqual(("asm", None), reference[offset])

        self.assertEqual(
            ("lib", "libultra_2_0L_d, cents2ratio, .rodata"),
            working[0x2C760],
        )
        self.assertNotIn(0x2C760, reference)

        profile = yaml.safe_load(
            (ROOT / "config/profiles/us.yaml").read_text(encoding="utf-8")
        )
        main = next(segment for segment in profile["segments"] if segment.get("name") == "main")
        self.assertIn([0x2C770, "lib", "libultrare", "n_drvrNew", ".rodata"], main["subsegments"])

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

        self.assertEqual(("lib", "libultrare, vi, .text"), working[0x242B0])
        self.assertEqual(("asm", None), reference[0x242B0])
        self.assertEqual(("lib", "libultrare, initialize, .data"), working[0x2BD10])
        self.assertEqual(("lib", "libultrare, vi, .data"), working[0x2BD80])
        self.assertEqual(("lib", "libultrare, controller, .data"), working[0x2BE10])
        self.assertEqual(
            ("lib", "libultrare, vimodepallan1, .data"), working[0x2BE30]
        )
        self.assertEqual(
            ("lib", "libultrare, xprintf, .data"), working[0x2AAF0]
        )
        self.assertEqual(
            ("lib", "libultrare, syncputchars_data, .data"), working[0x2B9D0]
        )
        self.assertEqual(
            ("lib", "libultrare, xldtob, .text"), working[0x1550]
        )
        self.assertEqual(("lib", "libultrare, xprintf, .text"), working[0x20D0])
        self.assertEqual(("asm", None), reference[0x20D0])
        self.assertEqual(("asm", None), reference[0x1550])
        self.assertEqual(
            ("lib", "libultrare, exceptasm_data, .data"), working[0x2C1B0]
        )
        self.assertNotIn(0x2BD80, reference)
        self.assertNotIn(0x2BE30, reference)
        for offset in (0x2AAF0, 0x2B9D0, 0x2BF80, 0x2C1B0):
            self.assertNotIn(offset, reference)
        profile = yaml.safe_load(
            (ROOT / "config/profiles/us.yaml").read_text(encoding="utf-8")
        )
        main = next(segment for segment in profile["segments"] if segment.get("name") == "main")
        self.assertIn(
            {"start": 0x2BF80, "type": "lib", "name": "libultrare", "object": "xprintf",
             "section": ".rodata", "linker_section_order": ".data"},
            main["subsegments"],
        )
        self.assertIn(
            {"start": 0x2BF20, "type": "lib", "name": "libultrare", "object": "xldtob",
             "section": ".rodata", "linker_section_order": ".data"},
            main["subsegments"],
        )
        linked_bss = {
            entry["vram"]: (entry["name"], entry["object"])
            for entry in main["subsegments"]
            if isinstance(entry, dict) and entry.get("type") == "lib" and entry.get("section") == ".bss"
        }
        self.assertEqual(("libultrare", "initialize"), linked_bss[0x800428E0])
        self.assertEqual(("libultrare", "n_csplayer"), linked_bss[0x80042810])
        self.assertIn({"type": "bss", "name": 42850, "vram": 0x80042850}, main["subsegments"])
        self.assertEqual(("libultrare", "pfsisplug"), linked_bss[0x800429D0])
        self.assertEqual(("libultrare", "controller"), linked_bss[0x80042A10])
        self.assertEqual(("libultrare", "leointerrupt"), linked_bss[0x80042AC0])
        self.assertEqual(("libultrare", "leodiskinit"), linked_bss[0x80043AC0])

    def test_conker_audio_library_sections_preserve_raw_reference(self) -> None:
        entries = segment_subsegments(ROOT / "config/profiles/us.yaml", "main")
        ranges = {a: (b, kind, name) for (a, kind, name), (b, _, _) in zip(entries, entries[1:])}
        reference = {
            offset: (kind, name)
            for offset, kind, name in segment_subsegments(ROOT / "config/reference/us.yaml", "main")
        }
        for start, end, member in (
            (0x13320, 0x15550, "n_csplayer"),
            (0x15550, 0x155A0, "n_cspsetbank"),
            (0x17AA0, 0x17AF0, "n_cspplay"),
            (0x17D80, 0x17DF0, "n_cspsetpan"),
            (0x18CB0, 0x18D00, "n_cspsetseq"),
            (0x18D00, 0x18D50, "n_cspsetvol"),
            (0x18D50, 0x18DA0, "n_cspstop"),
            (0x18DA0, 0x18E60, "n_sl"),
            (0x19B50, 0x1AAE0, "n_cspctrl"),
            (0x1C060, 0x1C690, "n_event"),
            (0x1C690, 0x1C770, "n_synaddplayer"),
            (0x1C770, 0x1C810, "n_synstopvoice"),
            (0x1C810, 0x1C910, "n_synfreevoice"),
            (0x1C910, 0x1C9E0, "n_synsetvol"),
            (0x1C9E0, 0x1CA90, "n_synsetpitch"),
            (0x1CA90, 0x1CB40, "n_synfilter13"),
            (0x1CB40, 0x1CBF0, "n_synfilter12"),
            (0x1D900, 0x1DBA0, "n_synfx"),
            (0x1DC80, 0x1E170, "n_synallocvoice"),
            (0x1E170, 0x1E2A0, "n_synstartvoiceparam"),
            (0x1E2A0, 0x1E350, "n_synsetpan"),
            (0x1E350, 0x1E400, "n_synfilter11"),
            (0x1E400, 0x1E480, "n_cspsendmidi"),
            (0x1E480, 0x1E4A0, "n_syndelete"),
            (0x1E4A0, 0x1E530, "n_synallocfx"),
            (0x1FFE0, 0x20000, "n_synsetpriority"),
        ):
            self.assertEqual((end, "lib", f"libultrare, {member}, .text"), ranges[start])
            self.assertEqual(("asm", None), reference[start])
        profile = yaml.safe_load((ROOT / "config/profiles/us.yaml").read_text())
        main = next(segment for segment in profile["segments"] if segment.get("name") == "main")
        self.assertIn([0x2BA40, "lib", "libultrare", "n_sl", ".data"], main["subsegments"])
        self.assertIn([0x2BA50, "lib", "libultrare", "n_csplayer", ".data"], main["subsegments"])
        self.assertIn([0x2BBE0, "data"], main["subsegments"])
        self.assertIn([0x2C460, "lib", "libultrare", "n_csplayer", ".rodata"], main["subsegments"])
        self.assertIn([0x2C6B0, "lib", "libultrare", "n_sndplayer", ".rodata"], main["subsegments"])
        self.assertIn([0x2BA20, "lib", "libultrare", "n_sndplayer", ".data"], main["subsegments"])
        self.assertEqual((0x17870, "lib", "libultrare, n_sndplayer, .text"), ranges[0x155A0])
        # The reference retains its larger bank-wrapper/sound-player raw block.
        self.assertNotIn(0x155A0, reference)
        self.assertEqual(("asm", None), reference[0x15550])
        self.assertIn([0x2C790, "lib", "libultrare", "n_synfx", ".rodata"], main["subsegments"])
        self.assertIn([0x2C7A0, "lib", "libultrare", "n_reverb", ".rodata"], main["subsegments"])

    def test_game_maps_cover_all_reviewed_raw_boundaries(self) -> None:
        expected = {
            "us": (544, 0x0, 0x1F9BF0),
            "eu": (537, 0x0, 0x1FA3E0),
        }
        units = json.loads((ROOT / "progress/source_units.json").read_text())["source_units"]
        functions = {
            item["symbol"]: item
            for item in json.loads((ROOT / "progress/functions.json").read_text())["functions"]
        }
        for region, (count, first, last) in expected.items():
            entries = segment_subsegments(ROOT / "config" / "game" / f"{region}.yaml", "game")
            offsets = [offset for offset, _, _ in entries]
            self.assertGreaterEqual(len(entries), count)
            self.assertEqual(first, offsets[0])
            self.assertEqual(last, offsets[-1])
            self.assertEqual(sorted(set(offsets)), offsets)
            for unit in units:
                if not unit.get("boundary_evidence", {}).get(region, {}).get("reviewed"):
                    continue
                if any(functions[symbol].get("overlay", "main") != "game" for symbol in unit["functions"]):
                    continue
                bounds = unit["regions"][region]
                with self.subTest(region=region, source=unit["source"]):
                    self.assertIn(int(bounds["start"], 0), offsets)
                    self.assertIn(int(bounds["end"], 0), offsets)

    def test_mp3_libraries_preserve_their_raw_comparison(self) -> None:
        entries = segment_subsegments(ROOT / "config/game/us.yaml", "game")
        ranges = {a: (b, kind, name) for (a, kind, name), (b, _, _) in zip(entries, entries[1:])}
        self.assertEqual((0x1F8870, "lib", "libultrare, main, .text"), ranges[0x1F7F60])
        self.assertEqual((0x1F7F60, "lib", "libultrare, decoder, .text"), ranges[0x1F3DE0])
        self.assertEqual((0x4A5E0, "asm", None), ranges[0x4A400])
        self.assertEqual((0x1F9BF0, "lib", "libultrare, lib_46650, .text"), ranges[0x1F8CF0])
        from scripts.prepare_game_reference import raw_reference_map
        profile = yaml.safe_load(raw_reference_map((ROOT / "config/game/us.yaml").read_text()))
        reference = next(segment for segment in profile["segments"] if segment.get("name") == "game")
        self.assertIn([0x1F3DE0, "asm"], reference["subsegments"])
        self.assertIn([0x1F2960, "asm"], reference["subsegments"])
        self.assertIn([0x4A2B0, "asm"], reference["subsegments"])
        self.assertIn([0x4A620, "asm"], reference["subsegments"])
        self.assertIn([0x4A730, "asm"], reference["subsegments"])
        self.assertIn([0x1F7F60, "asm"], reference["subsegments"])
        self.assertIn([0x1F8CF0, "asm"], reference["subsegments"])
        self.assertEqual((0x1F8CF0, "lib", "libultrare, util, .text"), ranges[0x1F8870])
        self.assertIn([0x1F8870, "asm"], reference["subsegments"])
        self.assertIn([0x1F9BF0, "asm"], reference["subsegments"])
        self.assertNotIn([0x1F7F60, "lib", "libultrare", "main", ".text"], reference["subsegments"])

    def test_additional_game_sdk_sections_have_exact_extents(self) -> None:
        entries = segment_subsegments(ROOT / "config/game/us.yaml", "game")
        ranges = {a: (b, kind, name) for (a, kind, name), (b, _, _) in zip(entries, entries[1:])}
        for start, end, archive, member in (
            (0x47C00, 0x47D60, "libultrare", "cosf"),
            (0x47D60, 0x47F00, "libultrare", "sinf"),
            (0x47F00, 0x48190, "libultrare", "perspective"),
            (0x48190, 0x48360, "libultrare", "rotate"),
            (0x4A2B0, 0x4A400, "libultrare", "expf"),
            (0x4A620, 0x4A730, "libultrare", "logf"),
            (0x1EF040, 0x1EF080, "libultra_2_0I", "piread"),
            (0x1EF080, 0x1EF090, "libultra_2_0I", "sqrtf"),
            (0x1EF090, 0x1EF450, "libultrare", "controller"),
            (0x1EF450, 0x1EF610, "libultrare", "pfsinit"),
            (0x1EFAA0, 0x1EFD00, "libultrare", "contreaddata"),
            (0x1EFD00, 0x1EFF70, "libultrare", "mtxutil"),
            (0x1F0140, 0x1F0350, "libultra_2_0I", "mtxcatf"),
            (0x1F0350, 0x1F0410, "libultrare", "siacs_game"),
            (0x1F0410, 0x1F04C0, "libultra_2_0I", "sirawdma"),
            (0x1F1D10, 0x1F2080, "libultrare", "pfsisplug"),
            (0x1F2080, 0x1F2430, "libultrare", "contramread"),
            (0x1F2430, 0x1F27E0, "libultrare", "contramwrite"),
            (0x1F27E0, 0x1F2960, "libultra_2_0I", "crc"),
        ):
            with self.subTest(member=member):
                self.assertEqual((end, "lib", f"{archive}, {member}, .text"), ranges[start])
        self.assertEqual((0x1F3DE0, "lib", "libultrare, playback, .text"), ranges[0x1F2960])

    def test_named_us_splits_keep_identity_after_source_integration(self) -> None:
        entries = segment_subsegments(ROOT / "config" / "game" / "us.yaml", "game")
        names = {offset: name for offset, _, name in entries if name is not None}
        self.assertEqual("game_3BFD0", names[0xEB20])
        self.assertEqual("game/game_1765E0", names[0x149130])
        self.assertEqual("game/game_1A6300", names[0x178E50])
        self.assertEqual("game/game_1BFC70", names[0x1927C0])
        self.assertIn((0x149130, "c", "game/game_1765E0"), entries)

        from scripts.prepare_game_reference import raw_reference_map
        profile = yaml.safe_load(raw_reference_map((ROOT / "config/game/us.yaml").read_text()))
        reference = next(segment for segment in profile["segments"] if segment.get("name") == "game")
        self.assertIn([0xEB20, "asm", "game_3BFD0"], reference["subsegments"])
        self.assertIn([0x149130, "asm"], reference["subsegments"])
        self.assertIn([0x149550, "asm"], reference["subsegments"])


if __name__ == "__main__":
    unittest.main()
