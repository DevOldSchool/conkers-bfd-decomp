# Conker US N-audio main bus reconstruction

ROM `0x1FB40:0x1FFE0` is the complete 1,184-byte `n_alMainBusPull`
implementation. The source-family reference is Perfect Dark revision
`169ed48bdcbfb3b568b028bd5bebb27680073514`, `src/lib/naudio/n_mainbus.c`.
The earlier provisional `n_alSavePull` name described the wrong source family.
The Conker synthesizer calls this entry, then emits its own output-save commands.

The Conker routine conditionally requests MP3 samples, clears an additional
auxiliary buffer, orders buses by the output-filter setting, mixes stereo
according to two external routing arrays, and applies the reviewed driver
filter coefficients and state. These changes require the Conker implementation
in `lib/libultrare/src/libultrare/audio/n_mainbus.c`.

The second C candidate, using the established IDO `-O1 -g2` flags, reproduces
every text byte after resolving relocations. The first candidate initialized
the bus index before the MP3 block; moving that initialization after the block
reproduces the retail instruction order. Normalized object MD5 is
`8fe243e53dc86ec6dd3a873bc6556b39`. The complete text template has one occurrence
in the main executable. The object has no nonempty data, rodata, or BSS section.

The MP3 flag at `0x800E0E04` and routing bytes at `0x800428C4/0x800428C6`
remain external; this reconstruction does not claim their original allocation.
The MP3 sample routine executes at `0x151F2E88`. The main linker uses alias
`0x851F2E88` for the same JAL low 28 bits because the main image is linked at
`0x80000000` and executes in the `0x10000000` mapping. The driver's math-helper
call similarly uses linker alias `0x850484A0` for runtime `0x150484A0`.

The canonical map links the whole text section from `libultrare.a`.
The independently generated comparison map remains raw. No existing raw
source-unit inventory was associated with this interval.
