# Conker US RSP source

`rspboot.s` and `asp.s` derive from `src/rsp/` in
[n64decomp/perfect_dark](https://github.com/n64decomp/perfect_dark/tree/169ed48bdcbfb3b568b028bd5bebb27680073514/src/rsp),
revision `169ed48bdcbfb3b568b028bd5bebb27680073514`. The upstream MIT notice is
retained in `LICENSE`. Original source annotations containing Perfect Dark ROM
addresses and instruction words have been removed; instructions remain symbolic
RSP assembly. Local `.L040...` labels retain their upstream identities, not
claims about Conker addresses. `rspboot.s` is otherwise unchanged.

Build with `./conker rsp`. armips v0.11.0 is pinned to commit
`156f78f6bccfc07498578ac491ce7fe2a1e807a6` in `toolchain/tools.lock.json`.
`toolchain/rsp.Dockerfile` adds it to the digest-pinned CPU toolchain without
changing IDO. The assembler build explicitly includes `<limits>` for GCC 13
compatibility; its upstream source is unchanged. The child-image cache key includes the base image ID, recipe and
assembler revision. Assembler output has no ROM input. The build verifies the
owned ROM SHA-1, the four independently reviewed range MD5s, exact byte equality,
and complete output ownership before atomically replacing `librsp.a`.

## Conker audio variant

Overlay 0 loads at IMEM `0x1080`; overlay 1 at `0x1238`. File offsets are
`0x0000:0x0F70` and `0x0F70:0x1930`. Descriptors and dispatch entries are computed
from source labels. Conker differs from Perfect Dark in these reviewed ways:

- Command dispatch decrements the local command count centrally. Handler exits
  no longer repeat that decrement, and some use useful work in the delay slot.
- Buffer addresses use direct command-relative adds; redundant masks are absent.
- MP3ADDY stores only the MP3 address, omitting the extra high-word store.
- The resampler uses two lane-selection vectors with interleaved vector merges.
- The envelope mixer reads both channel flag halfwords and applies separate gain
  vectors before accumulation, instead of the Perfect Dark XOR-only path.
- The MP3 instruction body is unchanged. Four trailing NOPs belong to Conker's
  descriptor-covered `0x9C0` bytes. They follow the final return and delay slot;
  they are verified target instructions, not padding used to hide a code mismatch.

## Initialized data ownership

`asp.s` owns the full `0xB50`-byte initialized payload. File layout:

| File range | Contents |
|---|---|
| `0x000:0x010` | Two 8-byte overlay DMA descriptors: file offset, length minus one, IMEM destination |
| `0x010:0x030` | Sixteen command-dispatch halfwords, resolved from overlay 0 labels |
| `0x030:0x0C0` | ADPCM masks, lane offsets, unit vectors, resampler selectors, envelope constants and reserved zero vector |
| `0x0C0:0x2C0` | 64 phases of four signed 16-bit resampling filter coefficients |
| `0x2C0:0x310` | MP3 transform coefficient vectors (overlay 1 DMEM `0x10:0x60`) |
| `0x310:0x330` | MP3 synthesis-window endpoint vector (DMEM `0x60:0x80`) |
| `0x330:0xB50` | MP3 synthesis/dewindow lookup table (DMEM `0x80:0x8A0`) |

The two data overlays both load their initialized bodies at DMEM `0x10`.
`.headersize` expresses their distinct logical addresses. The following `.skip`
declarations describe runtime scratch buffers and task state; they produce no
initialized payload bytes. The MP3 coefficient/window tables retain upstream
values, while overlay descriptors, dispatch addresses and overlay 0 vectors are
Conker-specific. No data bytes are copied from the ROM by the build.

RSP code and initialized data are reported separately from CPU function matching.
The existing CPU progress denominator is preserved, including its historical
cut at `0x292F0`; no RSP bytes are credited to its CPU numerator.
