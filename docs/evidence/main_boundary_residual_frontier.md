# US main boundary review: remaining frontier

This records the remaining frontier of the ongoing 2026-09-30 main review,
separate from the complete game-overlay ownership map and ASM-to-C progress.

## Verified progress

Eight registration batches added 25 reviewed working units, 220 registered
spans and 62,768 bytes. The subsequent
[owned beta comparison](main_boundary_beta_comparison.md) adds a 64-byte, two-member hardware-init/probe working family. With the two existing
bootstrap units, main now has 28 reviewed units, 229 registered spans and
64,112 reviewed source bytes.
The nineteen custom/privileged spans in the seventh batch and the earlier
96-byte fixed-TLB routine are separately verified original assembly: twenty
spans, 9,736 bytes, with no C matching credit. All earlier registration and
matching records are preserved. The independent raw-reference map remains
unchanged; the canonical map now explicitly classifies the 64-byte zero tail
as text-ordered data without assigning an original object owner.

| Classification in CPU interval `0x1050:0x290D0` | Bytes |
| --- | ---: |
| Already exact CPU library text | 98,512 |
| Reviewed working units, canonically raw | 64,112 |
| Known zero-filled text tail | 64 |
| Three remaining raw navigation ranges | 1,280 |
| Total | 163,968 |

The handwritten entry `0x1000:0x1050` lies outside this interval. The existing
progress denominator ends at `0x292F0`, including another 544 RSP bytes; this
review does not silently change that denominator.

The complete memberships and evidence are in:

- [System wrappers](main_system_wrapper_boundaries.md)
- [Allocation, transfer, scheduler and controller](main_allocator_transfer_controller_boundaries.md)
- [Audio driver and sequence controller](main_audio_driver_sequence_boundaries.md)
- [Sound-record callbacks and handles](main_sound_record_family_boundary.md)
- [Sequence API and MP3 adapter](main_sequence_api_mp3_adapter_boundaries.md)
- [Fixed TLB alias](main_tlb_alias_boundary.md)
- [Handwritten families and complete interior-entry accounting](main_handwritten_family_boundaries.md)
- [Spatial-audio calculations](main_spatial_audio_boundaries.md)
- [Zero-filled text tail](main_text_zero_tail_226b0.md)
- [Beta-selected hardware-init/probe family](main_boundary_beta_comparison.md)

These are working families, not claims that every historical filename or
original object boundary has been recovered. The handwritten inventory records
non-overlapping verification spans; documented interior ABI entries remain
inside their owners rather than becoming overlapping ordinary C work items.

## Remaining exact ranges

| US ROM range | Bytes | Current result | Required next evidence/action |
| --- | ---: | --- | --- |
| `0x38C0:0x38E0` | 32 | Varargs-style empty stub | Owned selector/reference or independent original grouping |
| `0x39B0:0x39C0` | 16 | Ambiguous no-op return | Preserve uncertainty without an unsupported stock identity |
| `0x50A0:0x5570` | 1,232 | Five raw spans but six independent-index proposals | Resolve ownership and the unselected empty `0x5298` proposal without shrinking a span for matching credit |

The remaining cases need new positive ownership/entry evidence. The completed
bounded static scans of the available US main/game images cannot supply it;
repeating those scans would add no evidence. There is no current permission
blocker, but these bytes must remain uncertain until a new call/selector,
independent original map or meaningful cross-version correlation appears. The
owned PAL ROM has now been checksum-validated and used for a
[targeted regional comparison](main_boundary_pal_comparison.md): it preserves
the ambiguous entries and supplies no new selection or ownership evidence for
them. The subsequent debug/ECTS comparison provides positive selected
counterparts and a specific hardware-domain relationship for `0x38E0:0x3920`;
that complete pair is now reviewed. They do not resolve the three remaining
ranges. See the [beta evidence and bounded result](main_boundary_beta_comparison.md).
No original debug map was available for this review.
A negative runtime trace would not establish an original boundary or prove
unreachability.

## The unselected `0x5298` proposal

Both unsplit and independently range-scoped spimdisasm 1.33.0 IDO analyses
propose `0x5218:0x5298` and `0x5298:0x52A0`. The split raw reference instead
retains the complete `0x5218:0x52A0` span. The first body's ordinary epilogue
ends at `0x5294`; the final two words are another `jr $ra; nop`.

A complete direct J/JAL scan of main CPU and decompressed game code found no
selection of `0x5298`. Neither initialized main data nor decompressed game data
contains its `0x80005298/0x10005298` pointer, and neither CPU image has an
immediate low-half address construction for that exact target. These bounded
negative results do not establish unreachability or original ownership. The
raw words are preserved; no forced symbol, shortened registration or new empty
function is introduced. The same scans found no positive selection of the tiny
stub ranges above.

## Resolved implementation obstacles

- The pinned RSP assembler was built in an isolated extension, all four RSP
  payloads matched, and the unchanged full US ROM was reproduced byte-for-byte.
  See [toolchain and verifier proof](main_original_assembly_verification.md).
- Original-assembly verification now supports main CPU spans, including strict
  checked cross-span local labels and unpadded literal constants. Its exact
  full-span assembly/link/ROM gate remains unchanged.
- The apparent handwritten index disagreements were reconciled through positive
  calls, custom shared-stack/register contracts, owned state and complete
  interior-entry accounting. Every retained original span passes actual proof.
  No blanket label promotion or speculative parser change was needed.

## Completion and integration sequence

1. Preserve the separate reviewed branch while game matching continues. Replay
   registration transactions onto the chosen baseline instead of replacing its
   inventories; this preserves newer game matches and source-unit states.
2. Spatial-family ownership and zero-tail classification now pass full-ROM
   equality. Retain the three unknown stub/entry ranges explicitly rather than
   registering them to obtain a completion percentage.
3. For any later positive empty-stub evidence, regenerate references independently
   and reconcile complete memberships before changing registered spans.
4. Keep CPU source ownership, original assembly, RSP, text data, padding and
   matched C progress as separate measures. Mixed main C/ASM integration remains
   a separate unsupported transition, not a reason to withhold proven raw ownership.

Completion requires evidence-backed ownership or explicit classification of each
scoped range and its applicable registration/map/build gates. Removing `asm`
tokens or increasing a percentage is not proof.

## Verification

The fixed-TLB batch and the nineteen-span handwritten batch each pass clean
`BATCH_COMPLETE`, including full US ROM equality, fresh assembled/link/ROM
original-assembly proofs, all 1,070 tests (12 declared skips), metadata/progress
and whitespace gates. No new C match or mixed main integration is claimed.
The earlier five batch reports remain historical records of the checks available
at that time. The spatial/padding batch also reproduces the full US ROM after
regeneration, with a dedicated map test for text ordering and no invented
function credit. The final expanded suite passes 1,071 tests with 12 declared
skips. Private ROMs, generated raw assembly and binaries remain ignored. The later
hardware-pair registration and its final checks are recorded separately in
[the beta comparison](main_boundary_beta_comparison.md#reproduction-and-verification).

## Separate game function-span caveat

Complete game-overlay source ownership does not establish that every retained
raw function span is already a complete C-rewrite target. The existing
[dispatcher evidence](game_dispatcher_callback_groups.md#resolving-the-function-index-disagreements)
explicitly retains the unproven interior entry proposals `0x15040A4C`,
`0x15073070` and `0x1513E134` inside preceding raw spans.

The current deferred record for `func_15040A40` is a concrete consequence:
its 20-byte span includes the twelve-byte `sw/jr/nop` stub followed by an
unlabelled eight-byte `jr/nop` at `0x40A4C`. The preserved attempt is nonzero;
this review does not claim it was rerun. Shortening the registered span or
inventing a second function just to get zero difference would be unsupported.
Find independent entry/selector evidence first, then reconcile all affected
members and independently regenerate/verify their complete spans. The enclosing
reviewed source-unit range `0x40350:0x40D90` remains fully owned throughout.
No game registration or matching source is changed by this note.
