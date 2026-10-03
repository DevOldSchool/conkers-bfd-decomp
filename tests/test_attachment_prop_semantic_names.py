"""Exact bank-09 attachment identities, bounded actions and approved label corrections."""
import copy
import hashlib
import json
import struct
import unittest
from test_model_name_confidence import resolve_synthetic_name

from scripts import model_assets as models
from scripts import model_semantic_names as names
from scripts import model_attachment_events as events
from test_key_model_semantic_names import KEY_MODEL_NAMES
from test_held_character_semantic_names import HELD_CHARACTER_NAMES
from test_remaining_scene_prop_semantic_names import (REMAINING_SCENE_PROP_NAMES,
    restore_remaining_scene_corrections, historical_canonical_bytes)

ATTACHMENT_PROP_NAMES = {(9, 13, 0): 'Bottle',
 (9, 20, 0): 'Lighter-fluid container',
 (9, 24, 0): 'Frying pan',
 (9, 25, 0): 'Yellow handheld console',
 (9, 28, 0): 'Mask and snorkel',
 (9, 42, 0): 'Toilet-paper roll',
 (9, 43, 0): 'Crown',
 (9, 44, 0): 'Travel suitcase',
 (9, 55, 0): 'Chainsaw',
 (9, 58, 0): 'Curved sword',
 (9, 61, 0): 'Paired red canisters',
 (9, 65, 0): 'Revolver',
 (9, 70, 0): 'Black gas mask',
 (9, 71, 0): 'Green gas mask',
 (9, 73, 0): 'Green ring-pull can',
 (9, 75, 0): 'Flashlight',
 (9, 83, 0): 'Scalpel',
 (9, 84, 0): 'Syringe',
 (9, 93, 0): 'Skull bandana',
 (9, 96, 0): 'Open milk carton',
 (9, 99, 0): 'Headphones',
 (9, 111, 0): 'Drumstick',
 (9, 112, 0): 'Hexagonal dumbbell',
 (9, 113, 0): 'Scythe',
 (9, 114, 0): 'Pitchfork',
 (9, 118, 0): 'Red-tipped scalpel',
 (9, 121, 0): 'Black sunglasses',
 (9, 123, 0): 'Bone-handled knife',
 (9, 124, 0): 'Wrapped-handle knife',
 (9, 125, 0): 'White mug',
 (9, 131, 0): 'Three coloured balls',
 (9, 139, 0): 'Handled net'}

CANONICAL_CORRECTIONS = {375: {'after': {'aliases': ['Milk carton (former label)',
                             'Milk carton — ROM 09 / 0020 (former label)'],
                 'category': 'scene-items',
                 'label': 'Lighter-fluid container — ROM 09 / 0020',
                 'name': 'object-bank09-0020-rom',
                 'note': 'Geometry and textures extracted from the ROM. Native colour, lighting '
                         'and raster appearance remain unverified. No capture inputs. The exact '
                         'linked texture pixels read LIGHTER FLUID beside flame icons; the '
                         'diagnostic vertex view shows a rectangular container with a narrow '
                         'spout. Current material views expose only part of the form, especially '
                         'from front and rear. This descriptive label does not establish actual '
                         'contents or gameplay use. Native visibility remains unverified.',
                 'render_case': 'object-bank09-0020-rom'},
       'before': {'category': 'scene-items',
                  'label': 'Milk carton — ROM 09 / 0020',
                  'name': 'object-bank09-0020-rom',
                  'note': 'Geometry and textures extracted from the ROM. Native colour, lighting '
                          'and raster appearance remain unverified. No capture inputs.',
                  'render_case': 'object-bank09-0020-rom'}},
 380: {'after': {'aliases': ['Cleaver (former label)', 'Cleaver — ROM 09 / 0123 (former label)'],
                 'category': 'scene-items',
                 'label': 'Bone-handled knife — ROM 09 / 0123',
                 'name': 'object-bank09-0123-rom',
                 'note': 'Geometry and textures extracted from the ROM. Native colour, lighting '
                         'and raster appearance remain unverified. No capture inputs. Fresh '
                         'material and diagnostic vertex views show a broad pointed blade with a '
                         'pale bone-shaped handle, supporting a descriptive knife label. The exact '
                         'ROM source remains distinct from the wrapped-handle variant. Handle '
                         'material composition, gameplay use and native visibility remain '
                         'unverified.',
                 'render_case': 'object-bank09-0123-rom'},
       'before': {'category': 'scene-items',
                  'label': 'Cleaver — ROM 09 / 0123',
                  'name': 'object-bank09-0123-rom',
                  'note': 'Geometry and textures extracted from the ROM. Native colour, lighting '
                          'and raster appearance remain unverified. No capture inputs.',
                  'render_case': 'object-bank09-0123-rom'}},
 381: {'after': {'aliases': ['Cleaver — wrapped handle (former label)',
                             'Cleaver — wrapped handle — ROM 09 / 0124 (former label)'],
                 'category': 'scene-items',
                 'label': 'Wrapped-handle knife — ROM 09 / 0124',
                 'name': 'object-bank09-0124-rom',
                 'note': 'Geometry and textures extracted from the ROM. Native colour, lighting '
                         'and raster appearance remain unverified. No capture inputs. Fresh '
                         'material and diagnostic vertex views show a broad pointed blade with a '
                         'pale wrap-patterned handle and a red band, supporting a descriptive '
                         'knife label. The exact ROM source remains distinct from the '
                         'bone-shaped-handle variant. Gameplay use and native visibility remain '
                         'unverified.',
                 'render_case': 'object-bank09-0124-rom'},
       'before': {'category': 'scene-items',
                  'label': 'Cleaver — wrapped handle — ROM 09 / 0124',
                  'name': 'object-bank09-0124-rom',
                  'note': 'Geometry and textures extracted from the ROM. Native colour, lighting '
                          'and raster appearance remain unverified. No capture inputs.',
                  'render_case': 'object-bank09-0124-rom'}}}

EXPECTED_CONSUMERS = [{'role': 'shared action interpreter: selected kind-1/2 records request bank-09 model byte +0; '
          'kind-0 follows a distinct parent-modification ABI and action ID is not model ID',
  'sha1': '419012702249e321c26fc2badb49949b0aafa0fc',
  'size_bytes': 356,
  'symbol': 'func_15083568',
  'vram': '0x15083568'},
 {'role': 'conditional shared attachment constructor: retain model byte +1 and distinct action '
          'byte +6; owner, duplicate, allocation and load gates apply; caller a3 controls halfword '
          '+1C',
  'sha1': 'f506f08cf457bc3d9bb7a751c0c1381e2ddd39a9',
  'size_bytes': 608,
  'symbol': 'func_15030AF4',
  'vram': '0x15030AF4'},
 {'role': 'shared descriptor loader: signed animation selector +17 chooses direct loading or '
          'animation wrapper, preserving model index +1',
  'sha1': 'd03a13f16beb1aacae4a2c964a393164e8a477c4',
  'size_bytes': 384,
  'symbol': 'func_1502FFD8',
  'vram': '0x1502FFD8'},
 {'role': 'shared model loader: pass bank 9 and exact requested index to asset loading; cached '
          'branches retain that identity',
  'sha1': '8637778facf0ce5e9a4cd03316b390e02fdf84e2',
  'size_bytes': 456,
  'symbol': 'func_1502FE10',
  'vram': '0x1502FE10'},
 {'role': 'shared animation wrapper: forward the descriptor model index unchanged to bank-09 '
          'loading; animation selection does not identify the parent',
  'sha1': 'b678946246dbc937322777d197d874c3dbd0839b',
  'size_bytes': 396,
  'symbol': 'func_1503F62C',
  'vram': '0x1503F62C'},
 {'role': 'generic model-keyed initializer called after construction, with side effects for some '
          'selected entries; no gameplay identity or no-op assumption',
  'sha1': '433d396431907cf2bdef8fc872dbcd46dd31d274',
  'size_bytes': 452,
  'symbol': 'func_15031A50',
  'vram': '0x15031A50'}]

PARTIAL_MATERIAL_ENTRIES = {65, 99, 43, 13, 112, 20, 84, 24, 121, 28}

ACTION_PINS = {4: {'animation_selector': -1,
     'entry': 13,
     'flags': 1,
     'header_address': '0x80086CDC',
     'header_hashes': {'sha1': '19403833036a95ed3c257485408c7797a2994c43',
                       'sha256': 'e18c7661b5d645b365f3779e089fcd9e1a92aa25189e09f877cc4de9024f1aad'},
     'kind': 1,
     'record_address': '0x8009CE40',
     'record_hashes': {'sha1': '3f56e352a048b3930bbfd3a24da9f92f5da87aea',
                       'sha256': '9603a86006625dcdadf04a0bcf667b0d2b9d4742b7913b7060046a509a64bc38'},
     'updater_selector': 0},
 12: {'animation_selector': -1,
      'entry': 20,
      'flags': 1,
      'header_address': '0x80086D1C',
      'header_hashes': {'sha1': 'df9da697fe21dd1a7915190ec382f43c043d4466',
                        'sha256': '404ec174bf93b5537d9596c1652a0fd2d2fbe3e0e2aa21a5e3c0d9781c8a4dd3'},
      'kind': 1,
      'record_address': '0x8009CEA0',
      'record_hashes': {'sha1': '1b7589a7a2f0846d4f7b57dc600db7f088bd8e98',
                        'sha256': '14b286861d657d3536a780bc6d75343284cc6c92199fadaa0addb833487d8b6d'},
      'updater_selector': 0},
 16: {'animation_selector': -1,
      'entry': 24,
      'flags': 0,
      'header_address': '0x80086D3C',
      'header_hashes': {'sha1': '4687d9253e116601c8948fdf22a820c321fcc1f4',
                        'sha256': '3360c0eb4d50eca0470a50e88af1980d4c697f65a9e6f4518ae144d4869720bb'},
      'kind': 1,
      'record_address': '0x8009CF20',
      'record_hashes': {'sha1': 'ec5186947d52281da436d26dda96ac07e25ca725',
                        'sha256': 'f2a01c0954e5483b0b43fcd5d501a092563d146c0a2ac80f5306c3032bfbea9a'},
      'updater_selector': 0},
 21: {'animation_selector': -1,
      'entry': 25,
      'flags': 0,
      'header_address': '0x80086D64',
      'header_hashes': {'sha1': '00843197c051d2e4bb334614c3f5e527d51565fc',
                        'sha256': '245362442460fe3b3035eeb24e848f0fae31b765e9780097461ec04dd09e8f2d'},
      'kind': 1,
      'record_address': '0x8009CF30',
      'record_hashes': {'sha1': '7928df3d2dfd2aa0bbf03490c7e27fa6827affad',
                        'sha256': '7b1f3bfeeb0fcfa28378efc1491733207eea894f6d44754e9145839b96996d58'},
      'updater_selector': 2},
 22: {'animation_selector': -1,
      'entry': 65,
      'flags': 0,
      'header_address': '0x80086D6C',
      'header_hashes': {'sha1': '907d3435236eb510d5862e4a51cb1fcc1f0d052b',
                        'sha256': 'dcb172e21adc3ce93188c89d30320ab1be717fd0345c005905765815727d1883'},
      'kind': 1,
      'record_address': '0x8009CFB0',
      'record_hashes': {'sha1': '232f533b705d7c058ac4a48e82c19d487fe13d30',
                        'sha256': '4c7109914bdc83529ad3b14f82a90a59fe893181d620244f417c96fd7052b57e'},
      'updater_selector': 16},
 32: {'animation_selector': -1,
      'entry': 28,
      'flags': 0,
      'header_address': '0x80086DBC',
      'header_hashes': {'sha1': '97fc57daec7ac2b44d27a761d25d91d5add22972',
                        'sha256': 'dd194ae481a996c30579e2664eb22839ff212aa688c590a60feb26fbfa742f68'},
      'kind': 1,
      'record_address': '0x8009D010',
      'record_hashes': {'sha1': 'd70844b2b225c191dcb762fb9a242f19e426c87e',
                        'sha256': '8740604e613d0208278f532505bc953f4971de738d53db11734cdac09e0213da'},
      'updater_selector': 3},
 34: {'animation_selector': -1,
      'entry': 124,
      'flags': 0,
      'header_address': '0x80086DCC',
      'header_hashes': {'sha1': 'b3f9147868ebf3b03042cc5d69d0ec99742f414d',
                        'sha256': '716cc305853aac5570c17919871f972a62420cffeba0abd624fcf43ead5d545a'},
      'kind': 1,
      'record_address': '0x8009D1D0',
      'record_hashes': {'sha1': 'c8893811588d0dc7f6e6e388fc345c2cc34540b9',
                        'sha256': '194667e6623acf4f29b04818d6f3fada23f52b15c44e7b7b7532e87f6025cba2'},
      'updater_selector': 0},
 37: {'animation_selector': -1,
      'entry': 70,
      'flags': 0,
      'header_address': '0x80086DE4',
      'header_hashes': {'sha1': 'e5e50795ddb69454b2ab70a4369abc9f22300e54',
                        'sha256': '36135fc5e30331414ffaf389ea61454328c87365313a794f13697a17ab8ea731'},
      'kind': 1,
      'record_address': '0x8009D5A0',
      'record_hashes': {'sha1': '029b1fc22780ab82a116328fba4989f43c99a564',
                        'sha256': '672dbdf64f32a354ab6fa9eb06f0a31f172804f2f013265bb9c81343a7de878b'},
      'updater_selector': 0},
 38: {'animation_selector': -1,
      'entry': 71,
      'flags': 0,
      'header_address': '0x80086DEC',
      'header_hashes': {'sha1': '24efe58916fc843d55fc92a0da15420b81bf795d',
                        'sha256': '8714cdf726d96c8be4c7a4a79fb503c8e7040cd9f2d341f4232b987bcd007ac0'},
      'kind': 1,
      'record_address': '0x8009D5B0',
      'record_hashes': {'sha1': '3a3b4b47b51a3cfefd8521b49ff85c1f553d9c1d',
                        'sha256': 'c32675126bc3391f4b36c04dfc8664aa395dfa9f732ca4345d37dcafe5b02c08'},
      'updater_selector': 0},
 43: {'animation_selector': 0,
      'entry': 131,
      'flags': 0,
      'header_address': '0x80086E14',
      'header_hashes': {'sha1': 'cafb754ef045ed71c71203be6c04736635254686',
                        'sha256': 'e2a69444f003eaabb0dd798862ad689f58475e5ea0765b2806bf13fdaa803214'},
      'kind': 2,
      'record_address': '0x8009D280',
      'record_hashes': {'sha1': '0aafa02cad9077cb91e7403144e7c62570b474ee',
                        'sha256': 'de8938ada882185799c7dffe192ee39abd130e48fb889de09dda8e839ec3bb7e'},
      'updater_selector': 5},
 47: {'animation_selector': -1,
      'entry': 123,
      'flags': 0,
      'header_address': '0x80086E34',
      'header_hashes': {'sha1': '9af6d9e1d8b03db10d94c41b0e9ab03e986cc021',
                        'sha256': '18cf9ccd236b28f01c2d43b5b2a88452ef9983f597f7a83c1707483b18513cfd'},
      'kind': 1,
      'record_address': '0x8009D1A0',
      'record_hashes': {'sha1': '01f5a6d4cc555dfd78ab7d7215c234eb95d8dc7f',
                        'sha256': '3b6d9815f9d8d948b01a0e3d5cc89dffa08e00e9d1c9683323cab71b488c5f61'},
      'updater_selector': 0},
 48: {'animation_selector': -1,
      'entry': 121,
      'flags': 0,
      'header_address': '0x80086E3C',
      'header_hashes': {'sha1': '7a4a89a156e4dabc829ce2e82074c9e678348e68',
                        'sha256': '4b1104d4b1c281306f86b9393126773bdc736b829d2e3f929e7bf5f133e0ad73'},
      'kind': 1,
      'record_address': '0x8009D8C0',
      'record_hashes': {'sha1': '8384e9a5753267e08c449402cdba4d903b3bf643',
                        'sha256': 'cf7fd4e9c00193b2887d5f518db95786aaf2e0016206df8a5b0712c324ddb2de'},
      'updater_selector': 0},
 51: {'animation_selector': 11,
      'entry': 139,
      'flags': 0,
      'header_address': '0x80086E54',
      'header_hashes': {'sha1': '71a4480a301b0fc2ae5465322d849ddfef80fb93',
                        'sha256': '43e8ff863179cfd430148ef54d9b38b32e8ba1e6bfe492789b6fc4f6fbab87a3'},
      'kind': 2,
      'record_address': '0x8009D170',
      'record_hashes': {'sha1': '2650e98a638485b14058f5f0e87b0ee8135cbfd1',
                        'sha256': '9b511297b2cf3fccfd1b8941599e57a0e635fd3e4d6132799edd3931c0c609e8'},
      'updater_selector': 0},
 62: {'animation_selector': -1,
      'entry': 43,
      'flags': 1,
      'header_address': '0x80086EAC',
      'header_hashes': {'sha1': 'f78b8c8e3070b318c147c07f4026d5c874da5f3c',
                        'sha256': 'a304ad6217678f4bbb1c6c6750d35bf5e4789a5d9e237f06c3647266bfb837e6'},
      'kind': 1,
      'record_address': '0x8009D400',
      'record_hashes': {'sha1': '6de34d2dab8ba6cfaf0af604b7f2677f7d9a34d8',
                        'sha256': '8c0e79f961b7be4a81c358c6ff3607f218505299b9a54e9657a7df6a8dc89c98'},
      'updater_selector': 0},
 63: {'animation_selector': -1,
      'entry': 44,
      'flags': 0,
      'header_address': '0x80086EB4',
      'header_hashes': {'sha1': '439c21b3a7b6196cf5465f62be16ec292d600575',
                        'sha256': 'a3b6ef23a352485201dcbfb7712c2c5d2ed9d8c7af6b486ba765ba0df567c828'},
      'kind': 1,
      'record_address': '0x8009D410',
      'record_hashes': {'sha1': 'edd19bc862f77db7ef4a926d4549df39effbd414',
                        'sha256': 'c938ecc1f0104e4b811000d8c72de4611451188a3f9c94f8b3ec4c56aca69df8'},
      'updater_selector': 0},
 86: {'animation_selector': -1,
      'entry': 55,
      'flags': 5,
      'header_address': '0x80086F6C',
      'header_hashes': {'sha1': '06465ec9a26eeab906474f774d092f1be538c34a',
                        'sha256': '92489386adc01c17b160b32f508cf002b702ad0bc9e31d13b0ae2c0d97818651'},
      'kind': 1,
      'record_address': '0x8009D4A0',
      'record_hashes': {'sha1': '0cdee72bff13500259c225eef49ee577bd255863',
                        'sha256': 'e014b225e7759c354224338bfd94a302d7729a24c48b0dffd84b3f1d2c173a0c'},
      'updater_selector': 17},
 88: {'animation_selector': -1,
      'entry': 58,
      'flags': 2,
      'header_address': '0x80086F7C',
      'header_hashes': {'sha1': 'fe09be25bd3e60d6a986eec31d97d4d58c71c371',
                        'sha256': 'c8b4670cfa1bfbdf6fc99fc792f9897f8fb4f718ef746d3a4231f07025a93df2'},
      'kind': 1,
      'record_address': '0x8009D4E0',
      'record_hashes': {'sha1': 'dc6ef717869b16548abe63148d31db98adc7d445',
                        'sha256': 'e5d8a6ae934aea2d4abff887162d156a585424cbaed8ff6a82edfd3d8b27d9e5'},
      'updater_selector': 0},
 92: {'animation_selector': -1,
      'entry': 61,
      'flags': 0,
      'header_address': '0x80086F9C',
      'header_hashes': {'sha1': '1497f439678a7620064d5791130887b4c1872d08',
                        'sha256': '2e5922aa80e723ddf490eacce139865ae3669445038e193e93e025b8c7a782c3'},
      'kind': 1,
      'record_address': '0x8009D520',
      'record_hashes': {'sha1': '84f49901a115cd36d51e835176656bf06075f101',
                        'sha256': '9c47ea5cb0ae6428106217e603cdb35349434dca674abd975c9eaf952414e67e'},
      'updater_selector': 0},
 96: {'animation_selector': -1,
      'entry': 73,
      'flags': 0,
      'header_address': '0x80086FBC',
      'header_hashes': {'sha1': 'ee67c11b3f0935a4b43027b8b61cde27a66ad547',
                        'sha256': 'f95768a99a200b6c0d89855ba9a9fe0c39402d6250fbeea7923703d1c648c93e'},
      'kind': 1,
      'record_address': '0x8009D5F0',
      'record_hashes': {'sha1': 'e7b811e84ee1835dd891ac55c76171a2ce5c4ea6',
                        'sha256': 'f7a9f2a8b4078dfb5d785dbb56c643f784ff18b4858f5c5cbdeb5eb2db332fa4'},
      'updater_selector': 0},
 100: {'animation_selector': -1,
       'entry': 75,
       'flags': 0,
       'header_address': '0x80086FDC',
       'header_hashes': {'sha1': '8fbfbae18293f7061da52e599f3b2921d5688b57',
                         'sha256': 'de0d157fa7fdfde0ab6f34a1632e73adafb921aab7d2f8166be15351e452d12b'},
       'kind': 1,
       'record_address': '0x8009D710',
       'record_hashes': {'sha1': 'da9ed2931daa938fab5b5e14b628b2347df2e1a8',
                         'sha256': '9aaff1be4d8cc4e55f16c4d2431ae7b8157482d4d8ead08a3c154619281213c9'},
       'updater_selector': 18},
 107: {'animation_selector': -1,
       'entry': 83,
       'flags': 8,
       'header_address': '0x80087014',
       'header_hashes': {'sha1': '692ae2229de0eed5dc6a53be8766b83276b6abd3',
                         'sha256': 'c0a56ed461ddbd1c84dc1a49c44db6d73b902c5a5eaaa726b9a0175e57281ae1'},
       'kind': 1,
       'record_address': '0x8009D620',
       'record_hashes': {'sha1': '08ef0bc8e242f933ab3576ef2a31f5e2975293ee',
                         'sha256': '07211478836f1109d28b18cf9e0273fea88ffbc31ad2c9ee620bf32cbc44c78a'},
       'updater_selector': 0},
 108: {'animation_selector': -1,
       'entry': 84,
       'flags': 8,
       'header_address': '0x8008701C',
       'header_hashes': {'sha1': '0e3b947c93934f5e176999ab1d921611102fd198',
                         'sha256': '7939130dfc1ffab84b2360858dd6e7bcfac62932ca27870f564b80161eb1c931'},
       'kind': 1,
       'record_address': '0x8009D630',
       'record_hashes': {'sha1': 'ffdf3385b111ca0cdce61221140fbe6fac33a456',
                         'sha256': '6f9d4d9494f1420ca003a2e4de4d69fcc38e1459d92136b14dfb6b500bd93d3e'},
       'updater_selector': 0},
 110: {'animation_selector': -1,
       'entry': 125,
       'flags': 0,
       'header_address': '0x8008702C',
       'header_hashes': {'sha1': 'cad0c3ef3f07c6c062e3ed031930331ed71d17b5',
                         'sha256': 'ce4d7044a0f57e83c9800512a2dd9e3acbd61007119a4cc0891bd9a007d099a0'},
       'kind': 1,
       'record_address': '0x8009D8D0',
       'record_hashes': {'sha1': 'c50b3daf88d2f5a47f17dd2a1864df25ed4656bd',
                         'sha256': '17d08daf203b8db75e76abbaf08471d93d251b6ef25a4492c8783005ead0c6dc'},
       'updater_selector': 0},
 121: {'animation_selector': -1,
       'entry': 93,
       'flags': 0,
       'header_address': '0x80087084',
       'header_hashes': {'sha1': 'c0bb303b8a6b9ce9b73855afac66d8092a34be60',
                         'sha256': 'f9fc49647027a5ca4a628fc5d33a31a70eb18e02aa08d02c85536766070d6f5e'},
       'kind': 1,
       'record_address': '0x8009D690',
       'record_hashes': {'sha1': '9f9ae5c74be54e0e65de3d7e42ec7ce83b6b8c32',
                         'sha256': 'e4082f186a33e51b6377406d444b5a49937bf58c5a36842a0100349812cf3b2a'},
       'updater_selector': 20},
 122: {'animation_selector': -1,
       'entry': 93,
       'flags': 0,
       'header_address': '0x8008708C',
       'header_hashes': {'sha1': 'f50900dcdb4d94dea2db3e3aa5f41289e7f5e4c1',
                         'sha256': '033efe859460e8035c8b85d7e20da33d392d86c026ba4606d6714e9ed433bd1a'},
       'kind': 1,
       'record_address': '0x8009D6D0',
       'record_hashes': {'sha1': '8bcd3c236635240657e1dfa3b6a14e81f0d287f5',
                         'sha256': '8953659c6ea096b3f684409fe149cdebf2f846dcc204baca2411676de0e7e98f'},
       'updater_selector': 0},
 125: {'animation_selector': -1,
       'entry': 96,
       'flags': 0,
       'header_address': '0x800870A4',
       'header_hashes': {'sha1': '2e2d3f8fdd3d756b2dd5252404fde0949b381d64',
                         'sha256': 'a77dc33e688878f793c9b03d91176cf4743bb7d17abd029201dbc7fee2b09d08'},
       'kind': 1,
       'record_address': '0x8009D730',
       'record_hashes': {'sha1': 'fd25eb9914fb005fa4e4642ade3e361ea7b45802',
                         'sha256': 'fcaae281c0f17c574b186cb16b15cfa499d32992bdb688e578abae641aaa3107'},
       'updater_selector': 0},
 127: {'animation_selector': -1,
       'entry': 99,
       'flags': 0,
       'header_address': '0x800870B4',
       'header_hashes': {'sha1': 'bbd275147bee83d0385b2082bb5c48ae914e1ad5',
                         'sha256': '701acffdc7ba3755328d04815109c832a2cbd9ad7aef8ef4b6ca3e1fcbd43fb7'},
       'kind': 1,
       'record_address': '0x8009D750',
       'record_hashes': {'sha1': '14b11ae52a6d898cbcad3a06f22313787fe820f4',
                         'sha256': '0d888f1d851f8a2c7431828729fc9a25025c558ebd6e9e23d5961be7031a36bc'},
       'updater_selector': 0},
 147: {'animation_selector': -1,
       'entry': 42,
       'flags': 0,
       'header_address': '0x80087154',
       'header_hashes': {'sha1': 'e9e58e1c74e352a1b04e12c81deceefbbb1bb791',
                         'sha256': 'ee9bd47418f481a9da1af7953ef38c4e6e0b35cdfac3356faa95f70e51bab86d'},
       'kind': 1,
       'record_address': '0x8009D430',
       'record_hashes': {'sha1': '97ebefd42f6c5c0754e395e003d4706f44a8e70d',
                         'sha256': '5c3f21541c7b99a9b8d3922a4e3e970e04ef170885a729f425c94c7b09b5d558'},
       'updater_selector': 11},
 149: {'animation_selector': -1,
       'entry': 111,
       'flags': 0,
       'header_address': '0x80087164',
       'header_hashes': {'sha1': 'fbadd23699c71a847230d3f62200865f5528d2d1',
                         'sha256': 'ba64fe40d040ea5f44e4b880e9365fa23e5f5e4679025056b3b19ae9d605ce01'},
       'kind': 1,
       'record_address': '0x8009D7F0',
       'record_hashes': {'sha1': '54712f3e3e5c29c435601d7dae8a203177911c0a',
                         'sha256': '7b686749a4e8929e8fa01a2ec166a7d300bbcd3cb18f57f2d5ae6e73bed1029a'},
       'updater_selector': 0},
 150: {'animation_selector': -1,
       'entry': 112,
       'flags': 0,
       'header_address': '0x8008716C',
       'header_hashes': {'sha1': '54fd76642cf0b2312195454fd26f89ed644eaf4a',
                         'sha256': '8c1d7f71bc80b89a6dea08a274e8a038e47e19e6fd670c8b56bcd7ce5b6a286a'},
       'kind': 1,
       'record_address': '0x8009D810',
       'record_hashes': {'sha1': '2a642990cad6c555982f0ca93c43dffbefe510ae',
                         'sha256': '2639378b181468eabeb1a6e62957642244650b39c005199d9573edab588f2a33'},
       'updater_selector': 0},
 151: {'animation_selector': -1,
       'entry': 113,
       'flags': 0,
       'header_address': '0x80087174',
       'header_hashes': {'sha1': '660d5ca79c510cc16a6bfa47eef8e84d30017406',
                         'sha256': 'df1d2cb52ab063aceec0a210ee09b70bebe90bddc3285451245fc78ceacc4a06'},
       'kind': 1,
       'record_address': '0x8009D830',
       'record_hashes': {'sha1': '45d4c47a2db6e6d6a15b9e458960f18a8af92bc0',
                         'sha256': 'a579244e3755edf3df66a74e5864e2634a73ed214a460a799ea374abc3ec0371'},
       'updater_selector': 0},
 153: {'animation_selector': -1,
       'entry': 118,
       'flags': 0,
       'header_address': '0x80087184',
       'header_hashes': {'sha1': 'f3efa96b4c0b808ac77a14312e19b9b45dee8433',
                         'sha256': '5241f7cb963f528f778c27b649ebf934cdae9c68fb11c20213c843d60d4024c1'},
       'kind': 1,
       'record_address': '0x8009D860',
       'record_hashes': {'sha1': 'a647dc121cde81db3eb1b7746b734ab6a03a59be',
                         'sha256': '1fd2578aba1dcee2b838d2606107d416b37a912f9860e3e5d7f2f167ccac7419'},
       'updater_selector': 0},
 154: {'animation_selector': -1,
       'entry': 114,
       'flags': 0,
       'header_address': '0x8008718C',
       'header_hashes': {'sha1': '52667b092c4d556aee446c51878118782f80640e',
                         'sha256': '2fd456d30a98d329925344a05f5e592d4906e5b2f5abc15dd36ac833afdc17d0'},
       'kind': 1,
       'record_address': '0x8009D870',
       'record_hashes': {'sha1': '49e20d263d304b28e1d40009f88373f6e2e8fbbb',
                         'sha256': 'a19ac015ec760d6c8176a808d77c9df0bb65d23345298d19f635945e282aa58b'},
       'updater_selector': 0},
 162: {'animation_selector': -1,
       'entry': 111,
       'flags': 0,
       'header_address': '0x800871CC',
       'header_hashes': {'sha1': '3ad352633814fe038d4e891068d75da588db3c18',
                         'sha256': 'cfaf44a19239175e880b1c338f26662825b31f1f216c810dabacec09cf1366dd'},
       'kind': 1,
       'record_address': '0x8009D800',
       'record_hashes': {'sha1': '157503460274c4ccda5b6f95b034a60890d47da3',
                         'sha256': '98b170598b92905ade2a99cc60269903129d810335e7a16fdcddedd2ba5078b4'},
       'updater_selector': 0},
 163: {'animation_selector': -1,
       'entry': 112,
       'flags': 0,
       'header_address': '0x800871D4',
       'header_hashes': {'sha1': 'fd967ff600154253004e03857a574a7ae8f1f310',
                         'sha256': '668d32359bae89d2b3d7dc9d6f9a84fde111aa19cdd44ef0825ced00cc3351e7'},
       'kind': 1,
       'record_address': '0x8009D820',
       'record_hashes': {'sha1': '8268ce1463023910834b96a397419ff698508786',
                         'sha256': '04badab1cdd2e76b9805f535041d78b7602d16e0b959e64543ac0bef1841955a'},
       'updater_selector': 0},
 166: {'animation_selector': -1,
       'entry': 58,
       'flags': 2,
       'header_address': '0x800871EC',
       'header_hashes': {'sha1': '457720b4ed553fcbf3ad6cbb336f2807fb3bfec7',
                         'sha256': '0203855c077aa24819c5bf7a628e56267c1a0fdc060701df08bfa91a3136f02d'},
       'kind': 1,
       'record_address': '0x8009D4F0',
       'record_hashes': {'sha1': '0dbbacc7bf58def76d236bedae7bbf8ef7b9ab68',
                         'sha256': '1bd574799448c2996b81c20a8276efe35514953717eed147f948012362bfd10d'},
       'updater_selector': 0}}

EVENT_COUNTS = {'actions': 49,
 'attachment_entries': 45,
 'create': 109,
 'event_lists': 1472,
 'events': 226,
 'remove': 117,
 'routes': 4027,
 'unresolved_lists': 0}

CREATE_WITNESSES = [{'action': 21,
  'action_record': {'header_address': '0x80086D64',
                    'header_pin': {'size_bytes': 8, 'sha256': '245362442460fe3b3035eeb24e848f0fae31b765e9780097461ec04dd09e8f2d'},
                    'records': [{'address': '0x8009CF30',
                                 'bank': 9,
                                 'entry': 25,
                                 'kind': 1,
                                 'record_pin': {'size_bytes': 16, 'sha256': '7b1f3bfeeb0fcfa28378efc1491733207eea894f6d44754e9145839b96996d58'},
                                 'record_index': 0,
                                 'updater': 2}]},
  'auxiliary_offset': 14400,
  'descriptor_segment_index': 180,
  'event_pin': {'size_bytes': 12, 'sha256': 'b5c0552a8bbf08648b4d85150fa37548a7b217464625c08dd2106d8ff06833d7'},
  'event_index': 1,
  'event_offset': 14428,
  'logical_animation_index': 13,
  'opcode': 105,
  'operation': 'create',
  'pair_index': 90,
  'parent_entries': [0,
                     1,
                     2,
                     3,
                     4,
                     59,
                     117,
                     130,
                     136,
                     144,
                     150,
                     152,
                     156,
                     157,
                     159,
                     160,
                     176,
                     177,
                     178,
                     180],
  'route_bank': 15,
  'route_entry': 0,
  'route_payload_sha1': 'a3054d3f765982fbf8a23520e1758b15812331af',
  'runtime_table_index': 1,
  'time': 28.0},
 {'action': 16,
  'action_record': {'header_address': '0x80086D3C',
                    'header_pin': {'size_bytes': 8, 'sha256': '3360c0eb4d50eca0470a50e88af1980d4c697f65a9e6f4518ae144d4869720bb'},
                    'records': [{'address': '0x8009CF20',
                                 'bank': 9,
                                 'entry': 24,
                                 'kind': 1,
                                 'record_pin': {'size_bytes': 16, 'sha256': 'f2a01c0954e5483b0b43fcd5d501a092563d146c0a2ac80f5306c3032bfbea9a'},
                                 'record_index': 0,
                                 'updater': 0}]},
  'auxiliary_offset': 15048,
  'descriptor_segment_index': 156,
  'event_pin': {'size_bytes': 12, 'sha256': '2fb1dee5ec2f706ad09e2a675120adc22f647d3fcc788ac4c876431612b195fb'},
  'event_index': 1,
  'event_offset': 15076,
  'logical_animation_index': 70,
  'opcode': 105,
  'operation': 'create',
  'pair_index': 78,
  'parent_entries': [0,
                     1,
                     2,
                     3,
                     4,
                     59,
                     117,
                     130,
                     136,
                     144,
                     150,
                     152,
                     156,
                     157,
                     159,
                     160,
                     176,
                     177,
                     178,
                     180],
  'route_bank': 15,
  'route_entry': 0,
  'route_payload_sha1': 'a3054d3f765982fbf8a23520e1758b15812331af',
  'runtime_table_index': 1,
  'time': 5.0},
 {'action': 32,
  'action_record': {'header_address': '0x80086DBC',
                    'header_pin': {'size_bytes': 8, 'sha256': 'dd194ae481a996c30579e2664eb22839ff212aa688c590a60feb26fbfa742f68'},
                    'records': [{'address': '0x8009D010',
                                 'bank': 9,
                                 'entry': 28,
                                 'kind': 1,
                                 'record_pin': {'size_bytes': 16, 'sha256': '8740604e613d0208278f532505bc953f4971de738d53db11734cdac09e0213da'},
                                 'record_index': 0,
                                 'updater': 3}]},
  'auxiliary_offset': 14136,
  'descriptor_segment_index': 216,
  'event_pin': {'size_bytes': 12, 'sha256': '45a66a5cd3a0e8faa4f09bfb6080f5aece793d118860f88550ce7871729f0b48'},
  'event_index': 0,
  'event_offset': 14152,
  'logical_animation_index': 85,
  'opcode': 105,
  'operation': 'create',
  'pair_index': 108,
  'parent_entries': [0,
                     1,
                     2,
                     3,
                     4,
                     59,
                     117,
                     130,
                     136,
                     144,
                     150,
                     152,
                     156,
                     157,
                     159,
                     160,
                     176,
                     177,
                     178,
                     180],
  'route_bank': 15,
  'route_entry': 0,
  'route_payload_sha1': 'a3054d3f765982fbf8a23520e1758b15812331af',
  'runtime_table_index': 1,
  'time': 26.0},
 {'action': 43,
  'action_record': {'header_address': '0x80086E14',
                    'header_pin': {'size_bytes': 8, 'sha256': 'e2a69444f003eaabb0dd798862ad689f58475e5ea0765b2806bf13fdaa803214'},
                    'records': [{'address': '0x8009D280',
                                 'bank': 9,
                                 'entry': 131,
                                 'kind': 2,
                                 'record_pin': {'size_bytes': 16, 'sha256': 'de8938ada882185799c7dffe192ee39abd130e48fb889de09dda8e839ec3bb7e'},
                                 'record_index': 0,
                                 'updater': 5}]},
  'auxiliary_offset': 10572,
  'descriptor_segment_index': 254,
  'event_pin': {'size_bytes': 12, 'sha256': 'afdaa776c45fcf72a8f090386b4863e047dc86142f8ac1ab36ff4a43d3b2b3c3'},
  'event_index': 1,
  'event_offset': 10600,
  'logical_animation_index': 94,
  'opcode': 105,
  'operation': 'create',
  'pair_index': 127,
  'parent_entries': [0,
                     1,
                     2,
                     3,
                     4,
                     59,
                     117,
                     130,
                     136,
                     144,
                     150,
                     152,
                     156,
                     157,
                     159,
                     160,
                     176,
                     177,
                     178,
                     180],
  'route_bank': 15,
  'route_entry': 0,
  'route_payload_sha1': 'a3054d3f765982fbf8a23520e1758b15812331af',
  'runtime_table_index': 1,
  'time': 20.0},
 {'action': 88,
  'action_record': {'header_address': '0x80086F7C',
                    'header_pin': {'size_bytes': 8, 'sha256': 'c8b4670cfa1bfbdf6fc99fc792f9897f8fb4f718ef746d3a4231f07025a93df2'},
                    'records': [{'address': '0x8009D4E0',
                                 'bank': 9,
                                 'entry': 58,
                                 'kind': 1,
                                 'record_pin': {'size_bytes': 16, 'sha256': 'e5d8a6ae934aea2d4abff887162d156a585424cbaed8ff6a82edfd3d8b27d9e5'},
                                 'record_index': 0,
                                 'updater': 0}]},
  'auxiliary_offset': 7704,
  'descriptor_segment_index': 512,
  'event_pin': {'size_bytes': 12, 'sha256': '7c6cfa5854835c0a53b54913cef9a395094538f49c9ba2298840f87a7765bbd3'},
  'event_index': 0,
  'event_offset': 7720,
  'logical_animation_index': 288,
  'opcode': 105,
  'operation': 'create',
  'pair_index': 256,
  'parent_entries': [0,
                     1,
                     2,
                     3,
                     4,
                     59,
                     117,
                     130,
                     136,
                     144,
                     150,
                     152,
                     156,
                     157,
                     159,
                     160,
                     176,
                     177,
                     178,
                     180],
  'route_bank': 15,
  'route_entry': 0,
  'route_payload_sha1': 'a3054d3f765982fbf8a23520e1758b15812331af',
  'runtime_table_index': 1,
  'time': 18.0},
 {'action': 86,
  'action_record': {'header_address': '0x80086F6C',
                    'header_pin': {'size_bytes': 8, 'sha256': '92489386adc01c17b160b32f508cf002b702ad0bc9e31d13b0ae2c0d97818651'},
                    'records': [{'address': '0x8009D4A0',
                                 'bank': 9,
                                 'entry': 55,
                                 'kind': 1,
                                 'record_pin': {'size_bytes': 16, 'sha256': 'e014b225e7759c354224338bfd94a302d7729a24c48b0dffd84b3f1d2c173a0c'},
                                 'record_index': 0,
                                 'updater': 17}]},
  'auxiliary_offset': 7632,
  'descriptor_segment_index': 622,
  'event_pin': {'size_bytes': 12, 'sha256': 'b2d6f1155feb1741bd73f48e01ce07b45ccd8a5a7bab56daba292cee25903a86'},
  'event_index': 1,
  'event_offset': 7660,
  'logical_animation_index': 349,
  'opcode': 105,
  'operation': 'create',
  'pair_index': 311,
  'parent_entries': [0,
                     1,
                     2,
                     3,
                     4,
                     59,
                     117,
                     130,
                     136,
                     144,
                     150,
                     152,
                     156,
                     157,
                     159,
                     160,
                     176,
                     177,
                     178,
                     180],
  'route_bank': 15,
  'route_entry': 0,
  'route_payload_sha1': 'a3054d3f765982fbf8a23520e1758b15812331af',
  'runtime_table_index': 1,
  'time': 21.0},
 {'action': 22,
  'action_record': {'header_address': '0x80086D6C',
                    'header_pin': {'size_bytes': 8, 'sha256': 'dcb172e21adc3ce93188c89d30320ab1be717fd0345c005905765815727d1883'},
                    'records': [{'address': '0x8009CFB0',
                                 'bank': 9,
                                 'entry': 65,
                                 'kind': 1,
                                 'record_pin': {'size_bytes': 16, 'sha256': '4c7109914bdc83529ad3b14f82a90a59fe893181d620244f417c96fd7052b57e'},
                                 'record_index': 0,
                                 'updater': 16}]},
  'auxiliary_offset': 7836,
  'descriptor_segment_index': 632,
  'event_pin': {'size_bytes': 12, 'sha256': '6593d7625026af51c224722bcb0a062b9f1213705f00910d7e24aab224dc481e'},
  'event_index': 1,
  'event_offset': 7864,
  'logical_animation_index': 355,
  'opcode': 105,
  'operation': 'create',
  'pair_index': 316,
  'parent_entries': [0,
                     1,
                     2,
                     3,
                     4,
                     59,
                     117,
                     130,
                     136,
                     144,
                     150,
                     152,
                     156,
                     157,
                     159,
                     160,
                     176,
                     177,
                     178,
                     180],
  'route_bank': 15,
  'route_entry': 0,
  'route_payload_sha1': 'a3054d3f765982fbf8a23520e1758b15812331af',
  'runtime_table_index': 1,
  'time': 8.0},
 {'action': 100,
  'action_record': {'header_address': '0x80086FDC',
                    'header_pin': {'size_bytes': 8, 'sha256': 'de0d157fa7fdfde0ab6f34a1632e73adafb921aab7d2f8166be15351e452d12b'},
                    'records': [{'address': '0x8009D710',
                                 'bank': 9,
                                 'entry': 75,
                                 'kind': 1,
                                 'record_pin': {'size_bytes': 16, 'sha256': '9aaff1be4d8cc4e55f16c4d2431ae7b8157482d4d8ead08a3c154619281213c9'},
                                 'record_index': 0,
                                 'updater': 18}]},
  'auxiliary_offset': 6996,
  'descriptor_segment_index': 658,
  'event_pin': {'size_bytes': 12, 'sha256': '3162879671a72ef8ca96a798e640f0282f0bc4ad0ce888281bcab9e9494b0069'},
  'event_index': 0,
  'event_offset': 7012,
  'logical_animation_index': 374,
  'opcode': 105,
  'operation': 'create',
  'pair_index': 329,
  'parent_entries': [0,
                     1,
                     2,
                     3,
                     4,
                     59,
                     117,
                     130,
                     136,
                     144,
                     150,
                     152,
                     156,
                     157,
                     159,
                     160,
                     176,
                     177,
                     178,
                     180],
  'route_bank': 15,
  'route_entry': 0,
  'route_payload_sha1': 'a3054d3f765982fbf8a23520e1758b15812331af',
  'runtime_table_index': 1,
  'time': 19.0},
 {'action': 16,
  'action_record': {'header_address': '0x80086D3C',
                    'header_pin': {'size_bytes': 8, 'sha256': '3360c0eb4d50eca0470a50e88af1980d4c697f65a9e6f4518ae144d4869720bb'},
                    'records': [{'address': '0x8009CF20',
                                 'bank': 9,
                                 'entry': 24,
                                 'kind': 1,
                                 'record_pin': {'size_bytes': 16, 'sha256': 'f2a01c0954e5483b0b43fcd5d501a092563d146c0a2ac80f5306c3032bfbea9a'},
                                 'record_index': 0,
                                 'updater': 0}]},
  'auxiliary_offset': 15120,
  'descriptor_segment_index': 836,
  'event_pin': {'size_bytes': 12, 'sha256': '2fb1dee5ec2f706ad09e2a675120adc22f647d3fcc788ac4c876431612b195fb'},
  'event_index': 1,
  'event_offset': 15148,
  'logical_animation_index': 476,
  'opcode': 105,
  'operation': 'create',
  'pair_index': 418,
  'parent_entries': [0,
                     1,
                     2,
                     3,
                     4,
                     59,
                     117,
                     130,
                     136,
                     144,
                     150,
                     152,
                     156,
                     157,
                     159,
                     160,
                     176,
                     177,
                     178,
                     180],
  'route_bank': 15,
  'route_entry': 0,
  'route_payload_sha1': 'a3054d3f765982fbf8a23520e1758b15812331af',
  'runtime_table_index': 1,
  'time': 5.0},
 {'action': 47,
  'action_record': {'header_address': '0x80086E34',
                    'header_pin': {'size_bytes': 8, 'sha256': '18cf9ccd236b28f01c2d43b5b2a88452ef9983f597f7a83c1707483b18513cfd'},
                    'records': [{'address': '0x8009D1A0',
                                 'bank': 9,
                                 'entry': 123,
                                 'kind': 1,
                                 'record_pin': {'size_bytes': 16, 'sha256': '3b6d9815f9d8d948b01a0e3d5cc89dffa08e00e9d1c9683323cab71b488c5f61'},
                                 'record_index': 0,
                                 'updater': 0}]},
  'auxiliary_offset': 9060,
  'descriptor_segment_index': 216,
  'event_pin': {'size_bytes': 12, 'sha256': 'beeeff3c1e67611e96b8cfa8ea24f00fe929c331aea72dbddc008e7bdc37ef5d'},
  'event_index': 0,
  'event_offset': 9076,
  'logical_animation_index': 714,
  'opcode': 105,
  'operation': 'create',
  'pair_index': 108,
  'parent_entries': [0,
                     1,
                     2,
                     3,
                     4,
                     59,
                     117,
                     130,
                     136,
                     144,
                     150,
                     152,
                     156,
                     157,
                     159,
                     160,
                     176,
                     177,
                     178,
                     180],
  'route_bank': 15,
  'route_entry': 0,
  'route_payload_sha1': 'a3054d3f765982fbf8a23520e1758b15812331af',
  'runtime_table_index': 1,
  'time': 24.0},
 {'action': 108,
  'action_record': {'header_address': '0x8008701C',
                    'header_pin': {'size_bytes': 8, 'sha256': '7939130dfc1ffab84b2360858dd6e7bcfac62932ca27870f564b80161eb1c931'},
                    'records': [{'address': '0x8009D630',
                                 'bank': 9,
                                 'entry': 84,
                                 'kind': 1,
                                 'record_pin': {'size_bytes': 16, 'sha256': '6f9d4d9494f1420ca003a2e4de4d69fcc38e1459d92136b14dfb6b500bd93d3e'},
                                 'record_index': 0,
                                 'updater': 0}]},
  'auxiliary_offset': 1404,
  'descriptor_segment_index': 84,
  'event_pin': {'size_bytes': 12, 'sha256': 'd577aca6be9cedae961b9898a3115aefd431a10b0a2023bb1d0b0d102d03bfce'},
  'event_index': 3,
  'event_offset': 1456,
  'logical_animation_index': 49,
  'opcode': 105,
  'operation': 'create',
  'pair_index': 42,
  'parent_entries': [90, 95, 116, 141],
  'route_bank': 15,
  'route_entry': 90,
  'route_payload_sha1': '6d9e91402632f984376c4fa67ba9a3aae4d7b3f6',
  'runtime_table_index': 0,
  'time': 32.0},
 {'action': 21,
  'action_record': {'header_address': '0x80086D64',
                    'header_pin': {'size_bytes': 8, 'sha256': '245362442460fe3b3035eeb24e848f0fae31b765e9780097461ec04dd09e8f2d'},
                    'records': [{'address': '0x8009CF30',
                                 'bank': 9,
                                 'entry': 25,
                                 'kind': 1,
                                 'record_pin': {'size_bytes': 16, 'sha256': '7b1f3bfeeb0fcfa28378efc1491733207eea894f6d44754e9145839b96996d58'},
                                 'record_index': 0,
                                 'updater': 2}]},
  'auxiliary_offset': 14376,
  'descriptor_segment_index': 180,
  'event_pin': {'size_bytes': 12, 'sha256': 'b5c0552a8bbf08648b4d85150fa37548a7b217464625c08dd2106d8ff06833d7'},
  'event_index': 1,
  'event_offset': 14404,
  'logical_animation_index': 13,
  'opcode': 105,
  'operation': 'create',
  'pair_index': 90,
  'parent_entries': [128],
  'route_bank': 15,
  'route_entry': 128,
  'route_payload_sha1': 'f66fea8d5739d2e3febe8e840a0b684b09c9b2e1',
  'runtime_table_index': 1,
  'time': 28.0},
 {'action': 16,
  'action_record': {'header_address': '0x80086D3C',
                    'header_pin': {'size_bytes': 8, 'sha256': '3360c0eb4d50eca0470a50e88af1980d4c697f65a9e6f4518ae144d4869720bb'},
                    'records': [{'address': '0x8009CF20',
                                 'bank': 9,
                                 'entry': 24,
                                 'kind': 1,
                                 'record_pin': {'size_bytes': 16, 'sha256': 'f2a01c0954e5483b0b43fcd5d501a092563d146c0a2ac80f5306c3032bfbea9a'},
                                 'record_index': 0,
                                 'updater': 0}]},
  'auxiliary_offset': 15024,
  'descriptor_segment_index': 156,
  'event_pin': {'size_bytes': 12, 'sha256': '2fb1dee5ec2f706ad09e2a675120adc22f647d3fcc788ac4c876431612b195fb'},
  'event_index': 1,
  'event_offset': 15052,
  'logical_animation_index': 70,
  'opcode': 105,
  'operation': 'create',
  'pair_index': 78,
  'parent_entries': [128],
  'route_bank': 15,
  'route_entry': 128,
  'route_payload_sha1': 'f66fea8d5739d2e3febe8e840a0b684b09c9b2e1',
  'runtime_table_index': 1,
  'time': 5.0},
 {'action': 32,
  'action_record': {'header_address': '0x80086DBC',
                    'header_pin': {'size_bytes': 8, 'sha256': 'dd194ae481a996c30579e2664eb22839ff212aa688c590a60feb26fbfa742f68'},
                    'records': [{'address': '0x8009D010',
                                 'bank': 9,
                                 'entry': 28,
                                 'kind': 1,
                                 'record_pin': {'size_bytes': 16, 'sha256': '8740604e613d0208278f532505bc953f4971de738d53db11734cdac09e0213da'},
                                 'record_index': 0,
                                 'updater': 3}]},
  'auxiliary_offset': 14112,
  'descriptor_segment_index': 216,
  'event_pin': {'size_bytes': 12, 'sha256': '45a66a5cd3a0e8faa4f09bfb6080f5aece793d118860f88550ce7871729f0b48'},
  'event_index': 0,
  'event_offset': 14128,
  'logical_animation_index': 85,
  'opcode': 105,
  'operation': 'create',
  'pair_index': 108,
  'parent_entries': [128],
  'route_bank': 15,
  'route_entry': 128,
  'route_payload_sha1': 'f66fea8d5739d2e3febe8e840a0b684b09c9b2e1',
  'runtime_table_index': 1,
  'time': 26.0},
 {'action': 43,
  'action_record': {'header_address': '0x80086E14',
                    'header_pin': {'size_bytes': 8, 'sha256': 'e2a69444f003eaabb0dd798862ad689f58475e5ea0765b2806bf13fdaa803214'},
                    'records': [{'address': '0x8009D280',
                                 'bank': 9,
                                 'entry': 131,
                                 'kind': 2,
                                 'record_pin': {'size_bytes': 16, 'sha256': 'de8938ada882185799c7dffe192ee39abd130e48fb889de09dda8e839ec3bb7e'},
                                 'record_index': 0,
                                 'updater': 5}]},
  'auxiliary_offset': 10572,
  'descriptor_segment_index': 254,
  'event_pin': {'size_bytes': 12, 'sha256': 'afdaa776c45fcf72a8f090386b4863e047dc86142f8ac1ab36ff4a43d3b2b3c3'},
  'event_index': 1,
  'event_offset': 10600,
  'logical_animation_index': 94,
  'opcode': 105,
  'operation': 'create',
  'pair_index': 127,
  'parent_entries': [128],
  'route_bank': 15,
  'route_entry': 128,
  'route_payload_sha1': 'f66fea8d5739d2e3febe8e840a0b684b09c9b2e1',
  'runtime_table_index': 1,
  'time': 20.0},
 {'action': 88,
  'action_record': {'header_address': '0x80086F7C',
                    'header_pin': {'size_bytes': 8, 'sha256': 'c8b4670cfa1bfbdf6fc99fc792f9897f8fb4f718ef746d3a4231f07025a93df2'},
                    'records': [{'address': '0x8009D4E0',
                                 'bank': 9,
                                 'entry': 58,
                                 'kind': 1,
                                 'record_pin': {'size_bytes': 16, 'sha256': 'e5d8a6ae934aea2d4abff887162d156a585424cbaed8ff6a82edfd3d8b27d9e5'},
                                 'record_index': 0,
                                 'updater': 0}]},
  'auxiliary_offset': 7704,
  'descriptor_segment_index': 512,
  'event_pin': {'size_bytes': 12, 'sha256': '7c6cfa5854835c0a53b54913cef9a395094538f49c9ba2298840f87a7765bbd3'},
  'event_index': 0,
  'event_offset': 7720,
  'logical_animation_index': 288,
  'opcode': 105,
  'operation': 'create',
  'pair_index': 256,
  'parent_entries': [128],
  'route_bank': 15,
  'route_entry': 128,
  'route_payload_sha1': 'f66fea8d5739d2e3febe8e840a0b684b09c9b2e1',
  'runtime_table_index': 1,
  'time': 18.0},
 {'action': 86,
  'action_record': {'header_address': '0x80086F6C',
                    'header_pin': {'size_bytes': 8, 'sha256': '92489386adc01c17b160b32f508cf002b702ad0bc9e31d13b0ae2c0d97818651'},
                    'records': [{'address': '0x8009D4A0',
                                 'bank': 9,
                                 'entry': 55,
                                 'kind': 1,
                                 'record_pin': {'size_bytes': 16, 'sha256': 'e014b225e7759c354224338bfd94a302d7729a24c48b0dffd84b3f1d2c173a0c'},
                                 'record_index': 0,
                                 'updater': 17}]},
  'auxiliary_offset': 7632,
  'descriptor_segment_index': 622,
  'event_pin': {'size_bytes': 12, 'sha256': 'b2d6f1155feb1741bd73f48e01ce07b45ccd8a5a7bab56daba292cee25903a86'},
  'event_index': 1,
  'event_offset': 7660,
  'logical_animation_index': 349,
  'opcode': 105,
  'operation': 'create',
  'pair_index': 311,
  'parent_entries': [128],
  'route_bank': 15,
  'route_entry': 128,
  'route_payload_sha1': 'f66fea8d5739d2e3febe8e840a0b684b09c9b2e1',
  'runtime_table_index': 1,
  'time': 21.0},
 {'action': 22,
  'action_record': {'header_address': '0x80086D6C',
                    'header_pin': {'size_bytes': 8, 'sha256': 'dcb172e21adc3ce93188c89d30320ab1be717fd0345c005905765815727d1883'},
                    'records': [{'address': '0x8009CFB0',
                                 'bank': 9,
                                 'entry': 65,
                                 'kind': 1,
                                 'record_pin': {'size_bytes': 16, 'sha256': '4c7109914bdc83529ad3b14f82a90a59fe893181d620244f417c96fd7052b57e'},
                                 'record_index': 0,
                                 'updater': 16}]},
  'auxiliary_offset': 7836,
  'descriptor_segment_index': 632,
  'event_pin': {'size_bytes': 12, 'sha256': '6593d7625026af51c224722bcb0a062b9f1213705f00910d7e24aab224dc481e'},
  'event_index': 1,
  'event_offset': 7864,
  'logical_animation_index': 355,
  'opcode': 105,
  'operation': 'create',
  'pair_index': 316,
  'parent_entries': [128],
  'route_bank': 15,
  'route_entry': 128,
  'route_payload_sha1': 'f66fea8d5739d2e3febe8e840a0b684b09c9b2e1',
  'runtime_table_index': 1,
  'time': 8.0},
 {'action': 100,
  'action_record': {'header_address': '0x80086FDC',
                    'header_pin': {'size_bytes': 8, 'sha256': 'de0d157fa7fdfde0ab6f34a1632e73adafb921aab7d2f8166be15351e452d12b'},
                    'records': [{'address': '0x8009D710',
                                 'bank': 9,
                                 'entry': 75,
                                 'kind': 1,
                                 'record_pin': {'size_bytes': 16, 'sha256': '9aaff1be4d8cc4e55f16c4d2431ae7b8157482d4d8ead08a3c154619281213c9'},
                                 'record_index': 0,
                                 'updater': 18}]},
  'auxiliary_offset': 6996,
  'descriptor_segment_index': 658,
  'event_pin': {'size_bytes': 12, 'sha256': '3162879671a72ef8ca96a798e640f0282f0bc4ad0ce888281bcab9e9494b0069'},
  'event_index': 0,
  'event_offset': 7012,
  'logical_animation_index': 374,
  'opcode': 105,
  'operation': 'create',
  'pair_index': 329,
  'parent_entries': [128],
  'route_bank': 15,
  'route_entry': 128,
  'route_payload_sha1': 'f66fea8d5739d2e3febe8e840a0b684b09c9b2e1',
  'runtime_table_index': 1,
  'time': 19.0},
 {'action': 16,
  'action_record': {'header_address': '0x80086D3C',
                    'header_pin': {'size_bytes': 8, 'sha256': '3360c0eb4d50eca0470a50e88af1980d4c697f65a9e6f4518ae144d4869720bb'},
                    'records': [{'address': '0x8009CF20',
                                 'bank': 9,
                                 'entry': 24,
                                 'kind': 1,
                                 'record_pin': {'size_bytes': 16, 'sha256': 'f2a01c0954e5483b0b43fcd5d501a092563d146c0a2ac80f5306c3032bfbea9a'},
                                 'record_index': 0,
                                 'updater': 0}]},
  'auxiliary_offset': 15096,
  'descriptor_segment_index': 836,
  'event_pin': {'size_bytes': 12, 'sha256': '2fb1dee5ec2f706ad09e2a675120adc22f647d3fcc788ac4c876431612b195fb'},
  'event_index': 1,
  'event_offset': 15124,
  'logical_animation_index': 476,
  'opcode': 105,
  'operation': 'create',
  'pair_index': 418,
  'parent_entries': [128],
  'route_bank': 15,
  'route_entry': 128,
  'route_payload_sha1': 'f66fea8d5739d2e3febe8e840a0b684b09c9b2e1',
  'runtime_table_index': 1,
  'time': 5.0},
 {'action': 47,
  'action_record': {'header_address': '0x80086E34',
                    'header_pin': {'size_bytes': 8, 'sha256': '18cf9ccd236b28f01c2d43b5b2a88452ef9983f597f7a83c1707483b18513cfd'},
                    'records': [{'address': '0x8009D1A0',
                                 'bank': 9,
                                 'entry': 123,
                                 'kind': 1,
                                 'record_pin': {'size_bytes': 16, 'sha256': '3b6d9815f9d8d948b01a0e3d5cc89dffa08e00e9d1c9683323cab71b488c5f61'},
                                 'record_index': 0,
                                 'updater': 0}]},
  'auxiliary_offset': 9060,
  'descriptor_segment_index': 216,
  'event_pin': {'size_bytes': 12, 'sha256': 'beeeff3c1e67611e96b8cfa8ea24f00fe929c331aea72dbddc008e7bdc37ef5d'},
  'event_index': 0,
  'event_offset': 9076,
  'logical_animation_index': 714,
  'opcode': 105,
  'operation': 'create',
  'pair_index': 108,
  'parent_entries': [128],
  'route_bank': 15,
  'route_entry': 128,
  'route_payload_sha1': 'f66fea8d5739d2e3febe8e840a0b684b09c9b2e1',
  'runtime_table_index': 1,
  'time': 24.0}]


# These pins retain exact-record identity without redistributing record payloads.
# Raw fields are accepted only from an in-memory report generated from an owned ROM.
WITNESS_PAYLOAD_FIELDS = ("header_hex", "record_hex", "event_hex")


def normalize_witness_payloads(value):
    """Preserve every semantic field and replace raw payloads before assertions."""
    if isinstance(value, list):
        return [normalize_witness_payloads(item) for item in value]
    if not isinstance(value, dict):
        return value
    normalized = {}
    for key, item in value.items():
        if key in WITNESS_PAYLOAD_FIELDS:
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
            normalized[pin_key] = {
                "size_bytes": len(raw), "sha256": hashlib.sha256(raw).hexdigest()}
        elif key.endswith("_hex"):
            raise ValueError("unreviewed witness payload field")
        else:
            normalized[key] = normalize_witness_payloads(item)
    return normalized


def witness_semantic_leaves(value, path=()):
    """Visit all decoded fields, retaining separate payload and structure checks."""
    if isinstance(value, dict):
        for key, item in value.items():
            if key not in WITNESS_PAYLOAD_FIELDS:
                yield from witness_semantic_leaves(item, path + (key,))
    elif isinstance(value, list):
        for index, item in enumerate(value):
            yield from witness_semantic_leaves(item, path + (index,))
    else:
        yield path, value


def digest(value):
    return hashlib.sha256(json.dumps(value, sort_keys=True, separators=(",", ":")).encode()).hexdigest()


def restore_attachment_corrections(test, canonical):
    """Check exact approved rows before restoring the historical full-file guard."""
    for index, change in CANONICAL_CORRECTIONS.items():
        test.assertEqual(change["after"], canonical["models"][index])
        canonical["models"][index] = copy.deepcopy(change["before"])


class AttachmentPropSemanticNameTests(unittest.TestCase):
    def test_all_170_prior_records_and_branch_are_unchanged(self):
        registry = names.load_registry()
        retained = [r for r in registry["models"]
                    if (r["bank"], r["entry"], r["segment"]) not in ATTACHMENT_PROP_NAMES
                    and (r["bank"], r["entry"], r["segment"]) not in KEY_MODEL_NAMES
                    and (r["bank"], r["entry"], r["segment"]) not in HELD_CHARACTER_NAMES
                    and (r["bank"], r["entry"], r["segment"]) not in REMAINING_SCENE_PROP_NAMES]
        self.assertEqual(170, len(retained))
        self.assertEqual("f197bac435a8b4a529c0fd3dd24cc9036e98a0a3f8b35c7126432717d1798574", digest(retained))
        self.assertEqual([(1, 75, 0)], [(r["bank"], r["entry"], r["segment"])
                         for r in registry["models"] if "model_specific_branch" in r])

    def test_exact_32_records_and_six_conditional_shared_spans(self):
        added = [r for r in names.load_registry()["models"]
                 if (r["bank"], r["entry"], r["segment"]) in ATTACHMENT_PROP_NAMES]
        self.assertEqual(32, len(added))
        self.assertEqual("1b3e60a93724f371137a17ae19564506e0321810add6e7d67a12a483b95bf67b", digest(added))
        self.assertEqual(ATTACHMENT_PROP_NAMES,
                         {(r["bank"], r["entry"], r["segment"]): r["name"] for r in added})
        for r in added:
            self.assertEqual(EXPECTED_CONSUMERS, r["consumers"])
            self.assertNotIn("model_specific_branch", r)
            limits = " ".join(r["limitations"])
            self.assertIn("conditional", limits)
            self.assertIn("caller-dependent", limits)
            self.assertIn("side effects", limits)
            self.assertEqual(r["entry"] in PARTIAL_MATERIAL_ENTRIES,
                             "Current material visibility is partial" in limits)
        self.assertEqual([356, 608, 384, 456, 396, 452],
                         [c["size_bytes"] for c in EXPECTED_CONSUMERS])

    def test_canonical_delta_is_exact_and_preserves_every_prior_field(self):
        canonical = json.loads((names.ROOT / "config/model-inspection.json").read_text())
        for change in CANONICAL_CORRECTIONS.values():
            before, after = change["before"], change["after"]
            self.assertEqual({k:v for k,v in before.items() if k not in {"label", "note", "aliases"}},
                             {k:v for k,v in after.items() if k not in {"label", "note", "aliases"}})
            self.assertTrue(after["note"].startswith(before["note"] + " "))
            self.assertTrue(set(before.get("aliases", [])) <= set(after["aliases"]))
            self.assertIn(before["label"] + " (former label)", after["aliases"])
        restore_remaining_scene_corrections(self, canonical)
        restore_attachment_corrections(self, canonical)
        self.assertEqual("fd274a67cbdbc53c6b7c69995579872c7693209d9ea6df61991b1abbf4feb342", digest(canonical))
        barrel = next(r for r in canonical["models"] if r["name"] == "object-bank03-0076-rom")
        self.assertEqual("Red warning barrel — ROM bank 03 / 0076", barrel["label"])

    def test_action_ids_leads_and_same_bytes_do_not_expand_numeric_identity(self):
        registry = names.load_registry(); payload = b"equal bytes cannot expand model identity"
        for r in registry["models"]:
            r.update(source_bytes=len(payload), model_sha1=hashlib.sha1(payload).hexdigest(),
                     model_sha256=hashlib.sha256(payload).hexdigest())
        for key, label in ATTACHMENT_PROP_NAMES.items():
            self.assertEqual(label, resolve_synthetic_name(registry, "us", registry["rom_sha1"], key, payload)["name"])
            self.assertEqual({"status":"unknown", "name":None}, resolve_synthetic_name(
                registry, "us", registry["rom_sha1"], (9, key[1], 1), payload))
        for key in [(9, 134, 0), (9, 138, 0), (9, 166, 0), (9, 4, 0), (9, 12, 0)]:
            self.assertEqual({"status":"unknown", "name":None},
                             resolve_synthetic_name(registry, "us", registry["rom_sha1"], key, payload))
        self.assertEqual(58, ACTION_PINS[166]["entry"])
        records = {r["entry"]:r for r in registry["models"] if r["bank"] == 9}
        self.assertNotEqual(records[123]["name"], records[124]["name"])

    @unittest.skipUnless((names.ROOT / "roms/baserom.us.z64").is_file(), "owned US ROM unavailable")
    def test_owned_rom_models_and_payload_mutations(self):
        registry = names.load_registry()
        _, _, rom_digest, bundles, _ = models.load_model_bundles("us", names.ROOT / "roms/baserom.us.z64", 9)
        sources = {(9,b.index,s.index):s.data for b in bundles for s in b.segments}
        for key, label in ATTACHMENT_PROP_NAMES.items():
            self.assertEqual(label, names.resolve_name(registry,"us",rom_digest,key,sources[key])["name"])
            changed = bytearray(sources[key]); changed[-1] ^= 1
            with self.assertRaisesRegex(ValueError, "named model source identity changed"):
                names.resolve_name(registry,"us",rom_digest,key,bytes(changed))
        self.assertNotEqual(sources[9,123,0], sources[9,124,0])

    @unittest.skipUnless((names.ROOT / "roms/baserom.us.z64").is_file(), "owned US ROM unavailable")
    def test_all_36_headers_and_records_and_selected_kind_abi(self):
        path, layout = models.resolve_rom("us", names.ROOT / "roms/baserom.us.z64")
        rom, _ = models.normalize_rom(path.read_bytes())
        self.assertEqual(names.load_registry()["rom_sha1"], hashlib.sha1(rom).hexdigest())
        game = models.parse_game_archive(rom[layout["game_start"]:layout["game_end"]])
        self.assertEqual(36,len(ACTION_PINS))
        entries = set(); kinds = {1:0,2:0}
        for action, expected in ACTION_PINS.items():
            address = 0x80086CC4 + (action-1)*8
            self.assertEqual(int(expected["header_address"],16),address)
            start = address-layout["game_data_vram"]; header = game.data[start:start+8]
            self.assertEqual(expected["header_hashes"],dict(sha1=hashlib.sha1(header).hexdigest(),sha256=hashlib.sha256(header).hexdigest()))
            pointer, count = struct.unpack(">IB3x",header)
            self.assertEqual(1,count); self.assertEqual(int(expected["record_address"],16),pointer)
            start = pointer-layout["game_data_vram"]; record = game.data[start:start+16]
            self.assertEqual(expected["record_hashes"],dict(sha1=hashlib.sha1(record).hexdigest(),sha256=hashlib.sha256(record).hexdigest()))
            self.assertIn(record[3],(1,2))  # Kind0 byte0 has a separate ABI.
            self.assertEqual((expected["entry"],expected["kind"],expected["updater_selector"],expected["flags"]),
                             (record[0],record[3],record[2],record[7]))
            self.assertEqual(expected["animation_selector"],record[6] if record[3]==2 else -1)
            entries.add(record[0]); kinds[record[3]] += 1
        self.assertEqual({k[1] for k in ATTACHMENT_PROP_NAMES},entries)
        self.assertEqual({1:34,2:2},kinds)
        self.assertEqual([(43,131,0),(51,139,11)],[(a,p["entry"],p["animation_selector"]) for a,p in ACTION_PINS.items() if p["kind"]==2])

    @unittest.skipUnless((names.ROOT / "roms/baserom.us.z64").is_file(), "owned US ROM unavailable")
    def test_stored_create_event_witnesses_are_exact_and_bounded(self):
        path, layout = models.resolve_rom("us", names.ROOT / "roms/baserom.us.z64")
        rom, _ = models.normalize_rom(path.read_bytes())
        game = models.parse_game_archive(rom[layout["game_start"]:layout["game_end"]])
        report = normalize_witness_payloads(events.report(models,rom,layout,game))
        self.assertEqual(EVENT_COUNTS,report["counts"])
        selected = [e for e in report["events"] if e["operation"]=="create" and e["action"] in ACTION_PINS]
        self.assertEqual(CREATE_WITNESSES,selected)
        self.assertEqual([16,21,22,32,43,47,86,88,100,108],sorted({e["action"] for e in selected}))
        # Independently slice owned-ROM headers, action records and route events.
        # No raw payload is passed to an assertion or saved as an expected fixture.
        banks = {b.index: b for b in models.parse_asset_banks(rom, layout["asset_table"])}
        route_entries = {e.index: e for e in models.parse_asset_entries(rom, banks[15])}
        route_payloads = {}
        for witness in CREATE_WITNESSES:
            action = witness["action_record"]
            header_offset = int(action["header_address"], 16) - layout["game_data_vram"]
            header = game.data[header_offset:header_offset + 8]
            self.assert_payload_pin(action["header_pin"], header, "header")
            pointer, count = struct.unpack(">IB3x", header)
            self.assertEqual(len(action["records"]), count)
            for record in action["records"]:
                address = pointer + record["record_index"] * 16
                self.assertEqual(int(record["address"], 16), address)
                offset = address - layout["game_data_vram"]
                raw = game.data[offset:offset + 16]
                self.assert_payload_pin(record["record_pin"], raw, "record")
                self.assertEqual((record["entry"], record["updater"], record["kind"]),
                                 (raw[0], raw[2], raw[3]))
            entry_index = witness["route_entry"]
            if entry_index not in route_payloads:
                entry = route_entries[entry_index]
                raw = rom[entry.start:entry.end]
                route_payloads[entry_index] = models.decode_rzip_chunk(raw).data if entry.compressed else raw
            payload = route_payloads[entry_index]
            self.assertEqual(witness["route_payload_sha1"], hashlib.sha1(payload).hexdigest())
            offset = witness["event_offset"]
            raw = payload[offset:offset + 12]
            self.assert_payload_pin(witness["event_pin"], raw, "event")
            time, command, argument = struct.unpack(">fII", raw)
            self.assertEqual((witness["time"], witness["opcode"], witness["action"]),
                             (time, command & 255, argument))

    def assert_payload_pin(self, pin, raw, label):
        self.assertEqual(pin["size_bytes"], len(raw), label + " length changed")
        self.assertEqual(pin["sha256"], hashlib.sha256(raw).hexdigest(),
                         label + " SHA-256 changed")

    def assert_create_witnesses(self, actual):
        self.assertEqual(CREATE_WITNESSES, normalize_witness_payloads(actual),
                         "stored create witnesses changed")

    def test_witness_normalization_preserves_synthetic_fields_and_rejects_unsafe_shapes(self):
        raw = bytes(range(12))  # Synthetic, not an original-record fixture.
        row = {"event_hex": raw.hex(), "action": 7, "nested": [{"kind": 1}]}
        expected = {"event_pin": {"size_bytes": 12, "sha256": hashlib.sha256(raw).hexdigest()},
                    "action": 7, "nested": [{"kind": 1}]}
        self.assertEqual(expected, normalize_witness_payloads(row))
        for value in (None, 7, "not hexadecimal", raw.hex().upper(), raw.hex() + " "):
            with self.subTest(case="encoding"), self.assertRaisesRegex(ValueError, "invalid witness payload encoding"):
                normalize_witness_payloads({"event_hex": value})
        with self.assertRaisesRegex(ValueError, "conflicting witness payload pin"):
            normalize_witness_payloads({"event_hex": raw.hex(), "event_pin": {}})
        with self.assertRaisesRegex(ValueError, "unreviewed witness payload field"):
            normalize_witness_payloads({"unreviewed_hex": raw.hex()})

    @unittest.skipUnless((names.ROOT / "roms/baserom.us.z64").is_file(), "owned US ROM unavailable")
    def test_owned_witness_positives_precede_payload_semantic_and_scope_rejections(self):
        path, layout = models.resolve_rom("us", names.ROOT / "roms/baserom.us.z64")
        rom, _ = models.normalize_rom(path.read_bytes())
        game = models.parse_game_archive(rom[layout["game_start"]:layout["game_end"]])
        # Keep actual bytes only in memory for mutations; assertions normalize first.
        actual = [e for e in events.report(models, rom, layout, game)["events"]
                  if e["operation"] == "create" and e["action"] in ACTION_PINS]
        self.assert_create_witnesses(actual)
        payload_paths = (("event_hex",), ("action_record", "header_hex"),
                         ("action_record", "records", 0, "record_hex"))
        for index, witness in enumerate(actual):
            for path in payload_paths:
                row = witness
                for key in path[:-1]:
                    row = row[key]
                raw = bytes.fromhex(row[path[-1]])
                for offset in range(len(raw)):
                    changed = copy.deepcopy(actual)
                    target = changed[index]
                    for key in path[:-1]:
                        target = target[key]
                    bad = bytearray(raw); bad[offset] ^= 1
                    target[path[-1]] = bad.hex()
                    with self.subTest(witness=index, field=path[-1], byte=offset), self.assertRaisesRegex(
                            AssertionError, "stored create witnesses changed"):
                        self.assert_create_witnesses(changed)
                changed = copy.deepcopy(actual)
                target = changed[index]
                for key in path[:-1]:
                    target = target[key]
                target[path[-1]] = raw[:-1].hex()
                with self.subTest(witness=index, field=path[-1], case="length"), self.assertRaisesRegex(
                        AssertionError, "stored create witnesses changed"):
                    self.assert_create_witnesses(changed)
            for path, value in witness_semantic_leaves(witness):
                changed = copy.deepcopy(actual)
                target = changed[index]
                for key in path[:-1]:
                    target = target[key]
                target[path[-1]] = value + 1 if isinstance(value, (int, float)) else value + " changed"
                with self.subTest(witness=index, field=path), self.assertRaisesRegex(
                        AssertionError, "stored create witnesses changed"):
                    self.assert_create_witnesses(changed)
        for changed in (actual[:-1], actual + [actual[0]], list(reversed(actual))):
            with self.subTest(case="scope"), self.assertRaisesRegex(AssertionError, "stored create witnesses changed"):
                self.assert_create_witnesses(changed)


if __name__ == "__main__":
    unittest.main()
