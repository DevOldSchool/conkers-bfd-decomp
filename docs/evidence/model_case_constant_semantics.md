# Bounded model case constants

Prepared against `f6134c662678e4e0e1b7b1afb9b306b8a0abf79d`.
Only `src/game/game_16EE20.c` changes. The 15 existing input case labels in
matched `func_15141C0C` use one anonymous source-local enum, after the reviewed
source-unit comment and before every use. The role remains the shared
`actor_get_effect_selector_callback_index`; the numeric exported symbol and
its `s32 func_15141C0C(void *actor)` ABI are retained.

## Names and scope

The accepted 91-model `config/model-semantic-names.json` is the identity
source. These are descriptive model-record labels, not recovered original
symbols or character-exclusive controller identities.

| Constant | Bank-01 model entry |
| --- | ---: |
| `MODEL_CONKER` | 0 |
| `MODEL_CONKER_VARIANT_1` | 1 |
| `MODEL_CONKER_VARIANT_2` | 2 |
| `MODEL_CONKER_VARIANT_3` | 3 |
| `MODEL_CONKER_VARIANT_4` | 4 |
| `MODEL_ROCKMAN` | 16 |
| `MODEL_BUGGER_LUGS` | 33 |
| `MODEL_BIG_BIG_GUY` | 43 |
| `MODEL_DINO_BABY` | 54 |
| `MODEL_HAYBOT_HAY_COVERED` | 69 |
| `MODEL_HAYBOT` | 75 |
| `MODEL_FANGY` | 83 |
| `MODEL_COW` | 121 |
| `MODEL_CONKER_BLACK_OUTFIT` | 150 |
| `MODEL_RED_DINOSAUR` | 165 |

Each enumerator has an explicit unsuffixed integer value within signed-int
range. No enum-typed parameter, return, object or shared header is introduced.
Variant numbering distinguishes the four reviewed Conker records; it does not
assert LOD tiers, distances or selection rules. Entry 150 denotes the black
outfit, not a scene-specific role. Hay-covered Haybot 69 remains distinct from
Haybot 75. Supporting identity evidence is in the registry's cited
`additional_character_semantic_registry_expansion.md`,
`more_character_semantic_registry_expansion.md`,
`character_semantic_registry_expansion.md`, `us_haybot_appearance.md`, and
`character_semantic_naming.md`.

Cases `0x7B`, `0x91`, `0x54` and `0x58` remain numeric. Return values, actor
field access, every other literal, masks, fields, globals, declarations and
function signatures are unchanged. This does not name callback/handler indices
or infer effects, scene activation, runtime use, anatomy or appearance.

## Preservation and actual tool support

- Replacing exactly the 15 case identifiers with their original literal
  spellings and removing only the added enum/comment recovers the whole source
  byte-for-byte. An isolated patch apply/reverse also recovers the original
- All 34 deferred guard-through-pragma blocks, including scores and raw
  placeholders, are unchanged. All 1,559 live tracked files remained byte-identical
  during isolated preparation
- Exhaustive evaluation of all 256 model-byte inputs produces identical
  before/after callback-index maps. These also equal the map recovered by
  pinned m2c from independently ROM-checked reference code and jump tables
- Complete declaration/discovery snapshots compare equal: 94 active source
  signatures, 51 active definition signatures, 85 discovered C definitions
  including preserved disabled candidates, 70 object declaration results,
  121 numeric function-symbol identities, and the full 4,082-entry project
  signature index. Function bodies are compared after only the authorized
  case inverse; no selected-line proxy is used
- Current `prepare_m2c_context` generates both complete source contexts,
  including preserved deferred bodies. Removing the added enum and reversing
  the 15 case substitutions makes those complete contexts byte-identical
- Actual pinned m2c `09e0e72337804a713e2c3b8d522abe85838470ea` parses both full
  contexts for the changed classifier and the same-unit `func_15141970` wrapper.
  All four invocations exit 0, have empty stderr, no context fallback and no
  `M2C_ERROR`; each before/after output is byte-identical. No cache or modified
  runtime recipe is used. The wrapper's recovered call declaration also agrees

The 180-byte raw classifier span independently matches the normalized US ROM,
with SHA-256
`94e412a0d3fc5d286a38dfc6d4cab08ce7bfa4dd0c1a82fa8d912dab0c0c0c8d`.
Both raw switch tables are supplied through existing checksum-validated
`prepare_game_jump_tables` support.

The parser regenerates numeric case literals; it does not automatically recover
these semantic names. Existing enum declarations must remain before their uses.
The current declaration-repair API still rejects a supplied enum declaration as
an unresolved composite declaration. This trial does not extend that API or
claim enum-typed ABI support.

## Frozen source pins

| Artifact | SHA-256 |
| --- | --- |
| Before source | `f77eb80ee051c164f8609366e2a70691c0e22e717bfe218df0da8ac3f3e0d51b` |
| After source | `b950cbd2276f847cdf93719a7169091055e5ddbf1e8c8409b7830d53e90d3df0` |
| Source-only patch | `dfe8dec78fcc4ae52dbbf2a8a92b5c28df88d23eaa3302d5057c2e979627c4cc` |
| Classifier m2c output, both contexts | `b96a16690ed739b7d50936cfe46d6a755bf7545e2078bc26a79512ca005e6277` |
| Wrapper m2c output, both contexts | `980f5114e0f9831d155de1036a71ceee6bdf76d1acaaa9642c4aef84bbf04755` |

## Acceptance remains separate

This source-only preparation ran no compiler, focused comparator, source-unit
layout gate, build, matching/queue or inventory transaction, commit or push.
Acceptance still requires independent full-span US `CURRENT (0)` and reviewed
source-unit layout for `func_15141C0C`, a clean batch, full US ROM and mapped
layout verification, progress/whitespace checks and the required complete
suites. This patch adds no C match or matched bytes.

## Accepted integration

The classifier remains full-span US `CURRENT (0)` with its reviewed source-unit
layout preserved. The combined five-function naming batch returned
`BATCH_COMPLETE`; integrated game/data/rodata checks, the byte-exact full US ROM
build, progress and whitespace passed. All 1,737 tests pass in the host suite
(37 environment/tool skips) and ROM-enabled pinned-toolchain suite (one optional
validator skip). Independent review reinterpreted all 256 model inputs from ROM,
recomputed declaration/discovery contexts, and reran all four pinned m2c calls.
This adds exactly 15 source-local case constants, no linked symbol or C match.
