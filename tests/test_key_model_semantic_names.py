"""Exact stored text-entry keys, complete consumer spans and additive-only naming."""
import copy
import hashlib
import json
import struct
import unittest
from test_model_name_confidence import resolve_synthetic_name

from scripts import model_assets as models, model_semantic_names as names
from test_held_character_semantic_names import HELD_CHARACTER_NAMES
from test_remaining_scene_prop_semantic_names import (REMAINING_SCENE_PROP_NAMES,
    restore_remaining_scene_corrections, historical_canonical_bytes)

KEY_MODEL_NAMES = {(9, 453, 0): 'Letter block A',
 (9, 454, 0): 'Letter block B',
 (9, 455, 0): 'Letter block C',
 (9, 456, 0): 'Letter block D',
 (9, 457, 0): 'Letter block E',
 (9, 458, 0): 'Letter block F',
 (9, 459, 0): 'Letter block G',
 (9, 460, 0): 'Letter block H',
 (9, 461, 0): 'Letter block I',
 (9, 462, 0): 'Letter block J',
 (9, 463, 0): 'Letter block K',
 (9, 464, 0): 'Letter block L',
 (9, 465, 0): 'Letter block M',
 (9, 466, 0): 'Letter block N',
 (9, 467, 0): 'Letter block O',
 (9, 468, 0): 'Letter block P',
 (9, 469, 0): 'Letter block Q',
 (9, 470, 0): 'Letter block R',
 (9, 471, 0): 'Letter block S',
 (9, 472, 0): 'Letter block T',
 (9, 473, 0): 'Letter block U',
 (9, 474, 0): 'Letter block V',
 (9, 475, 0): 'Letter block W',
 (9, 476, 0): 'Letter block X',
 (9, 477, 0): 'DEL key block',
 (9, 478, 0): 'Dot key block',
 (9, 479, 0): 'Letter block Y',
 (9, 480, 0): 'Letter block Z',
 (9, 481, 0): 'Return key block',
 (9, 482, 0): 'Long blank key block'}

EXPECTED_CONSUMERS = [{'role': 'shared text-entry initializer: conditionally allocate the owner, request bank-09 entries '
          '453..482 in thirty 12-byte records, resolve primary display lists and rewrite their vertex '
          'colors, combiner and OtherMode',
  'sha1': '3b13bb43cb9cbd47806192f7f91164293859bb77',
  'size_bytes': 568,
  'symbol': 'func_151EDF4C',
  'vram': '0x151EDF4C'},
 {'role': 'shared text-entry update/draw consumer: map selected resource slots to character, delete or '
          'submit actions, evaluate submissions, and emit all thirty primary display lists with '
          'selected-key state',
  'sha1': '4465f83e60f35bd1eafcc03650ee0f725f1adb32',
  'size_bytes': 2660,
  'symbol': 'func_151EE184',
  'vram': '0x151EE184'}]

MODEL_PINS = {453: {'display_list_sha256': '1b8d8410976a5373077f3cae58cae4289094ea18f11f6e0d24cf0781fd8a0d24',
       'faces': 10,
       'header': {'primary_list_bytes': 208,
                  'primary_list_offset': 232,
                  'sha256': '6512e0db017e0560801031f5fa0dcd1e16457eaa767f3fd0c455599e3408c8e6',
                  'size': 40},
       'source_payload': {'bytes': 440,
                          'sha1': '5a25bee15c7ce6ba4a89b69987bd2bd4412ed606',
                          'sha256': 'f94db7a7d00b026452642f29b4fdbb74f712c232e80fa6378e246800b9693328'},
       'vertex_bytes_sha256': 'ae7966c646947864682dc40156972f3dc2160456bf514b20c078c43c643f8b5b',
       'vertices': 12},
 454: {'display_list_sha256': '2f634ea1d0a375c8a981fc79a2a8f07201823487fdbdc5f40d9be26d292ed36f',
       'faces': 10,
       'header': {'primary_list_bytes': 208,
                  'primary_list_offset': 232,
                  'sha256': '6512e0db017e0560801031f5fa0dcd1e16457eaa767f3fd0c455599e3408c8e6',
                  'size': 40},
       'source_payload': {'bytes': 440,
                          'sha1': 'abbafeb2f943a276d76e9568402c28d2a6dcca3d',
                          'sha256': '595954cadc2dd87816d0d5c00c38bc48546ae24255e3c6879171f34d6661bf6f'},
       'vertex_bytes_sha256': '9acc65280af5d48785d1ae7e41289351d191d22c761fdc0ce2cbec2747d2cfe7',
       'vertices': 12},
 455: {'display_list_sha256': 'eff260749974e5a6437a045208d090ce55493e086372df916e818952604c9ed6',
       'faces': 10,
       'header': {'primary_list_bytes': 208,
                  'primary_list_offset': 232,
                  'sha256': '6512e0db017e0560801031f5fa0dcd1e16457eaa767f3fd0c455599e3408c8e6',
                  'size': 40},
       'source_payload': {'bytes': 440,
                          'sha1': 'ddeff0e33db57ebfff7df1fe2e2b0e6a5d1681c5',
                          'sha256': '0c5114bd0b4f2d51b25f05aff0ca64cd46b8360e756baa2cce38e518024bb6d4'},
       'vertex_bytes_sha256': '00f016d40e81e3121e6c4a26d6860315084ce0c61161956cf615510bd215ed73',
       'vertices': 12},
 456: {'display_list_sha256': '803a402007b02455b9764271fc90657f5a7fabba591ef38037fe4ca359288fb8',
       'faces': 10,
       'header': {'primary_list_bytes': 208,
                  'primary_list_offset': 232,
                  'sha256': '6512e0db017e0560801031f5fa0dcd1e16457eaa767f3fd0c455599e3408c8e6',
                  'size': 40},
       'source_payload': {'bytes': 440,
                          'sha1': '4a3bc742d1fe54dd9df913041e0aee272c4d6d6f',
                          'sha256': 'abfbb5fc73f949c3206e93ad8b05ef16c8d6bd2371a9fac3794422c75687ce13'},
       'vertex_bytes_sha256': 'b901d7cb0208c8df909c8abd08cd3f22b69376c66fab22f60cde24683e62e13a',
       'vertices': 12},
 457: {'display_list_sha256': 'ebe0d8fad8ed679f3863683ebf5db8c17831919341a9f5aa4c74f46a1b73870d',
       'faces': 10,
       'header': {'primary_list_bytes': 208,
                  'primary_list_offset': 232,
                  'sha256': '6512e0db017e0560801031f5fa0dcd1e16457eaa767f3fd0c455599e3408c8e6',
                  'size': 40},
       'source_payload': {'bytes': 440,
                          'sha1': '8770e79a6372e510c9a581735311c1ebfb110fdb',
                          'sha256': 'ebe5555ee2bf2d31eaca5ca4b7caa7c5f5d0196ab2a41329aefcae239b6dc04d'},
       'vertex_bytes_sha256': 'c31441abdce220d09860db8486f4033f0b93556688920b74868ca1a190b6010f',
       'vertices': 12},
 458: {'display_list_sha256': '66434fa1268480d6220b92ad0e641045f700f7506f4e3658badb65b078128c34',
       'faces': 10,
       'header': {'primary_list_bytes': 208,
                  'primary_list_offset': 232,
                  'sha256': '6512e0db017e0560801031f5fa0dcd1e16457eaa767f3fd0c455599e3408c8e6',
                  'size': 40},
       'source_payload': {'bytes': 440,
                          'sha1': '0969209ae38985560f8bb4189562f1513ba8e0dc',
                          'sha256': '5b0e14df82177d924c4cdd8e715ac1c69140cc56d8be0910c88bd400e01cbbde'},
       'vertex_bytes_sha256': '947ae4307cb3f76e9b767d6dfdf835d07b2dd41f73b02132a92ca37cde1b3d24',
       'vertices': 12},
 459: {'display_list_sha256': '74026d945e09087b3c39bedf59e67290b9a66e2ba07a752e63160614d6f56171',
       'faces': 10,
       'header': {'primary_list_bytes': 208,
                  'primary_list_offset': 232,
                  'sha256': '6512e0db017e0560801031f5fa0dcd1e16457eaa767f3fd0c455599e3408c8e6',
                  'size': 40},
       'source_payload': {'bytes': 440,
                          'sha1': '709345b79e78670cc8373e42c1db2422d06c9839',
                          'sha256': '7be6a15ddb39f54fb03250140851fd4007c87446638bbb4503d75f7646370b55'},
       'vertex_bytes_sha256': '93f5f849f598ef137481828dae82881d9456258ee0cb000b60a0060dd98ce248',
       'vertices': 12},
 460: {'display_list_sha256': '06a874189ae27cee1fe0110e3211f83aff21c701d5d02c888edab4557b513025',
       'faces': 10,
       'header': {'primary_list_bytes': 208,
                  'primary_list_offset': 232,
                  'sha256': '6512e0db017e0560801031f5fa0dcd1e16457eaa767f3fd0c455599e3408c8e6',
                  'size': 40},
       'source_payload': {'bytes': 440,
                          'sha1': 'c347da71f2108f1674f2bea7b7bd55b7ea78704c',
                          'sha256': '6467f03a8188bdd0f7cb2bd9a0343482e0f84d7a05a78380fe9a657fae0810bf'},
       'vertex_bytes_sha256': '7cc992df126a61e4b121f34e99b2b012d5b57fedaaec88f2a57e52953ead8059',
       'vertices': 12},
 461: {'display_list_sha256': '3a5cf9f4107644afe3754b06e57b5c75a496880649a8fa5eefd11acf0a9b87a2',
       'faces': 10,
       'header': {'primary_list_bytes': 208,
                  'primary_list_offset': 232,
                  'sha256': '6512e0db017e0560801031f5fa0dcd1e16457eaa767f3fd0c455599e3408c8e6',
                  'size': 40},
       'source_payload': {'bytes': 440,
                          'sha1': 'c12e48702bb7faf9b3adaf1aef234aa398b696ba',
                          'sha256': 'ea2c86b711a1a9aa0b67d5f09bd5898edcc77774249bd1a75db484f85b3e6e3a'},
       'vertex_bytes_sha256': '38cfef57b88a5adbc9b9cc66b0734153158f0080b2973a3ef6f9870da0a0e861',
       'vertices': 12},
 462: {'display_list_sha256': 'e722cc726a1c7d24bcebc7fade2410160f29e06092d1ab845dab6748eda3355c',
       'faces': 10,
       'header': {'primary_list_bytes': 208,
                  'primary_list_offset': 232,
                  'sha256': '6512e0db017e0560801031f5fa0dcd1e16457eaa767f3fd0c455599e3408c8e6',
                  'size': 40},
       'source_payload': {'bytes': 440,
                          'sha1': '56b230c4d5790c42e71ec616d12f1e266b26e0dd',
                          'sha256': '20bfbc64c40030c45aa4bf5cc6cc2f07290c0fce048f8347dd3575033389a573'},
       'vertex_bytes_sha256': '5c5f9143257281991e84f71c4338599525e17c444d8942cfbe8f17e36f27da21',
       'vertices': 12},
 463: {'display_list_sha256': 'a7b32046a8d06882f8f89bf323605e6076851351721ed9d7ef94003db63f695c',
       'faces': 10,
       'header': {'primary_list_bytes': 208,
                  'primary_list_offset': 232,
                  'sha256': '6512e0db017e0560801031f5fa0dcd1e16457eaa767f3fd0c455599e3408c8e6',
                  'size': 40},
       'source_payload': {'bytes': 440,
                          'sha1': '87c05d4fa6a723ed7c6090064fcfd8f478562393',
                          'sha256': '9c67ea1f9fec8b90b46b5fe609cf849b5d02be3b38a89478ccbbd6348bc6a444'},
       'vertex_bytes_sha256': 'ecbe6eb7c302e996fc935f39bcac9ead6da8212b6af2637597afbda893d974c0',
       'vertices': 12},
 464: {'display_list_sha256': '8e78e01199f19db0dfe59e3ca14e542a6ccc0cbae3fc1da5e7fa2b121f2adfd5',
       'faces': 10,
       'header': {'primary_list_bytes': 208,
                  'primary_list_offset': 232,
                  'sha256': '6512e0db017e0560801031f5fa0dcd1e16457eaa767f3fd0c455599e3408c8e6',
                  'size': 40},
       'source_payload': {'bytes': 440,
                          'sha1': '3977972adddbfb81377818b17c04548976a4578a',
                          'sha256': 'df2aaaba6600bcbb7bef6f041c245b476c7699f7e9a3b1869b8a2ae0e50296c7'},
       'vertex_bytes_sha256': 'f5d8701a18127c55705c51a1d7a9ef8de7eae38bf3632da9780e28aadb682866',
       'vertices': 12},
 465: {'display_list_sha256': '4b9849ac29d2729a98b7a471e1d5ac15b0aaf3f3bd1c9bb640a60e06378374ae',
       'faces': 10,
       'header': {'primary_list_bytes': 208,
                  'primary_list_offset': 232,
                  'sha256': '6512e0db017e0560801031f5fa0dcd1e16457eaa767f3fd0c455599e3408c8e6',
                  'size': 40},
       'source_payload': {'bytes': 440,
                          'sha1': '4500057942604e8bf5e5c8213fd459eca0e4cbb8',
                          'sha256': '89eef1c41cd78839bafed95e1f19c62653aa587bc83863b751984899b55e7b60'},
       'vertex_bytes_sha256': '60795ed849dc7dc3d3cb51d65dcd59c0ea8df9e689046accaea276373ee0c0db',
       'vertices': 12},
 466: {'display_list_sha256': 'c8c1d20c29487727fa6a18eed0e6c6167297cc7b603fb0c5df494a7debc6fad9',
       'faces': 10,
       'header': {'primary_list_bytes': 208,
                  'primary_list_offset': 232,
                  'sha256': '6512e0db017e0560801031f5fa0dcd1e16457eaa767f3fd0c455599e3408c8e6',
                  'size': 40},
       'source_payload': {'bytes': 440,
                          'sha1': '8dd8374f274a9cc71649822ba46b3b4dad6d3ec0',
                          'sha256': '7666ab8f47a9430ba736f56005f399e792b2ee18b5515c924cc849030440afb3'},
       'vertex_bytes_sha256': '4112cd294c0268fb3dd4e379b5ba14b28a3201a74bac9d1e6714a80e62f05b45',
       'vertices': 12},
 467: {'display_list_sha256': 'dfbf95abbdb8516525983822b036f11acdb8440a05ee83ad1e8557b623c23746',
       'faces': 10,
       'header': {'primary_list_bytes': 208,
                  'primary_list_offset': 232,
                  'sha256': '6512e0db017e0560801031f5fa0dcd1e16457eaa767f3fd0c455599e3408c8e6',
                  'size': 40},
       'source_payload': {'bytes': 440,
                          'sha1': '533e5032e911aa0da00440ff7528fac609afbd29',
                          'sha256': '860536ecb93bc548754d055adc317201b9e928dbac51d50e088a114c68fa4883'},
       'vertex_bytes_sha256': 'b56d4055425552a34257a2c486c8853d54c23c752e651722d80f5c1599dd79a9',
       'vertices': 12},
 468: {'display_list_sha256': '9ef8a0b0f560bdee74e54b287eac1a09b5cdcb87d04156bdd04122ac3c414293',
       'faces': 10,
       'header': {'primary_list_bytes': 208,
                  'primary_list_offset': 232,
                  'sha256': '6512e0db017e0560801031f5fa0dcd1e16457eaa767f3fd0c455599e3408c8e6',
                  'size': 40},
       'source_payload': {'bytes': 440,
                          'sha1': 'e32ef03385ad31605d29f261f692df898c5877bc',
                          'sha256': '1a84f3e8e3ba56e075734e88448cfc6326b9bdfea2584d5d268b9b7d375f2e2a'},
       'vertex_bytes_sha256': '418b451200dd93eab2ed08a02b7bb1cb71fba832efd126c05e49ca1576fdffbe',
       'vertices': 12},
 469: {'display_list_sha256': 'ebdea6984b9613d1ec688e4cfd0a808953d38eb730b2ef0e95a6f8c5358a85a3',
       'faces': 10,
       'header': {'primary_list_bytes': 208,
                  'primary_list_offset': 232,
                  'sha256': '6512e0db017e0560801031f5fa0dcd1e16457eaa767f3fd0c455599e3408c8e6',
                  'size': 40},
       'source_payload': {'bytes': 440,
                          'sha1': '7770eace9e59e0e55d3797cf41f2746d5613f2f4',
                          'sha256': '66648b4bd096ecb69c6e7cefe0135778b18d04789926e89319eb500ef923ba5d'},
       'vertex_bytes_sha256': 'cd45a81624d0248289f818c3f676aa15bb36115a5655389d34e9943687b12570',
       'vertices': 12},
 470: {'display_list_sha256': '74d905239d7660b94dfeb8cbd5e1ea593bbf3a96460ffdf29484487bbe38b202',
       'faces': 10,
       'header': {'primary_list_bytes': 208,
                  'primary_list_offset': 232,
                  'sha256': '6512e0db017e0560801031f5fa0dcd1e16457eaa767f3fd0c455599e3408c8e6',
                  'size': 40},
       'source_payload': {'bytes': 440,
                          'sha1': '40664151fd7f0e2d0886f80795404177bd7c0032',
                          'sha256': '65fbf141560392320ea20996353acf3cb49e8eef4797ca4dff1669b9d608f4b7'},
       'vertex_bytes_sha256': '717cd6fcdbdbb783b7339ebd8ab21660cf576a7cf1e6d5c7cf4772a535866d39',
       'vertices': 12},
 471: {'display_list_sha256': 'af40adce6c915fccfa836f95853894b9a7f7b28bd75ae55c4e25cda4753611ac',
       'faces': 10,
       'header': {'primary_list_bytes': 208,
                  'primary_list_offset': 232,
                  'sha256': '6512e0db017e0560801031f5fa0dcd1e16457eaa767f3fd0c455599e3408c8e6',
                  'size': 40},
       'source_payload': {'bytes': 440,
                          'sha1': '50a6ae5352bc4fd8990eb857b294d21c11f37dca',
                          'sha256': '802293932a1028b99e491f1a264b827a348330baee70681ba410ae6dd248ca9f'},
       'vertex_bytes_sha256': 'be5ab498f135b20d120c434951ce7758c50c4ccdbd8943583914c9d746883099',
       'vertices': 12},
 472: {'display_list_sha256': '8797f0b4a901219a6655f05e20c895d72c8dde52687df4341656662c445a4298',
       'faces': 10,
       'header': {'primary_list_bytes': 208,
                  'primary_list_offset': 232,
                  'sha256': '6512e0db017e0560801031f5fa0dcd1e16457eaa767f3fd0c455599e3408c8e6',
                  'size': 40},
       'source_payload': {'bytes': 440,
                          'sha1': 'eb75c5d0ae7ed5b902c73808ee76712a942d21bb',
                          'sha256': 'b9ec533a0d3c807e8a2da2e8d00313bfc15cb47da41c12d50971b2ef2a496258'},
       'vertex_bytes_sha256': '90131e63c2656f5dbc57696b733ca58a5e15df55ea39724dc8b3f306580350bc',
       'vertices': 12},
 473: {'display_list_sha256': 'df56e427865714396ea905d73d66fa96b0f762fad36bca2dbf96f2c97655815b',
       'faces': 10,
       'header': {'primary_list_bytes': 208,
                  'primary_list_offset': 232,
                  'sha256': '6512e0db017e0560801031f5fa0dcd1e16457eaa767f3fd0c455599e3408c8e6',
                  'size': 40},
       'source_payload': {'bytes': 440,
                          'sha1': '33104d4f442536334501c4bc803c807c7e5dea58',
                          'sha256': '09d406b9418a034fed78cbb034ff4d56549de6f203a052fb4f6829aace0de7f3'},
       'vertex_bytes_sha256': '167d681d7bd6041b1baf8a5361494e2129acac3202d599749594dc150b43412e',
       'vertices': 12},
 474: {'display_list_sha256': '6a0873ee7bcc0c98f4000a70830e013c1782f3245ea2e13a8296bbbfd40915eb',
       'faces': 10,
       'header': {'primary_list_bytes': 208,
                  'primary_list_offset': 232,
                  'sha256': '6512e0db017e0560801031f5fa0dcd1e16457eaa767f3fd0c455599e3408c8e6',
                  'size': 40},
       'source_payload': {'bytes': 440,
                          'sha1': 'abc77be2bbfcc5538dca04e5a02ff6204a62f4c9',
                          'sha256': '56dce205aa6c7b41ed610234bde329391195ba7e4b83370f7980624cac79caff'},
       'vertex_bytes_sha256': '27368883866014899a17915962081d1d167c4d8ff50061d7037468faaff3494d',
       'vertices': 12},
 475: {'display_list_sha256': 'eed0cd34e95c8b37acbe42bf3341353a93ac3c5a645e487c04e6e0a83e9d097f',
       'faces': 10,
       'header': {'primary_list_bytes': 208,
                  'primary_list_offset': 232,
                  'sha256': '6512e0db017e0560801031f5fa0dcd1e16457eaa767f3fd0c455599e3408c8e6',
                  'size': 40},
       'source_payload': {'bytes': 440,
                          'sha1': 'ffb81d608d88be418d89e2bafc1a389cefbbb999',
                          'sha256': 'fba1bcbb84dda51d4b0c1e449c74635d288e486aeae8e78027784be25fdb75f5'},
       'vertex_bytes_sha256': 'e4987eb499f2b8e308351c00a34e2053fc036b70ae97f578657c6df144cc0dd7',
       'vertices': 12},
 476: {'display_list_sha256': 'bccbba8817e091badaa5a46d762ffd6b97072484f1f1d1c39f91652b52620ced',
       'faces': 10,
       'header': {'primary_list_bytes': 208,
                  'primary_list_offset': 232,
                  'sha256': '6512e0db017e0560801031f5fa0dcd1e16457eaa767f3fd0c455599e3408c8e6',
                  'size': 40},
       'source_payload': {'bytes': 440,
                          'sha1': '37bbcbe9fa3000b6cfcd6b8683147182bae4973d',
                          'sha256': '8d6d12b090542d5b3bd3d2694434c3c533045e3ca730a2c144f281d85fb2eb42'},
       'vertex_bytes_sha256': '7a9fc7b4e63f16870ec9835c21581ee26bd172a1b9717309757394e106a6a4d1',
       'vertices': 12},
 477: {'display_list_sha256': '610b094e153800168f7540717be5b0c3888754af6b7dcac17d19db96a7da23fc',
       'faces': 10,
       'header': {'primary_list_bytes': 208,
                  'primary_list_offset': 232,
                  'sha256': '6512e0db017e0560801031f5fa0dcd1e16457eaa767f3fd0c455599e3408c8e6',
                  'size': 40},
       'source_payload': {'bytes': 440,
                          'sha1': '022d08efd8b6fde9489d754b837a12a267119f84',
                          'sha256': '9530cf2fafce778e887ce4d1cd9d6e1f976f1e701677b5e2390c058d2d885839'},
       'vertex_bytes_sha256': 'b43a81fcfc3baa8d9df5acf547666adaafa630e62f1307dd157c0b52bedf275c',
       'vertices': 12},
 478: {'display_list_sha256': 'e0244c3eb4f5b107d411783c0c67b308a1de5ebd9d95f3988ca5faae6ce3575f',
       'faces': 10,
       'header': {'primary_list_bytes': 208,
                  'primary_list_offset': 232,
                  'sha256': '6512e0db017e0560801031f5fa0dcd1e16457eaa767f3fd0c455599e3408c8e6',
                  'size': 40},
       'source_payload': {'bytes': 440,
                          'sha1': '0a49c4ae32e8971004c065ef79ca1fa9b70e65e9',
                          'sha256': 'c428949c25c8097260f263ce33e687063dd058d8793c5ad64d61515a226928aa'},
       'vertex_bytes_sha256': '6f6ad4e1db260f8f616b62316ccc045bc1836e6f3a11d2a810732555b398de7b',
       'vertices': 12},
 479: {'display_list_sha256': '9dc5a1bd01cde2caa6194755344c533ca1b698a169c8b36f02392205878408c2',
       'faces': 10,
       'header': {'primary_list_bytes': 208,
                  'primary_list_offset': 232,
                  'sha256': '6512e0db017e0560801031f5fa0dcd1e16457eaa767f3fd0c455599e3408c8e6',
                  'size': 40},
       'source_payload': {'bytes': 440,
                          'sha1': '352dd0ededceb8c4ca700ff369a267546901dfd6',
                          'sha256': '7a7967573b34d38998bb1ee01c20ecccc09eb6ca8ac1e66f8e5bb7bb408b0cda'},
       'vertex_bytes_sha256': 'f13ead401e1daf028fb72ce451a6d8003d748c36b63eabbf6710cc2997b014ed',
       'vertices': 12},
 480: {'display_list_sha256': '9ce51cb9e85e1cca39b228f72afeec7bc1b9c0e16d30462dbaccc62477aa514b',
       'faces': 10,
       'header': {'primary_list_bytes': 208,
                  'primary_list_offset': 232,
                  'sha256': '6512e0db017e0560801031f5fa0dcd1e16457eaa767f3fd0c455599e3408c8e6',
                  'size': 40},
       'source_payload': {'bytes': 440,
                          'sha1': '0ddabd3d7f5dc53ed3540e5b0a7c57d3037fb9e7',
                          'sha256': '5d7a2b949c96700647119c91de659c942a8be0374b6a9d4631ca83dbab4935b1'},
       'vertex_bytes_sha256': 'ba2e876a144f0f26fd0f068ef086565e59de935e6ea04affa89ff61157f7f9ba',
       'vertices': 12},
 481: {'display_list_sha256': '318b50c479ba8c2c4ae657bde543d27d737d0bf54d2bb68d6e325236829d708d',
       'faces': 10,
       'header': {'primary_list_bytes': 224,
                  'primary_list_offset': 232,
                  'sha256': '41b5875ea4d5cab851f5b233c072c197faff7d101393a98882e48701ac1ece1b',
                  'size': 40},
       'source_payload': {'bytes': 456,
                          'sha1': 'a01289be931f15023f74af5ddc18239f051a5e9f',
                          'sha256': 'b1e8946403fae2063c69c98013c6b7d7cd9614422ff7af46d3fa1716d26e4467'},
       'vertex_bytes_sha256': 'be7a69d33b450458bf61a8724e31366d780955c9a00ab37cbbfe894f0ab8acae',
       'vertices': 12},
 482: {'display_list_sha256': 'beeb0a854affcd0adf887cad96f10325214027ab5ce2e224ec967d930e8933ba',
       'faces': 10,
       'header': {'primary_list_bytes': 224,
                  'primary_list_offset': 264,
                  'sha256': '0f37f47ac2d5611180527102a7622675f83642c13db7f065b4b0c5960cc57e69',
                  'size': 40},
       'source_payload': {'bytes': 488,
                          'sha1': '8cdbb291c825f023c2284b49103c66f5c25b22c8',
                          'sha256': 'b7633728f0fc1ab193382b4f9affadaae3688ef6c270a17ae14538ea88270fd6'},
       'vertex_bytes_sha256': 'd5f34e1df15a94691c19655ff86450c946bb9368b075128d394dfb0ee882a9b3',
       'vertices': 14}}

SOURCE_JOINS = {453: {'canonical_pointer': 'models/689',
       'canonical_record': {'category': 'scene-items',
                            'label': 'Letter block A — ROM 09 / 0453 / 00',
                            'name': 'object-bank09-0453-00-rom',
                            'note': 'Geometry and textures extracted directly from the ROM. Descriptive '
                                    'label from the exported geometry; no recovered source name is '
                                    'claimed. Native lighting, dynamic material state and complete '
                                    'appearance remain unverified. No capture inputs.',
                            'render_case': 'object-bank09-0453-00-rom'},
       'validation_pointer': 'render_cases/713',
       'validation_record': {'id': 'object-bank09-0453-00-rom',
                             'reference': 'build/assets/models/validation/baselines/object-bank09-0453-00-rom.png',
                             'size': 512,
                             'source': 'build/assets/models/rom-only/us-bank-09-preview/geometry/0453-00.gltf'}},
 454: {'canonical_pointer': 'models/690',
       'canonical_record': {'category': 'scene-items',
                            'label': 'Letter block B — ROM 09 / 0454 / 00',
                            'name': 'object-bank09-0454-00-rom',
                            'note': 'Geometry and textures extracted directly from the ROM. Descriptive '
                                    'label from the exported geometry; no recovered source name is '
                                    'claimed. Native lighting, dynamic material state and complete '
                                    'appearance remain unverified. No capture inputs.',
                            'render_case': 'object-bank09-0454-00-rom'},
       'validation_pointer': 'render_cases/714',
       'validation_record': {'id': 'object-bank09-0454-00-rom',
                             'reference': 'build/assets/models/validation/baselines/object-bank09-0454-00-rom.png',
                             'size': 512,
                             'source': 'build/assets/models/rom-only/us-bank-09-preview/geometry/0454-00.gltf'}},
 455: {'canonical_pointer': 'models/691',
       'canonical_record': {'category': 'scene-items',
                            'label': 'Letter block C — ROM 09 / 0455 / 00',
                            'name': 'object-bank09-0455-00-rom',
                            'note': 'Geometry and textures extracted directly from the ROM. Descriptive '
                                    'label from the exported geometry; no recovered source name is '
                                    'claimed. Native lighting, dynamic material state and complete '
                                    'appearance remain unverified. No capture inputs.',
                            'render_case': 'object-bank09-0455-00-rom'},
       'validation_pointer': 'render_cases/715',
       'validation_record': {'id': 'object-bank09-0455-00-rom',
                             'reference': 'build/assets/models/validation/baselines/object-bank09-0455-00-rom.png',
                             'size': 512,
                             'source': 'build/assets/models/rom-only/us-bank-09-preview/geometry/0455-00.gltf'}},
 456: {'canonical_pointer': 'models/692',
       'canonical_record': {'category': 'scene-items',
                            'label': 'Letter block D — ROM 09 / 0456 / 00',
                            'name': 'object-bank09-0456-00-rom',
                            'note': 'Geometry and textures extracted directly from the ROM. Descriptive '
                                    'label from the exported geometry; no recovered source name is '
                                    'claimed. Native lighting, dynamic material state and complete '
                                    'appearance remain unverified. No capture inputs.',
                            'render_case': 'object-bank09-0456-00-rom'},
       'validation_pointer': 'render_cases/716',
       'validation_record': {'id': 'object-bank09-0456-00-rom',
                             'reference': 'build/assets/models/validation/baselines/object-bank09-0456-00-rom.png',
                             'size': 512,
                             'source': 'build/assets/models/rom-only/us-bank-09-preview/geometry/0456-00.gltf'}},
 457: {'canonical_pointer': 'models/693',
       'canonical_record': {'category': 'scene-items',
                            'label': 'Letter block E — ROM 09 / 0457 / 00',
                            'name': 'object-bank09-0457-00-rom',
                            'note': 'Geometry and textures extracted directly from the ROM. Descriptive '
                                    'label from the exported geometry; no recovered source name is '
                                    'claimed. Native lighting, dynamic material state and complete '
                                    'appearance remain unverified. No capture inputs.',
                            'render_case': 'object-bank09-0457-00-rom'},
       'validation_pointer': 'render_cases/717',
       'validation_record': {'id': 'object-bank09-0457-00-rom',
                             'reference': 'build/assets/models/validation/baselines/object-bank09-0457-00-rom.png',
                             'size': 512,
                             'source': 'build/assets/models/rom-only/us-bank-09-preview/geometry/0457-00.gltf'}},
 458: {'canonical_pointer': 'models/694',
       'canonical_record': {'category': 'scene-items',
                            'label': 'Letter block F — ROM 09 / 0458 / 00',
                            'name': 'object-bank09-0458-00-rom',
                            'note': 'Geometry and textures extracted directly from the ROM. Descriptive '
                                    'label from the exported geometry; no recovered source name is '
                                    'claimed. Native lighting, dynamic material state and complete '
                                    'appearance remain unverified. No capture inputs.',
                            'render_case': 'object-bank09-0458-00-rom'},
       'validation_pointer': 'render_cases/718',
       'validation_record': {'id': 'object-bank09-0458-00-rom',
                             'reference': 'build/assets/models/validation/baselines/object-bank09-0458-00-rom.png',
                             'size': 512,
                             'source': 'build/assets/models/rom-only/us-bank-09-preview/geometry/0458-00.gltf'}},
 459: {'canonical_pointer': 'models/695',
       'canonical_record': {'category': 'scene-items',
                            'label': 'Letter block G — ROM 09 / 0459 / 00',
                            'name': 'object-bank09-0459-00-rom',
                            'note': 'Geometry and textures extracted directly from the ROM. Descriptive '
                                    'label from the exported geometry; no recovered source name is '
                                    'claimed. Native lighting, dynamic material state and complete '
                                    'appearance remain unverified. No capture inputs.',
                            'render_case': 'object-bank09-0459-00-rom'},
       'validation_pointer': 'render_cases/719',
       'validation_record': {'id': 'object-bank09-0459-00-rom',
                             'reference': 'build/assets/models/validation/baselines/object-bank09-0459-00-rom.png',
                             'size': 512,
                             'source': 'build/assets/models/rom-only/us-bank-09-preview/geometry/0459-00.gltf'}},
 460: {'canonical_pointer': 'models/696',
       'canonical_record': {'category': 'scene-items',
                            'label': 'Letter block H — ROM 09 / 0460 / 00',
                            'name': 'object-bank09-0460-00-rom',
                            'note': 'Geometry and textures extracted directly from the ROM. Descriptive '
                                    'label from the exported geometry; no recovered source name is '
                                    'claimed. Native lighting, dynamic material state and complete '
                                    'appearance remain unverified. No capture inputs.',
                            'render_case': 'object-bank09-0460-00-rom'},
       'validation_pointer': 'render_cases/720',
       'validation_record': {'id': 'object-bank09-0460-00-rom',
                             'reference': 'build/assets/models/validation/baselines/object-bank09-0460-00-rom.png',
                             'size': 512,
                             'source': 'build/assets/models/rom-only/us-bank-09-preview/geometry/0460-00.gltf'}},
 461: {'canonical_pointer': 'models/697',
       'canonical_record': {'category': 'scene-items',
                            'label': 'Letter block I — ROM 09 / 0461 / 00',
                            'name': 'object-bank09-0461-00-rom',
                            'note': 'Geometry and textures extracted directly from the ROM. Descriptive '
                                    'label from the exported geometry; no recovered source name is '
                                    'claimed. Native lighting, dynamic material state and complete '
                                    'appearance remain unverified. No capture inputs.',
                            'render_case': 'object-bank09-0461-00-rom'},
       'validation_pointer': 'render_cases/721',
       'validation_record': {'id': 'object-bank09-0461-00-rom',
                             'reference': 'build/assets/models/validation/baselines/object-bank09-0461-00-rom.png',
                             'size': 512,
                             'source': 'build/assets/models/rom-only/us-bank-09-preview/geometry/0461-00.gltf'}},
 462: {'canonical_pointer': 'models/698',
       'canonical_record': {'category': 'scene-items',
                            'label': 'Letter block J — ROM 09 / 0462 / 00',
                            'name': 'object-bank09-0462-00-rom',
                            'note': 'Geometry and textures extracted directly from the ROM. Descriptive '
                                    'label from the exported geometry; no recovered source name is '
                                    'claimed. Native lighting, dynamic material state and complete '
                                    'appearance remain unverified. No capture inputs.',
                            'render_case': 'object-bank09-0462-00-rom'},
       'validation_pointer': 'render_cases/722',
       'validation_record': {'id': 'object-bank09-0462-00-rom',
                             'reference': 'build/assets/models/validation/baselines/object-bank09-0462-00-rom.png',
                             'size': 512,
                             'source': 'build/assets/models/rom-only/us-bank-09-preview/geometry/0462-00.gltf'}},
 463: {'canonical_pointer': 'models/699',
       'canonical_record': {'category': 'scene-items',
                            'label': 'Letter block K — ROM 09 / 0463 / 00',
                            'name': 'object-bank09-0463-00-rom',
                            'note': 'Geometry and textures extracted directly from the ROM. Descriptive '
                                    'label from the exported geometry; no recovered source name is '
                                    'claimed. Native lighting, dynamic material state and complete '
                                    'appearance remain unverified. No capture inputs.',
                            'render_case': 'object-bank09-0463-00-rom'},
       'validation_pointer': 'render_cases/723',
       'validation_record': {'id': 'object-bank09-0463-00-rom',
                             'reference': 'build/assets/models/validation/baselines/object-bank09-0463-00-rom.png',
                             'size': 512,
                             'source': 'build/assets/models/rom-only/us-bank-09-preview/geometry/0463-00.gltf'}},
 464: {'canonical_pointer': 'models/700',
       'canonical_record': {'category': 'scene-items',
                            'label': 'Letter block L — ROM 09 / 0464 / 00',
                            'name': 'object-bank09-0464-00-rom',
                            'note': 'Geometry and textures extracted directly from the ROM. Descriptive '
                                    'label from the exported geometry; no recovered source name is '
                                    'claimed. Native lighting, dynamic material state and complete '
                                    'appearance remain unverified. No capture inputs.',
                            'render_case': 'object-bank09-0464-00-rom'},
       'validation_pointer': 'render_cases/724',
       'validation_record': {'id': 'object-bank09-0464-00-rom',
                             'reference': 'build/assets/models/validation/baselines/object-bank09-0464-00-rom.png',
                             'size': 512,
                             'source': 'build/assets/models/rom-only/us-bank-09-preview/geometry/0464-00.gltf'}},
 465: {'canonical_pointer': 'models/701',
       'canonical_record': {'category': 'scene-items',
                            'label': 'Letter block M — ROM 09 / 0465 / 00',
                            'name': 'object-bank09-0465-00-rom',
                            'note': 'Geometry and textures extracted directly from the ROM. Descriptive '
                                    'label from the exported geometry; no recovered source name is '
                                    'claimed. Native lighting, dynamic material state and complete '
                                    'appearance remain unverified. No capture inputs.',
                            'render_case': 'object-bank09-0465-00-rom'},
       'validation_pointer': 'render_cases/725',
       'validation_record': {'id': 'object-bank09-0465-00-rom',
                             'reference': 'build/assets/models/validation/baselines/object-bank09-0465-00-rom.png',
                             'size': 512,
                             'source': 'build/assets/models/rom-only/us-bank-09-preview/geometry/0465-00.gltf'}},
 466: {'canonical_pointer': 'models/702',
       'canonical_record': {'category': 'scene-items',
                            'label': 'Letter block N — ROM 09 / 0466 / 00',
                            'name': 'object-bank09-0466-00-rom',
                            'note': 'Geometry and textures extracted directly from the ROM. Descriptive '
                                    'label from the exported geometry; no recovered source name is '
                                    'claimed. Native lighting, dynamic material state and complete '
                                    'appearance remain unverified. No capture inputs.',
                            'render_case': 'object-bank09-0466-00-rom'},
       'validation_pointer': 'render_cases/726',
       'validation_record': {'id': 'object-bank09-0466-00-rom',
                             'reference': 'build/assets/models/validation/baselines/object-bank09-0466-00-rom.png',
                             'size': 512,
                             'source': 'build/assets/models/rom-only/us-bank-09-preview/geometry/0466-00.gltf'}},
 467: {'canonical_pointer': 'models/703',
       'canonical_record': {'category': 'scene-items',
                            'label': 'Letter block O — ROM 09 / 0467 / 00',
                            'name': 'object-bank09-0467-00-rom',
                            'note': 'Geometry and textures extracted directly from the ROM. Descriptive '
                                    'label from the exported geometry; no recovered source name is '
                                    'claimed. Native lighting, dynamic material state and complete '
                                    'appearance remain unverified. No capture inputs.',
                            'render_case': 'object-bank09-0467-00-rom'},
       'validation_pointer': 'render_cases/727',
       'validation_record': {'id': 'object-bank09-0467-00-rom',
                             'reference': 'build/assets/models/validation/baselines/object-bank09-0467-00-rom.png',
                             'size': 512,
                             'source': 'build/assets/models/rom-only/us-bank-09-preview/geometry/0467-00.gltf'}},
 468: {'canonical_pointer': 'models/704',
       'canonical_record': {'category': 'scene-items',
                            'label': 'Letter block P — ROM 09 / 0468 / 00',
                            'name': 'object-bank09-0468-00-rom',
                            'note': 'Geometry and textures extracted directly from the ROM. Descriptive '
                                    'label from the exported geometry; no recovered source name is '
                                    'claimed. Native lighting, dynamic material state and complete '
                                    'appearance remain unverified. No capture inputs.',
                            'render_case': 'object-bank09-0468-00-rom'},
       'validation_pointer': 'render_cases/728',
       'validation_record': {'id': 'object-bank09-0468-00-rom',
                             'reference': 'build/assets/models/validation/baselines/object-bank09-0468-00-rom.png',
                             'size': 512,
                             'source': 'build/assets/models/rom-only/us-bank-09-preview/geometry/0468-00.gltf'}},
 469: {'canonical_pointer': 'models/705',
       'canonical_record': {'category': 'scene-items',
                            'label': 'Letter block Q — ROM 09 / 0469 / 00',
                            'name': 'object-bank09-0469-00-rom',
                            'note': 'Geometry and textures extracted directly from the ROM. Descriptive '
                                    'label from the exported geometry; no recovered source name is '
                                    'claimed. Native lighting, dynamic material state and complete '
                                    'appearance remain unverified. No capture inputs.',
                            'render_case': 'object-bank09-0469-00-rom'},
       'validation_pointer': 'render_cases/729',
       'validation_record': {'id': 'object-bank09-0469-00-rom',
                             'reference': 'build/assets/models/validation/baselines/object-bank09-0469-00-rom.png',
                             'size': 512,
                             'source': 'build/assets/models/rom-only/us-bank-09-preview/geometry/0469-00.gltf'}},
 470: {'canonical_pointer': 'models/706',
       'canonical_record': {'category': 'scene-items',
                            'label': 'Letter block R — ROM 09 / 0470 / 00',
                            'name': 'object-bank09-0470-00-rom',
                            'note': 'Geometry and textures extracted directly from the ROM. Descriptive '
                                    'label from the exported geometry; no recovered source name is '
                                    'claimed. Native lighting, dynamic material state and complete '
                                    'appearance remain unverified. No capture inputs.',
                            'render_case': 'object-bank09-0470-00-rom'},
       'validation_pointer': 'render_cases/730',
       'validation_record': {'id': 'object-bank09-0470-00-rom',
                             'reference': 'build/assets/models/validation/baselines/object-bank09-0470-00-rom.png',
                             'size': 512,
                             'source': 'build/assets/models/rom-only/us-bank-09-preview/geometry/0470-00.gltf'}},
 471: {'canonical_pointer': 'models/707',
       'canonical_record': {'category': 'scene-items',
                            'label': 'Letter block S — ROM 09 / 0471 / 00',
                            'name': 'object-bank09-0471-00-rom',
                            'note': 'Geometry and textures extracted directly from the ROM. Descriptive '
                                    'label from the exported geometry; no recovered source name is '
                                    'claimed. Native lighting, dynamic material state and complete '
                                    'appearance remain unverified. No capture inputs.',
                            'render_case': 'object-bank09-0471-00-rom'},
       'validation_pointer': 'render_cases/731',
       'validation_record': {'id': 'object-bank09-0471-00-rom',
                             'reference': 'build/assets/models/validation/baselines/object-bank09-0471-00-rom.png',
                             'size': 512,
                             'source': 'build/assets/models/rom-only/us-bank-09-preview/geometry/0471-00.gltf'}},
 472: {'canonical_pointer': 'models/708',
       'canonical_record': {'category': 'scene-items',
                            'label': 'Letter block T — ROM 09 / 0472 / 00',
                            'name': 'object-bank09-0472-00-rom',
                            'note': 'Geometry and textures extracted directly from the ROM. Descriptive '
                                    'label from the exported geometry; no recovered source name is '
                                    'claimed. Native lighting, dynamic material state and complete '
                                    'appearance remain unverified. No capture inputs.',
                            'render_case': 'object-bank09-0472-00-rom'},
       'validation_pointer': 'render_cases/732',
       'validation_record': {'id': 'object-bank09-0472-00-rom',
                             'reference': 'build/assets/models/validation/baselines/object-bank09-0472-00-rom.png',
                             'size': 512,
                             'source': 'build/assets/models/rom-only/us-bank-09-preview/geometry/0472-00.gltf'}},
 473: {'canonical_pointer': 'models/709',
       'canonical_record': {'category': 'scene-items',
                            'label': 'Letter block U — ROM 09 / 0473 / 00',
                            'name': 'object-bank09-0473-00-rom',
                            'note': 'Geometry and textures extracted directly from the ROM. Descriptive '
                                    'label from the exported geometry; no recovered source name is '
                                    'claimed. Native lighting, dynamic material state and complete '
                                    'appearance remain unverified. No capture inputs.',
                            'render_case': 'object-bank09-0473-00-rom'},
       'validation_pointer': 'render_cases/733',
       'validation_record': {'id': 'object-bank09-0473-00-rom',
                             'reference': 'build/assets/models/validation/baselines/object-bank09-0473-00-rom.png',
                             'size': 512,
                             'source': 'build/assets/models/rom-only/us-bank-09-preview/geometry/0473-00.gltf'}},
 474: {'canonical_pointer': 'models/710',
       'canonical_record': {'category': 'scene-items',
                            'label': 'Letter block V — ROM 09 / 0474 / 00',
                            'name': 'object-bank09-0474-00-rom',
                            'note': 'Geometry and textures extracted directly from the ROM. Descriptive '
                                    'label from the exported geometry; no recovered source name is '
                                    'claimed. Native lighting, dynamic material state and complete '
                                    'appearance remain unverified. No capture inputs.',
                            'render_case': 'object-bank09-0474-00-rom'},
       'validation_pointer': 'render_cases/734',
       'validation_record': {'id': 'object-bank09-0474-00-rom',
                             'reference': 'build/assets/models/validation/baselines/object-bank09-0474-00-rom.png',
                             'size': 512,
                             'source': 'build/assets/models/rom-only/us-bank-09-preview/geometry/0474-00.gltf'}},
 475: {'canonical_pointer': 'models/711',
       'canonical_record': {'category': 'scene-items',
                            'label': 'Letter block W — ROM 09 / 0475 / 00',
                            'name': 'object-bank09-0475-00-rom',
                            'note': 'Geometry and textures extracted directly from the ROM. Descriptive '
                                    'label from the exported geometry; no recovered source name is '
                                    'claimed. Native lighting, dynamic material state and complete '
                                    'appearance remain unverified. No capture inputs.',
                            'render_case': 'object-bank09-0475-00-rom'},
       'validation_pointer': 'render_cases/735',
       'validation_record': {'id': 'object-bank09-0475-00-rom',
                             'reference': 'build/assets/models/validation/baselines/object-bank09-0475-00-rom.png',
                             'size': 512,
                             'source': 'build/assets/models/rom-only/us-bank-09-preview/geometry/0475-00.gltf'}},
 476: {'canonical_pointer': 'models/712',
       'canonical_record': {'category': 'scene-items',
                            'label': 'Letter block X — ROM 09 / 0476 / 00',
                            'name': 'object-bank09-0476-00-rom',
                            'note': 'Geometry and textures extracted directly from the ROM. Descriptive '
                                    'label from the exported geometry; no recovered source name is '
                                    'claimed. Native lighting, dynamic material state and complete '
                                    'appearance remain unverified. No capture inputs.',
                            'render_case': 'object-bank09-0476-00-rom'},
       'validation_pointer': 'render_cases/736',
       'validation_record': {'id': 'object-bank09-0476-00-rom',
                             'reference': 'build/assets/models/validation/baselines/object-bank09-0476-00-rom.png',
                             'size': 512,
                             'source': 'build/assets/models/rom-only/us-bank-09-preview/geometry/0476-00.gltf'}},
 477: {'canonical_pointer': 'models/713',
       'canonical_record': {'category': 'scene-items',
                            'label': 'DEL key block — ROM 09 / 0477 / 00',
                            'name': 'object-bank09-0477-00-rom',
                            'note': 'Geometry and textures extracted directly from the ROM. Descriptive '
                                    'label from the exported geometry; no recovered source name is '
                                    'claimed. Native lighting, dynamic material state and complete '
                                    'appearance remain unverified. No capture inputs.',
                            'render_case': 'object-bank09-0477-00-rom'},
       'validation_pointer': 'render_cases/737',
       'validation_record': {'id': 'object-bank09-0477-00-rom',
                             'reference': 'build/assets/models/validation/baselines/object-bank09-0477-00-rom.png',
                             'size': 512,
                             'source': 'build/assets/models/rom-only/us-bank-09-preview/geometry/0477-00.gltf'}},
 478: {'canonical_pointer': 'models/714',
       'canonical_record': {'category': 'scene-items',
                            'label': 'Dot key block — ROM 09 / 0478 / 00',
                            'name': 'object-bank09-0478-00-rom',
                            'note': 'Geometry and textures extracted directly from the ROM. Descriptive '
                                    'label from the exported geometry; no recovered source name is '
                                    'claimed. Native lighting, dynamic material state and complete '
                                    'appearance remain unverified. No capture inputs.',
                            'render_case': 'object-bank09-0478-00-rom'},
       'validation_pointer': 'render_cases/738',
       'validation_record': {'id': 'object-bank09-0478-00-rom',
                             'reference': 'build/assets/models/validation/baselines/object-bank09-0478-00-rom.png',
                             'size': 512,
                             'source': 'build/assets/models/rom-only/us-bank-09-preview/geometry/0478-00.gltf'}},
 479: {'canonical_pointer': 'models/715',
       'canonical_record': {'category': 'scene-items',
                            'label': 'Letter block Y — ROM 09 / 0479 / 00',
                            'name': 'object-bank09-0479-00-rom',
                            'note': 'Geometry and textures extracted directly from the ROM. Descriptive '
                                    'label from the exported geometry; no recovered source name is '
                                    'claimed. Native lighting, dynamic material state and complete '
                                    'appearance remain unverified. No capture inputs.',
                            'render_case': 'object-bank09-0479-00-rom'},
       'validation_pointer': 'render_cases/739',
       'validation_record': {'id': 'object-bank09-0479-00-rom',
                             'reference': 'build/assets/models/validation/baselines/object-bank09-0479-00-rom.png',
                             'size': 512,
                             'source': 'build/assets/models/rom-only/us-bank-09-preview/geometry/0479-00.gltf'}},
 480: {'canonical_pointer': 'models/716',
       'canonical_record': {'category': 'scene-items',
                            'label': 'Letter block Z — ROM 09 / 0480 / 00',
                            'name': 'object-bank09-0480-00-rom',
                            'note': 'Geometry and textures extracted directly from the ROM. Descriptive '
                                    'label from the exported geometry; no recovered source name is '
                                    'claimed. Native lighting, dynamic material state and complete '
                                    'appearance remain unverified. No capture inputs.',
                            'render_case': 'object-bank09-0480-00-rom'},
       'validation_pointer': 'render_cases/740',
       'validation_record': {'id': 'object-bank09-0480-00-rom',
                             'reference': 'build/assets/models/validation/baselines/object-bank09-0480-00-rom.png',
                             'size': 512,
                             'source': 'build/assets/models/rom-only/us-bank-09-preview/geometry/0480-00.gltf'}},
 481: {'canonical_pointer': 'models/717',
       'canonical_record': {'category': 'scene-items',
                            'label': 'Return key block — ROM 09 / 0481 / 00',
                            'name': 'object-bank09-0481-00-rom',
                            'note': 'Geometry and textures extracted directly from the ROM. Descriptive '
                                    'label from the exported geometry; no recovered source name is '
                                    'claimed. Native lighting, dynamic material state and complete '
                                    'appearance remain unverified. No capture inputs.',
                            'render_case': 'object-bank09-0481-00-rom'},
       'validation_pointer': 'render_cases/741',
       'validation_record': {'id': 'object-bank09-0481-00-rom',
                             'reference': 'build/assets/models/validation/baselines/object-bank09-0481-00-rom.png',
                             'size': 512,
                             'source': 'build/assets/models/rom-only/us-bank-09-preview/geometry/0481-00.gltf'}},
 482: {'canonical_pointer': 'models/718',
       'canonical_record': {'category': 'scene-items',
                            'label': 'Long blank key block — ROM 09 / 0482 / 00',
                            'name': 'object-bank09-0482-00-rom',
                            'note': 'Geometry and textures extracted directly from the ROM. Descriptive '
                                    'label from the exported geometry; no recovered source name is '
                                    'claimed. Native lighting, dynamic material state and complete '
                                    'appearance remain unverified. No capture inputs.',
                            'render_case': 'object-bank09-0482-00-rom'},
       'validation_pointer': 'render_cases/742',
       'validation_record': {'id': 'object-bank09-0482-00-rom',
                             'reference': 'build/assets/models/validation/baselines/object-bank09-0482-00-rom.png',
                             'size': 512,
                             'source': 'build/assets/models/rom-only/us-bank-09-preview/geometry/0482-00.gltf'}}}

KEY_ACTIONS = {453: (0, 0, 0, 65),
 454: (1, 0, 1, 66),
 455: (2, 0, 2, 67),
 456: (3, 0, 3, 68),
 457: (4, 0, 4, 69),
 458: (5, 0, 5, 70),
 459: (6, 1, 0, 71),
 460: (7, 1, 1, 72),
 461: (8, 1, 2, 73),
 462: (9, 1, 3, 74),
 463: (10, 1, 4, 75),
 464: (11, 1, 5, 76),
 465: (12, 2, 0, 77),
 466: (13, 2, 1, 78),
 467: (14, 2, 2, 79),
 468: (15, 2, 3, 80),
 469: (16, 2, 4, 81),
 470: (17, 2, 5, 82),
 471: (18, 3, 0, 83),
 472: (19, 3, 1, 84),
 473: (20, 3, 2, 85),
 474: (21, 3, 3, 86),
 475: (22, 3, 4, 87),
 476: (23, 3, 5, 88),
 477: (24, 4, 0, None),
 478: (25, 4, 1, 46),
 479: (26, 4, 2, 89),
 480: (27, 4, 3, 90),
 481: (28, 4, 4, None),
 482: (29, 5, 0, 32)}

def digest(value):
    return hashlib.sha256(json.dumps(value, sort_keys=True, separators=(",", ":")).encode()).hexdigest()


class KeyModelSemanticNameTests(unittest.TestCase):
    def test_all_202_prior_records_and_their_branches_are_unchanged(self):
        registry = names.load_registry()
        retained = [r for r in registry["models"]
                    if (r["bank"], r["entry"], r["segment"]) not in KEY_MODEL_NAMES
                    and (r["bank"], r["entry"], r["segment"]) not in HELD_CHARACTER_NAMES
                    and (r["bank"], r["entry"], r["segment"]) not in REMAINING_SCENE_PROP_NAMES]
        self.assertEqual(202, len(retained))
        self.assertEqual("8d93066c00aa34e9d8df3e30351796c27652b54baf82c9b7fc58eb254e582c98", digest(retained))
        self.assertEqual([(1, 75, 0)], [(r["bank"], r["entry"], r["segment"])
                         for r in registry["models"] if "model_specific_branch" in r])

    def test_exact_30_records_and_only_two_complete_shared_consumers(self):
        added = [r for r in names.load_registry()["models"]
                 if (r["bank"], r["entry"], r["segment"]) in KEY_MODEL_NAMES]
        self.assertEqual(30, len(added))
        self.assertEqual("67d48540c3509a178362519643571f72e3b733d5289b03a490f30fd853724548", digest(added))
        self.assertEqual(KEY_MODEL_NAMES,
                         {(r["bank"], r["entry"], r["segment"]): r["name"] for r in added})
        for record in added:
            self.assertEqual(EXPECTED_CONSUMERS, record["consumers"])
            self.assertNotIn("model_specific_branch", record)
            self.assertEqual(["docs/evidence/key_model_semantic_registry_expansion.md",
                              "docs/evidence/text_entry_model_role_names.md"], record["evidence"])
        self.assertEqual([568, 2660], [c["size_bytes"] for c in EXPECTED_CONSUMERS])
        self.assertNotIn("func_151EEBE8", {c["symbol"] for c in EXPECTED_CONSUMERS})

    def test_whole_canonical_file_and_all_thirty_numeric_joins_remain_unchanged(self):
        raw = (names.ROOT / "config/model-inspection.json").read_bytes()
        self.assertEqual("55a86fac63f12faa0f74fbdeb1f1b992374513acd174c7353885898ba436e1cd", hashlib.sha256(historical_canonical_bytes(self, raw)).hexdigest())
        canonical = json.loads(raw)
        validation = json.loads((names.ROOT / "config/model-validation.json").read_text())
        for entry, pin in SOURCE_JOINS.items():
            self.assertEqual(pin["canonical_record"],
                             canonical["models"][int(pin["canonical_pointer"].split("/")[-1])])
            self.assertEqual(pin["validation_record"],
                             validation["render_cases"][int(pin["validation_pointer"].split("/")[-1])])
            self.assertEqual(pin["canonical_record"]["render_case"], pin["validation_record"]["id"])
            self.assertEqual(KEY_MODEL_NAMES[9, entry, 0], pin["canonical_record"]["label"].split(" — ")[0])

    def test_labels_do_not_spread_to_slots_ascii_banks_or_other_segments(self):
        registry = names.load_registry()
        payload = b"equal bytes cannot substitute for a numeric key"
        for r in registry["models"]:
            r.update(source_bytes=len(payload), model_sha1=hashlib.sha1(payload).hexdigest(),
                     model_sha256=hashlib.sha256(payload).hexdigest())
        unknown = {"status": "unknown", "name": None}
        for key, label in KEY_MODEL_NAMES.items():
            self.assertEqual(label, resolve_synthetic_name(registry, "us", registry["rom_sha1"], key, payload)["name"])
            for other in [(1,key[1],0),(3,key[1],0),(4,key[1],0),(9,key[1],1)]:
                self.assertEqual(unknown, resolve_synthetic_name(registry,"us",registry["rom_sha1"],other,payload))
        for key in [(9,452,0),(9,483,0),(9,0,0),(9,26,0),(9,27,0),(9,30,0)]:
            self.assertEqual(unknown, resolve_synthetic_name(registry,"us",registry["rom_sha1"],key,payload))
        self.assertEqual("DEL key block", KEY_MODEL_NAMES[9,477,0])
        self.assertEqual("Dot key block", KEY_MODEL_NAMES[9,478,0])
        self.assertEqual("Letter block Y", KEY_MODEL_NAMES[9,479,0])
        self.assertEqual("Letter block Z", KEY_MODEL_NAMES[9,480,0])

    def test_limits_preserve_stored_appearance_dynamic_selector_and_ui_namespace(self):
        for r in names.load_registry()["models"]:
            if (r["bank"], r["entry"], r["segment"]) not in KEY_MODEL_NAMES:
                continue
            limits = " ".join(r["limitations"])
            for phrase in ["first two referenced vertex colors", "combiner and OtherMode",
                           "runtime activation", "middle selector is dynamic", "UI state 3 is not a scene ID",
                           "without a local NULL check", "successful loading is not guaranteed"]:
                self.assertIn(phrase, limits)
            slot,row,column,_ = KEY_ACTIONS[r["entry"]]
            self.assertIn(f"Resource slot {slot}, selection row {row}, column {column}", limits)

    @unittest.skipUnless((names.ROOT / "roms/baserom.us.z64").is_file(), "owned US ROM unavailable")
    def test_owned_models_headers_and_payload_adverse_controls(self):
        registry = names.load_registry()
        _, _, digest_, bundles, _ = models.load_model_bundles("us", names.ROOT / "roms/baserom.us.z64", 9)
        sources = {(9,b.index,s.index):s.data for b in bundles for s in b.segments}
        faces = vertices = 0
        for entry,pin in MODEL_PINS.items():
            key = (9,entry,0); data = sources[key]
            self.assertEqual(KEY_MODEL_NAMES[key], names.resolve_name(registry,"us",digest_,key,data)["name"])
            self.assertEqual(pin["source_payload"], {"bytes":len(data), "sha1":hashlib.sha1(data).hexdigest(),
                                                   "sha256":hashlib.sha256(data).hexdigest()})
            self.assertEqual(pin["header"]["sha256"], hashlib.sha256(data[:40]).hexdigest())
            geometry = models.parse_geometry_for_bank(data,9)
            self.assertEqual(data, models.rebuild_direct_model(data,geometry))
            self.assertEqual(pin["header"]["primary_list_offset"],geometry.display_list_offset)
            self.assertEqual(pin["header"]["primary_list_bytes"],geometry.display_list_size)
            self.assertEqual(pin["vertices"],len(geometry.vertices)); vertices += len(geometry.vertices)
            self.assertEqual(pin["faces"],len(geometry.faces)); faces += len(geometry.faces)
            self.assertEqual(pin["vertex_bytes_sha256"],hashlib.sha256(data[40:geometry.display_list_offset]).hexdigest())
            self.assertEqual(pin["display_list_sha256"],hashlib.sha256(data[geometry.display_list_offset:]).hexdigest())
            for offset in [0,39,40,geometry.display_list_offset,len(data)-1]:
                changed = bytearray(data); changed[offset] ^= 1
                with self.subTest(entry=entry,offset=offset), self.assertRaisesRegex(ValueError,"named model source identity changed"):
                    names.resolve_name(registry,"us",digest_,key,bytes(changed))
            for field in ["model_sha1","model_sha256","source_bytes"]:
                bad = copy.deepcopy(registry)
                rec = next(r for r in bad["models"] if (r["bank"],r["entry"],r["segment"])==key)
                rec[field] = rec[field]+1 if field=="source_bytes" else "0"*len(rec[field])
                with self.subTest(entry=entry,field=field), self.assertRaisesRegex(ValueError,"named model source identity changed"):
                    names.resolve_name(bad,"us",digest_,key,data)
        self.assertEqual((300,362),(faces,vertices))

    @unittest.skipUnless((names.ROOT / "roms/baserom.us.z64").is_file(), "owned US ROM unavailable")
    def test_owned_complete_consumer_positive_and_every_byte_negative(self):
        path,layout = models.resolve_rom("us", names.ROOT / "roms/baserom.us.z64")
        rom,_ = models.normalize_rom(path.read_bytes())
        code = models.parse_game_archive(rom[layout["game_start"]:layout["game_end"]]).code
        registry = names.load_registry()
        registry["models"] = [next(r for r in registry["models"] if (r["bank"],r["entry"],r["segment"])==(9,453,0))]
        start = 0x151EDF4C; size = 568+2660
        selected = code[start-layout["game_vram"]:start-layout["game_vram"]+size]
        self.assertEqual(2,names.verify_consumers(selected,start,registry))
        for offset in range(size):
            changed=bytearray(selected); changed[offset]^=1
            symbol="func_151EDF4C" if offset<568 else "func_151EE184"
            with self.subTest(offset=offset), self.assertRaisesRegex(ValueError,"model-name consumer changed: "+symbol):
                names.verify_consumers(bytes(changed),start,registry)
        for amount in [1,4]:
            with self.assertRaisesRegex(ValueError,"model-name consumer changed: func_151EE184"):
                names.verify_consumers(selected[:-amount],start,registry)

    @unittest.skipUnless((names.ROOT / "roms/baserom.us.z64").is_file(), "owned US ROM unavailable")
    def test_owned_input_and_resource_contract_uses_noncontiguous_alphabet(self):
        path,layout=models.resolve_rom("us",names.ROOT / "roms/baserom.us.z64")
        rom,_=models.normalize_rom(path.read_bytes())
        code=models.parse_game_archive(rom[layout["game_start"]:layout["game_end"]]).code
        # Verify complete spans before interpreting individual semantic constants.
        for consumer in EXPECTED_CONSUMERS:
            offset=int(consumer["vram"],16)-layout["game_vram"]
            self.assertEqual(consumer["sha1"],hashlib.sha1(code[offset:offset+consumer["size_bytes"]]).hexdigest())
        def immediate(address,opcode,rs,rt):
            word=struct.unpack_from(">I",code,address-layout["game_vram"])[0]
            self.assertEqual((opcode,rs,rt),(word>>26,(word>>21)&31,(word>>16)&31))
            return word&0xFFFF
        first=immediate(0x151EDFC0,9,0,11); stop=immediate(0x151EE108,9,0,1)
        stride=immediate(0x151EE110,9,10,10); bound=immediate(0x151EEAFC,10,4,1)
        self.assertEqual((453,483,12,360),(first,stop,stride,bound))
        self.assertEqual(stride,immediate(0x151EEAF8,9,4,4))
        alpha=immediate(0x151EE3D4,9,16,16)
        space=immediate(0x151EE404,9,0,20); dot=immediate(0x151EE45C,9,0,20)
        correction=immediate(0x151EE898,9,16,20)-0x10000
        self.assertEqual((65,32,46,-2),(alpha,space,dot,correction))
        self.assertEqual(19,immediate(0x151EE8C4,10,8,1))
        derived={}
        for row,columns in enumerate([6,6,6,6,5,1]):
            for column in range(columns):
                slot=row*6+column-(1 if row==5 else 0)
                char=space if row==5 else None if row==4 and column in (0,4) else dot if row==4 and column==1 else slot+alpha+(correction if row==4 else 0)
                derived[first+slot]=(slot,row,column,char)
        self.assertEqual(KEY_ACTIONS,derived)
        self.assertEqual([None,46,89,90,None,32],[derived[e][3] for e in range(477,483)])


if __name__ == "__main__":
    unittest.main()
