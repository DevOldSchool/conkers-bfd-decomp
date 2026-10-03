# Reviewed US scene-prop model names

Historical checkpoint: the reviewed/named totals below count source-bound
descriptive labels, not confirmed semantic identities or distinct characters.
Gallery labels and source hashes do not establish human confirmation. The
[current confidence review](model_name_confidence_review.md) supersedes the
old reviewed/unknown naming status; source pins and validation history remain
evidence for their stated scope.

This source-only expansion adds 20 bank-04 descriptive model identities to the
[91-name character/object checkpoint](additional_character_semantic_registry_expansion.md),
for **111 reviewed names and 1,376 unknown models**. All 91 prior registry records,
including every consumer role and Haybot's sole model-specific branch, are
unchanged. No C, linked symbol, ABI, matching state, scene selection or asset changes.
The existing schema remains version 2.

## Source identity and visual evidence

The owned normalized US ROM is 67,108,864 bytes, SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, SHA-256
`32e6a8b970ec12ac5f782344945aa0c98a193832eefb687529d03bab6948714b`.
The [registry](../../config/model-semantic-names.json) pins every numeric bank,
entry, segment, source byte count, SHA-1 and SHA-256. Its reviewed complete-file
pin is enforced by [model_semantic_names.py](../../scripts/model_semantic_names.py).

Each exact canonical inspection pointer's `render_case` was joined to its
validation source, then to a ROM-only preview manifest's numeric bank, entry and
segment. Source paths select records; filenames do not prove identity. Bank-04
bundle descriptors and selected source bytes were freshly decoded from the owned
ROM and checked against the supported parser. All selected OBJ positions and
ordered faces, and all glTF triangle-corner positions and source RGBA, match the
fresh ROM geometry. Every texture image matches its manifest SHA-1; all 121
referenced preview dependencies and 20 render files were separately fingerprinted
and rechecked. Four actual contact sheets were inspected again for this expansion.
These are static source previews, not native frames or live observations.

The table uses decimal entries and segments. Canonical pointers select the prior
review leads; they are not independent proof of an exact name. Eighteen leads are
confirmed descriptively. The two marked corrections are evidence-led changes to
those leads, explained below. No fresh external reference pixels were inspected.

| Bank:entry:segment | Descriptive label | Bytes | Model SHA-1 | Canonical model index |
| --- | --- | ---: | --- | ---: |
| `04:0001:09` | Hanging pull ring | 1224 | `15b4ad1e03b2dcbe65d8b25a462c4ee23ff29160` | 331 |
| `04:0002:29` | Rock Solid lettering | 408 | `d4322997d3b25c33c1dc548689f0b01a02cd9e6e` | 81 |
| `04:0006:04` | Windmill blades | 7224 | `32108ff02ccffcb8dba4569bfd9347b60cf8a78d` | 318 |
| `04:0007:11` | Rusty metal hatch | 3992 | `c0285710721f5f1369e064eb031fd6704ea9f0a6` | 322 |
| `04:0010:06` | Lighter fluid can | 2024 | `e36e65beb7d5ec638459b825bc1af2d0f0215a3a` | 345 |
| `04:0016:20` | Mechanical grabber | 3800 | `b00579abb1f1de1eb259cb21c059a8516819d006` | 321 |
| `04:0019:13` | Diagram easel — circular plan | 2456 | `958cdf029986e0a8c139b1530de9a20a909b11a9` | 333 |
| `04:0020:09` | Wooden ladder (corrected) | 1416 | `608df209f27b92938fde1bdbec5ce71919e9f0c7` | 54 |
| `04:0023:08` | Metal grid platform | 4072 | `09ca9a76f092db6358e6272191ec7507dd19744f` | 324 |
| `04:0024:05` | Wooden door with metal fittings | 4952 | `5771979dfece3bdfaac31d346a63465591cab56c` | 323 |
| `04:0033:06` | Chainsaw | 3560 | `8bccca7cf6ab502fb62d9586d10346023b708f87` | 326 |
| `04:0035:15` | Vine-covered column | 10776 | `8425a2630d8b758cc87616fddaf462273e02afd2` | 316 |
| `04:0041:20` | Wooden bridge | 2728 | `4b236599e27fde9054b90f3f56361988bf11929a` | 337 |
| `04:0043:07` | Paris 200 km sign | 3560 | `18c57956a7c9289060cd8e71625f8f3fb685c5f6` | 336 |
| `04:0045:12` | Diagram easel — pipe plan | 3000 | `08a54b6e7bffc9ab652d6771a90ae73c72e83755` | 334 |
| `04:0045:13` | Wooden watchtower with red banner | 4072 | `8f3c50c4f772cfff0a9d44ec2fd888fb6ab04e1c` | 327 |
| `04:0054:05` | Paired metal gate | 3432 | `a929344c614d7edb0b01f3744cbfcc5cdab25bc9` | 325 |
| `04:0060:17` | Gold candelabrum | 7368 | `cf3eec760f991c9c4a7f2c0fddb05d46020cc2d6` | 314 |
| `04:0065:05` | Reinforced wooden door | 1672 | `4322e20e5b0c13eb4f1507fe4e8b6752522e4e30` | 343 |
| `04:0067:06` | Spotted egg dome (corrected) | 2744 | `42c1fbc9d5f1ff0844035f54e66be1350558b41d` | 329 |

Canonical model indices refer to `config/model-inspection.json#/models/<index>`.
Validation joins retain their existing render IDs and source/reference paths.
ROCK SOLID, PARIS 200 km and LIGHTER FLUID are legible source-art lettering; these
labels do not infer an original level title, real-world distance or behavior.
The other labels follow visible form: a branched candle stand, vine-covered
column, four windmill blades, metal grabber, hatch, doors, grid platform, paired
gate, toothed saw, tower, ring, two diagram easels, plank bridge, ladder and dome.
These are descriptive model identities, not original developer symbols.

## Two bounded canonical corrections

Only canonical records **54** and **329** change. Their stable names, render
cases, categories and other fields are retained, and their existing note caveats
are kept verbatim before the new evidence. Both old short labels and complete
old display labels remain searchable as explicitly marked **former-label**
aliases. No other canonical record or bank-01 egg label changes.

- `04:0020:09`: **Wooden post** becomes **Wooden ladder**. The actual preview
  shows two long wooden side rails and repeated horizontal rungs. Exact source
  rails span Y=-700..981 around Z=0 and Z=-95; the repeatable transparent rung
  material uses texture 2948, alongside wood-rail texture 7672. The evidence
  supports the ladder shape, not climbability or any gameplay function.
- `04:0067:06`: **Spotted egg** becomes **Spotted egg dome**. The cracked
  cream/brown rounded surface has purple spots and a broad cut lower edge.
  The exact source has 113 vertices and 94 faces, with Y bounds [-515,2].
  Collapsing split vertices by exact XYZ yields ten one-use boundary edges,
  all at Y=-515, and zero bottom-plane faces. This supports an open-bottom
  partial model, not a complete or closed egg, whole character, or equivalence
  to any bank-01 source.

Historical inspection-config SHA-256
`b43ebaff477fe60d72635866310daaec1181df6c630923bf6114aa50cbef9f98`
continues to describe the earlier canonical evidence in the prior character
reports. It is not silently replaced there. The two-correction configuration
has SHA-256 `ce0df225d335aaf59fd6b452c4494fe970bef11ba4a4c666178c4eb0f2802608`.
The former labels are historical search aliases, not additional identities.

## Complete placed-object route

All twenty sources are **later bank-04 segments**, not initial slots 0..3.
The relevant [placement consumers](us_model_scene_consumers.md) are followed
through the all-descriptor relocation and placed-object route:

1. `15007E14` calls `150031EC` before `15007E24` calls `150039E0`, with the
   same scene global. `150031EC` requests `[04, scene]` at `15003218..15003230`
   and retains the descriptor table at `800B0E50`. Its relocation loop handles
   every descriptor. The `<4` discriminator at `1500335C` separates initial-slot
   installation; no initial-slot renderer edge is assigned to these names.
2. `150039E0` reads `[0B, scene]` and `[0C, scene, 2]` placement tables.
   Records are 0x44 bytes; runtime pool objects are 0xA0 bytes. **All 22 witnesses
   here are bank 0B**, kind 1 or 2. The 511 decoded bank-0C child-2 records are
   kind 0 and refer to bank 03; they provide no bank-04 relationship here.
3. Placement `+0C` supplies the initial kind. Kinds 1/2 take `1500401C` and
   read `*(800B0E50 + 8 * placement[+10])` at `15004080..15004090`. Header
   `+0` becomes object `+1C`, the primary display-list pointer, at
   `15004130..15004138`. Model+0x28 is the vertex base; header+0x10/+0x08
   supplies object+0x44/+0x9C. Earlier same-kind/index records may reuse these
   same source-derived pointers. Reuse does not merge numeric identities.
4. `15112A80` groups contiguous objects using `object+70 >> 4`. Initial
   candidate gates test `+6E != 1`, `(+70 & 8)==0`, `(+4F & 1)!=0`, alpha,
   view, state and distance. Zero-mask groups are omitted at `15112EC0`.
   Surviving group indices enter the per-view list through `80089240`, with
   counts at `800DBEE8`. Every selected witness is a singleton group.
5. `151135C4` reads that count/list, computes `800DBEF4 + index*0xA0`, obtains
   the corresponding matrix and calls `151137D4` at `1511372C`. The renderer
   applies further opacity/pass gates. At `15113B80` it tests object+70 mask `0x02`;
   selected initial flags leave this bit clear, taking `15113BE4..15113BF0`
   and emitting `DE000000` with the exact object+1C pointer. Its alternate
   branch passes that same pointer to `150A50C0`; no alternate-path visibility
   is asserted for any selected source.

The five core full spans are included in each new record. Two previously pinned
shared consumer records (selector and renderer) are reused without changing
their roles. The loader's bank-04 role is separately bounded; its full identity
agrees with the earlier bank-03 consumer. The registry now has 44 unique complete
consumer spans and 685 references. Supporting context uses the remaining full
spans below; support is not prop-exclusive controller ownership. All 18 extents
were checked against active function sizes and fresh ROM bytes, then compared
word-for-word to independent original reference assembly. The five core spans
also agree with separate raw per-function assembly. Twenty-five instruction
windows were reauthenticated inside those full bodies.

| Function | End exclusive | Bytes | SHA-1 |
| --- | --- | ---: | --- |
| `func_150031EC` | `0x150034B4` | 712 | `ed48d58ffb38dab90c140a0d547dbdae13f3225a` |
| `func_150039E0` | `0x15004574` | 2964 | `b7b5ae00e5b5a3c5a0d28ad82582a25479a3bc66` |
| `func_15112A80` | `0x15113180` | 1792 | `7b060425a0e9d27a05fa6f7c819a8b0811c91552` |
| `func_151135C4` | `0x151137D4` | 528 | `04f7c62d81e7232c89b3309fdeade178adab34aa` |
| `func_151137D4` | `0x15113C88` | 1204 | `95326ee5c7b73267556e889aedfdef799930e221` |
| `func_151148A8` | `0x1511490C` | 100 | `982eaba37b6c1dba097b1c79a4acafeb014eead9` |
| `func_1511490C` | `0x151149AC` | 160 | `629429fa4dce5a8dfb8eab6df18755a557d07775` |
| `func_150A8050` | `0x150A81A0` | 336 | `9d826a49f8529b88a58d6e5c9455f61c87f6244c` |
| `func_150A7CB0` | `0x150A7D00` | 80 | `9b41e5a7ae2b80ac7139471fe9dcc4016d16937b` |
| `func_150A7A48` | `0x150A7B80` | 312 | `50a10c8988bdedf7c044f28a9c22e9edbb43e1c6` |
| `func_15019130` | `0x15019414` | 740 | `3a4612c396cab4d5fea684c240da2c509477bdac` |
| `func_15007B3C` | `0x150081E4` | 1704 | `5897d750e22cca5cfd3807a70361042faaf11c86` |
| `func_150045C4` | `0x150049A4` | 992 | `37dee925089b4581e1686a4aabefd610ad02694f` |
| `func_150195A0` | `0x150198FC` | 860 | `387af6476d77ef09b7b3251fc9c3743cdcadf0e0` |
| `func_151897A4` | `0x151898C0` | 284 | `2412bfe0600cf8fe34f5f15008a364d76bd80464` |
| `func_15113180` | `0x15113218` | 152 | `240ebd2300a14589b1a43df6572d0d161014fedb` |
| `func_15113218` | `0x151135C4` | 940 | `0eaadfc90c71ef62b8d64a04db07167432812e90` |
| `func_1510D8C0` | `0x1510D970` | 176 | `93a912bad5e9ddc0bebe3f683c48b2a06d31a773` |

## Exact static placement witnesses and limits

Bank is **0B** throughout. Scene, segment and record indices are decimal.
SHA-1 covers the complete 0x44-byte record. `Inactive` means the decoded
unchanged singleton cannot enter the reviewed candidate-list route because
initial inactive byte +34 is 1. `Unresolved` means these initial inactive/flag
checks do not exclude it; it does **not** mean visible or active at runtime.

| Scene / segment | Record | Initial object +70 | Initial route | Record SHA-1 |
| --- | ---: | --- | --- | --- |
| 2 / 29 | 23 | `0x0` | Unresolved | `d844898f832785462adcbebacc2f5ec4bfebbf18` |
| 60 / 17 | 11 | `0x0` | Inactive | `e4136d2d599bd766d4bf6c068c23d4ba99f63110` |
| 35 / 15 | 11 | `0x0` | Unresolved | `a8d015f42fb6d651ed645091724c9f48b8f0d4b7` |
| 6 / 4 | 3 | `0x4` | Unresolved | `456ec458f84efdcb186e5e94f933fcefe17661c5` |
| 16 / 20 | 14 | `0x0` | Inactive | `a7b3448614da499c914d10f5a8280e8270e8eee8` |
| 7 / 11 | 3 | `0x4` | Unresolved | `af9d8aa85bb58856a5447d4432619e444570bc8e` |
| 24 / 5 | 1 | `0x0` | Unresolved | `c38dcedffffb8c933ff3d1861172a1b45969843c` |
| 23 / 8 | 1 | `0x0` | Inactive | `4cdd83a455a1c9cdf8c5ec568ff7d08a352244b2` |
| 54 / 5 | 0 | `0x0` | Unresolved | `2d8f7ced840ef5903c5f23e564e2e304bb9c0c56` |
| 33 / 6 | 2 | `0x0` | Inactive | `6df8e3a50977846770fd1b3f11c9aee8a92b40b4` |
| 45 / 13 | 9 | `0x0` | Inactive | `5345951d04e9e7532eaac38084ba887189acf4fb` |
| 67 / 6 | 2 | `0x0` | Inactive | `445854fbe8900c298d3d66a5c30e834300fc4a3d` |
| 1 / 9 | 5 | `0x4` | Inactive | `0b92860b5d5210bce3339a9cba076c2e3a7ee233` |
| 19 / 13 | 7 | `0x0` | Inactive | `161dd95b9d2a83cd49c463ea74b778f1cf505f60` |
| 45 / 12 | 8 | `0x0` | Inactive | `cf28216b72ec8970a6f3c5dc1c6b3ef9b582fbdb` |
| 43 / 7 | 3 | `0x4` | Inactive | `d62fd5df518b89148e7c900013683dcafae0a81f` |
| 41 / 20 | 0 | `0x1` | Unresolved | `2106da10375d758beda14b76b8da14ae3e326e9e` |
| 41 / 20 | 1 | `0x1` | Unresolved | `f17da3653a3b09df482e44ef97850203d7823268` |
| 65 / 5 | 1 | `0x0` | Unresolved | `0c04cc8d82eccbbc2656c6ea9d18de50aad520c9` |
| 10 / 6 | 5 | `0x0` | Inactive | `6f2b1bb58006120d8cbe8d44719060bd7b835297` |
| 20 / 9 | 5 | `0x0` | Unresolved | `0cf7fda3f49a1d785281e920b030202c456c0eb9` |
| 20 / 9 | 6 | `0x0` | Unresolved | `7333fa1dd266e08c43dc3b567072079ba8e1d5ef` |

There are eleven initially inactive witnesses and eleven other witnesses.
Runtime activation, view, state, distance and draw-pass conditions remain
unresolved. `151897A4` separately calls `151137D4` through a supplied object
pointer at `15189868`; no selected identity is assigned to that route. Therefore
initial exclusion is not a claim of global invisibility or unused status.

- **Scene 45:** pipe-plan easel segment 12 / record 8 and tower segment 13 /
  record 9 are distinct models at identical identity transforms, both initially
  inactive. The unchanged static assembly selects the easel. Colocation does
  not establish simultaneous drawing, activation or mutual-exclusion logic.
- **Scene 60:** candelabrum segment 17 / record 11 is at the origin and initially
  inactive. The existing whole-assembly hold for detached elevated geometry
  remains. An isolated descriptive identity does not resolve that hold.
- **Scene 65:** door segment 5 / record 1 initially copies updater `151150B0`
  from dispatch row 22. Initialization `150045C4` clears that exact object+38
  pointer at `15004724`; callback+78 is already zero. No persistent controller
  name is supported, and no updater is renamed.
- **Scene 41:** bridge segment 20 has records 0/1 with positions
  [-644,500,-4660] and [1609,1050,-5879], Y rotations -29 and -118 degrees,
  and unit scale. Object+70 bit 0x01 causes separate copied vertex buffers.
  Initialization transforms those copies, while later candidate matrices use
  identity. Applying placement again to runtime vertices would double-transform
  them. Source identity remains unchanged.
- **Scene 54:** gate segment 5 / record 0 is at [0,0,3242], zero rotation, and
  scale **[0.75,0.75,0.75]**. This corrects an earlier research README's
  overgeneralization that every selected placement had unit scale. The frozen
  source JSON and ROM record already contain 0.75 and remain intact. All other
  selected source placement scales are [1,1,1]. The regression test checks the
  actual positions, rotations and scales of every witness from owned ROM bytes.

No scene selection, exclusion, scene card, validation path or scene association
is changed. Naming grants no extraction, material, runtime-observation, scene,
visibility, animation, lighting, fog, combiner or native-raster credit. The two
chainsaw sources remain distinct bank-03 and bank-04 identities. No gameplay
behavior or whole-character claim follows from any prop name.

## Reproduction and verification scope

```sh
python3 -m scripts.model_semantic_names --rom roms/baserom.us.z64
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s tests -p 'test_model_semantic_names.py'
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s tests -p 'test_scene_prop_semantic_names.py'
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s tests -p 'test_model_coverage.py'
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s tests -p 'test_model_coverage_rom_policy.py'
```

The source-only focused checks verify all prior records, exact new identities
and full consumer roles, the sole unchanged Haybot branch, two exact canonical
corrections with former-label aliases, every unchanged canonical field, and
unchanged scene-selection/validation inputs. The owned-ROM witness test checks
all 22 exact records and transforms; it is explicitly skipped without that ROM.
The full registry audit covers all 111 exact sources and 44 complete consumers.

Fresh complete coverage reports compare the guarded 91-name baseline with this
111-name proposal: exactly these twenty keys change from unknown to reviewed.
Every other model field and all 10,394 material-run rows, 232,162 source faces,
non-naming summary and per-bank fields, evidence availability, six texture
manifest paths/digests and other top-level fields remain identical. Neither
report supplies export or runtime-observation manifests. The registry digest
changes as intended. No game build, queue transaction, compiled-C comparison,
CURRENT/layout gate, commit or push is part of this metadata-only preparation.

The integrated 111-name checkpoint passed all 1,737 host tests (37
expected environment/tool skips) and all 1,737 ROM-enabled pinned-toolchain tests
(one optional validator skip), plus the byte-exact full US ROM build,
integrated game/data/rodata, progress and whitespace gates. Fresh integrated
coverage exactly equals the reviewed full-corpus report. Independent review
reauthenticated all 20 source/geometry/render joins, all 22 placement witnesses,
44 registry consumers and supporting spans, and the two bounded canonical
corrections. A five-function source-naming batch in the same checkpoint also
passed focused zero/layout and clean-batch gates; these metadata additions
contribute no C matches. Historical preparation audits must use their pinned
canonical snapshot or an explicitly authenticated mapping of the two corrections;
a failing setup guard is not evidence that a later mutation test reached its target.
