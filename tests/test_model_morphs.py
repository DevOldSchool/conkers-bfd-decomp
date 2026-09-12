from __future__ import annotations

import copy
import json
import struct
import tempfile
import unittest
from dataclasses import replace
from pathlib import Path

from scripts import model_assets as models, model_morphs as morphs, model_validation
from scripts.rzip_pack import encode_rzip_chunk


def table(payloads, compressed=False):
    offset = len(payloads) * 8
    header, body = bytearray(), bytearray()
    for index, payload in enumerate(payloads):
        blob = encode_rzip_chunk(payload) if compressed else payload
        flags = (0x10000000 if compressed else 0) | (0x80000000 if index == len(payloads) - 1 else 0)
        header.extend(struct.pack(">II", offset, len(blob) | flags))
        body.extend(blob)
        padding = -len(blob) % 8
        body.extend(bytes(padding))
        offset += len(blob) + padding
    return bytes(header + body)


def fixture():
    positions = [(0, 0, 0), (10, 0, 0), (0, 10, 0)]
    vertices = b"".join(struct.pack(">hhhHhh4B", *p, 0, 0, 0, 255, 255, 255, 255) for p in positions)
    commands = b"".join(struct.pack(">II", *p) for p in (
        (0xD7000000, 0), (0x01003006, 0x01000000), (0x05000204, 0), (0xDF000000, 0)))
    header = struct.pack(">10I", 88, len(commands), 0, 0, 0, 0, 0, 0, 0, 0x80000000)
    geometry = models.parse_model_geometry(header + vertices + commands)
    geometry = replace(geometry, header_words=(16, 12))
    model_data = bytes(16) + struct.pack(">3I", 0, 1, 2)
    leaves = [[struct.pack(">3h", *p) + bytes(10),
               struct.pack(">3h", p[0] + 1, p[1] - 2, p[2] + 3) + bytes(10)] for p in positions]
    data = table([table(part, True) for part in leaves])
    selector = {"bank_entry": 0, "character_entry": 0, "shape_count": 2, "part_vertex_counts": [1, 1, 1]}
    return data, model_data, geometry, selector


class MorphTests(unittest.TestCase):
    def test_decode_maps_native_vertex_ranges_and_reconstructs_all_leaves(self):
        data, model, geometry, selector = fixture()
        result = morphs.parse_targets(data, model, geometry, selector)
        self.assertEqual([0, 1, 2], result["vertex_starts"])
        for target in result["targets"]:
            for part in target["parts"]:
                blob = morphs.encode_part(part)
                self.assertEqual(16, len(blob))
                self.assertEqual(tuple(part["positions"][0]), struct.unpack_from(">3h", blob))
        deltas = morphs.target_deltas(result, geometry)
        self.assertEqual({0: (0, 0, 0), 1: (0, 0, 0), 2: (0, 0, 0)}, deltas[0])
        self.assertEqual({0: (1, -2, 3), 1: (1, -2, 3), 2: (1, -2, 3)}, deltas[1])

    def test_gltf_targets_preserve_basis_and_export_native_position_deltas(self):
        data, model, geometry, selector = fixture()
        result = morphs.parse_targets(data, model, geometry, selector)
        encoded, binary = models.encode_gltf(0, 0, geometry, bank_index=1, character_morphs=result)
        document = json.loads(encoded)
        mesh = document["meshes"][0]
        self.assertEqual([0, 0], mesh["weights"])
        self.assertEqual(["rom-shape-00", "rom-shape-01"], mesh["extras"]["targetNames"])
        primitive = mesh["primitives"][0]
        values = [model_validation.accessor(document, target["POSITION"], [binary]) for target in primitive["targets"]]
        self.assertEqual([(0.0, 0.0, 0.0)] * 3, values[0])
        self.assertEqual([(1.0, -2.0, 3.0)] * 3, values[1])
        self.assertEqual([(0., 0., 0.), (10., 0., 0.), (0., 10., 0.)],
                         model_validation.accessor(document, primitive["attributes"]["POSITION"], [binary]))
        self.assertNotIn("animations", document)
        with self.assertRaisesRegex(ValueError, "different character"):
            models.encode_gltf(1, 0, geometry, bank_index=1, character_morphs=result)
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / '0000-00.gltf'
            path.write_bytes(encoded)
            blob_path = path.with_suffix('.bin')
            blob_path.write_bytes(binary)
            runs = [{"face_count": 1, "runtime_material": None}]
            comparison = model_validation.compare_geometry(path, geometry, None, runs, result)
            self.assertEqual(6, comparison['morph_corners'])
            target = document['accessors'][primitive['targets'][1]['POSITION']]
            view = document['bufferViews'][target['bufferView']]
            changed = bytearray(binary)
            struct.pack_into('<f', changed, view['byteOffset'], 17.0)
            blob_path.write_bytes(changed)
            with self.assertRaisesRegex(ValueError, "morph delta"):
                model_validation.compare_geometry(path, geometry, None, runs, result)

    def test_tables_fail_closed_on_flags_overlap_and_padding(self):
        original = table([b"1234", b"abcd"])
        for offset, value in ((0, 8), (4, 0x10000004), (8, 16), (12, 4)):
            candidate = bytearray(original)
            struct.pack_into(">I", candidate, offset, value)
            with self.subTest(offset=offset):
                with self.assertRaises(ValueError):
                    morphs.children(bytes(candidate), 2, compressed=False)
        candidate = bytearray(original)
        candidate[20] = 1
        with self.assertRaisesRegex(ValueError, "padding"):
            morphs.children(bytes(candidate), 2, compressed=False)

    def test_wrong_model_mapping_or_basis_is_rejected(self):
        data, model, geometry, selector = fixture()
        for starts in ((0, 1, 3), (0, 0, 2), (1, 0, 2)):
            with self.assertRaises(ValueError):
                morphs.parse_targets(data, model[:16] + struct.pack(">3I", *starts), geometry, selector)
        changed = replace(geometry, vertices=(replace(geometry.vertices[0], x=1), *geometry.vertices[1:]))
        with self.assertRaisesRegex(ValueError, "shape zero"):
            morphs.parse_targets(data, model, changed, selector)
        result = morphs.parse_targets(data, model, geometry, selector)
        part = copy.deepcopy(result["targets"][0]["parts"][0])
        part["padding_size"] = 16
        with self.assertRaisesRegex(ValueError, "padding"):
            morphs.encode_part(part)
        with self.assertRaisesRegex(ValueError, "consumer changed"):
            morphs.verify_consumers(b"", 0x15000000, b"", 0x80082B20)


if __name__ == "__main__":
    unittest.main()
