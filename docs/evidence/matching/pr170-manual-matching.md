# Manual matching from PR #170

Base: `fed0a221aa6dba4189e08bd084180ec3ab418f4c` on
`codex/struct-type-recovery`. Work completed on 24 October 2026.

## Accepted functions

All eleven are **matched** with independent full-span US `CURRENT (0)`,
layout, progress, whitespace and clean `BATCH_COMPLETE` acceptance.
Finish counts below exclude exploratory probe variants; independent rechecks
are shown separately.

| Function | Source | Finish calls |
| --- | --- | --- |
| `151D8F30` | `src/game/game_2062D0.c` | 2 |
| `15081E0C` | `src/game/game_AEB40.c` | 1 context recheck |
| `1501A764` | `src/game/game_476D0.c` | 4 |
| `15174FA4` | `src/game/game_1A20A0.c` | 6 worker + 1 independent |
| `151D75C4` | `src/game/game_204660.c` | 3 |
| `151D7264` | `src/game/game_204660.c` | 3 |
| `151D71B0` | `src/game/game_204660.c` | 2 overnight + 1 continuation |
| `1515942C` | `src/game/game_1865D0.c` | 3 |
| `15048664` | `src/done/game/game_75A90.c` | 2 worker + 1 independent |
| `150486B8` | `src/done/game/game_75A90.c` | 2 worker + 1 independent |
| `151B22F4` | `src/game/game_1DF510.c` | 2 worker + 1 independent |

The reviewed `75A90` unit is complete and was relocated with
`./conker progress integrate func_150486B8`; its source mapping and inventories
were updated transactionally. Source-local ABI changes received caller-impact
audits. Existing matches `151D9EB0`, `15059140`, `151D74B0`, `15048360` and
`15048408` were independently rechecked and included in clean batches.

Shared dependency changes: **no**. No shared headers, assembly, compiler flags,
tooling or asset reconstruction changed. The changed code is in the sources
listed above and the preserved-candidate sources below; metadata changes are
limited to `config/game/us.yaml`, `progress/functions.json` and
`progress/source_units.json`.

## Clean batch verification

Each command finished with `AGENT_ACTION: BATCH_COMPLETE`:

```sh
./conker verify-batch func_151D8F30 func_15081E0C func_151D9EB0
./conker verify-batch func_15059140 func_1501A764 func_15174FA4
./conker verify-batch func_151D75C4 func_151D7264
./conker verify-batch func_151D71B0 func_151D74B0
./conker verify-batch func_1515942C func_15048664 func_150486B8 func_151B22F4 func_15048360 func_15048408
```

Builds ran serially with `CONKER_JOBS=1`. Each batch passed the matching test
subset: 1,062 tests, six skipped, across 68 modules. Metadata, progress and
whitespace checks passed; no acceptance IDs remain pending.

The reconstructed US GAME overlay is byte-identical: 2,072,880 bytes,
SHA1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
This validates the GAME overlay, not the full ROM or reconstructed assets.
The source tree was validated before committing; the PR records the resulting
commit. Private build logs and generated progress reports remain untracked.

## Preserved unmatched work

These eleven overnight candidates remain disabled behind canonical `GLOBAL_ASM`;
they receive no match credit. The later short-function continuation added no
new unmatched implementations.

| Function | Source | Last confirmed CURRENT | Remaining mismatch |
| --- | --- | ---: | --- |
| `151D9014` | `src/game/game_2062D0.c` | 380 | registers and scheduling |
| `151A4590` | `src/game/game_1D0840.c` | 459 | registers, operands and stack |
| `1507A2F8` | `src/game/game_A28B0.c` | 425 | frame and registers |
| `151CAD28` | `src/game/effects/effects_sight.c` | 5806 | control/data and stack |
| `1514A594` | `src/game/game_177480.c` | 30 | three commuted float additions |
| `1505D6F0` | `src/game/game_83300.c` | 60 | F0/F2 allocation |
| `150F03F8` | `src/game/game_11D830.c` | 5437 | frame and lifetimes |
| `150CF800` | `src/game/game_FC9E0.c` | 1466 | frame; future rodata review also needed |
| `151C1180` | `src/game/game_1ED0F0.c` | 1627 | query scheduling and tail registers |
| `151D7CD0` | `src/game/game_204660.c` | 1565 | float registers, stack and scheduling |
| `150C1A40` | `src/game/game_EEE70.c` | 340 | F28/F30 allocation and angle scheduling |

Existing stalled candidates were restored after non-improving probes.
`src/game/game_12B050.c` changes only a deferred-score comment; the existing
`15159594` body in `game_1865D0.c` is also unchanged, with its score refreshed
by the supported transaction. Inventory reasons retain exhausted hypotheses.

The earlier `151D7CD0` score-2054 attempt was rejected for an uninitialized
saved-float read. The preserved score-1565 candidate removes that read.
Earlier broad-scope `151C1180` snapshots were also rejected and neighboring
edits restored before the final independent check. Neither rejected variant
is active or preserved as the final candidate.
