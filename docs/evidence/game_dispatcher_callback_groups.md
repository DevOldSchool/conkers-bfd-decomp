# US dispatch tables, command handlers and descriptor callbacks

Evidence type: `structural_analysis`

Four additional working boundaries contain 662 recovered function entries and
90,672 code bytes. Their offset-derived filenames come from the independently
recorded C groups in the pinned upstream US map. They remain structural
hypotheses about source grouping, not recovered historical filenames or matched
C implementations. All members stay raw ASM.

## Inputs and ranges

The upstream input is `mkst/conker` revision
`3adf229175c037c771f251f169f9dd80ca306924`, inspected locally in its
[US map](https://github.com/mkst/conker/blob/3adf229175c037c771f251f169f9dd80ca306924/conker/conker.us.yaml).
The combined-to-game offset adjustment is `-0x2D4B0`.
Owned retail game code SHA-1:
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
Retail initialized game data SHA-1:
`42bbe7f02702ca7af5da499fb5cf2f34b7d3d23b` (base `80082B20`).

| Working source | Combined range | Game range | Recovered entries | Bytes | Debug correlations (strong) | ECTS correlations (strong) |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| `game_6D800.c` | `0x6D800:0x6E240` | `0x40350:0x40D90` | 64 | 2,624 | 55 (5) | 53 (4) |
| `game_981E0.c` | `0x981E0:0xA28B0` | `0x6AD30:0x75400` | 329 | 42,704 | 278 (133) | 237 (102) |
| `game_A28B0.c` | `0xA28B0:0xA9260` | `0x75400:0x7BDB0` | 211 | 27,056 | 180 (110) | 168 (103) |
| `game_169510.c` | `0x169510:0x16DC80` | `0x13C060:0x1407D0` | 58 | 18,288 | 47 (36) | 33 (25) |

Correlation counts retain the cached beta discovery index, which also proposes
unreferenced eight-byte stubs. Strong matches corroborate related instruction
sequences and order across versions; they are not US C match evidence. The
registration membership below instead follows the regenerated raw reference.

## Runtime relationships and grouping evidence

### `game_6D800.c`

The range combines compact handlers with the dispatcher that uses them.
At `0x40B04:0x40B1C`, an input byte is scaled by four to select a function
from `800844B0`, followed by `jalr`. The later path beginning at `0x40CF4`
also materializes the same table. Retail data contains 255 aligned pointers
to the initially labeled members; `800844B4` additionally selects the
previously unlabeled return-only callback `150407A0`.
The complete group also has eleven direct internal call sites.
Most beta correlations are weak because many short handlers are identical;
the table consumer and stored entry addresses are the stronger evidence.

### `game_981E0.c`

This large handler family consistently operates on the current object pointer
at `800D154C` and the argument/state word at `800D1580`. Its members also
share `800CC2D0` and `800C3E78`. The nontrivial helper `1506E46C` has
seventeen direct intra-range callers; `1506BA4C`, `1506B100`, `1506BAD8`,
`1506C460` and `15073118` are other reused internal helpers.

The original raw labels have 306 retail data references across
`80086150:8008670C`. These tables include the ordered compact member families
and later callback entries `15074E80`, `15074EE8`, `15074F30`, `15074F48`,
`15074FD4`, `15075050`, `150750A4` and `150750C4`.
The earlier state group at `0x5E39C:0x5E3B4` indexes the callback table at
`8008630C` with a halfword, installing the selected entry into a descriptor.
That table supplies independent entry evidence for twelve additional
return-only handlers, described in `game_return_callback_symbols.md`.
Other table references are consumed at `0x71D48:0x71D54` and by the
already reviewed state routines dispatching through `80086694` at
`0x5BD94` and `0x5C6F4`.

The current 329 recovered entries span complete connected handler families.
They are not assumed to share one historical file merely because of their
size or adjacency: the prior C split, common state, callback tables and long
cross-build correlations are the combined basis for this working grouping.
Finer original subdivisions remain possible.

### `game_A28B0.c`

The closing `func_1507BC14` is a bytecode interpreter. It reads a stream
pointer at current-object `+0x218`, loads a byte opcode, and for opcodes
below `0xF7` copies four operand bytes into `800D1890:800D1893`. It then
selects a handler from `80086730`, executes `jalr` at `0x7BD60`, and advances
the stream by five bytes. Other opcode values advance by one byte. Its loop
also respects the halfword state at object `+0x21C`.

The opening `15075400` implements related stream stepping/search logic with
the same threshold and five-byte stride; it has 32 direct callers in the
range. The operand conversion helper `1507A3E8` combines the four global
bytes into one big-endian word and has fifteen internal callers. `15075548`
and `1507BB28` are other reused handlers/helpers. The family therefore
connects its opening helpers, central handlers and closing interpreter.
There are 203 pointers to the initially labeled members in
`80086734:80086A84`; the three additional return-only handlers are explicit
entries in the same interpreter table. All 211 entries now have separate
raw labels. The current-object pointer and operand-byte globals recur
throughout the group.

### `game_169510.c`

This descriptor/callback group begins with `1513C060`, which tests object
flags, updates a halfword lifetime, and dispatches through `80089C70`.
The constructor `1513C350` has five callers within the range, including
`1513C5B0`; other repeated internal helpers include `1513D2F0`, `1513E2AC`,
`1513FFF4`, `151400D0`, `1513E13C`, `1513C92C` and `1513CA48`.
Fifty-four retail function-table references select members throughout the
range, including paired wrappers at `8008C620/8008C628` and late helpers at
`8008C634`, `8008C63C`, `8008C648` and `8008C64C`.
The closing `151406AC` uses the shared list storage at `800DCE50`, also
used by the separately reviewed allocation/lifecycle group `game_1944C0.c`.
The adjacent callback group `game_16DC80.c` calls into these routines.

## Resolving the function-index disagreements

The checked-in game symbol list records sixteen eight-byte callback entries
whose bodies previously lacked top-level labels. Their table evidence and
exact instruction bytes are documented in
[the callback-symbol note](game_return_callback_symbols.md). Regenerating
through `./conker game-asm --profile us` adds exactly those sixteen names and
removes no existing function symbol. All affected instruction words remain
identical. The regeneration also normalizes previously stale reference file
names and raw slice boundaries to the current canonical map; those generated
files are not edited or checked in.

Three further index proposals inside these four ranges have no independently
established entry reference: `15040A4C`, `15073070`, and `1513E134`.
Their return/nop words remain intact in the preceding raw span and receive no
separate work item. The membership table gives each recovered raw span,
including such retained instructions and final padding. It does not silently
claim those bytes are implemented C or identify an original function name.

## Complete bounds review and validation

All words in the complete ranges have been compared against the owned retail
image with contiguous offsets and exact runtime addresses. No conditional
branch enters or leaves any proposed range. The preceding and closing routines
return before each boundary's padding. The registered raw spans cover every
byte in each range, including unlabeled return sequences, without overlapping.
No data/BSS allocation is assigned to the source groups. A successful full
build validates byte preservation, not the historical source hypotheses.

Use `./conker register-source-unit --overlay game --register-members` with
this note as evidence, followed by the full `./conker progress integrate
--profile us --all-reviewed` gate. All members remain raw assembly.

The first integration attempt passes for all four units, including the new
callback-symbol metadata. The complete 2,072,880-byte overlay retains SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All 170 Python tests, generated
progress checks and whitespace checks pass. There are now 1,650 registered
functions and 154 source units, including 152 reviewed boundaries.

## Raw hashes and recovered membership

### `game_6D800.c`

Range SHA-1: `473f38ada2b9ec2e4443e2dd9a8cdcbca9e5d3c8`.

| US member | Recovered raw span |
| --- | ---: |
| `func_15040350` | `0x78` |
| `func_150403C8` | `0x364` |
| `func_1504072C` | `0x1c` |
| `func_15040748` | `0xc` |
| `func_15040754` | `0x4c` |
| `func_150407A0` | `0x8` |
| `func_150407A8` | `0xc` |
| `func_150407B4` | `0xc` |
| `func_150407C0` | `0xc` |
| `func_150407CC` | `0xc` |
| `func_150407D8` | `0xc` |
| `func_150407E4` | `0xc` |
| `func_150407F0` | `0xc` |
| `func_150407FC` | `0xc` |
| `func_15040808` | `0xc` |
| `func_15040814` | `0xc` |
| `func_15040820` | `0xc` |
| `func_1504082C` | `0x40` |
| `func_1504086C` | `0xc` |
| `func_15040878` | `0xc` |
| `func_15040884` | `0xc` |
| `func_15040890` | `0xc` |
| `func_1504089C` | `0xc` |
| `func_150408A8` | `0xc` |
| `func_150408B4` | `0xc` |
| `func_150408C0` | `0xc` |
| `func_150408CC` | `0x24` |
| `func_150408F0` | `0xc` |
| `func_150408FC` | `0xc` |
| `func_15040908` | `0xc` |
| `func_15040914` | `0xc` |
| `func_15040920` | `0xc` |
| `func_1504092C` | `0xc` |
| `func_15040938` | `0xc` |
| `func_15040944` | `0xc` |
| `func_15040950` | `0xc` |
| `func_1504095C` | `0xc` |
| `func_15040968` | `0xc` |
| `func_15040974` | `0xc` |
| `func_15040980` | `0xc` |
| `func_1504098C` | `0xc` |
| `func_15040998` | `0xc` |
| `func_150409A4` | `0xc` |
| `func_150409B0` | `0xc` |
| `func_150409BC` | `0xc` |
| `func_150409C8` | `0xc` |
| `func_150409D4` | `0xc` |
| `func_150409E0` | `0xc` |
| `func_150409EC` | `0xc` |
| `func_150409F8` | `0xc` |
| `func_15040A04` | `0xc` |
| `func_15040A10` | `0xc` |
| `func_15040A1C` | `0xc` |
| `func_15040A28` | `0xc` |
| `func_15040A34` | `0xc` |
| `func_15040A40` | `0x14` |
| `func_15040A54` | `0xc` |
| `func_15040A60` | `0xc` |
| `func_15040A6C` | `0xc` |
| `func_15040A78` | `0x250` |
| `func_15040CC8` | `0x98` |
| `func_15040D60` | `0xc` |
| `func_15040D6C` | `0xc` |
| `func_15040D78` | `0x18` |

### `game_981E0.c`

Range SHA-1: `2b1ae34c7f7ad79a75155abbb40f4d964a236298`.

| US member | Recovered raw span |
| --- | ---: |
| `func_1506AD30` | `0x244` |
| `func_1506AF74` | `0x6c` |
| `func_1506AFE0` | `0x40` |
| `func_1506B020` | `0x50` |
| `func_1506B070` | `0x8` |
| `func_1506B078` | `0x88` |
| `func_1506B100` | `0x4c` |
| `func_1506B14C` | `0x4c` |
| `func_1506B198` | `0x50` |
| `func_1506B1E8` | `0x40` |
| `func_1506B228` | `0x40` |
| `func_1506B268` | `0x54` |
| `func_1506B2BC` | `0x6c` |
| `func_1506B328` | `0x40` |
| `func_1506B368` | `0x8` |
| `func_1506B370` | `0x40` |
| `func_1506B3B0` | `0x8` |
| `func_1506B3B8` | `0x134` |
| `func_1506B4EC` | `0x20` |
| `func_1506B50C` | `0x14` |
| `func_1506B520` | `0x84` |
| `func_1506B5A4` | `0x8` |
| `func_1506B5AC` | `0x8` |
| `func_1506B5B4` | `0x18` |
| `func_1506B5CC` | `0x18` |
| `func_1506B5E4` | `0x50` |
| `func_1506B634` | `0x10c` |
| `func_1506B740` | `0xb4` |
| `func_1506B7F4` | `0x38` |
| `func_1506B82C` | `0x34` |
| `func_1506B860` | `0x2c` |
| `func_1506B88C` | `0x28` |
| `func_1506B8B4` | `0x40` |
| `func_1506B8F4` | `0x28` |
| `func_1506B91C` | `0x28` |
| `func_1506B944` | `0x40` |
| `func_1506B984` | `0x28` |
| `func_1506B9AC` | `0x14` |
| `func_1506B9C0` | `0x8c` |
| `func_1506BA4C` | `0x8c` |
| `func_1506BAD8` | `0x8c` |
| `func_1506BB64` | `0x44` |
| `func_1506BBA8` | `0x7c` |
| `func_1506BC24` | `0x7c` |
| `func_1506BCA0` | `0x28` |
| `func_1506BCC8` | `0x120` |
| `func_1506BDE8` | `0x44` |
| `func_1506BE2C` | `0x28` |
| `func_1506BE54` | `0x30` |
| `func_1506BE84` | `0x14` |
| `func_1506BE98` | `0x28` |
| `func_1506BEC0` | `0x1c` |
| `func_1506BEDC` | `0x40` |
| `func_1506BF1C` | `0x40` |
| `func_1506BF5C` | `0x3d0` |
| `func_1506C32C` | `0xec` |
| `func_1506C418` | `0x24` |
| `func_1506C43C` | `0x24` |
| `func_1506C460` | `0xa0c` |
| `func_1506CE6C` | `0x47c` |
| `func_1506D2E8` | `0x204` |
| `func_1506D4EC` | `0x8` |
| `func_1506D4F4` | `0x44` |
| `func_1506D538` | `0x38` |
| `func_1506D570` | `0x14` |
| `func_1506D584` | `0x130` |
| `func_1506D6B4` | `0x98` |
| `func_1506D74C` | `0x14c` |
| `func_1506D898` | `0x9c` |
| `func_1506D934` | `0x1c` |
| `func_1506D950` | `0x8` |
| `func_1506D958` | `0x120` |
| `func_1506DA78` | `0x1c` |
| `func_1506DA94` | `0x9c` |
| `func_1506DB30` | `0x2c` |
| `func_1506DB5C` | `0x28` |
| `func_1506DB84` | `0x1c` |
| `func_1506DBA0` | `0x34` |
| `func_1506DBD4` | `0x3c` |
| `func_1506DC10` | `0x94` |
| `func_1506DCA4` | `0x1c` |
| `func_1506DCC0` | `0x1c` |
| `func_1506DCDC` | `0x1c` |
| `func_1506DCF8` | `0x8` |
| `func_1506DD00` | `0x44` |
| `func_1506DD44` | `0x28` |
| `func_1506DD6C` | `0x4c` |
| `func_1506DDB8` | `0x8` |
| `func_1506DDC0` | `0x44` |
| `func_1506DE04` | `0x80` |
| `func_1506DE84` | `0x268` |
| `func_1506E0EC` | `0x1e0` |
| `func_1506E2CC` | `0x1a0` |
| `func_1506E46C` | `0x190` |
| `func_1506E5FC` | `0x40` |
| `func_1506E63C` | `0x40` |
| `func_1506E67C` | `0x40` |
| `func_1506E6BC` | `0x40` |
| `func_1506E6FC` | `0x40` |
| `func_1506E73C` | `0x40` |
| `func_1506E77C` | `0x40` |
| `func_1506E7BC` | `0x40` |
| `func_1506E7FC` | `0x4c` |
| `func_1506E848` | `0x50` |
| `func_1506E898` | `0x40` |
| `func_1506E8D8` | `0x40` |
| `func_1506E918` | `0x40` |
| `func_1506E958` | `0x40` |
| `func_1506E998` | `0x40` |
| `func_1506E9D8` | `0x40` |
| `func_1506EA18` | `0x40` |
| `func_1506EA58` | `0x40` |
| `func_1506EA98` | `0x128` |
| `func_1506EBC0` | `0x90` |
| `func_1506EC50` | `0x80` |
| `func_1506ECD0` | `0x20` |
| `func_1506ECF0` | `0x1c` |
| `func_1506ED0C` | `0x40` |
| `func_1506ED4C` | `0x1c` |
| `func_1506ED68` | `0x28` |
| `func_1506ED90` | `0x1c` |
| `func_1506EDAC` | `0x1c` |
| `func_1506EDC8` | `0x28` |
| `func_1506EDF0` | `0x24` |
| `func_1506EE14` | `0x24` |
| `func_1506EE38` | `0x28` |
| `func_1506EE60` | `0x4c` |
| `func_1506EEAC` | `0x2c` |
| `func_1506EED8` | `0x1c` |
| `func_1506EEF4` | `0x68` |
| `func_1506EF5C` | `0x58` |
| `func_1506EFB4` | `0x14` |
| `func_1506EFC8` | `0x3c` |
| `func_1506F004` | `0x28` |
| `func_1506F02C` | `0x30` |
| `func_1506F05C` | `0x34` |
| `func_1506F090` | `0x34` |
| `func_1506F0C4` | `0x2c` |
| `func_1506F0F0` | `0x2c` |
| `func_1506F11C` | `0x30` |
| `func_1506F14C` | `0x30` |
| `func_1506F17C` | `0x2c` |
| `func_1506F1A8` | `0x37c` |
| `func_1506F524` | `0x28` |
| `func_1506F54C` | `0x374` |
| `func_1506F8C0` | `0x30` |
| `func_1506F8F0` | `0xd0` |
| `func_1506F9C0` | `0xd0` |
| `func_1506FA90` | `0xd0` |
| `func_1506FB60` | `0x88` |
| `func_1506FBE8` | `0x34` |
| `func_1506FC1C` | `0x34` |
| `func_1506FC50` | `0x24` |
| `func_1506FC74` | `0x28` |
| `func_1506FC9C` | `0x2c` |
| `func_1506FCC8` | `0x34` |
| `func_1506FCFC` | `0x34` |
| `func_1506FD30` | `0xc0` |
| `func_1506FDF0` | `0x2c` |
| `func_1506FE1C` | `0x2c` |
| `func_1506FE48` | `0x2c` |
| `func_1506FE74` | `0x2c` |
| `func_1506FEA0` | `0x2c` |
| `func_1506FECC` | `0x2c` |
| `func_1506FEF8` | `0x2c` |
| `func_1506FF24` | `0x2c` |
| `func_1506FF50` | `0x28` |
| `func_1506FF78` | `0x34` |
| `func_1506FFAC` | `0x34` |
| `func_1506FFE0` | `0x34` |
| `func_15070014` | `0x28` |
| `func_1507003C` | `0x48` |
| `func_15070084` | `0x30` |
| `func_150700B4` | `0x30` |
| `func_150700E4` | `0x30` |
| `func_15070114` | `0x30` |
| `func_15070144` | `0x80` |
| `func_150701C4` | `0x30` |
| `func_150701F4` | `0x30` |
| `func_15070224` | `0xdc` |
| `func_15070300` | `0x390` |
| `func_15070690` | `0x34` |
| `func_150706C4` | `0x34` |
| `func_150706F8` | `0x68` |
| `func_15070760` | `0x34` |
| `func_15070794` | `0x34` |
| `func_150707C8` | `0x30` |
| `func_150707F8` | `0x38` |
| `func_15070830` | `0x30` |
| `func_15070860` | `0x38` |
| `func_15070898` | `0x380` |
| `func_15070C18` | `0x28` |
| `func_15070C40` | `0x9c` |
| `func_15070CDC` | `0x24` |
| `func_15070D00` | `0x24` |
| `func_15070D24` | `0x23c` |
| `func_15070F60` | `0x2d0` |
| `func_15071230` | `0x24` |
| `func_15071254` | `0x24` |
| `func_15071278` | `0x34` |
| `func_150712AC` | `0xb4` |
| `func_15071360` | `0xd4` |
| `func_15071434` | `0x3c` |
| `func_15071470` | `0x3c` |
| `func_150714AC` | `0x3c` |
| `func_150714E8` | `0x5c` |
| `func_15071544` | `0x48` |
| `func_1507158C` | `0x48` |
| `func_150715D4` | `0x48` |
| `func_1507161C` | `0xc` |
| `func_15071628` | `0x40` |
| `func_15071668` | `0x28` |
| `func_15071690` | `0x5c` |
| `func_150716EC` | `0x78` |
| `func_15071764` | `0x7c` |
| `func_150717E0` | `0x50` |
| `func_15071830` | `0x30` |
| `func_15071860` | `0x28` |
| `func_15071888` | `0x5c` |
| `func_150718E4` | `0xb4` |
| `func_15071998` | `0x34` |
| `func_150719CC` | `0x34` |
| `func_15071A00` | `0x34` |
| `func_15071A34` | `0x30` |
| `func_15071A64` | `0xb4` |
| `func_15071B18` | `0x1f0` |
| `func_15071D08` | `0x30` |
| `func_15071D38` | `0x40` |
| `func_15071D78` | `0x50` |
| `func_15071DC8` | `0x2c` |
| `func_15071DF4` | `0x2c` |
| `func_15071E20` | `0x1c` |
| `func_15071E3C` | `0x1c` |
| `func_15071E58` | `0x7c` |
| `func_15071ED4` | `0x40` |
| `func_15071F14` | `0x40` |
| `func_15071F54` | `0x2c` |
| `func_15071F80` | `0x30` |
| `func_15071FB0` | `0x2c` |
| `func_15071FDC` | `0x1c8` |
| `func_150721A4` | `0x44` |
| `func_150721E8` | `0x20` |
| `func_15072208` | `0xe8` |
| `func_150722F0` | `0x4c` |
| `func_1507233C` | `0x24` |
| `func_15072360` | `0x28` |
| `func_15072388` | `0x24` |
| `func_150723AC` | `0x34` |
| `func_150723E0` | `0x40` |
| `func_15072420` | `0x24c` |
| `func_1507266C` | `0xd4` |
| `func_15072740` | `0x6c` |
| `func_150727AC` | `0x44` |
| `func_150727F0` | `0x128` |
| `func_15072918` | `0x28` |
| `func_15072940` | `0x28` |
| `func_15072968` | `0x4c` |
| `func_150729B4` | `0x1c` |
| `func_150729D0` | `0x44` |
| `func_15072A14` | `0x2c` |
| `func_15072A40` | `0x3c` |
| `func_15072A7C` | `0x7c` |
| `func_15072AF8` | `0x4c` |
| `func_15072B44` | `0x25c` |
| `func_15072DA0` | `0x38` |
| `func_15072DD8` | `0x60` |
| `func_15072E38` | `0x44` |
| `func_15072E7C` | `0x1c` |
| `func_15072E98` | `0x28` |
| `func_15072EC0` | `0x34` |
| `func_15072EF4` | `0x1c` |
| `func_15072F10` | `0x13c` |
| `func_1507304C` | `0x8` |
| `func_15073054` | `0x24` |
| `func_15073078` | `0x2c` |
| `func_150730A4` | `0x2c` |
| `func_150730D0` | `0x48` |
| `func_15073118` | `0x314` |
| `func_1507342C` | `0x4bc` |
| `func_150738E8` | `0xbc` |
| `func_150739A4` | `0x1c` |
| `func_150739C0` | `0x68` |
| `func_15073A28` | `0x28` |
| `func_15073A50` | `0xe8` |
| `func_15073B38` | `0xf0` |
| `func_15073C28` | `0x20` |
| `func_15073C48` | `0x8` |
| `func_15073C50` | `0x68` |
| `func_15073CB8` | `0x3c` |
| `func_15073CF4` | `0x40` |
| `func_15073D34` | `0x40` |
| `func_15073D74` | `0x30` |
| `func_15073DA4` | `0x88` |
| `func_15073E2C` | `0x78` |
| `func_15073EA4` | `0x78` |
| `func_15073F1C` | `0x38` |
| `func_15073F54` | `0x8` |
| `func_15073F5C` | `0x1c` |
| `func_15073F78` | `0x28` |
| `func_15073FA0` | `0x6a4` |
| `func_15074644` | `0x20` |
| `func_15074664` | `0x8c` |
| `func_150746F0` | `0xf4` |
| `func_150747E4` | `0x5c` |
| `func_15074840` | `0x30` |
| `func_15074870` | `0x1c` |
| `func_1507488C` | `0x68` |
| `func_150748F4` | `0x18` |
| `func_1507490C` | `0x74` |
| `func_15074980` | `0xc4` |
| `func_15074A44` | `0x28` |
| `func_15074A6C` | `0x28` |
| `func_15074A94` | `0xe8` |
| `func_15074B7C` | `0x5c` |
| `func_15074BD8` | `0x14` |
| `func_15074BEC` | `0x14` |
| `func_15074C00` | `0x80` |
| `func_15074C80` | `0x16c` |
| `func_15074DEC` | `0x18` |
| `func_15074E04` | `0x7c` |
| `func_15074E80` | `0x68` |
| `func_15074EE8` | `0x48` |
| `func_15074F30` | `0x18` |
| `func_15074F48` | `0x8c` |
| `func_15074FD4` | `0x7c` |
| `func_15075050` | `0x54` |
| `func_150750A4` | `0x20` |
| `func_150750C4` | `0x98` |
| `func_1507515C` | `0x2a4` |

### `game_A28B0.c`

Range SHA-1: `634a553ad90bcc9606e0ce631f363a74df98daa8`.

| US member | Recovered raw span |
| --- | ---: |
| `func_15075400` | `0x98` |
| `func_15075498` | `0xb0` |
| `func_15075548` | `0x108` |
| `func_15075650` | `0x234` |
| `func_15075884` | `0xb4` |
| `func_15075938` | `0x118` |
| `func_15075A50` | `0x5c` |
| `func_15075AAC` | `0xb4` |
| `func_15075B60` | `0x2c` |
| `func_15075B8C` | `0x2c` |
| `func_15075BB8` | `0x30` |
| `func_15075BE8` | `0x3c` |
| `func_15075C24` | `0x7c` |
| `func_15075CA0` | `0x2c` |
| `func_15075CCC` | `0x40` |
| `func_15075D0C` | `0x2c` |
| `func_15075D38` | `0x2c` |
| `func_15075D64` | `0x38` |
| `func_15075D9C` | `0x2c` |
| `func_15075DC8` | `0x20` |
| `func_15075DE8` | `0x84` |
| `func_15075E6C` | `0x2c` |
| `func_15075E98` | `0x1c` |
| `func_15075EB4` | `0x4c` |
| `func_15075F00` | `0x40` |
| `func_15075F40` | `0x2c` |
| `func_15075F6C` | `0xc0` |
| `func_1507602C` | `0x19c` |
| `func_150761C8` | `0x2c` |
| `func_150761F4` | `0x2c` |
| `func_15076220` | `0x30` |
| `func_15076250` | `0x60` |
| `func_150762B0` | `0x24` |
| `func_150762D4` | `0x6c` |
| `func_15076340` | `0x54` |
| `func_15076394` | `0x1c` |
| `func_150763B0` | `0x118` |
| `func_150764C8` | `0x1c` |
| `func_150764E4` | `0x1c` |
| `func_15076500` | `0x2c` |
| `func_1507652C` | `0x70` |
| `func_1507659C` | `0x64` |
| `func_15076600` | `0x8` |
| `func_15076608` | `0x1c` |
| `func_15076624` | `0x54` |
| `func_15076678` | `0x58` |
| `func_150766D0` | `0x90` |
| `func_15076760` | `0x8` |
| `func_15076768` | `0x8c` |
| `func_150767F4` | `0xe8` |
| `func_150768DC` | `0x280` |
| `func_15076B5C` | `0x1c` |
| `func_15076B78` | `0x1c` |
| `func_15076B94` | `0xe8` |
| `func_15076C7C` | `0x38` |
| `func_15076CB4` | `0x18` |
| `func_15076CCC` | `0x38` |
| `func_15076D04` | `0x38` |
| `func_15076D3C` | `0xb8` |
| `func_15076DF4` | `0x1c` |
| `func_15076E10` | `0x38` |
| `func_15076E48` | `0x8` |
| `func_15076E50` | `0xf0` |
| `func_15076F40` | `0x38` |
| `func_15076F78` | `0x30` |
| `func_15076FA8` | `0x13c` |
| `func_150770E4` | `0x90` |
| `func_15077174` | `0x1c` |
| `func_15077190` | `0x60` |
| `func_150771F0` | `0xa4` |
| `func_15077294` | `0x54` |
| `func_150772E8` | `0x30` |
| `func_15077318` | `0x44` |
| `func_1507735C` | `0x8` |
| `func_15077364` | `0xa0` |
| `func_15077404` | `0xb0` |
| `func_150774B4` | `0x54` |
| `func_15077508` | `0x3e8` |
| `func_150778F0` | `0xb8` |
| `func_150779A8` | `0x2c` |
| `func_150779D4` | `0xcc` |
| `func_15077AA0` | `0x1c` |
| `func_15077ABC` | `0x58` |
| `func_15077B14` | `0x30` |
| `func_15077B44` | `0x3c` |
| `func_15077B80` | `0x34` |
| `func_15077BB4` | `0x30` |
| `func_15077BE4` | `0x38` |
| `func_15077C1C` | `0x1c` |
| `func_15077C38` | `0x168` |
| `func_15077DA0` | `0x1c` |
| `func_15077DBC` | `0xe0` |
| `func_15077E9C` | `0x50` |
| `func_15077EEC` | `0x1c` |
| `func_15077F08` | `0x2c` |
| `func_15077F34` | `0x30` |
| `func_15077F64` | `0x110` |
| `func_15078074` | `0xc8` |
| `func_1507813C` | `0x68` |
| `func_150781A4` | `0x50` |
| `func_150781F4` | `0xd8` |
| `func_150782CC` | `0x1c` |
| `func_150782E8` | `0x70` |
| `func_15078358` | `0x44` |
| `func_1507839C` | `0x184` |
| `func_15078520` | `0x24` |
| `func_15078544` | `0x258` |
| `func_1507879C` | `0xd8` |
| `func_15078874` | `0x1c` |
| `func_15078890` | `0x70` |
| `func_15078900` | `0x108` |
| `func_15078A08` | `0x58` |
| `func_15078A60` | `0x5ac` |
| `func_1507900C` | `0x30` |
| `func_1507903C` | `0x54` |
| `func_15079090` | `0x34` |
| `func_150790C4` | `0x58` |
| `func_1507911C` | `0xd4` |
| `func_150791F0` | `0x38` |
| `func_15079228` | `0xb8` |
| `func_150792E0` | `0x1c` |
| `func_150792FC` | `0x38` |
| `func_15079334` | `0x5c` |
| `func_15079390` | `0x48` |
| `func_150793D8` | `0x198` |
| `func_15079570` | `0xec` |
| `func_1507965C` | `0x70` |
| `func_150796CC` | `0xc4` |
| `func_15079790` | `0xf0` |
| `func_15079880` | `0x78` |
| `func_150798F8` | `0x30` |
| `func_15079928` | `0x60` |
| `func_15079988` | `0x2c` |
| `func_150799B4` | `0x74` |
| `func_15079A28` | `0x30` |
| `func_15079A58` | `0x40` |
| `func_15079A98` | `0x98` |
| `func_15079B30` | `0x3f4` |
| `func_15079F24` | `0x2c` |
| `func_15079F50` | `0x1c` |
| `func_15079F6C` | `0x50` |
| `func_15079FBC` | `0x144` |
| `func_1507A100` | `0x64` |
| `func_1507A164` | `0xac` |
| `func_1507A210` | `0x60` |
| `func_1507A270` | `0x34` |
| `func_1507A2A4` | `0x54` |
| `func_1507A2F8` | `0xbc` |
| `func_1507A3B4` | `0x18` |
| `func_1507A3CC` | `0x1c` |
| `func_1507A3E8` | `0x40` |
| `func_1507A428` | `0x54` |
| `func_1507A47C` | `0x58` |
| `func_1507A4D4` | `0x54` |
| `func_1507A528` | `0xf8` |
| `func_1507A620` | `0xdc` |
| `func_1507A6FC` | `0x20` |
| `func_1507A71C` | `0x58` |
| `func_1507A774` | `0x4c` |
| `func_1507A7C0` | `0x1c` |
| `func_1507A7DC` | `0x2c` |
| `func_1507A808` | `0x30` |
| `func_1507A838` | `0x40` |
| `func_1507A878` | `0x30` |
| `func_1507A8A8` | `0x44` |
| `func_1507A8EC` | `0x98` |
| `func_1507A984` | `0xc4` |
| `func_1507AA48` | `0x268` |
| `func_1507ACB0` | `0x30` |
| `func_1507ACE0` | `0x50` |
| `func_1507AD30` | `0x30` |
| `func_1507AD60` | `0x1c` |
| `func_1507AD7C` | `0x30` |
| `func_1507ADAC` | `0x34` |
| `func_1507ADE0` | `0x98` |
| `func_1507AE78` | `0x1c` |
| `func_1507AE94` | `0xa8` |
| `func_1507AF3C` | `0x5c` |
| `func_1507AF98` | `0xa8` |
| `func_1507B040` | `0x18` |
| `func_1507B058` | `0x104` |
| `func_1507B15C` | `0x1c` |
| `func_1507B178` | `0xbc` |
| `func_1507B234` | `0x4c` |
| `func_1507B280` | `0x4c` |
| `func_1507B2CC` | `0x4c` |
| `func_1507B318` | `0x4c` |
| `func_1507B364` | `0x4c` |
| `func_1507B3B0` | `0x4c` |
| `func_1507B3FC` | `0x4c` |
| `func_1507B448` | `0x4c` |
| `func_1507B494` | `0x4c` |
| `func_1507B4E0` | `0x4c` |
| `func_1507B52C` | `0x4c` |
| `func_1507B578` | `0x4c` |
| `func_1507B5C4` | `0x6c` |
| `func_1507B630` | `0xb0` |
| `func_1507B6E0` | `0x54` |
| `func_1507B734` | `0x88` |
| `func_1507B7BC` | `0x2c` |
| `func_1507B7E8` | `0x9c` |
| `func_1507B884` | `0x70` |
| `func_1507B8F4` | `0x64` |
| `func_1507B958` | `0x1c` |
| `func_1507B974` | `0xd4` |
| `func_1507BA48` | `0x88` |
| `func_1507BAD0` | `0x28` |
| `func_1507BAF8` | `0x28` |
| `func_1507BB20` | `0x8` |
| `func_1507BB28` | `0xec` |
| `func_1507BC14` | `0x19c` |

### `game_169510.c`

Range SHA-1: `0821aa3815d7f3892abb923b571b1b43096bb3da`.

| US member | Recovered raw span |
| --- | ---: |
| `func_1513C060` | `0x2f0` |
| `func_1513C350` | `0x19c` |
| `func_1513C4EC` | `0xc4` |
| `func_1513C5B0` | `0xa0` |
| `func_1513C650` | `0xec` |
| `func_1513C73C` | `0xc8` |
| `func_1513C804` | `0xd0` |
| `func_1513C8D4` | `0x2c` |
| `func_1513C900` | `0x2c` |
| `func_1513C92C` | `0x84` |
| `func_1513C9B0` | `0x4c` |
| `func_1513C9FC` | `0x4c` |
| `func_1513CA48` | `0x24` |
| `func_1513CA6C` | `0x34` |
| `func_1513CAA0` | `0x34` |
| `func_1513CAD4` | `0x84` |
| `func_1513CB58` | `0x4c` |
| `func_1513CBA4` | `0x4c` |
| `func_1513CBF0` | `0x3ac` |
| `func_1513CF9C` | `0x34` |
| `func_1513CFD0` | `0x14` |
| `func_1513CFE4` | `0x30c` |
| `func_1513D2F0` | `0x1c8` |
| `func_1513D4B8` | `0x6c` |
| `func_1513D524` | `0x70` |
| `func_1513D594` | `0xd4` |
| `func_1513D668` | `0x94` |
| `func_1513D6FC` | `0x404` |
| `func_1513DB00` | `0x49c` |
| `func_1513DF9C` | `0xd4` |
| `func_1513E070` | `0x14` |
| `func_1513E084` | `0xb8` |
| `func_1513E13C` | `0x168` |
| `func_1513E2A4` | `0x8` |
| `func_1513E2AC` | `0x43c` |
| `func_1513E6E8` | `0x154` |
| `func_1513E83C` | `0x29c` |
| `func_1513EAD8` | `0x2dc` |
| `func_1513EDB4` | `0x30` |
| `func_1513EDE4` | `0x30` |
| `func_1513EE14` | `0x300` |
| `func_1513F114` | `0x39c` |
| `func_1513F4B0` | `0x34` |
| `func_1513F4E4` | `0x19c` |
| `func_1513F680` | `0x40` |
| `func_1513F6C0` | `0x28` |
| `func_1513F6E8` | `0x40` |
| `func_1513F728` | `0x304` |
| `func_1513FA2C` | `0x44` |
| `func_1513FA70` | `0x44` |
| `func_1513FAB4` | `0x540` |
| `func_1513FFF4` | `0xdc` |
| `func_151400D0` | `0xc0` |
| `func_15140190` | `0x218` |
| `func_151403A8` | `0x34` |
| `func_151403DC` | `0x34` |
| `func_15140410` | `0x29c` |
| `func_151406AC` | `0x124` |

