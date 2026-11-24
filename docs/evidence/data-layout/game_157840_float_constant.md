# US game_157840 depth blend constant

`func_1512B1B8` samples a depth row on both sides of a screen column and
blends two owner fields toward the sampled values:
`owner->unk_60C += (...) * 0.05f` and `owner->unk_610 += (...) * 0.05f`. The
raw code loads the factor once with `lui`/`lwc1` from `0x800A3678` and keeps it
in a callee-saved float register, an IDO per-function literal rather than a
named global.

| Address | Word | Literal | Use |
| --- | --- | --- | --- |
| `0x800A3678` | `3D4CCCCD` | 0.05f | both blend statements |

The word was read from the checksum-validated US ROM (normalized SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) with
`rom_game_data` from `scripts/verify_game_rodata.py`. No other reference
function reads it. As the extern `D_800A3678` held in a local the deferred body
had the wrong frame and saved-register order; written as the literal twice the
function is `CURRENT (0)`.

The words from `0x800A367C` (`3BA3D70A` 0.005f, `3DCCCCCD` 0.1f, ...) are read
by later, still unmatched functions of this unit through extern symbols and
are not owned by this mapping; when those functions use literals the extent
must grow. The generated `game_157840.o` has rodata `3d4ccccd` followed by 12
zero alignment bytes, with no data relocations. `config/game/us-rodata.ld` maps
the object `.rodata` at `0x800A3678` as informational data with `SUBALIGN(4)`,
a 0x10-byte section-size assertion and a 4-byte payload-size symbol; the
verifier compares only the payload with the ROM.
