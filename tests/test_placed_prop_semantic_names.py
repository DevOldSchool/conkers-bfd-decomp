"""Bounded bank-03 identities, exact placements and one canonical correction."""
import copy
import hashlib
import json
import struct
import unittest
from test_model_name_confidence import resolve_synthetic_name

from scripts import model_assets as models
from scripts import model_semantic_names as names
from test_attachment_prop_semantic_names import ATTACHMENT_PROP_NAMES, restore_attachment_corrections
from test_key_model_semantic_names import KEY_MODEL_NAMES
from test_held_character_semantic_names import HELD_CHARACTER_NAMES
from test_remaining_scene_prop_semantic_names import (REMAINING_SCENE_PROP_NAMES,
    restore_remaining_scene_corrections, historical_canonical_bytes)

PLACED_PROP_NAMES = {(3, 0, 0): 'Wooden crate',
 (3, 39, 0): 'Wooden barrel',
 (3, 50, 0): 'Round metal hatch',
 (3, 55, 0): 'Green helmet',
 (3, 66, 0): 'Door marked M',
 (3, 69, 0): 'Door marked F',
 (3, 71, 0): 'Twin red canisters',
 (3, 72, 0): 'Radiation-marked missile',
 (3, 75, 0): 'Wooden hatch',
 (3, 76, 0): 'Red warning barrel',
 (3, 78, 0): 'Hanging lantern',
 (3, 80, 0): 'Green-panel post',
 (3, 81, 0): 'Hazard-striped container',
 (3, 84, 0): 'Green gas mask',
 (3, 88, 0): 'Shield',
 (3, 89, 0): 'Green flag',
 (3, 94, 0): 'Double-barrel firearm',
 (3, 96, 0): 'Wooden stool',
 (3, 99, 0): 'Drinking glass',
 (3, 100, 0): 'Twin red canisters',
 (3, 101, 0): 'Radiation-marked missile',
 (3, 102, 0): 'War newspaper',
 (3, 106, 0): 'Three bone-handled knives',
 (3, 107, 0): 'Bone crossbow',
 (3, 109, 0): 'Mines crate'}

CANONICAL_INDEX = 195

CANONICAL_BEFORE = {'category': 'scene-items',
 'label': 'Radioactive barrel — ROM bank 03 / 0076',
 'name': 'object-bank03-0076-rom',
 'note': 'Geometry and embedded texture images extracted from the ROM. Native colours, lighting '
         'and appearance remain unverified. No capture inputs.',
 'render_case': 'object-bank03-0076-rom'}

CANONICAL_AFTER = {'aliases': ['Radioactive barrel (former label)',
             'Radioactive barrel — ROM bank 03 / 0076 (former label)'],
 'category': 'scene-items',
 'label': 'Red warning barrel — ROM bank 03 / 0076',
 'name': 'object-bank03-0076-rom',
 'note': 'Geometry and embedded texture images extracted from the ROM. Native colours, lighting '
         'and appearance remain unverified. No capture inputs. The visible yellow panel bears a '
         'black exclamation warning. Radioactive contents and gameplay behavior are not '
         'established by this source-model appearance.',
 'render_case': 'object-bank03-0076-rom'}

EXPECTED_CONSUMERS = [{'role': 'shared conditional bank-03 route: load kind-0 placement model index at +0x10 and retain '
          'its primary list; a concrete placement witness is separate evidence',
  'sha1': 'b7b5ae00e5b5a3c5a0d28ad82582a25479a3bc66',
  'size_bytes': 2964,
  'symbol': 'func_150039E0',
  'vram': '0x150039E0'},
 {'role': 'shared conditional placed-object dispatch: select runtime record for drawing; no '
          'model-specific activation or visibility is established',
  'sha1': '04f7c62d81e7232c89b3309fdeade178adab34aa',
  'size_bytes': 528,
  'symbol': 'func_151135C4',
  'vram': '0x151135C4'},
 {'role': 'shared conditional placed-object renderer: submit primary list on its ordinary direct '
          'branch only when runtime flags and other gates admit it',
  'sha1': '95326ee5c7b73267556e889aedfdef799930e221',
  'size_bytes': 1204,
  'symbol': 'func_151137D4',
  'vram': '0x151137D4'}]

UNCHANGED_SOURCE_PINS = {'config/model-scene-assemblies.json': '4f2f9d6a63087fffc2894b8cff6d00e0a970001cf8ebd3e7e6159fee86fdb5bc',
 'config/model-validation.json': 'cc9756fdf6ca78a977c456fb9a95c93dd01401fc318722e3947f175bfac48e02',
 'docs/evidence/us_static_scene_assemblies.md': '3b169a97f17868768ec207c1361bbbb7f684e981e2cfa8d7d6d56821dfebeeaf'}

PLACEMENTS = {0: [],
 39: [],
 50: [(12,
       18,
       2,
       '03bb3b2be6b9d2753fdd765a088c03c45dd8d0a0',
       '37c36423f6c4ef4ba67998121c3e88cbd34a1e810de6cfcc464ce7c199ba3aca',
       0)],
 55: [(12,
       4,
       2,
       'd443aca435b98849fb62fa8d2604af4bdf3b853c',
       'ca030427036f9018093f7688f84e8be1538986abbd5c8a3d18446a0a444c2ee9',
       0),
      (12,
       4,
       3,
       '21865e7995c589247f95d45727d7b2f48aa70972',
       '0c3dcc1456d9835b3dc63758702ee3b16091cf30b1b8f320217352bef217038c',
       0)],
 66: [(12,
       29,
       1,
       'd5694405d5e06cfef8ab675d8b1c0da219191a8f',
       'a93f79b211dca4b55fdada9cf3afcb85cf1d693cf2472f27f48711e1b492524d',
       0)],
 69: [(12,
       29,
       3,
       '7476054b84603b9fba267f3bf05cc5e70624fffd',
       '0c24eea7d61134983f6b7e736ec5764befd49888f4476202d2e9234a087040d1',
       0)],
 71: [(12,
       36,
       0,
       '1b8702c13972cee3c5410a5cb2cea6668d1782e2',
       '8aa2f8f27b4c74228ae037225e444544c22acbfd89b56b10c789e517308330a2',
       4),
      (12,
       36,
       7,
       '0dd3a7bf7b13ab58b840fb40ff55a082814c3cc9',
       '9ffd64b07fe4d117501c0130931e5e26d7c2221673a7ed0177b3243c1e0c3b51',
       4)],
 72: [(12,
       36,
       1,
       '4f4415e523d43c16d68879a03c9367e3ff07f2bb',
       '227237480d10d130a8226e2fe7cf2b16188e53fb78b9b242d39307da7dbbfb91',
       4),
      (12,
       36,
       5,
       '00e3b9ac67f3f49f6f2212d932cc0ede4124108b',
       '3b5dca8b6f65141c7bc8341f84a03680fb29cc88ac49360f2d8d522f89e6d3ae',
       4),
      (12,
       50,
       2,
       '34421882fd515d4b7f597a7843c17da06216f420',
       '09eef089040c281e9bea02bfa985bd9080e2f749fed00961653f9da8f86854ad',
       4),
      (12,
       50,
       3,
       '02eabf67a12a1b187ccb754749fc5a01d82e4e00',
       'f224914085199e294199d43e748f8ca6455f64702ad0b4ff39d2ed12e3da3564',
       4),
      (12,
       50,
       4,
       '68642e8bbae84058d77941b4d6a0a53c7e062798',
       '662cf09363b537ff4a5778c1b14b336b5b2a31924ee869aa88a4f419e4b71564',
       4),
      (12,
       50,
       6,
       '7c5ed62fe12e7529418f4472f5edf24525c6a565',
       'b577e5cf034af741fb5dba673a0ee401869cd4dbc1b60b365f953c605305db48',
       4)],
 75: [(12,
       29,
       6,
       '7abe43dd9e654b635328ad8bb892bf0b1ccc087f',
       '0f34f426a0b2222d0c796290c47112047da70d5b51b96cf200cf79a5329ea81f',
       0)],
 76: [],
 78: [(12,
       29,
       8,
       'bd56875d507a0b3679f09ef29755473563196958',
       '19bfbc07c67d9ba46a8421e8667e47c0e617da5b36f1a32ecc07cf8790b10a94',
       0)],
 80: [(12,
       36,
       4,
       '7763a46856b05e4a92c34a781a9fa55b1e0a1172',
       '7f9204b7f924025f0ef11dc022dafca70da8ce6bad6d9e7e735045fb67394759',
       4),
      (12,
       36,
       6,
       '82cd4bdbabedef0e43affe1b67d963bc4eecb3ae',
       'ef9ae5344a78e38a6a863cc7dc851a1f77df9b06abc07449ae85b03234ba1c0c',
       4)],
 81: [(12,
       36,
       2,
       '38170654fa9e282acdf64166049750806cfe78a2',
       'b1133f1aa287de1d6b3aae5f0bf4c39d463b61b21ca6bd8be80e84df5da799b2',
       4)],
 84: [(12,
       45,
       9,
       '942a92d604573b78e81d9babfa2c3dd2b4bad087',
       'b749a2ad651823825c838c6b80fe4eb777ddf86515197448a274b7942a7b79cd',
       4),
      (12,
       45,
       10,
       '975e0049cb4ff4408b012d9f5961916af4a5403e',
       'd97bb01138a330edd295a8367786f2abe434c64dd350e65afd6b977f4b5f8f7d',
       4),
      (12,
       45,
       11,
       '5fb8d2d676a4ace7e915a46603975a5909c94b29',
       '7d12061932e2b1e25a2670e901e309f2e3a80e46e56b49b82a4e80e290f8caad',
       4),
      (12,
       45,
       12,
       '96af61f1d9e83370b1b14a4127741b971d6ea6f7',
       'fd6f8f5db0bc31cc79f15a11e8f2f203e9d408bb2a9622660163772914bd4575',
       4),
      (12,
       45,
       13,
       '99653d089affa09d62ff59f8ce7fc91c77df4422',
       'efb334bf4c764466d711449a883a2a242cd5b0f398d0a7cfe8ba4c3f7c658355',
       4),
      (12,
       45,
       14,
       '1a0615c34cf9849e01b77ca5dba65ec4236024e8',
       'e05988fec9737f20dcfb0a8564354d4ff6696812452520472e195ed7537445e6',
       4)],
 88: [(12,
       36,
       8,
       '5de8a70bca09e4b3404aa94188dc288159752ef9',
       '8ae3910d82f6c7c8415fa48d52b82877b4b636ad8e7023a06c50352b4056dab3',
       4)],
 89: [(12,
       48,
       17,
       '0ae3c748f1f76f4cc14544d08662b9123cf1fdd1',
       'a2eb5fda206a55b097f230dd22b5a3b6197d19a0886b69a39c8ba8c4ed13f433',
       4)],
 94: [(12,
       52,
       13,
       'd2a0063a417a38b7efdeafad5258a321cc673388',
       '199688b25dd0b08bdeca53164dec88110fcdf88fcc3be4fd655ef4e03a9d43dd',
       4),
      (12,
       62,
       18,
       '5b3820fbd91a9c391100062f2db26354115e1d58',
       'cf49bf1b1aa475db71cde66e821a1366c7ca9aecb93ecae723e1feb8a793fc3e',
       4),
      (12,
       62,
       28,
       '0094b5fed017ad69ead888ac9179f4abc6e3a7d8',
       'e0ff9fe6272f98e10fc27282d3301f86deeee372ccf9ce8095865a59297cba79',
       4),
      (12,
       63,
       8,
       '7142e642af5e8f747f21a301186f964b55387743',
       '9458629d0c7e789f1fd10c9de3070e0041757cd7efb9d319d594abaec25321b9',
       4),
      (12,
       65,
       0,
       '418cd0c4b397daf1afbd87e59b1e00f1a1ff32ae',
       '69f6fe9262b43c76602e481e64e082daf3049d788cde2b964d5d6035c5629c72',
       0)],
 96: [(12,
       29,
       9,
       '4c579166da5207e6aae7a86dd8085b0c45812d63',
       '641429a3f6815a93e4f97cdd49d19126dac23f184705d2d67c01e71bd3f24183',
       4)],
 99: [(12,
       10,
       3,
       'e8629a046d3a8399fba0387af57288225a915076',
       '1e75ff709c66443956a1e1598a2472582bcb4afcebc4cbd9f779aba67be0abc9',
       0),
      (12,
       10,
       5,
       '73e955a8ef185b81c1aaa6ab98c242ba1db9a2b8',
       'ec4e02efec7a192f06aa39acefd320b7007e6551c2e48dbf129fba89883b3f38',
       0),
      (12,
       41,
       2,
       '4e6c1dd0b7e7c2b644625219b3125a4c53297521',
       '959d71d03c3cf64723affe063f48c58151e0b54c6fc51373a3b8c44f93917f94',
       0),
      (12,
       49,
       0,
       '4b18f77b4fa62d7ab15e903a3e3b2a10968123dd',
       '051d3edc8e924430f90f47b943e75890ff72da2b8cd095170c7efd7da328f752',
       0)],
 100: [(12,
        51,
        0,
        'cd593ee40fde467a6c589626ee8cca3ee59517c3',
        '15fcba1de4aeeb6d96fab7b0e5a466cbe4e329030c3aaf423849d66aeae4adf9',
        4),
       (12,
        51,
        1,
        'd5dc6aa1f1788907e468b36fff3fd38dc59ba3c6',
        'f5ddf1efe77e49490f6ec497e3aa0a9c913b4c6de1bf627e25084b560954098d',
        4),
       (12,
        51,
        5,
        '1c6272331e9bf0f64b6bae7ba68247f0b2d3f2d8',
        'b7929afa0e155f7ec8871012c038a47fb3d6c6cb10a369253cb4b8830db2ece3',
        4)],
 101: [(12,
        51,
        2,
        '3320bd554aafb08a1d3531fa70a361689229d3c5',
        '06b53ea7982916d3a6e9bd8f11dbfb0c0a07dedff827fb3b357ee943337cfbf5',
        4),
       (12,
        51,
        3,
        '5299933c1cdceaca2c0b7661b0dba7bec3f00595',
        '6cc7af0263a0a1eada3c539cfcca54712568fe67ae6394a5eef76af75b04e2f3',
        4),
       (12,
        51,
        4,
        'b878fe05d1504b96a55d1d24f1524f1e33b4b850',
        '58664c470b75617085a27ebbaaa29b384977a0f0d09e08adfd24b8ebfaf396e6',
        4),
       (12,
        51,
        6,
        '1236556eda6b7412ea281c83a073b3df70c337a4',
        '9c599ff078ea2d3abebb52d554bbc1ce1cad28aa35c433808245d83c6d4ae139',
        4)],
 102: [(12,
        6,
        6,
        'ca0091c7906d67291009eaa25fc565f0c12d84b2',
        '4a9c8ca69d1a7cae719d86f8cd574ccacdbd7c91a21d31827b4c1fe0395617da',
        0)],
 106: [(12,
        63,
        13,
        '206331c2eb63da94d7bdec22994051288e4ba138',
        '1bc1aa0a7fd49053a889e7d176b09395a9547d3b9df1ecd7e84669eea892c620',
        4),
       (12,
        63,
        14,
        '9e40323010cb473e7a53708e58aab1983b8ff52b',
        '0bc1a20090fe1d2100d25643c63e320ed7805ba340aaba0b6cd0139b44f31681',
        4),
       (12,
        63,
        17,
        '73fc59d4c0f43817ba4398003018f7f670ae30d0',
        '826e4e57081bfe2ed6859134bc7b8364b4d3b9d307c6c1038d9ebd15400c7a37',
        4),
       (12,
        63,
        18,
        '033ea61759eb2b2c88ec1d48f0d23aae230137ea',
        '458af2413fdcaa9920beb252a60dbfc41096d950d5d5e027ef3b265a8384004c',
        4)],
 107: [(12,
        63,
        11,
        'c7cb7d7146b0a6b09c125c14f55d32d6276b8818',
        '63398f28e2bc403afb6dc5f9ddc74540e9f967b74820414c634d73c34c784ecb',
        4),
       (12,
        63,
        12,
        '7418e6d1ff07481e1ceda7192fe900a7dd059a8e',
        '36858c406bda9590215bccdc16db4759f960868de13b1782486eeece42bb3003',
        4),
       (12,
        63,
        15,
        'b7197bc84813c36ae6f28a9458dadea6eea777b3',
        'a9550948194bd60e4fb6df15af06fefe5a55771b21a4d352b754237b0f5e31bb',
        4),
       (12,
        63,
        16,
        '20e26a1f334c60e540ad67c49e30707cf92a4493',
        '8db2099f7cd33fc33da573f667e5fa0ef1a43b1d0ce88939d6f85b0fae7102a9',
        4)],
 109: []}

DEFAULT_ROW_PINS = {0: ('2f295bb421303fc9658c50db9f7f2237fbbbf54c',
     'c48d65dfccd6a79e9173396cbd5d6ce2676c08da5496b46659bf4f41ba58743e'),
 39: ('eba2573d1ec5c90c9476cc621d601709753f10f5',
      'c3e42245ffdff31c980d63b232de1414ca2461a08c6efccca2af96737ef4d068'),
 50: ('eba2573d1ec5c90c9476cc621d601709753f10f5',
      'c3e42245ffdff31c980d63b232de1414ca2461a08c6efccca2af96737ef4d068'),
 55: ('55730ecaa02e456191798c87dba5372fd5d24641',
      'de695ca3ef6f067f2757d8e21840aa21120c1a8ca5ea48c1d09802ed17f88aea'),
 66: ('55730ecaa02e456191798c87dba5372fd5d24641',
      'de695ca3ef6f067f2757d8e21840aa21120c1a8ca5ea48c1d09802ed17f88aea'),
 69: ('55730ecaa02e456191798c87dba5372fd5d24641',
      'de695ca3ef6f067f2757d8e21840aa21120c1a8ca5ea48c1d09802ed17f88aea'),
 71: ('19bdd10dac489ff194cc79961d34aeaa3692d81b',
      '8d28d22974c948991b72a1d9407288ae24b07691d80bcc7e6dd947d9938b5581'),
 72: ('19bdd10dac489ff194cc79961d34aeaa3692d81b',
      '8d28d22974c948991b72a1d9407288ae24b07691d80bcc7e6dd947d9938b5581'),
 75: ('d624419583e08ccfd4ba14a20aee92311008f9c1',
      '5c3b603ee05da40370835f9aca1097de3f44c32e011a1702d6b2e9faf1b505b1'),
 76: ('eba2573d1ec5c90c9476cc621d601709753f10f5',
      'c3e42245ffdff31c980d63b232de1414ca2461a08c6efccca2af96737ef4d068'),
 78: ('f4718d45b8814efdd73fdcb2040577fd833e36bc',
      '6e6fa388875ea948bff3ec9dbc095c13110717a74e24ab074979df40fdcdd747'),
 80: ('19bdd10dac489ff194cc79961d34aeaa3692d81b',
      '8d28d22974c948991b72a1d9407288ae24b07691d80bcc7e6dd947d9938b5581'),
 81: ('19bdd10dac489ff194cc79961d34aeaa3692d81b',
      '8d28d22974c948991b72a1d9407288ae24b07691d80bcc7e6dd947d9938b5581'),
 84: ('4d5c3e3ccbc8ae59daed2efb03975523609d0a2d',
      '4d92fc036828d902b3cee53eddd585e80686e168319894a02cc6aa865994aac8'),
 88: ('afe7a56e178af27f3521fbb84976ee9e2da669a7',
      '8bcd3b2385840a1e6351aaedfaf167a273d848b37eb21d42678c39ef754c146e'),
 89: ('19bdd10dac489ff194cc79961d34aeaa3692d81b',
      '8d28d22974c948991b72a1d9407288ae24b07691d80bcc7e6dd947d9938b5581'),
 94: ('7d6f3ae201c26a2e5fd6ad34d89913407c0b5cbc',
      'df153584514bfcd52f7a041b3cb707b2e8eb1dc94b44075c4f54312e4a79f748'),
 96: ('88df65a93addd0dcfe52add2a3e4402c830cb276',
      '1cd54986d7b10f8da284e48d9e73b0423accd0b9b0a7fb5ad8b536d3988c24d9'),
 99: ('729f0efde6039f7406e6f8e9034a848fa70b3811',
      '87c7db7ddd52ed2684799ae70e42c71b3ce6ae01f5bba2eaed65743041766b33'),
 100: ('15c236cca09e8a333ecfb4c50691d1d53462d800',
       'b67079e0c243acf4ab415514900b53b7b44068e4390cd4b905d61e94ad5c79b2'),
 101: ('15c236cca09e8a333ecfb4c50691d1d53462d800',
       'b67079e0c243acf4ab415514900b53b7b44068e4390cd4b905d61e94ad5c79b2'),
 102: ('55730ecaa02e456191798c87dba5372fd5d24641',
       'de695ca3ef6f067f2757d8e21840aa21120c1a8ca5ea48c1d09802ed17f88aea'),
 106: ('4d5c3e3ccbc8ae59daed2efb03975523609d0a2d',
       '4d92fc036828d902b3cee53eddd585e80686e168319894a02cc6aa865994aac8'),
 107: ('7d6f3ae201c26a2e5fd6ad34d89913407c0b5cbc',
       'df153584514bfcd52f7a041b3cb707b2e8eb1dc94b44075c4f54312e4a79f748'),
 109: ('7d6f3ae201c26a2e5fd6ad34d89913407c0b5cbc',
       'df153584514bfcd52f7a041b3cb707b2e8eb1dc94b44075c4f54312e4a79f748')}


def digest(value):
    return hashlib.sha256(json.dumps(value, sort_keys=True, separators=(",", ":")).encode()).hexdigest()


class PlacedPropSemanticNameTests(unittest.TestCase):
    def test_all_145_prior_records_and_branch_are_unchanged(self):
        registry = names.load_registry()
        retained = [r for r in registry["models"]
                    if (r["bank"], r["entry"], r["segment"]) not in PLACED_PROP_NAMES and (r["bank"], r["entry"], r["segment"]) not in ATTACHMENT_PROP_NAMES
                    and (r["bank"], r["entry"], r["segment"]) not in KEY_MODEL_NAMES
                    and (r["bank"], r["entry"], r["segment"]) not in HELD_CHARACTER_NAMES
                    and (r["bank"], r["entry"], r["segment"]) not in REMAINING_SCENE_PROP_NAMES]
        self.assertEqual(145, len(retained))
        self.assertEqual("31f7baee26ea09d494702562af84d9a5d7b1fc51e3785124c40f16bf69af052b", digest(retained))
        self.assertEqual([(1, 75, 0)], [(r["bank"], r["entry"], r["segment"])
                         for r in registry["models"] if "model_specific_branch" in r])

    def test_all_25_additions_and_conditional_shared_contracts(self):
        added = [r for r in names.load_registry()["models"]
                 if (r["bank"], r["entry"], r["segment"]) in PLACED_PROP_NAMES]
        self.assertEqual(25, len(added))
        self.assertEqual(PLACED_PROP_NAMES,
                         {(r["bank"], r["entry"], r["segment"]): r["name"] for r in added})
        self.assertEqual("3dd5c2b38eb366ad943ef57bba8b5c2561df4d3c95ebf05bff815f8d18ef2eb5", digest(added))
        for r in added:
            self.assertEqual(EXPECTED_CONSUMERS, r["consumers"])
            self.assertNotIn("model_specific_branch", r)
            self.assertTrue(any("conditional contracts" in s for s in r["limitations"]))
        self.assertEqual([2964, 528, 1204], [c["size_bytes"] for c in EXPECTED_CONSUMERS])

    def test_numeric_namespaces_remain_distinct(self):
        registry = names.load_registry()
        payload = b"equal bytes cannot expand a numeric identity"
        for r in registry["models"]:
            r.update(source_bytes=len(payload), model_sha1=hashlib.sha1(payload).hexdigest(),
                     model_sha256=hashlib.sha256(payload).hexdigest())
        for key, label in PLACED_PROP_NAMES.items():
            self.assertEqual(label, resolve_synthetic_name(registry, "us", registry["rom_sha1"], key, payload)["name"])
            self.assertEqual({"status": "unknown", "name": None},
                             resolve_synthetic_name(registry, "us", registry["rom_sha1"], (3, key[1], 1), payload))
        for key in ((3, 2, 0), (3, 38, 0), (3, 70, 1), (3, 108, 1), (9, 138, 0), (1, 161, 0)):
            self.assertEqual({"status": "unknown", "name": None},
                             resolve_synthetic_name(registry, "us", registry["rom_sha1"], key, payload))

    def test_byte_identical_pairs_keep_keys_and_base_names(self):
        records = {r["entry"]: r for r in names.load_registry()["models"] if r["bank"] == 3}
        for a, b in ((71, 100), (72, 101)):
            self.assertNotEqual(records[a]["entry"], records[b]["entry"])
            for field in ("source_bytes", "model_sha1", "model_sha256", "name"):
                self.assertEqual(records[a][field], records[b][field])
            self.assertNotIn("variant", records[b]["name"])

    def test_bounded_absences_and_appearance_limits(self):
        records = {r["entry"]: r for r in names.load_registry()["models"]
                   if (r["bank"], r["entry"], r["segment"]) in PLACED_PROP_NAMES}
        for entry, r in records.items():
            limits = " ".join(r["limitations"])
            self.assertEqual(entry in {0, 39, 76, 109}, "No matching placement" in limits)
            if entry in {0, 39, 76, 109}:
                self.assertIn("does not establish unused status", limits)
            self.assertIn("No runtime activation", limits)
        for entry, label in ((76, "Red warning barrel"), (80, "Green-panel post"),
                             (94, "Double-barrel firearm"), (106, "Three bone-handled knives")):
            self.assertEqual(label, records[entry]["name"])

    def test_only_entry76_canonical_correction(self):
        canonical = json.loads((names.ROOT / "config/model-inspection.json").read_text())
        self.assertEqual(CANONICAL_AFTER, canonical["models"][CANONICAL_INDEX])
        for field in CANONICAL_BEFORE.keys() - {"label", "note", "aliases"}:
            self.assertEqual(CANONICAL_BEFORE[field], CANONICAL_AFTER[field])
        self.assertTrue(CANONICAL_AFTER["note"].startswith(CANONICAL_BEFORE["note"] + " "))
        self.assertIn(CANONICAL_BEFORE["label"] + " (former label)", CANONICAL_AFTER["aliases"])
        canonical["models"][CANONICAL_INDEX] = copy.deepcopy(CANONICAL_BEFORE)
        restore_remaining_scene_corrections(self, canonical)
        restore_attachment_corrections(self, canonical)
        self.assertEqual("32b76aa9908f1c65f78ac72be6051b6e393b1410b30973a73209ef9e54ad444d", digest(canonical))
        post = next(r for r in canonical["models"] if r["name"] == "object-bank03-0080-rom")
        self.assertEqual("Green illuminated post — ROM bank 03 / 0080", post["label"])
        for path, expected in UNCHANGED_SOURCE_PINS.items():
            self.assertEqual(expected, hashlib.sha256((names.ROOT / path).read_bytes()).hexdigest())

    @unittest.skipUnless((names.ROOT / "roms/baserom.us.z64").is_file(), "owned US ROM unavailable")
    def test_owned_rom_models_and_payload_mutations(self):
        registry = names.load_registry()
        _, _, rom_digest, bundles, _ = models.load_model_bundles("us", names.ROOT / "roms/baserom.us.z64", 3)
        sources = {(3, b.index, s.index): s.data for b in bundles for s in b.segments}
        self.assertEqual(registry["rom_sha1"], rom_digest)
        for key, label in PLACED_PROP_NAMES.items():
            self.assertEqual(label, names.resolve_name(registry, "us", rom_digest, key, sources[key])["name"])
            changed = bytearray(sources[key]); changed[-1] ^= 1
            with self.assertRaisesRegex(ValueError, "named model source identity changed"):
                names.resolve_name(registry, "us", rom_digest, key, bytes(changed))
        self.assertEqual(sources[3, 71, 0], sources[3, 100, 0])
        self.assertEqual(sources[3, 72, 0], sources[3, 101, 0])

    @unittest.skipUnless((names.ROOT / "roms/baserom.us.z64").is_file(), "owned US ROM unavailable")
    def test_all_52_placements_and_propagated_flags(self):
        path, layout = models.resolve_rom("us", names.ROOT / "roms/baserom.us.z64")
        rom, _ = models.normalize_rom(path.read_bytes())
        self.assertEqual(names.load_registry()["rom_sha1"], hashlib.sha1(rom).hexdigest())
        game = models.parse_game_archive(rom[layout["game_start"]:layout["game_end"]])
        for entry, expected in DEFAULT_ROW_PINS.items():
            start = 0x800A26C0 + entry * 12 - layout["game_data_vram"]
            row = game.data[start:start + 12]
            self.assertEqual(expected, (hashlib.sha1(row).hexdigest(), hashlib.sha256(row).hexdigest()))
        banks = {b.index: b for b in models.parse_asset_banks(rom, layout["asset_table"])}
        tables = {}; kinds = {11: {}, 12: {}}
        for bank in (11, 12):
            for e in models.parse_asset_entries(rom, banks[bank]):
                raw = rom[e.start:e.end]
                data = models.decode_rzip_chunk(raw).data if e.compressed else raw
                data = models.nested_asset_payload(data, 2) if bank == 12 else data
                count, padding = divmod(len(data), 0x44)
                self.assertFalse(any(data[count * 0x44:]))
                if bank == 12:
                    self.assertEqual(0, padding)
                tables[bank, e.index] = [data[i * 0x44:(i + 1) * 0x44] for i in range(count)]
                for record in tables[bank, e.index]:
                    kind = struct.unpack_from(">I", record, 12)[0]
                    kinds[bank][kind] = kinds[bank].get(kind, 0) + 1
        self.assertEqual({1: 296, 2: 431}, kinds[11])
        self.assertEqual({0: 511}, kinds[12])
        actual = {entry: [] for entry in PLACEMENTS}
        for scene in sorted({s for _, s in tables}):
            # Selector40/66 marker persists across later records and the bank
            # transition, but is reset for each loader invocation/scene.
            marker = False
            for bank in (11, 12):
                for index, record in enumerate(tables.get((bank, scene), [])):
                    kind, entry, selector = struct.unpack_from(">III", record, 12)
                    marker |= selector in (40, 66)
                    if kind != 0 or entry not in actual:
                        continue
                    start = 0x800A26C0 + entry * 12 - layout["game_data_vram"]
                    defaults = game.data[start:start + 12]
                    flags = (defaults[9] & 0xF7) | (4 if marker else 0)
                    actual[entry].append((bank, scene, index, hashlib.sha1(record).hexdigest(),
                                          hashlib.sha256(record).hexdigest(), flags))
        self.assertEqual(PLACEMENTS, actual)
        self.assertEqual(52, sum(map(len, actual.values())))
        self.assertEqual([0, 39, 76, 109], [e for e, rows in actual.items() if not rows])
        # An initialized branch selector is separate from runtime eligibility.
        self.assertTrue(all(not row[-1] & 2 for rows in actual.values() for row in rows))


if __name__ == "__main__":
    unittest.main()
