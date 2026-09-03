# US VI and RSP library-boundary evidence

This note records the remaining reviewed library-shaped ranges at the end of
the US main executable. It separates an archive-backed stock VI helper from a
Conker-specific VI object and from the two RSP microcode blobs. The CPU raw
reference map remains authoritative even where an RSP blob crosses its
generated CPU `.text`/`.data` split.

## Inputs

- US ROM SHA-1: `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
- Pinned ultralib revision: `e24c836796df4bf520ff8b11a5c9d2cea3a66cbd`.
- GoldenEye source/checksum survey: revision
  `c4356466796c697dfd298010b9bed261f9ed8c6a`.
- Perfect Dark RSP and VI source: revision
  `169ed48bdcbfb3b568b028bd5bebb27680073514`.
- DK64 VI source: revision `2431154b417d4e80a6bfaf38291213c059be59f7`.
- Banjo-Tooie boundary map: revision
  `25033be6ec9e35975483f064d086391d2381ca4c`.
- Local Banjo-Kazooie boundary map: revision
  `9db90a003fff15d13d29505d571aff2543b50383`.

## VI object sequence

| US ROM range | VRAM range | Size | Identity | State |
|---:|---:|---:|---|---|
| `0x242B0:0x24400` | `0x800242B0:0x80024400` | `0x150` | Rare-modified `vi.o` / `__osViInit` | source/archive-backed |
| `0x24400:0x24410` | `0x80024400:0x80024410` | `0x10` | 2.0I `vigetcurrcontext.o` / `__osViGetCurrentContext` | archive-backed |
| `0x24410:0x24770` | `0x80024410:0x80024770` | `0x360` | 2.0I `viswapcontext.o` / `__osViSwapContext` | archive-backed |

The first range owns `0x2BD80:0x2BDF0` (`0x70`) of data. Its layout is the
standard two `0x30`-byte VI contexts followed by `__osViCurr` at data offset
`0x60`, `__osViNext` at `0x64`, `osViClock` at `0x68`, and one trailing word.
The function clears exactly the first `0x60` bytes, assigns the two context
pointers, selects the PAL, MPAL, or NTSC mode, stores the matching VI clock,
waits for vertical blank, and calls the adjacent `__osViSwapContext`.

This proves the complete `vi.o` text/data ownership, but no tested stock or
Rare-game object is byte-identical. GoldenEye, Perfect Dark, and DK64 provide
the same source family while leaving `osViClock` initialization elsewhere;
Conker performs it inside `__osViInit`. The local
`lib/libultrare/src/libultrare/io/vi.c` reconstruction compiles to exactly
`.text=0x150` and `.data=0x70`. Linking both sections at the reviewed locations
produces the byte-identical US ROM. Its complete object MD5 is
`e84b02761a0ffd9bf7224aac4f86d5d3`.

The selected PAL mode at `0x2BE30:0x2BE80` is also a complete Conker-specific
object boundary. Its common PAL timings overlap the Rare family, but its two
field records differ from the stock 2.0I-L and surveyed Rare-game objects.
`lib/libultrare/src/libultrare/io/vimodepallan1.c` reproduces the full
`.data=0x50` object (MD5 `68ed0c6c7829f56cd8fa9b2b8801ac83`) rather than
misidentifying it as a stock SDK mode.

The middle range has a complete 2.0I `.text=0x10` member with two relocations
to `__osViCurr`. The relocation target and its position between `vi.o` and
`viswapcontext.o` distinguish it from unrelated 16-byte return stubs. It is
now linked from the pinned 2.0I archive.

## RSP microcode boundaries

| US ROM range | Size | Identity | MD5 |
|---:|---:|---|---|
| `0x290D0:0x291A0` | `0xD0` | `rspbootTextStart:rspbootTextEnd` | `9414dd746eddee59ce6bf97eca16853e` |
| `0x291A0:0x2A110` | `0xF70` | Rare `n_aspMain` overlay 0 | `6864e8310f25c15951984eb993d41aca` |
| `0x2A110:0x2AAD0` | `0x9C0` | Rare `n_aspMain` overlay 1 / MP3 | `303b874b553871857297f5ba830841e7` |
| `0x2C960:0x2D4B0` | `0xB50` | Rare `n_aspMainDataStart:n_aspMainDataEnd` | `442fc9d7c4428c46e3ad08757c1524b3` |

`rspboot` is the standard SGI/Rare boot microcode. Its complete `0xD0` bytes
have the same MD5 recorded for GoldenEye US, EU, and JP `rspboot.o`, and its
instructions agree with Perfect Dark's matching `rspboot.s` source.

The audio microcode identity is independently encoded by the game task setup:
it stores `0x100291A0` as the task ucode pointer, `0x100290D0` as the boot
pointer, their difference (`0xD0`) as the boot size, and `0x8002C960` as the
ucode-data pointer. The data blob's first two overlay descriptors give text
file ranges `0x0000:0x0F70` and `0x0F70:0x1930`, proving the text end at
`0x2AAD0` and the internal overlay boundary at `0x2A110`. The exact descriptor
words are `00000000 0f6f1080 00000f70 09bf1238`: overlay 0 is loaded at IMEM
`0x1080`, while overlay 1 begins at file offset `0x0F70` and is loaded at IMEM
`0x1238`. The data layout then occupies exactly `0xB50` bytes through the end
of the main segment at `0x2D4B0`.

Perfect Dark's decompiled `asp.s` supplies the same two-overlay structure,
DMEM layout, dispatcher, DMA helpers, and MP3 overlay. Its instruction labels
also explain why the generated CPU map is misleading here. Perfect Dark's
variant starts its second overlay at `0xF80`; Conker's own descriptor is the
authoritative evidence for the different `0xF70` split above. Only
`0x291A0:0x292F0` was disassembled as CPU text, while the same RSP code
continues through `0x2AAD0` inside the generated data segment. DK64,
Banjo-Kazooie, and Banjo-Tooie independently name the related Rare binary
`n_aspMain`.

## Integration status

- `vigetcurrcontext.o` is a normal archive-backed 2.0I mapping and contributes
  its 16 bytes to matched build progress.
- The Conker-specific `vi.o` and PAL-mode objects now link from the verified
  `libultrare` snapshot. Their text/data placements, relocations, complete
  object MD5s, and the full-ROM checksum all pass; the `0x150` VI text bytes
  therefore contribute to archive-backed progress.
- `rspboot` and Conker's `n_aspMain` now assemble from `src/rsp/` into
  `librsp.a`; CPU function progress excludes these RSP payloads.

## Current-branch integration (2026-09-03)

The independently developed reconstruction from the isolated library worktree
was reviewed and brought onto the active branch without copying its unrelated
CPU, formatting or inventory edits. Source provenance and Conker-specific
instruction and data changes are documented in `src/rsp/README.md`; the upstream
MIT notice is retained in `src/rsp/LICENSE`.

armips v0.11.0 is pinned at `156f78f6bccfc07498578ac491ce7fe2a1e807a6`.
The child Docker image retains the existing CPU compiler and adds that assembler.
Its source build supplies the standard `<limits>` header needed by current
libstdc++, without changing the instruction encoder. The cache key includes the
base image ID, recipe and assembler revision.

`./conker rsp` assembles without reading the ROM, then independently verifies
its SHA-1, every payload's reviewed MD5, exact byte equality and complete output
ownership before replacing the archive. The four freshly generated payloads
match the ranges and MD5s in the table above: 6,656 code bytes and 2,896 initialized
data bytes. No payload is made by wrapping bytes extracted from the ROM.

`./conker build --profile us` then passes for the complete 67,108,864-byte ROM,
SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, with all four generated members
linked from `librsp.a`. Unlike a text-only comparison, this includes both audio
microcode overlays and their entire initialized data. The raw comparison map
stays unchanged, including its historical CPU split inside RSP code at `0x292F0`.
The active map follows complete RSP payload boundaries instead.

All 164 Python tests pass. RSP regression coverage rejects wrong reference hashes,
byte changes, truncation, extra assembler output, gaps or overlaps in payload
ownership, ROM incbins and accidental credit to CPU progress. The extra-output
check runs before same-named member slicing and preserves a previous archive
on verification failure. Progress output is current and whitespace checks pass.
