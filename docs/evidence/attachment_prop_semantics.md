# Bank-09 attachment and UI prop descriptions

All labels here are [appearance-only descriptions](model_name_confidence_review.md),
not confirmed item, character, gameplay or original developer identities. Bank-09
entry numbers are distinct from action, lookup, animation and character-bank
indices. Source hashes and complete consumer pins live in the registry.

## Specialized source observations and routes

These segment-zero records were inspected as ROM-only neutral source renders;
cigar-like and helmet-like shapes also had individual views. Stored texture
phases and inspection presets are not native runtime state.

| Bank:entry:segment | Label | Bounded visual basis |
| --- | --- | --- |
| `09:0029:00` | Cigar | Brown cylindrical body and pale tip |
| `09:0133:00` | Military helmet | Green dome, white marking and two straps |
| `09:0162:00` | Wall-mounted flame (UI model) | Tapered flame-like surface with a small wall plate |
| `09:0164:00` | Upright cash bundle | Folded green banknotes, red band and eyes |
| `09:0165:00` | Upright cash bundle — attachment variant | Similar imagery to 164, distinct source and specialized consumer |
| `09:0185:00` | Conker HUD head | Orange squirrel head, cream muzzle and black eyes |
| `09:0186:00` | Digital timer | Four-digit device; displayed digits belong to an inspection preset |
| `09:0345:00` | Hanging bell | Small green bell hanging from a dark cord |


- **Action attachments, 09:29 and 09:133.** `1514DCAC` requests action **35**
  followed by **68** on the same parent. Action 35's header `80086DD4` points
  to one record at `8009D1E0` (model **133**, kind 2, animation selector 2).
  Action 68's header `80086EDC` points to one record at `8009D1F0` (model
  **29**, kind 1, selector -1). `15083568` passes the distinct fields through
  `15030AF4` and `1502FFD8`; the animated path uses `1503F62C`, while both
  reach explicit bank-09 loading in `1502FE10`. Owner checks, duplicate
  suppression, allocation and loading can prevent creation. No Conker parent,
  smoking controller or guaranteed creation is inferred.
- **Direct timer, 09:186.** `15093878` calls `1518C900` with model 186 and
  stores its primary list at `800D2448`. `150938BC` derives digit textures
  from `800D2450`, binds four pixel segments and submits that retained list.
  The registry also pins the relocation and texture/matrix helpers selected
  by the [direct-binding evidence](us_direct_segment_texture_bindings.md).
  The rendered 00:00 is an explicit inspection preset, never an initial or
  observed gameplay time. The label therefore omits the preset.
- **Dedicated HUD head, 09:185.** `1509093C` loads model 185 through
  `1502FE10`, retains its list at state `800D24C8+0x80` and maintains four
  correlated texture selectors. `150911F4` uses `1510D0EC` to bind them and
  submits the retained list. This is separate from bank-01 Conker model 0,
  which has its own separately classified record. The label does not select a texture phase or native
  HUD deformation. See [specialized consumers](us_special_attachment_materials.md).
- **Copied-list UI, 09:162 and 09:164.** `151EB06C` requests model 164 /
  animation 23 at `151EB5BC`, and model 162 / animation 8 at `151EB5D8`.
  `151ED90C` constructs the copied lists; `151EDBDC` renders them. Their
  shared animation/model/texture helpers are pinned separately from the
  specialized attachment path. The flame's shape is not world-placement or
  damage-controller evidence. See [UI constructors](us_ui_constructor_materials.md).
- **Specialized cash attachment, 09:165.** `150FAE18` or `151D6BFC` passes
  model 165 to `15157010`. Callbacks `150FB1E8` / `151D710C` bind descriptor
  195 through `15133EEC`; type-54 renderer `15157420` submits the model.
  Source hashes, size and native alpha handling differ from UI model 164,
  even though displayed mesh/rig/images agree. Neither identity collapses
  into the other, or into bank-01 character 165. Whole constructors have
  broader unproved event purposes. See [specialized consumers](us_special_attachment_materials.md).
- **Ordinary lookup, 09:345.** `15010A60` stores lookup selector **86** at
  template `+0x56` and flags `0x0D00` at `+0x50`, then calls `1513264C`.
  The table at `800A3880` maps selector 86 to model **345**; `151336A8`
  loads it and `15132B80` submits its list. The reviewed initial callback
  flag is clear. This is not ringing behavior, and neither 86 nor 345 is
  the square-base bank-03 bell. See [ordinary objects](us_bank09_object_materials.md).

The legacy `Cigar`, `Military helmet`, `Conker HUD head`, and other table
wording is retained descriptive provenance. The pixels and routing do not confirm
a proper item/character identity, military role, exclusive parent or behavior.

## Generic action attachment records

Canonical render cases join exact validation paths, unique numeric manifest rows
and independent ROM-decoded payloads. Manifest SHA-256:
`f191011cd994a2e19be32ec8ac5086d9a505447f20c38fcb1d066281aa9ea47f`.
The review round-tripped source geometry through the native attachment format,
checked glTF dependencies, and inspected six material and four supplemental sheets
plus entry 20's linked pixels. Canonical indices below are `/models/` indices;
entries are bank 09, segment 0. V/F/J are source vertices/faces/joints.

| Entry | Descriptive name | Actions | V/F/J | Canonical index |
| ---: | --- | --- | --- | ---: |
| 13 | Bottle | 4 | 127/78/0 | 357 |
| 20 | Lighter-fluid container | 12 | 72/56/0 | 375 |
| 24 | Frying pan | 16 | 94/92/0 | 224 |
| 25 | Yellow handheld console | 21 | 62/40/0 | 804 |
| 28 | Mask and snorkel | 32 | 76/72/0 | 361 |
| 42 | Toilet-paper roll | 147 | 26/20/0 | 854 |
| 43 | Crown | 62 | 166/135/0 | 227 |
| 44 | Travel suitcase | 63 | 83/66/0 | 366 |
| 55 | Chainsaw | 86 | 143/110/0 | 229 |
| 58 | Curved sword | 88, 166 | 42/30/0 | 501 |
| 61 | Paired red canisters | 92 | 72/54/0 | 377 |
| 65 | Revolver | 22 | 176/146/0 | 230 |
| 70 | Black gas mask | 37 | 85/74/0 | 359 |
| 71 | Green gas mask | 38 | 85/74/0 | 360 |
| 73 | Green ring-pull can | 96 | 48/40/0 | 387 |
| 75 | Flashlight | 100 | 28/28/0 | 855 |
| 83 | Scalpel | 107 | 22/28/0 | 856 |
| 84 | Syringe | 108 | 47/44/0 | 385 |
| 93 | Skull bandana | 121, 122 | 64/50/0 | 419 |
| 96 | Open milk carton | 125 | 57/32/0 | 495 |
| 99 | Headphones | 127 | 59/56/0 | 376 |
| 111 | Drumstick | 149, 162 | 42/70/0 | 365 |
| 112 | Hexagonal dumbbell | 150, 163 | 49/62/0 | 896 |
| 113 | Scythe | 151 | 47/54/0 | 378 |
| 114 | Pitchfork | 154 | 59/40/0 | 388 |
| 118 | Red-tipped scalpel | 153 | 22/28/0 | 857 |
| 121 | Black sunglasses | 48 | 38/24/0 | 816 |
| 123 | Bone-handled knife | 47 | 45/50/0 | 380 |
| 124 | Wrapped-handle knife | 34 | 45/50/0 | 381 |
| 125 | White mug | 110 | 50/58/0 | 371 |
| 131 | Three coloured balls | 43 | 132/72/4 | 362 |
| 139 | Handled net | 51 | 150/122/5 | 239 |

- 15083568 at 150835A0–150835BC computes 80086CC4 + (action - 1) * 8, reads u8 count at header +4 and program pointer at +0. The loop advances records by 16 at 1508368C. Only the 36 explicit selected headers are accepted here; no whole-table extent is inferred.
- Record kind 0 at +3 follows 150835E0–15083614 to 15083AC8; byte +0 in that ABI is not admitted as a bank 09 index. The selected kinds 1/2 instead use 15083620–1508367C. Record +0 goes to constructor a1, record +1 to a2, record +7 to a3. Record +2 is a separate updater selector. Action ID is a separate stack parameter, not the model entry.
- Kind 2 passes record +6 as attachment animation selector; other selected kind 1 records pass -1. Selected action 43 requests model 131 with selector 0; action 51 requests model 139 with selector 11. Every other selected action is kind 1 and selector -1. The selected kinds are explicitly checked; this review does not extrapolate unknown kinds.
- 15030AF4 retains incoming model a1 in s1 at 15030AFC, writes descriptor byte +1 at 15030BEC, and writes the distinct action ID to byte +6 at 15030C18. Updater reaches byte +7 at 15030C48. Selector reaches byte +17 at 15030C80. Texture halfwords +18/+1A are zeroed; that alone supplies no texture binding.
- Caller a3 of 15083568 is copied through s6 to constructor stack argument 6. At 15030CE0–15030CFC a nonzero value is stored as descriptor halfword +1C, while zero becomes FFFF. The expression-specific zero-a3 assumption is deliberately not copied into these generic actions.
- 1502FFD8 reads signed descriptor +17 at 1502FFF8. -1 selects 1502FE10 at 15030028; other values select 1503F62C at 15030058. Both read descriptor +1 as the index. 1503F62C saves and forwards that same index to 1502FE10 at 1503F694/1503F6BC.
- 1502FE10 retains its index and at 1502FE64–1502FE80 passes explicit bank 9 and that index to 1502B6BC. Cached-model branches do not change that index identity.

## Necessary scope limits

15030AF4 requires nonzero owner byte +3B. Unless record flag 8 bypasses the check, an existing descriptor with the same owner, action and model suppresses another creation. Allocation and model-load failures can prevent success. 15083568 attempts records in order and returns the last result; it has no rollback or aggregate-success result. These are stored constructor requests, never observed runtime instances.

15031A50 is the generic model-keyed initializer called after construction. Its body has side effects for some selected entries (including 55, 61, 73, 93); this audit does not assign gameplay meanings from these calls, does not assert a no-op initializer for all selected models, and does not audit downstream updater behavior. Shared consumers retain generic roles.

Fresh event discovery reproduced 4027 routes, 1472 event lists, zero unresolved lists, 226 events, 49 actions, 45 attachment entries, 109 create events and 117 remove events. Selected positive stored-create witnesses exist for actions 16,21,22,32,43,47,86,88,100,108. The report retains exact event records and discovery context, but no live parent/reachability claim follows. The other 26 selected actions are established by their exact stored headers and records, not by an inferred event witness.


### Exact selected records

These 36 explicit headers each contain one selected 16-byte record. Header address is `80086CC4 + (action-1)*8`. Only the explicit selected headers are accepted; no whole-table extent is inferred. Kinds1/2 request model byte0; kind0 has the distinct parent-modification ABI. The two kind2 requests are action43/model131/animation0 and action51/model139/animation11; the remaining34 are kind1 with selector -1. Hashes below are SHA-256 of the complete header/record.

| Action | Entry | Kind | Animation | Header address | Record address | Header SHA-256 | Record SHA-256 |
|---:|---:|---:|---:|---|---|---|---|
|4|13|1|-1|`0x80086CDC`|`0x8009CE40`|`e18c7661b5d645b365f3779e089fcd9e1a92aa25189e09f877cc4de9024f1aad`|`9603a86006625dcdadf04a0bcf667b0d2b9d4742b7913b7060046a509a64bc38`|
|12|20|1|-1|`0x80086D1C`|`0x8009CEA0`|`404ec174bf93b5537d9596c1652a0fd2d2fbe3e0e2aa21a5e3c0d9781c8a4dd3`|`14b286861d657d3536a780bc6d75343284cc6c92199fadaa0addb833487d8b6d`|
|16|24|1|-1|`0x80086D3C`|`0x8009CF20`|`3360c0eb4d50eca0470a50e88af1980d4c697f65a9e6f4518ae144d4869720bb`|`f2a01c0954e5483b0b43fcd5d501a092563d146c0a2ac80f5306c3032bfbea9a`|
|21|25|1|-1|`0x80086D64`|`0x8009CF30`|`245362442460fe3b3035eeb24e848f0fae31b765e9780097461ec04dd09e8f2d`|`7b1f3bfeeb0fcfa28378efc1491733207eea894f6d44754e9145839b96996d58`|
|22|65|1|-1|`0x80086D6C`|`0x8009CFB0`|`dcb172e21adc3ce93188c89d30320ab1be717fd0345c005905765815727d1883`|`4c7109914bdc83529ad3b14f82a90a59fe893181d620244f417c96fd7052b57e`|
|32|28|1|-1|`0x80086DBC`|`0x8009D010`|`dd194ae481a996c30579e2664eb22839ff212aa688c590a60feb26fbfa742f68`|`8740604e613d0208278f532505bc953f4971de738d53db11734cdac09e0213da`|
|34|124|1|-1|`0x80086DCC`|`0x8009D1D0`|`716cc305853aac5570c17919871f972a62420cffeba0abd624fcf43ead5d545a`|`194667e6623acf4f29b04818d6f3fada23f52b15c44e7b7b7532e87f6025cba2`|
|37|70|1|-1|`0x80086DE4`|`0x8009D5A0`|`36135fc5e30331414ffaf389ea61454328c87365313a794f13697a17ab8ea731`|`672dbdf64f32a354ab6fa9eb06f0a31f172804f2f013265bb9c81343a7de878b`|
|38|71|1|-1|`0x80086DEC`|`0x8009D5B0`|`8714cdf726d96c8be4c7a4a79fb503c8e7040cd9f2d341f4232b987bcd007ac0`|`c32675126bc3391f4b36c04dfc8664aa395dfa9f732ca4345d37dcafe5b02c08`|
|43|131|2|0|`0x80086E14`|`0x8009D280`|`e2a69444f003eaabb0dd798862ad689f58475e5ea0765b2806bf13fdaa803214`|`de8938ada882185799c7dffe192ee39abd130e48fb889de09dda8e839ec3bb7e`|
|47|123|1|-1|`0x80086E34`|`0x8009D1A0`|`18cf9ccd236b28f01c2d43b5b2a88452ef9983f597f7a83c1707483b18513cfd`|`3b6d9815f9d8d948b01a0e3d5cc89dffa08e00e9d1c9683323cab71b488c5f61`|
|48|121|1|-1|`0x80086E3C`|`0x8009D8C0`|`4b1104d4b1c281306f86b9393126773bdc736b829d2e3f929e7bf5f133e0ad73`|`cf7fd4e9c00193b2887d5f518db95786aaf2e0016206df8a5b0712c324ddb2de`|
|51|139|2|11|`0x80086E54`|`0x8009D170`|`43e8ff863179cfd430148ef54d9b38b32e8ba1e6bfe492789b6fc4f6fbab87a3`|`9b511297b2cf3fccfd1b8941599e57a0e635fd3e4d6132799edd3931c0c609e8`|
|62|43|1|-1|`0x80086EAC`|`0x8009D400`|`a304ad6217678f4bbb1c6c6750d35bf5e4789a5d9e237f06c3647266bfb837e6`|`8c0e79f961b7be4a81c358c6ff3607f218505299b9a54e9657a7df6a8dc89c98`|
|63|44|1|-1|`0x80086EB4`|`0x8009D410`|`a3b6ef23a352485201dcbfb7712c2c5d2ed9d8c7af6b486ba765ba0df567c828`|`c938ecc1f0104e4b811000d8c72de4611451188a3f9c94f8b3ec4c56aca69df8`|
|86|55|1|-1|`0x80086F6C`|`0x8009D4A0`|`92489386adc01c17b160b32f508cf002b702ad0bc9e31d13b0ae2c0d97818651`|`e014b225e7759c354224338bfd94a302d7729a24c48b0dffd84b3f1d2c173a0c`|
|88|58|1|-1|`0x80086F7C`|`0x8009D4E0`|`c8b4670cfa1bfbdf6fc99fc792f9897f8fb4f718ef746d3a4231f07025a93df2`|`e5d8a6ae934aea2d4abff887162d156a585424cbaed8ff6a82edfd3d8b27d9e5`|
|92|61|1|-1|`0x80086F9C`|`0x8009D520`|`2e5922aa80e723ddf490eacce139865ae3669445038e193e93e025b8c7a782c3`|`9c47ea5cb0ae6428106217e603cdb35349434dca674abd975c9eaf952414e67e`|
|96|73|1|-1|`0x80086FBC`|`0x8009D5F0`|`f95768a99a200b6c0d89855ba9a9fe0c39402d6250fbeea7923703d1c648c93e`|`f7a9f2a8b4078dfb5d785dbb56c643f784ff18b4858f5c5cbdeb5eb2db332fa4`|
|100|75|1|-1|`0x80086FDC`|`0x8009D710`|`de0d157fa7fdfde0ab6f34a1632e73adafb921aab7d2f8166be15351e452d12b`|`9aaff1be4d8cc4e55f16c4d2431ae7b8157482d4d8ead08a3c154619281213c9`|
|107|83|1|-1|`0x80087014`|`0x8009D620`|`c0a56ed461ddbd1c84dc1a49c44db6d73b902c5a5eaaa726b9a0175e57281ae1`|`07211478836f1109d28b18cf9e0273fea88ffbc31ad2c9ee620bf32cbc44c78a`|
|108|84|1|-1|`0x8008701C`|`0x8009D630`|`7939130dfc1ffab84b2360858dd6e7bcfac62932ca27870f564b80161eb1c931`|`6f9d4d9494f1420ca003a2e4de4d69fcc38e1459d92136b14dfb6b500bd93d3e`|
|110|125|1|-1|`0x8008702C`|`0x8009D8D0`|`ce4d7044a0f57e83c9800512a2dd9e3acbd61007119a4cc0891bd9a007d099a0`|`17d08daf203b8db75e76abbaf08471d93d251b6ef25a4492c8783005ead0c6dc`|
|121|93|1|-1|`0x80087084`|`0x8009D690`|`f9fc49647027a5ca4a628fc5d33a31a70eb18e02aa08d02c85536766070d6f5e`|`e4082f186a33e51b6377406d444b5a49937bf58c5a36842a0100349812cf3b2a`|
|122|93|1|-1|`0x8008708C`|`0x8009D6D0`|`033efe859460e8035c8b85d7e20da33d392d86c026ba4606d6714e9ed433bd1a`|`8953659c6ea096b3f684409fe149cdebf2f846dcc204baca2411676de0e7e98f`|
|125|96|1|-1|`0x800870A4`|`0x8009D730`|`a77dc33e688878f793c9b03d91176cf4743bb7d17abd029201dbc7fee2b09d08`|`fcaae281c0f17c574b186cb16b15cfa499d32992bdb688e578abae641aaa3107`|
|127|99|1|-1|`0x800870B4`|`0x8009D750`|`701acffdc7ba3755328d04815109c832a2cbd9ad7aef8ef4b6ca3e1fcbd43fb7`|`0d888f1d851f8a2c7431828729fc9a25025c558ebd6e9e23d5961be7031a36bc`|
|147|42|1|-1|`0x80087154`|`0x8009D430`|`ee9bd47418f481a9da1af7953ef38c4e6e0b35cdfac3356faa95f70e51bab86d`|`5c3f21541c7b99a9b8d3922a4e3e970e04ef170885a729f425c94c7b09b5d558`|
|149|111|1|-1|`0x80087164`|`0x8009D7F0`|`ba64fe40d040ea5f44e4b880e9365fa23e5f5e4679025056b3b19ae9d605ce01`|`7b686749a4e8929e8fa01a2ec166a7d300bbcd3cb18f57f2d5ae6e73bed1029a`|
|150|112|1|-1|`0x8008716C`|`0x8009D810`|`8c1d7f71bc80b89a6dea08a274e8a038e47e19e6fd670c8b56bcd7ce5b6a286a`|`2639378b181468eabeb1a6e62957642244650b39c005199d9573edab588f2a33`|
|151|113|1|-1|`0x80087174`|`0x8009D830`|`df1d2cb52ab063aceec0a210ee09b70bebe90bddc3285451245fc78ceacc4a06`|`a579244e3755edf3df66a74e5864e2634a73ed214a460a799ea374abc3ec0371`|
|153|118|1|-1|`0x80087184`|`0x8009D860`|`5241f7cb963f528f778c27b649ebf934cdae9c68fb11c20213c843d60d4024c1`|`1fd2578aba1dcee2b838d2606107d416b37a912f9860e3e5d7f2f167ccac7419`|
|154|114|1|-1|`0x8008718C`|`0x8009D870`|`2fd456d30a98d329925344a05f5e592d4906e5b2f5abc15dd36ac833afdc17d0`|`a19ac015ec760d6c8176a808d77c9df0bb65d23345298d19f635945e282aa58b`|
|162|111|1|-1|`0x800871CC`|`0x8009D800`|`cfaf44a19239175e880b1c338f26662825b31f1f216c810dabacec09cf1366dd`|`98b170598b92905ade2a99cc60269903129d810335e7a16fdcddedd2ba5078b4`|
|163|112|1|-1|`0x800871D4`|`0x8009D820`|`668d32359bae89d2b3d7dc9d6f9a84fde111aa19cdd44ef0825ced00cc3351e7`|`04badab1cdd2e76b9805f535041d78b7602d16e0b959e64543ac0bef1841955a`|
|166|58|1|-1|`0x800871EC`|`0x8009D4F0`|`0203855c077aa24819c5bf7a628e56267c1a0fdc060701df08bfa91a3136f02d`|`1bd574799448c2996b81c20a8276efe35514953717eed147f948012362bfd10d`|

## Appearance limits and canonical corrections

Material visibility is partial or effectively absent for entries13,20,24,28,43,65,84,99,112,121. Vertex diagnostics support coherent shapes but do not prove native appearance. Entry112's current material view is blank despite inherited linked-face coverage notes. No alpha, material, exporter or renderer correction was made. Descriptive colour terms concern inspected pixels only. Bottle13 omits unsupported blue; paired red canisters61 claims no fuel contents; red-tipped scalpel118 claims no blood/injury; three coloured balls131 claims no juggling behavior. Neutral joint hierarchy for131/139 does not establish an activated pose or parent transform.

Exactly three canonical label/note corrections are admitted:

- Entry20: Milk carton becomes Lighter-fluid container. The exact linked pixels read LIGHTER FLUID beside flame icons; diagnostic geometry shows a rectangular container with spout. Material front/rear views remain partial. No actual contents/use claim.
- Entry123: Cleaver becomes Bone-handled knife. A pointed blade and bone-shaped handle support the descriptive label; handle composition remains unknown.
- Entry124: Cleaver with wrapped handle becomes Wrapped-handle knife. The pointed blade, pale wrap pattern and red band remain a distinct exact ROM/material identity from123.

All existing notes/caveats remain verbatim and the new evidence is appended. Old aliases and former full display labels are retained. Names, IDs, render cases, categories and paths are unchanged. The prior entry76 Red warning barrel correction is retained exactly. Former labels remain provenance, not support for stronger semantic claims.

Separate visual leads134 Anvil,138 Green two-button device and166 Light bulb remain excluded. The earlier bounded queries1..255 do not prove unused status or absence of indirect use. Action166 is a different namespace and positively requests model58 (Curved sword).
