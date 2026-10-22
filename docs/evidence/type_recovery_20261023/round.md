# Shared type recovery round (US, 2026-10-23)

Base: `4a91a197b192e3fe29025447d0fb79a3e375b912` (`origin/main` after
PRs #168 and #169 merged). One worker, one build process at a time, no
permutation or individual function reshaping. The US ROM was copied into a
fresh worktree; submodules, host dependencies, setup and independent reference
preparation completed before measurement.

## Baseline and measurement

`./conker sweep unchanged --output build/us/manual-attempts/struct-type-recovery/baseline.tsv`
scored every preserved deferred candidate in exact isolated mode. The scorer
writes TSV regardless of filename; `baseline.json` in the ignored task ledger
is a lossless JSON conversion. The committed [raw baseline](baseline.tsv) is
unchanged (SHA-256
`13851f6b99a47c8d1b132693fbc4ae4ae44257e42d46d86972349705d24b0678`).

- 1,384 candidates in 452 sources; 1,335 successfully scored.
- Score sum: **2,794,626**; **784** candidates above 1,000.
- **49** pre-existing compilation errors remain unscored. Their stored scores
  are never substituted for missing measured scores.
- **Four** baseline zeros already existed; they are not improvements or new
  matches from this round.
- Baseline scorer elapsed time: **258.5 seconds**, excluding worktree/setup
  and validation. This is subprocess time, not end-to-end task time.

`struct-layouts` found 87 clusters with at least three copies;
`declaration-conflicts` found 629 conflicting symbols. `blockers` had no saved
outcomes in the fresh worktree and therefore supplied no ranking evidence.
Rankings join layout/symbol mentions in deferred bodies with the freshly
measured scores, excluding matched functions and counting each dependent once.
Scores describe the whole dependent function, not the impact of that symbol.

## Kept lead: rectangle spawn helper `func_1515548C`

The matched US definition in `src/game/game_182140.c` establishes:

```c
void *func_1515548C(void *, u8, s32, s32, s32, u8, s32);
```

The helper copies the 0x58-byte descriptor, stores the second argument in a
byte at returned-object offset 0x68, forwards the sixth argument as a byte
allocation selector, and returns the allocated object or null. The third
argument is treated as an address word passed to `func_151555AC`; it remains
`s32`, matching the accepted definition. Every recorded direct call passes
zero or an existing integer word in that slot. Argument count and return uses
were audited across all callers; no arguments, casts or body statements were
added, removed or reshaped to satisfy the declaration.

Local declarations instead returned `void` or `u8 *`, accepted unrelated
pointer types for the descriptor/address word, or widened both byte slots to
`s32`. The shared declaration now lives in `include/game_functions.h`; all
eight local copies in seven caller files were removed. `game_FC9E0.c` gains
the direct overlay include. The owning definition already included it and
requires no source edit. No new struct layout is claimed for the private
0x58-byte descriptor views.

Touched files: `include/game_functions.h`,
`src/game/effects/effects_sfx_w1_bee_cavern.c`,
`src/game/effects/effects_sight.c`, `src/game/game_114740.c`,
`src/game/game_114B80.c`, `src/game/game_127060.c`,
`src/game/game_188440.c`, and `src/game/game_FC9E0.c`.

| Scope | Candidates | Score sum before | Score sum after | Reduction | New matches |
| --- | ---: | ---: | ---: | ---: | ---: |
| Direct deferred callers | 11 | 32,570 | 31,940 | 630 | 0 |
| Every candidate in touched caller files | 33 | 95,346 | 94,716 | 630 | 0 |

Only four scores change in the [complete rescore](rectangle-spawn.tsv):

| Candidate | Before | After | Reduction |
| --- | ---: | ---: | ---: |
| `func_151CCF08` | 3,493 | 2,758 | 735 |
| `func_151CB5FC` | 6,057 | 5,585 | 472 |
| `func_150FAE18` | 2,229 | 2,181 | 48 |
| `func_151CAB78` | 1,557 | 2,182 | -625 |

The regression is retained deliberately to use the matched helper's proven
byte contract consistently. Paired complete-source `probe` variants reproduce
1,557 and 2,182 with the same 0xE8 frame. At the second argument's `mode &
0xFF`, IDO changes one `andi a1,v0,0xFF` into `move a1,v0; andi t3,a1,0xFF;
move a1,t3`, shifting subsequent temporary registers and instruction offsets.
The function body is identical. No speculative source rewrite hides the
625-point regression. Gross reductions of 1,255 exceed it by 630.

Validation: all **52** matched functions in edited sources plus the helper
owner passed independent full-span US `finish` with `CURRENT (0)`, layout,
progress and whitespace gates. A separate compiler audit built **43 pairs**
of historical/current canonical and individually activated deferred units:
no errors or canonical `cfe` warnings, and the same two pre-existing deferred
warning-712 sites before and after (`func_150E81A8`, `func_151C9ED4`). This
covers every `#if 0` candidate in the edited files and the helper's source.
The `game_114740.c` unit has no matched function: both deferred candidates
were compiled individually; clean integration covers its retained assembly.

Clean `CONKER_JOBS=1 ./conker verify-batch func_150BDE90 func_151C8674
func_150E8824 func_150FA468 func_1515B5F4 func_150CF530 func_1515548C`
reported **BATCH_COMPLETE**. The 2,072,880-byte US GAME image equals the
independently extracted reference byte for byte (SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`). The matching subset passed:
1,062 tests, six skipped. The clean build log has no `cfe: Warning` lines.
Existing SDK `cc` option warnings are separate. No asset reconstruction inputs
changed; this validates the GAME image and mapped data, not reconstructed assets.
Whitespace checks passed.
