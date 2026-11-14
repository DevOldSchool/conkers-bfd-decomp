# US game_179F30 effect setup constants

`func_1514D64C` fills an effect setup record before spawning it. Its raw HI16/LO16
pairs in `asm/nonmatchings/game_179F30/func_1514D64C.s` (`1514D690`/`1514D694`,
`1514D7BC`/`1514D7C0`, `1514D7C8`/`1514D7CC`, `1514D7D8`/`1514D7DC`) address the four
words 0x800A5DF4..0x800A5E03; no other reference function touches them. The
checksum-validated US game-data archive (ROM SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base 0x80082B20) holds
`358637BD 3F4CCCCD 3F19999A 358637BD` there, exactly `0.000001f`, `0.8f`, `0.6f` and
`0.000001f` (IDO emits one word per use). With `extern f32` symbols the deferred body
scored CURRENT 5162; as literals the function is `CURRENT (0)`.

The unit already owned the `func_1514EA1C` switch table at 0x800A5E20
([manual batch jump tables](manual_batch_jump_tables.md)). The new literals precede
it in function order, so the compiled `game_179F30.o` `.rodata` is 0x40 bytes: the
four literals at offset 0, the 0x28-byte table at offset 0x10 and 8 zero alignment
bytes. The words 0x800A5DE4..0x800A5DF0 stay extern reads of the matched
`func_1514D564` and 0x800A5E04..0x800A5E1C stay extern reads of later members, so
game_179F30 is a split unit: `scripts/split_game_rodata.py` splits it into
`.rodata.179f30_0` (0x10 at 0x800A5DF4, literal pool) and `.rodata.179f30_10` (0x28 at
0x800A5E20, table with HI16/LO16 sites at text offsets 0x1FB4/0x1FBC), each with an
exact linker size assertion, as described in
[game rodata literal sub-pools](game_rodata_literal_sub_pools.md).
`config/data/us.json` records both owners. No reference assembly, compiler flag or
verifier change is involved.

After `func_1514CA80` matched, its four jump tables precede this pool in the
object. The two sections above are now `.rodata.179f30_438` and
`.rodata.179f30_448` at the same addresses; see the
[game_179F30 jump tables](game_179f30_jump_tables.md).

## func_1514EECC particle constants (round-24)

`func_1514EECC` fills a particle setup record. Its raw HI16/LO16 pairs in
`asm/nonmatchings/game_179F30/func_1514EECC.s` address 0x800A5E48..0x800A5E57,
where the checksum-validated archive holds `3E19999A 3F333333 3ECCCCCD 358637BD`:
`0.15f` (loaded once and stored to two fields), `0.7f`, `0.4f` and `0.000001f`.
With `extern f32` symbols the body scores CURRENT 794 (frame 0x128); as literals
the function is `CURRENT (0)`.

`func_1514EECC` follows `func_1514EA1C` in the source, so the literals form a new
0x10-byte pool at object offset 0x470, right after the 0x28-byte table, and the
object `.rodata` grows from 0x470 to 0x480 bytes with no alignment tail. The
split layout gains the range `(0x470, 0x10)`, mapped as `.rodata.179f30_470` at
0x800A5E48 with an exact size assertion and a matching `config/data/us.json`
owner. The table ends at 0x800A5E48, so the pool is contiguous with it in the
ROM as well. The words from 0x800A5E58 (`D_800A5E58`, `D_800A5E5C`) stay extern
reads of later members.
