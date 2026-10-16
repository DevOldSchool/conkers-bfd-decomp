# Second matching batch: US scalar literals

The existing US functions func_151254F4 and func_1515F040 need natural C
floating literals to reproduce the original load scheduling. External scalar
loads were non-exact at CURRENT (120); the exact ROM literals each passed
independent full-span CURRENT (0), reviewed source-unit layout, progress and
whitespace through the canonical finish transaction.

| Function | Source | Span | Constant address | Bytes | Value |
| --- | --- | ---: | --- | --- | --- |
| func_151254F4 | src/game/camera/camera_camera.c | 160 | 0x800A352C | 3c8efa35 | 0.01745329238474369f |
| func_1515F040 | src/game/game_18A8F0.c | 108 | 0x800A6520 | 46fffe00 | 32767.0f |

Values were read using scripts/verify_game_rodata.py:rom_game_data(), which
checks US ROM SHA-1 4cbadd3c4e0729dec46af64ad018050eada4f47a before decoding
the original GAME archive. Its loaded data base is 0x80082B20. The respective
archive offsets are 0x20A0C and 0x23A00.

Each freshly compiled full source object contains one 4-byte literal followed
by 12 zero alignment bytes in its 0x10-byte .rodata input section. The INFO
placements retain the original loaded addresses without appending data to the
code payload. Payload extents are exactly four bytes; adjacent ROM data is not
claimed as padding. The existing verifier checks payload equality and zero
object alignment, and config/data/us.json records both active/done owner paths.

The camera helper retains its existing ABI and uses defined unsigned address
scaling/addition. The clamp's observed callers supply reciprocal integer
values and indices 0..2; the finite clamped range times 65536 fits signed32.
No compiler settings, original references, acceptance criteria or ABI change.

Final acceptance passed on 2026-10-16: data ownership audit, ten-function
BATCH_COMPLETE, 2,696 tests with eight skips, progress and layout gates.
Independent byte comparisons reproduced the 2,072,880-byte GAME payload
(SHA1 90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5) and both original-assets and
reconstructed-assets 67,108,864-byte US ROMs (SHA1
4cbadd3c4e0729dec46af64ad018050eada4f47a). Each literal payload matched the
original ROM and each object's 12 alignment bytes were verified zero-filled.

Tested base: a0e1bd680a6c1f9b2dac1809197d35fb5256569b plus this branch's
uncommitted changes. The validated source/configuration manifest SHA-256 is
e1b7822d3e0820e4d445c33d25884daa91a8efed927bb434ba2c09c024097698.
The manifest, complete command logs, independent byte-check script and final
checkpoint are preserved in the task-5 resume-evidence package. No compiler,
ABI or acceptance inputs changed during validation. These results are local;
no commit or publication was performed.
