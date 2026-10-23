# game_16EE20 pointer-table ABI repair (US, 2026-10-23)

The saved `func_15145EA4` candidate now compiles and scores **353**, clearing
one deferred-candidate ABI blocker. The 22 previously scored candidates in
this source remain **42,535 -> 42,535**. This is restored scoring coverage,
with **zero numerical reduction and zero new matches**.

The retained source diff is only the local declaration's first two parameters
(`s32 *` -> `f32 **`) and removal of the two now-unnecessary casts in deferred
caller `func_1514654C`. No matched body or shared header changes. This repair
is retained because the requested lead is the compile blocker; it does not
claim to meet the numerical-improvement gate for a speculative owner adoption.

## Comparison and coverage

Continuation base: `49691194320d62cc41cea43fc472486c2883dadd`.
Current baseline: [render-fields-final.tsv](render-fields-final.tsv), SHA-256
`e3c97458273a74ce509f631235e8444f6bb6d2f2eb5b4d5228b4c4121aae31e7`.
All comparisons use measured `new` values, not saved CURRENT annotations.
In particular, caller `1514654C` remains 2,033, not its stored 1,533.

| Scope | Before -> after | Numerical reduction |
| --- | ---: | ---: |
| Existing 22 scored candidates in game_16EE20.c | 42,535 -> 42,535 | 0 |
| Restored func_15145EA4 | ERR -> 353 | Not comparable |
| Source after restored coverage, 23 scores | 42,888 | 0 |
| Original 1,334 scored deferred rows | 2,791,259 -> 2,791,259 | 0 |
| Expanded final population, 1,335 scores | 2,791,612 | 0 |

The error count changes from 49 to 48; no prior numeric score changes and no
new zero appears. The PR's **3,367-point cumulative reduction and one earlier
match** remain unchanged. The raw score sum grows by 353 because an unscored
row becomes measurable; that is neither a regression nor a reduction.
The [full final sweep](render-abi-16ee20-final.tsv) visits 1,383 candidates
in 452 sources with 1,383 isolated compiles, taking 121.3 scorer seconds
(excluding research, other checks and delivery). The same four pre-existing
zeros remain. [All trial measurements](render-abi-16ee20-trials.tsv).

## ABI evidence

Independent `reference/game/us/asm/141970.s` establishes the exact local
pointer-table contract:

- `15145F04` loads an input pointer from a four-byte table slot; `15145F18`,
  `15145F2C` and `15145F40` read float XYZ at offsets 0/4/8 through it.
- `15145F54` loads the output pointer. Its address and +4/+8 are passed to
  `func_150A7960`; `15145F94` and `15145F9C` advance both tables by four bytes.
- The alternate branch repeats those operations from `15145FB8`, with table
  increments at `15146048`/`15146050`.
- Caller `1514654C` forwards its original input/output table pointers at
  `15146678`/`1514667C`; the matrix address and signed count remain in a2/a3.

The third argument stays an integer address word: `D_800C3E90` selects fixed
matrix conversion versus direct float-matrix use. Input-null/zero-vector
fallback and signed-count handling are unchanged. No value conversion, new
local, control-flow or statement-order change is introduced.

There are no matched callers inside the edited source. Four matched callers
elsewhere (`150FFBDC`, `150FDF38`, `150FE49C`, `15135424`) retain their independent
local declarations and word-encoded pointer arrays. This local fix does not
change those translation units or assert that a shared prototype can be
introduced without recovering each caller's actual pointer types. Two
read-only workers independently reviewed the raw contract and impact.

## Rejected render-owner adoption

After establishing the repair-only comparison point, one bounded trial added
`game_render_view.h`, adopted its existing field0C/field10 and indexed owner
in `func_15144CEC`, and preserved opaque 0x34/0x38 byte reads. It also retained
the separate root load after the arg1[0] store, as required by raw `15144E54`.

The header imports SDK `Gfx`, which conflicts with this source's private
`Gfx` typedef around line 688. All 23 trial candidates fail with that same
redeclaration error, so no numerical gain is claimed. The whole render trial
is restored; no render-header include or field substitution remains.
The trial did not reach a focused match or alter inventory. Resolving the
private display-command type and macro dependency is separate prerequisite
work, not a reason to bypass SDK definitions or add casts to satisfy a header.

## Validation

All **65/65 existing matched functions** in this source pass independent
full-span US `finish`, each with `CURRENT (0)`, `STOP_MATCHED` and layout,
progress and whitespace gates. These are rechecks, not new matches.

The compiler audit is already complete: 24 before/after cases cover canonical
source and all 23 deferred candidates. Before the repair, only 15145EA4 fails;
after it, all 24 compile. Five pre-existing warning-712 emissions are identical
before/after: two in 15141E38, one in 15143134 and two in 15145EA4. The latter
warnings also appear before its baseline redeclaration error. Canonical source
has zero warnings. No new cfe warning is introduced.

`CONKER_JOBS=1 ./conker verify-batch func_15142314` reports
**BATCH_COMPLETE**: 1,062 tests, six skipped, zero cfe warnings in its log.
One nominee covers the sole edited source; all 65 matches were checked
individually beforehand. The 2,072,880-byte US GAME image equals independent
ROM extraction, SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
The source hash remains unchanged through audit, sweep and clean integration.
No pending batch IDs. [Machine-readable validation](render-abi-16ee20-validation.json).

The ignored ledger is `build/us/manual-attempts/render-abi-16ee20-20261023/`.
All edits, compiles, sweeps and finish transactions are serial. No assembly,
compiler flags, tooling, asset inputs or supported inventory state is changed
by hand. No permutations or new asset-reconstruction claim.

## Next five investigations

1. The game_16EE20 SDK/private-Gfx dependency, then a fresh render-owner trial
   against the now-fully-scored source; candidate 15144CEC remains 3,547.
2. D_800B0DF0 level-header roles: 13 candidates / 43,380; seek a concrete role
   disagreement rather than repeating nominal type substitutions.
3. func_151A8B20's matched return/byte/short contract: two candidates / 5,439.
4. Actor 0x31C / owner 0x3D4 child pointer roles: 150BDB70 at 1,520; resolve
   struct126/struct127 ownership using matched camera code and initialization.
5. Allocator return chain 80003C40 -> 80003C6C / GAME alias: 42 dependents /
   89,251; establish the inner return contract before changing the wrapper.
