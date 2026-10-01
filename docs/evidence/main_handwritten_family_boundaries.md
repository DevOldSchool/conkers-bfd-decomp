# Main handwritten families and retained interior entries

Evidence kind: `structural_analysis`. This review establishes three complete
working assembly families, 23 registered non-overlapping raw spans and 9,840
bytes. It does not claim 23 independently callable ordinary C functions or
recover historical filenames. Four ordinary-looking spans remain C candidates;
nineteen spans with positive privileged-instruction or custom-ABI evidence
are retained as verified original assembly.

## Boundary and indexing reconciliation

The original unsplit IDO disassembler index merged `0x5AB0/0x5B04` and crossed
both `0x6240` and `0x71D0` from `0x5C2C`. Independently disassembling each range
limits that overrun, but still merges real called entries such as `0x632C`
and `0x6E00`. These heuristic merges are not evidence of C or object ownership.
Direct call sites, explicit ABI state and complete raw instruction coverage
provide the positive reconciliation below. No symbol is added to force the
heuristic CSV to agree.

Every raw instruction word in all three ranges was compared to the
checksum-validated owned US ROM. The declared raw spans tile each range
without gaps or overlap, and no whole-main conditional branch crosses any
outer endpoint. The unchanged canonical image rebuilds byte-identically with
the [restored pinned toolchain](main_original_assembly_verification.md).
The existing raw navigation boundaries and the separately reviewed predecessor
and successor units are retained. The
[legacy map](https://github.com/mkst/conker/blob/3adf229175c037c771f251f169f9dd80ca306924/conker/conker.us.yaml)
is corroboration only; the state and control-flow evidence is independent.

| Working source | ROM range | Spans | Bytes | Range SHA-1 |
| --- | --- | ---: | ---: | --- |
| `src/main/init_5AB0.c` | `0x5AB0:0x6240` | 5 | 1,936 | `606fc04031e435f934367d80488511f98b84ab67` |
| `src/main/init_6240.c` | `0x6240:0x71D0` | 10 | 3,984 | `9173af2c49f456f4e3fea86b683c67a32ccb95a3` |
| `src/main/init_71D0.c` | `0x71D0:0x8120` | 8 | 3,920 | `be1a90de1505b7bc25bf9222b7324aa0f5fdde93` |

## TLB setup and demand-paging family, `0x5AB0:0x6240`

The ROM entry selects `0x80005AB0` at `0x1024/0x102C` and jumps there at
`0x1030`. That member installs the fixed TLB index-zero main-code alias and
transfers to `0x10001050`. The allocator/setup member `0x5B04`, directly called
from `0x13EC/0x1520`, programs the wired limit to two, excluding the two fixed
aliases from random replacement. It creates the backing-page bitmap and pool
state at `0x8003BE70/74/78/7C`.

The bitmap initializer `0x5BE0` consumes those exact fields; it is called by the
startup and recovery paths. The exception-selected `0x5C2C` (call at `0x7708`)
uses the same bitmap/pool and page table at `0x80043B40`, invokes the local
page-load/decompression path, updates CP0 mappings and resumes the faulted
operation. Its eviction continuation shares that page table and transfers back
into the fault path. The final `0x61F8` invalidates an explicit TLB index range
while preserving EntryHi and is selected by the same bootstrap paths at
`0x1074/0x145C/0x14E0`. The bitmap loop itself is left raw for possible C work;
all other spans have explicit CP0 instructions.

## Shared-frame decompression family, `0x6240:0x71D0`

The wrapper at `0x6240` calls `0x625C` at `0x6248`; it is used by main startup
and multiple game resource loaders. `0x625C` recognizes the `0x1172` stream
header, allocates a `0xA88`-byte shared frame, and keeps stream/output state in
saved integer and floating-point registers. Its internal dispatcher `0x632C`
stores its return address inside that existing frame at `sp+0xA6C`; the next
helper `0x6380` similarly uses `sp+0xA68`, not an independent C stack frame.

The positive call chain reaches every raw span: `0x625C -> 0x632C -> 0x6380`,
then `0x6380 -> 0x6424/0x6828/0x692C`; `0x6424 -> 0x696C/0x6E00` and
`0x692C -> 0x6E00`. The bootstrap-selected constructor `0x709C` builds the
shared decode tables at `0x8003BE90`, reuses the same `0xA88` frame layout and
calls `0x696C` at `0x714C/0x7194` with additional arguments in `$t8/$t9`.
These specific shared-frame/register contracts establish one working assembly
family. The ordinary outer wrapper remains raw; the nine custom-ABI spans
are preserved as original assembly.

## Exception, dispatch and diagnostic family, `0x71D0:0x8120`

SDK initialization selects the `0x100071D0` trampoline at `0x2283C:0x22898`.
It transfers through `$k0` to `0x100071E0`, saves privileged CPU context, and
uses the current-thread and run-queue objects at `0x8002BE00/0x8002BDF8`.
The exception dispatcher, fatal path, queue operations and context restore
consume the same thread layout. The eight words at `0x2C1D0:0x2C1F0` select
`0x7728, 0x76E0, 0x76B8, 0x74DC, 0x74C0, 0x7648, 0x7478, 0x7488` through
main runtime aliases; every target is inside the dispatcher span.

Fatal path `0x777C` calls diagnostic `0x7DAC` at `0x779C`. The diagnostic in
turn calls the local hexadecimal/string and glyph helpers. Those use a custom
return register and shared framebuffer/font state, rather than independent C
ABIs. The `0x7DA0` public entry deliberately executes `syscall`. Queue helpers
`0x79D8/0x7A24` remain raw candidates; their specific use by the dispatcher
and scheduler proves working-family membership without requiring original-ASM
classification. The remaining six spans have explicit privileged instructions,
custom return-register contracts or owned interior entries with those contracts.

## Interior entries retained within their owning spans

Indentation in disassembler output is not an ABI classification. The table
accounts for every indented global label and the additional computed entries.
They remain present in the unchanged full-span assembly proofs. They are not
silently dropped or promoted to new C functions.

| Interior address(es) | Owning registered span start | Positive role/evidence |
| --- | --- | --- |
| `0x5B3C` | `0x5B04` | Allocation retry from direct jump `0x5B68`; requires the parent's saved stack and `$s0` |
| `0x5D20`, `0x60F0`, `0x6138` | `0x5C2C` | Internal paging/eviction continuations reached by jumps `0x61E8`, `0x60D0`, `0x5CEC` |
| `0x62F0` | `0x625C` | Shared-frame restoration/return, reached by `0x6324` |
| `0x6418` | `0x6380` | Common epilogue reading the parent's `sp+0xA68` return slot |
| `0x6750`, `0x681C` | `0x6424` | Internal loop/error continuations selected by direct jumps |
| `0x6C40`, `0x6CB8`, `0x6CBC`, `0x6D48`, `0x6D74`, `0x6DBC` | `0x696C` | Local decode-table construction continuations, each directly jumped to within this span |
| `0x6E2C`, `0x6E30` | `0x6E00` | Shared bitstream/decode loops, selected by jumps `0x6EF8/0x7080` |
| `0x71E0` | `0x71D0` | Computed main-alias trampoline target at `0x71D0:0x71D8` |
| `0x7760` | `0x71D0` | Recovery continuation selected at `0x8084/0x8088` and installed in saved return state |
| `0x77B8` | `0x777C` | Thirteen direct JAL sites in the exception family; saves `$ra` in `$s2` and returns with `jr $s2` at `0x7874` |
| `0x78B4` | `0x777C` | SDK scheduler calls including `0x22B8C/0x22C6C/0x22E74`; saves thread CPU/FPU context and transfers to dispatcher |
| `0x7BF8` | `0x7A38` | Thread-return trampoline selected by `0x3828/0x382C`; follows privileged `eret` path physically but has its own entry contract |
| `0x7C04` | `0x7A38` | Computed helper called by `jalr $t3,$t0` at `0x7C80/0x7CCC`; normal helper return is `jr $t3` at `0x7C64` |
| `0x7CC4` | `0x7C74` | String helper with six direct diagnostic JAL callers; preserves return in `$a1` and returns through that register |
| `0x7D28` | `0x7C74` | Glyph helper selected by JAL at `0x7CA4/0x7D0C`, consuming the caller's `$t1/$t2/$t4` state |
| `0x7F70` | `0x7DAC` | Deliberate internal self-loop, not a callable function |

The interrupt-table local targets above are also retained in their owner.
Direct jumps, conditional branches and computed continuations are explicitly
distinguished from ordinary independent function entries. This review does not
change the parser or create overlapping inventory records for these labels.

## Complete registered spans

`raw_asm` below leaves an ordinary candidate available. `original_asm` requires
an actual full-span assembled/link/ROM proof, including all its interior entries.

| Span | State after verification |
| --- | --- |
| `0x5ab0:0x5b04` | `original_asm` |
| `0x5b04:0x5be0` | `original_asm` |
| `0x5be0:0x5c2c` | `raw_asm` |
| `0x5c2c:0x61f8` | `original_asm` |
| `0x61f8:0x6240` | `original_asm` |
| `0x6240:0x625c` | `raw_asm` |
| `0x625c:0x632c` | `original_asm` |
| `0x632c:0x6380` | `original_asm` |
| `0x6380:0x6424` | `original_asm` |
| `0x6424:0x6828` | `original_asm` |
| `0x6828:0x692c` | `original_asm` |
| `0x692c:0x696c` | `original_asm` |
| `0x696c:0x6e00` | `original_asm` |
| `0x6e00:0x709c` | `original_asm` |
| `0x709c:0x71d0` | `original_asm` |
| `0x71d0:0x777c` | `original_asm` |
| `0x777c:0x79d8` | `original_asm` |
| `0x79d8:0x7a24` | `raw_asm` |
| `0x7a24:0x7a38` | `raw_asm` |
| `0x7a38:0x7c74` | `original_asm` |
| `0x7c74:0x7da0` | `original_asm` |
| `0x7da0:0x7dac` | `original_asm` |
| `0x7dac:0x8120` | `original_asm` |

## Reproduction and gates

For each source/range row, replay `./conker register-source-unit --overlay main
--register-members --source <source> --us-start <start> --us-end <end>
--evidence-kind structural_analysis --evidence-reference
 docs/evidence/main_handwritten_family_boundaries.md`. For each original span,
run `./conker verify-original-asm <id>` with the relevant privileged/shared-ABI
reason and this evidence reference, then one clean `verify-batch` over that group.

All three source units remain canonically raw. No canonical/reference split,
C implementation, C-match count or matched-byte total changes. Raw aliases are
preserved inside their owning spans; future C work must not cross a retained
original span or remove its interior entry contracts.

All nineteen original spans passed independent assembled/link/ROM proof and
one clean `BATCH_COMPLETE`: full US ROM equality, 1,070 tests (12 declared
skips), metadata/progress and whitespace gates. Four ordinary spans remain
raw candidates, and no C matching credit is added.
