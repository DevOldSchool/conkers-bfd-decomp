# US game-overlay SDK text boundaries

Evidence type: `structural_analysis`

Ten SDK objects now link directly from the pinned `lib/ultralib` sources into
the US game overlay: 22 functions and `0x1EB0` (7,856) text bytes. Their former
`src/game/sdk/` skeletons and raw-ASM work items have been retired through the
supported command. Progress credits the compiled archive text, without creating
individual matched-function records for these library routines.

## Inputs and method

- US ROM SHA-1: `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
- Decompressed US game-code SHA-1:
  `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
- SDK source: `decompals/ultralib` revision
  `e24c836796df4bf520ff8b11a5c9d2cea3a66cbd`, already pinned locally.
- Comparison objects: existing `lib/ultralib/build/I/libultra/src/**/*.o`.
  The final archive uses matching `libultra_rom` objects built with
  `MODERN_LD=1`; SDK source and object instructions are unchanged.
  A scan of the existing I-L `libultra`, `libultra_d`, and `libultra_rom`
  outputs covered 1,079 distinct complete text templates of at least 32 bytes.
- Raw authority: `build/beta-index/us/game.code.bin`, checked against the
  game-code SHA-1 above, and `reference/game/us/asm/<start>.s`. The beta-index
  directory supplies cached retail bytes here; beta correlations are not used.

The scanner reuses `read_object_templates` and `find_occurrences` from
`scripts/audit_library_boundaries.py`. It compares the entire ELF `.text`
section, including internal spacing and final padding. Only relocation bits
are masked: MIPS26 retains the opcode, and HI16/LO16 retains the instruction
and register fields. Each selected section has exactly one complete masked
occurrence in the US game image. The relocation checks below establish the
corresponding call and data identities rather than treating the masked match
alone as proof.

For every row, the start and end already exist in `config/game/us.yaml`, the
range was raw assembly, and every instruction word in the corresponding raw
assembly file equals the cached US bytes. The listed top-level `glabel`s cover
the complete range, and all referenced `.L` labels are defined within it.
The temporary function and source-unit records were removed only after
checking their exact archive extents and byte-for-byte skeleton contents.

## Archive ranges

Source paths below are relative to `lib/ultralib/src/`. Each basename identifies
the corresponding member of `build/game-libs/us/libultra_2_0I.a`. Offsets are
relative to the decompressed game image; add `0x15000000` for instruction VRAM.

| Source | US game range | Bytes | Recovered US members |
| --- | --- | ---: | --- |
| `gu/random.c` | `0x1EF610:0x1EF640` | 48 | `func_151EF610` |
| `io/visetspecial.c` | `0x1EF640:0x1EF800` | 448 | `func_151EF640` |
| `gu/ortho.c` | `0x1EF800:0x1EF9C0` | 448 | `func_151EF800`, `func_151EF954` |
| `os/settimer.c` | `0x1EF9C0:0x1EFAA0` | 224 | `func_151EF9C0` |
| `libc/sprintf.c` | `0x1EFF70:0x1EFFF0` | 128 | `func_151EFF70`, `func_151EFF94` |
| `gu/normalize.c` | `0x1EFFF0:0x1F0080` | 144 | `func_151EFFF0` |
| `gu/mtxcatl.c` | `0x1F0080:0x1F0140` | 192 | `func_151F0080`, `func_151F00E0` |
| `os/gettime.c` | `0x1F04C0:0x1F0550` | 144 | `func_151F04C0` |
| `io/contpfs.c` | `0x1F0550:0x1F12B0` | 3,424 | `func_151F0550`, `func_151F05AC`, `func_151F0614`, `func_151F0A2C`, `func_151F0BC4`, `func_151F0E20`, `func_151F0F1C`, `func_151F123C` |
| `io/pfschecker.c` | `0x1F12B0:0x1F1D10` | 2,656 | `func_151F12B0`, `func_151F1974`, `func_151F1B28` |

## Symbol and relocation review

- `random.o`: the sized `guRandom` symbol occupies `+0x0:0x2C`, followed by
  four padding bytes. Both references to its seed resolve to `0x80091970`.
  Its complete 16-byte `.data` section equals game-data offset `0xEE50`:
  `0a6b99cd000000000000000000000000`. The separate RZIP data payload preserves
  those initialized bytes. A `NOLOAD` linker section at `0x80091970` binds the
  original section-relative relocations without adding data to the code image.
- `visetspecial.o`: `osViSetSpecialFeatures` occupies `+0x0:0x1B8`.
  Every `__osViNext` reference resolves to the reviewed main data symbol at
  `0x8002BDE4`. Calls resolve to `__osDisableInt=0x10022DC0` and
  `__osRestoreInt=0x10022DE0`.
- `ortho.o`: ELF symbol offsets place `guOrthoF` at `+0x0` and `guOrtho` at
  `+0x154`, exactly matching the raw entries. The wrapper calls the local
  `guOrthoF=0x151EF800`; the other targets are the nearby matrix helpers
  `guMtxIdentF=0x151EFE00` and `guMtxF2L=0x151EFD00`.
- `settimer.o`: `osSetTimer` occupies `+0x0:0xD4`. Its references resolve to
  the main `__osTimerList=0x8002BD70`, `__osInsertTimer=0x10024128`, and
  `__osSetTimerIntr=0x100240B4`.
- `sprintf.o`: the static output callback starts at `+0x0`, with the sized
  `sprintf` symbol at `+0x24`. The callback address passed at game offset
  `0x1EFFB0` resolves locally to `0x151EFF70`. Calls resolve to the main
  `memcpy=0x10022EC0` and `_Printf=0x100020D0`.
- `normalize.o`: `guNormalize` occupies `+0x0:0x84`. Its sole relocation is
  the call at `0x1F0020` to the reviewed main `sqrtf=0x10026530`.
- `mtxcatl.o`: the I/J layout places `guMtxXFML` at `+0x0` and `guMtxCatL`
  at `+0x60`. All six calls resolve consistently to
  `guMtxL2F=0x151EFEB8`, `guMtxXFMF=0x151F0140`,
  `guMtxCatF=0x151F01E0`, and `guMtxF2L=0x151EFD00`. The latter two float
  helpers were subsequently linked from `mtxcatf.o`, replacing the untouched
  `game_21D5F0.c` skeleton; see the additional object evidence.
- `gettime.o`: `osGetTime` occupies `+0x0:0x84`. The calls use the main
  interrupt helpers above and `osGetCount=0x10024770`. Data references resolve
  to `__osBaseCounter=0x800429B8` and the two words of
  `__osCurrentTime=0x800429B0:0x800429B8`.
- `contpfs.o`: the eight ELF function offsets are `+0x0`, `+0x5C`, `+0xC4`,
  `+0x4DC`, `+0x674`, `+0x8D0`, `+0x9CC`, and `+0xCEC`; all equal the raw
  member offsets. They identify `__osSumcalc`, `__osIdCheckSum`,
  `__osRepairPackId`, `__osCheckPackId`, `__osGetId`, `__osCheckId`,
  `__osPfsRWInode`, and `__osPfsSelectBank`. All 36 call relocations resolve
  to the corresponding main-executable SDK routines. In particular,
  references to object-local function names call the main copies, including
  `__osSumcalc=0x10027910`, `__osIdCheckSum=0x1002796C`,
  `__osRepairPackId=0x100279D4`, `__osCheckPackId=0x10027DEC`, and
  `__osPfsSelectBank=0x100285FC`. This is not an ordinary unmodified archive
  object linked at the game VRAM.
- `pfschecker.o`: `osPfsChecker`, `corrupted_init`, and `corrupted` occur at
  ELF offsets `+0x0`, `+0x6C4`, and `+0x878`, respectively. All 15 calls
  resolve to the matching main SDK implementations. Even the two static
  helpers call the main copies at `0x10028D34` and `0x10028EE8`; the explicit
  linker bindings preserve those call instructions.

Main calls use the physical `0x100...` aliases encoded in the target. They
must not be silently replaced with game-local calls or `0x800...` aliases.
The complete `contpfs`, `pfschecker`, `gettime`, and `settimer` text ranges
also equal their main-ROM ranges byte for byte, without relocation masking:
`0x27910:0x28670`, `0x28670:0x290D0`, `0x24F40:0x24FD0`, and
`0x24A40:0x24B20`, respectively. This directly corroborates both the duplicate
SDK identities and their retained calls into the main executable.

## Scope and rejected extensions

These are reviewed, reproducible archive text boundaries with SDK object and
symbol evidence. They do not recover the original Conker linker map or establish
an exact SDK version. Only `random.o` has a non-empty allocated non-text section
among these ten objects; its complete data bytes and runtime address are
independently verified as described above.
In particular, the `mtxcatl` range is also compatible with separate K/L
`mtxxfml.o` and `mtxcatl.o` sections. The existing combined range is retained;
the internal `0x1F00E0` position is not promoted to an original object boundary.

The complete `crc.o` occurrence at `0x1F27E0:0x1F2960` and `piread.o`
occurrence at `0x1EF040:0x1EF080` were subsequently reviewed and integrated,
with explicit new map ends. See [the additional object evidence](game_sdk_additional_objects.md).
The access-queue range `0x1F0350:0x1F0410` matches both PI and SI masked
templates, while a message-buffer reference differs from the main allocation.
It is left unassigned pending a separate section-ownership review.

The matching `mtxcatf.o` range at `0x1F0140:0x1F0350` was subsequently linked
from the archive and its untouched generic source skeleton retired. No
upstream C implementation is copied into the game source tree.

## Reproducing the complete-section comparisons

After preparing the normal SDK research objects and `./conker beta-index`,
the following read-only check reproduces the unique complete-text matches.
It does not substitute for the relocation review above.

```sh
python3 - <<'PY'
import hashlib
import sys
from pathlib import Path
sys.path.insert(0, 'scripts')
from audit_library_boundaries import read_object_templates, find_occurrences

code = Path('build/beta-index/us/game.code.bin').read_bytes()
assert hashlib.sha1(code).hexdigest() == '90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5'
expected = {
    'gu/random': 0x1EF610, 'io/visetspecial': 0x1EF640,
    'gu/ortho': 0x1EF800, 'os/settimer': 0x1EF9C0,
    'libc/sprintf': 0x1EFF70, 'gu/normalize': 0x1EFFF0,
    'gu/mtxcatl': 0x1F0080, 'os/gettime': 0x1F04C0,
    'io/contpfs': 0x1F0550, 'io/pfschecker': 0x1F12B0,
}
for member, start in expected.items():
    path = Path(f'lib/ultralib/build/I/libultra/src/{member}.o')
    text = next(s for s in read_object_templates(path) if s.section == '.text')
    assert find_occurrences(text, code, 0, len(code)) == [start]
    print(member, f'0x{start:X}:0x{start + len(text.text):X}')
PY
```

## Archive integration

`config/game/us.yaml` assigns the ten ranges to `lib` / `.text` entries.
`game-libs` builds the pinned 2.0I ROM archive and stages only the ten required
members, unchanged, in `build/game-libs/us/libultra_2_0I.a`. The game link uses
that archive with `--whole-archive`, rather than `src/game/sdk` placeholders.

`config/game/us-sdk.ld` records the reviewed external and main-copy bindings.
The explicit assignments for `contpfs` and `pfschecker` also override references
to symbols defined in those objects, preserving the main-executable targets
encoded in retail. The library object bodies and SDK sources are not patched.
The script places only the verified seed data in an external `NOLOAD` section;
the separately compressed game-data payload remains unchanged.

The integrated map generator retains library starts and their following raw
boundaries. The independent reference generator converts both C and library
entries back to raw assembly. Consequently future focused comparisons cannot
use an archive-linked object as their own reference.

`./conker retire-library-units --evidence-reference
 docs/evidence/game_sdk_tail_text_bounds.md` removes the ten untouched source
skeletons and 22 work items atomically. The command now supports mixed game
units as well as raw main units, requires an exact library `.text` extent,
rejects active/deferred/matched function work and edited skeletons, and
validates the remaining inventory before writing it.

Validation on 2026-09-02:

- `./conker game-build --refresh`: byte-identical US game code, SHA-1
  `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
- `./conker build --profile us`: byte-identical complete US ROM, SHA-1
  `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
- All 147 repository tests passed, including archive reference independence,
  boundary preservation, and guarded retirement of mixed game units.
- Progress output, whitespace, and shell syntax checks passed. The temporary
  `src/game/sdk` directory is gone, and unrelated changes are preserved.
