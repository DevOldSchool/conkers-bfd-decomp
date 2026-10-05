# Compiler-backed m2c context pilot, 2026-10-05

The Conker wrapper discarded all source context when its lightweight flattener
encountered additional includes, macros, or unsupported conditionals. Recovering
that context with the pinned IDO preprocessor improved generated C on a bounded
US sample. The retained changes also honor an explicit local m2c checkout and
record generator/context provenance. No game source, assembly, compiler flags,
shared game headers, progress records, or m2c-fork implementation were changed.

## Retained result

| Generator and experiment | Cases | Scorable before → after | Full-span zeros before → after | Regressions |
| --- | ---: | ---: | ---: | ---: |
| Current fork, restored context | 39 | 14 → 32 | 7 → 13 | 0 |
| Pinned generator, restored context | 39 | 10 → 27 | 6 → 12 | 0 |
| Current fork, grouped inference (rejected) | 24 | 23 → 20 | 14 → 13 | 3 |

The fork gained 18 scorable starters. Of the 14 previously scorable cases, 13
scores were unchanged and `func_1503D45C` improved from 270 to 265. Its generated
`s32 *` advance changed from eight elements to two, preserving the original
eight-byte advance. Six formerly unsupported or compile-failing starters now
have full-span `CURRENT (0)`:

- `func_151749F8`
- `func_15042D78`
- `func_15043A00`
- `func_15042D50`
- `func_800010F8`
- `func_800014A0`

For example, restored context supplies the declaration of `func_15043384`, so
`func_15042D50` no longer emits an unknown return/argument declaration and passes
its pointer argument as `NULL`.

These are generated-starter measurements, not newly accepted game-source
matches. Some sampled functions were already matched. No `finish`, integration,
or `verify-batch` transaction was performed or required for this tooling change.
Seven fork cases remain unscorable; these exclusions are included in the table's
39-case denominator. The selected sample does not estimate a whole-game rate.

## Selection and verification

- Wrapper baseline: Conker commit `490ed96`, before this change.
- Fork: `c24dd86cee4389973dc878eb3f22484dc782a166`.
- Default m2c: pinned `09e0e72337804a713e2c3b8d522abe85838470ea`.
- Compiler: repository-pinned IDO 5.3 image and unchanged US compiler flags.
- Of 744 registered source files, 13 lost context. The pilot selected up to four
  shortest available full-span functions per affected source, at most 1000 bytes;
  39 cases from 11 sources met those bounds and had existing raw extracts.
- The group experiment selected 24 deterministic hash-ordered callers of at most
  256 bytes, with up to three same-source callees of at most 512 bytes. It used
  the fork's existing shared inference passes. Sibling bodies were removed before
  scoring the target. It yielded no numerical score improvements and made
  `func_151AE890`, `func_15146BD8`, and `func_1515D5F8` unsupported. The middle
  function had previously scored zero. No grouped-generation feature is retained.
- Each pair used identical canonical declaration scaffolding and only the target
  function body. The diagnostic harness permits the existing `M2C_FIELD` macro;
  unresolved types and errors are excluded. It does not repair starter bodies.
- All 189 target, sibling, and control assembly spans were independently verified
  against checksum-validated US ROM bytes with `rom_span.raw_span`.
- Scores compare the complete registered function span, including trailing
  instructions, through the repository's `asm_diff_command` and CURRENT parser.
- The final compiler-backed implementation reproduced all 39 experimental fork
  starters exactly. The real `./conker m2c` wrapper was smoke-tested with the local
  fork on `func_15042D50`; its path, commit, Python-source hash, and recovered
  context hash were recorded.
- All 98 existing control cases were regenerated using current source with both
  the pre-change wrapper and retained implementation: all 98 starters were
  byte-identical. Historical source drift was detected before this paired rerun;
  historical scores were not presented as fresh current-source measurements.
- 108 focused tests pass across m2c/context/host selection, call-signature
  recovery, next selection, compiler flags, and repository safety. Shell syntax
  and whitespace checks pass.

## Reproduction and artifacts

Use the normal manual loop with an explicit local fork:

```sh
CONKER_MIPS_TO_C=/absolute/path/to/m2c-conker/m2c.py ./conker next --ready
```

The compiler stays pinned. Without an override, the generator also stays at its
pinned version. Inspect preprocessor output directly with:

```sh
./conker m2c-context --profile us src/game/game_70200.c
```

Ignored evidence is retained under `build/context-pilot/`: manifests, original
and generated C, reference assembly, compiler/diff logs, `results.json`,
`replay/results.json`, `replay/current-controls.json`, `rom-input-proof.json`,
`summary.json`, the baseline wrapper snapshot, and the pilot scripts. These are
local ROM-derived artifacts, not repository source. The scripts record this
workspace's absolute paths and require adapting those paths when replayed
elsewhere. The initial experimental generator script must use the saved
baseline wrapper to reproduce the pre-change side.
