"""Exact bank-04 labels, bounded consumer routes and canonical corrections."""
from pathlib import Path
import copy
import hashlib
import json
import struct
import unittest

from scripts import model_assets as models
from scripts import model_semantic_names as names

SCENE_PROP_NAMES = {(4, 1, 9): 'Hanging pull ring',
 (4, 2, 29): 'Rock Solid lettering',
 (4, 6, 4): 'Windmill blades',
 (4, 7, 11): 'Rusty metal hatch',
 (4, 10, 6): 'Lighter fluid can',
 (4, 16, 20): 'Mechanical grabber',
 (4, 19, 13): 'Diagram easel — circular plan',
 (4, 20, 9): 'Wooden ladder',
 (4, 23, 8): 'Metal grid platform',
 (4, 24, 5): 'Wooden door with metal fittings',
 (4, 33, 6): 'Chainsaw',
 (4, 35, 15): 'Vine-covered column',
 (4, 41, 20): 'Wooden bridge',
 (4, 43, 7): 'Paris 200 km sign',
 (4, 45, 12): 'Diagram easel — pipe plan',
 (4, 45, 13): 'Wooden watchtower with red banner',
 (4, 54, 5): 'Paired metal gate',
 (4, 60, 17): 'Gold candelabrum',
 (4, 65, 5): 'Reinforced wooden door',
 (4, 67, 6): 'Spotted egg dome'}

EXPECTED_CONSUMERS = [{'symbol': 'func_150031EC',
  'vram': '0x150031EC',
  'size_bytes': 712,
  'sha1': 'ed48d58ffb38dab90c140a0d547dbdae13f3225a',
  'role': 'load bank-04 scene bundle and relocate all model descriptors, including later segments '
          'outside initial slots 0..3'},
 {'symbol': 'func_150039E0',
  'vram': '0x150039E0',
  'size_bytes': 2964,
  'sha1': 'b7b5ae00e5b5a3c5a0d28ad82582a25479a3bc66',
  'role': 'resolve bank-0B kind-1/2 placement +0x10 through the bank-04 descriptor table and retain its '
          'primary list at object +0x1C'},
 {'symbol': 'func_15112A80',
  'vram': '0x15112A80',
  'size_bytes': 1792,
  'sha1': '7b060425a0e9d27a05fa6f7c819a8b0811c91552',
  'role': 'build per-view candidate groups from placed objects under inactive, flag, alpha, state, '
          'distance and view gates'},
 {'symbol': 'func_151135C4',
  'vram': '0x151135C4',
  'size_bytes': 528,
  'sha1': '04f7c62d81e7232c89b3309fdeade178adab34aa',
  'role': 'select the placed-object runtime record for the shared draw path'},
 {'symbol': 'func_151137D4',
  'vram': '0x151137D4',
  'size_bytes': 1204,
  'sha1': '95326ee5c7b73267556e889aedfdef799930e221',
  'role': 'submit the placed-object primary list on the ordinary direct branch'}]

CANONICAL_BEFORE = {54: {'name': 'object-bank04-0020-09-rom',
      'label': 'Wooden post — ROM 04 / 0020 / 09',
      'render_case': 'object-bank04-0020-09-rom',
      'note': 'Geometry and textures extracted from ROM. Indexed texture decoding now follows the '
              'verified ordinary placement renderer. Runtime colours, lighting, visibility and native '
              'raster parity remain unverified.',
      'category': 'scene-items'},
 329: {'name': 'object-bank04-0067-06-rom',
       'label': 'Spotted egg — ROM 04 / 0067 / 06',
       'render_case': 'object-bank04-0067-06-rom',
       'note': 'Geometry and textures extracted from the ROM. Native colour, lighting and raster '
               'appearance remain unverified. No capture inputs.',
       'category': 'scene-items'}}

CANONICAL_AFTER = {54: {'name': 'object-bank04-0020-09-rom',
      'label': 'Wooden ladder — ROM 04 / 0020 / 09',
      'render_case': 'object-bank04-0020-09-rom',
      'note': 'Geometry and textures extracted from ROM. Indexed texture decoding now follows the '
              'verified ordinary placement renderer. Runtime colours, lighting, visibility and native '
              'raster parity remain unverified. The exact source has two long wooden rails and repeated '
              'horizontal rungs, including the transparent rung texture. This supports a descriptive '
              'ladder label; climbability and gameplay behavior are unproven.',
      'category': 'scene-items',
      'aliases': ['Wooden post (former label)', 'Wooden post — ROM 04 / 0020 / 09 (former label)']},
 329: {'name': 'object-bank04-0067-06-rom',
       'label': 'Spotted egg dome — ROM 04 / 0067 / 06',
       'render_case': 'object-bank04-0067-06-rom',
       'note': 'Geometry and textures extracted from the ROM. Native colour, lighting and raster '
               'appearance remain unverified. No capture inputs. The exact source is an open-bottom '
               'dome: 113 vertices, 94 faces, ten boundary edges at Y=-515 and no bottom-plane faces. A '
               'complete egg, closed bottom or equivalence to the bank-01 egg is not established.',
       'category': 'scene-items',
       'aliases': ['Spotted egg (former label)', 'Spotted egg — ROM 04 / 0067 / 06 (former label)']}}

SCENE_ASSOCIATION_PINS = {'config/model-scene-assemblies.json': '4f2f9d6a63087fffc2894b8cff6d00e0a970001cf8ebd3e7e6159fee86fdb5bc',
 'config/model-validation.json': 'cc9756fdf6ca78a977c456fb9a95c93dd01401fc318722e3947f175bfac48e02',
 'docs/evidence/us_static_scene_assemblies.md': '3b169a97f17868768ec207c1361bbbb7f684e981e2cfa8d7d6d56821dfebeeaf'}

PLACEMENTS = {(4, 2, 29): [(23,
               'd844898f832785462adcbebacc2f5ec4bfebbf18',
               'efc6c63756824acdb3e9cb0164cd98689bd8fbb3539e0d87d28ec6abd594f14e',
               0,
               0,
               (-4017, 345, 145),
               (0, 0, 0),
               (1.0, 1.0, 1.0))],
 (4, 60, 17): [(11,
                'e4136d2d599bd766d4bf6c068c23d4ba99f63110',
                'bb4130d2878fc55fd5e47a4b9016ab9e2522ffa20548831c8a154131244143f4',
                1,
                0,
                (0, 0, 0),
                (0, 0, 0),
                (1.0, 1.0, 1.0))],
 (4, 35, 15): [(11,
                'a8d015f42fb6d651ed645091724c9f48b8f0d4b7',
                'd13f4c399a00c05c9b1cd6a818679d4eb8d999bc7076e47a4f34b52e03b3234a',
                0,
                0,
                (-2649, 1026, 10),
                (0, 0, 0),
                (1.0, 1.0, 1.0))],
 (4, 6, 4): [(3,
              '456ec458f84efdcb186e5e94f933fcefe17661c5',
              '29041c64273e6886cdd1a94b86898402e342c65b6fd90236adf342c1e02a1b04',
              0,
              4,
              (2763, -18, -678),
              (0, -23, 0),
              (1.0, 1.0, 1.0))],
 (4, 16, 20): [(14,
                'a7b3448614da499c914d10f5a8280e8270e8eee8',
                '406aec26bca3d1e62f464623a0a9a449667a6ea19ba356d0fad94dd5308d410d',
                1,
                0,
                (0, 0, 0),
                (0, 0, 0),
                (1.0, 1.0, 1.0))],
 (4, 7, 11): [(3,
               'af9d8aa85bb58856a5447d4432619e444570bc8e',
               '65b3e66ac3bb26a4f02aa4177a7b69a26344b532543839b327e7ccbb2c17f261',
               0,
               4,
               (-5, -1442, 2750),
               (0, 0, 0),
               (1.0, 1.0, 1.0))],
 (4, 24, 5): [(1,
               'c38dcedffffb8c933ff3d1861172a1b45969843c',
               'ccf5e20c4ee0f88e5c048118ef83f467ca77aa1ac161284b935bc3db041bfd61',
               0,
               0,
               (249, -385, -358),
               (0, 0, 0),
               (1.0, 1.0, 1.0))],
 (4, 23, 8): [(1,
               '4cdd83a455a1c9cdf8c5ec568ff7d08a352244b2',
               '4958229040526b238b861ff0b76595c9259492203c4b000a6eb8b5b9c7e9f25b',
               1,
               0,
               (2870, -1289, -4510),
               (0, 0, 0),
               (1.0, 1.0, 1.0))],
 (4, 54, 5): [(0,
               '2d8f7ced840ef5903c5f23e564e2e304bb9c0c56',
               'ef2c25008f61ccc378cb1595be73e67bf07319ee40cacf5fd6119d1815cd93d9',
               0,
               0,
               (0, 0, 3242),
               (0, 0, 0),
               (0.75, 0.75, 0.75))],
 (4, 33, 6): [(2,
               '6df8e3a50977846770fd1b3f11c9aee8a92b40b4',
               'd1e48a97661503b8494a22784bfba75be20a48584bf2a618ff2b50480abdc8f0',
               1,
               0,
               (0, 0, 0),
               (0, 0, 0),
               (1.0, 1.0, 1.0))],
 (4, 45, 13): [(9,
                '5345951d04e9e7532eaac38084ba887189acf4fb',
                'aedadd142f76a3b820cbb76278d5414161af58347ab83267ed71e8d21fa9aeaa',
                1,
                0,
                (0, 0, 0),
                (0, 0, 0),
                (1.0, 1.0, 1.0))],
 (4, 67, 6): [(2,
               '445854fbe8900c298d3d66a5c30e834300fc4a3d',
               '6b795cc52000760a6f54f1d9b8670bbb1cedeed3faa0a55b39e2a7cbf37cf6b5',
               1,
               0,
               (-313, 1977, 9),
               (0, 0, 0),
               (1.0, 1.0, 1.0))],
 (4, 1, 9): [(5,
              '0b92860b5d5210bce3339a9cba076c2e3a7ee233',
              '91e47b367e418ec0048d12b207d7d541da3f34efaa0d93b7203a81ba8d38acb7',
              1,
              4,
              (0, 0, 0),
              (0, 0, 0),
              (1.0, 1.0, 1.0))],
 (4, 19, 13): [(7,
                '161dd95b9d2a83cd49c463ea74b778f1cf505f60',
                'c5a175ce604fbb4520e6e78bbf6a2227019804f361f70b7437631e422f6242ac',
                1,
                0,
                (0, 0, 0),
                (0, 0, 0),
                (1.0, 1.0, 1.0))],
 (4, 45, 12): [(8,
                'cf28216b72ec8970a6f3c5dc1c6b3ef9b582fbdb',
                '2408837c7781de9bfde031e8dbe9810e8c0aa9c48a207010ff5b03482cf9321d',
                1,
                0,
                (0, 0, 0),
                (0, 0, 0),
                (1.0, 1.0, 1.0))],
 (4, 43, 7): [(3,
               'd62fd5df518b89148e7c900013683dcafae0a81f',
               'e208c6e9f16e81962765afcba682ba8926685a7e83a21e62ab81df5879d956f8',
               1,
               4,
               (0, 0, 0),
               (0, 0, 0),
               (1.0, 1.0, 1.0))],
 (4, 41, 20): [(0,
                '2106da10375d758beda14b76b8da14ae3e326e9e',
                'ab65d6c95bd1769c3f9102630ef78e103b1a8daf337f52235f09d2e1fe1a489b',
                0,
                1,
                (-644, 500, -4660),
                (0, -29, 0),
                (1.0, 1.0, 1.0)),
               (1,
                'f17da3653a3b09df482e44ef97850203d7823268',
                'c7550ad407c63e8a88b4d4e762daa6c167f675f9d8038ed22ceef7209b312cbc',
                0,
                1,
                (1609, 1050, -5879),
                (0, -118, 0),
                (1.0, 1.0, 1.0))],
 (4, 65, 5): [(1,
               '0c04cc8d82eccbbc2656c6ea9d18de50aad520c9',
               '5c5aad34c990475f0f0ce2330d3ad38d7cfbc5fae62786cd66ba9ad6e518d329',
               0,
               0,
               (1032, -480, 705),
               (0, 0, 0),
               (1.0, 1.0, 1.0))],
 (4, 10, 6): [(5,
               '6f2b1bb58006120d8cbe8d44719060bd7b835297',
               '177c5780461d5c582ae845cd9aac610e388061db41f7aa42157ad64792a21809',
               1,
               0,
               (0, -500, 0),
               (0, 0, 0),
               (1.0, 1.0, 1.0))],
 (4, 20, 9): [(5,
               '0cf7fda3f49a1d785281e920b030202c456c0eb9',
               'f184b9a487a5ff6c1de2021a4c202015b317d87b2c894d40c66fbc27fc7fdd80',
               0,
               0,
               (-9159, 3119, 488),
               (0, 0, 0),
               (1.0, 1.0, 1.0)),
              (6,
               '7333fa1dd266e08c43dc3b567072079ba8e1d5ef',
               '51837136132cb199412d195fe02b91f30f8f70e9f26f678141efae4d7c57dedc',
               0,
               0,
               (-9159, 3119, -370),
               (0, 0, 0),
               (1.0, 1.0, 1.0))]}


def canonical_digest(value):
    return hashlib.sha256(json.dumps(value, sort_keys=True, separators=(",", ":")).encode()).hexdigest()


class ScenePropSemanticNameTests(unittest.TestCase):
    def test_all_91_prior_records_and_haybot_branch_are_unchanged(self):
        registry = names.load_registry()
        retained = [r for r in registry["models"] if r["bank"] != 4
                    and "docs/evidence/remaining_character_semantic_registry_expansion.md" not in r["evidence"]]
        self.assertEqual(91, len(retained))
        self.assertEqual("daab097c956a0343961bba5e5d20d4641fef1b0758a8cbd03ec677e6197561b0", canonical_digest(retained))
        self.assertEqual([(1, 75, 0)], [(r["bank"], r["entry"], r["segment"])
                         for r in registry["models"] if "model_specific_branch" in r])

    def test_twenty_exact_numeric_identities_and_all_added_fields_are_pinned(self):
        added = [r for r in names.load_registry()["models"] if r["bank"] == 4]
        self.assertEqual(20, len(added))
        self.assertEqual(SCENE_PROP_NAMES, {(r["bank"], r["entry"], r["segment"]): r["name"] for r in added})
        self.assertEqual("74511feeb7e1c46452a30f8b04f08f4c9ccaf0b3d382b87e52747ab0d7ba19f0", canonical_digest(added))
        self.assertTrue(all(r["segment"] >= 4 for r in added))

    def test_complete_shared_consumer_chain_is_bounded_to_later_segments(self):
        records = names.load_registry()["models"]
        for record in records:
            if record["bank"] == 4:
                self.assertEqual(EXPECTED_CONSUMERS, record["consumers"])
                self.assertNotIn("model_specific_branch", record)
                self.assertTrue(any("initial-slot renderer" in s for s in record["limitations"]))
                self.assertTrue(any("bank-0C child 2 does not supply" in s for s in record["limitations"]))
        self.assertEqual(44, len({c["symbol"] for r in records for c in r["consumers"]}))
        self.assertEqual(923, sum(len(r["consumers"]) for r in records))

    def test_source_names_do_not_spread_to_other_banks_or_neighbor_segments(self):
        registry = names.load_registry()
        payload = b"equal synthetic bytes do not equate different numeric identities"
        for record in registry["models"]:
            record.update(source_bytes=len(payload), model_sha1=hashlib.sha1(payload).hexdigest(),
                          model_sha256=hashlib.sha256(payload).hexdigest())
        for key, label in SCENE_PROP_NAMES.items():
            self.assertEqual(label, names.resolve_name(registry, "us", registry["rom_sha1"], key, payload)["name"])
        for key in ((4, 20, 8), (4, 67, 5), (4, 0, 0), (4, 20, 0), (3, 20, 9), (9, 67, 6), (1, 171, 0)):
            self.assertEqual({"status": "unknown", "name": None},
                             names.resolve_name(registry, "us", registry["rom_sha1"], key, payload))

    def test_exact_two_canonical_labels_aliases_and_original_caveats(self):
        canonical = json.loads((names.ROOT / "config/model-inspection.json").read_text())
        for index, expected in CANONICAL_AFTER.items():
            actual = canonical["models"][index]
            self.assertEqual(expected, actual)
            old = CANONICAL_BEFORE[index]
            self.assertTrue(actual["note"].startswith(old["note"] + " "))
            self.assertIn(old["label"] + " (former label)", actual["aliases"])
            for field in old.keys() - {"label", "note", "aliases"}:
                self.assertEqual(old[field], actual[field])
            canonical["models"][index] = copy.deepcopy(old)
        # Restoring exactly the two corrections must recover every prior canonical field.
        self.assertEqual("9dfc780720519fdd905113607443a6e2cdfad0f49ddc095777bfaa32a96650b0", canonical_digest(canonical))

    def test_static_scene_selection_validation_paths_and_historical_hashes_stay_unchanged(self):
        for path, digest in SCENE_ASSOCIATION_PINS.items():
            self.assertEqual(digest, hashlib.sha256((names.ROOT / path).read_bytes()).hexdigest(), path)
        for path in ("more_character_semantic_registry_expansion.md", "additional_character_semantic_registry_expansion.md"):
            self.assertIn("b43ebaff477fe60d72635866310daaec1181df6c630923bf6114aa50cbef9f98", (names.ROOT / "docs/evidence" / path).read_text())

    def test_model_specific_limits_do_not_claim_activation_or_whole_models(self):
        records = {(r["entry"], r["segment"]): r for r in names.load_registry()["models"] if r["bank"] == 4}
        inactive = {(60,17),(16,20),(23,8),(33,6),(45,13),(67,6),(1,9),(19,13),(45,12),(43,7),(10,6)}
        for key, record in records.items():
            text = " ".join(record["limitations"])
            self.assertIn("runtime activation/visibility", text)
            self.assertEqual(key in inactive, "Initially inactive singleton" in text)
        for key, phrase in (((45,12), "colocated"), ((45,13), "colocated"), ((60,17), "whole-assembly"),
                            ((65,5), "cleared"), ((41,20), "placement twice"), ((20,9), "Climbability"), ((67,6), "bottom")):
            self.assertIn(phrase.lower(), " ".join(records[key]["limitations"]).lower())

    @unittest.skipUnless((names.ROOT / "roms/baserom.us.z64").is_file(), "owned US ROM unavailable")
    def test_all_22_bank0b_records_and_exact_real_transforms(self):
        path, layout = models.resolve_rom("us", names.ROOT / "roms/baserom.us.z64")
        rom, _ = models.normalize_rom(path.read_bytes())
        self.assertEqual(names.load_registry()["rom_sha1"], hashlib.sha1(rom).hexdigest())
        bank = next(b for b in models.parse_asset_banks(rom, layout["asset_table"]) if b.index == 11)
        entries = {e.index: e for e in models.parse_asset_entries(rom, bank)}
        total = inactive_count = 0
        for (_, scene, segment), expected in PLACEMENTS.items():
            e = entries[scene]
            data = models.decode_rzip_chunk(rom[e.start:e.end]).data if e.compressed else rom[e.start:e.end]
            actual = []
            for index in range(len(data) // 0x44):
                raw = data[index * 0x44:(index + 1) * 0x44]
                kind, model, selector = struct.unpack_from(">III", raw, 12)
                if kind not in (1, 2) or model != segment:
                    continue
                flags = (raw[0x3C] & 0xF7) | (4 if selector in (0x28, 0x42) else 0)
                self.assertEqual(0, flags >> 4)
                self.assertTrue(raw[0x32] & 1)
                actual.append((index, hashlib.sha1(raw).hexdigest(), hashlib.sha256(raw).hexdigest(),
                               raw[0x34], flags, struct.unpack_from(">3h", raw),
                               struct.unpack_from(">3h", raw, 6), struct.unpack_from(">3f", raw, 32)))
                total += 1
                inactive_count += raw[0x34] == 1
            self.assertEqual(expected, actual, (scene, segment))
        self.assertEqual(22, total)
        self.assertEqual(11, inactive_count)
        # The gate is the exception to unit scale; a historical README overgeneralized it.
        self.assertEqual((0.75, 0.75, 0.75), PLACEMENTS[(4, 54, 5)][0][-1])


if __name__ == "__main__":
    unittest.main()
