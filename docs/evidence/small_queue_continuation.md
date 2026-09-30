# Small ready-queue continuation — 2026-09-30

The user approved continuing the small-function queue after the two bounded
workflow trials. Two isolated source streams retain one canonical integrator.
Each target is screened against prior attempts and exact raw instruction
fingerprints; the initial source and at most two evidence-backed revisions
remain the normal limit. This is ongoing matching, not another controlled
throughput experiment.

## First related group

Seven fresh 480-byte targets received 17 manual C variants. Two reached full
registered-span `CURRENT (0)`; five best candidates were preserved disabled,
with original assembly active. One simultaneous selection was resolved before
any source edits: the worker retained `game_16EE20.c`, and the integrator
excluded that exact file and selected another target. No shared implementation
checkout or generated-state merge was used.

### New focused matches

- `func_150AE5B0`, `src/game/game_DBA60.c`: 80 → 0. A source-local partial camera
  type and existing variadic/camera helper declarations preserve the observed
  ABI. Moving the independent flags-at-0x84 update before the flags-at-0x2C
  read recovers the raw load order and schedule. The mixed unit remains mixed
- `func_1519003C`, `src/game/game_1BC650.c`: 210 → 0. A direct switch on the
  existing byte field removes a redundant selector temporary. The integrator
  independently reproduced the worker's zero result. This mixed unit also
  remains mixed

The second function adds two adjacent ROM-backed switch tables to an already
reviewed external-rodata section. The old strict size assertion correctly
blocked the initial full build. Both independent audits resolved every old
and new relocation and agreed on all 290 table words, their exact contiguous
0x488-byte payload, and eight zero alignment bytes. The mapping base is
unchanged; only the proven section/payload extents change. See
[the complete ownership and byte proof](game_1bc650_jump_tables.md).
The earlier `func_1518FDC4` was independently rechecked at `CURRENT (0)` and is
included as a regression in the clean batch; it is not a new match.

### Preserved candidates

| Target | Source | Scores | Remaining evidence |
| --- | --- | --- | --- |
| `func_1511D9E4` | `game_1483E0.c` | 2310, 1630, 1400 | Separate allocation/output pointers recover entry flow; byte strides and real intermediate values improve loop shape, but scalar allocation and joins differ |
| `func_1514C678` | `game_1797A0.c` | 4012 | Stopped after the initial candidate: existing full-width formal declarations do not support the narrow-formal hypothesis; explicit use-site casts retain different normalization lifetimes |
| `func_1517F814` | `game_1AC2F0.c` | 338, 234, 368 | Natural viewport/coordinate types give the same control flow; actual local ordering improves stack offsets, but frame and clamp FP allocation differ |
| `func_15114D24` | `game_13F9D0.c` | 1248, 1884, 1180 | Worker tested stopped-sound-handle lifetime and a real fullword handle local; integrator reproduced 1180 |
| `func_1514654C` | `game_16EE20.c` | 2722, 2730, 1533 | Typed records/matrices, nested selection and a reused model/child pointer improve the candidate; frame/register differences remain; integrator reproduced 1533 |

The narrow-formal issue was deferred early rather than treated as a quota for
more variants. No artificial padding, permutation search, assembly edits,
compiler changes or shared-header changes were used. Existing raw switch gates
and all acceptance checks remain in force.

### Clean acceptance

The canonical group consists of the two new matches and the existing
`func_1518FDC4` regression. Its final clean-batch result is recorded below.


The canonical clean gate returned `BATCH_COMPLETE` at 21:41:09 UTC on
2026-09-30, taking 76.680 seconds. The complete 2,072,880-byte US game-code
image and every mapped external-rodata payload matched the owned ROM. The
expanded 1BC650 section verified 1,160 payload bytes and eight zero-alignment
bytes. All 1,092 tests passed (12 skipped), with metadata, generated progress
and whitespace passing. This group adds **two batch-verified functions / 960
bytes**, with no new complete source unit. The old switch is a regression only;
all five disabled candidates add no matched bytes. Pending batch IDs were
cleared only after this clean success.
