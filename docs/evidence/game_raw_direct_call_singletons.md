# US direct-call singleton source units

Evidence kind: `structural_analysis`. These thirty-nine remaining raw-map
segments each contain one complete function reached by a direct `jal` call
from outside its range. The raw assembly index and independent US function CSV
agree on every start and span. All endpoints are 16-byte aligned and no
conditional branch crosses an endpoint. Generic source names derive from
retail-ROM offsets; every function remains raw assembly.

| Source | US range | Bytes | Function | Debug | ECTS | Range SHA-1 |
| --- | --- | ---: | --- | --- | --- | --- |
| `src/game/game_12DAB0.c` | `0x100600:0x101090` | 2,704 | `func_15100600` | - | - | `d1fdad1973663b865309025d3326371d2da5c5cd` |
| `src/game/game_1DC150.c` | `0x1AECA0:0x1AF270` | 1,488 | `func_151AECA0` | - | - | `de3ef597d4103a3092473d62691d1a852e905ea1` |
| `src/game/game_112F90.c` | `0xE5AE0:0xE5FD0` | 1,264 | `func_150E5AE0` | strong | candidate | `5ef52b73a8243497847d82e1813fa96130bcdaa9` |
| `src/game/game_48B10.c` | `0x1B660:0x1BB20` | 1,216 | `func_1501B660` | strong | strong | `43983ee62dd822808e0fced8d306971ea2ca653c` |
| `src/game/game_1BA1D0.c` | `0x18CD20:0x18D1C0` | 1,184 | `func_1518CD20` | strong | - | `a3ea0ff5dcdb3ac68c8480f708ebe32730361321` |
| `src/game/game_14F130.c` | `0x121C80:0x1220D0` | 1,104 | `func_15121C80` | - | - | `3f27a438b2cc310076598e6426ed8af45374a05f` |
| `src/game/game_1FF760.c` | `0x1D22B0:0x1D26C0` | 1,040 | `func_151D22B0` | - | - | `2f3ec4cd7cdb7f9b928fba80274b1ab197825ac6` |
| `src/game/game_128970.c` | `0xFB4C0:0xFB8C0` | 1,024 | `func_150FB4C0` | candidate | - | `cf914bfb1d1fe6a220544cf26dde2391502f2f63` |
| `src/game/game_DDB60.c` | `0xB06B0:0xB0A60` | 944 | `func_150B06B0` | - | - | `0cce7ac9507a68fa033b16301f9f5786338dc27b` |
| `src/game/game_1A0420.c` | `0x172F70:0x1732E0` | 880 | `func_15172F70` | strong | strong | `58c691d923a984fc5de88fc2ded7b7f93c81535b` |
| `src/game/game_193130.c` | `0x165C80:0x165F70` | 752 | `func_15165C80` | strong | strong | `8ecdff025d68a2bee155b02d730c88cdf8f3ddcd` |
| `src/game/game_15BAA0.c` | `0x12E5F0:0x12E8E0` | 752 | `func_1512E5F0` | candidate | candidate | `bdc5011ab9f7e6fd58603956b24cc6a784c60ce7` |
| `src/game/game_76E50.c` | `0x499A0:0x49C40` | 672 | `func_150499A0` | strong | strong | `25b5c6745a43e43121c7a2d3b90b74ee12c0b1be` |
| `src/game/game_113480.c` | `0xE5FD0:0xE6230` | 608 | `func_150E5FD0` | strong | - | `3c77615c007c6ecda043ad65707f2ca3cfa806ca` |
| `src/game/game_D52A0.c` | `0xA7DF0:0xA8050` | 608 | `func_150A7DF0` | strong | - | `4b0b12413fa14606677a6cf5af6f50602560614f` |
| `src/game/game_637C0.c` | `0x36310:0x36570` | 608 | `func_15036310` | - | - | `cba72f4fd10a4fccd6e2465b4dc3e8cc90c5f396` |
| `src/game/game_1A7260.c` | `0x179DB0:0x179FE0` | 560 | `func_15179DB0` | candidate | candidate | `a321ac5a5e3dada4dce9e039ae6b2fe90c33a2a3` |
| `src/game/game_778B0.c` | `0x4A400:0x4A5E0` | 480 | `func_1504A400` | strong | strong | `4cfb8d97d90b52a4b71af0e7c631568f88168f0a` |
| `src/game/game_15A840.c` | `0x12D390:0x12D560` | 464 | `func_1512D390` | strong | strong | `df2acc5ba9710d544b57599c14e29cb01569a188` |
| `src/game/game_1355D0.c` | `0x108120:0x1082D0` | 432 | `func_15108120` | - | - | `154cd9e96d9f1600dcfc64c896578969679152de` |
| `src/game/game_15B960.c` | `0x12E4B0:0x12E5F0` | 320 | `func_1512E4B0` | - | - | `9a17497a666a1537984fe12dfb0e68b3e459fab4` |
| `src/game/game_43880.c` | `0x163D0:0x16500` | 304 | `func_150163D0` | strong | strong | `5d42be01ef96501de4cbd04700429767b3cc0aa9` |
| `src/game/game_20A290.c` | `0x1DCDE0:0x1DCEF0` | 272 | `func_151DCDE0` | - | - | `dc1ab30242e2ee8d5d2f2922deb9cf8792f03334` |
| `src/game/game_1DC980.c` | `0x1AF4D0:0x1AF5C0` | 240 | `func_151AF4D0` | - | - | `2dfe8e900ffb7c0fb5a26d03b26ebf60e5951286` |
| `src/game/game_137DE0.c` | `0x10A930:0x10AA20` | 240 | `func_1510A930` | strong | strong | `7f8d001ae3575a0aa30794acc8c2d87f5b99df09` |
| `src/game/game_1DBC60.c` | `0x1AE7B0:0x1AE890` | 224 | `func_151AE7B0` | strong | candidate | `7a5232a4c930f95ce0e53c2e0f00cfb03cf2af2e` |
| `src/game/game_1227F0.c` | `0xF5340:0xF5420` | 224 | `func_150F5340` | strong | - | `dd4d31c35ec98d546946065a64ed9c857dcc0b59` |
| `src/game/game_43330.c` | `0x15E80:0x15F40` | 192 | `func_15015E80` | strong | - | `de0bf4a985301376dafa9b538a8d3cb355a8eb7c` |
| `src/game/game_11F6E0.c` | `0xF2230:0xF22D0` | 160 | `func_150F2230` | - | - | `09ba675d74641bf826dbbeb3538f838feafeeffe` |
| `src/game/game_6B280.c` | `0x3DDD0:0x3DE70` | 160 | `func_1503DDD0` | strong | strong | `bb76ab1025b2d2d4a341fee7c8c4447f91ba5555` |
| `src/game/game_DF260.c` | `0xB1DB0:0xB1E20` | 112 | `func_150B1DB0` | - | - | `87d826404c85c372ee27710180457a061211826f` |
| `src/game/game_EEB10.c` | `0xC1660:0xC16C0` | 96 | `func_150C1660` | strong | candidate | `eaf78d57bda6d715c151a938fb072fe1c692b4b8` |
| `src/game/game_E2DA0.c` | `0xB58F0:0xB5950` | 96 | `func_150B58F0` | - | - | `4e756fa56a51d87f8bfce48502b928548fdc192c` |
| `src/game/game_1E3050.c` | `0x1B5BA0:0x1B5BF0` | 80 | `func_151B5BA0` | strong | strong | `28df615e3ce511d6339893f3c683b25e869f5d26` |
| `src/game/game_15D6E0.c` | `0x130230:0x130280` | 80 | `func_15130230` | - | - | `5075817bcae5188293be94d07d0c1d68c51c41e1` |
| `src/game/game_40440.c` | `0x12F90:0x12FE0` | 80 | `func_15012F90` | - | - | `cf6a4dbb73c33be32a9b16ce309601c01112ba83` |
| `src/game/game_FC4F0.c` | `0xCF040:0xCF080` | 64 | `func_150CF040` | strong | strong | `204ce71180084c150fd9239f867ad1c414c2e1b5` |
| `src/game/game_1E6B10.c` | `0x1B9660:0x1B9690` | 48 | `func_151B9660` | strong | strong | `62aab7ec2b01f92891e4282328a36e037898e5bf` |
| `src/game/game_42DC0.c` | `0x15910:0x15920` | 16 | `func_15015910` | candidate | - | `5689e2ff90bb554bf5ebee77747968d7bdbbf005` |

Every function has at least one external caller. Beta correlations are retained
as supporting identity evidence where available; the direct call target and
exact indexed span establish each working singleton boundary.
