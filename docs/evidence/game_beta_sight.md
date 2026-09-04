# US sight source-family mapping

Evidence type: `structural_analysis`

This maps the existing raw game range `0x1C71A0:0x1CD2C0` to
`src/game/effects/effects_sight.c`: 46 functions and 24,864 bytes. The name is
inferred from an ECTS source-path anchor and independently reviewed retail
code. The complete range is a structural grouping hypothesis, not a recovered
original linker-map or translation-unit symbol. Its members remain raw ASM.

## Inputs

The owned images were validated against their configured normalized hashes:

| Image | Normalized ROM SHA-1 | Game-code SHA-1 |
| --- | --- | --- |
| Retail US | `4cbadd3c4e0729dec46af64ad018050eada4f47a` | `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5` |
| Debug | `3b99222ee76f6277a963142cd807b3df25d5174f` | `a1c41378211a6e50c60fd16ffeccedb3909d7bf1` |
| ECTS | `06597dc935651f8995bfacc30fde6e621d44c3e1` | `b4f9b6d9e4f93b85fbecbf3e68fc416c7b1d3b4a` |

The existing `./conker beta-index` report and function-index caches supply
discovery candidates. The instruction and source-string checks below read
the owned images independently; no beta image is a US matching target.

ECTS offsets and its code hash below incorporate the loader-derived layout
correction. Source-string runtime addresses and the US body evidence are
unchanged.

## Source identity and changed retail anchor

ECTS retains `../Effects/Sight/effects_sight.c` at game-data offsets
`0x27C08`, `0x27C48`, `0x27C98`, and `0x27CE8`, corresponding to runtime
addresses `0x80090B98`, `0x80090BD8`, `0x80090C28`, and `0x80090C78`.
Every occurrence was checked directly. Adjacent parameter names are `WIDTH`,
`HEIGHT`, `TOP_POSITION`, and `BOTTOM_POSITION`.

ECTS `func_151B82D0` constructs these filename pointers at game offsets
`0x1B8308`, `0x1B834C`, `0x1B839C`, and `0x1B83E8` for four debug parameter
calls. Its retail counterpart is inferred as `func_151CCF08`, whose complete
796-byte body also has a strong cached correlation with the later debug
`func_151CF9B4`. The ECTS body is 912 bytes and is not an exact fingerprint
match to retail.

The independent ECTS/retail body review finds a distinctive common descriptor
and emission loop after the debug parameter setup:

- Both use a `0x138`-byte frame, establish a 130.0 position component, and
  build a screen-space effect descriptor with a 300 halfword at stack `+0xF2`.
- Both fill the descriptor's `+0xFA` mode with 7 and its color/alpha bytes
  through `+0x103` with 255.
- The same ordered constants occupy the same descriptor slots:
  `0x00200004` at `+0x108`, `0x001F0601` at `+0x10C`, followed by 8, 19,
  128 and 32 at `+0x110`, `+0x114`, `+0x118` and `+0x11C`.
- Both set unit scale at `+0x128` and `+0x12C`, clear the following two
  floats, alternate top/bottom placement at `+0xE4`, and pass the completed
  descriptor to the effect emitter followed by a copy operation.

Retail replaces the four parameter calls with constants and mode-dependent
tables, adds arguments controlling selection and appearance, and changes
descriptor flags and dimensions. These differences are retained as evidence
of a related source family, not ignored to claim instruction equality.

## Range and grouping evidence

The local upstream checkout at
`mkst/conker@3adf229175c037c771f251f169f9dd80ca306924` records the raw combined
range `0x1F4650:0x1FA770` in `conker/conker.us.yaml`. Subtracting `0x2D4B0`
gives the existing retail game range above. Unlike an original object symbol,
this upstream raw split is only navigation evidence.

The full range contains related sight setup, update, callback and screen-effect
helpers. Internal calls include `func_151C71A0` to `func_151C756C`, and the
later dispatcher `func_151C9BA0` to the descriptor constructors and update
routines. Its reset path `func_151C9DE8` directly calls the identified
`func_151CCF08`. Callback tables reference the opening setup at `0x80082EC0`,
update handlers at `0x80089F10:0x80089F98`, and later routines at
`0x8008ACD8:0x8008ACF8`. These table references establish uses, not ownership
of the tables themselves.

The range has 29 cached later-debug correlations, including 23 marked strong,
and 15 ECTS correlations, including seven marked strong. They corroborate
the surrounding source order. Every current raw assembly word was compared
with the retail image; all 46 top-level labels agree with the function index.
Conditional branches stay inside the proposed range, the preceding function
returns before its padding, and the next range begins with a fresh prologue.

The early and late helper clusters need not be one original file merely
because they are adjacent. The retained filename proves a source identity
inside this range; the grouping, neighboring correlations, callback uses and
existing split support the reviewed working boundary without proving exact
historical ownership of all 46 functions. No data/BSS allocation is assigned
and no additional interior split is invented.

## Trail lead retained for further research

ECTS `func_151A2F44` retains `../Effects/Trail/trail.c` beside controls for
floating-sprite frame speed and size, dynamic-rectangle dimensions and alpha,
and trail life. It is a 1,532-byte routine with several effect-construction
paths. The nearby retail range `0x1B6320:0x1B8400` has substantially different
constructors and callbacks. The first retail constructor shares an object
position-copy pattern, which is insufficient to identify it as the complete
counterpart of that ECTS routine.

The earlier negative call-reference result used an incorrect ECTS code base
and is withdrawn. The [loader-derived correction](ects_game_layout.md)
places the anchor at `0x151A2F44`, with a direct call from its wrapper at
`0x151A2F2C`. That wrapper is called at `0x1506688C`. The correlated retail
command instead calls `func_150E0348`, so proximity to the later ECTS
constructor alone cannot establish that retail `0x1B6320` owns the retained
trail filename. This remains a source-identity lead; this sight review grants
no trail mapping credit.

A wider case-insensitive ASCII search for `.c`, `.h`, `.cc`, and `.cpp` in
each image's first `0x40000` normalized ROM bytes and decompressed game code
and data found no further source-path strings beyond the cached beta-index
paths. The additional short matches were instruction/binary fragments. This
does not cover every separately compressed asset or establish the absence of
other non-string evidence.

## Registration and validation

Use `./conker register-source-unit --overlay game --register-members` with
this note as the evidence reference. The command creates the ordered source
skeleton and inventory records. The complete US overlay comparison gates
integration; successful integration does not credit any function as matched C.

`./conker progress integrate --profile us func_151C71A0` passes on the first
attempt. The complete 2,072,880-byte integrated US overlay has SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`, matching the owned ROM-derived
payload. The comparison map keeps the range as raw assembly. All 46 new
functions remain `raw_asm` in the inventory, while the source unit is `mixed`.

All 170 Python tests pass; generated progress and whitespace checks pass.
Only the game overlay was rebuilt for this overlay mapping. Reviewed coverage
is now 327,040 / 2,237,392 tracked bytes (14.6170%) overall, and
228,528 / 2,072,880 bytes (11.0247%) in the game overlay. The 542-function
inventory has 132 source units, of which 130 have reviewed boundaries.
Exact matched code remains 150,564 bytes (6.7294%).

Raw range SHA-1: `63285b2baff0d9f96b1efcab0cc5058b42c09a1f`.

| US member | Function-index span |
| --- | ---: |
| `func_151C71A0` | `0x3CC` |
| `func_151C756C` | `0x92C` |
| `func_151C7E98` | `0x438` |
| `func_151C82D0` | `0x3A4` |
| `func_151C8674` | `0x38` |
| `func_151C86AC` | `0x100` |
| `func_151C87AC` | `0x34` |
| `func_151C87E0` | `0x1BC` |
| `func_151C899C` | `0x630` |
| `func_151C8FCC` | `0x1CC` |
| `func_151C9198` | `0x33C` |
| `func_151C94D4` | `0x104` |
| `func_151C95D8` | `0x104` |
| `func_151C96DC` | `0x30` |
| `func_151C970C` | `0x34` |
| `func_151C9740` | `0x380` |
| `func_151C9AC0` | `0x70` |
| `func_151C9B30` | `0x34` |
| `func_151C9B64` | `0x3C` |
| `func_151C9BA0` | `0x248` |
| `func_151C9DE8` | `0xEC` |
| `func_151C9ED4` | `0x64` |
| `func_151C9F38` | `0x768` |
| `func_151CA6A0` | `0x42C` |
| `func_151CAACC` | `0xAC` |
| `func_151CAB78` | `0x1B0` |
| `func_151CAD28` | `0x3E8` |
| `func_151CB110` | `0x38C` |
| `func_151CB49C` | `0x74` |
| `func_151CB510` | `0xEC` |
| `func_151CB5FC` | `0x31C` |
| `func_151CB918` | `0x58` |
| `func_151CB970` | `0x1FC` |
| `func_151CBB6C` | `0x74` |
| `func_151CBBE0` | `0x80` |
| `func_151CBC60` | `0x574` |
| `func_151CC1D4` | `0xBC` |
| `func_151CC290` | `0x2C` |
| `func_151CC2BC` | `0x268` |
| `func_151CC524` | `0x258` |
| `func_151CC77C` | `0xC4` |
| `func_151CC840` | `0x4DC` |
| `func_151CCD1C` | `0x178` |
| `func_151CCE94` | `0x74` |
| `func_151CCF08` | `0x31C` |
| `func_151CD224` | `0x9C` |
