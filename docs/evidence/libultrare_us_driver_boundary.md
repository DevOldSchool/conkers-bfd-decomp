# Conker US audio driver source boundary

`0x1CBF0:0x1D900` is a reviewed six-function N-audio driver construction
unit, 3,344 bytes, now reconstructed exactly under
`lib/libultrare/src/libultrare/audio/n_drvrNew.c`. This is a Conker variant.

## Independent evidence

The owned US ROM SHA-1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
All 836 words in independently generated `reference/us/asm/1CBF0.s` equal
the retail interval, whose SHA-1 is
`f4a019516267cd938f3a235b20f9b5f919a61dbe`.
The independent comparison main map retains this interval as raw ASM.

Perfect Dark revision `169ed48bdcbfb3b568b028bd5bebb27680073514`,
`src/lib/naudio/n_drvrNew.c`, supplies the same complete six-function sequence.
The already matched Conker `n_synfilter12.o` ends at `0x1CBF0`, and the
already matched Conker `n_synfx.o` starts at `0x1D900`. Function behavior,
internal references, and these complete neighboring objects support the
boundary independently of alignment.

| Raw entry | Reviewed source-family identity | Structural evidence |
| --- | --- | --- |
| `0x8001CBF0` | Coefficient helper corresponding to PD `func0003b710` | Clamps frequency against output rate minus 200, calls a floating-point math helper, and writes numerator/denominator coefficients. No original function name is claimed. |
| `0x8001CD54` | `n_alFxInitlpfilter` | Computes low-pass gain and a 16-element coefficient vector, clearing its first eight entries. |
| `0x8001CEA4` | `alSemitones2Ratio` | Selects positive/negative semitone multipliers and uses repeated squaring. |
| `0x8001CF38` | `n_alFxInitlpfilter_mono` | Rejects a zero setting, clamps the setting to ten, calls the first helper, and fills the mono coefficient vector. |
| `0x8001D124` | `n_alFxNew` | Allocates an effect, delay sections and paired sample buffers; constructs optional resampler and low-pass state. |
| `0x8001D6E8` | `alN_PVoiceNew` | Allocates decoder/resampler/envelope state, obtains a DMA callback, and initializes a physical voice. |

The mono initializer calls `0x8001CBF0`; the effect constructor calls
`0x8001CD54`. Both constructors call the independently identified heap
allocator at `0x80012844`. Exact Conker `n_synallocfx.o` calls the effect
constructor, while exact `n_synfx.o` calls the mono initializer. Internal
entry alignment and the final return at `0x8001D8F4`, delay slot, and one
padding word agree with this complete source-family grouping.

## Differences requiring a Conker reconstruction

The first helper passes floating-point arguments and reads its result from
`$f0`. This differs from the surveyed Perfect Dark source's documented missing
math-function declaration and resulting integer ABI conversion. Its encoded
call resolves to game address `0x150484A0` when executing in the main
`0x10000000` mapping; the raw reference's `func_850484A0` label reflects its
alternate disassembly PC, not a new game symbol attribution.

The destination is already tracked as `src/game/game_75950.c`. Its zero-axis
cases, square-root normalization, calls to the neighboring inverse-cosine
helper, and quadrant corrections reproduce the algorithm in the same pinned
Perfect Dark revision's `src/game/atan2f.c`. This strengthens the call's
source-family identification without renaming or claiming a C match for that
existing raw game unit.

The physical voice constructor uses Conker's expanded layout: decoder state
at `+0x14/+0x18`, resampler state at `+0x48`, envelope state at `+0x5C`,
and additional filter state through `+0xCC`. These offsets must be reproduced
from the ROM rather than importing another game's structure unchanged.

## Exact reconstruction

The first complete C candidate reproduces all 3,344 text bytes with IDO
`-O1 -g2`. All six function entries and every resolved relocation agree with
the independently extracted retail text. The complete text template occurs
once in the main executable. Normalized object MD5 is
`101c524fed18ca3bc40e7838b0bfb1da`.

The entire 32-byte `.rodata` section equals ROM `0x2C770:0x2C790`, bounded by
the exact `cents2ratio.o` and `n_synfx.o` constants. This object allocates no
`.data` or `.bss`. The constructor references default effect parameters at
`0x8002BBE0` externally; their full original allocation is not established
and is not attributed to this object.

The canonical map links the text and rodata from the Rare archive. The six
former raw work items and source skeleton are retired through
`./conker retire-library-units` using this evidence.
