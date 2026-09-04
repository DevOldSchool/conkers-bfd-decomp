# US type-4B display object and framebuffer helpers

Evidence kind: `structural_analysis`. Existing raw navigation intervals are retained as working source families; original filenames and exact historical compilation-unit boundaries remain unknown. No functions are implemented in C.

## Type `0x4B`: `0x10D970:0x10E670`

`1510D970` allocates type `0x4B` via `15167A68` at `0x10D9BC`, choosing size `0x128` or `0x13A`. It initializes orientation records and owner/control fields `+0x110`, `+0x120/+0x121/+0x124`. The owned type table at `8008B4A8`, stride `0x34`, gives row `8008C3E4`. Row update/draw/additional-render slots point to local `1510DA84`, `1510E120`, `1510E634` at `8008C3E4/8008C3EC/8008C404`. Update and draw consume the constructor's state; update directly calls the local vector/angle helper `1510E388`. The final callback emits the identity-matrix command. All five entries are accounted for by one constructor, its registered callbacks and its called helper.

## Framebuffer operations: `0x1D5E90:0x1D6970`

`151D5E90` and `151D6418` emit image/rectangle commands using common dimensions `800BE620/800BE624`. `151D61B0` processes a 16-bit image using those same dimensions and two-byte pixel stride; its external caller at `0x19AE0` passes the active framebuffer `800BE9C4`, then calls local `151D5E90` with that same framebuffer at `0x19AF8`.

`151D6778` owns the rendering lifecycle: it allocates `width * height * 2` bytes, stores the buffer at `800BE570`, calls local `151D6418` for an existing buffer, and calls local `151D5E90` for the current frame. `151D66F0` controls this mode using `800BE574/800BE575` and releases/clears that same buffer when disabled. The distinct pixel helper is included as part of this image-operation family, supported by the shared pixel geometry and framebuffer caller; adjacency alone is not treated as proof of an original object.

## Raw checks

Both ranges use existing 16-byte-aligned endpoints. All raw words match the owned US image, recovered entry spans exactly cover the ranges, and whole-image conditional-branch scanning finds no crossing edges. Independent CSV membership and beta correlations are recorded below. Correlations are supporting identity evidence, not source-boundary proof.

### `src/game/game_13AE20.c`

Range `0x10d970:0x10e670`; 5 entries, 3,328 bytes.
SHA-1: `1c46b2c19ddd61bc6309edcf6296a083955b08c1`.
debug: 2 correlations, 2 strong.
ects: 2 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1510D970` | `0x114` |
| `func_1510DA84` | `0x69c` |
| `func_1510E120` | `0x268` |
| `func_1510E388` | `0x2ac` |
| `func_1510E634` | `0x3c` |

### `src/game/game_203340.c`

Range `0x1d5e90:0x1d6970`; 5 entries, 2,784 bytes.
SHA-1: `ade52b17c2d41639c69f2d427bfde96aa2fae4ae`.
debug: 5 correlations, 5 strong.
ects: 1 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151D5E90` | `0x320` |
| `func_151D61B0` | `0x268` |
| `func_151D6418` | `0x2d8` |
| `func_151D66F0` | `0x88` |
| `func_151D6778` | `0x1f8` |

## Integration result

Passed the first integration attempt. The complete US game overlay remains byte-identical: 2,072,880 bytes; SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
