# US game_11D830 float constant

The matched `func_150F0A24` initializes two fields of its effect packet with the same float. Its raw code loads `D_800A1854` once and stores that value twice. The checksum-validated US game-data archive contains big-endian `416E147B` at that address, exactly 14.880000114440918, reproduced by `14.88f`. ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; decompressed game-data offset is 0x1ED34 relative to base 0x80082B20.

The generated `build/us/src/game/game_11D830.o` snapshot SHA-256 is `8ffa27f634e684f6e987f8f907f309d37a84c553a17777cab771a8471bc3adce`. Its rodata is `416e147b000000000000000000000000`: one four-byte constant followed by 12 zero alignment bytes, with no data relocations. The sole HI16/LO16 reference pair appears at text offsets 0x168 and 0x16C. The other raw float constants at 0x800A1858 and 0x800A185C retain external symbol references and are outside this mapping's owned payload.

A read-only ELF32 audit used `scripts/verify_game_rodata.py` checksum-validating `rom_game_data()` and `verify_bytes` with section size 0x10, target address 0x800A1854 and payload size 4. The ROM comparison and zero-alignment check passed. The INFO mapping retains linked bytes for verification without appending to the code-only payload. A size assertion detects unexpected constant-pool growth. Existing adjacent nonzero ROM values are not treated as padding or replaced.

The full registered instruction comparison reached CURRENT (0), with focused layout, progress and whitespace checks passed. Clean linked verify-batch must still return BATCH_COMPLETE before this is reported as batch-verified. No reference assembly, compiler flag or verifier changes are involved.
