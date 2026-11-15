# US game_FA360 drift float constants

The unit's rodata is one first-use literal pool at 0x800A0710..0x800A07A3, owned by three functions in source order.
The checksum-validated US game-data archive (ROM SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base
0x80082B20) holds exactly the single- and double-precision values of the C literals listed below.

- `func_150CCEB0` builds a drifting particle and randomises its offsets, sway and phase. It loads 15 words from
  0x800A0710..0x800A074B: `469C4000 C61C4000 3A83126F` three times (`20000.0f`, `-10000.0f`, `0.001f`, the offset
  written `+ -10000.0f`), then `3A83126F 44974000 38D1B717 464A8000 466E2400 38D1B717` (`0.001f`, `1210.0f`,
  `0.0001f`, `12960.0f`, `15241.0f`, `0.0001f`). IDO emits one word per use, which reproduces the duplicated ROM
  words. `206.0f`, `58.0f` and `360.0f` are built with `lui`. The function matched with extern symbols and keeps
  CURRENT (0) with the literals.
- `func_150CD17C` integrates a drifting object's position, applies per-frame drag in unrolled loops, and while the
  object falls sways it with `func_151436B4`, then wraps its phase into one turn. It loads the sway angle offset at
  0x800A074C (`3FC90FDB`, pi/2) and the phase wrap period at 0x800A0750 (`40C90FDB`, 2*pi). The raw function loads
  the period once and keeps it in `$f2` across both wrap loops, the literal-pool pattern; with extern symbols IDO
  reloads it after every store to the phase field (CURRENT 1235 for that candidate), while the literals match.
- `func_150CD7F8` spawns falling particles around the camera yaw. It loads `0.08f`, `0.992233f`, `-10.1175995f`
  (0x800A0754..0x800A075F), the doubles `8400.0` (`40C06800 00000000`) at 0x800A0760 and `2026.6800000000003`
  (`409FAAB8 51EB8520`) at 0x800A0768, then `0.59999996f`, `0.017453292f`, `0.39269912f`, `1613.5835f`,
  `2411.0085f`, `25.300001f`, `3.1415927f`, `0.15100001f`, `40.743664f`, `78.6f`, `25.2f`, `-1.108f` and `0.201f`
  (0x800A0770..0x800A07A3). The extern candidate scored CURRENT 1565; with the literals the function is CURRENT (0).
  `500.0f`, `180.0f`, `360.0f`, `1.0f` and `15.0f` are built with `lui`.

The pool must start at 0x800A0710. The doubles sit at 8-aligned 0x800A0760 directly after three floats, and IDO aligns
doubles within the object's `.rodata`. With the pool starting at 0x800A074C (4 mod 8, as when only `func_150CD17C`
used literals) the doubles would fall at object offset 0x14 and gain a 4-byte padding word that ROM does not have.
Starting from the 8-aligned 0x800A0710 the doubles land at object offset 0x50 with no padding, so no sub-pool split is
needed.

The generated `game_FA360.o` has 0xA0 bytes of `.rodata`: the 0x94-byte payload in load order followed by 12 zero
alignment bytes, with no data relocations. `config/game/us-rodata.ld` maps it as an INFO section at 0x800A0710 with
a 0xA0 extent assertion and a 0x94 payload; `config/data/us.json` records the owner. The alignment bytes fall at
0x800A07A4..0x800A07AF, over `D_800A07A4` (`3B808081`, 1/255) which a later function in this unit still reads as an
extern; they do not describe ROM contents and only the payload is compared. The preceding words through 0x800A070F
belong to the `game_F9430` pool and the extern reads of `game_FA240`. No reference assembly, compiler flag or
verifier changes are involved.
