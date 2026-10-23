# Narrow-prototype recovery probes, 2026-10-23

Comparison point: `d943e10e`, [spatial-point-final.tsv](spatial-point-final.tsv),
measured deferred sum **2,792,094**. Inventory annotations are not the baseline.
All three bounded probes were rejected and every implementation file restored.
This continuation adds **zero reduction and zero matches**; the PR remains at
**2,532 total reduction and one new match**.

| Probe | Full source cohort | Measured sum before -> trial | Decision |
| --- | ---: | ---: | --- |
| `func_15136698` exact matched prototype | 15 rows, 14 scored | 30,377 -> 30,816 | Reject: caller `func_151AECA0` increases 12,471 -> 12,910 (+439); other scores and the baseline error are unchanged. |
| `func_1518A3C0` exact matched prototype | 18 scored | 27,033 -> 27,033 | Reject: neutral, including the sole width-mismatched caller `func_150BA55C` at 1,332. |
| `func_15153634` matched byte arguments | 13 scored | 29,168 -> 29,168 | Reject: all six directly affected deferred callers remain unchanged. |

[Per-candidate measurements](narrow-prototypes-rejected.tsv) and
[machine-readable validation](narrow-prototypes-validation.json).

## Evidence and limits

- `func_15136698`: matched `effects/blood.c` returns `void *` and uses
  `(f32, f32, u8, u8, s16, s32, void *, u8, u8, u8, s32)`.
  Raw `134070.s` reads bytes at 151366E8 and 151367A8..B0, and the signed
  halfword lifetime at 15136748. The trial shared declaration removed the
  caller's conflicting local signature; its existing vertex address was
  explicitly represented as the canonical integer address word. The caller's
  frame remains 0x160 but its score worsens. `func_1513A594` is the same baseline
  argument-count compiler failure, never counted as zero or improvement.
- `func_1518A3C0`: matched `game_1B7870.c` uses the existing `Vec3f` type and
  `(Vec3f *, Vec3f *, f32, Vec3f *, Vec3f *, f32, f32, u8, s16, u8, s32, u8, s32)`.
  Raw `18A3C0.s` reads lifetime at 1518A440 and bytes at 1518A430/1518A43C.
  Three caller declarations were temporarily replaced with the exact shared
  declaration. The diagnostic used address casts for caller float arrays;
  these are **not an acceptable final header adoption** under the workflow's
  no-header-only-casts rule. Nothing from that diagnostic is retained. Any
  future shared-vector delivery must recover the actual caller vector types.
- `func_15153634`: matched `game_17CAF0.c` uses `(Game153634Config *, u8, u8, s32)`;
  raw `14F640.s` masks the bytes at 1515364C/15153650. Only the two scalar widths
  in five source-local prototypes were probed. This is ABI reconnaissance,
  not a delivered shared declaration. All caller values are already bytes or
  small constants, explaining why no code-generation benefit is established.
  A separate read-only review found the 0x6C layouts have different field names
  and signedness; EC420's matched `func_150BFFE0` uses its private field names,
  and 1EC390 deliberately copies the position through an integer aggregate.
  These are not interchangeable identical-type promotions.

## Restoration and validation scope

A final exact `sweep unchanged` across all eleven trial sources visits 46 rows:
**45 scores totaling 86,578 and one unchanged compiler failure**. Every score
and frame equals the current baseline. Git confirms `include/`, `src/` and
`progress/` are byte-for-byte unchanged from `d943e10e`.

No rejected candidate was activated in canonical source or passed to `finish`.
No assembly, inventory, compiler settings or asset inputs changed. All builds
and sweeps were serial; no permutations. A second worker only inspected code.

No additional clean batch was needed after exact restoration. The retained
implementation is still the one validated by the prior **BATCH_COMPLETE**
(1,062 tests, six skipped). Its 2,072,880-byte GAME binary was compared again
with the independent ROM extraction and is identical, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. This evidence-only continuation
adds no cfe warning or new claim of a passing rejected trial.

The ignored detailed ledger is
`build/us/manual-attempts/narrow-prototypes-20261023/`.

## Next five investigations

Weights measure current candidate exposure, not predicted gains. None justifies
repeating the discarded generic declaration/field substitutions.

| Priority | Lead | Measured exposure | Required new evidence |
| ---: | --- | ---: | --- |
| 1 | Remaining `D_800BE628` render users | 22 scored / 58,600 | Additional matched-backed fields or matrix/viewport roles; exclude recorded bounds/width regressions and ABI-blocked files. |
| 2 | `D_800B0DF0` level header | 13 / 43,380 | Concrete callback/count/dimension/transition role disagreement; existing accesses mostly already have correct widths. |
| 3 | `func_151A8B20` signature | 2 / 5,439 | Matched `void *(void *, s16, s32, u8, s32)` differs from caller return/argument declarations. Existing explicit narrow values may make this neutral. |
| 4 | Actor 0x31C / owner 0x3D4 child contract | `func_150BDB70` / 1,520; broader impact uncounted | Resolve `struct126 *` versus `struct127 *` ownership using matched `func_15127EB8` and raw initialization; do not merge views by offset alone. |
| 5 | Allocator return chain `80003C40` -> `80003C6C` / GAME alias | 42 GAME dependents / 89,251 | Establish the deferred inner allocator's return contract before changing the matched integer-address wrapper; retain argument widths and address-word uses. |

The actor lead names `src/game/game_EB020.c` and `include/types.h` fields
`struct127.unk31C` / `struct108.unk3D4`; matched
`src/game/camera/camera_camera.c:2398` writes the child byte at 0x197.
