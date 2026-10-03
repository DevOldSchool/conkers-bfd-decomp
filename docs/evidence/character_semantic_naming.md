# US character semantic naming

The first naming pilot covers Haybot, bank `01`, decimal entry `75` (`0x4B`),
segment `0`. These are reviewed descriptive names, not recovered original
developer symbols. Model identity is not actor-instance identity or a unique
behavior type. No appearance or runtime-activation claim follows from naming.

## Registry and source identities

[`config/model-semantic-names.json`](../../config/model-semantic-names.json)
records the normalized US ROM SHA-1, model size/SHA-1/SHA-256, eight full
consumer spans and the separately bounded Haybot update branch. The registry's
complete bytes are pinned in `scripts/model_semantic_names.py`; extending it
requires a new reviewed registry and pin. Duplicate identities cannot resolve
to a name. A known key with changed source bytes is rejected, and a different
ROM, profile, bank, entry or segment receives no naming credit.

`model-assets coverage` now reports this one exact model's name as `reviewed`,
with evidence links and the stable key `01:0075:00`. Its independent geometry,
material, scene, visibility and runtime evidence dimensions remain unchanged.
Other models, including other Haybot forms, remain unknown in this pilot.

The existing [Haybot appearance evidence](us_haybot_appearance.md) supplies the
reviewed character identity. The [ROM selector contract](../../config/model-haybot-rom-variants.json)
agrees with the source model and selector branch hashes. This naming audit uses
the owned ROM and repository evidence; it does not require raw captures or
model exports and does not rerun an appearance audit.

## Model-to-consumer chain

1. `func_1503CF20` loads bank `01` and installs model-indexed draw and texture
   tables. `func_1503D774` separately loads bank `11` defaults into
   `D_800D1C90[modelIndex]`.
2. `func_15082A44` reads spawn-record byte `+0x04`, passes that index to
   `func_150839B8` for defaults, then calls `func_150837D4`, which stores it at
   actor byte `+0x04`. This is the generic creation pipeline; the pilot does not
   identify a particular scene's Haybot spawn record or establish its execution.
3. `func_15061B4C` reads actor `+0x04` at `0x15061BD8`. Its branch
   `0x15061FA8..0x1506208C` tests model `75` and derives actor `+0x68` from the
   six-step `+0x69` phase: selectors `15,16,17,17,16,15`.
4. The ordinary texture binder `func_1502F01C` resolves actor `+0x68/+0x69`
   through the 12-byte descriptors in `D_800C5338[modelIndex]` for segments
   `10/11`. The model loader installs the descriptor table. Initial selectors
   come from `func_150839B8`; expressions can change them via `func_1507E5C8`.
5. `func_1502CCFC` selects primary or secondary part tables. Actor part masks
   and rendering gates still determine what is submitted; a name does not
   establish that every source face appears.

See [ROM character defaults](us_rom_character_defaults.md) and
[character draw tables](us_character_draw_tables.md) for the independent
loader, binder and part-selection evidence.

The full `func_15061B4C` is a shared dispatcher, not a Haybot-only function.
The `+0x69` phase interpretation is local to the Haybot branch: the same actor
byte is also a texture selector elsewhere. It is not renamed globally.
The branch's arithmetic does not establish playback timing or an observed
cycle. Constants remain numeric in the unchanged assembly.

## Bounded C naming changes

| Existing symbol or field | Descriptive role or source name | Scope |
| --- | --- | --- |
| `func_150839B8` | `actor_apply_character_defaults` | Comment only; linked symbol retained. Parameters become `actor`, `modelIndex`, `spawnRecord`; locals become `defaults`, `spawnOverride`, `value`. |
| `func_1507E5C8` | `actor_apply_current_expression` | Comment only; linked symbol retained. `actor` and `expressionRecord` describe the proven pointers; the [expression audit](character_expression_semantics.md) resolves the caller override as `morphDurationOverride`. |
| `Game83300Actor.field_4` | `modelIndex` | Same unsigned byte at `+0x04`, matching the existing source-local morph view. |

The defaults function reuses its full-width `value` for the spawn override;
it is not given a misleading model-only lifetime. No padding, type, argument
width, declaration order, expression, store order or function position changes.
The actor view remains source-local rather than introducing a shared ABI.

Macro aliases are deliberately deferred. The repository has an existing
profile-alias pattern and some alias-aware helpers, but other tooling still
locates literal C definition names. Original function IDs, regional symbols,
addresses, `GLOBAL_ASM` paths and source-unit members remain stable.

## Reproduction and acceptance

```sh
python3 -m scripts.model_semantic_names --rom roms/baserom.us.z64
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s tests \
  -p 'test_model_semantic_names.py'

./conker finish func_150839B8
./conker finish func_1507E5C8
./conker finish func_1505DFDC
./conker finish func_1505841C
./conker verify-batch func_150839B8 func_1507E5C8 func_1505DFDC func_1505841C
./conker progress check
git -c core.whitespace=cr-at-eol diff --check
```

The two additional focused checks cover the matched users of the renamed
source-local actor view. The retained deferred `func_1505E650` candidate uses
the same member name but is not promoted or claimed as matched. Acceptance
requires all four full-span US comparisons to remain `CURRENT (0)`, their
reviewed source-unit layouts to remain unchanged, and a clean `BATCH_COMPLETE`
with byte-identical integrated game code and mapped rodata. The work adds no
new matched functions or bytes.

Tests distinguish the numeric identity domains, reject changed model/registry
bytes and consumer spans, and check that naming does not promote extraction,
scene, material, visual-parity or runtime evidence. A ROM-backed test repeats
the independent consumer/model audit when the reviewed US ROM is available.

## Current-main revalidation

The original pilot was developed separately. This continuation starts from
current main and reapplies only its still-supported names; unrelated subsequent
ABI and deferred-candidate fixes are preserved. Old pilot test and coverage
totals are historical results, not validation of this continuation.

The current-main port preserves all four full-span `CURRENT (0)` comparisons
and their source-unit layouts. Its clean batch reached `BATCH_COMPLETE` with
1,712 tests passing (37 skips), byte-identical integrated game code and mapped
rodata, and clean progress/whitespace gates. The unedited baseline separately
verified the complete US ROM and RSP payloads. No new C match is claimed.

The fresh ROM-backed coverage audit contains 1,487 models, 10,394 material runs
and 232,162 source faces. Exactly `01:0075:00` receives the reviewed Haybot name;
1,486 remain unknown. No model-export or runtime-observation manifest was
supplied, and naming grants no credit in those independent dimensions.
