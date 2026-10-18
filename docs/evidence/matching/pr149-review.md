# PR 149 review corrections

Reviewed base: `6251af62c288950f82f6bbef0b29eb13669de1ee` (`main` when PR 149 was opened).
Original PR commit: `b1f7665b4200ddeee5421abed1694e1c1e49227e`.
The accepted switch verifier, rodata mappings, assembly and shared declarations
are unchanged by this correction.

## Source corrections

| Function | Correction | Authoritative US result | New finish calls |
| --- | --- | --- | --- |
| `func_1509B4A0` | Skip the call with a meaningful early continue when the predicate returns zero; remove the trailing no-op continue | `CURRENT (0)`, layout/progress/whitespace passed | 1 |
| `func_151D8C00` | Restore natural distance comparison; reject dead comma | `CURRENT (25)`, deferred | 1 |
| `func_151AAA4C` | Restore natural multiplication; reject dead comma | `CURRENT (20)`, deferred | 1 |
| `func_1510448C` | Restore natural field load; reject redundant u8 mask | `CURRENT (30)`, deferred | 1 |
| `func_1505A630` | Restore natural u32 conversion; reject redundant u16 narrowing | `CURRENT (135)`, deferred | 1 |
| `func_150D596C` | Revert score-neutral comparison operand swap | `CURRENT (10)`, deferred | 1 |
| `func_150E9E34` | Remove unused external float declaration | `CURRENT (0)`, layout/progress/whitespace passed | 1 |
| `func_15109064` | Remove stray blank line; preserve compound-pointer candidate | `CURRENT (160)`, deferred | 1 retained-form check, 1 main-body comparison |

The two comma variants are historical operand-order hints only. They are not
retained candidates. The rejected mask and narrowing likewise receive no match
credit. Their saved attempts are annotated `invalid` with the review reason.
`func_1505A630`'s literal-versus-symbol alias problem is separate: the rejected
narrowing candidate had two ROM-equal literal words labelled `D_80004000` in the
reference, but the natural form still has other instruction/register differences.
This PR does not change the alias verifier or claim an exact match for it.

## Baseline scores and reproducible context

All measurements use the pinned US IDO compiler/flags and the full registered
reference span. Historical inventory scores are not fresh verification.

`func_1502FD70` has exactly the same function body as main, SHA-256
`44a7da150e8388ce0b5c3a1f2069a4e74f3bafce3facda02ee4805e3ef45bd88`. The complete main source was extracted using
`git show 6251af62:src/game/game_58F80.c`. Only this target's disabled-candidate
wrapper and matching `GLOBAL_ASM` pragma were removed in an ignored snapshot;
all other declarations and source text were preserved. Command:

```sh
./conker probe func_1502FD70 build/us/manual-attempts/pr149-review/func_1502FD70.main.c
# CURRENT (135), frame leaf
```

The supported resume/defer transaction also measured `CURRENT (135)` for the
unchanged body in the PR source context. The full-span residual includes the
missing final registered nop in addition to the existing register differences.
The historical 35 marker is stale; there is no source regression in this PR.

For `func_15109064`, the main function body was extracted from
`git show 6251af62:src/game/game_135D00.c` and temporarily substituted into the
resumed target at its original position in the PR source. Surrounding declarations
and functions were held constant. Commands and results:

```sh
./conker resume func_15109064
# Substitute only the main body into its original target span.
./conker finish func_15109064
# CURRENT (170), CONTINUE_MISMATCH
# Restore the compound-pointer body; its separate finish gives:
./conker finish func_15109064
# CURRENT (160), CONTINUE_MISMATCH
```

The retained-body check was run before the main-body substitution; the saved
retained source was restored byte-for-byte afterward, and `defer` measured it
again. Main-body attempt: `b08eddc2f42244a281af30a4cbf3131a`.
Retained-body attempt: `fd7e46e19bef49a6a18ae68996c29657`.
The compound-pointer form removes the reversed `addu` operands at reference
`+0x14`, reducing 170 to 160. Both forms still move the case-29 store into the
return delay slot and change the case-30 branch target. Historical 130 does not
reproduce with the current authoritative comparison.

Standalone probes scored these bodies 270/260. They are not the authoritative
170/160 results: the mixed object has a 0x74-byte candidate followed immediately
by `func_151090DC`, inside the registered 0x78-byte reference span. `finish` uses
`ShortInteriorExtent` to avoid treating that neighboring instruction as target
code. This preserves the missing-word mismatch; it does not accept a short span.
No scorer or assembly changes were made to obtain these measurements.

## Deferred evidence and searches

Every deferred reason changed by the original PR retains its full inherited main
reason, including earlier rejected hypotheses, ledger paths and the PR 121
[evidence](https://github.com/DevOldSchool/conkers-bfd-decomp/blob/dbedd671496fa3a9ee4191841e9fd3858621b814/docs/evidence/matching/pr121-review.md).
New reasons use separate `seed`, `iterations` and (when recorded) `elapsed_seconds`
fields within the reason text; no inventory schema change is needed.
Updates use supported `resume`/`defer` transactions and fresh measured scores.

Local attempt details remain in `build/us/manual-attempts/deferred-20261018/ledger.md`
and `build/us/manual-attempts/pr149-review/ledger.md`. Those ignored ledgers and
private build logs are not committed. This note preserves the review conclusions
and reproduction context in the repository.

## Final validation

The single final clean batch passed for all 13 accepted PR functions and the
previously affected existing caller:

```sh
./conker verify-batch func_1509B4A0 func_1518BA90 func_15108BC0 func_15108B80 func_15108D24 func_15108AB4 func_1512C068 func_150AFE64 func_15002878 func_150E9E34 func_151604A0 func_150E8930 func_1511473C func_15194DC8
```

Result: `AGENT_ACTION: BATCH_COMPLETE`. Full suite: 2,817 tests OK, 8 skipped
(177.599 seconds test subprocess time; not total workflow time).
Metadata, progress and whitespace gates passed. The 2,072,880-byte integrated
US game image retains SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`;
all mapped rodata payloads match the ROM and alignment bytes remain zero.
There are no pending matches or active nonmatching C candidates. The final
verification record was added after the batch; no source or inventory changed.
