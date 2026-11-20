# US effects_sight interpolation constant

`func_151CBC60` interpolates sight colours over 35 steps. Its raw HI16/LO16
pair in `asm/nonmatchings/effects/effects_sight/func_151CBC60.s` loads
`0x800AAEBC`, and no other reference function touches that word. The
checksum-validated US ROM (SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`,
game-data base `0x80082B20`) holds `3CEA0EA1` there, which round trips as
`0.028571429f` (1/35); the C source writes that literal.

The generated `effects_sight.o` has 0x10 bytes of `.rodata`
(`3cea0ea1 00000000 00000000 00000000`): the constant and 12 zero alignment
bytes, with no data relocations. The alignment bytes fall on `0x800AAEC0..`
(`0.01f`, `0.2f`, `4.2f`), which compiled functions in this unit read through
extern symbols such as `D_800AAEC0`; only the 4-byte payload is owned and
compared. `config/game/us-rodata.ld` maps the object as an INFO section at
`0x800AAEBC` with a 0x10 extent assertion and a 0x4 payload;
`config/data/us.json` records the owner. No reference assembly, compiler flag
or verifier change is involved.

## func_151C9BA0 switch split (round-23)

`func_151C9BA0` matched as a natural `switch` over cases 9..0x3B. Its raw dispatch
(`lui`/`lw` at text offsets 0x2A84/0x2A8C of the integrated object) loads
`jtbl_800AADBC_game`, whose 0x33 checksum-validated ROM words at
0x800AADBC..0x800AAE87 are the case targets `151C9C38`, `151C9C68`, `151C9C98`,
`151C9CB4`, `151C9D98`, `151C9DD4` and the default `151C9DC8`. The compiled table
emits the same targets as text-relative `R_MIPS_32` entries (default 0x2C14), and it
precedes the constant in text order, so `effects_sight.o` `.rodata` is now 0xD0 bytes:
the 0xCC table, the `3CEA0EA1` constant at offset 0xCC and no alignment tail.
The words between (0x800AAE88..0x800AAEBB) belong to other members and stay extern
reads. `effects_sight.o` joined `GAME_SPLIT_RODATA_OBJS`; `scripts/split_game_rodata.py`
splits it into `.rodata.effects_sight_0` (0xCC at 0x800AADBC, table sites 0x2A84/0x2A8C)
and `.rodata.effects_sight_cc` (0x4 at 0x800AAEBC), each with an exact linker size
assertion and a base symbol, replacing the former single 0x10 placement and its payload
symbol; `config/data/us.json` names both sections. The constant keeps its runtime
address, and the linked-payload verification compares both ranges with the ROM.

`func_151C899C` (also round-23) loads `491.0f`, `0.0605f`, `0.0523f`, `0.698f`,
`-0.44500002f` and `0.441f` from 0x800AAC58..0x800AAC6F (ROM `43F58000 3D77CED9
3D563886 3F32B021 BEE3D70B 3EE1CAC1`); no other reference function reads them. It
precedes `func_151C9BA0` in text, so its pool leads the object `.rodata` (now 0xF0
bytes: 0x18 pool, 0xCC table, 0x4 constant and 4 zero alignment bytes) as
`.rodata.effects_sight_0` at 0x800AAC58; the table and constant keep their runtime
addresses as `.rodata.effects_sight_18` and `.rodata.effects_sight_e4`.

## func_151C8FCC pool growth (round-29)

`func_151C8FCC` loads `30.1f`, `0.3f` and `0.000001f` from 0x800AAC70..0x800AAC7B
(checksum-validated ROM `41F0CCCD 3E99999A 358637BD`); its raw HI16/LO16 pairs
at 0x151C8FD4/0x151C8FD8, 0x151C9058/0x151C905C and 0x151C90E4/0x151C90EC are the
only reference reads of those words (`D_800AAC7C` belongs to `func_151C9198` and
stays an extern read). It sits between `func_151C899C` and `func_151C9BA0` in text,
so the compiled object places its three literals at `.rodata` offsets 0x18, 0x1C
and 0x20, directly after the `func_151C899C` pool and contiguous with it in ROM.
`.rodata.effects_sight_0` at 0x800AAC58 grows from 0x18 to 0x24; the object
`.rodata` is now 0x100 bytes (0x24 pool, 0xCC table, 0x4 constant and 0xC zero
alignment bytes), and the later ranges are renamed by their new offsets to
`.rodata.effects_sight_24` (table, sites 0x2A84/0x2A8C, still 0x800AADBC) and
`.rodata.effects_sight_f0` (constant, still 0x800AAEBC). The split layout, linker
sections, base symbols, extent assertions and `config/data/us.json` section names
follow; no text or reference assembly changes.
