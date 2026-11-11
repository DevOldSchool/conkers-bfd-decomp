# US game_111670 effect literal pool

`func_150E5558` builds an effect packet from eight float constants at 0x800A1140..0x800A115C, in the order the raw code first loads them: two radian-to-degree factors, the packet size, three alternative field4 values, the field4C value and the random yaw scale. With extern symbols IDO allocates and schedules these loads differently (for example `$f12` and `$f0` swap around the 0x800A1148 load); float literals reproduce the raw instructions exactly.

The checksum-validated US game-data archive contains big-endian `42652EE0 42652EE0 3E2E147B 3F19999A 3E99999A 3E99999A BF47AE14 40933333` at 0x800A1140, reproduced by `57.295776f`, `57.295776f`, `0.17f`, `0.6f`, `0.3f`, `0.3f`, `-0.78f` and `4.6f`. ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base 0x80082B20.

The generated `build/us/src/game/game_111670.o` has a 0x20-byte `.rodata` equal to those 32 ROM bytes, with no alignment padding and no data relocations. Only `func_150E5558` references `.rodata`. Earlier unit constants (for example 0x800A1060 used by `func_150E42F8`) keep their extern symbols and are outside this mapping; the next ROM word at 0x800A1160 belongs to the following data and is not replaced.

The INFO mapping retains linked bytes for verification without appending to the code-only payload, and a size assertion detects constant-pool growth. The full registered instruction comparison reached CURRENT (0) with focused layout, progress and whitespace checks passed; the clean linked verify-batch result is recorded in the commit that adds this mapping. No reference assembly, compiler flag or verifier changes are involved.

## Spark constants (func_150E4E04)

`func_150E4E04`, the member before `func_150E5558` in text order, hoists five
loop-invariant literals: `815.0f`, `0.0001f`, `0.9f`, `0.315f` and `957.0f`.
With extern symbols IDO reloads them inside the loop (CURRENT 523); as literals
the function reaches CURRENT (0). The same checksum-validated archive holds
big-endian `444BC000 38D1B717 3F666666 3EA147AE 446F4000` at
0x800A112C..0x800A113F, immediately before the 0x800A1140 pool. The mapping
therefore starts at 0x800A112C: the object `.rodata` is 0x40 bytes, 0x34 of
payload (these five words followed by the eight words above) and 12 zero
alignment bytes. The word at 0x800A1128 stays the extern of the matched
`func_150E4928`.

## Leading literal (func_150E42F8)

`func_150E42F8` compares each sampled height with `-10000.0f`. The reference
loads the word once before the loop into callee-saved `$f20` (`lui`/`lwc1` at
text offsets 0x194/0x1A8 of the unit). The preserved candidate read
`extern f32 D_800A1060` and scored CURRENT 80; a `limit` local initialised from
the extern scores 280. With `limit = -10000.0f` as a literal the function is
`CURRENT (0)` with the reference's ten named local homes. The
checksum-validated archive holds `C61C4000` at 0x800A1060.

That word lies 0xCC bytes below the 0x800A112C pool. The words between
(0x800A1064..0x800A112B) are zero padding, a byte table and constants read by
other members through externs, including the matched `func_150E4928` word at
0x800A1128, and they are not part of either mapping. The object `.rodata` is
still 0x40 bytes: `C61C4000`, the 0x34-byte pool above, and 8 zero alignment
bytes. `scripts/split_game_rodata.py` splits it into `.rodata.111670_0`
(0x4 at 0x800A1060) and `.rodata.111670_4` (0x34 at 0x800A112C); see
[literal sub-pools](game_rodata_literal_sub_pools.md). The former 0x34
payload-size symbol is replaced by two exact section assertions. The
`extern f32 D_800A1060` declaration is removed from the source.
