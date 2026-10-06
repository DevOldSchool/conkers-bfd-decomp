# US static flag texture conflict

`03:0090:00` remains material-blocked on two of its 30 source faces. The
checksum-validated ROM explicitly requests a 16 × 16 CI8 image and a 256-entry
palette from flat 1637, whose entire decompressed payload is 160 bytes. The
reviewed placement loader and updater do not supply a texture conversion for
this conflict. This is a source-span limitation, not an ordinary missing CI8
decoder case. No exporter or material substitution is made by this audit.

## Stored image contract

The model has 40 vertices and a 504-byte display list beginning at model offset
`0x2A8`. Material run 1 covers source faces 16–17. These commands are stored in
the ROM; offsets below are relative to the model, not the list:

| Offset | Words | Meaning |
| --- | --- | --- |
| `0x350` | `FD500000 00000665` | Flat 1637, mode zero, 16-bit transfer image |
| `0x358` | `F3000000 0707F000` | Load 128 transfer texels: 256 bytes, DXT zero |
| `0x360` | `F5480400 00090240` | CI8 render tile, TMEM zero, 16-byte row stride |
| `0x368` | `F2402402 0043E43E` | 16 × 16 bounds |
| `0x370` | `FD100000 00400665` | Flat 1637, trailing 512-byte palette mode one |
| `0x380` | `F0000000 063FC000` | Load 256 palette entries through tile 6 |
| `0x388` | `FC127FFF FF17F23F` | Texture/shade colour; environment-dependent alpha |
| `0x390` | `DE000000 08000050` | Inherited render-state list at segment 8 + `0x50` |
| `0x3A0` | `06181A1C 001C1A1E` | The two affected triangles |

The inherited load-tile definitions are `F5500000 07000000` (tile 7, TMEM zero)
and `F5600100 06000000` (tile 6, palette destination). The previous material
loaded flat 2299; it does not provide the missing source bytes. The new F3
command writes the full requested 256-byte destination span, including the
96 bytes read beyond flat 1637's payload.

The shared relocation function `1510CE60` preserves the FD/F3/F5 command words.
At `1510CFD4–1510CFE4`, mode one computes `payload_base + payload_length - 512`.
For this payload, that is `payload_base - 352`. Thus the palette read spans
`[-352, 160)` relative to the payload, while the index read spans `[0, 256)`.
The missing bytes cannot be supplied by padding, a different TLUT mode, or
retaining prior TMEM contents without changing the stored command contract.
The current decoder correctly returns `direct-ci8-payload-span-unresolved`.

## Related rigged flag

Curated `01:0169:00`, labelled Red flag, also has 40 vertices and 30 source
faces and references exactly the same eight flat IDs: 1637 and 2293–2299.
Its run 6 uses flat 1637 for two faces with a different, complete contract:

```text
FD100000 00000665
F5100000 07000000
F3000000 0703F000       64 × 16-bit transfer texels = 128 bytes
FD100000 00800665      trailing 32-byte palette, mode two
F0000000 0603C000      16 palette entries
F5000200 00090240      four-bit render tile
F2002002 0003E03E      16 × 16 bounds
DE000000 08000050
```

The proven character path interprets this four-bit tile with TLUT as CI4,
using pixel bytes `[0, 128)` and palette bytes `[128, 160)`. This establishes a
valid use of the payload in that model. It does not establish a replacement
material for bank 03. The ordered vertices and face indices differ; the
character has a nine-joint rig and four exported animation Actions. No geometry,
pose, native draw-state or gallery equivalence is claimed.

## Reviewed placement and update path

The fresh ROM placement decode finds one static association: bank `0C`, scene
48, record 18, SHA-1 `0540aea929e5c7a88fbbb64984d9f7aca5be5543`. It has
`model_source = [3, 90]`, position `[-330, 440, -3802]`, rotation `[0, 0, 0]`,
and updater index 40 in word `+0x14`. At `80088E70`, the dispatch record is
`1511DF6C 00000000 00000000`.

The model default at `800A2AF8` is `0000000000001F4021000100`; its flags byte
at offset 9 is zero. The loader additionally sets bit `0x04` for updater 40
at `15003C64–15003C8C`, then reapplies it after loading defaults at
`15003F28–15003F34`. Effective initial object `+0x70` is therefore `0x04`.
The rewritten-display-list bit `0x02` remains clear. Renderer `151137D4`
selects the ordinary `DE` submission at `15113BE4–15113BF0`, using the list
pointer stored at object `+0x1C`.

The reviewed 2,068-byte updater `1511DF6C` initializes its private state and
changes transforms and interaction state. Its direct writes do not change
texture, model-list or material-command pointers. `1511DD98` selects interaction
sounds; `151D6970` only invokes its effect in scenes 50/51. The loader's
`15004AAC` calculates bounds, and `15004CE0` relocates selected MoveMem pointers;
neither changes texture formats or load sizes. These are bounded path findings,
not proof against every possible external runtime mutation.

## Precise capture requirement

A future positive capture should follow scene `D_800BE9F0 = 48`, placement 18,
and a submitted object with unsigned halfword `+0x54 = 90`. At submission
`15113BE4`, `s1` identifies the object. Let `P = u32(object + 0x1C)`:

- The affected pixel FD is at `P + 0xA8`; its relocated pointer is `u32(P + 0xAC)`.
- The palette FD is at `P + 0xC8`; its relocated pointer is `u32(P + 0xCC)`.
- The triangle command is at `P + 0xF8`.

Retain the actual submitted nested list, the complete 256-byte pixel and
512-byte palette source spans, and the effective segment-8 `+0x50` list.
Compare the commands with the stored contract before claiming a rewrite or
conversion. A pointer/cache hit alone does not prove the affected draw, and
captured out-of-payload memory would remain capture evidence rather than a
ROM-only texture source.

Neither existing `us-runtime-materials-all-states-with-textures` nor
`us-runtime-materials-character-draws` appearance index lists bank-04 scene 48
or bank-03 entry 90. This bounded index check does not establish that all saved
states lack scene 48. No saved-state corpus replay or live trace was run in that initial audit; the
controlled follow-up below records later evidence.

## Source guards and reproduction

US normalized ROM SHA-1: `4cbadd3c4e0729dec46af64ad018050eada4f47a`.

| Source | Bytes | SHA-1 |
| --- | ---: | --- |
| Bank 03 entry 90 segment 0 | 1,192 | `7cb3b131efeaf13ef8319d833e76db2513d3ec84` |
| Bank 01 entry 169 segment 0 | 2,552 | `ad0f94ad57d3d85587a3fe982adf4fa30e3c065a` |
| Flat 1637 | 160 | `7602be37c751d90cb285bd6f86dadcbff7b72e0a` |
| `150039E0` loader | 2,964 | `b7b5ae00e5b5a3c5a0d28ad82582a25479a3bc66` |
| `15004AAC` bounds | 324 | `edce0f24009d616637ad123c7f0327b0bb7609c2` |
| `15004CE0` MoveMem relocation | 112 | `ea153fbab42e3c903408560dbd468112772d536b` |
| `1510CE60` texture relocation | 652 | `9a12376e197e0ae05d6d351d5d538865aa7dcc68` |
| `1510D0EC` flat loader | 648 | `47b67aab9ed8a4eb1706ced5424981ff21373aba` |
| `151137D4` renderer | 1,204 | `95326ee5c7b73267556e889aedfdef799930e221` |
| `1511DF6C` updater | 2,068 | `8fef4a2b7c592c75017c197250ae59571b743dff` |
| `1511DD98` interaction sound | 468 | `e23370625c5620e6950d89c7882a0aea02f6190e` |
| `151D6970` interaction effect gate | 68 | `a22e748b787c5af361ec0c97351f3eb62753d069` |

The first eight code spans were independently compared word-for-word with the
retained raw US assembly over their full registered lengths. The final matched
function was reviewed in source and pinned to its ROM bytes.

Run from the repository root:

```sh
PYTHONDONTWRITEBYTECODE=1 python3 \
  build/assets/models/reference/review-followup-20261001/materials/static-flag-audit.py
```

The ignored reproducer verifies both source models, the exact load contract,
flat payload, nine code hashes, dispatch/default records and fresh placement.
It writes `static-flag-audit.json` beside itself. This audit leaves the two
material-blocked faces and both model identities intact. Reopen with a proven
runtime rewrite/conversion or complete source-span evidence, not another
texture-layout guess.

## Controlled scene-48 investigation, 2 October 2026

An isolated copy of Save-Game-13 was advanced using a source-proven pending
scene/mode/entry request. The original state and emulator UI were untouched.
The local pinned debugger core used native Angrylion/CXD4 execution, with no
scheduler completion shim or material/visibility changes. This is an engineered
scene request, not a naturally observed gameplay transition.

The valid scene-48 run reached 55 VI boundaries and 54 graphics-task headers
before the game transitioned to scene 26. Four complete initial tasks decoded
without unresolved addresses. Neither the target's updater nor a direct model-90
draw was observed. The retained probes do not contain model 90's object record,
so they establish no live flags or loaded-model claim for that target.

Fresh source examination identifies two initial gates in the exact placement:
record byte `+0x32 = 0` is copied to object `+0x4F`, and byte `+0x34 = 1` is
copied to object `+0x6E`. The candidate builder first rejects nonzero `+0x6E`,
then requires bit 0 of `+0x4F`. Thus camera proximity alone is insufficient for
this authored initial state. A normal activation or later mutation must be
proved before another targeted capture; no extra entrance scan is justified.
The material conflict remains unresolved.

Earlier failed attempts are excluded from target evidence: their virtual-memory
guards probed nonresident overlays and induced guest TLB exceptions. Corrected
guards read only proven resident spans and preserve PC/registers. The valid
results and the source-only gate proof are under
`build/assets/models/reference/resolution-goal-20261002/runtime/`, in
`scene48-bounded-result.json` and `scene48-source-initial-gate.json`.

## Exact scene-48 activation-program review

The scene's declared event is bank20 entry187, a22,202-byte program with
21,618 bytes before its native data boundary and584 trailing data bytes. The
unchanged recovery decoder rejects this nonzero data header. A separate,
source-pinned diagnostic retains the original bytes and uses the native
`150ADB50/54` header+8 data base as the code boundary. An independent review
reconstructs all3,515 instructions and97 complete native6 call packets, checks
branch boundaries and native arity/dispatch tables, and rejects changed input.
This is static syntax analysis, not execution or reachability proof.

Generic class3 operation0 can clear object+6E, while operation13 can change
object+4F. The exact flag placement has explicit ID19, requiring descriptor
`0x3013` for this route. The program does not provide such a direct packet:
its computed class3 cohort contains IDs1–17. Literal19 at program0x4F6
belongs to an actor-selector table; two other literal19 call arguments are
operation numbers. None proves activation of the static flag.

The bounded result supplies no new runtime replay or material admission.
A later activation claim still needs the actual target object and a submitted
display list. Evidence is retained in
`build/assets/models/reference/resolution-goal-20261002/runtime/scene48-activation-source/`,
including the separate diagnostic and independent review. The recovery helper,
ROM, exporter, gallery and gameplay state were preserved.
