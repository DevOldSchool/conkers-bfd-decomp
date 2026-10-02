# US embedded type-55/85 geometry sources

The five display lists selected by `151582C8` are independent, bounded geometry
sources in the US game data image. They are not entries in an indexed model bank.
The exporter preserves each list's native local positions, ordered triangle indices
and every vertex byte. It does not assign a material or claim that every selector
is instantiated during gameplay.

This evidence is for normalized US ROM SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. The supported backend is
[`model_embedded_type55.py`](../../scripts/model_embedded_type55.py). Its guards cover
complete consumer spans and exact descriptor, table, setup, teardown, list and
vertex bytes. Existing exporters and gallery records are unaffected.

## Native consumer chain

| Consumer | Full size | ROM/raw-ASM SHA-1 |
| --- | ---: | --- |
| Dispatcher `151674F8` | 1,392 | `1a4cc2434666765a39feb16096d26a83d4b8fcc3` |
| Constructor `151580B0` | 296 | `245f256fa6f56f8569af3c594f97fec803883e8f` |
| Renderer `151582C8` | 708 | `fbfe9a770dc1694858e8e48fc9e202480daca985` |

Every word in those full spans was independently compared with the raw US assembly
under `asm/nonmatchings/game_1944C0` and `game_185560` before implementation.

Constructor `151580B0` chooses object type 55 when the fourth argument's low byte is
zero, and type 85 otherwise (`151580E4..151580F4`). After successful allocation,
`15158128..15158134` copies exactly `0x44` caller bytes into object offset `0x10`.
Thus caller byte `+0x06` supplies renderer selector byte object `+0x16`. This
constructor proof does not establish a caller's values or any particular instance.

Both 52-byte descriptors, at `8008BFD4` and `8008C5EC`, contain renderer `151582C8`
at offset `+8`, setup list `8008ADD0` at `+0x10`, and teardown list `8008ADF0` at
`+0x24`. Their identical SHA-1 is `f5058a160bb3f1c6742d358d836f73577dca181a`.
The dispatcher submits the nonzero setup pointer before dispatching the descriptor's
renderer. The renderer has its own conditional callback/early-return path; the
presence of these descriptors is not visibility evidence.

The decisive submission at `15158550..15158574` writes `DE000000`, loads unsigned
object byte `+0x16`, shifts it left by two, reads the selected pointer from
`8008AFB8`, and writes that pointer as the display-list argument. The renderer does
not bounds-check that byte. The supported exporter accepts only selectors 0–4,
which are the five independently pinned source entries. This bound is an exporter
admission rule, not an invented native clamp.

The preceding matrix command uses object address `+0x58 + 64*D_800BE9C0`, where
`D_800BE9C0` is the frame-buffer index. The diagnostic does not bake that runtime
matrix or pretend the index is a camera/view selector.

## Exact source variants

The pointer table is 20 bytes, SHA-1
`f492873577f76671a15a3dcca17ba38cfa3d8be0`. Its order is significant:

| Selector | List address | Vertex address | Vertices | Triangles | List bytes |
| ---: | --- | --- | ---: | ---: | ---: |
| 0 | `8008AE60` | `800A6080` | 5 | 6 | 72 |
| 1 | `8008AEA8` | `800A60D0` | 4 | 4 | 56 |
| 2 | `8008AF38` | `800A6170` | 5 | 6 | 72 |
| 3 | `8008AF80` | `800A61C0` | 4 | 4 | 56 |
| 4 | `8008AEE0` | `800A6110` | 6 | 8 | 88 |

Each complete list begins with `E7000000 00000000`, then loads all its vertices
starting at cache slot zero. Only the explicitly ordered `TRI1` commands follow,
ending in `DF000000 00000000`. The earlier discovery scan began eight bytes after
each true list start; the exporter retains the leading pipe-sync command too.

Selectors 0 and 2 have identical positions and ordered faces, but different vertex
RGB. The same is true of selectors 1 and 3. These distinct source byte records are
preserved separately. Selector 4 has six red vertices, each with alpha 64. Every
source flag and signed ST is zero in this pinned cohort; those bytes are retained
rather than discarded or converted into fabricated normalized UVs.

## Diagnostic output boundary

For each selector, the backend returns the original vertex and display-list binary,
the selector table, both descriptors, setup/teardown binaries, and one glTF/bin
pair. The existing embedded-geometry command owns packing and output verification.
No raw source bytes are changed by packing.

The glTF uses only native-position `POSITION`, normalized unsigned-byte `COLOR_0`,
and the exact ordered indices. It has no material, normals, UVs, textures, skin,
animation or node transform. The source vertex RGBA bytes are not a native lighting
or combiner result: native geometry mode can also determine how the colour bytes
are interpreted. A default glTF viewer generally treats vertex alpha as opaque
without an explicit blending material. Selector 4's alpha 64 is therefore retained
as source data, not presented as a proved native-opacity rendering.

The setup list resets a matrix and enables texturing with a fixed scale; the renderer
also emits caller-dependent combiner/colour/OtherMode state and can perform texture
setup. Pinning that consumer boundary does not reconstruct all its material inputs.
These files make no claim about activation, native placement, lighting, opacity,
texture use, timing or pixel parity. A separate source-backed material investigation
can build on the exact geometry without modifying it.

Focused tests independently decode all five display lists using the existing
F3DEX2 model parser, compare literal positions/RGBA/ordered faces, and check exact
binary bytes after GLB packing. Mutation tests cover every pinned data byte, the
beginning/middle/end of every full consumer span, constructor/submission words,
invalid selectors (including booleans), and altered manifest geometry/provenance.

## Supported command and validation

Run `./conker model-assets embedded-geometry --primitive type55-0` to create
selector 0; replace its suffix with 1–4 for the other selectors. Add `--verify`
to compare an existing export with a fresh ROM derivation. Each default output
is `build/assets/models/embedded-geometry-type55-N/`.

All five create/verify pairs pass. Khronos validates the ten glTF/GLB files with
zero errors or warnings. Blender 5.2.1 imports preserve the exact positions
(up to its documented axis conversion), ordered faces and vertex colours
(maximum linear channel import error 1/255). All five diagnostic renders were
inspected. The 52 embedded tests and full 694-model-test suite pass. All 16
prior type-6/8/13 files remain byte-identical and their fresh verification passes.
Evidence is in `build/assets/models/reference/resolution-goal-20261002/embedded-type55/validation/summary.json`.

The separate material-source audit establishes that the observed source route
enables lighting; stored vertex colours therefore do not establish final native
SHADE. Its caller selects 0–3. A bounded wrapper/constructor/direct-allocator
audit found no route selecting 4, which remains an extracted source variant
without proved activation. No material, appearance or gallery promotion follows.
