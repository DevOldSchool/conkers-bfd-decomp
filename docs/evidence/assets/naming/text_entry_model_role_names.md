# Text-entry key model roles

`func_151EDF4C` has comment role `ui_text_entry_key_models_load`;
`func_151EE184` has comment role `ui_text_entry_update_and_draw`. Both remain raw;
`151EDF4C` retains its excluded `CURRENT (611)` candidate.

## Exact keys and input mapping

Bank-09 entries 453–482 are direct segment-zero models. The canonical numeric
source joins, independently decoded geometry/texture pixels and inspected glyphs
agree on the following identities. Resource slots, input characters and texture
indices are distinct domains.

| Entries | Resource slots | Visible key | Consumer action |
| --- | --- | --- | --- |
| 453–476 | 0–23 | A–X | Append ASCII `slot + 0x41` |
| 477 | 24 | DEL | Delete the previous character, if present |
| 478 | 25 | Dot | Append ASCII `0x2E` |
| 479–480 | 26–27 | Y/Z | Append ASCII `slot + 0x41 - 2` |
| 481 | 28 | Return arrow | Submit and evaluate the current text |
| 482 | 29 | Long blank key | Append ASCII `0x20` space |

The selection grid has four six-key rows, a five-key row, and a final one-key row.
Its normal-state text limit is nineteen characters, although the owner reserves
two 32-byte text buffers. The letter resources are not one contiguous A–Z range.
The thirty source models contain 300 faces and 362 vertices in total; entry 482
has fourteen vertices, and the others have twelve. No stored joint/animation
inventory is inferred for these direct models.

## Load and draw consumers

`151EDF4C` allocates `0x1A8` bytes and, if successful, places the thirty twelve-byte
records at owner `+0x40`. Each iteration requests indexed bank 09 entry `0x1C5`
through `0x1E2` using `1502B6BC`. The record retains the primary display list, model
allocation and dependency output. The owner allocation is guarded; individual
model-loader returns are dereferenced without a local NULL test and the texture
resolver's success result is ignored. Loading all resources is not guaranteed.

`151EE184` returns immediately if the resource-array pointer is NULL. Otherwise
it updates key selection, performs text insertion/deletion or submission, prepares
matrices, and emits all thirty primary display-list calls at twelve-byte strides
with bound `0x168`. Its selected key uses different matrix/environment state. It
also draws the current text and a conditional cursor. This is an update-and-draw
consumer, rather than a renderer-only function.

Submission compares nineteen character positions, padded with spaces, against
32 candidate columns from loaded string-table indices `0x90..0xA2`, under initial
mask `0xFFC3FFFE`. A match updates `D_800E9D00`; bits `0x400` and `0x800` are mutually
excluded by this path. Unmatched text is checked against a separate word table,
with distinct and repeated-submission feedback. There is no player-name or
persistent-save write in this function.

## Caller and table provenance

The decoded game data selects `151DE8F0` at `D_8008FDEC[3]` and `151EC3E8` at
`D_8008FFC0[3]`, linking initialization/update and drawing through the same UI
state. The sole direct game-code calls into the two named functions occur at
`151DE914` and `151EC4B0`, respectively. The draw route additionally tests active
object bytes `+0x3E == 0`, `+0x2C == 1`, and nonzero `D_8008FEF8`.

For that state, `151E51EC` calls `151E6964(1)`. The latter loads the nested indexed
route `(bank 0x1C, D_800BEAAB, subentry 0)` and builds `D_800E0BD8` from NUL-separated
strings. The middle selector is dynamic. Only outer entry 0 is populated in the
reviewed US ROM; its first subentry has 200 records, including the menu text
“Cheat entry” and the exact transposed rows used by submission. This supports a
code-entry role without claiming a captured selector value or invocation.

The adjacent `151EEBE8` follows a different image/rectangle route and does not
consume the thirty-key array. No key role is assigned to it.

## Stored appearance and runtime limits

The initializer rebases each opcode 01 vertex pointer and changes the first two
referenced vertex colors from source yellow to opaque black. It replaces stored
combiner `FC121824/FF33FFFF` with `FC127E05/FFFFF3F8` and stored
OtherMode `EF08AC3F/00552230` with `EF18AC3F/0F0A4000`. Draw-time selection adds
further environment-color/alpha and transform state. The inspected source
materials establish key/glyph identity; they do not reproduce these initialized
or dynamic materials, native lighting, blending or actual visibility.

Static caller/data-pointer scans describe reviewed code and data. They are not
proof against computed pointers or all other execution contexts. No exclusive
ownership, gameplay activation, named voice/character, player-name use or native
raster equivalence is claimed.

## Direct key-model source evidence

The thirty entries join exact preview-manifest, validation and canonical records
and original compressed extents. Geometry, ordered faces, UVs/colours and 31 linked
flat textures reproduce the reviewed source previews. Five contact sheets were
inspected; their glyphs support appearance descriptions, not confirmed gameplay
identities. Canonical “Letter block” labels and source paths are unchanged.

Every source has a 40-byte direct header and ten faces. Primary lists start at
232 except entry 482 at 264; list sizes are 208 bytes through entry 480 and 224
for 481–482. Normal keys span 40 units, return 80 and blank 240. Blank geometry
alone does not prove its space action. Grid rows are 6/6/6/6/5/1, with zero-based
slots in the mapping above; input bit `0x10` activates the selected action.
UI state 3, slot, bank entry, character byte and flat texture index are distinct.
Exact model hashes and the two complete consumers are in the registry.
