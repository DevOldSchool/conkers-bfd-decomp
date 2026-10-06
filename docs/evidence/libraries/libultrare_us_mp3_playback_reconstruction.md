# Conker US MP3 playback reconstruction

The complete Rare MP3 playback wrapper is integrated as `mp3/playback.o`:
fourteen functions and 5,248 text bytes at overlay offset
`0x1F2960:0x1F3DE0`, runtime `0x151F2960:0x151F3DE0`. This library-only search
now covers 31 reconstructed CPU objects, 165 functions and 88,384 text bytes.

## Source and boundary evidence

Perfect Dark revision `169ed48bdcbfb3b568b028bd5bebb27680073514`,
`src/lib/mp3.c`, supplies independent library lineage. Conker's complete
instruction sequence and call/data references establish the differences
below. The filename describes the reconstructed library role; it does not
claim recovery of the original Conker filename.

| Overlay offset | Function | Bytes |
| --- | --- | ---: |
| `0x1F2960` | `mp3_play_file` | 584 |
| `0x1F2BA8` | `mp3_stop` | 64 |
| `0x1F2BE8` | `mp3_pause` | 100 |
| `0x1F2C4C` | `mp3_unpause` | 144 |
| `0x1F2CDC` | `mp3_is_busy` | 144 |
| `0x1F2D6C` | `mp3_set_vol` | 144 |
| `0x1F2DFC` | `mp3_set_pan` | 80 |
| `0x1F2E4C` | `mp3_set_filter` | 60 |
| `0x1F2E88` | `mp3_make_samples` | 2,908 |
| `0x1F39E4` | `mp3_update_vars` | 568 |
| `0x1F3C1C` | `mp3_set_text_callback` | 24 |
| `0x1F3C34` | `mp3_set_dma_func` | 24 |
| `0x1F3C4C` | `mp3_handle_dma` | 300 |
| `0x1F3D78` | `mp3_dma` | 96 |

Eight final alignment bytes complete the object. Its resolved full-text
template occurs exactly once in the independently ROM-derived overlay.
The next boundary is the already reconstructed decoder at `0x1F3DE0`.
The canonical map uses the Rare archive; comparison-map generation retains
an independent raw-assembly range.

## Conker behavior and storage

Playback lazily allocates the power table and loads three compressed lookup
assets through existing game services. Successful allocations are pinned;
failure paths release the partial allocations. Those services remain external
dependencies. Stop, pause, unpause, busy-query and volume operations preserve
Conker's interrupt masking around state updates.

The reconstruction retains Conker's frame-restart path, two channel clears,
filter commands, and level-dependent cleanup. The filter initializer receives
22,020.0 Hz (`0x46AC0800`), and volume clamps to `0x7FFF`. Pan clamps to 0–127.
The DMA callback checks for a null result, converts the returned physical
address to the cached segment, invalidates the cache, and copies the data.
Prefetch requests use `0x810` bytes.

The source-local playback view starts at external address `0x800E0D80`.
The envelope prefix occupies `0x30` bytes; the filter view occupies the next
`0x30`. Verified fields include file size at `+0x60`, DMA offset at `+0x64`,
DMA callback at `+0x7C`, text callback at `+0x80`, state at `+0x84`, volume at
`+0x88`, pan at `+0x94/+0x96`, and the state timer at `+0x98`.

The reconstructed object emits only `.text`: no initialized data, rodata,
BSS or COMMON allocation. External declarations do not prove the original
object emitted no BSS. Original workspace ownership remains unresolved and
the raw storage allocation is preserved.

## Object and integration checks

IDO `-O1 -g2` produces the exact object; only non-runtime `.mdebug` metadata
is removed for reproducibility. Object MD5:
`d945c0c3356a429bd20ab7dcf4a40cc2`.
Resolved complete-text SHA-1: `4ca3738ba6dcfaf74dd5cab929a36f3f87c67f1d`.
All 450 relocations are reviewed and resolved: 52 calls and 199 HI/LO pairs.

Two compiled candidates were needed, preceded by one compile-only macro
name-collision fix. The second removes redundant terminal returns and uses
Conker's observed volume limit and filter rate. All fourteen functions and
the final padding compare exactly. The linker preserves the existing raw
caller name with `func_151F3C4C = mp3_handle_dma`; no game source changed.

`./conker game-build --profile us` passes the complete 2,072,880-byte overlay
comparison, SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
`./conker build --profile us` also passes the full 67,108,864-byte US ROM,
SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`. The main build preserves the
original compressed overlay asset; the independently identical newly linked
overlay payload is checked separately, without claiming recompression.

All 31 research objects compare exactly; all 164 Python tests pass. Progress
rendering and whitespace checks pass. Exact CPU library text totals 139,008
bytes: 92,368 in main and 46,640 in the overlay. Separate RSP payloads receive
no CPU-progress credit. Function and source-unit inventories are unchanged.

The library goal remains active. MP3 bit/Huffman utilities, formatting, the
preserved power candidate and external workspace ownership remain unresolved.
