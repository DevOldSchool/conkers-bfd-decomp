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

Each full source object currently contains one 4-byte literal followed by 12
zero alignment bytes in its 0x10-byte `.rodata` input section. The linker consumes
that entire section into a non-ALLOC `INFO` output section at the original
address. Its 16-byte ELF envelope is retained for inspection; it is not appended
to or used to overwrite the loaded GAME data. The original checksum-validated
GAME data archive supplies the runtime bytes. The integrated code resolves its
literal references to the original addresses and is compared independently.

`__game_rodata_camera_camera_payload_size` and
`__game_rodata_18a8f0_payload_size` are each 4. `verify_game_rodata.py` compares
only those four bytes against ROM and requires the remaining twelve ELF bytes
to be zero. `config/data/us.json` records the source owner alternatives for the
section/payload; it does not grant ownership of the zero alignment envelope.
The next constants at `0x800A3530` and `0x800A6524` remain external ROM data,
including their existing users in these source files. The envelope overlaps
those numeric addresses in the ELF metadata, not in loaded output ownership.

Maintainer-approved extension (2026-10-17): `func_1515F0AC` loads the next
constant, `32767.0f` at `0x800A6524` (big-endian `46FFFE00`), and only a literal
reproduces its raw schedule. Because it follows `func_1515F040` in the unit, the
`game_18A8F0.o` pool is now `46fffe0046fffe00` plus eight zero alignment bytes,
and `__game_rodata_18a8f0_payload_size` is 8; the section size stays 0x10. The
camera placement is unchanged. The paragraphs below describe the original
review.

Future natural literals in either source may change the object pool's order,
contents or size. Keeping the same 16-byte size alone is insufficient: a second
nonzero word would fail the current zero-tail check even if the SIZEOF assert
still passes. Expanding the payload requires proving every intervening word,
its order, address and all affected references. Noncontiguous or reordered pools
may require separately proved section placement. Any change to these shared
placements/payload extents needs separate maintainer approval and data-audit,
full-span/layout/integration and full ROM validation. This review changes no
placement and claims no neighboring constants.

The camera helper retains its existing ABI and uses defined unsigned address
scaling/addition. The clamp's observed callers supply reciprocal integer
values and indices 0..2; the finite clamped range times 65536 fits signed32.
No compiler settings, original references, acceptance criteria or ABI change.

Historical branch acceptance passed on 2026-10-16: data ownership audit, ten-function
BATCH_COMPLETE, 2,696 tests with eight skips, progress and layout gates.
Independent byte comparisons reproduced the 2,072,880-byte GAME payload
(SHA1 90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5) and both original-assets and
reconstructed-assets 67,108,864-byte US ROMs (SHA1
4cbadd3c4e0729dec46af64ad018050eada4f47a). Each literal payload matched the
original ROM and each object's 12 alignment bytes were verified zero-filled.

Historical accepted publication: commit
`555402fd3932816ba0c03540964e0cd395e7dfae`, tree
`e430c4b8047383a494db470700b18af0a9628371` (prefix `e430c4b8`, verified with
`git rev-parse 555402fd3932816ba0c03540964e0cd395e7dfae^{tree}`). Its parent/tested
base is `a0e1bd680a6c1f9b2dac1809197d35fb5256569b`; the pre-publication validated
files were committed unchanged. The results above apply to that exact tree.
The review revision was published as commit
`dbedd671496fa3a9ee4191841e9fd3858621b814`, tree
`2c8655253987e74c3cec97351504c7614d7e5823`. Its validated snapshot preserved all ten accepted
function bodies and passed clean BATCH_COMPLETE (2,696 tests, eight skips,
184.140 seconds), full-span/layout/integration and independent GAME/full US ROM
comparisons with original and reconstructed assets. Its validation-manifest
SHA256 was `3f2b3a5b4c2f2d5b0dd6e326eebdaca5fc3daed9f1351fafb4b265c5b888c248`.

Commit `cfbdd7d3a331ce9591b8f8176d29180a21c39948` subsequently merged main.
The earlier branch results do not validate that combined tree or later heads.
This documentation cleanup changes no C, layout, compiler or acceptance rules;
it does not provide new GAME/ROM/asset verification of the combined tree. Run
the commands below on the intended merge head before relying on such evidence.

Reproduce using the repository's pinned toolchain and a locally supplied,
checksum-validated US ROM (never add the ROM or build reports to Git):

```sh
CONKER_JOBS=1 ./conker objdiff data-audit
CONKER_JOBS=1 ./conker verify-batch func_1507CD0C func_1517F7B4 func_1507EEB8 func_1504C8BC func_1517A84C func_151A8A78 func_1510D694 func_150AF200 func_151254F4 func_1515F040
CONKER_JOBS=1 ./conker build
CONKER_JOBS=1 ./conker build --assets
cmp build/game-reference/us/game.code.bin build/game-integrated/us/conker.game.us.integrated.bin
cmp roms/baserom.us.z64 build/us/original-assets/conker.us.z64
cmp roms/baserom.us.z64 build/us/conker.us.z64
./conker progress check
git -c core.whitespace=cr-at-eol diff --check
```

All three `cmp` commands must exit zero. Expected sizes and SHA1 values are
recorded above; `verify_game_rodata.py:rom_game_data()` independently rejects an
unrecognized original ROM before decoding the GAME archive.
