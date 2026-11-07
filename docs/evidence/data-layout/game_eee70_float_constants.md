# US game_EEE70 dust burst constants

`func_150C1A40` spawns a dust burst and reads five float constants. The raw
HI16/LO16 pairs in `asm/nonmatchings/game_EEE70/func_150C1A40.s` address
`0x800A0210..0x800A0220`. The checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds
big-endian `408147AE 3ECCCCCD BF666666 3DCCCCCD 3F666666` there. These words are
reproduced by `4.04f`, `0.4f`, `-0.9f`, `0.1f` and `0.9f`, in the order the C
first uses them. With extern symbols IDO kept the 0.9f and 0.1f loads in place,
which swapped two saved float registers. As literals it hoists them as the raw code does.

The generated `game_EEE70.o` has 0x20 bytes of `.rodata`: these five words
followed by 12 zero alignment bytes, with no data relocations. The other unit
member, `func_150C1E34`, is still assembly; its double at `0x800A0228` keeps
its extern symbol. The zero word at `0x800A0224` is alignment padding before
that double. `config/game/us-rodata.ld` maps the section as INFO at
`0x800A0210` with a 0x20 extent assertion and a 0x14-byte payload, and
`config/data/us.json` records the owner. No reference assembly, compiler flag
or verifier change is involved.
