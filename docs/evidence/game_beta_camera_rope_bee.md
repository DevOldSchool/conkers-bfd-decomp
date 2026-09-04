# US camera, rope and bee-cavern source-family boundaries

Evidence type: `structural_analysis`

This review assigns three existing raw ranges to source families identified
from owned earlier ROMs. It records complete US membership and checks their
retail structure independently. The ranges are reviewed structural hypotheses,
not recovered original linker symbols. Beta similarity and successful raw-ASM
integration do not make any function instruction-matched C.

## Inputs and boundary provenance

- Retail US ROM SHA-1: `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
- Retail game-code SHA-1: `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
- Debug normalized ROM SHA-1: `3b99222ee76f6277a963142cd807b3df25d5174f`.
- ECTS normalized ROM SHA-1: `06597dc935651f8995bfacc30fde6e621d44c3e1`.
- Earlier-build source paths and function anchors: cached `./conker beta-index`
  output in `build/beta-index/report.json`. This command validates the input
  hashes and reuses its function-index caches without `--refresh`.
- External navigation map: local checkout of
  `mkst/conker@3adf229175c037c771f251f169f9dd80ca306924`,
  `conker/conker.us.yaml`.

| Assigned source | Upstream combined offsets | Current game offsets | Members | Bytes |
| --- | --- | --- | ---: | ---: |
| `src/game/camera/camera_camera.c` | `0x14FF90:0x155C90` | `0x122AE0:0x1287E0` | 45 | 23,808 |
| `src/game/effects/holtenrope.c` | `0x1E0560:0x1E2180` | `0x1B30B0:0x1B4CD0` | 17 | 7,200 |
| `src/game/effects/effects_sfx_w1_bee_cavern.c` | `0xEB340:0xEBD00` | `0xBDE90:0xBE850` | 8 | 2,496 |

The translation subtracts the US combined-image game base `0x2D4B0`.
The upstream camera range is explicitly a C unit named `game_14FF90`; the
other two are raw split ranges, so their grouping needs the structural
corroboration below. No upstream C implementation or completion state is
imported. All six endpoints already exist in the active map.

## Camera identity

The debug data contains `../Camera/camera_camera.c` at offset `0x21604`,
runtime `0x8007C6F4`. Instructions at debug game offsets `0x12A7EC` and
`0x12A7F0`, inside `func_1512A758`, construct that exact pointer for a debug
parameter call. Its retail counterpart is inferred as `func_15124C38`.
The automatic whole-function fingerprint does not match this changed body.

Independent checks of the two bodies establish the relationship:

- Both first test the object's halfword flag and the second argument, then
  follow the linked object pointer. The debug fields `+0x7E4`/`+0x3D0` become
  retail `+0x7F4`/`+0x3D4`.
- Both calculate a height from linked signed halfwords including `+0x114`,
  handle the `0x100`/`0x200` flags, and pass three stack halfword addresses at
  `+0x52`, `+0x50`, and `+0x4E` to the next calculation.
- Debug calls `func_1504A150`, `func_1512ADCC`, `func_1504A150` in order;
  the cached independent correlations map these to the same retail sequence
  `func_150495B0`, `func_15125490`, `func_150495B0`.
- The nearby ordered correlations include debug `0x12A5F0` to retail
  `0x124AB4`, and the strong four-function run starting at debug `0x12AC6C`
  to retail `0x125330`. They bracket the changed camera routine.

Retail adds substantial character/height handling and omits the filename
parameter call. Its body is 1,540 bytes versus 1,052 in debug; neither the
filename alone nor a fixed cross-version offset is used to claim equality.
The existing C-unit extent, these anchors and the surrounding camera field
accesses support the assigned family name. Exact historical ownership of all
45 members remains a structural inference.

ECTS addresses below use the loader-derived layout correction documented in
[ECTS game layout](ects_game_layout.md). US ranges and body comparisons are
unchanged.

## Holten rope identity and grouping

ECTS `func_151A1870` references `../Effects/HoltenRope/holtenrope.c` at data
offsets `0x27034`, `0x2705C`, and `0x27084`, through three debug parameter
calls. Its runtime core corresponds to retail `func_151B4B78`:

- Both begin the point chain at float bits `0xC47A0000` and use an increment
  loaded from a constant table.
- Both write the first points at `+0x48` and `+0x60`, clear their other axes,
  and use the same unrolled four-point loop: counter starts at 2, increments
  by 4, ends at 10, and the pointer advances by `0x60`.
- Both finish by clearing bit 1 of the byte at `+0x10` and return 1.

The ECTS wrapper is 336 bytes including parameter calls and a stack frame;
retail is a 164-byte leaf. Register allocation differs. The preceding three
functions also have ordered strong correlations: retail `0x1B48DC`,
`0x1B498C`, `0x1B4A14` correspond to ECTS `0x1A15D4`, `0x1A1684`, `0x1A170C`.

The retail group opens with an allocator for effect type `0x33`, copying a
`0x38`-byte descriptor and reserving a further `0x150` bytes. Its update and
render callbacks occur together at `0x8008BF04` and `0x8008BF0C`; the end
wrappers are in that same descriptor at `0x8008BF2C` and `0x8008BF30`.
The method table at `0x8008FAF0:0x8008FB18` contains the point-chain initializer
and the related force/point handlers. It also references the preceding shared
helper `func_151B2FA0`; this does not justify absorbing that other raw range.
The next range starts with a different effect constructor at `0x1B4CD0`.
These callbacks, internal calls and shared layout corroborate the existing
17-member grouping beyond simple alignment.

## Bee-cavern effects identity and grouping

ECTS retains `../Effects/Sfx/effects_sfx_w1_bee_cavern.c` in thirteen data
occurrences from `0x1DD50` through `0x1E194`. The references occur in two
routines, `func_150B6C1C` and `func_150B7250`; their retail counterparts are
inferred as `func_150BDF0C` and `func_150BE1C4`.

The first ECTS routine registers twelve debug parameters before decrementing
its effect timer and emitting randomized particles. Retail retains that
timer/emission pattern with baked-in values and an adjusted field layout.
Its sequence of random, effect-spawn and copy operations corresponds to the
post-parameter-call sequence in ECTS, although the particle parameters differ.
The second routine in each version advances the float at `+0x14` using the
float at `+0x80`, then tests a height limit and returns a boolean. Retail
reverses the comparison and uses a fixed 120.0 limit; ECTS obtains its limit
from a debug parameter. These are source-family relationships, not matches.

The group's first function has an independent ordered correlation, retail
`0xBDE90` to ECTS `0xB6BA0`. Retail callback tables reference its timer
routine at `0x8008A624`, teardown at `0x8008A9C8`, and height test at
`0x8008ACF0`. The following helpers and renderer complete the existing
eight-function split; the preceding function and final renderer each return
before their respective boundary padding. The exact historical file extent
is less certain than the two named anchors, so it is explicitly retained as
a structural grouping hypothesis.

## Raw membership and verification

Every word in each existing generated raw assembly range was compared against
the independently ROM-derived retail code, including final padding. All
conditional branch targets stay inside their reviewed range. The preceding
functions return before the starts; each end is followed by a fresh function
prologue. Ordered raw `glabel` membership agrees with the ROM function index.
The three ranges cover 70 functions and 33,504 bytes without overlaps.

Registration uses `./conker register-source-unit --overlay game
--register-members` with this evidence reference. All newly registered
functions remain `raw_asm`; generated source skeletons contain ordered
`GLOBAL_ASM` pragmas. No beta code, guessed C bodies, or target assembly edits
are introduced. Integration must pass the complete US overlay comparison
before these source mappings are retained in the canonical build.

Sight and trail filename leads still need further retail/body and full-range
review; they receive no mapping credit in this batch.

`./conker progress integrate --profile us --all-reviewed` succeeds on the first
attempt, retaining precisely these three new mixed C/ASM mappings. The complete
2,072,880-byte output has SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`, identical to the owned US overlay.
The generated comparison map remains raw assembly. All 170 Python tests pass;
progress and whitespace checks pass. No main-executable build was needed for
these overlay-only source mappings.

Reviewed coverage becomes 302,176 / 2,237,392 bytes (13.5057%) overall and
203,664 / 2,072,880 bytes (9.8252%) in the game overlay. Exact matched code
remains 150,564 bytes (6.7294%). The inventory now has 496 functions and 131
source units, including the 70 new raw functions and three mixed units; no new
function receives match credit.

### src/game/camera/camera_camera.c

Raw range SHA-1: `531389c00d98c41e7195f3a0cc9b229491e4473e`.

| US member | Function-index span |
| --- | ---: |
| `func_15122AE0` | `0x17C` |
| `func_15122C5C` | `0x414` |
| `func_15123070` | `0x10C` |
| `func_1512317C` | `0x38C` |
| `func_15123508` | `0x60` |
| `func_15123568` | `0x168` |
| `func_151236D0` | `0x264` |
| `func_15123934` | `0x98` |
| `func_151239CC` | `0x88` |
| `func_15123A54` | `0xD1C` |
| `func_15124770` | `0x50` |
| `func_151247C0` | `0x2F4` |
| `func_15124AB4` | `0x64` |
| `func_15124B18` | `0x120` |
| `func_15124C38` | `0x604` |
| `func_1512523C` | `0xF4` |
| `func_15125330` | `0x64` |
| `func_15125394` | `0x38` |
| `func_151253CC` | `0xC4` |
| `func_15125490` | `0x64` |
| `func_151254F4` | `0xA0` |
| `func_15125594` | `0x74` |
| `func_15125608` | `0x20` |
| `func_15125628` | `0x68` |
| `func_15125690` | `0x2C` |
| `func_151256BC` | `0x268` |
| `func_15125924` | `0x148` |
| `func_15125A6C` | `0x1D4` |
| `func_15125C40` | `0x174` |
| `func_15125DB4` | `0x384` |
| `func_15126138` | `0x104` |
| `func_1512623C` | `0x13C` |
| `func_15126378` | `0x11A8` |
| `func_15127520` | `0x290` |
| `func_151277B0` | `0x1F0` |
| `func_151279A0` | `0x518` |
| `func_15127EB8` | `0x134` |
| `func_15127FEC` | `0x44` |
| `func_15128030` | `0x388` |
| `func_151283B8` | `0x10C` |
| `func_151284C4` | `0x7C` |
| `func_15128540` | `0x140` |
| `func_15128680` | `0xC` |
| `func_1512868C` | `0xE8` |
| `func_15128774` | `0x6C` |

### src/game/effects/holtenrope.c

Raw range SHA-1: `d4ef2d3bb23ebaf66e39796d56fc040f9182a38a`.

| US member | Function-index span |
| --- | ---: |
| `func_151B30B0` | `0xD4` |
| `func_151B3184` | `0x144` |
| `func_151B32C8` | `0x76C` |
| `func_151B3A34` | `0x48` |
| `func_151B3A7C` | `0x274` |
| `func_151B3CF0` | `0x238` |
| `func_151B3F28` | `0xB4` |
| `func_151B3FDC` | `0x2C8` |
| `func_151B42A4` | `0x534` |
| `func_151B47D8` | `0x104` |
| `func_151B48DC` | `0xB0` |
| `func_151B498C` | `0x88` |
| `func_151B4A14` | `0x164` |
| `func_151B4B78` | `0xA4` |
| `func_151B4C1C` | `0x50` |
| `func_151B4C6C` | `0x2C` |
| `func_151B4C98` | `0x38` |

### src/game/effects/effects_sfx_w1_bee_cavern.c

Raw range SHA-1: `74adff34edfe73d677ddda6283e777727fdcfd91`.

| US member | Function-index span |
| --- | ---: |
| `func_150BDE90` | `0x7C` |
| `func_150BDF0C` | `0x244` |
| `func_150BE150` | `0x74` |
| `func_150BE1C4` | `0x4C` |
| `func_150BE210` | `0xD8` |
| `func_150BE2E8` | `0x150` |
| `func_150BE438` | `0x5C` |
| `func_150BE494` | `0x3BC` |
