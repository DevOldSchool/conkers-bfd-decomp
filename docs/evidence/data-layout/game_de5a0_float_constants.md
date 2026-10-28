# US game_DE5A0 float constants

`func_150B10F0` compares an object with the object at `D_800CC2D0`: when that
object is within range and below a height-dependent limit, it computes a heading
with `func_1505A630`, may adjust a global height, and writes an offset through
`func_1505A184`. It loads seven per-function rodata constants with `lui`/`lwc1`
pairs. The checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`) contains big-endian
`44898000 44834000 3F333333 44898000 44548000 3DB851EC 3D3851EC` at
`0x8009F8A0`, exactly the single-precision values of `1100.0f`, `1050.0f`,
`0.7f`, `1100.0f`, `850.0f`, `0.09f` and `0.045f`; the game-data base is
`0x80082B20`. The repeated `1100.0f` occupies two entries, matching IDO's
per-use literal emission for this function.

With extern symbols the best candidate reached CURRENT (1862). The literals,
the raw local order, a single height/limit variable, and the `u8 *, s32, f32,
f32, f32, f32, s32` callee prototype for `func_1505E650` (its third and fourth
arguments are passed from FPU registers, as in `game_120950.c`) reproduce the
raw function (CURRENT 0). The generated `build/us/src/game/game_DE5A0.o` has the
32-byte `.rodata`
`44898000448340003f33333344898000445480003db851ec3d3851ec00000000`: the seven
constants in load order followed by four zero alignment bytes, with no data
relocations. The words from `0x8009F8BC` are loaded by later functions in this
unit through extern symbols and are not owned by this mapping.

`config/game/us-rodata.ld` places this pool in an INFO section at the original
address with `SUBALIGN(4)`, an exact 32-byte extent assertion and a 28-byte
payload-size symbol. `config/data/us.json` records the source owner and its
completed-path alias. The original data archive supplies the runtime bytes.

The function passed independent full-span `CURRENT (0)`, layout, progress and
whitespace checks. Clean batch verification remains the linked integration gate.
No reference assembly, compiler options or verifier rules changed.
