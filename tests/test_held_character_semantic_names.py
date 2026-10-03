"""Five bounded bank-01 labels with exact identities and unchanged historical guards."""
import copy
import hashlib
import json
import unittest
from test_model_name_confidence import resolve_synthetic_name

from scripts import model_assets as models, model_character_parts as parts, model_semantic_names as names
from test_remaining_scene_prop_semantic_names import (REMAINING_SCENE_PROP_NAMES,
    restore_remaining_scene_corrections, historical_canonical_bytes)

HELD_CHARACTER_NAMES = {(1, 151, 0): 'Berri — variant',
 (1, 154, 0): 'Bat — blue eyes',
 (1, 155, 0): 'Bat — yellow eyes',
 (1, 162, 0): 'Bat — red eyes',
 (1, 171, 0): 'Spotted egg'}

EXPECTED_CONSUMERS = [{'role': 'load bank-01 model and install indexed draw/texture tables',
  'sha1': '2335fa3855313510f1f46512cfa704ab301814d1',
  'size_bytes': 1096,
  'symbol': 'func_1503CF20',
  'vram': '0x1503CF20'},
 {'role': 'initialize an actor from a spawn record; shared path, not character-exclusive',
  'sha1': 'df94e52b3063e063c091fac537096563d3e47620',
  'size_bytes': 2152,
  'symbol': 'func_15082A44',
  'vram': '0x15082A44'},
 {'role': 'store the model index at actor offset 0x04',
  'sha1': '7bd9c8414be99e3bc26944fe08eb04064933a30d',
  'size_bytes': 280,
  'symbol': 'func_150837D4',
  'vram': '0x150837D4'},
 {'role': 'actor_apply_character_defaults',
  'sha1': '83514e60fb88c39b8e225ba6b68a54a5094c2dff',
  'size_bytes': 272,
  'symbol': 'func_150839B8',
  'vram': '0x150839B8'},
 {'role': 'actor_apply_current_expression',
  'sha1': '77b08fc8d2ec99c73d27527f43df6c9952d0c5fa',
  'size_bytes': 240,
  'symbol': 'func_1507E5C8',
  'vram': '0x1507E5C8'},
 {'role': 'bind actor-selected texture descriptors',
  'sha1': 'a9ae1253feb21fae8ecc3c314d949162c3e6afa5',
  'size_bytes': 584,
  'symbol': 'func_1502F01C',
  'vram': '0x1502F01C'},
 {'role': 'submit primary or secondary character parts',
  'sha1': '2176c655198fed8b1867b28f059cb4765bced897',
  'size_bytes': 2128,
  'symbol': 'func_1502CCFC',
  'vram': '0x1502CCFC'}]

MODEL_PINS = {114: {'joints': 45,
       'material_status_faces': {'excluded-secondary-draw-pass': 0,
                                 'native-material-combiner-unresolved': 3,
                                 'rom-default-combiner-does-not-use-texture': 7,
                                 'rom-default-indexed': 114,
                                 'rom-state-consensus-character-intensity-mipmap-base-i8': 84,
                                 'runtime-composed-character-texture': 464,
                                 'runtime-composed-character-trilinear-base': 64},
       'primary_faces': 736,
       'source_bytes': 24376,
       'source_hashes': {'sha1': '9570420ff5c4cc20788d9b42079780494f7823a7',
                         'sha256': '8d0692a4f0663ce18da927a6b92eac7798e74c7c6b75a7d09b4738e2347c3777'},
       'vertices': 683},
 151: {'joints': 51,
       'material_status_faces': {'character-intensity-mipmap-base-ia8': 4,
                                 'excluded-secondary-draw-pass': 0,
                                 'native-material-combiner-unresolved': 3,
                                 'rom-default-combiner-does-not-use-texture': 7,
                                 'rom-default-indexed': 114,
                                 'rom-state-consensus-character-intensity-mipmap-base-i8': 84,
                                 'rom-state-consensus-character-intensity-shade-alpha-i8': 52,
                                 'runtime-composed-character-texture': 538},
       'primary_faces': 802,
       'source_bytes': 25800,
       'source_hashes': {'sha1': 'd56a7a5f2be62ee3f212e9e4f6e47a9a69c5c407',
                         'sha256': '8286360d16924cee18588934bc0a3aac3d6a480e7c4a945b1e1a8f6a69022ecf'},
       'vertices': 739},
 154: {'joints': 36,
       'material_status_faces': {'character-indexed-combiner-preview-unresolved': 174,
                                 'excluded-secondary-draw-pass': 0,
                                 'native-material-combiner-unresolved': 11,
                                 'rom-default-indexed': 16,
                                 'runtime-composed-character-texture': 124,
                                 'runtime-composed-character-trilinear-base': 60,
                                 'runtime-composed-direct-ia16-texture': 18},
       'primary_faces': 403,
       'source_bytes': 17080,
       'source_hashes': {'sha1': '8595d9090f169e7f5706d69ad50484ad4b270675',
                         'sha256': '213af78e2785ced050d5369838c8a57748fa20b11c1bd05360d9827388aa0db0'},
       'vertices': 408},
 155: {'joints': 36,
       'material_status_faces': {'character-indexed-combiner-preview-unresolved': 186,
                                 'native-material-combiner-unresolved': 14,
                                 'rom-default-indexed': 16,
                                 'runtime-composed-character-texture': 32,
                                 'runtime-composed-character-trilinear-base': 48,
                                 'runtime-composed-direct-ia16-texture': 18},
       'primary_faces': 314,
       'source_bytes': 11400,
       'source_hashes': {'sha1': 'f5247b7c7d91be66589863d66341d891fd55e7c0',
                         'sha256': '7c13d0045a2847d661066b4633729e1dfd0e8c46c4dd06853d8ccf1f035791d1'},
       'vertices': 335},
 161: {'joints': 4,
       'material_status_faces': {'runtime-composed-character-texture': 87,
                                 'runtime-composed-character-trilinear-base': 8,
                                 'runtime-composed-direct-ia8-texture': 8},
       'primary_faces': 103,
       'source_bytes': 3448,
       'source_hashes': {'sha1': 'fe4b7b95762cd7bd8c7ef1a0f68db02719a6e69c',
                         'sha256': '2756df2c2ae9b8b5d464528478a5701223a03628c46f8833c60e6750a6e4987e'},
       'vertices': 110},
 162: {'joints': 39,
       'material_status_faces': {'character-indexed-combiner-preview-unresolved': 210,
                                 'excluded-secondary-draw-pass': 0,
                                 'rom-default-indexed': 6,
                                 'runtime-composed-character-texture': 194,
                                 'runtime-composed-character-trilinear-base': 80,
                                 'runtime-composed-direct-ia8-texture': 18},
       'primary_faces': 508,
       'source_bytes': 19304,
       'source_hashes': {'sha1': '4ad4407283a3804feea427d39d518a8cd2b1eece',
                         'sha256': '31279085fef01c074510ad8c93836cb16cccdb8842641b476d19e5251740ebe1'},
       'vertices': 486},
 171: {'joints': 1,
       'material_status_faces': {'runtime-composed-character-texture': 44},
       'primary_faces': 44,
       'source_bytes': 792,
       'source_hashes': {'sha1': 'bf9bc0af2a43f62c76ac993bda34be6619332faf',
                         'sha256': 'c0d73cedcce0650951becf1744074175eb40604cd35e48cb9369d9dc54c41ba3'},
       'vertices': 24}}

SOURCE_JOINS = {114: [{'canonical_index': 8,
        'canonical_sha256': '83f83ea9b85f8d0aa6eddf3847b4aa8b2111bc8a1379bd9e74055a44352a329a',
        'validation_index': 44,
        'validation_sha256': 'e69ace7c83ab8dfefd29b5bc6236ca11b5f35112ed1d3b0336cdec0b413df44e'}],
 151: [{'canonical_index': 9,
        'canonical_sha256': 'cf684c387244efce71a7f83e02603d2892bebafee01fb4e4b21fd22552ea7d16',
        'validation_index': 45,
        'validation_sha256': '9f2d48b2059d4e4f2dad9e75d3e218d9104e77cf6eedf58c161d4e6c11db1495'}],
 154: [],
 155: [],
 161: [{'canonical_index': 79,
        'canonical_sha256': '4de7e546e628a9012035b9ca34e39d44ab611d37465ba93081552ce27c453cfe',
        'validation_index': 103,
        'validation_sha256': '8f139cd3dca8a857b1eb2e1eac0f257ee7b0cea1efe0a75578966628c263e96b'}],
 162: [],
 171: [{'canonical_index': 159,
        'canonical_sha256': '3cfd5d716afe24f0cac0f35db551c73c6546f0bb0fbd1016379dc05ef0a5b7a9',
        'validation_index': 183,
        'validation_sha256': 'c492cb8a23ebb13a2ca2a5df1fe7bc81bfbb08ba12088706d9de233fea88d69a'}]}

def digest(value):
    return hashlib.sha256(json.dumps(value, sort_keys=True, separators=(",", ":")).encode()).hexdigest()


class HeldCharacterSemanticNameTests(unittest.TestCase):
    def test_all_232_prior_records_and_114_comparison_unchanged(self):
        registry = names.load_registry()
        retained = [r for r in registry["models"]
                    if (r["bank"], r["entry"], r["segment"]) not in HELD_CHARACTER_NAMES
                    and (r["bank"], r["entry"], r["segment"]) not in REMAINING_SCENE_PROP_NAMES]
        self.assertEqual(232, len(retained))
        self.assertEqual("e97dbe77a17530694ec3da783ed32f34f0cfce79f2c9ef67710138f09f65b884", digest(retained))
        reference = next(r for r in retained if (r["bank"], r["entry"], r["segment"]) == (1,114,0))
        self.assertEqual("8456875267be885faba5a725b32c8a7b2ee99eb1c219a7f4b7309c351220851f", digest(reference))
        self.assertEqual([(1,75,0)], [(r["bank"],r["entry"],r["segment"])
                         for r in registry["models"] if "model_specific_branch" in r])

    def test_exact_five_records_and_seven_shared_full_spans(self):
        registry = names.load_registry()
        added = [r for r in registry["models"]
                 if (r["bank"],r["entry"],r["segment"]) in HELD_CHARACTER_NAMES]
        self.assertEqual(5,len(added))
        self.assertEqual("7eeaa54390cd8d6eb996367db234fffa360282a0f4ab8a8b8402fffcb5d0b368",digest(added))
        self.assertEqual(HELD_CHARACTER_NAMES,
                         {(r["bank"],r["entry"],r["segment"]):r["name"] for r in added})
        for record in added:
            self.assertEqual(EXPECTED_CONSUMERS,record["consumers"])
            self.assertNotIn("model_specific_branch",record)
            self.assertEqual(["docs/evidence/held_character_semantic_registry_expansion.md",
                              "docs/evidence/us_rom_character_defaults.md",
                              "docs/evidence/us_character_draw_tables.md"],record["evidence"])
        self.assertEqual([1096,2152,280,272,240,584,2128],
                         [c["size_bytes"] for c in EXPECTED_CONSUMERS])
        self.assertNotIn("func_15084D00",{c["symbol"] for c in EXPECTED_CONSUMERS})
        self.assertEqual(267,len(registry["models"]))
        self.assertEqual(47,len({c["symbol"] for r in registry["models"] for c in r["consumers"]}))
        self.assertEqual(1375,sum(len(r["consumers"]) for r in registry["models"]))

    def test_canonical_validation_bytes_and_exact_joins_or_absence(self):
        canon_raw=(names.ROOT/"config/model-inspection.json").read_bytes()
        validation_raw=(names.ROOT/"config/model-validation.json").read_bytes()
        self.assertEqual("55a86fac63f12faa0f74fbdeb1f1b992374513acd174c7353885898ba436e1cd",hashlib.sha256(historical_canonical_bytes(self, canon_raw)).hexdigest())
        self.assertEqual("cc9756fdf6ca78a977c456fb9a95c93dd01401fc318722e3947f175bfac48e02",hashlib.sha256(validation_raw).hexdigest())
        canonical=json.loads(canon_raw);validation=json.loads(validation_raw)
        for entry,joins in SOURCE_JOINS.items():
            target=f"/us-bank-01-preview/geometry/{entry:04d}-00.gltf"
            matches=[(i,r) for i,r in enumerate(validation["render_cases"])
                     if r.get("source","").endswith(target)]
            self.assertEqual([j["validation_index"] for j in joins],[i for i,_ in matches])
            linked=[(i,r) for i,r in enumerate(canonical["models"])
                    if r.get("render_case") in {v["id"] for _,v in matches}]
            self.assertEqual([j["canonical_index"] for j in joins],[i for i,_ in linked])
            for j in joins:
                c=canonical["models"][j["canonical_index"]];v=validation["render_cases"][j["validation_index"]]
                self.assertEqual(j["canonical_sha256"],digest(c));self.assertEqual(j["validation_sha256"],digest(v))
                self.assertEqual(c["render_case"],v["id"])
            if entry in (154,155,162):
                self.assertEqual([],joins)
                self.assertFalse(any(r.get("name")==f"character-bank01-{entry:04d}-rom"
                                     for r in canonical["models"]))

    def test_limits_hold_visibility_identity_and_descriptor_claims(self):
        records={r["entry"]:r for r in names.load_registry()["models"] if r["bank"]==1}
        for _,entry,_ in HELD_CHARACTER_NAMES:
            limits=" ".join(records[entry]["limitations"])
            for phrase in ["runtime activation", "seven complete shared consumers", "native material parity",
                           "Static scene and player-selection associations remain conditional", "func_15084D00"]:
                self.assertIn(phrase,limits)
        self.assertIn("material renders still omit torso, arm and leg surfaces", " ".join(records[151]["limitations"]))
        self.assertIn("Heist, Trinity", " ".join(records[151]["limitations"]))
        for entry,col,count in [(154,"blue",174),(155,"yellow",186),(162,"red",210)]:
            limits=" ".join(records[entry]["limitations"])
            for phrase in ["direct fresh visual review", "no exact canonical or validation record exists",
                           f"Eye colour ({col})", f"{count} indexed-combiner-unresolved faces",
                           "raw captures were unavailable", "proper bat identity", "child/baby age"]:
                self.assertIn(phrase,limits)
        self.assertIn("no species, Dinosaur/Yoshi association, hatching behavior or absolute size",
                      " ".join(records[171]["limitations"]))
        self.assertNotIn(161,records)

    def test_equal_bytes_do_not_spread_labels_to_unknown_numeric_identities(self):
        registry=names.load_registry();payload=b"same bytes do not equate numeric identities"
        for r in registry["models"]:
            r.update(source_bytes=len(payload),model_sha1=hashlib.sha1(payload).hexdigest(),
                     model_sha256=hashlib.sha256(payload).hexdigest())
        unknown={"status":"unknown","name":None}
        for key,label in HELD_CHARACTER_NAMES.items():
            self.assertEqual(label,resolve_synthetic_name(registry,"us",registry["rom_sha1"],key,payload)["name"])
            for other in [(1,key[1],1),(3,key[1],1),(4,key[1],1),(9,key[1],1)]:
                self.assertEqual(unknown,resolve_synthetic_name(registry,"us",registry["rom_sha1"],other,payload))
            for profile,rom_hash in [("eu",registry["rom_sha1"]),("us","0"*40)]:
                self.assertEqual(unknown,resolve_synthetic_name(registry,profile,rom_hash,key,payload))
        for key in [(1,161,0),(1,151,2),(1,154,2),(1,155,2),(1,162,2),(1,171,2)]:
            self.assertEqual(unknown,resolve_synthetic_name(registry,"us",registry["rom_sha1"],key,payload))

    @unittest.skipUnless((names.ROOT/"roms/baserom.us.z64").is_file(),"owned US ROM unavailable")
    def test_owned_positive_models_then_targeted_identity_hash_size_failures(self):
        registry=names.load_registry()
        _,_,rom_hash,bundles,_=models.load_model_bundles("us",names.ROOT/"roms/baserom.us.z64",1)
        sources={(1,b.index,s.index):s.data for b in bundles for s in b.segments}
        # Positive controls cover all five additions, held 161 and comparison 114 before any mutation.
        for entry,pin in MODEL_PINS.items():
            data=sources[1,entry,0]
            self.assertEqual(pin["source_bytes"],len(data))
            self.assertEqual(pin["source_hashes"],dict(sha1=hashlib.sha1(data).hexdigest(),sha256=hashlib.sha256(data).hexdigest()))
            geometry,layout=models.parse_character_model_geometry(data)
            primary,_=parts.primary_preview(data,geometry,layout)
            self.assertEqual((pin["vertices"],pin["primary_faces"],pin["joints"]),
                             (len(primary.vertices),len(primary.faces),len(layout["joints"])))
            result=names.resolve_name(registry,"us",rom_hash,(1,entry,0),data)
            self.assertEqual({"status":"unknown","name":None} if entry==161 else
                             ("Berri — pink outfit" if entry==114 else HELD_CHARACTER_NAMES[1,entry,0]),
                             result if entry==161 else result["name"])
        for key in HELD_CHARACTER_NAMES:
            data=sources[key]
            for offset in [0,39,len(data)//2,len(data)-1]:
                bad=bytearray(data);bad[offset]^=1
                with self.subTest(key=key,offset=offset),self.assertRaisesRegex(ValueError,"named model source identity changed"):
                    names.resolve_name(registry,"us",rom_hash,key,bytes(bad))
            for bad_data in [data[:-1],data+b"\0"]:
                with self.subTest(key=key,length=len(bad_data)),self.assertRaisesRegex(ValueError,"named model source identity changed"):
                    names.resolve_name(registry,"us",rom_hash,key,bad_data)
            for field in ["model_sha1","model_sha256","source_bytes"]:
                bad=copy.deepcopy(registry);r=next(r for r in bad["models"] if (r["bank"],r["entry"],r["segment"])==key)
                r[field]=r[field]+1 if field=="source_bytes" else "0"*len(r[field])
                with self.subTest(key=key,field=field),self.assertRaisesRegex(ValueError,"named model source identity changed"):
                    names.resolve_name(bad,"us",rom_hash,key,data)
            wrong=sources[1,114,0]
            with self.subTest(key=key,identity="comparison substitution"),self.assertRaisesRegex(ValueError,"named model source identity changed"):
                names.resolve_name(registry,"us",rom_hash,key,wrong)

    @unittest.skipUnless((names.ROOT/"roms/baserom.us.z64").is_file(),"owned US ROM unavailable")
    def test_owned_complete_consumer_positive_then_every_byte_and_tail_failures(self):
        path,layout=models.resolve_rom("us",names.ROOT/"roms/baserom.us.z64")
        rom,_=models.normalize_rom(path.read_bytes())
        code=models.parse_game_archive(rom[layout["game_start"]:layout["game_end"]]).code
        registry=names.load_registry();registry["models"]=[next(r for r in registry["models"] if (r["bank"],r["entry"],r["segment"])==(1,151,0))]
        self.assertEqual(7,names.verify_consumers(code,layout["game_vram"],registry))
        for consumer in EXPECTED_CONSUMERS:
            base=int(consumer["vram"],16);start=base-layout["game_vram"]
            selected=code[start:start+consumer["size_bytes"]]
            one=copy.deepcopy(registry);one["models"][0]["consumers"]=[consumer]
            self.assertEqual(1,names.verify_consumers(selected,base,one))
            for offset in range(len(selected)):
                changed=bytearray(selected);changed[offset]^=1
                with self.subTest(symbol=consumer["symbol"],offset=offset),self.assertRaisesRegex(ValueError,"model-name consumer changed: "+consumer["symbol"]):
                    names.verify_consumers(bytes(changed),base,one)
            for amount in [1,4]:
                with self.subTest(symbol=consumer["symbol"],tail=amount),self.assertRaisesRegex(ValueError,"model-name consumer changed: "+consumer["symbol"]):
                    names.verify_consumers(selected[:-amount],base,one)

    @unittest.skipUnless((names.ROOT/"roms/baserom.us.z64").is_file(),"owned US ROM unavailable")
    def test_each_added_records_consumer_hash_size_address_rejected(self):
        path,layout=models.resolve_rom("us",names.ROOT/"roms/baserom.us.z64")
        rom,_=models.normalize_rom(path.read_bytes())
        code=models.parse_game_archive(rom[layout["game_start"]:layout["game_end"]]).code
        registry=names.load_registry()
        for key in HELD_CHARACTER_NAMES:
            one=copy.deepcopy(registry);one["models"]=[next(r for r in one["models"] if (r["bank"],r["entry"],r["segment"])==key)]
            self.assertEqual(7,names.verify_consumers(code,layout["game_vram"],one))
            for i,consumer in enumerate(EXPECTED_CONSUMERS):
                for field,value in [("sha1","0"*40),("size_bytes",consumer["size_bytes"]-4),("vram",hex(int(consumer["vram"],16)+4))]:
                    bad=copy.deepcopy(one);bad["models"][0]["consumers"][i][field]=value
                    with self.subTest(key=key,symbol=consumer["symbol"],field=field),self.assertRaisesRegex(ValueError,"model-name consumer changed: "+consumer["symbol"]):
                        names.verify_consumers(code,layout["game_vram"],bad)


if __name__=="__main__":
    unittest.main()
