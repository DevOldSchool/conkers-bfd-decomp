# Conker US MP3 decoder reconstruction

This library-only pass integrates `mp3/decoder.o`: nine functions, 16,768
text bytes and 20,928 bytes of complete data and rodata. The active search
now accounts for 26 reconstructed archive objects, 147 functions and 77,344
text bytes. Ordinary game-code implementation remains outside this goal.

## Source family and bounds

Perfect Dark revision `169ed48bdcbfb3b568b028bd5bebb27680073514`,
`src/lib/mp3/decoder.c`, independently identifies the decoder algorithms and
tables. The library-local stream layout is verified against Conker's accesses.
Source lineage does not establish Conker's original filenames or storage
ownership by itself.

| Overlay offset | Function | Bytes |
| --- | --- | ---: |
| `0x1F3DE0` | `mp3dec_init` | 1,288 |
| `0x1F42E8` | `mp3dec00040164` | 3,152 |
| `0x1F4F38` | `mp3dec_unpack_scale_fac` | 2,132 |
| `0x1F578C` | `mp3dec00041600` | 3,128 |
| `0x1F63C4` | `mp3dec00042238` | 1,452 |
| `0x1F6970` | `mp3dec000427d8` | 440 |
| `0x1F6B28` | `mp3dec_reduce_aliases` | 1,192 |
| `0x1F6FD0` | `mp3dec_set_side_info` | 2,276 |
| `0x1F78B4` | `mp3dec_decode_frame` | 1,708 |

The complete relocated text covers `0x1F3DE0:0x1F7F60` at runtime
`0x151F3DE0:0x151F7F60`, immediately followed by the already verified MP3
stream object. Its complete template occurs exactly once in the ROM-derived
overlay. All nine functions and all emitted allocated sections match using
IDO `-O1 -g2`; only non-runtime `.mdebug` metadata is removed.

Two candidate compiles were needed. Eight functions and both nontext sections
matched immediately. Conker's final frame decoder treats a zero refill return
as failure, where the reference checked minus one; correcting that condition
matched the final function and complete text.

## Conker variant and external storage

Initialization preserves the nine sine-window loops, relocates the 33 loaded
Huffman pointers and uses an externally supplied power-table allocation.
Unlike the reference, Conker loads Huffman assets instead of constructing
them here. It constructs the 8,192-entry power table with the ROM's iterative
recurrence and two 256-entry scaling tables by repeated multiplication.
The loop order, constants, failure return and stack layout match the raw code.

The object emits no BSS or COMMON. Workspace remains explicitly external:
the sine windows at `0x800E0E38`, power-table pointer at `0x800E1078`, and
scaling tables at `0x800E1080` and `0x800E1480`. Surrounding raw storage remains
intact. These external declarations do not prove that the original Conker
decoder object owned no BSS; original workspace ownership remains unresolved.

The bit/Huffman utilities and transform routines remain raw dependencies.
The power helper at `0x1504A400` provides a further independently reviewable
math-library lead. Calls to the reconstructed stream and decoder functions
now resolve to actual archive exports.

## Complete object evidence

Compiler-object MD5: `7257cd8f7d34bbdc0e6d3fd6f7a09819`.
Resolved full-text SHA-1: `0f8348f8d83fe1d945cd01ed1a7dee90709cc608`.
All 308 relocations are resolved: 61 calls, 107 HI/LO pairs and 33 data
pointer relocations. No instruction rewriting or ROM-derived replacement
payload is used.

| Section | RAM interval | Game-data interval | Bytes | Resolved SHA-1 |
| --- | --- | --- | ---: | --- |
| `.data` | `0x80091990:0x80091A20` | `0xEE70:0xEF00` | 144 | `7544c2cce15233b16f12e5fac67379793578528e` |
| `.rodata` | `0x800ABB20:0x800B0C50` | `0x29000:0x2E130` | 20,784 | `1e62bf97fa38168610bcf836126ce9c4faf79672` |

The data contains the complete 34-entry Huffman pointer list and two null
byte pointers. The rodata includes all independently sourced Huffman tables,
scale-factor, reorder, alias and rate tables, extra transform constants,
local constant arrays, floating literals and alignment. Unreferenced tables
are retained; no matching slices were cherry-picked.

Every byte of both complete emitted sections is compared after relocation
against the separately decompressed game-data payload (SHA-1
`42bbe7f02702ca7af5da499fb5cf2f34b7d3d23b`). The linker places these sections
at the verified RAM addresses with `NOLOAD` and exact size assertions because
the integration target contains only executable overlay bytes. This does not
claim to regenerate or recompress the game's data asset.

## Verification

`./conker game-build --profile us` passes for the complete integrated overlay:
2,072,880 bytes, SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`, identical
to the independently ROM-derived payload. The canonical map selects the
archive; cached comparison assembly remains raw, and regenerated reference
maps also convert this library interval to raw assembly.

`./conker build --profile us` passes for the complete 67,108,864-byte US ROM,
SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`. The main build preserves
the original compressed overlay asset. The newly compiled overlay is verified
separately through the complete payload equality above.

All 26 research objects match; all 158 Python tests pass. The archive rebuild
preserves every previously pinned checksum. Progress output is regenerated
and whitespace checks pass. No function inventory or source-unit record was
changed. Exact library text totals 127,968 bytes: 92,368 in main and 35,600
in the overlay. Remaining library leads include the MP3 playback wrapper,
bit and transform utilities, math helpers, formatting, RSP microcode and
unresolved static-storage ownership.
