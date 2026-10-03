# Bounded source-local model case constants

Enum spellings retain the exact registry descriptors and the
[record's confidence class](model_name_confidence_review.md); they provide no
additional semantic or qualifier confirmation. Constants distinguish bank-01
model bytes from callback/handler/profile results. Linked symbols and `s32`
interfaces remain unchanged; there is no enum-typed ABI or shared header.

## Active callback-selector cases

`src/game/game_16EE20.c` defines 19 explicitly valued source-local constants
before use by `func_15141C0C`, whose role remains
`actor_get_effect_selector_callback_index`. The initial fifteen are:

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


The remaining four preserve their original results:

| Constant | Bank-01 entry | Replaced case | Unchanged return |
| --- | ---: | --- | ---: |
| `MODEL_BUGA_THE_KNUT` | 84 | `0x54` | 5 |
| `MODEL_SHC_SOLDIER` | 88 | `0x58` | 7 |
| `MODEL_THE_EXPERIMENT` | 123 | `0x7B` | 8 |
| `MODEL_ROCKWOMAN` | 145 | `0x91` | 1 |

Variant numbers distinguish records, not LOD tiers. The black-outfit and
hay-covered descriptors do not establish scenes, transitions or identities beyond
their classified source records. Only case operands change spelling; the actor
byte read, all returns, masks, globals and other literals stay unchanged.

## Disabled fragment-profile cases

`src/game/effects/blood.c` defines 36 constants used only inside the disabled
`func_15134070` candidate. The enum is outside its guard, immediately before the
role comment, so function-only extraction/replacement and restore retain the
required declarations without adding an enum prefix to the candidate artifact.
The raw function retains `CURRENT (2310)`, its exact signature, switch order,
returns and adjacent fallback. Entries 154 and 171 remain numeric cases: later
appearance-only descriptions do not retroactively extend this constant set.

| Entry | Retained descriptor | Constant | Unchanged profile return |
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
retained labels literally. They do not establish military rank, LOD order,
damage state, transitions, runtime activation, exclusive controllers or native
rendering. These identifiers are descriptive project names, not recovered
original symbols.

As established by [actor effect-selector evidence](model_resource_role_names.md),
this shared classifier returns one of 20 profile indices or unsupported 99.
Profiles index `D_800A3FD8`, `D_80089A20` and `D_800A3F14`; they are neither bank
nor model IDs. Character model identity does not make this helper character-exclusive.
No return value or profile-domain name is changed.

## Reproducible source and parser boundary

Exact case-token inverses and removal of the enum declarations reconstruct the
prior whole sources. The disabled guards and other function bodies are preserved.
Exhaustive maps for all 256 input bytes agree between before/after source,
original ROM instruction execution (including delay slots), and recovered m2c
switches. Complete discovery, signature, declaration and project-index snapshots
are unchanged; full contexts retain deferred bodies. Candidate extraction,
replacement, restore/preserve and focused-source reconstruction preserve the
function-only boundary.

Pinned m2c `09e0e72337804a713e2c3b8d522abe85838470ea` parsed complete before/after
contexts for `15141C0C`/`15141970` and `15134070`/`151380B4`; explicit uncached
review runs succeeded with empty stderr, no fallback and byte-identical outputs.
It regenerates numeric cases rather than semantic names. Declaration repair still
rejects an enum prefix as an unresolved composite declaration; successful full
context parsing does not extend declaration repair or enum-typed ABI support.
The wrapper declaration remains `void func_1514EDF0(s32, s32);`; the profile
helper recovers `void func_15143134(f32 *, f32 *, s32);`.

Classifier jump tables are at `800A5218` (45 words, SHA-256
`86f8fce2e3e2d2274ea6428cbe145990fc2ea9b20cf12c370643b74901d20b4c`)
and `800A52CC` (89 words, SHA-256
`08235b758331733ee7a2f57c4be96c13c31c0a87a4ff9b7ee4b5213e8fb400de`).
The 180-byte classifier SHA-256 is
`94e412a0d3fc5d286a38dfc6d4cab08ce7bfa4dd0c1a82fa8d912dab0c0c0c8d`;
the 32-byte wrapper SHA-256 is
`29cd3f295eff584c7858c32207eee6a699b49db47e39fed487b07da0d1a33980`.

The retained [fragment evidence JSON](fragment_model_case_constant_semantics.json)
owns its exact 36-record source pins, jump tables, complete ROM spans, all-input
map digest and uncached parser-output fingerprints. Its historical registry and
acceptance metadata describe that audit, not today's confidence or test totals.
The integrated object comparison found allocated sections and symbols unchanged,
with no emitted `MODEL_` symbols; nonallocated `.mdebug` differed, so whole-object
byte equality was not claimed. There are 19 active case uses and 36 disabled-only
constants, with no C-match or matched-byte credit from naming.
