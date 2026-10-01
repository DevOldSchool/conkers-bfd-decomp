# US main allocation, transfer and controller working units

Evidence kind: `structural_analysis`. Five working source units cover twenty-six
entries and 8,032 bytes across six former navigation ranges. These neutral
source names assert complete working memberships, not original filenames or
matching implementations. All members remain raw assembly in the canonical
main build. Neither canonical nor reference map changes.

## Inputs and verification

Use the same checksum-validated US ROM, separately generated split raw assembly,
unsplit spimdisasm 1.33.0 IDO index, whole-main branch decoding, and normalized
main/game direct-call scan described in
[the first main batch](main_system_wrapper_boundaries.md). Every raw word
matches the ROM; raw and independent unsplit starts and full spans agree.
Complete memberships cover the listed ranges without gaps. All outer endpoints
are 16-byte aligned; no conditional branch crosses them in either direction.
No direct call from either CPU image enters one of these ranges at an unlisted
function start. Address-selected thread entries and switch targets are checked
below. These checks do not assign data, rodata or BSS to a source object.

The [legacy map at mkst/conker
3adf229175c037c771f251f169f9dd80ca306924](https://github.com/mkst/conker/blob/3adf229175c037c771f251f169f9dd80ca306924/conker/conker.us.yaml)
corroborates all five outer working ranges. In particular, it keeps the entire
`0x5570:0x5AB0` motor family together rather than requiring the later internal
navigation split at `0x57E0` to be an original object boundary.

## Complete memberships

| Source | US ROM range | Member starts (prefix `func_800`) | Bytes | Range SHA-1 |
| --- | --- | --- | ---: | --- |
| `src/main/init_3C40.c` | `0x3C40:0x4470` | `03C40`, `03C6C`, `04074`, `04250`, `04308`, `043B4`, `0440C` | 2,096 | `ed85dada4f63f147cdfcb4e401329a09047d29c6` |
| `src/main/init_4470.c` | `0x4470:0x49E0` | `04470`, `04514`, `04674`, `046E4`, `0480C` | 1,392 | `d56079b413c1b9a17aeb1058e4f67d286386ac66` |
| `src/main/init_49E0.c` | `0x49E0:0x50A0` | `049E0`, `04DB0`, `04F00`, `04FE0`, `05020` | 1,728 | `b563e8c2f8b28b748c447906a905480786bcaf85` |
| `src/main/init_5570.c` | `0x5570:0x5AB0` | `05570`, `056A0`, `057E0`, `05948` | 1,344 | `6afa39725155de37ce16933e64ef528dc6b248bc` |
| `src/main/init_11FA0.c` | `0x11FA0:0x12560` | `11FA0`, `11FB0`, `11FDC`, `11FEC`, `12020` | 1,472 | `01603766952812ab69a10c01690ccb6f2cb094d6` |

## Structural membership evidence

### Allocation and tagged-list operations, `0x3C40:0x4470`

The seven entries form an allocation/free/list-maintenance API over the same
record format and list heads, not just neighboring users of an SDK primitive.
`0x3C40` wraps `0x3C6C`; the allocator calls `0x440C` to update the largest
free-block state at `0x800380B0` and `0x8002AC30`. Allocation and free operations
maintain heads at `0x800380B4/0x800380B8/0x800380BC`. The `0x4250` and `0x4308`
walkers call the `0x4074` free operation; the latter passes record base plus
`0xC` at `0x4378:0x437C`. The separate `0x43B4` entry writes the allocation tag
into the high byte at user pointer minus four (`0x43D8:0x43F0`), matching the
tag extraction used by the walkers. Thus it belongs to the same record API
although it has no direct call edge to another member. All seven have reviewed
callers; the allocator has the bootstrap caller at `0x12D8`.

### Transfer initialization and queue operations, `0x4470:0x49E0`

`0x4470` initializes the PI manager and queue state, including the queue at
`0x800388C8`, ring state near `0x80038908`, and transfer flags
`0x8003A570/0x8003A571`. `0x4514` submits a transfer and invokes local helper
`0x480C` at `0x4558`; `0x4674` consumes the same completion queue and active
flag; `0x46E4` uses the same ring state for another transfer path. `0x480C`
coordinates the backing manager's `0x8003A572/0x8003A573/0x8003A575` state.
Each of these five entries has a direct external caller in the scanned CPU
images, and the complete initializer/submit/wait/helper grouping agrees with
the legacy source interval. No layout padding is added or storage allocated.

### Scheduler thread and local handlers, `0x49E0:0x50A0`

All five entries belong to one connected local-call component. The thread
entry `0x49E0` calls `0x4DB0`, which calls `0x4F00`; the family also calls
`0x4FE0`, which calls `0x5020`. The adjacent initializer constructs
`0x100049E0` at `0x5188:0x5194` and passes it to the thread constructor at
`0x51A4`. The seven words at ROM `0x2C0A0:0x2C0BC` are switch targets wholly
inside the first member (`0x49E0:0x4DB0`), not additional entries. They are
reviewed references only; their source ownership remains outside this claim.

### Motor packets and initialization, `0x5570:0x5AB0`

The two submission routines at `0x5570` and `0x56A0` send channel-indexed
64-byte packets from `0x8003BC30` and `0x8003BD30`, respectively. The initializer
at `0x57E0` constructs both exact packet families: calls to local builder
`0x5948` at `0x5904` and `0x5928` receive these same bases plus channel times
64. The two templates use state at `0x8003BE30` and `0x8003BE50`. This complete
producer/consumer relationship accounts for all four members. The SI access
and packet structure corroborate the legacy motor lineage, without claiming
a matching stock object. Existing external callers select both submission
routines and the initializer. The internal `0x57E0` navigation split is retained
in both maps; the reviewed working unit deliberately spans it.

### Shared-state setters, reset and dispatcher, `0x11FA0:0x12560`

Three entries set the state at `0x80042770`, `0x80042774` and `0x80042778`.
The `0x11FEC` reset clears those same values and the phase at `0x8004277C`.
The `0x12020` dispatcher reads and updates the same state throughout its
complete span, providing the membership relationship despite no local calls.
All five entries have direct callers in main or game code; examples are main
`0xB7C4` and game offsets `0x25B94`, `0x74694`, `0x7EA0`, `0x19118`.
The five targets at ROM `0x2C410:0x2C424` all lie inside the dispatcher.
The next `0x12560` family uses a distinct stream/callback state beginning at
`0x800427A0`; no membership is inferred across that outer boundary.

## Withheld neighboring work

The independent unsplit index identifies an eight-byte entry at
`0x5298:0x52A0` that the split raw assembly leaves inside `0x5218`. Therefore
`0x50A0:0x5570` is not registered in this batch. Handwritten TLB/control code
beginning at `0x5AB0` also causes the unsplit IDO analysis to merge through
several later navigation ranges; those ranges need separate entry evidence
and symbol reconciliation, not automatic registration. Larger audio/dispatch
ranges and the mixed `0x12560:0x12820` interval remain under review.

## Registration and verification

Replay each table row through `./conker register-source-unit --overlay main
--register-members` with its source and bounds, `--evidence-kind
structural_analysis`, and this document as the evidence reference. Do not
replace inventories wholesale when reconciling concurrent game matching.

The checkpoint changes only evidence, skeletons, inventory and generated
progress. No runtime source, map or build settings change. All 75 project-state
tests and 13 segment-map tests pass, generated progress is current, and
whitespace checks pass. A full main build is not claimed: the cloud CPU image
lacks the RSP extension. No source unit is integrated before every member
matches and its supported complete-unit build passes.
