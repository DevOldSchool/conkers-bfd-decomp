# US game_1FA770 particle gravity constants

`func_151CD674` integrates a particle trail with two float constants loaded before its loop: a gravity term at 0x800AAFC0 and half of it at 0x800AAFC4. With extern symbols IDO allocates them to `$f0`/`$f2` and reorders the frame-rate address setup; float literals reproduce the raw `$f16`/`$f14` allocation and schedule.

The checksum-validated US game-data archive contains big-endian `BE828F5D BE028F5D` at 0x800AAFC0, reproduced exactly by `-0.25500003f` and `-0.12750001f` (the shortest decimal spellings of those bit patterns). ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base 0x80082B20.

The generated `build/us/src/game/game_1FA770.o` has rodata `be828f5dbe028f5d0000000000000000`: the two constants followed by 8 zero alignment bytes, with no data relocations; only `func_151CD674` references it. The earlier unit constants at 0x800AAFB4..0x800AAFBC and the later words from 0x800AAFC8 keep their extern symbols and are outside this mapping's owned payload; they are not treated as padding or replaced.

The INFO mapping retains linked bytes for verification without appending to the code-only payload, and a size assertion detects constant-pool growth. The full registered instruction comparison reached CURRENT (0) with focused layout, progress and whitespace checks passed; the clean linked verify-batch result is recorded in the commit that adds this mapping. No reference assembly, compiler flag or verifier changes are involved.
