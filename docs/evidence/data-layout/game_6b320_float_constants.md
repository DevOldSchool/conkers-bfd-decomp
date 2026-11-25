# US game_6B320 particle constants

`func_1503ECA0` scales a landed particle's velocity by two float constants. The raw
code loads them with `lui`/`lwc1` from 0x80098928 and 0x8009892C, IDO per-function
literals rather than named globals: written as the literals `0.4f` and `0.8f` the
function reaches CURRENT (0).

`func_1503E5F8` builds an orientation from a direction vector: it compares the vector
length against an epsilon and converts the resulting angles to degrees. Its raw
HI16/LO16 pairs in `asm/nonmatchings/game_6B320/func_1503E5F8.s` (`1503E654`/`1503E67C`
and `1503E7CC`/`1503E7D0`) address 0x80098918 and 0x8009891C; no other reference
function touches them. Written as the literals `0.0001f` and `57.295776f` the deferred
body (CURRENT 3575 with extern symbols) reaches CURRENT (0).

The checksum-validated US game-data archive contains big-endian `38D1B717 42652EE0` at
0x80098918 and `3ECCCCCD 3F4CCCCD` at 0x80098928, which the four literals reproduce.
ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base 0x80082B20.

`func_1503EB78` (matched in round-30) sits between those two functions in the unit and
scales its two inputs by `0.02745098f` (`3CE0E0E1` at 0x80098920) and uses `-0.3f`
(`BE99999A` at 0x80098924). While it was deferred it read both words through the extern
symbols `D_80098920`/`D_80098924`, which left a hole between the two pools and made
game_6B320 a split unit (`.rodata.6b320_0` and `.rodata.6b320_8`). With the literals the
residual float-register swap disappears (CURRENT 0) and the pool is contiguous, so the
split is retired.

The generated `game_6B320.o` now has rodata
`38d1b717 42652ee0 3ce0e0e1 be99999a 3ecccccd 3f4ccccd`: the `func_1503E5F8` pair, the
`func_1503EB78` pair, then the `func_1503ECA0` pair, 0x18 payload bytes followed by 8
zero alignment bytes and no data relocations. These are exactly the ROM words at
0x80098918..0x8009892F. `config/game/us-rodata.ld` maps the whole object `.rodata` at
0x80098918 with a 0x20-byte section-size assertion and a 0x18-byte payload-size symbol;
the verifier compares only the payload. The string data from 0x80098930 is outside the
payload and is not treated as padding or replaced. `config/data/us.json` records the
single owner.

The INFO mappings retain linked bytes for verification without appending to the
code-only payload. No reference assembly, compiler flag or verifier changes are involved.
