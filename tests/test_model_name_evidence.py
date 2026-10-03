"""Current-ROM evidence contracts; source identity does not prove naming confidence.

The shared semantic-name tests audit every registry model and consumer. This
module keeps the source-specific joins, placements, attachment events and ABI
exceptions which cannot be replaced by that generic audit. ROM bytes stay local.
"""
from collections import Counter
import hashlib
import json
import struct
import unittest

from scripts import model_assets as models
from scripts import model_attachment_events as events
from scripts import model_character_parts as parts
from scripts import model_semantic_names as names
import model_name_evidence_fixtures as pins


ROM = names.ROOT / "roms/baserom.us.z64"
PAYLOAD_FIELDS = ("header_hex", "record_hex", "event_hex")


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def normalize_payloads(value):
    """Keep decoded fields, but never expose owned-ROM bytes in assertion output."""
    if isinstance(value, list):
        return [normalize_payloads(item) for item in value]
    if not isinstance(value, dict):
        return value
    result = {}
    for key, item in value.items():
        if key in PAYLOAD_FIELDS:
            pin_key = key[:-4] + "_pin"
            if pin_key in value:
                raise ValueError("conflicting witness payload pin")
            if not isinstance(item, str):
                raise ValueError("invalid witness payload encoding")
            try:
                raw = bytes.fromhex(item)
            except ValueError:
                raise ValueError("invalid witness payload encoding") from None
            if raw.hex() != item:
                raise ValueError("invalid witness payload encoding")
            result[pin_key] = {"size_bytes": len(raw), "sha256": sha256(raw)}
        elif key.endswith("_hex"):
            raise ValueError("unreviewed witness payload field")
        else:
            result[key] = normalize_payloads(item)
    return result


class ModelNameSourceEvidenceTests(unittest.TestCase):
    def test_exact_canonical_validation_numeric_joins(self):
        canonical = json.loads((names.ROOT / "config/model-inspection.json").read_text())["models"]
        validation = json.loads((names.ROOT / "config/model-validation.json").read_text())["render_cases"]
        for bank, entry, ci, vi, source_name, render_case, source_path in pins.SOURCE_JOINS:
            with self.subTest(bank=bank, entry=entry):
                c, v = canonical[ci], validation[vi]
                self.assertEqual((source_name, render_case), (c["name"], c["render_case"]))
                self.assertEqual((render_case, source_path), (v["id"], v["source"]))
                self.assertEqual([vi], [i for i, r in enumerate(validation) if r["source"] == source_path])
                self.assertEqual([ci], [i for i, r in enumerate(canonical) if r.get("render_case") == render_case])
                # Older bank-03 paths use the explicit non-rom-only root. Both
                # roots must still select the same bank, entry and segment.
                recovered = source_path.replace("build/assets/models/", "build/assets/models/rom-only/", 1) if "/rom-only/" not in source_path else source_path
                self.assertEqual(f"build/assets/models/rom-only/us-bank-{bank:02x}-preview/geometry/{entry:04d}-00.gltf", recovered)
        for entry in pins.UNJOINED_CHARACTERS:
            with self.subTest(unjoined=entry):
                suffix = f"/us-bank-01-preview/geometry/{entry:04d}-00.gltf"
                self.assertFalse(any(r["source"].endswith(suffix) for r in validation))
                self.assertFalse(any(r.get("name") == f"character-bank01-{entry:04d}-rom" for r in canonical))

    def test_current_canonical_identities_preserve_search_aliases(self):
        canonical = json.loads((names.ROOT / "config/model-inspection.json").read_text())["models"]
        for index, source_name, render_case, label, aliases in pins.CANONICAL_IDENTITIES:
            with self.subTest(index=index):
                row = canonical[index]
                self.assertEqual((source_name, render_case, label), (row["name"], row["render_case"], row["label"]))
                self.assertTrue(set(aliases) <= set(row.get("aliases", [])))

    def test_payload_normalization_rejects_unreviewed_or_ambiguous_encodings(self):
        raw = bytes(range(12))  # Synthetic; never an original-record fixture.
        row = {"event_hex": raw.hex(), "action": 7, "nested": [{"kind": 1}]}
        self.assertEqual({"event_pin": {"size_bytes": 12, "sha256": sha256(raw)},
                          "action": 7, "nested": [{"kind": 1}]}, normalize_payloads(row))
        for value in (None, 7, "not hexadecimal", raw.hex().upper(), raw.hex() + " "):
            with self.subTest(value=value), self.assertRaisesRegex(ValueError, "invalid witness payload encoding"):
                normalize_payloads({"event_hex": value})
        for row, error in (({"event_hex": raw.hex(), "event_pin": {}}, "conflicting"),
                           ({"unreviewed_hex": raw.hex()}, "unreviewed")):
            with self.assertRaisesRegex(ValueError, error):
                normalize_payloads(row)


@unittest.skipUnless(ROM.is_file(), "owned US ROM unavailable")
class CurrentRomModelNameEvidenceTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.path, cls.layout = models.resolve_rom("us", ROM)
        cls.rom, _ = models.normalize_rom(cls.path.read_bytes())
        cls.registry = names.load_registry()
        if hashlib.sha1(cls.rom).hexdigest() != cls.registry["rom_sha1"]:
            raise ValueError("owned ROM identity changed")
        cls.game = models.parse_game_archive(cls.rom[cls.layout["game_start"]:cls.layout["game_end"]])
        cls.banks = {b.index: b for b in models.parse_asset_banks(cls.rom, cls.layout["asset_table"])}
        cls.sources = {}
        cls.placement_tables = {}

    def source(self, bank, entry, segment=0):
        if bank not in self.sources:
            _, _, _, bundles, _ = models.load_model_bundles("us", self.path, bank)
            self.sources[bank] = {(b.index, s.index): s.data for b in bundles for s in b.segments}
        return self.sources[bank][entry, segment]

    def asset(self, bank, entry):
        records = {e.index: e for e in models.parse_asset_entries(self.rom, self.banks[bank])}
        record = records[entry]
        raw = self.rom[record.start:record.end]
        return models.decode_rzip_chunk(raw).data if record.compressed else raw

    def data_at(self, address, size):
        offset = address - self.layout["game_data_vram"]
        self.assertGreaterEqual(offset, 0)
        raw = self.game.data[offset:offset + size]
        self.assertEqual(size, len(raw))
        return raw

    def placements(self):
        if not self.placement_tables:
            kinds = {11: Counter(), 12: Counter()}
            for bank in (11, 12):
                for entry in models.parse_asset_entries(self.rom, self.banks[bank]):
                    data = self.asset(bank, entry.index)
                    if bank == 12:
                        data = models.nested_asset_payload(data, 2)
                    count, padding = divmod(len(data), 68)
                    self.assertFalse(any(data[count * 68:]))
                    if bank == 12:
                        self.assertEqual(0, padding)
                    rows = [data[i * 68:(i + 1) * 68] for i in range(count)]
                    self.placement_tables[bank, entry.index] = rows
                    kinds[bank].update(struct.unpack_from(">I", row, 12)[0] for row in rows)
            self.assertEqual({11: {1: 296, 2: 431}, 12: {0: 511}}, kinds)
            self.assertEqual({11: 54, 12: 65}, dict(Counter(b for b, _ in self.placement_tables)))
        return self.placement_tables

    def test_character_geometry_and_held_unknown_source(self):
        for entry, size, digest, vertices, faces, joints in pins.CHARACTER_GEOMETRY:
            with self.subTest(entry=entry):
                raw = self.source(1, entry)
                self.assertEqual((size, digest), (len(raw), sha256(raw)))
                geometry, layout = models.parse_character_model_geometry(raw)
                primary, _ = parts.primary_preview(raw, geometry, layout)
                self.assertEqual((vertices, faces, joints),
                                 (len(primary.vertices), len(primary.faces), len(layout["joints"])))
        # Shared character machinery and valid geometry do not name held entry161.
        self.assertEqual({"status": "unknown", "name": None}, names.resolve_name(
            self.registry, "us", self.registry["rom_sha1"], (1, 161, 0), self.source(1, 161)))

    def test_object_geometry_and_equal_bytes_keep_distinct_keys(self):
        for entry, vertices, faces, minimum, maximum in pins.OBJECT_GEOMETRY:
            with self.subTest(entry=entry):
                geometry = models.parse_geometry_for_bank(self.source(3, entry), 3)
                self.assertEqual((vertices, faces), (len(geometry.vertices), len(geometry.faces)))
                bounds = tuple(tuple(fn(getattr(v, axis) for v in geometry.vertices) for axis in "xyz") for fn in (min, max))
                self.assertEqual((minimum, maximum), bounds)
        records = {r["entry"]: r for r in self.registry["models"] if r["bank"] == 3}
        for a, b in ((71, 100), (72, 101)):
            self.assertEqual(sha256(self.source(3, a)), sha256(self.source(3, b)))
            self.assertNotEqual(records[a]["entry"], records[b]["entry"])
            self.assertEqual(records[a]["name"], records[b]["name"])
        self.assertEqual(records[64]["name"], records[65]["name"])
        self.assertNotEqual(sha256(self.source(3, 64)), sha256(self.source(3, 65)))

    def test_object_placements_transforms_and_cross_bank_selector_propagation(self):
        entries = {entry for _, group, _ in pins.OBJECT_DEFAULTS for entry in group}
        for digest, group, default_flag in pins.OBJECT_DEFAULTS:
            for entry in group:
                with self.subTest(default_entry=entry):
                    raw = self.data_at(0x800A26C0 + entry * 12, 12)
                    self.assertEqual(digest, sha256(raw))
                    if default_flag is not None:
                        self.assertEqual(default_flag, raw[9])
        tables = self.placements()
        actual, transforms = [], []
        transform_keys = {(e, s, i) for e, s, i, *_ in pins.OBJECT_TRANSFORMS}
        for scene in sorted({s for _, s in tables}):
            # The marker crosses the bank-0B/bank-0C transition, then resets
            # for each scene. It is an initialization flag, not draw eligibility.
            origin = None
            for bank in (11, 12):
                for index, raw in enumerate(tables.get((bank, scene), [])):
                    kind, entry, selector = struct.unpack_from(">III", raw, 12)
                    if selector in (40, 66) and origin is None:
                        origin = (bank, scene, index, selector)
                    if kind != 0 or entry not in entries:
                        continue
                    defaults = self.data_at(0x800A26C0 + entry * 12, 12)
                    flags = (defaults[9] & 0xF7) | (4 if origin else 0)
                    actual.append((entry, bank, scene, index, sha256(raw), flags))
                    if (entry, scene, index) in transform_keys:
                        transforms.append((entry, scene, index, selector, raw[60], raw[50],
                                           struct.unpack_from(">3h", raw), struct.unpack_from(">3h", raw, 6),
                                           struct.unpack_from(">3f", raw, 32), origin))
        self.assertEqual(sorted(pins.OBJECT_PLACEMENTS), sorted(actual))
        self.assertEqual(sorted(pins.OBJECT_TRANSFORMS), sorted(transforms))
        self.assertEqual(pins.UNPLACED_OBJECTS, tuple(sorted(entries - {r[0] for r in actual})))
        self.assertTrue(all(not r[-1] & 2 for r in actual))
        canisters = [r for r in actual if r[0] == 85]
        self.assertEqual(6, len(canisters))
        self.assertTrue(all(r[-1] == 4 for r in canisters))
        # Scene45 record25 has selector0, but inherits record0's selector marker.
        witness = next(r for r in transforms if r[:3] == (85, 45, 25))
        self.assertEqual(0, witness[3])
        self.assertEqual((12, 45, 0, 40), witness[-1])

    def test_later_scene_segments_keep_inactivity_and_nonunit_scale(self):
        tables = self.placements()
        identities = {(scene, segment) for scene, segment, *_ in pins.SCENE_PLACEMENTS}
        actual = []
        for scene, segment in sorted(identities):
            for index, raw in enumerate(tables[11, scene]):
                kind, model, selector = struct.unpack_from(">III", raw, 12)
                if kind not in (1, 2) or model != segment:
                    continue
                flags = (raw[60] & 0xF7) | (4 if selector in (40, 66) else 0)
                self.assertEqual(0, flags >> 4)
                self.assertTrue(raw[50] & 1)
                actual.append((scene, segment, index, sha256(raw), raw[52], flags,
                               struct.unpack_from(">3h", raw), struct.unpack_from(">3h", raw, 6),
                               struct.unpack_from(">3f", raw, 32)))
        self.assertEqual(sorted(pins.SCENE_PLACEMENTS), sorted(actual))
        self.assertEqual(11, sum(r[4] == 1 for r in actual))
        self.assertEqual((0.75, 0.75, 0.75), next(r[-1] for r in actual if r[:2] == (54, 5)))

    def test_attachment_header_record_kind_and_action_id_contracts(self):
        kinds = Counter()
        for action, entry, kind, updater, flags, animation, address, header_hash, record_hash in pins.ATTACHMENT_ACTIONS:
            with self.subTest(action=action):
                header = self.data_at(0x80086CC4 + (action - 1) * 8, 8)
                self.assertEqual(header_hash, sha256(header))
                self.assertEqual((address, 1), struct.unpack(">IB3x", header))
                raw = self.data_at(address, 16)
                self.assertEqual(record_hash, sha256(raw))
                self.assertEqual((entry, kind, updater, flags), (raw[0], raw[3], raw[2], raw[7]))
                self.assertEqual(animation, raw[6] if kind == 2 else -1)
                kinds[kind] += 1
        self.assertEqual({1: 34, 2: 2}, kinds)
        self.assertEqual([(43, 131, 0), (51, 139, 11)], [(p[0], p[1], p[5]) for p in pins.ATTACHMENT_ACTIONS if p[2] == 2])
        self.assertEqual(58, next(p[1] for p in pins.ATTACHMENT_ACTIONS if p[0] == 166))
        keys = {(r["bank"], r["entry"], r["segment"]) for r in self.registry["models"]}
        for action in (4, 12, 134, 138, 166):
            self.assertNotIn((9, action, 0), keys)
        self.assertNotEqual(sha256(self.source(9, 123)), sha256(self.source(9, 124)))

    def test_stored_attachment_events_join_headers_routes_and_parents(self):
        report = normalize_payloads(events.report(models, self.rom, self.layout, self.game))
        self.assertEqual(pins.ATTACHMENT_EVENT_COUNTS, report["counts"])
        actions = {p[0]: p for p in pins.ATTACHMENT_ACTIONS}
        routes = {entry: (digest, parents) for entry, digest, parents in pins.ATTACHMENT_ROUTES}
        selected = [r for r in report["events"] if r["operation"] == "create" and r["action"] in actions]
        expected = []
        for action, route, auxiliary, descriptor, pair, table, animation, event_index, offset, time, digest in pins.ATTACHMENT_CREATE_EVENTS:
            _, entry, kind, updater, _, _, address, header_hash, record_hash = actions[action]
            route_hash, parents = routes[route]
            expected.append(dict(action=action, route_bank=15, route_entry=route,
                route_payload_sha1=route_hash, parent_entries=list(parents), auxiliary_offset=auxiliary,
                descriptor_segment_index=descriptor, pair_index=pair, runtime_table_index=table,
                logical_animation_index=animation, event_index=event_index, event_offset=offset,
                time=time, opcode=105, operation="create", event_pin={"size_bytes": 12, "sha256": digest},
                action_record={"header_address": f"0x{0x80086CC4 + (action - 1) * 8:08X}",
                    "header_pin": {"size_bytes": 8, "sha256": header_hash}, "records": [
                        dict(address=f"0x{address:08X}", bank=9, entry=entry, kind=kind, updater=updater,
                             record_index=0, record_pin={"size_bytes": 16, "sha256": record_hash})]}))
            # Independent slices protect the report's event offset/time/action join.
            payload = self.asset(15, route)
            self.assertEqual(route_hash, hashlib.sha1(payload).hexdigest())
            raw = payload[offset:offset + 12]
            self.assertEqual((12, digest), (len(raw), sha256(raw)))
            event_time, command, argument = struct.unpack(">fII", raw)
            self.assertEqual((time, 105, action), (event_time, command & 255, argument))
        self.assertEqual(expected, selected)

    def test_key_geometry_headers_and_lossless_direct_rebuild(self):
        vertices = faces = 0
        for entry, header_index, vertex_count, face_count, vertex_hash, display_hash in pins.KEY_GEOMETRY:
            with self.subTest(entry=entry):
                raw = self.source(9, entry)
                header_size, offset, size, digest = pins.KEY_HEADERS[header_index]
                self.assertEqual(digest, sha256(raw[:header_size]))
                geometry = models.parse_geometry_for_bank(raw, 9)
                self.assertTrue(raw == models.rebuild_direct_model(raw, geometry), "direct-model rebuild changed")
                self.assertEqual((offset, size, vertex_count, face_count),
                                 (geometry.display_list_offset, geometry.display_list_size, len(geometry.vertices), len(geometry.faces)))
                self.assertEqual(vertex_hash, sha256(raw[header_size:offset]))
                self.assertEqual(display_hash, sha256(raw[offset:]))
                vertices += vertex_count
                faces += face_count
        self.assertEqual((362, 300), (vertices, faces))

    def test_key_ui_resource_stride_and_noncontiguous_alphabet(self):
        # The registry audit verifies the complete initializer and input spans.
        # These original instruction pins separately check the actual ABI values.
        def immediate(address, opcode, rs, rt):
            word = struct.unpack_from(">I", self.game.code, address - self.layout["game_vram"])[0]
            self.assertEqual((opcode, rs, rt), (word >> 26, (word >> 21) & 31, (word >> 16) & 31))
            return word & 0xFFFF
        first = immediate(0x151EDFC0, 9, 0, 11)
        stop = immediate(0x151EE108, 9, 0, 1)
        stride = immediate(0x151EE110, 9, 10, 10)
        bound = immediate(0x151EEAFC, 10, 4, 1)
        self.assertEqual((453, 483, 12, 360), (first, stop, stride, bound))
        self.assertEqual(stride, immediate(0x151EEAF8, 9, 4, 4))
        alpha = immediate(0x151EE3D4, 9, 16, 16)
        space = immediate(0x151EE404, 9, 0, 20)
        dot = immediate(0x151EE45C, 9, 0, 20)
        correction = immediate(0x151EE898, 9, 16, 20) - 0x10000
        self.assertEqual((65, 32, 46, -2), (alpha, space, dot, correction))
        self.assertEqual(19, immediate(0x151EE8C4, 10, 8, 1))
        actual = []
        for row, columns in enumerate((6, 6, 6, 6, 5, 1)):
            for column in range(columns):
                slot = row * 6 + column - (1 if row == 5 else 0)
                char = space if row == 5 else None if row == 4 and column in (0, 4) else dot if row == 4 and column == 1 else slot + alpha + (correction if row == 4 else 0)
                actual.append((first + slot, slot, row, column, char))
        self.assertEqual(pins.KEY_ACTIONS, tuple(actual))
        self.assertEqual([None, 46, 89, 90, None, 32], [r[-1] for r in actual[-6:]])

    def test_entry58_texture_consensus_requires_all_eleven_distinct_tables(self):
        tables = models.parse_runtime_render_state_tables(self.game.data, self.layout["game_data_vram"])
        self.assertEqual(tuple(p[0] for p in pins.TEXTURE_TABLES), tuple(int(t["base_address"], 0) for t in tables))
        geometry = models.parse_geometry_for_bank(self.source(3, 58), 3)
        payloads = {}
        for _, index, size_address, start, size, compressed_hash, decoded_size, decoded_hash, _ in pins.ENTRY58_TEXTURES:
            compressed = self.rom[start:start + size]
            self.assertEqual(size, struct.unpack(">H", self.data_at(size_address, 2))[0])
            self.assertEqual(compressed_hash, sha256(compressed))
            data = models.decode_rzip_chunk(compressed).data
            self.assertEqual((decoded_size, decoded_hash), (len(data), sha256(data)))
            payloads[index] = data
        for run, *_, png_hash in pins.ENTRY58_TEXTURES:
            texture, status, evidence = models.rom_render_state_preview_texture(geometry.material_runs[run], {}, payloads, tables)
            self.assertIsNotNone(texture)
            self.assertEqual(png_hash, sha256(texture.png_data))
            self.assertEqual(80, evidence["segment_8_offset"])
            self.assertEqual("runtime-composed-direct-ci4-texture", evidence["texture_status"])
            self.assertEqual(list(pins.TEXTURE_TABLES), [(int(t["base_address"], 16), tuple(t["other_mode"])) for t in evidence["tables"]])
            for bad in (tables[:-1], tables[:-1] + (tables[0],)):
                with self.subTest(run=run), self.assertRaisesRegex(ValueError, "requires every verified table"):
                    models.rom_render_state_preview_texture(geometry.material_runs[run], {}, payloads, bad)


if __name__ == "__main__":
    unittest.main()
