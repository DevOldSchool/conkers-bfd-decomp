# Conker US MP3 stream reconstruction

This library-only pass integrates `mp3/main.o`: four functions and 2,320
text bytes. The active search now accounts for 25 reconstructed archive
objects, 138 functions and 60,576 text bytes. The library goal remains active;
ordinary game-code implementation is outside its scope.

## Source family and bounds

Perfect Dark revision `169ed48bdcbfb3b568b028bd5bebb27680073514`,
`src/lib/mp3/main.c`, independently identifies the stream refill, frame reader,
stream initialization and continuation routines. Its `mp3/mp3.h` provides the
stream field layout, verified against Conker's accesses. The reconstruction
keeps this view local to the library. Source-family naming does not establish
Conker's original filename or original object membership by itself.

| Overlay offset | Function | Bytes |
| --- | --- | ---: |
| `0x1F7F60` | `mp3main00043dd0` | 296 |
| `0x1F8088` | `mp3main_read_frame` | 1,340 |
| `0x1F85C4` | `mp3main_start_file` | 236 |
| `0x1F86B0` | `mp3main_continue_file` | 436 |

All four functions match on the first candidate compile using IDO `-O1 -g2`.
Their complete text, including twelve final alignment bytes, covers
`0x1F7F60:0x1F8870` at runtime `0x151F7F60:0x151F8870`. The complete relocated
template occurs exactly once in the ROM-derived overlay. The preceding
routine returns at `0x1F7F58` with its delay slot at `0x1F7F5C`; the aligned
stream boundary follows immediately. The end is the independently identified
handwritten MP3 bit/Huffman utility family, beginning at `0x1F8870`.

The canonical map adds an archive boundary inside the former raw
`0x1F3DE0:0x1F8870` block. The existing cached comparison assembly remains raw
and unchanged. Regenerating the comparison map also converts the new archive
range to raw assembly, never to the candidate's compiled C.

## Conker differences

The source retains Conker's additional synchronization-byte check, which
accepts only `0xFF` or `0xF3` before applying the frame mask. The stream is an
external static instance at `0x800E1880`, rather than the reference's allocated
stream pointer. Initialization returns null if the initial frame read fails.
The separate reference-only initialization wrapper and counters are not
included in this four-function Conker interval.

Continuation follows the six-buffer frame ring and invokes the decoder
callback. When the frame's copyright bit is set, it reads a null-terminated
text record through the stream DMA callback, then forwards the record and
its length including the terminator through an optional external callback.
The byte-read loop, callback arguments, local array extent and resulting
stack frame all match the raw instructions. A failed frame read changes the
external MP3 state to 3 and returns zero.

## Object and external dependencies

Compiler-object MD5: `dbbda4bbbb4b5d5cc983d37e5fd42bb4`.
Resolved full-text SHA-1: `5c73afefeda51d0af7c8796ee6617fe71f51f706`.

The reconstructed object emits only `.text` of size `0x910`; it has no data,
rodata, BSS or COMMON allocation. All 32 relocations are resolved and checked:
20 calls and six HI/LO pairs. No instruction rewriting, copied ROM payload,
or data-pointer staging is used for this object.

External bindings are established independently from the raw call and data
references:

| Symbol | Runtime address |
| --- | --- |
| `bcopy` | `0x10023A10` |
| `bzero` | `0x100226F0` |
| `strlen` | `0x10022EEC` |
| `mp3util_get_bits` | `0x151F8960` |
| `mp3dec_decode_frame` | `0x151F78B4` |
| `mp3dec_set_side_info` | `0x151F6FD0` |
| `__conker_mp3_stream` | `0x800E1880` |
| `__conker_mp3_state` | `0x800E0E04` |
| `__conker_mp3_text_callback` | `0x800E0E00` |

Decoder, bit utilities and global storage remain raw. The current source
claims no original BSS ownership; its explicit external declarations do not
prove that the original Conker object emitted no BSS. The reference's static
arrays and initialization counters are not used to manufacture storage
bounds in this ROM.

## Verification

`./conker game-build --profile us` reports the complete integrated overlay
payload OK. The 2,072,880-byte output has SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`, exactly matching the independently
ROM-derived comparison payload. This is the gate that verifies the newly
linked MP3 implementation across the entire overlay.

`./conker build --profile us` also passes: the complete 67,108,864-byte US ROM
retains SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`. The main build preserves
the original compressed overlay asset; it does not claim to recompress the
newly built overlay. The independently identical overlay payload is verified
separately above.

All 25 objects in the active library research comparison pass. All 158 Python
tests pass; progress output is current and whitespace checks are clean. The
full library rebuild preserves every previously pinned object checksum.
The new regression checks the exact canonical MP3 extent and independent raw
reference generation. No function inventory or source-unit records changed.

Exact library text now totals 111,200 bytes: 92,368 in main and 18,832 in the
overlay. The active library leads still include the MP3 playback wrapper,
decoder and handwritten bit utilities, formatting helpers, RSP microcode,
and unresolved static-storage ownership. No ordinary game code was added.


## Playback-wrapper follow-up

The next review target is the complete preceding wrapper interval
`0x1F2960:0x1F3DE0` (5,248 bytes). Its fourteen entries are `0x1F2960`,
`0x1F2BA8`, `0x1F2BE8`, `0x1F2C4C`, `0x1F2CDC`, `0x1F2D6C`, `0x1F2DFC`,
`0x1F2E4C`, `0x1F2E88`, `0x1F39E4`, `0x1F3C1C`, `0x1F3C34`, `0x1F3C4C`
and `0x1F3D78`. Perfect Dark's `src/lib/mp3.c` supplies library lineage, but
Conker has material initialization, state-machine, DMA and mixer differences.
The wrapper is now reconstructed and integrated as a complete exact library
object; see [playback evidence](libultrare_us_mp3_playback_reconstruction.md).
The observations below record the original lead; they do not establish BSS
ownership.

The opening play routine lazily loads three Huffman assets and allocates the
power table. It calls main allocation/free helpers and the existing game asset
loader; those calls are dependencies, not authorization to implement game code.
Stop, pause, unpause, busy-query and volume changes bracket updates with
`osSetIntMask`. Conker adds a text callback setter at `0x1F3C1C`, and its DMA
callback checks for a null result, converts the returned physical address and
invalidates the data cache before copying. The prefetch length is `0x810`.

The raw global block starts at `0x800E0D80`; verified accesses put file size at
`+0x60`, DMA offset at `+0x64`, DMA callback at `+0x7C`, text callback at `+0x80`,
state at `+0x84`, volume at `+0x88`, current pan at `+0x94`, target pan at
`+0x96`, and the state timer at `+0x98`. The envelope update still uses the
reference's initial `0x30`-byte prefix. This is a partial layout observation,
not proof of the original object's BSS allocation or complete block size.
