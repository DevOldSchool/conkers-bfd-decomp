# Actor effect-selector naming

These are evidence-backed descriptive roles, not recovered original names.
The two shared selectors read the actor model byte at `+0x04` but return
**different index domains**. Numeric exported symbols and every C literal are
retained. Character identities come from the existing
[reviewed registry](../../config/model-semantic-names.json),
[character expansion](more_character_semantic_registry_expansion.md) and
[actor model-byte contract](character_semantic_naming.md).

## Bounded naming changes

| Existing symbol | Naming-only change |
| --- | --- |
| `func_15141C0C` | Role comment `actor_get_effect_selector_callback_index`; existing `arg0` becomes `actor` |
| `func_15141DA4` | Role comment `actor_request_timed_effect_handler`; existing `arg0/arg1/arg2/temp_v0` become `actorAddress/selectorCallbackIndex/effectHandlerIndex/handlerRecord` |
| `func_15134070` | Role comment `actor_get_fragment_effect_profile_index` before the existing disabled guard; deferred C is unchanged |
| `func_151B01B8` | Local `kind` becomes `effectProfileIndex`; comment distinguishes optional profile-source actor `arg1` from position/transform actor `arg0` |
| `func_15194B1C` | Local `type` becomes `effectProfileIndex`; comment only describes its guarded first call |

The last two functions retain numeric whole-function identities. No inferred
particle purpose is assigned. All argument types, declaration order, casts,
control flow, checks, layouts, struct fields, shared headers, aliases, enums,
source-unit boundaries and function states remain unchanged. `func_151B4CD0`
is outside this patch.

## Evidence and index domains

- `15141C0C` returns `0..11`. At `15141AAC`, its sole static direct caller
  `15141A7C` obtains the value, then indexes the 12 pointers in `D_8008A084`
  at `15141ABC..15141AC4`. Default slot 11 is null. The selected callback's
  separate result indexes 20 eight-byte handler records in `D_8008A0B4`
  at `15141B14..15141B1C`, after rejecting `-1`.
- The complete `15141DA4` body separately bounds callback index `<12` and
  handler index `<20`, including nonnegative checks, the global gate,
  null slots and the existing redundant `-1` test. Only a positive record
  second word leads to `15141E38`. That helper creates or refreshes an
  actor-attached controller; `15149130` initializes its `+0x0E` counter and
  `15149264` decrements it by `D_800BE9E4`. “Timed” means this engine counter;
  no seconds, frame duration or other physical units are established.
- `15134070` returns `0..19` or unsupported `99`. Its profile is shared by
  20 sixteen-byte descriptors at `D_800A3FD8`, 20 selector-array pointers at
  `D_80089A20`, and 20 element counts at `D_800A3F14`. The descriptor and
  fragment selectors resolve through the separate `D_800A3880` lookup to
  bank-09 models. The profile is neither a bank ID nor a model ID. The existing
  [model-constructor evidence](us_model_constructor_tables.md) covers that
  downstream loader contract.
- All ten static direct callers of `15134070` reject `99` before indexed
  profile use. They are `150D5A6C`, `15136C3C`, `1513783C`, `15138BC0`,
  `15138C80`, `151945CC`, `15194B1C`, `151B01B8`, `151B09BC`, `151B4CD0`.
  The direct-edge scan covers the full decoded game code and 34,460
  independently ROM-checked main-reference words. It finds no other direct
  edge and no literal selector address in aligned game data; computed indirect
  calls remain outside this completeness claim.
- In complete matched `151B01B8`, the selected profile only gates descriptor
  byte `+0x0E` and the packet variant. The separate actor inputs are retained.
  In complete matched `15194B1C`, the profile is passed to `15138120` with mode
  zero only when supported; `15136C3C` and `15194AB4` are called afterward
  regardless of that sentinel test. No broader whole-function role is claimed.

## Qualified character consequences

- Conker models 0–4 and 150 select callback slot 0, but profiles 0 and 7
  respectively. Shared callback membership does not imply an identical profile
- Fangy 83 and Red Dinosaur 165 share callback slot 6 with model 54, but
  **both return 99 from the shared profile selector**. Only the two audited
  caller-local overrides in `151B01B8` and `151B09BC` select profile 4 for
  them; those callers also select 4 for an absent profile-source actor
- Tediz 90/95/116/117/122 select profile 2, while Tediz medic 141 is unsupported
  (`99`). This is not an all-Tediz classification
- Gregg 112/178 select profile 17 and Gregg 180 selects 16. Fire Imp 58/61
  use null callback slot 11 and unsupported profile 99

These shared helpers are not character-exclusive controllers. Neither the
roles nor the descriptor variant establish blood color, footsteps, death
purpose, anatomy, scene activation or native visual appearance.

## Byte provenance and preservation proof

The normalized 67,108,864-byte US ROM has SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a` and SHA-256
`32e6a8b970ec12ac5f782344945aa0c98a193832eefb687529d03bab6948714b`.
This preparation independently rechecked 64 complete active-inventory function
spans against ROM bytes and the separate reference instruction stream, plus 13
tables, all 20 fragment arrays and every input in both 256-byte selector maps.
The five directly annotated function spans are:

| Symbol | Complete span, exclusive end | SHA-256 |
| --- | --- | --- |
| `func_15134070` | `0x15134070..0x1513416c` (252 bytes) | `87c6650f4d53ddcc1a52b24bcf502d38175637e9f42275f90d9046895338e5a6` |
| `func_15141C0C` | `0x15141c0c..0x15141cc0` (180 bytes) | `94e412a0d3fc5d286a38dfc6d4cab08ce7bfa4dd0c1a82fa8d912dab0c0c0c8d` |
| `func_15141DA4` | `0x15141da4..0x15141e38` (148 bytes) | `1c3bdd2386e3f79123844688a5a63b02ef766dd60bd06faa03bdd0758527640a` |
| `func_15194B1C` | `0x15194b1c..0x15194b94` (120 bytes) | `967fd90bccec5f4df296d293e57419c446139520bc0956fc05f86a76767b5d89` |
| `func_151B01B8` | `0x151b01b8..0x151b03b8` (512 bytes) | `a90836585e44bade9aa06afdd5023793100ede7f90409175573ca66279c83611` |

Preparation checked these exact token substitutions over whole matched bodies:
`15141C0C arg0→actor` (2 occurrences);
`15141DA4 arg0→actorAddress` (2), `arg1→selectorCallbackIndex` (4),
`arg2→effectHandlerIndex` (6), `temp_v0→handlerRecord` (4);
`151B01B8 kind→effectProfileIndex` (5);
`15194B1C type→effectProfileIndex` (4).
New names have no pre-existing token collision in their function and no
macro definition collision in tracked C/header/include files. Applying the
inverse substitutions in those same complete bodies and deleting only the
five added comments recovers **all four original source files byte-for-byte**.
Number/string token streams, numeric symbol references and every preprocessor
directive are unchanged. All 68 existing deferred-candidate blocks across these
files retain their complete contents, scores, end markers and adjacent pragmas.

The unchanged `15134070` guard-through-pragma slice has SHA-256
`5b8a76923e872626424241087df3f1b5e80a7c16abf1af79a119791795c3ee0d`. Its score remains
`CURRENT (2310)` and state remains `raw_asm`; this is not a new C match.

Exact whole-source SHA-256 pins after the reviewed sentinel-wording clarification:

| Source | Before | After |
| --- | --- | --- |
| `src/game/game_16EE20.c` | `bdcf65326dbd99e7990d47a4589099d27a73950f73f393b61f47195cd62db0dd` | `f77eb80ee051c164f8609366e2a70691c0e22e717bfe218df0da8ac3f3e0d51b` |
| `src/game/effects/blood.c` | `89b01f21097009e567d6de52219e6024f01e69e1d7688c32ba2f732c42012741` | `3376e7743c1aa3f6034fcfbbb7e5d796101076c9e3f0013710a2cd30e479266c` |
| `src/game/game_1DD500.c` | `399bfdb7d035ace51f1d97e6ccb9a0ec216743c4516eee2e9070d7a468729bd4` | `0ac4ebe346ac29a27c9d02d23fb322f531591b73b80a552d4c817ebf3a6403e0` |
| `src/game/game_1C1150.c` | `26ddb3617542746f2d016397d54db68fe14cc7f0f7932be1847abc70119f4c47` | `c6b3fea9b3545e09ed5cc174ee36e4bed868099e09b77867d82198eb0c163e51` |

Source-only patch SHA-256:
`2673070a34b5ebcb8e7bc082968c2f078e3a9c776e549c890a1095efc662b20e`.
Prepared against HEAD `3026ab67182aefe05507d6891605e55d23e6c2e2`.
The independent review added the explicit callback-result `-1` wording to
one comment; this clarification changes no C token or expression.
Patch applicability/whitespace checks passed; an isolated apply and reverse
recovered the original bytes. All 1,557 live tracked files were unchanged
during preparation, including unrelated work and all headers.

## Integration acceptance

No compiler, queue, matching-state, build or progress transaction was run during
isolated preparation. The four prior matched functions still require focused
full-span US rechecks on the applied source:

- `func_15141C0C`
- `func_15141DA4`
- `func_151B01B8`
- `func_15194B1C`

Acceptance requires all four to remain `CURRENT (0)`, unchanged source-unit
layout, the clean `verify-batch` gate, progress and whitespace checks. Do not
promote or run a new match attempt for comment-only raw `func_15134070`.
Source alpha-equivalence and static ROM evidence are not substitutes for those
post-application gates. This patch adds no new matched functions or bytes.

The accepted change passed all four full-span focused comparisons at
`CURRENT (0)`, preserved their reviewed source-unit layouts, and returned
`BATCH_COMPLETE` from the clean four-function batch. Integrated game/data/rodata
checks, the byte-exact full US ROM build, progress and whitespace checks passed.
All 1,729 tests pass in both the host suite (37 environment/tool skips) and the
ROM-enabled pinned-toolchain suite (one optional validator skip). Independent
review verified the exact source inverse, all 68 unchanged deferred blocks,
64 complete supporting spans and both exhaustive 256-model selector maps.
The result adds two descriptive roles on matched functions, one raw-function
role comment and seven clarified local identifiers; no new C match is claimed.
