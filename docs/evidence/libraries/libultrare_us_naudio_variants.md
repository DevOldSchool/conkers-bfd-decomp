# Conker US N-audio library variants

Twenty-four complete reconstructed library objects replace 6,736 raw main-code
bytes and contain 34 functions. All remain in `lib/libultrare`, with the raw
comparison map unchanged. These are Conker reconstructions of the N-audio
source families, not unchanged Nintendo or GoldenEye object claims.

## Authority and source lineage

The authority is the owned US ROM with SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a` and the independently generated
main assembly under `reference/us/asm/`. Existing raw split boundaries provided
navigation only. Every proposed object was compiled, compared across its entire
text including padding, checked for unique occurrence in the main executable,
and then compared with every relocation resolved to its actual retail target.
A full byte-identical ROM link is the integration gate.

The N-audio algorithms were reviewed in Perfect Dark revision
`169ed48bdcbfb3b568b028bd5bebb27680073514`, `src/lib/naudio/`, and Banjo-Kazooie
revision `9db90a003fff15d13d29505d571aff2543b50383`, `src/core1/n_audio/`.
These are source-lineage references, not copied Conker match evidence.
The MIDI and channel-pan wrappers were additionally compared with the pinned
ultralib revision `e24c836796df4bf520ff8b11a5c9d2cea3a66cbd`,
`src/audio/cspsendmidi.c` and `src/audio/cspsetpan.c`.

The existing Rare SDK headers provide the scalar, ALPlayer, ALEvent,
ALEventQueue, ALSynConfig, and ALHeap declarations. `n_audio_partial.h` adds
only reviewed Conker field offsets. Those partial views neither allocate nor
claim the complete original runtime structures.

## Complete object boundaries

Every range below fills an existing raw text interval exactly. Each rebuilt
complete text template occurs once in US main code, retaining opcode/register
bits when identifying relocation sites. The subsequent resolved comparison
checks all bytes. Function offsets and sizes come from the rebuilt ELF symbols;
the emitted final returns and alignment bytes are included in the range check.
No function inventory or source-unit records occupied these intervals.

| Member | US ROM range | Function offsets / sizes | Resolved text SHA-1 |
| --- | --- | --- | --- |
| `n_cspplay.o` | `0x17AA0:0x17AF0` | `0x0/0x44` | `4bd076cdb0768b588c53519faf67c4af0467e0ea` |
| `n_cspsetpan.o` | `0x17D80:0x17DF0` | `0x0/0x6c` | `4351b4316b6380e9d194d422dedf04173b3cb67a` |
| `n_cspsetseq.o` | `0x18CB0:0x18D00` | `0x0/0x50` | `7f3ef27542127f278a7e89ff7dc80ca22a1a0963` |
| `n_cspsetvol.o` | `0x18D00:0x18D50` | `0x0/0x50` | `71e18039175d8ab02d370a36b3ba31f68503ae6e` |
| `n_cspstop.o` | `0x18D50:0x18DA0` | `0x0/0x44` | `db740bfcf64173fb17d575513265d3b4312f7ddb` |
| `n_sl.o` | `0x18DA0:0x18E60` | `0x0/0x6c`, `0x6c/0x4c` | `af37663281284a436119a63ba628c332160054a4` |
| `n_event.o` | `0x1C060:0x1C690` | `0x0/0xa8`, `0xa8/0x11c`, `0x1c4/0x2cc`, `0x490/0x194` | `6728c6a0cf518008a145c1a86b7e0616ed3054d0` |
| `n_synaddplayer.o` | `0x1C690:0x1C770` | `0x0/0x70`, `0x70/0x70` | `1fbc28dd26c3b78eab22f25f6b11107b5d9c2481` |
| `n_synstopvoice.o` | `0x1C770:0x1C810` | `0x0/0xa0` | `9530a03deecf81d4fcb1da409c0608ab4ec739a9` |
| `n_synfreevoice.o` | `0x1C810:0x1C910` | `0x0/0x100` | `23f93f9136c60b483cd531c7995e219578bfa944` |
| `n_synsetvol.o` | `0x1C910:0x1C9E0` | `0x0/0xc4` | `4117e6cc7f3218d6888d26ad71276c2e04e3b6fd` |
| `n_synsetpitch.o` | `0x1C9E0:0x1CA90` | `0x0/0xb0` | `384043767ccfd1d638d60ae87c4114b23010d988` |
| `n_synfilter13.o` | `0x1CA90:0x1CB40` | `0x0/0xb0` | `07448a0f4d8b57fa79c20235092dc18e10fbcf4d` |
| `n_synfilter12.o` | `0x1CB40:0x1CBF0` | `0x0/0xb0` | `5e72f3b2216c776b26fd9c68cda269d7457e205d` |
| `n_synfx.o` | `0x1D900:0x1DBA0` | `0x0/0xb0`, `0xb0/0x78`, `0x128/0x78`, `0x1a0/0x44`, `0x1e4/0xb8` | `f18951a0d3665d2533fd3903fc303f6a75e31f7c` |
| `n_cseqnextdelta.o` | `0x1DBA0:0x1DC80` | `0x0/0xdc` | `63edf8446edcd4d868d0fa37add769b391b6a749` |
| `n_synallocvoice.o` | `0x1DC80:0x1E170` | `0x0/0x2bc`, `0x2bc/0x22c` | `ed47d111e86b66c61ebe1b5592756c7fe40de107` |
| `n_synstartvoiceparam.o` | `0x1E170:0x1E2A0` | `0x0/0x12c` | `94aa82b917758e61c510e440cb5c4a6bef8a0a65` |
| `n_synsetpan.o` | `0x1E2A0:0x1E350` | `0x0/0xb0` | `dc1822e7a6f993d6fc6d170c7c3043b29a88e763` |
| `n_synfilter11.o` | `0x1E350:0x1E400` | `0x0/0xb0` | `75171b33f066e9fec0622ca8bf67bff8d1de75ce` |
| `n_cspsendmidi.o` | `0x1E400:0x1E480` | `0x0/0x78` | `7e0c417dc9d1c8d96cae861ed8ff44e2df221e81` |
| `n_syndelete.o` | `0x1E480:0x1E4A0` | `0x0/0x1c` | `469f175cd4b7effcd413fdb8c28a7649ab8f7b1a` |
| `n_synallocfx.o` | `0x1E4A0:0x1E530` | `0x0/0x88` | `036ec838b0a2ef7976aa22d0763edc8e580dcad0` |
| `n_synsetpriority.o` | `0x1FFE0:0x20000` | `0x0/0x1c` | `756486188cfa9489f1f683f9ce6f4292d9664ae8` |

`n_synaddplayer.o` contains two identical list-insertion bodies. Their complete
membership and entry offsets are exact, but that does not distinguish original
sound-player versus sequence-player API names. The exported names therefore
remain `__conker_audio_add_player_1` and `__conker_audio_add_player_2`.

## Conker differences

- The objects reproduce with IDO 5.3 `-O1 -g2`, using the existing Rare flags.
- The virtual voice stores its physical-voice pointer at `+0x08` and priority
  at `+0x1A`; the latter differs from the surveyed N-audio voice layout.
  Narrow parameters use existing SDK API signatures and the observed signed
  halfword or unsigned byte loads, rather than inferring parameter types from
  stores alone.
- Physical-voice scheduling offset is at `+0x90`; synth parameter samples and
  current samples remain `+0x1C` and `+0x20`. All update-list field accesses
  reproduce their original widths and offsets.
- `n_alSynFreeVoice` additionally passes the voice's `+0x14` pointer to the
  callback at synth `+0x2C`, even when the physical voice was already absent.
  This behavior is present in retail and retained in the source.
- Sequence event wrappers use queue offset `+0x48` and posting flags `2`.
  The stop event is `AL_SEQP_STOP_EVT` (`16`).
- `n_alCSPSendMidi` passes its supplied delay directly; the stock routine
  multiplies ticks by the sequence tempo.
- Effect allocation uses the synth auxiliary-bus pointer at `+0x48`, bus
  stride `0x44`, and effect pointer at bus `+0x20`. The main effects getter
  reads bus `+0x1C`; the output-filter getter reads bus `+0x40`.
- The five-function effects unit combines the set-mix, get-reference, and
  set-parameter source families. `n_synfx.c` is a reconstruction filename,
  not a claim to have recovered the original filename. Its unaligned internal
  entries, exact source order and membership, final padding, and single
  constant section all match the complete existing interval.
- Effect-reference getters compare the main-bus handler against physical
  `0x1001E530`. The scoped `__conker_audio_fx_pull` alias preserves that exact
  pointer without changing the raw function's virtual address.
- Filters `0x11`, `0x12`, and `0x13` retain the surveyed Rare API names and
  integer/float payloads. The voice-start update contains all three filter
  parameters and reads `unityPitch` from voice `+0x1E`.
- Voice allocation retains the SDK two-function membership and the 552-sample
  stolen-voice delay. Conker additionally copies configuration `+0x08` into
  voice release data, moves physical-voice `+0x08` list nodes to the selected
  auxiliary bus at `+0x14`, and clears physical-voice `+0x28`. The complete
  allocator matches 1,264 bytes, including its internal call and padding.
- The event object copies 16-byte events in 28-byte list items. Its inline
  list operations are represented as C macros with scoped SDK-typed locals;
  no assembly body or instruction patch is used. The complete event object
  matches with all four functions and their internal entry offsets.
- Posting flag mask `0x02` requests interrupt masking/restoration; `0x01` permits
  consuming the last free item. Next-event does not toggle interrupts. Flush
  returns the retail zero-sentinel accumulated removed-event time; it retains
  the original accumulation and sentinel behavior rather than simplifying it.

## Relocations and non-text sections

| External helper | Main virtual address |
| --- | --- |
| `osSetIntMask` | `0x80024880` |
| `__n_allocParam` | `0x800196E4` |
| `_n_freePVoice` | `0x800198B0` |
| `_n_timeToSamples` | `0x800199C8` |
| `n_alEnvmixerParam` | `0x80020978` |
| `bcopy` | `0x80023A10` |
| `n_alFxParamHdl` | `0x8001ED6C` |
| `n_alFxInitlpfilter_mono` | `0x8001CF38` |
| `n_alSynNew` | `0x80018E60` |
| `n_alFxNew` | `0x8001D124` |

These main virtual addresses encode the same MIPS26 call words as the raw
physical-code aliases. The shutdown call to `n_alSynDelete` binds directly to
the newly mapped library entry at `0x8001E480`. The event posting helper now
also binds to the actual library symbol at `0x8001C224`, replacing its
temporary raw-code alias.

`n_sl.o` owns the initialized runtime section: `.data=0x10`
at ROM `0x2BA40:0x2BA50`, virtual `0x8002BA40:0x8002BA50`. Its two pointer
symbols are `n_alGlobals=+0x00` and `n_syn=+0x04`, followed by eight bytes of
section padding. The complete section is zero and equals retail; those zero
bytes alone would be ambiguous. The initialization and shutdown relocations
independently establish both symbol addresses, and the compiled section
establishes its complete extent. Other audio objects bind to that same real
`n_syn` definition, so no absolute alias or duplicate state is introduced.

`n_synfx.o` additionally owns `.rodata=0x10` at ROM `0x2C790:0x2C7A0`,
virtual `0x8002C790:0x8002C7A0`. Its bytes are
`3dcccccd000000000000000000000000`: the float 0.1 followed by section padding.
Both the full byte comparison and the output-filter setter relocation verify
this placement. The other twenty-one objects have only text among their runtime
sections. There is no omitted data, rodata, or BSS allocation. The independent
reference retains the original raw data range across the new initialized-data mapping.

## Reproducible checksums

`object-md5s.txt` records these as Conker reconstruction checksums. The `-g2`
objects have non-runtime `.mdebug` removed after compilation because IDO embeds
build time and hostname there. This preserves instruction scheduling while
making complete ELF checksums reproducible. Existing accepted upstream object
hashes are unchanged. Rebuilds after shared-header changes verified all
previously accepted reconstructed-object hashes.

## Validation

On 2026-09-02, the complete US ROM passed `./conker build --profile us`
with SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`. The clean
`./conker game-build --refresh` also passed, preserving all 2,072,880 game-code
bytes and SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
All 151 Python tests passed; generated progress and whitespace checks passed.
The main and game comparison maps retain independent raw assembly.

All 24 audio C candidates matched on their first compilation. A complete-object
scan of those rebuilt templates found no additional copies in the game overlay.
The library mappings add no speculative function names to identical helpers
and no source-unit completion records for still-raw intervals. The remaining
nine-function synthesizer was registered separately as a raw Rare source
unit; see [`libultrare_us_synthesizer_boundary.md`](libultrare_us_synthesizer_boundary.md).
The separate six-function driver construction family is likewise retained as
raw source; see [`libultrare_us_driver_boundary.md`](libultrare_us_driver_boundary.md).

The final compact-sequence object reconstructs the complete single-function
`src/lib/ultra/audio/cseq.c` from the same pinned Perfect Dark revision.
`__alCSeqNextDelta` uses the existing SDK `ALCSeq` layout: valid tracks at
`+0x04`, last delta at `+0x10`, pending-subtraction flag at `+0x14`, and the
16 unsigned per-track deltas at `+0xB8`. Its 220-byte function plus one
padding word fills the 224-byte interval exactly between the verified
`n_synfx.o` and `n_synallocvoice.o`. It has no relocations or nonempty runtime
data/rodata/BSS sections, and its complete text occurs once in US main code.
The filename `n_cseqnextdelta.c` distinguishes this reconstruction from full
stock compact-sequence implementations; it does not claim Conker retained
the surveyed filename.
