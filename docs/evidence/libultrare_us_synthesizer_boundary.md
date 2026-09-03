# Conker US synthesizer source boundary

`0x18E60:0x19AB0` is a reviewed nine-function N-audio synthesizer unit,
3,152 bytes. It was initially retained as raw source. The subsequent library
matching pass reproduced the complete object under
`lib/libultrare/src/libultrare/audio/n_synthesizer.c`; see the reconstruction
evidence below. This is a Conker variant, not an unchanged SDK object.

## Independent evidence

The owned US ROM SHA-1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
All 788 words in independently generated `reference/us/asm/18E60.s` equal the
retail range, whose SHA-1 is `8af7d37d4d2ffe1cf71acd4c35b630d855f722aa`.
The independent comparison map retains this interval as raw ASM.

Perfect Dark revision `169ed48bdcbfb3b568b028bd5bebb27680073514`,
`src/lib/naudio/n_synthesizer.c`, provides the same complete nine-function
sequence. Function behavior, shared state, internal calls, and the already
verified neighboring objects establish the boundary; alignment is corroboration
only. The reconstructed `n_sl.o` ends exactly at `0x18E60`, and the independently
matched stock-debug `cents2ratio.o` begins at `0x19AB0`.

| Raw entry | Reviewed source-family identity | Structural evidence |
| --- | --- | --- |
| `0x80018E60` | `n_alSynNew` | Initializes synth state, clamps auxiliary buses, allocates buses/voices/update pool, and links the free lists. |
| `0x80019498` | `n_alAudioFrame` | Calls next-sample selection, advances client callbacks, generates bounded audio command chunks, and collects freed voices. |
| `0x800196E4` | `__n_allocParam` | Pops synth `+0x40` update-list head and clears the returned node's next pointer. |
| `0x80019744` | `_n_freeParam` | Pushes one update node onto synth `+0x40`. |
| `0x80019770` | `_n_collectPVoices` | Moves the lame list at `+0x14` to free list `+0x04`, including Conker's extra auxiliary-node cleanup. |
| `0x800198B0` | `_n_freePVoice` | Moves one physical voice to the lame list at synth `+0x14`. |
| `0x80019964` | `_n_timeToSamplesNoRound` | Converts microseconds using synth output rate `+0x54`, division by 1,000,000, and rounding by 0.5. |
| `0x800199C8` | `_n_timeToSamples` | Calls the preceding conversion helper and masks off the low four bits. |
| `0x80019A04` | `__n_nextSampleTime` | Searches the client list at synth `+0x00` using samples-left `+0x10` and current samples `+0x20`. |

The internal calls preserve this organization: frame `0x80019498` calls
`0x80019A04`, `0x80019964`, and `0x80019770`; the aligned-time helper calls
`0x80019964`. Newly exact library objects independently call `0x80018E60`,
`0x800196E4`, `0x800198B0`, and `0x800199C8` at these same entries.
Many internal entries are not 16-byte aligned, so splitting them into unrelated
objects would lose the observed grouping. The last helper returns at
`0x80019A9C`, followed by its delay slot and twelve bytes of final padding.

## Differences requiring a Conker reconstruction

Initialization copies additional configuration callbacks into synth offsets
`+0x24:+0x38`; the release callback at `+0x2C` is independently used by the
matched Conker voice-release wrapper. The raw auxiliary buses use linked
physical-voice membership, agreeing with the exact Conker allocator and the
collector's extra unlink/clear operations. The frame routine emits Conker
command words after its pull call rather than using the surveyed implementation
unchanged. These are concrete behavioral/layout differences.

The time conversion references the float at `0x8002C750`. Its existing state pointer
`n_syn=0x8002BA44` is owned by the now-matched `n_sl.o`; that does not make all
synthesizer code or storage an exact archive member.

## Exact reconstruction

The first complete C candidate reproduces all 3,152 text bytes using IDO
`-O1 -g2`, including the unsigned sample-time comparisons, the 0xD0 physical
voice stride, 0x24 update entries, 0x44 auxiliary buses, 0x38 output filters,
and 0x14 main bus allocation. Its nine ELF entries have the exact raw offsets.
Every relocation is resolved to the reviewed retail target before comparison.
The full text template occurs once in the main executable.

The entire 16-byte `.rodata` section equals ROM `0x2C750:0x2C760`, ending at
the independently matched `cents2ratio.o` constants. It contains the time
conversion constant and padding; no data or BSS is allocated by this object.
Normalized full-object MD5 is `a6bbe68588a5e3d50b331739541e4046`; resolved
text SHA-1 remains `8af7d37d4d2ffe1cf71acd4c35b630d855f722aa`.

The canonical map now links this text and rodata from the Rare archive, while
the independent comparison map remains raw. The nine former raw work items
and source skeleton are retired through `./conker retire-library-units`.

The frame pull target is now independently reconstructed as `n_alMainBusPull`
at `0x8001FB40`. Correcting its earlier provisional `n_alSavePull` name changes
the object symbol table and MD5, with identical relocated text.
