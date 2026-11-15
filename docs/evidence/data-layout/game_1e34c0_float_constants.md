# US game_1E34C0 wave float constants

The unit's rodata is a four-word literal pool at `0x800AA450..0x800AA45F`. The checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds `4101999A 40C90FDB 3F0E5605 3D79DB24`
there, the single-precision values of `8.1f`, `6.2831855f`, `0.55600005f` and `0.061000004f`.

- `func_151B6010` scales its spawn size by `8.1f`. It matched with the extern `D_800AA450` and keeps `CURRENT (0)`
  with the literal, which supplies the first pool word.
- `func_151B6254` advances a phase by `0.55600005f` per frame, wraps it into one turn (`6.2831855f`, loaded once
  before the wrap loop) and modulates a size by `0.061000004f` times the sine of the phase. Its raw HI16/LO16 pairs
  address `0x800AA454..0x800AA45F`; with extern symbols the candidate scored CURRENT 469, and with the literals the
  function is `CURRENT (0)`.

The generated `game_1E34C0.o` has exactly 0x10 bytes of `.rodata`, all payload, with no data relocations.
`config/game/us-rodata.ld` maps it as an INFO section at `0x800AA450` with a 0x10 extent assertion and a 0x10 payload;
`config/data/us.json` records the owner. The object has no alignment tail, so the following words from `0x800AA460`
are untouched; the `game_1E37D0` pool starts at `0x800AA470`. No reference assembly, compiler flag or verifier change
is involved.
