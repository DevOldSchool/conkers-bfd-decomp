# Main transfer candidate (US)

## Scope and result

On 2026-10-18, manual probes improved the preserved `func_8000480C`
candidate in `src/main/init_4470.c` from CURRENT (1354) to CURRENT (854).
An independent `finish` comparison covered the full registered 468-byte span.
This is still a candidate, not an exact match. The C remains under `#if 0`
and the canonical `GLOBAL_ASM` remains active. No shared dependencies, ABI,
assembly, compiler flags or runtime implementation changed.

The raw code copies size into S0 and source into S1 before polling. Introducing
an actual `u32 busSource` local improved allocation relative to modifying the
source parameter. Declaring it after the existing locals also restored the
transfer union anchor at stack offset 0x38; the frame remains 0x40 bytes.
The retained source contains the complete reproducible candidate.

## Manual hypothesis results

| Variant | CURRENT | Frame |
| --- | ---: | ---: |
| Original candidate | 1354 | 0x40 |
| Source local before existing locals | 884 | 0x40 |
| Source local after existing locals (retained) | 854 | 0x40 |
| Size local only | 1702 | 0x48 |
| Source and size locals | 1974 | 0x40 |
| Source local with symbolic segment | 1962 | 0x48 |
| Source local last with symbolic segment | 1982 | 0x48 |
| Size local last | 1722 | 0x48 |
| Both locals last | 1924 | 0x40 |
| Signed, register-qualified, or later-initialized source local (each) | 854 | 0x40 |
| Earlier common count calculation | 1474 | 0x40 |

Twelve manual variants were probed; no permutation search was used. Independent
finish records `9ee696df8fda407183c2e443a3f5962b` and
`171bc8ce0f48468cb7249a588b4c633f` confirmed 884 and 854 respectively.
The latter reports 42 register-only rows, nine operand/constant rows, one
opcode/control-flow row and four missing/extra rows (including one stack row).
The raw source is retained in S1; the candidate uses A3 and saves only S0.
These differences remain unresolved. A low score is not proof of equivalence.

## Other rejected hypotheses

The accompanying transactional deferral notes preserve these results:

| Function | Retained score | New hypotheses and scores |
| --- | ---: | --- |
| `func_80003ACC` | 265 | Signed byte count 265; direct count expression 1280 |
| `func_80003C6C` | 1375 | Endpoint reuse forward 2507, reverse 2707, both 2902 |
| `func_80004074` | 35 | Early return 35; separate free-list cursor 335; combined 335 |
| `func_8000A420` | 230 | Replace rounded local with denominator home 950 |
| `func_8000A750` | 1816 | Remove point-X cache 2032 |

No exact matches or pending matched batch IDs resulted. Candidate preservation
used `defer`; inventory state was not edited by hand. Detailed local probe inputs
and logs remain under `build/us/manual-attempts/main-review-20261018/` and are
not shipped as generated reports.

## Validation scope

The independent focused comparison above verifies the recorded nonzero score.
Progress consistency and whitespace checks passed after candidate preservation.
Before commit, `./conker test --matching` passed 980 tests (six skipped).
A match-only `verify-batch` is not applicable to this deferred-only checkpoint;
no BATCH_COMPLETE or exact-match claim is made.
