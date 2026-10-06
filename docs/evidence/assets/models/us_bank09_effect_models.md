# Bank-09 effect meshes and emission points

The checksum-validated US ROM contains eleven four-pair meshes at bank-09
entries 173 through 183. Their native loader and shared display-list rules
recover 127 additional source triangles. Bank 09 now has 462 mesh containers:
296 direct, 155 attachment and 11 effect models. Across the four model banks,
the inventory is 1,487 source models and parts, not 1,487 complete characters.

## Four-pair container and native consumers

`func_15183ACC` loads `[9, 173 + index]` and exposes four offset/size pairs:
the primary vertices, an optional second vertex buffer, the material display
list and the geometry display list. The fourth size has the final-pair flag
`0x80000000`. Vertices use the ordinary 16-byte N64 layout. Both buffers are
decoded and retained; their initial contents are identical where both exist.

The wrappers `func_151838B0` and `func_15183974` reuse geometry lists from
adjacent records: entry 174 draws with 173's list, and 182 with 181's list.
`func_15183BA4` chooses the first material record matching the effect type in
`0x800A72D0`. The eleven type bytes are
`10,10,21,22,23,24,20,19,68,69,19`; thus 174 uses 173's material and 183 uses
180's material. Missing dependencies are errors, not empty-model successes.

The parser checks every header region, vertex extent, alignment gap and list
terminator. It combines the native material call, draw setup and geometry call
in their original order, then uses the shared geometry decoder. Source offsets,
raw list bytes, both vertex buffers and dependency hashes remain available for
reconstruction. It never searches inside opaque data for triangle signatures.

`func_151674F8` invokes the material callback at dispatch-record offset `0x14`,
then emits `D9FDFFFF 00000000` to clear lighting. The ordinary renderer
`func_15176DF0` calls `func_15142FBC(0x82CA0, 0x504A50)`, which emits
`EF082CAF 00504A50`. This establishes the OtherMode for entries 173 through
182 after their material lists. Entry 183 reaches a special branch of
`func_151770C8`; its inherited OtherMode remains unknown. The extractor pins
the complete consumer spans, selector table and relevant dispatch fields
against the decompressed executable and data from ROM SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`.

These defaults prove direct RGBA16 textures for 173, 174, 179 and 180, and
RGBA32 textures for 175 through 178. The RGBA16 path requires a complete
payload, zero-DXT LoadBlock, matching tile stride and disabled TLUT. Existing
indexed texture handling covers 181 and 182. The new partial E2/E3 OtherMode
decoder also retains which bits are known without inventing the other fields.

The previews include a bird, butterflies, a dragonfly and bats. These are visual
descriptions, not recovered source names. Runtime deformation, environment
colour, transparency interactions and native raster parity remain separate
questions; a valid static glTF does not establish those properties.

## Twenty non-mesh point sets

`func_151D2AB0` loads bank-09 records selected by twenty halfwords at
`0x800AB140`, then divides the decoded byte length by sixteen. The selected
entries are 432, 434..446, 448..452 and 433, in the preserved table order.
`func_1518F8E0` chooses a point, reads its matrix slot byte at offset zero and
three float coordinates at offset four, then transforms that position using
the actor's matrix array at `+0x1D4` with a 64-byte matrix stride.

These are skeletal particle-emission points. The other three bytes are
preserved without assigning them a meaning. Extraction writes all 1,963 points
to `us-bank-09/emission-points.json`; reconstruction covers 31,408 decoded
bytes. They are not added to mesh counts or the inspection gallery. Entry 447
has no selector in this consumer and remains unclassified.

## Verification

`./conker model-assets verify --bank 09` reconstructs all 462 model containers
byte-for-byte (629,000 decoded bytes) and separately checks the twenty point
sets. `extract --bank 09` retains the model regions and structured point data.
`preview --bank 09` exports the models through the existing glTF path. A local
file-read audit under `reference/expansion-20260910-two-hours/` regenerates the
bank while rejecting save-state, trace and captured-model inputs.

Synthetic tests exercise shared dependencies, command order, truncated and
overlapping regions, complete RGBA16 transfers, partial OtherMode updates,
finite point coordinates, reserved-byte preservation and reconstruction.
