# US game_6B320 particle bounce constants

`func_1503ECA0` scales a landed particle's velocity by two float constants. The raw
code loads them with `lui`/`lwc1` from 0x80098928 and 0x8009892C, IDO per-function
literals rather than named globals: written as the literals `0.4f` and `0.8f` the
function reaches CURRENT (0).

The checksum-validated US game-data archive contains big-endian `3ECCCCCD` at
0x80098928 and `3F4CCCCD` at 0x8009892C, which `0.4f` and `0.8f` reproduce. ROM SHA1
is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base 0x80082B20.

The generated `game_6B320.o` has rodata `3ecccccd3f4ccccd0000000000000000`: the two
constants followed by eight zero alignment bytes, with no data relocations; only
`func_1503ECA0` references them. The words at 0x80098920 and 0x80098924 (used by
other `game_6B320` functions through extern symbols) and the string data from
0x80098930 are outside this mapping's owned eight-byte payload and are not treated
as padding or replaced.

The INFO mapping retains linked bytes for verification without appending to the
code-only payload, and a size assertion detects constant-pool growth. No reference
assembly, compiler flag or verifier changes are involved.
