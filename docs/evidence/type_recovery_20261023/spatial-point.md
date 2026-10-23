# D_800D2104 spatial coordinate recovery (US, 2026-10-23)

The shared spatial-record lead reduces the current measured deferred score sum
by **35**, from **2,792,129 to 2,792,094**, with no regressions or new matches.
The PR total is **2,532** against its original 2,794,626 baseline, with one
earlier 420-byte C match.

## Measurement

Continuation commit: `428eb12f7e4090a20827babc9cdafd12354bb1df`.
The comparison point is [root-owner-followup-final.tsv](root-owner-followup-final.tsv),
SHA-256 `b86baeadfbb5e1ac942177a133ef3b891eafac7dd57476269ae66344d0f6ab90`.
All comparisons use measured `new` columns, not stored inventory annotations.

| Scope | Scored candidates | Before -> after | Reduction | New matches |
| --- | ---: | ---: | ---: | ---: |
| `func_150B1484`, `src/game/game_DE5A0.c` | 1 | 1,000 -> 965 | 35 | 0 |
| All candidates in both retained sources | 7 | 11,577 -> 11,542 | 35 | 0 |
| Initial three-source trial, including neutral writer | 35 | 51,314 -> 51,279 | 35 | 0 |
| Full current-baseline comparison | 1,334 | 2,792,129 -> 2,792,094 | **35** | **0** |

The [complete exact sweep](spatial-point-final.tsv) has the same 1,383 deferred
rows, 1,334 measured scores, 49 compiler failures and four pre-existing zeros.
Only `func_150B1484` changes. The full scorer takes 127.0 seconds, excluding
research, audits and delivery. The neutral `game_981E0.c` writer trial is
restored exactly; all 35 candidates in the trial sources are then rescored
in 4.4 seconds and agree with the full sweep. This confirmation covers the
final restored-source state without another redundant full scan.

## Shared contract and matched evidence

`include/game_path.h` recovers `GameSpatialPoint`: signed 16-bit X/Y/Z at
0/2/4 and two opaque metadata bytes at 6, total size 8. It declares
`extern GameSpatialPoint **D_800D2104`. This is a pointer table of spatial
record sequences, not a generic resource/script table. Record zero has
origin/bounds uses; indexed points commonly start at byte 8. Their coordinate
prefix agrees, while the metadata remains deliberately unmodeled.

Matched `func_15077DBC` in `game_A28B0.c` proves signed coordinates and an
8-byte row stride. Independent `reference/game/us/asm/75400.s:3003..3063`
contains `lbu` selectors, pointer-slot stride four and signed `lh` coordinate
reads at 0x15077E10/0x15077E48/0x15077E80 from offsets 8/A/C after row indexing.
Matched `func_15079790` independently reads signed X/Z from record zero.
Matched `func_1507B974` reads an unsigned halfword at +6 (raw `75400.s:7256`),
so the final bytes are real metadata, not padding. The main `SpatialPoint`
reader in `init_A420.c` is **deferred corroboration only**. It was initially
mistaken for matched evidence during research; that classification was
corrected before adopting or validating this definition.

The allocator in `game_43D00.c` creates the pointer table, initializes some
rows as 0x10-byte blocks with two records, and installs other row pointers
into loaded data. The shared declaration imposes no ownership/lifetime rule.
The header replaces its local `void **` declaration. Adding `game_functions.h`
in the initial include block follows source-context rules; every candidate
is recompiled to check the effect.

The height reader in `game_DE5A0.c` replaces byte casts with the shared signed
Y field. `base + selector*8 + 0xA` becomes `[selector + 1].y`; a byte selector
of 255 promotes to int and becomes index 256, preserving the address without
truncation. There is no new local, statement reorder or control-flow change.
The paired compiler objects retain the same 0x38 frame and halfword reads;
address-add operand order and temporary-register choices account for the
35-point reduction. The function remains a nonzero candidate.

This assembles a coordinate prefix from independent matched field/stride
evidence; it does not promote a padded private owner or rename matched bodies.
A read-only independent worker reviewed the prefix, metadata and selector
edge. A separate read-only worker researched future prototypes. Neither
worker edited, compiled, ran inventory transactions or shared implementation
ownership. The user authorized multiple workers during this continuation;
all builds and mutations remain serial.

## Rejected placed-object recovery

Before the spatial trial, a new 0xA0 `D_800DBEF4` owner was tested from matched
resource, position, radius, flag and ID readers, keeping callback/payload
areas opaque. Neither bounded hypothesis improved scores. All nine sources
were restored exactly and the trial-only header removed. The layout is not
retained merely for nominal compatibility. [Every score](placed-object-rejected.tsv).

| Hypothesis | Scored cohort | Result |
| --- | ---: | --- |
| Shared fields and indexed root in `305D0`, `30E90`, `1AFC80`, `1B1600` | 17 | 35,035 -> 36,391 (+1,356). `func_150045C4`: 2,967 -> 3,368; `func_15182C5C`: 7,594 -> 8,549. Others unchanged. Restore. |
| Typed record differences/indexing in `305D0`, `1B5CC0`, `11FF10`, `131F30`, `111670`, `147470` | 21 | 37,415 -> 37,415. Restore; four resource-walker rows overlap the first cohort. |
| Spatial coordinate writer `game_981E0.c` | 28 | Every candidate unchanged, including `func_1506D2E8` at 650. Restore; no retained header change affects that source's 298 matches. |
| Broad spatial editor or erroneous address-of-root variants in `game_83300.c` | Not attempted | Four baseline prototype errors already block the every-candidate-compiles gate there. Keep the editor's existing view and do not impose a flat full payload. |

No rejected source, speculative placement owner or trial header remains.
No scored compiler error is counted as a numerical improvement.

## Validation

Both retained sources contain **zero matched C functions**, so neither has
a matched function to nominate. Their original GLOBAL_ASM pragmas remain.
A nine-pair pinned compiler audit covers both canonical sources and all seven
individually activated candidates: zero compile errors, zero cfe warnings
before or after. A pinned IDO/o32 data-object probe verifies all seven facts:
record size 8, pointer-slot size 4, member offsets 0/2/4/6, alignment 2.

The three matched evidence providers (`func_15077DBC`, `func_15079790`,
`func_1507B974`) are rechecked independently through `finish`: **3/3 CURRENT (0),
STOP_MATCHED**, with full registered spans, layout, progress and whitespace.
These are evidence rechecks, not new matches or header-dependent source edits.

`CONKER_JOBS=1 ./conker verify-batch func_15077DBC func_15079790 func_1507B974`
reports **BATCH_COMPLETE**, 1,062 tests, six skipped, zero cfe warnings in the
batch log. The 2,072,880-byte US GAME image equals independent ROM extraction,
SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
No pending batch IDs. [Machine-readable evidence](spatial-point-validation.json).

No assembly, compiler flags, tooling, inventory or asset inputs changed.
No permutation was run. This proves GAME and mapped-data integration; no new
asset reconstruction claim is made. Runtime paths are `include/game_path.h`,
`src/game/game_DE5A0.c` and `src/game/game_43D00.c`. The durable ignored ledger
is `build/us/manual-attempts/spatial-point-recovery-20261023/`; discarded
placement trials are in `placed-object-recovery-20261023/`.

## Next five concrete investigations

Priorities combine actual matched ABI discrepancies and measured weights.
These are untried hypotheses, not promised reductions. Declared byte widths
already reflected by constants or masks may still produce neutral results.
The weaker nominal vector/level-header surveys are not promoted as proven ABI
bugs. The stored `func_15149550` return blocker is stale: matched
`func_1513D524` already returns `void *`.

| Priority | Contract | Direct mismatched scored candidates | Weight | Matched evidence |
| ---: | --- | ---: | ---: | --- |
| 1 | `func_15153634` byte arguments | 6 | 8,656 | `game_17CAF0.c` uses `(Config *, u8, u8, s32)`; raw masks at 1515364C/15153650. Five caller sources currently widen both bytes. |
| 2 | `func_15136698` narrow arguments and pointer return | 1 | 12,471 | `effects/blood.c` matched signature; `game_1DC150.c` widens bytes/short, uses a pointer for word argument 5 and declares void return. |
| 3 | `func_1518A3C0` narrow stack arguments | 1 | 1,332 | `game_1B7870.c` matched byte/short contract; `game_E7970.c` widens six tail arguments. The other two callers already agree and are not included as mismatches. |
| 4 | Remaining D_800BE628 render-owner users | 22 | 58,600 | Reuse proven fields; honor recorded bounds regressions and baseline ABI blockers. |
| 5 | D_800B0DF0 level-header roles | 13 | 43,380 | Existing accesses mostly already have correct widths; seek distinct owner/table evidence before another nominal promotion. |
