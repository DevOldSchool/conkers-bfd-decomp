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

The generated `game_6B320.o` has rodata `38d1b717 42652ee0 3ecccccd 3f4ccccd`: the
`func_1503E5F8` pair then the `func_1503ECA0` pair, 0x10 bytes with no alignment
padding and no data relocations. The words at 0x80098920 and 0x80098924 (used by
the deferred `func_1503EB78` through extern symbols) lie between the two pools, so game_6B320 is a
split unit: `scripts/split_game_rodata.py` splits it into `.rodata.6b320_0` (0x8 at
0x80098918) and `.rodata.6b320_8` (0x8 at 0x80098928), each with an exact linker size
assertion, as described in [game rodata literal sub-pools](game_rodata_literal_sub_pools.md).
The string data from 0x80098930 is outside both ranges and is not treated as padding or
replaced. `config/data/us.json` records both owners.

The INFO mappings retain linked bytes for verification without appending to the
code-only payload. No reference assembly, compiler flag or verifier changes are involved.
