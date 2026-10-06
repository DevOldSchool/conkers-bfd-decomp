# Remaining character alpha and colour state

The ROM-only audit `./conker model-assets alpha-frontier` reads bank-01
entries 154, 155 and 162, their flat payloads and the eleven segment-8 tables.
It verifies the complete loader and renderer instruction spans through the
existing character draw-table guards. It does not change exports, texture
alpha or gallery eligibility. The default report is
`build/assets/models/character-alpha-frontier.json`; `--entry` can select a
different decimal bank-01 entry.

## Source facts

| Model ID | Primary drawable faces | Textured faces with zero-alpha palettes | Texture-independent colour faces |
| --- | ---: | ---: | ---: |
| `01:0154:00` | 403 | 174 | 11 |
| `01:0155:00` | 314 | 186 | 14 |
| `01:0162:00` | 508 | 210 | 0 |

The 570 affected textured faces reference CI4 flat assets 903, 905, 914 and
926. Each trailing 32-byte RGBA5551 palette contains sixteen zero-alpha
entries. Palette offsets, payload hashes and palette hashes are retained in
the report. This establishes palette bytes, not effective draw alpha or a new
texture-load approval. Primary geometry and degenerate-face selection match
the existing exports; secondary geometry is not added.

The 25 colour-only faces use `FCFFFE8F F517F8FF`, whose two combiner cycles
contain no TEXEL0/TEXEL1 inputs. All eleven referenced table variants select
two-cycle mode. These faces already do not count as missing textures in the
batch report. Their primitive/environment colours and K5 still need effective
state evidence. Eleven of these faces also retain a zero-alpha palette
binding; they are counted only in the colour-only column above, since that
binding is not sampled by the combiner.

## Conditional renderer selection

The SHA-1-guarded `func_1502CCFC` range is 2,128 bytes, with digest
`2176c655198fed8b1867b28f059cb4765bced897`. The renderer's original stack
argument at `sp+0x10` supplies caller opacity; `sp+0x18` supplies draw mode.
After the function's stack allocation these are `sp+0x160` and `sp+0x168`.
The branches at `1502CF04–1502CFB8` establish:

| Caller condition | Segment-8 base | Display-list table |
| --- | --- | --- |
| Mode 3 | `800832C0` | Secondary |
| Mode 5 | `800832C0` | Primary |
| Other reviewed modes, opacity below 255 | `80082FC0` | Primary |
| Other reviewed modes, opacity 255 | `80083140` | Primary |

This is conditional code evidence, not a positive observation of any of the
three models with those arguments. The diagnostic limits its caller domain to
modes 0–5 and byte opacity. The full renderer guard also covers the later
primary/secondary selection at `1502D3C0` and submission.

For affected offsets `0x40`, `0x70` and `0x100`, table `80083140` uses
OtherMode low words `04D12078` or `04D12278`. `ALPHA_CVG_SEL` is set and
`CVG_X_ALPHA` is clear: coverage replaces combiner alpha without multiplication
by that alpha. FORCE_BL is clear and depth writes are enabled. The low words
in table `80082FC0` are `04D049D8`; they enable blending and do not select
coverage as alpha. The bit definitions and cycle-two blender mux layout are
in `lib/ultralib/include/PR/gbi.h`.

Consequently, zero palette alpha is insufficient to prove invisibility. It is
also insufficient to choose an opaque preview: the call's opacity and draw
mode are not established for these models. The diagnostic records every table
variant and raw blender fields without choosing a default. It does not claim
pixel parity for coverage, depth, lighting or blending.

## Concrete ROM spawn and selection routes

The audit also verifies twenty caller/constructor spans and three jump tables
against fresh ROM bytes. Its bank-0E scan covers 69 entries and 962 complete
`0x30`-byte records. All nine matching records occur in entry **60**:

| Model ID | Bank-0E record indices | Combined record indices | Initial XYZ |
| --- | --- | --- | --- |
| `01:0154:00` | 12 | 17 | `(39, -244, -6646)` |
| `01:0155:00` | 26–32 | 31–37 | Seven positions retained in the report |
| `01:0162:00` | 8 | 13 | `(66, 795, -339)` |

Indices are zero-based. Combined indices include five records copied from ROM
`1A33F0–1A34E0` before the bank payload; they are **not live actor slots**.
The decoded scene-60 payload has SHA-256
`7193517876bc28cd2dbfdad7b4c71d4087d9f2dfd739f9714d840c24896b394c`.
The report retains each complete record, payload hash, ROM span and prefix hash.
It rejects partial records instead of padding or guessing their bounds.

The consumer chain is concrete:

- `150169A0` loads bank `0E`, indexed by its scene argument, after that prefix.
  The generic `1502B8E0` call at `15016AA8` receives path length 2, bank 14 and
  the scene index; the returned size is divided by `0x30`.
- `15022398` can pass a selected combined record to `15082A44` at `150224B0`.
  This is conditional on activation state; ROM membership alone does not prove
  that the record is instantiated or visible.
- `15082A44` reads record byte `+4` at `15082A8C` and passes it to
  `150837D4` at `15082FA4`. The latter writes it to actor byte `+4` at
  `15083820`. Signed record halfwords `+6/+8/+A` become actor XYZ at
  `+14/+18/+1C`. The renderer reads actor byte `+4`; the existing bank-01
  loader/table proof establishes the model namespace.
- Modes 3, 4 and 5 can instead select a display model through `150849CC`,
  using the actor's alternate-model byte array at `+2C4`. A spawn identity
  therefore still needs correlation with the renderer's selected part table.

There is another conditional route for 154 and 155. Jump table `80096808`
maps player-selection values **36 → 154** and **35 → 155**. `150859AC` selector
1 reads the value from `800D213C + 28 * player_index`; `150169A0` writes the
corresponding model byte and actor-type byte 21 into an enabled player's
record. These are numeric selection cases, not proven menu labels or observed
player choices. Entry 162 has no matching case in this reviewed switch.

## Script activation routes

All nine target spawn records have byte `+2 = 1`. The ordinary spawn routine
`150825C0` returns at `15082634` for this value, before its distance or visibility
tests. Moving closer alone cannot instantiate these unchanged records through
that routine. This is a record-specific gate, not a claim that the models can
never be created by another constructor.

The script route bypasses that gate. `1501D1D4` requests ROM asset path
`[6, scene, script]` through `1502B6BC`. The generic loader traverses eight-byte
offset/size descriptors, decompresses the final asset, then relocates its child
pointers through `1502B4A8`. `1501D348` reads the first child's track count,
initializes each counter from its track size divided by eight, and points
`800C35F0[slot]` at the contiguous actor descriptors after the track children.
It sets the slot active and calls `15022848` at `1501DA54`.

`15022848` dispatches each track to `15022398`. A nonempty track with descriptor
halfword `+0 = 2` uses descriptor byte `+2` as a selector. `15083E0C` resolves it
against **spawn-record byte `+0x28`**, returning the first matching combined
record; selector zero returns no record. The audit includes the ROM prefix in
this lookup and does not equate selectors with model IDs or array indices.
`15022398` then calls `15082A44` if that record does not already have an actor.

Scene 60 has **16 populated script assets**, comprising 150 tracks. Their
eight matching initial descriptors establish these conditional routes:

| Model ID | ROM script path(s) | Track index | Selector | Combined spawn record |
| --- | --- | ---: | ---: | ---: |
| `01:0154:00` | `[6,60,7]`, `[6,60,14]` | 1 | 18 | 17 |
| `01:0162:00` | `[6,60,7]`, `[6,60,8]` | 3 | 14 | 13 |
| `01:0162:00` | `[6,60,9]` through `[6,60,12]` | 2 | 14 | 13 |

Script 7 is the strongest shared capture target: it references both 154 and
162. Script 14's target track has two eight-byte records; the other seven
matches have one. None selects the seven 155 records (selectors 32–38) through
this initial type-2 route. That bounded absence does not exclude later script
commands, actor replacement or the player-selection route.

The schema-3 audit retains every script's exact ROM span, decompressed hash,
track hashes, descriptor offsets and raw descriptors. It rejects unknown flags,
truncated or overlapping children, partial track records and noncontiguous
actor descriptors. It does not infer script titles, gameplay triggers, timing,
visibility or effective material state from membership alone.

For an immediate load, `1501D348` needs the requested scene to equal
`800BE9F0`, the selected slot byte at `800C35EA + slot` to differ from 1, and
the pending-script byte `800C35C4` to be zero. Its arguments are scene in `a0`,
script index in `a1` and slot in `a2`. Capture a natural call for scene 60,
script 7 first, then its submitted character draws. The upstream gameplay
event that supplies this script index remains unresolved; no RAM or program
counter override has been used as native appearance evidence.

### Upstream trigger boundary

The scene-volume route at `150A1CDC` calls `1501D348` with the current scene
and record word `+0x18` as script index. Its dispatch uses record byte `+0x15`
shifted right by two and the 26-entry table at `8009F5B0`; only class 13 selects
that script-start branch. `15017930` loads these `0x34`-byte records from ROM
path `[12, scene, 5]`. Scene 60 contains 120 records and **none has class 13**.
This rules out an unchanged ROM volume directly starting script 7 through
that branch, not later mutations or other activation paths.

The remaining data-driven lead is scene 60's event-program list: bank-15
entry 60 lists bank-14 entries **169–173** (bank numbers are hexadecimal).
The event interpreter reaches the class-1 callback `1509C440` indirectly
through `150AE12C` and table `800884D4`. The callback can request a script;
the event instruction and conditions that supply index 7 remain unresolved.
A code literal at `1515A2EC` is not evidence for that request: the later OR
with `0xC000` changes it to an unrelated packed value. Do not repeat that
literal scan or treat byte-pattern hits inside event programs as call proof.

The bounded ROM check, consumer hashes, trigger-class histogram and event
payload hashes are retained in
`build/assets/models/reference/character-activation-20260916/trigger-frontier.json`.
No new runtime trace or appearance promotion follows from this check.

## Opacity in the ordinary wrapper

`1502C974` obtains opacity from `1506196C`: multiply actor byte `+7` by byte
`+B + view_index`; return 255 only for `255 * 255`, otherwise shift the product
right by eight. A conditional override restores 255 when actor pointer `+318`
is non-null, its word `+2C` equals `0x100`, and the view index differs from
actor byte `+127`.

Mode 4 then multiplies this result by the byte at `800DF7C4` and shifts right
by eight **without** the full-opacity special case. Its maximum is **254**.
Thus a mode-4 call through this wrapper selects `80082FC0`, even when both
opacity factors are 255. Other callers remain governed by the renderer table
above; this does not forbid a different caller from passing mode 4/opacity 255.
The wrapper forwards opacity at stack `+10` and mode at `+18` to `1502CCFC`.
Visibility gates can prevent the call entirely.

`150615DC` initializes the opacity bytes to 255, but initialization does not
establish their value at a later draw. Part masks and colour tables are also
mutable. No constructor defaults are promoted into an appearance preset.

## Remaining work

Capture script **`[6,60,7]`** activating naturally, then a submitted draw of
154 or 162, including
draw mode, opacity, actor part masks at `0x94/0x98`, and emitted primitive and
environment colours. Existing character draw tracing already records caller
arguments, selected part identities and returned command ranges. A new trace
format is unnecessary. Colour resolution remains through `1502CC34` and its
runtime tables; a favourable segment-8 table alone does not fix colour state.

The existing 26-state corpus contains none of these IDs in its active, drawn,
selected-display-model or loaded-part-table identity sets. All 78 source trace
hashes were checked; its 71 completed calls are reusable bounded negative
evidence. The check is saved under
`build/assets/models/reference/character-alpha-callers-20260916/saved-corpus-check.json`.
Five supplied snapshots already have scene variable `800BE9F0` equal to 60:
`auto-save` and `save-game-5` through `save-game-8`. The ROM instructions at
`15007ECC–15007ED8` forward that variable to `150169A0`. Each snapshot's
72-record spawn array at `801CB570` contains the nine target records after
the five-record prefix; all 45 target-record observations are byte-identical
to the ROM. None of the five snapshots has an active target actor or a nonzero
target primary part-table pointer. This establishes a useful starting scene,
but activation or gameplay progression is still required before drawing them.
State hashes and record comparisons are retained in `saved-scene60-spawns.json`
beside the corpus check. No new replay was needed for this memory observation.
The additional read-only `saved-scene60-activation.json` check finds slot 0
inactive and no pending script in all five snapshots. Their nine target
per-record ordinary-spawn flags are zero; the ROM record's separate `+2` gate
still prevents ordinary spawning. Retained track counts in an inactive slot
are not evidence that its script is currently running.

Do not replay this unchanged corpus. Use the existing
`config/model-trace-character-draws.json` with a fresh scene-60 state; retain
the selected part identities and submitted command stream, including primitive
and environment colours, OtherMode and conversion state. This character-spawn
evidence does not resolve the detached geometry that holds back the scene-60
static assembly.

Until that evidence exists, keep the three models material-blocked and retain
the ROM palettes unchanged. Do not repeat a blanket zero-alpha scan or apply
an opacity override. The SHC Soldier attachment investigation is separate and
does not provide this caller evidence.

Validation: the fresh ROM audit reproduces the current 174/186/210 missing-face
counts. Focused tests cover opacity boundaries, mode-3/mode-5 precedence,
coverage-times-alpha distinctions, trailing palette offsets, changed alpha
bits, short payload rejection, changed-consumer rejection, signed spawn
coordinates, record alignment and wrapper opacity ordering. Gallery exports
are unchanged; this diagnostic does not require extraction or republication.
The 12 focused tests also cover script bounds/flags/layout, zero counters,
zero selectors, wrong descriptor types and first-match prefix shadowing.
