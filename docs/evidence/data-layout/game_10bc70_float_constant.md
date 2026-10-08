# US game_10BC70 float constant

The matched `func_150DE7C0` initializes two scale fields of its spawn packet with the same float. Its raw code loads `D_800A0D5C` once into `$fa0` and stores that value twice. The checksum-validated US game-data archive contains big-endian `44308000` at that address, exactly 706.0, reproduced by `706.0f`. ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; decompressed game-data offset is 0x1E23C relative to base 0x80082B20.

The literal is required for the register allocation, not only for the bytes. With an extern `f32` load, IDO promotes the global and gives it priority over the `1.0f` size constant, producing `$fv1` for the scale and `$fa0` for `1.0f`. As a literal written in two separate stores, it competes as a constant with fewer references than `1.0f`, so `1.0f` takes `$fv1` and the scale takes `$fa0`, as in the original. The neighboring `D_800A0D58` (0.18) keeps its external symbol reference and is outside this mapping's owned payload.

The generated `build/us/src/game/game_10BC70.o` snapshot SHA-256 is `cde9d43c43d77ab87a22e4438a850751415d5ca8eea4ca14e68a533d4c50e8f7`. Its rodata is `44308000000000000000000000000000`: one four-byte constant followed by 12 zero alignment bytes, with no data relocations. The sole HI16/LO16 reference pair appears at text offsets 0x1F0 and 0x1F4.

`verify-batch` ran `scripts/verify_game_rodata.py` against the checksum-validated `rom_game_data()` with section size 0x10, target address 0x800A0D5C and payload size 4. The ROM comparison and zero-alignment check passed. The INFO mapping retains linked bytes for verification without appending to the code-only payload. A size assertion detects unexpected constant-pool growth. Existing adjacent nonzero ROM values are not treated as padding or replaced.

The full registered instruction comparison reached CURRENT (0), with focused layout, progress and whitespace checks passed, and `verify-batch func_150DE7C0` returned BATCH_COMPLETE. No reference assembly, compiler flag or verifier changes are involved.
