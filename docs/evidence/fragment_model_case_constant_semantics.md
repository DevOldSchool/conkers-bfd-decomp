# Fragment-profile model case constants

Historical checkpoint: the reviewed/named totals below count source-bound
descriptive labels, not confirmed semantic identities or distinct characters.
Gallery labels and source hashes do not establish human confirmation. The
[current confidence review](model_name_confidence_review.md) supersedes the
old reviewed/unknown naming status; source pins and validation history remain
evidence for their stated scope.

Isolated naming proposal based on `6659120ae39493d0d9e81961a05b6ccb791f436a`. The only proposed
C-source change is `src/game/effects/blood.c`: 36 reviewed model labels replace
36 numeric case labels in the existing **disabled** `func_15134070` candidate.
This adds **36 disabled-candidate constants**, zero active case uses, zero
matched-C roles and zero C matches. The 19 existing active model constants in
`src/game/game_16EE20.c` are unchanged and remain a separate count.

## Scope and declaration placement

A single anonymous source-local enum is immediately before the existing role
comment and deferred guard. Its 36 values are unsuffixed decimal integer
constant expressions, each representable as signed `int`. There is no enum-typed
parameter, object, shared header, exported identity or ABI change. Every use is
confined to the disabled candidate. The declaration is outside the guard so
supported function-only extraction, replacement and restore/preserve operations
retain the required declarations without incorporating an enum prefix into the
candidate function artifact.

The guard still says `CURRENT (2310)`, the candidate retains its exact signature,
local variable, byte read at `+0x04`, switch ordering, every return, other literal,
cast and expression, and the same adjacent raw-assembly placeholder. Its inventory
state remains `raw_asm`. Entries 154 (`0x9A`) and 171 (`0xAB`) have no accepted
bank-01 registry identity and remain numeric. No new matching attempt is proposed.

## Exact accepted identities

Identity authority is the accepted 170-record
[model registry](../../config/model-semantic-names.json), SHA-256
`e37a744ea2681f48a8ca175e75682c50d99c018a1d9eb2bacc55951169fa3590`. All 36 exact bank-01, segment-0 records were freshly
decoded from the checksum-validated owned US ROM. Full byte lengths and SHA-1
and SHA-256 pins match the accepted records; the accompanying [public metadata](fragment_model_case_constant_semantics.json)
contains all 36 digest records. No new visual identity review is claimed.

| Entry | Exact registry label | Constant | Unchanged profile return |
| ---: | --- | --- | ---: |
| 0 | Conker | `MODEL_CONKER` | 0 |
| 1 | Conker — variant 1 | `MODEL_CONKER_VARIANT_1` | 0 |
| 2 | Conker — variant 2 | `MODEL_CONKER_VARIANT_2` | 0 |
| 3 | Conker — variant 3 | `MODEL_CONKER_VARIANT_3` | 0 |
| 4 | Conker — variant 4 | `MODEL_CONKER_VARIANT_4` | 0 |
| 16 | Rockman | `MODEL_ROCKMAN` | 13 |
| 17 | Weasel Guard — tall variant | `MODEL_WEASEL_GUARD_TALL_VARIANT` | 1 |
| 20 | Weasel Guard — short shield variant | `MODEL_WEASEL_GUARD_SHORT_SHIELD_VARIANT` | 1 |
| 22 | Uga-Buga — blue headgear | `MODEL_UGA_BUGA_BLUE_HEADGEAR` | 4 |
| 52 | TNT Imp | `MODEL_TNT_IMP` | 11 |
| 56 | Rockman — bow tie | `MODEL_ROCKMAN_BOW_TIE` | 13 |
| 59 | Wise Guy | `MODEL_WISE_GUY` | 1 |
| 71 | Robo-Spider | `MODEL_ROBO_SPIDER` | 10 |
| 88 | SHC Soldier | `MODEL_SHC_SOLDIER` | 3 |
| 90 | Tediz | `MODEL_TEDIZ` | 2 |
| 91 | Rodent | `MODEL_RODENT` | 3 |
| 95 | Tediz — ammunition belt | `MODEL_TEDIZ_AMMUNITION_BELT` | 2 |
| 112 | Gregg the Grim Reaper — scythe | `MODEL_GREGG_THE_GRIM_REAPER_SCYTHE` | 17 |
| 116 | Tediz — variant 1 | `MODEL_TEDIZ_VARIANT_1` | 2 |
| 117 | Tediz — variant 2 | `MODEL_TEDIZ_VARIANT_2` | 2 |
| 122 | Tediz — variant 3 | `MODEL_TEDIZ_VARIANT_3` | 2 |
| 128 | SHC Soldier — variant | `MODEL_SHC_SOLDIER_VARIANT` | 3 |
| 135 | SHC Soldier — decorated uniform | `MODEL_SHC_SOLDIER_DECORATED_UNIFORM` | 14 |
| 136 | Uga-Buga | `MODEL_UGA_BUGA` | 4 |
| 144 | Surf Punk — sunglasses | `MODEL_SURF_PUNK_SUNGLASSES` | 4 |
| 145 | Rockwoman | `MODEL_ROCKWOMAN` | 13 |
| 150 | Conker — black outfit | `MODEL_CONKER_BLACK_OUTFIT` | 7 |
| 152 | Weasel — black helmet and uniform | `MODEL_WEASEL_BLACK_HELMET_AND_UNIFORM` | 12 |
| 156 | Villager — brown hat | `MODEL_VILLAGER_BROWN_HAT` | 5 |
| 157 | Villager — striped bonnet | `MODEL_VILLAGER_STRIPED_BONNET` | 6 |
| 159 | Zombie — dark suit | `MODEL_ZOMBIE_DARK_SUIT` | 9 |
| 160 | Zombie — purple dress | `MODEL_ZOMBIE_PURPLE_DRESS` | 8 |
| 176 | SHC Soldier — decorated uniform variant | `MODEL_SHC_SOLDIER_DECORATED_UNIFORM_VARIANT` | 14 |
| 177 | Tediz — broad-shouldered variant | `MODEL_TEDIZ_BROAD_SHOULDERED_VARIANT` | 15 |
| 178 | Gregg the Grim Reaper — hooded | `MODEL_GREGG_THE_GRIM_REAPER_HOODED` | 17 |
| 180 | Gregg the Grim Reaper — without robe | `MODEL_GREGG_THE_GRIM_REAPER_WITHOUT_ROBE` | 16 |

Costume, descriptive appearance and numbered variant distinctions follow the
accepted labels literally. They do not establish military rank, LOD order,
damage state, transitions, runtime activation, exclusive controllers or native
rendering. These identifiers are descriptive project names, not recovered
original symbols.

As established by [actor effect-selector evidence](actor_effect_selector_semantics.md),
this shared classifier returns one of 20 profile indices or unsupported 99.
Profiles index `D_800A3FD8`, `D_80089A20` and `D_800A3F14`; they are neither bank
nor model IDs. Character model identity does not make this helper character-exclusive.
No return value or profile-domain name is changed.

## Complete source and lifecycle preservation

- Removing exactly the one added enum and reversing exactly the 36 case tokens
  restores the entire original source byte-for-byte
- Isolated patch check/apply/reverse/check returns the exact original source;
  read-only live applicability and whitespace checks pass
- All 21 other deferred guard-through-pragma blocks and all
  25 matched C bodies in this source are byte-identical
- Before/after snapshots preserve 63 active source signatures,
  25 active definition signatures, 47 discovered C definitions including
  deferred bodies, 46 object-declaration results, 88 numeric function symbols and all
  4,082 project signature-index entries. Every discovered body is compared in full
- Current candidate discovery/extraction returns exactly the function body with
  no enum prefix. Replacing with that unchanged extracted artifact is byte-exact.
  Restore/preserve is byte-exact; in-memory activation and focused-source
  reconstruction agree exactly. These API checks compile or promote nothing
- Unmodified `prepare_m2c_context` generates both complete contexts with all
  47 active/deferred bodies retained. The same authorized inverse restores the
  entire before context; no declaration pruning, fallback or tooling change occurs
- All 1,568 tracked files remained byte-identical during preparation. The pinned
  toolchain settings remained unchanged

## ROM and explicit uncached m2c proof

The normalized owned US ROM is 67,108,864 bytes, SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, SHA-256
`32e6a8b970ec12ac5f782344945aa0c98a193832eefb687529d03bab6948714b`. All seven shared registry consumer spans were freshly
checked in full against their accepted hashes. They remain generic infrastructure.

The classifier's complete 252-byte raw-reference and placeholder spans match ROM
at SHA-256 `87c6650f4d53ddcc1a52b24bcf502d38175637e9f42275f90d9046895338e5a6`.
The same-source matched helper `func_151380B4` has a complete 108-byte raw span,
SHA-256 `2ffac69cc60f2d48c033828ede6be5c18d0bfe1cc7df6e09419e1e709601740d`.
Both dispatcher-derived jump tables are independently ROM-checked and supplied
through the unchanged checksum-validating jump-table API:

| Table | Words | SHA-256 |
| --- | ---: | --- |
| `0x800a4350` | 129 | `d321edfcf0ef657c343364be6b03428e24a84df3a377f3acee9bfa8fee19b509` |
| `0x800a4554` | 23 | `5147d2f64bc55d8d1c9690a7373e01ce362d5350f5b0823d7a904542926188c3` |

A strict parser consumes the complete switch body. Its before/after maps for all
256 byte inputs equal direct interpretation of the raw ROM MIPS words and jump
tables, including branch and return delay slots. Both resulting m2c maps agree
with the same exhaustive comparison.

Pinned m2c `09e0e72337804a713e2c3b8d522abe85838470ea` ran four actual processes:
classifier and same-source matched helper, each with the complete before and
after context and explicit `--no-cache`. Every process exited zero with empty
stderr and no `M2C_ERROR`; no context cache artifact was generated. Outputs for
each function are byte-identical across contexts. Classifier output SHA-256 is
`a06d99c5e77217866a8dc1f0362a32445f5c860cbf22994cf3e61f10f03f7a89`; helper output SHA-256 is
`da5cdcaffd9f13e35a0bf42f80ee8f7c3de9098d5adff78417e02e43ba4e7d6f`. Helper call-declaration recovery remains
`void func_15143134(f32 *, f32 *, s32);` in both contexts.

m2c regenerates numeric cases; semantic-name recovery is not claimed. Full-context
parsing accepts these source-local declarations at the stated pin. The current
separate declaration-repair API still rejects an enum prefix with “unresolved
composite declaration in m2c context; refusing partial fields.” Neither that API
nor enum-typed ABI support is extended.

## Frozen source/context hashes

| Artifact | SHA-256 |
| --- | --- |
| before.c | `13f6a0abb0993b88a7f5c24844c060d9be4b2f4a806e65585b6f510acb672bcd` |
| after.c | `24c0540fddfc5245173ef01b0de27bfdb4ac0685df5db21ec1716ab3eb4071ff` |
| source-only.patch | `9a0fe943a59bc0af385d7ace4fbb295da9348dc8f0e6e363f7cf3f65daa0778a` |
| context-before.c | `124ab7ae37274dbf2f393be45954321ca42539231b13277eb68f5eb456fe41b8` |
| context-after.c | `c7f2e23e7074074196b3e2bcb6ddabc76812ed125698b87a20bd3fe06bdc9f98` |

## Acceptance boundary

Source-only preparation ran no build, focused comparator, finish or
queue/progress transaction. Integration separately required binary and layout
equality, independent review, matched-neighbor full-span US `CURRENT (0)`
rechecks, full US ROM equality, aggregate tests and progress/whitespace checks.
Raw `func_15134070` remains excluded and unpromoted.

Public packaging contains evidence prose, metadata and hashes only. It excludes
source files, source patches, ROM/model bytes, raw assembly, generated contexts
and m2c output. The source-only patch is a separate authored proposal artifact.

## Accepted integration

Five matched neighbors across the affected source units retain full-span US
`CURRENT (0)` and reviewed layouts. The clean batch returned `BATCH_COMPLETE`;
full US ROM, integrated game/data/rodata, progress and whitespace checks passed.
All 1,756 tests pass in the host suite (37 environment/tool skips) and the
ROM-enabled pinned suite (one optional validator skip). Independent review
approved all 36 identities, the complete lifecycle/context inverse, all 256
inputs and four fresh explicit uncached m2c runs.

In the integrated blood object, every allocated section and all 321 ELF symbol
records are byte-for-byte unchanged, and no `MODEL_` symbols are emitted. Only
nonallocated `.mdebug` information differs; whole-object byte equality is not
claimed. The raw function, score and generated placeholder remain unchanged.
This accepts 36 constants used only in the disabled candidate, separately from
the 19 active model constants. It adds no active case uses, C roles or matches.
