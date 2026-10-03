# Remaining four model case constants

Historical checkpoint: the reviewed/named totals below count source-bound
descriptive labels, not confirmed semantic identities or distinct characters.
Gallery labels and source hashes do not establish human confirmation. The
[current confidence review](model_name_confidence_review.md) supersedes the
old reviewed/unknown naming status; source pins and validation history remain
evidence for their stated scope.

Prepared and verified against
`3abf2f67d0f94430a84a551179bcce8d330d62f3`. The source-only proposal changes
only `src/game/game_16EE20.c`. Preparation left tracked files unchanged.

## Exact scope and identity authority

Four unsuffixed decimal enumerators are inserted in numeric order into the
existing anonymous source-local enum, retaining all 15 existing constants:

| Constant | Bank-01 entry | Replaced case | Unchanged return |
| --- | ---: | --- | ---: |
| `MODEL_BUGA_THE_KNUT` | 84 | `0x54` | 5 |
| `MODEL_SHC_SOLDIER` | 88 | `0x58` | 7 |
| `MODEL_THE_EXPERIMENT` | 123 | `0x7B` | 8 |
| `MODEL_ROCKWOMAN` | 145 | `0x91` | 1 |

Exactly these four case uses change in matched `func_15141C0C`. The classifier
retains `s32 func_15141C0C(void *actor)`, its byte read at actor offset 4, every
return, field, other literal and numeric function identity. No enum-typed ABI,
parameter, object, shared header or linked symbol is introduced.

Identity authority is the accepted 145-record `config/model-semantic-names.json`,
SHA-256 `41b043cb6d15e4ae51033f54f91ddcf43f8590742b728cc6bef909e0bec0e416`,
and its `remaining_character_semantic_registry_expansion.md` evidence. Exact
bank-01 indexed entries were freshly decoded from the checksum-validated owned
US ROM. Their full byte lengths and both SHA-1 and SHA-256 match the registry:

| Entry | Bytes | SHA-256 |
| ---: | ---: | --- |
| 84 | 36744 | `c1e861e462c6fe5697b7678d806e1d791f4acfebded5ab7d0c5a3d3a471218fc` |
| 88 | 15672 | `21cb81a9500f255dfa3e2ffb90a870fe6b899e960a0143c756f68ae5124ca2d6` |
| 123 | 50840 | `efe2a55e78ea0f9a625dcff554718dcd5b602cde2fb32fb5371a47fbfb3f446d` |
| 145 | 11816 | `8c6fd008e2058232837a9b5158446d1191fb8f60727c39c818fe02afff7c4836` |

All seven shared consumer spans were freshly checked in full against their
registry SHA-1 pins: `func_1503CF20` (1096 bytes), `func_15082A44` (2152),
`func_150837D4` (280), `func_150839B8` (272), `func_1507E5C8` (240),
`func_1502F01C` (584), and `func_1502CCFC` (2128). These remain generic model
infrastructure. The names make no original-symbol, rank, damage-state, scene,
activation or exclusive-controller claim. No new appearance review is claimed.

## Fresh source and parser preservation proof

- Reversing only the four case substitutions and removing only the four new
  enumerator lines recovers the complete before source byte-for-byte
- An isolated patch apply/check/reverse/check returns the exact original file;
  preparation also passed read-only apply-check against the input source
- All 15 existing enumerators and all 34 deferred guard-through-pragma blocks
  are byte-identical, including disabled bodies, scores and raw placeholders
- Full before/after snapshots preserve 94 active source signatures, 51 active
  definition signatures, 85 discovered C definitions including deferred bodies,
  70 object-declaration results, 121 numeric function-symbol identities, and all
  4,082 project signature-index entries. Entire discovered bodies compare equal
  after only the four authorized case inverses, without a selected-line proxy
- The unchanged `prepare_m2c_context` API generated both complete contexts in
  private fixtures, including every deferred body. Applying the same exact
  four-line/four-use inverse makes the whole generated contexts byte-identical
- Strict whole-switch parsing evaluates all 256 possible input bytes. Both
  source maps and both m2c maps equal direct execution of raw ROM MIPS words,
  including taken/untaken branch delay slots and return delay slots
- All 1,565 live tracked files, including shared helpers, headers and lock files,
  remained byte-identical throughout preparation. Toolchain settings were unchanged.

## Independent ROM and actual pinned m2c

The normalized owned US ROM is 67,108,864 bytes, SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, SHA-256
`32e6a8b970ec12ac5f782344945aa0c98a193832eefb687529d03bab6948714b`.

The entire 180-byte classifier raw-reference span matches ROM at SHA-256
`94e412a0d3fc5d286a38dfc6d4cab08ce7bfa4dd0c1a82fa8d912dab0c0c0c8d`.
The same-unit `func_15141970` wrapper's complete 32-byte raw span matches at
`29cd3f295eff584c7858c32207eee6a699b49db47e39fed487b07da0d1a33980`.
Both switch tables were independently authenticated and then supplied through
the unchanged checksum-validating `prepare_game_jump_tables` API:

| Table | Words | SHA-256 |
| --- | ---: | --- |
| `0x800A5218` | 45 | `86f8fce2e3e2d2274ea6428cbe145990fc2ea9b20cf12c370643b74901d20b4c` |
| `0x800A52CC` | 89 | `08235b758331733ee7a2f57c4be96c13c31c0a87a4ff9b7ee4b5213e8fb400de` |

Pinned m2c `09e0e72337804a713e2c3b8d522abe85838470ea` was authenticated in
the existing isolated runtime. Preparation ran four fresh processes: classifier
and wrapper, each with the complete before and after context. Those calls used
the parser's default context-cache behavior. Independent review repeated all four
with explicit `--no-cache` and fresh copies of the frozen inputs. All eight calls
exited 0 with empty stderr, no `M2C_ERROR` and no context fallback. The uncached
review outputs match preparation exactly, and before/after outputs are
byte-identical for each function. The wrapper's recovered
`void func_1514EDF0(s32, s32);` declaration agrees in both contexts.

The tool regenerates numeric case labels. It does not recover semantic names.
The current declaration-repair API was exercised and still rejects an enum
prefix as an unresolved composite declaration. This proposal extends neither
that API nor enum-typed ABI support. The source-local enum stays before all uses.

## Frozen SHA-256 pins

| Artifact | SHA-256 |
| --- | --- |
| Before source | `b950cbd2276f847cdf93719a7169091055e5ddbf1e8c8409b7830d53e90d3df0` |
| After source | `711f85d574561b0f7fee44fe82514acd9081b7e83613e85c5e9c77b1f6482c43` |
| Source-only patch | `ee4fdcb4981c4d882dbbe6fe4a6a9b1c5e2a4615a4f4fc95ca10aeb59cfa639a` |
| Full before context | `18a82befb425b97927e1dbe977f97228114e79c3e96f8d7dd9e9fa7a81442795` |
| Full after context | `45d9f8c09ca45dbc97090bc08fb982ad05c571043b9a17b0b3ec7799b17cc6b7` |
| Classifier m2c, both contexts | `b96a16690ed739b7d50936cfe46d6a755bf7545e2078bc26a79512ca005e6277` |
| Wrapper m2c, both contexts | `980f5114e0f9831d155de1036a71ceee6bdf76d1acaaa9642c4aef84bbf04755` |

## Acceptance remains separate

Source-only preparation was separate from integrated match acceptance.
It ran no compiler, focused comparator, layout gate, game build or queue/inventory
transaction and changed no toolchain settings. Source-patch whitespace checks passed.

Integration requires independent full-span US `CURRENT (0)`, reviewed
source-unit layout, clean batch, full US ROM/mapped layout verification,
progress/whitespace and required suites. This proposal adds no C match or
matched byte. Public material is limited to authored source changes, this
metadata/evidence summary and hashes. ROMs, raw reference assembly, extracted
model bytes, full generated contexts and decompiler outputs stay private and
ignored.

## Accepted integration

Both the classifier and same-unit wrapper retain independent full-span US
`CURRENT (0)` and reviewed source-unit layout. The clean batch returned
`BATCH_COMPLETE`; full US ROM and integrated game/data/rodata, progress and
whitespace checks passed. All 1,741 tests passed for the source-only batch
(37 host skips, one optional validator skip in the ROM-enabled pinned suite).
The subsequent combined 170-model metadata checkpoint also passes all 1,749
tests in both configurations. Independent review approved the exact source
patch, all 256 inputs, complete contexts and four explicit uncached m2c reruns.
Four additional local constants bring this classifier to 19 named cases, with
no new C matches, bytes, linked names or ABI changes.
