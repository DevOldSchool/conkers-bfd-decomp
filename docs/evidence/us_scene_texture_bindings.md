# ROM scene texture bindings

Four primary terrain models in bank 04 recover 26 texture runs on 236 faces.
Their 8,526 drawable faces retain source geometry and UVs. The exporter resolves
textures through reviewed scene consumers and ROM frame arrays; save states and
captures are not extraction inputs.

## Consumer chain

Evidence uses normalized US ROM SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`.

`150031EC` loads the scene's bank-04 bundle and stores its initial display-list
slots at `0x800B0E00`. `1510B9D0` conditionally selects the primary terrain draw.
When the branch controlled by its saved `sp+0x90` flag is enabled, scene index
`0x800BE9F0` selects a jump-table row at `0x800A2C2C`. The four reviewed rows call
these texture-binding helpers before submitting slot zero:

| Scene | Jump target | Binding helper | Pixel segments |
| --- | --- | --- | --- |
| 19 | `1510BB6C` | `150DFBD0` | 2, 3, 4 |
| 20 | `1510BB4C` | `150C8600` | 1 through 10 |
| 26 | `1510BB5C` | `15100464` | 2 through 8 |
| 51 | `1510BB8C` | `150D765C` | 2 through 7 |

Each helper obtains a flat asset through `1510D0EC`, then emits
`DB060000 | (segment * 4)` and the returned pixel address. Intervening
`1510F800`/`150A49F4` update clipping pointers; `1515D914` and its reviewed
helpers prepare lighting. They do not replace these pixel segments. The static
primary geometry's explicit texture loads and OtherMode remain authoritative.
Rewritten geometry and secondary terrain passes are outside this contract.

`scripts/model_scene_texture_bindings.py` verifies the complete reviewed
consumer spans and six ROM table regions before decoding contexts. The existing
validated ROM flat-asset loader supplies the indexed texture payloads.
Only segment zero of these four bank-04 entries receives scene texture state;
unrelated models do not inherit it.

## Selectors and inspection states

The tables establish alternatives; they do not identify the user's current
level state. glTF exports therefore record an explicit inspection state with
zero phase and inactive switches, rather than claiming an initial gameplay
frame. The native formula and all applicable flat indices remain in metadata.

- Scene 19 reads five words at `0x80090344`: inactive slots select flat 1894;
  active slots select 1895 through 1898 using phase 0 through 3. `150DF8C0`
  checks each slot's gameplay flag. `150DF920` calls `151749A0` with a four-frame
  cycle. Inspection selects the inactive branch for all three slots.
- Scene 20 reads two five-frame arrays through `0x80088810`, at `0x80090230`
  and `0x80090244`. `1500FE30` initializes segments 1–5 to type zero and 6–10
  to type one. `150C8600` clamps signed phase shifted by eight to 0–4.
  Inspection preserves these type groups and selects phase zero.
- Scene 26 reads three frames at `0x80090324`: segments 2 and 3 select
  `(phase >> 2) % 3` and its next frame. Segments 4–8 independently choose
  between the two words at `0x80090330`. Inspection selects frames 1547 and
  1548, with flat 364 for the inactive switches. `15100340` establishes the
  switch's two values and advances the shared byte phase.
- Scene 51 uses the same pair of five-frame arrays through `0x80088900`.
  Segments 2–5 use the first array; 6–7 use the second. It advances the selector
  by 13 for each segment before modulo five. At inspection phase zero the
  selected array indices are **0, 3, 1, 4, 2, 0**. Assigning frame zero to every
  segment would lose these native offsets.

Every candidate frame must decode with the same dimensions and sampled format
before any scene texture is linked. Source segmented addresses, source faces,
UVs, palette absence and explicit texture state are preserved. Only the proven
zero-offset pixel bindings are eligible. The manifest uses
`rom_scene_texture_state`; glTF uses `romSceneTextureState`, separately from
object texture animation, render-state consensus and captured materials.

## Verification

All four independent source exports have complete texture links. Numeric checks
compare their faces and UV corners with the ROM. An independent RGBA16 indexing
check matches 40,960 pixels across twenty unique frame images. Twenty-four
mutations of the actual code/table regions are rejected. Unit regressions
cover phase offsets, type groups, dispatch changes, bounds, incomplete frame
sets, invalid binding offsets and forged provenance/pixels/capture mixing.

The full Python suite passes 788 tests. Four preview renders were reviewed as
stone courtyard/sand pits, circular lava chamber, industrial hub/passages and
lava channels/bridges; these are descriptive labels. The gallery config uses
separate render baselines. Full validation independently reloads the ROM
contexts, re-decodes every alternative and checks selected PNG bytes and glTF
metadata. Native lighting, visibility, current gameplay state and raster parity
remain incomplete.

The completed batch passes all 5,406 file checks and 818 render cases, including
the four additions; eight existing render cases remain incomplete. All four
final GLBs pass Blender import and Khronos validation. All 1,596 previously
published GLBs and preview PNGs remain byte-identical. `publication-proof.json`
records the final counts, checks and hashes.

Local proof is under `build/assets/models/reference/scene-bindings-20260911/`:
`rom-proof.json`, `read-audit-bank04.json`, `preview-bank04/`, `recovered.json`
and reviewed renders. Current publication counts and remaining work are in the
[asset roadmap](../asset-roadmap.md).
