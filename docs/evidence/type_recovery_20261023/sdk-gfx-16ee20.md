# game_16EE20 SDK graphics dependency (US, 2026-10-23)

Replaced the source-private `Gfx` type and display-command macros with the SDK
`PR/mbi.h` definitions. A source-local `F3DEX_GBI_2` selector preserves the
retail geometry-command encoding. All function bodies remain unchanged.
This resolves the requested SDK/private type conflict; it is a dependency
cleanup with **zero score reduction and zero new matches**.

## Measurement and rejected field adoption

Continuation base: `a7d9af231ad2658b648ea6e2b9faf951b3d45822`.
Comparison baseline: [render-abi-16ee20-final.tsv](render-abi-16ee20-final.tsv),
SHA-256 `b119be7f281ae732127a5915d8a60207def346fb480de91f4833aecfa7ee2c51`.
Comparisons use measured `new` values rather than stored CURRENT annotations.

| Trial | Candidates | Source score sum before -> after | Result |
| --- | ---: | ---: | --- |
| SDK dependency | 23 | 42,888 -> 42,888 | Retained, no regression |
| Indexed GameRenderView owner | 23 | 42,888 -> 43,133 | Rejected, +245 |
| Typed owner retaining byte offset | 23 | 42,888 -> 42,898 | Rejected, +10 |

Both owner trials now compile. Only `func_15144CEC` changes score:
**3,547 -> 3,792** for indexed access, and **3,547 -> 3,557** when preserving
the existing computed byte offset. Both retain its 0x58 frame. They use the
existing float field0C/field10 definitions, leave offsets 0x34/0x38 opaque,
and preserve the separate root reload after the arg1[0] store (raw
`15144E4C`, `15144E54`, `15144E60`). Both are fully reverted. No render-owner
header include or field substitutions remain; two non-improving trials ended
this attempt without body reshaping or permutations.

The [full final sweep](sdk-gfx-16ee20-final.tsv) retains **1,383 rows, 1,335
numeric scores, 48 existing compiler errors and sum 2,791,612**. Every measured
score, frame and error population is unchanged, including the four pre-existing
zeros. The PR remains at **3,367 points reduced and one earlier match**.
The earlier 353-point coverage addition still receives no reduction credit.
[Per-candidate trials](sdk-gfx-16ee20-trials.tsv).

## Evidence for SDK adoption

Independent `reference/game/us/asm/141970.s` shows the clear command's
`D9000000` at `15142BA8`, the set command's `D9FFFFFF` at
`15142BD4`/`15142BD8`, and eight-byte command strides at
`15142BB4`/`15142BEC`. SDK geometry macros require `F3DEX_GBI_2` for that
encoding; the default branch uses B6/B7. `PR/mbi.h` supplies `_SHIFTL` before
including GBI. Other used DP macros preserve command words and single packet
argument evaluation.

Pinned IDO layout probes confirm both private and SDK Gfx occupy eight bytes
with words at offsets 0/4. SDK alignment is eight rather than four. All four
users (`15142B7C`, `15142C10`, `15142CF0`, `15142FBC`) use pointers only; there
are no Gfx objects, arrays or embedded members in this source. The SDK/header
probe also confirms GameRenderView size 0x180 and float fields at 0x0C/0x10.

The final selector follows the initial types/game_functions includes and
precedes `PR/mbi.h`. Those initial headers do not include GBI or depend on the
selector. This order preserves the tooling's initial shared-header discovery
and its 10,276-byte declaration expansion. Two read-only workers reviewed the
SDK equivalence and final prefix. Initial-prefix pilot checks were superseded
by all final-source checks below.

## Validation

All **65 existing matched functions** pass independent full-span US `finish`
with `CURRENT (0)`, `STOP_MATCHED`, layout, progress and whitespace gates.
All **23 saved candidates compile**. A 24-case before/after audit, including
canonical source, retains the same five warning-712 emissions: two in
15141E38, one in 15143134 and two in 15145EA4. Canonical source has none.

`CONKER_JOBS=1 ./conker verify-batch func_15142B7C` reports
**BATCH_COMPLETE**, 1,062 tests with six skipped and zero cfe warnings in the
batch log. The sole touched source has one batch nominee and all 65 matches
were checked individually. The US GAME image is byte-identical to independent
ROM extraction: 2,072,880 bytes, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.

Source hash is stable across final audit, focused checks, sweep and clean
integration. No pending batch IDs. Builds, sweeps and finish transactions were
serial. No assembly, shared header, compiler flags, tooling, asset input or
inventory changes are retained. [Validation record](sdk-gfx-16ee20-validation.json).
Ignored working ledger: `build/us/manual-attempts/sdk-gfx-16ee20-20261023/`.

## Next five investigations

1. `D_800B0DF0` level-header roles: 13 candidates / 43,380 points; seek a field
   role disagreement before retrying correctly sized accesses.
2. `func_151A8B20`: two candidates / 5,439; reconcile matched pointer return,
   signed-short lifetime and unsigned-byte channel contracts.
3. Actor 0x31C / owner 0x3D4 child: `150BDB70` at 1,520; resolve struct126 versus
   struct127 using matched camera byte-0x197 access and owner initialization.
4. Allocator `80003C40 -> 80003C6C` / GAME alias: 42 dependents / 89,251;
   establish the inner return contract before changing the wrapper.
5. `game_18A8F0.c` declaration qualifier blocker: eight scored candidates /
   21,931 plus one ERR. Reconcile 1515E278's `u8 *volatile` parameter with its
   later `u8 *` declaration, then retry 1515D6D0's render adoption (290).
   Any restored score is coverage, not numerical reduction.
