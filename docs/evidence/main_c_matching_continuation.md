# Main C matching continuation

## Baseline and scope

This continuation starts from main commit
`2bf889bfc905e02359a3a9320832101a4b2ebfdd`, after the model-integration merge.
The baseline contains 2,633 accepted US C functions. The earlier game-matching
work's 38 functions / 14,244 bytes are already in that baseline and are not
counted again here. No source boundaries, compiler settings or shared headers
are changed.

Before new matching, the pinned toolchain smoke checks, an existing accepted
C function's independent CURRENT (0), RSP payload checks, complete US ROM
build, refreshed game-code/mapped-rodata comparison, progress and whitespace
checks passed.

## First batch: main stubs and scalar controls

Five functions match their entire independent registered US spans:

| Function | Source | Bytes | Source evidence |
| --- | --- | ---: | --- |
| `func_80011E88` | `init_EB00.c` | 12 | Void stub with one unused full-width argument home |
| `func_80011FA0` | `init_11FA0.c` | 16 | Full-width selector store |
| `func_80011FDC` | `init_11FA0.c` | 16 | Independent sibling selector store |
| `func_800085A4` | `init_8180.c` | 20 | Void stub with three full-width homes; existing `func_100085A4(s32, s32, s32)` game declaration corroborates the contract |
| `func_8000E75C` | `init_B1B0.c` | 20 | Arithmetic right shift and word-global update |

Every function matched on its first source form. `finish` confirmed CURRENT
(0), reviewed source-unit symbol layout, progress and whitespace. Owning units
remain in progress; a matched function is not a completed or integrated unit.

The clean five-function `verify-batch` returned `BATCH_COMPLETE`, including the
full US ROM build, 1,328 tests run with 12 skipped, metadata, progress and
whitespace. The new accepted total is **5 functions / 84 bytes**, and the US C
inventory is **2,638 functions**. No accepted IDs remain pending in this batch.

## Preserved candidates and negative findings

- `func_80003920`: the natural byte-global clear and an independently reviewed
  explicit-return form both score 60. The store is before `jr` instead of in
  its delay slot. The simpler candidate is preserved with original ASM active.
  Existing accepted main setters use the same compiler route successfully;
  this is not evidence for changing compilation settings.
- `func_8000390C`: the natural zero return reproduces the operations but scores
  100 over the full 20-byte registered span, which includes one trailing `nop`
  beyond the standalone candidate's 16-byte object. It is preserved inactive;
  no padding or reference change was introduced.
- `func_80007A24`: the existing SDK `__osPopThread` handwritten body explains
  the selected raw routine. It was left unchanged without a C trial or a new
  original-assembly acceptance claim.
- Independent reviews of earlier `func_150B17DC` (230) and `func_1506D2E8`
  (650) found their actual frames and stack homes already exact. Remaining
  allocation/scheduling differences do not justify repeating exhausted local
  forms. Both prior best candidates remain unchanged.

Detailed source snapshots, scores, hypotheses and command logs are retained in
the private task ledger. In the first batch, no permutation, artificial storage, volatile access,
narrow-formal inference, handwritten C-body assembly or weakened gate was used.

## Second batch: selector transitions and reset

`func_80011FB0` (44 bytes) and `func_80011FEC` (52 bytes) are newly accepted.
The conditional setter first scored 45 with seven register-only differences.
Naming the genuine previous selector value before testing it recovered the raw
value/address register roles and CURRENT (0). Its return type remains `void`;
no caller or declaration established a return-old contract. The reset's
right-associated assignment chain matched on its first source form, preserving
the raw reverse store order and address-register roles.

The owning unit's larger `func_80012020` (1,344 bytes) remains deferred. The
ready starter could not process its omitted jump-table input, so the candidate
was translated manually using the full raw body, bounded table/data context
and independently reviewed helper contracts. Two real two-float aggregates
preserve the initializer copies, while coherent two-element global arrays
represent the indexed output storage. The first source scored 591 with the
correct 0x70 frame, instruction count and branch structure.

Independent candidate-object `.mdebug` review identified source homes at
entry-SP offsets -4 (volume), -8 (selector), -16/-24 (aggregates), -28 (index)
and -32 (scale). Moving only the existing loop-index declaration above volume
predicted the exact live homes at SP+0x68, +0x5C and +0x54. That one revision
removed all 23 stack-related rows and improved the score to 495. The actual
scale spill stayed exact at +0x48, distinct from its abstract debug home +0x50.
No storage was added and this does not establish a universal declaration rule.

The remaining 18 rows are ten FP register/operand differences, six table or
array-alias operands, and two duplicate-byte-mask versus move instructions.
The helper parameters remain full-width: an extra byte mask is not qualifying
narrow-ABI evidence. Candidate table relative case starts agree with the raw
case-block positions, but this is not independent jump-table acceptance. The
best 495 source is preserved inactive; it contributes no accepted function or
byte count.

The clean related-family batch rechecked both earlier setters and accepted
the two new members: `BATCH_COMPLETE`, full US ROM match, 1,328 tests run with
12 skipped, metadata/progress/whitespace passed. The owning unit remains in
progress. This adds **2 functions / 96 bytes**, giving **7 / 180 bytes** since
the fresh baseline and **2,640** accepted US C functions. No batch IDs remain
pending at this checkpoint.

## Third batch: sound-control records

Three functions are newly accepted in `init_EB00.c`:

- `func_80011E94` (36 bytes): full-width boolean test and two byte stores,
  including the observed early return; first source form matched.
- `func_800112BC` (84 bytes): typed four-byte queue record, full-width formals
  and real count snapshot. The initial 660 source reloaded the count after byte
  stores. Preserving the raw once-loaded count removed that alias-driven reload
  and recovered CURRENT (0).
- `func_8001147C` (84 bytes): the initial full-width formal plus normalized
  local scored 365. The pre-existing active runtime-alias declaration
  `s32 func_1001147C(u16)` in `src/game/game_13F9D0.c`, outside its deferred
  caller body, supplies the narrow contract; the caller passes a `u16` sound
  field. Using that declared contract reduced the score to 10. Reversing the
  source integer-equality operands recovered the sole remaining branch-register
  order and CURRENT (0). The formal was not narrowed from a store instruction.

The same group preserves the following nonmatches:

- `func_8000853C` and `func_80008570` retain 225 each. Exact SDK/library and raw
  caller evidence establish the get-state result, single player input and
  queue setter's actual pointer argument. The generated starters' incidental
  register arguments were rejected. The existing full-width wrapper contracts
  remain; the incoming argument-home differences are unresolved.
- `func_80010F30` retains 248 with verified seven-argument forwarding and a
  returned sound handle. Full-width existing contracts and explicit use-site
  casts were retained instead of unsupported formal narrowing.
- `func_8000EBC4` improved 320 to 125 when its real value snapshot was moved
  before the timer branch, matching raw load order. A named step snapshot was
  code-neutral and discarded. Fourteen register rows remain.
- `func_800038E0` improved 845 to 410 by expressing the observed hardware write
  through its direct MMIO address. Only the genuine hardware pointee is
  volatile; the RAM globals are not. This is a semantic MMIO qualification,
  not an allocation technique. Independent review found no evidence for a
  signedness or extra-volatility experiment to defeat the remaining constant
  reuse. The conditional whole-unit alignment lead for `func_8000390C` remains
  unaccepted until this genuine companion matches; no padding was added.

The clean batch included the three new functions plus existing `80011E88`
and `800085A4` regressions. It returned `BATCH_COMPLETE`: full US ROM match,
1,328 tests run with 12 skipped, and metadata/progress/whitespace passed.
This adds **3 functions / 204 bytes**, giving **10 / 384 bytes** since the
fresh baseline and **2,643** accepted US C functions. Source units remain in
progress or raw as recorded; no new unit completion is claimed. No accepted
IDs remain pending at this checkpoint.

## Fourth batch: scalar controls and guarded lookups

Five related members of `init_B1B0.c` are newly accepted:

| Function | Bytes | Source evidence and attempts |
| --- | ---: | --- |
| `func_8000E8C4` | 44 | Full-width bit test and word flag clear; first form matched |
| `func_8000E770` | 48 | Independently nullable word outputs followed by flags read, retaining alias-sensitive order; first form matched |
| `func_8000E0F8` | 60 | Guarded pointer lookup and aligned state word; 410 to 0 by normalizing the existing full-width formal before the call instead of only in its argument expression |
| `func_8000BBE8` | 64 | Initial-state callback with three unused argument homes and a proven three-word helper call; first form matched |
| `func_8000E8F0` | 68 | Forwarded full-width selector, guarded leading record word and unsigned-byte table read; first form matched |

The raw `func_8000B1B0` body consumes incoming a0, so the final wrapper explicitly
forwards its argument rather than adopting the starter's guessed no-argument
contract. The existing runtime-alias declaration supports its `s32` result.
The adjacent `8000E704` body establishes the three real arguments and boolean
return used by the callback. No formal narrowing or shared dependency change
was needed.

All five passed independent full-span CURRENT (0), reviewed symbol layout,
progress and whitespace. The clean batch also rechecked existing `8000E75C`:
`BATCH_COMPLETE`, full US ROM match, 1,328 tests run with 12 skipped, and
metadata/progress/whitespace passed. This adds **5 functions / 284 bytes**,
giving **15 / 668 bytes** since the fresh baseline and **2,648** accepted US
C functions. The source unit remains in progress and no accepted IDs remain
pending at this checkpoint.

## Fifth batch: shared record fields and updates

Five further `init_B1B0.c` members matched on their first source forms:

| Function | Bytes | Recovered behavior |
| --- | ---: | --- |
| `func_8000CBA8` | 72 | Independently guard two table records, store the input halfword and duration, retaining pointer-table reloads |
| `func_8000E134` | 72 | Preserve the signed upper-bound test, 16-byte table stride and two accepted masked modes |
| `func_8000E704` | 88 | Guard a shared-record lookup and forward its low index byte and two full-width parameters |
| `func_8000CD40` | 96 | Signed approach/clamp arithmetic, including the negative-result guard and conditional step read |
| `func_8000E40C` | 96 | Clamp before lookup, then update the proven word fields according to the record's signed leading word |

The source-local partial record now includes independently observed index/id,
owner and child pointers, word fields at 0x2C/0x30 and halfwords at 0x4E/0x50.
Unused gaps retain only the offsets established by the raw accesses. The
previous word-only zero test at 0x60 is now a pointer-null test on the same
field; its machine code was explicitly revalidated. No shared header changed.

Two related pointer loops remain inactive candidates. `func_8000B1B0` improved
1655 to 290 after an explicit sentinel exit avoided the compiler's loop
transformation; a base-pointer return cast was code-neutral. Its missing
initial input relocation and register allocation remain. `func_8000B294`
improved 1935 to 765 to 140: the sentinel exit removed unrolling, then direct
primary-record expressions removed a redundant retained address. Its complete
96-byte instruction/control shape is now exact, while pointer-register
allocation and address-initializer ordering differ. Independent review of the
retained object found only real cursor and child state; no further unsupported
source experiment was proposed. Neither candidate contributes a new match.

The clean batch checked all five new matches and all six earlier accepted
members of the modified source unit. `BATCH_COMPLETE` confirms the full US
ROM match, 1,328 tests run with 12 skipped, metadata, progress and whitespace.
This adds **5 functions / 424 bytes**, giving **20 / 1,092 bytes** since the
fresh baseline and **2,653** accepted US C functions. The unit remains in
progress and no accepted IDs remain pending at this checkpoint.

## Sixth batch: genuine companion alignment recovery

Three related functions are newly accepted:

- `func_8000CBF0` (100 bytes): three-entry, mask-controlled halfword updates.
  The first do-while form scored 60 with only the index initialization moved.
  A normal counted for-loop recovered that schedule and CURRENT (0), retaining
  full-width arguments and the raw full-width zero-duration test.
- `func_8000B830` (136 bytes): a once-read global flag controls a callback state
  transition and the already matched scalar update helper. Its first source
  form matched, including all unused argument homes and the real state spill.
- `func_8000EA94` (108-byte registered span): three explicit selections, one
  genuine halfword local across a call, and the existing three-word helper
  contract. No default initialization was invented for the original other-input
  path.

The final selector first scored 200 solely because the stripped C object lacked
two terminal `nop` words. Its actual 96-byte code was already exact. The first
object had selector offset 0x33C and a 0x3A0-byte `.text` section, so only four
alignment bytes followed the code. After the genuine 136-byte `8000B830`
companion matched, the unchanged selector body moved to offset 0x3C4 in a
0x430-byte `.text` section. Normal 16-byte section alignment then supplied all
12 trailing bytes, and its complete registered 108-byte span reached CURRENT
(0). Reviewed source-unit symbol layout also passed. No source padding,
reference edit, compiler change or weakened comparison was used.

This focused terminal-span proof depends on the genuine C prefix present in
the tested source. Later changes to this unit must explicitly revalidate the
selector's full span; instruction equality alone is insufficient. Source-unit
ownership or historical object boundaries are not inferred from this result.

The clean three-new-function batch included four affected existing regressions:
`BATCH_COMPLETE`, full US ROM match, 1,328 tests run with 12 skipped, and
metadata/progress/whitespace passed. This adds **3 functions / 344 bytes**,
giving **23 / 1,436 bytes** since the fresh baseline and **2,656** accepted US
C functions. The source unit remains in progress. No accepted IDs remain
pending at this checkpoint.

## Seventh batch: audio-driver callbacks

Six members of `init_8F90.c` are newly accepted, each reaching instruction zero
on its first implementation form:

| Function | Bytes | Contract and behavior |
| --- | ---: | --- |
| `func_80009B2C` | 32 | Full-width tagged handle and signed byte decrement |
| `func_800093CC` | 52 | Initialized flag guards the mapped `osStopThread` call on the owned thread object |
| `func_80009980` | 60 | SDK DMA factory, one-time manager initialization and clearing the actual DMA-state pointer slot |
| `func_80009FFC` | 64 | Distinct custom bank-fetch factory with its own manager initialization |
| `func_80009B4C` | 68 | Tagged-handle release, separate decrement and byte reload, then forwarding the unchanged handle |
| `func_80009B90` | 84 | Proven signed-count/unsigned-state byte transitions and early return |

Independent consumer review establishes the function-pointer contracts rather
than inferring them from incidental registers. `PR/libaudio.h` defines
`ALDMAproc` as `s32 (s32, s32, void *)`; the driver constructor passes a DMA-state
slot through `ALDMANew`. That SDK contract is expressed locally using project
scalar aliases. The separate `ConkerBankFetch` type in `n_seqplayer.c` is
`void * (void *, s32)` and its factory takes no arguments. Its pointer-slot
consumer and mode argument are distinct from the SDK DMA interface. Both raw
runtime worker-address aliases are retained.

The release and retain consumer slots establish `void (void *)` callback
interfaces. In particular, the initializer's Config+0x18 release slot is copied
to the synthesizer and called with `voice->releaseData`. Refining `80009B2C`'s
initial full-width integer annotation to that proven pointer annotation kept
CURRENT (0); it is counted only once. No parameter was narrowed from byte
loads/stores, and the constant in v0 inside `80009B90` was not treated as a
return value. No shared header or compiler setting changed.

The clean six-function batch returned `BATCH_COMPLETE`: full US ROM match,
1,328 tests run with 12 skipped, reviewed layout, metadata, progress and
whitespace passed. This adds **6 functions / 360 bytes**, giving
**29 / 1,796 bytes** since the fresh baseline and **2,662** accepted US C
functions. The audio-driver unit remains in progress and no accepted IDs
remain pending at this checkpoint.

## Eighth checkpoint: cache-list candidates and regression validation

The source-local audio-buffer view now names the observed next/previous links,
saved word and writable owner slot, while retaining the independently proven
byte fields. The bank manager's active-list and free-anchor fields remain one
coherent object. This does not establish the unknown field at 0x10, total
record stride, or a pointer meaning for the saved word. No shared header changed.

Two related 216-byte functions remain inactive candidates:

- `func_80009BE4`: initial scores 1470, 1560 and 1960. Independent SDK list
  evidence justified a scoped insertion block, improving the best to 810.
  A subsequent real owner-slot snapshot restored the load order but scored
  900, so the 810 form is retained. Manager-address scheduling, symbolic
  aliases and copied-anchor allocation still differ.
- `func_8000A348`: scores 985, 920, 475 and 475. The owner-slot snapshot fixed
  its load order; the scoped insertion block then recovered the raw
  branch-likely/store merge. Both arguments cast to a distinct two-pointer
  SDK-prefix view were code-neutral, so the simpler 475 form is retained.
  The missing anchor copy and dependent register assignments remain, and the
  entire registered terminal span is not yet equal.

The concrete insertion evidence is SDK `alLink` in `sl.c` and the existing
`CONKER_AUDIO_LINK` scoped expansion in `n_audio_list.h`. The latter is project
reconstruction evidence, not proof of the original source spelling. Both raw
cleanup functions exhibit the same insertion pattern. The list walker keeps
its genuine pre-store next snapshot for traversal and head replacement while
reloading links during unlink after owner restoration; it also clears the
owner slot, unlike the single-record helper. No padding, volatile accesses,
overlapping independent globals or unsupported argument types were introduced.

A clean regression batch rechecked all six accepted audio-driver siblings
following the partial-type refinements: `BATCH_COMPLETE`, full US ROM match,
1,328 tests run with 12 skipped, metadata, progress and whitespace passed.
This checkpoint adds **no new C matches**. The cumulative accepted result
remains **29 functions / 1,796 bytes**, with **2,662** accepted US C functions.
Both best candidates and the failed source hypotheses are preserved.

## Ninth batch: complete MP3 adapter C coverage

All seven members of `init_12560.c` are newly matched over their full registered
spans, totaling 704 bytes:

| Function | Bytes | Proven behavior |
| --- | ---: | --- |
| `func_80012560` | 40 | Three-argument text callback forwards the actual text and length to the ring transport |
| `func_80012588` | 68 | Forwards the real initialization argument, initializes the transport and installs its callback |
| `func_800125CC` | 112 | Reads playback state once, preserves the exclusion gate, then fades or stops |
| `func_8001263C` | 172 | Resolves a resource path, retains pointer/size across calls and applies volume, pan and filter settings |
| `func_800126E8` | 48 | Reads transport text and returns the count expected by its active consumer |
| `func_80012718` | 184 | Uses observed position fields and the spatial helper, or the centered-pan path |
| `func_800127D0` | 80 | Reports the selected playback states, including the entire terminal registered span |

The matched MP3 decoder consumer declares the text callback as
`void (s32, u8 *, s32)` and passes all three arguments. The first adapter thus
preserves a1/a2 forwarding that its one-argument starter omitted. Similarly,
the initialization callee consumes the wrapper's incoming argument, and the
active `game_AD6B0.c` consumer tests the text-reader return count. These are
actual call contracts, not incidental register values. The ring helpers use
the existing four-word transport layout and the resource lookup retains its
existing variadic path-component interface. The mapped MP3 stop routine takes
no arguments; its incidental incoming zero is not declared as a parameter.

For `80012718`, pre-existing active declarations in `game_981E0.c` and
`game_A28B0.c` establish its first u16 and fourth s16 arguments. Its fifth
argument remains s32, with an explicit u16 value conversion; it was not
narrowed merely to obtain the halfword reload. Only the three position floats
and word at 0x318 are described by the local object view. The latter retains
an opaque field name and does not establish a character or model identity.

The six nonterminal members matched on their first implementation forms.
`800127D0` had exact 68-byte code initially but lacked the three trailing words
of its registered 80-byte span: offset 0x9C in a 0xE0-byte stripped C text
section. With all six genuine companions present, the unchanged body moved
to offset 0x270 in a 0x2C0-byte section, and normal 16-byte alignment supplied
all 12 trailing bytes. Its complete span then reached CURRENT (0). No padding,
compiler or reference change was used. Future changes to this C prefix must
revalidate the terminal function's full span.

The clean seven-function batch returned `BATCH_COMPLETE`: full US ROM match,
1,328 tests run with 12 skipped, reviewed symbol layout, metadata, progress
and whitespace passed. This adds **7 functions / 704 bytes**, giving
**36 / 2,500 bytes** since the fresh baseline and **2,669** accepted US C
functions. The complete source remains in raw-ASM integration mode, following
its required stop action; C coverage and integration are separate claims.
No accepted IDs remain pending at this checkpoint.

## Tenth batch: allocator wrappers and tag walks

Three related functions are newly accepted:

- `func_80003C40` (44 bytes): preserves the existing full-width allocator
  contract, inserts the helper's fourth zero argument and returns its result.
- `func_80004308` (172 bytes): reads the list under the interrupt mask, runs
  the existing text-reset helper, releases tags 1–4 and restores the mask.
- `func_80004250` (184 bytes): releases tag 2 and reduces tags 3/4 while
  preserving the low 24 bits, then reloads the next link after the possible
  free operation. It reuses the proven sibling storage shape and matched on
  its first implementation form.

For `80004308`, the first score was 10: every instruction and actual stack
access matched except the frame size, 0x38 instead of 0x40. The retained
object's debug homes were mask -4, tag -8 and block -12. Moving only the
existing cross-call mask declaration after the two genuine locals changed its
debug home to -12 and recovered the raw 0x40 frame while keeping the actual
mask spill at SP+0x34. The specific prediction was verified separately from
CURRENT (0). No storage or dummy values were added.

Three other members remain inactive candidates:

- `func_800043B4` keeps its best score 160 after 160/160/879. The observed
  12-byte allocation header and tag store are represented, but the delayed
  header-address adjustment and store schedule differ.
- `func_80004074` improved 2807 to 1191 to 1026. Correct successor lifetimes
  eliminated spurious reload/control changes; using the just-written
  destination links then removed redundant named pointer state. Initial
  pointer identity, stack homes and scheduling still differ.
- `func_8000440C` improved 12 to focused zero when the real maximum
  accumulator was declared before the retained largest-block pointer. Debug
  and runtime evidence both confirmed its home moving from -4/SP+4 to
  -8/SP+0 in the same eight-byte frame. Later genuine sibling additions
  changed the stripped C prefix, so the exact 88-byte body now lacks one
  terminal word of its registered 100-byte span, scoring 100. The supported
  reopen transaction restored assembly and preserved the candidate. It was
  never batch-accepted and contributes no new match.

The local free-record view distinguishes the 12-byte allocated header from
free-list links occupying the following payload words. No shared header,
argument narrowing, artificial alignment or reference change was used.

The clean three-function batch returned `BATCH_COMPLETE`: full US ROM match,
1,328 tests run with 12 skipped, metadata, progress and whitespace passed.
This adds **3 functions / 400 bytes**, giving **39 / 2,900 bytes** since the
fresh baseline and **2,672** accepted US C functions. The source remains in
progress with the best deferred candidates retained. No accepted IDs remain
pending at this checkpoint.

## Eleventh batch: scheduler state and completion helpers

Four related members of `init_49E0.c` are newly accepted:

| Function | Bytes | Behavior |
| --- | ---: | --- |
| `func_80004FE0` | 64 | Chooses the pending state or immediate completion path from the observed byte counter |
| `func_80005020` | 128 | Keeps the framebuffer snapshot across the effect callback, swaps it when required, then reloads the global task for the completion message |
| `func_80004DB0` | 336 | Receives a task, checks current/next framebuffer ownership and preserves the scheduler's byte-state gates |
| `func_80004F00` | 224 | Loads/starts the actual task and normalizes the frame counter before sending the scheduler message |

The SDK map and implementations establish the queue, current/next framebuffer
and swap-buffer contracts. The local task view describes only its observed
flags, framebuffer, embedded task bytes and completion fields; it is not
mistaken for the stock scheduler structure, whose offsets differ. The first
three functions matched on their first implementation forms, including the
complete terminal span of `80005020`.

`80004F00` scored 385, 255, 255 and finally 0. Removing a redundant local copy
of the global counter removed an extra value identity; reversing one equality
comparison was code-neutral and discarded. Independent review of the owning
thread then established that globals `D_8003A583` and `D_8003A584` are read
with unsigned byte loads. Correcting their starter-derived signed-byte local
annotations recovered the remaining constant-reuse and register schedule.
This is a data-type correction supported by the actual consumer, not a narrow
parameter workaround. The larger thread remains assembly; reading its switch
and shared-state evidence adds no C match.

A separate sequence wrapper, `800085F8`, is retained at 225. Its actual
channel-off helper consumes the incoming second argument, unlike the starter's
incorrect forwarding guess. The first full-width implementation encountered
the already documented incoming-home mismatch, and no existing declaration
supports narrowing its player index. That exhausted sibling hypothesis was
not repeated, and the candidate contributes no new match.

The clean batch checked all four new scheduler functions and the affected
existing sequence no-op regression: `BATCH_COMPLETE`, full US ROM match,
1,328 tests run with 12 skipped, metadata, progress and whitespace passed.
This adds **4 functions / 752 bytes**, giving **43 / 3,652 bytes** since the
fresh baseline and **2,676** accepted US C functions. Both source units remain
in progress, and no accepted IDs remain pending at this checkpoint.

## Twelfth batch: SP start and transfer completion wait

Two system-I/O functions are newly accepted:

- `func_8000349C` (68 bytes): the actual task-pointer interface, SP-busy poll
  and unsigned hardware-status call, matching on its first source form.
- `func_80004674` (112 bytes): consumes completion messages while re-reading
  the live byte counter. Its initial if/do form scored 120 solely from the
  index initialization schedule; a normal counted for-loop recovered zero.

The reviewed task and transfer families also retain six bounded candidates:

| Function | Best | Remaining evidence |
| --- | ---: | --- |
| `80003220` | 5623 | A coherent SDK task view preserves the real copy input and seven address conversions, but the compiler retains its common base instead of the raw field-address schedule |
| `80003330` | 10 | Literal uncached-segment address versus absolute-symbol HI/LO spelling |
| `80004470` | 70 | Explicit loop-end state improved 655 to 70; address initialization order and the array-end alias remain |
| `800046E4` | 20 | Exact operations and registers with an eight-byte frame/local-address shift |
| `80004514` | 1369 | Three valid control/type forms were code-neutral; incoming size storage and the register cascade remain |
| `8000480C` | 2223 | First typed direct-I/O candidate preserves the interlock and word/halfword copy behavior; layout, scheduling and segment aliases remain |

For `80003330`, independent linkage of the unmodified best candidate at its
registered address produces exactly the complete 364-byte ROM span, SHA-256
`0bd1f0bef956bb81e87810b86b5500858b616b9dc7c1eb6ff894f1cc4bdb21ce`.
The existing symbolic gate still reports CURRENT (10), and its linked-alias
path does not support this main-executable literal-versus-symbol case.
Therefore this remains a diagnostic result: assembly is active, no comparison
or reference tool was changed, and no C match is counted. Expressing the
verified absolute linker symbol directly instead scored 250 and was discarded.

For `800046E4`, object/debug evidence separates the request and response's
actual stack addresses from derived-value homes. Removing a redundant
remaining-count name was code-neutral at 20. Reusing the disjoint queue-index
and transfer-size roles recovered the frame but changed register/control
allocation, scoring 528; the simpler score-20 form is retained.

The direct-I/O candidate's visibility qualifiers have specific protocol
support. The manager thread reads the direct-reader interlock, marks itself
suspended, sets/clears the DMA-active byte and is explicitly resumed by this
helper. Those shared communication bytes, the PI status register and uncached
device reads require observable accesses. No unrelated RAM or local was made
volatile to alter code generation. The 24-byte queue and I/O-message views
come from the SDK contracts, with original full-width arguments retained.

The clean two-function batch returned `BATCH_COMPLETE`: full US ROM match,
1,328 tests run with 12 skipped, metadata, progress and whitespace passed.
This adds **2 functions / 180 bytes**, giving **45 / 3,832 bytes** since the
fresh baseline and **2,678** accepted US C functions. The best candidates,
failed hypotheses and linked-byte diagnostic are preserved. No accepted IDs
remain pending at this checkpoint.

## Thirteenth batch: sound owners, handles and stop callback

Five related `init_EB00.c` functions are newly accepted:

| Function | Bytes | Behavior |
| --- | ---: | --- |
| `func_800109D0` | 108 | Stops the owner's secondary handle, or its matching callback/owner/tag tuple, then clears the handle |
| `func_80010A3C` | 108 | Performs the corresponding primary-handle stop |
| `func_8000EF40` | 116 | Clears the observed record flag and stops/clears an inactive sound before zeroing the callback output |
| `func_800111C8` | 116 | Validates a handle entry, clears its ID/value, stops its actual sound state and clears that state pointer |
| `func_80010894` | 136 | Checks the owner's handle or matching tuple, clearing the stale handle when neither is active |

The owner view preserves only observed fields at 0x3B, 0x8C, 0x8E and 0x318.
The 0x30-byte record and 0xC-byte handle-entry views likewise expose only
observed fields. SDK symbol mappings establish the one-pointer stop helper
and pointer-to-state-pointer query helper, correcting extra starter arguments.
Existing active game declarations for the `func_100111C8` main alias,
including `game_1A6360.c` and the camera source, support `800111C8`'s `u16`
formal. Other handle inputs with active full-width declarations remain `s32`.

`8000EF40` has seven callback argument slots, even though two intermediate
stack arguments are unused. The existing callback declaration and dispatcher's
three stack-argument stores establish that its output is the seventh argument;
the starter's omission of unused slots is not a five-argument contract.

Four functions matched on their first source forms. `800111C8` improved from
18 to 0 by removing a redundant cached state-field value while retaining the
real entry pointer across the stop call, and expressing the field-left ID
comparison. The actual entry-pointer spill moved from SP+0x18 to SP+0x1C with
the same 0x28 frame; no storage was added.

Five bounded candidates remain inactive with assembly retained:

- `8000FE88`: 720 to 18 after direct returns removed the unnecessary result
  local. A real handle snapshot moved the pointer spill but enlarged the frame,
  scoring 20; the simpler score-18 form is preserved.
- `800100E0`: a real count snapshot recovered frameless tuple replacement at
  330, improving the initial 1186. Naming the end pointer introduced a frame;
  omitting the snapshot reloaded the count across writes. Moving only genuine
  declarations was code-neutral, so no further ordering search was attempted.
- `80010F88`: 120 with the supported second-argument `u16` contract and explicit
  value conversions for full-width inputs. Entry normalization scored 670 and
  a signed-short local was code-neutral. The remaining incoming-home schedule
  does not establish narrow formal types.
- `8000F3D0`: 324 with the actual one-argument state query and full-width handle
  normalization. Incoming-value identity remains unresolved.
- `8001123C`: 321 with its existing full-width handle contract, queued-stop
  attempt and immediate-stop fallback. No unsupported narrowing was tried.

The clean batch checked all five new functions and four affected earlier sound
functions: `BATCH_COMPLETE`, full US ROM match, 1,328 tests run with 12 skipped,
metadata, progress and whitespace passed. This adds **5 functions / 584 bytes**,
giving **50 / 4,416 bytes** since the fresh baseline and **2,683** accepted US
C functions. The source remains in progress. No accepted IDs remain pending
at this checkpoint.

## Fourteenth batch: sound callback state and spatial updates

Five more members of `init_EB00.c` are newly accepted:

| Function | Bytes | Behavior |
| --- | ---: | --- |
| `func_800107F8` | 156 | Checks the secondary owner sound, preserving the word-zero early exit |
| `func_8000F1A8` | 160 | Resets sound state, initializes the first sixteen handle-entry sequence fields and stops no-decay playback |
| `func_8000F91C` | 184 | Computes spatial gain and posts the four observed sound parameters |
| `func_8000EB00` | 196 | Seven-slot callback that gates activity and updates the randomized delay/sound fields |
| `func_8001001C` | 196 | Updates pitch and the word value of records matching a callback/owner/key tuple |

`800107F8` and `8001001C` matched on their first forms. The owner view adds
only the observed word at zero. The record view adds its word at 0xC and float
at 0x2C, retaining the proven 0x30-byte stride. The handle-entry view exposes
the initialized halfword at two, retaining its 0xC-byte stride. The reset's
0x180-byte clear and sixteen-entry initialization are kept as distinct observed
operations; neither is used to invent a narrower global-array extent.

The reset improved from 300 through 460 to 0. An indexed initialization loop
removed a redundant named cursor and recovered the compiler's exact unrolled
loop. Chaining the final flag resets recovered the address materialization,
but the starter-derived signed-byte annotations introduced an extra reload.
The actual consumer, `80011BB8`, reads both `D_80041F60` and `D_80041F61` with
`lbu` and copies one into the other. Correcting those local declarations to
`u8` removed the reload and produced full-span zero. This does not narrow a
parameter or add storage.

`8000F91C` uses the existing active runtime-alias declaration: only the first
formal is `u16` and the third is `s16`; the remaining formals stay full width
with explicit value conversions. The first two forms scored 10 from one
commuted multiply. Reversing the nested expression was code-neutral. Naming
the real returned scale before the unsigned multiplication recovered the raw
operand order, with the original frame and output-word address unchanged.

`8000EB00` preserves all seven callback slots and uses the actual no-argument
unsigned PRNG contract. Its initial score of 65 was entirely register identity.
Removing the redundant remaining-timer local, while retaining direct state
updates and the actual state pointer across both calls, recovered zero.

Eleven bounded candidates remain inactive with their best forms retained:

| Function | Best score | Unresolved evidence |
| --- | ---: | --- |
| `8000F44C` | 425 | Full-width handle reload/normalization versus a raw halfword reload |
| `8000FF90` | 290 | Single-loop control recovered from 1355; pointer/count/owner allocation remains |
| `8000F4D8` | 40 | Existing `u16` declaration reduced 435; endpoint address schedule and equality order remain |
| `8000F9D4` | 1794 | Full-width wrapper argument homes and conversion schedule |
| `8000FDF4` | 956 | Normalized handle identity and count/register schedule |
| `8000FEF0` | 2265 | Frameless candidate versus raw saved-register state |
| `8000EC24` | 888 | Stack-supplied output-pointer promotion/reload; the timer snapshot before possibly aliasing stores is preserved |
| `8001091C` | 210 | One incoming-value reload and coherent array-member address spelling |
| `80010E78` | 855 | Direct returns recover the 0x30 frame; argument-expression temporaries remain |
| `8000FD38` | 280 | Count reload placement around callback and record writes |
| `8000F85C` | 3166 | Event-parameter storage, spill schedule and coherent state-member address spelling |

The local `80010BE8` return annotation now reflects every raw exit: zero or an
unsigned-halfword handle. Its full-width parameter annotations are unchanged.
This supports a deferred candidate and adds no match by itself. No unsupported
parameter narrowing, array extent, overlapping global, volatile reload,
permutation search or compiler/reference change was used.

Object-symbol review confirms that the reset calls `sndp_stop_nodecays(void)`
at US 0x176EC, rather than the adjacent `sndp_stop_all` at 0x176C4. The exact
callee contract has no arguments; the loop-bound value remaining in a register
is not an argument. The cents conversion and sound-event contracts also agree
with their pinned library definitions.

The clean batch checked all five new functions and eight affected earlier
functions: `BATCH_COMPLETE`, full US ROM match, 1,328 tests run with 12 skipped,
metadata, progress and whitespace passed. This adds **5 functions / 892 bytes**,
giving **55 / 5,308 bytes** since the fresh baseline and **2,688** accepted US
C functions. The source remains in progress. No accepted IDs remain pending
at this checkpoint.

## Fifteenth batch: owner cleanup and callback evidence

This ten-function related pass adds `func_80010AA8` (320 bytes), matching on
its first form. It stops both owner handles through the direct-state or
record-lookup paths and clears both fields. The real record index stays live
across the query/stop calls; the subsequent record pointer serves the observed
read/modify/write. Those states are retained rather than mechanically removing
every local name.

The source-local owner view now also describes floats at 0x14/0x18/0x1C and
the word at 0x184. The callback copies those coordinates to record halfwords
2/4/6, and checks the owner's word zero and byte 0x3B against the saved key's
low byte. These are offset and behavior findings, not character/model names.
The record view also exposes the unsigned halfword at eight without changing
its 0x30-byte stride. No shared project header was changed.

Nine other bounded results are retained with assembly active:

| Function | Scores | Result |
| --- | --- | --- |
| `8000EDA0` | 925, 325, 85 | Full-width normalized timer state preserves both observed sign extensions; removing a redundant packed-word name leaves only register differences |
| `8000EE70` | 350, 700, 120 | An eager full-word masked-key snapshot recovers the raw control flow; a byte cast instead narrowed the load and was discarded |
| `8000ECCC` | 55, 55, 55 | Shared timer pattern matches all operations; chained halfword writes and a consumer-supported unsigned header field do not resolve allocation |
| `80010558` | 1530, 1530, 1530 | Existing first-`u16` contract retained; alternate supported helper annotations and a named handle are code-neutral |
| `80010720` | 2202 | Full-width sibling input retained; the exhausted neighboring wrapper experiments were not repeated |
| `80011EB8` | 885, 100 | Keeping the selected sound full-width until the final mask recovers every body instruction; one terminal alignment `nop` is still missing |
| `80010630` | 2124, 2195 | Naming the flags word does not recover the raw saved-volume lifetime; simpler first form retained |
| `8000FC18` | 1281 | Existing signed-coordinate-only contract retained; first/fifth inputs remain full-width values |
| `8000F568` | 1085, 495, 725 | Word-sized availability improves the nonrepeating selector; collapsing its initial-byte and mask identities worsens allocation |

`80011EB8` is **not accepted**. Its 228-byte instruction body is exact, but
acceptance covers the full registered 232 bytes. The current genuine C prefix
leaves no final padding where the reference has one `nop`. Its best object,
source and layout evidence are preserved for a later genuine neighboring-C
change; no padding or comparison exception was introduced.

The selector's actual contracts are one full-width argument for the game-side
mapping helper and two full-width arguments for `8000F568`, correcting the
starter's surplus arguments. The nonrepeating selector preserves its initial
unsigned remainder, signed retry remainder, byte-state stores and required
global-base reload after the potentially aliasing byte write.

The coherent source-type/candidate pass is checkpointed before moving to a
different family. Its clean batch checked the new function and six affected
earlier functions: `BATCH_COMPLETE`, full US ROM match, 1,328 tests run with
12 skipped, metadata, progress and whitespace passed. This adds **1 function /
320 bytes**, giving **56 / 5,628 bytes** since the fresh baseline and **2,689**
accepted US C functions. No accepted IDs remain pending; the source remains
in progress.

## Sixteenth batch: memory-limit initialization and C integration

`func_80003930` (128 bytes) matched on its first source form. It uses the
observed unsigned byte flag to select the two memory-limit address sets and
preserves all four global stores in each branch. The independent comparison
covers the complete registered span, including its natural final alignment.

This singleton's terminal action explicitly required integration. The
supported integration transaction moved it to `src/game/done/init_3930.c`,
changed only its existing profile entry from assembly to C, and marked the
reviewed source unit complete. The resulting complete US ROM was byte-identical.
No boundary was enlarged or newly inferred, and no reference or compiler flag
was changed. Progress and whitespace were rechecked after the transition.

The adjacent allocator initializer `80003BD0` remains deferred at 1520. Its
source-local header and free-link views agree with the already reviewed
allocation operations. The compiler coalesces repeated global-head loads that
remain in the raw routine. An opaque heap-start view with sequential final
copies scored 1915; aligned word initialization was code-neutral at 1915.
The clearer, lower-scoring typed form is preserved. No forced volatile access
or fabricated alias was introduced, and this initializer is not integrated.

The first clean batch exposed a boundary-test assumption that every non-library
main entry must retain its assembly tuple. The test now accepts a C transition
only for the identical raw assembly interval and successor, with one reviewed
complete source unit, exact source ownership, and contiguous zero-difference
matched-member coverage. Rejection cases cover missing or unreviewed metadata,
misnamed sources, changed extents, invalid members, gaps and overlaps. The
reference maps and function comparator are unchanged. This narrow correction
received independent review before acceptance.

The fresh clean retry passed: `BATCH_COMPLETE`, full US ROM match, 1,332 tests
run with 12 skipped, metadata, progress and whitespace. This adds **1 function /
128 bytes**, giving **57 / 5,756 bytes** since the fresh baseline and **2,690**
accepted US C functions. The memory-limit source unit is integrated; the
allocator initializer remains an assembly-backed candidate. No accepted IDs
remain pending.

## Seventeenth batch: thread context initialization

`func_800037F0` (208 bytes) uses a source-local partial view of the SDK thread
layout. The first form scored 1114. Restoring the SDK initialization order,
with priority immediately after ID, and its unsigned 64-bit saved-register
storage produced a full-span zero. Argument and address conversions still
sign-extend through `s32`/`s64`, and the initial stack subtracts 16 in 64-bit
arithmetic. The thread pointer and saved interrupt mask are genuine state.

The pinned interrupt object at 0x22DC0 establishes the no-argument disable
helper and one-argument restore helper at 0x22DE0. They enclose insertion into
the active-thread list. The raw `D_10007BF8` address remains opaque and exact;
its use in the saved return-address slot does not establish a semantic symbol
name. Independent review checked the partial layout and these contracts.

The mandatory integration moved this complete singleton to
`src/game/done/init_37F0.c`, preserving the reviewed 0x37F0–0x38C0 interval.
The resulting full US ROM was byte-identical.

The AI-buffer wrapper `80002DB0` remains assembly-backed at 845. Pinned SDK
source establishes a no-argument busy helper and the real buffer pointer held
across that call. Ordinary direct MMIO symbols worsened the result to 1060;
the SDK-style literal volatile MMIO form scored 855. The best symbol-based
hardware-register view is retained. The ordinary workaround flag still has
an address-allocation difference; no unsupported volatile flag or new data
ownership was introduced.

The clean batch checked the new initializer and rechecked `80003930`:
`BATCH_COMPLETE`, full US ROM match, 1,332 tests with 12 skipped, metadata,
progress and whitespace passed. This adds **1 function / 208 bytes**, giving
**58 / 5,964 bytes** since the fresh baseline and **2,691** accepted US C
functions. Both reviewed initializer units are integrated, and no accepted
IDs remain pending.
