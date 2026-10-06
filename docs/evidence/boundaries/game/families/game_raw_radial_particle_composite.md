# Raw radial and particle composite family

Reviewed US game range `0xCBF80:0xCCD90`, working source `src/game/game_F9430.c`: six raw entries, 3,600 bytes. This is a structural source-family hypothesis; the original filename and exact historical compilation-unit boundary remain unknown. No C implementation or instruction-match claim is made.

## Membership evidence

`func_150CBF80` is the composite factory. At `0xCC3E4` it passes particle step selector `0x18` to `func_1513D668`; that wrapper forwards it through `func_1513D594` to `func_1513D2F0`, which stores it at object byte `0x71` (`0x13D3A4`). The particle step table at `0x80089D60` selects the owned-ROM pointer at `0x80089DC0`, targeting local `func_150CC638`. The factory copies eight custom bytes to child offset `0x128` at `0xCC428:0xCC438`, used by this callback.

The same factory places selectors `0x11` and `0x12` at argument stack offset `0x1C` (`0xCC46C`, `0xCC5B8`) before calling `func_1514C678`. Its radial dispatcher reads that argument and indexes `0x8008AA00`; owned-ROM slots `0x8008AA44` and `0x8008AA48` point to local `func_150CC6B8` and `func_150CCA7C`.

`func_150CC6B8` constructs a child through `func_15130374`: descriptor base is stack `0x34`, selector 8 is written at stack `0x96`, becoming object update byte `0x72`. Table `0x80089760` slot `0x80089780` targets local `func_150CC8D4`. `func_150CCA7C` constructs its child through `func_15132A4C`: descriptor base is stack `0x28`, selector 3 at stack `0x89` becomes object byte `0x71`; table `0x800898B0` slot `0x800898BC` targets local `func_150CCCB4`. Thus both burst callbacks and their child updates belong to the factory family through actual selector dispatch.

The adjacent helper at `0xCCD90` remains external to this range. Common allocator/particle calls alone are not the membership basis.

## Boundary checks

Both existing raw boundaries are 16-byte aligned. Every raw instruction word was compared with the owned US image, all indexed entry spans exactly cover the range, and a whole-image conditional-branch scan found no crossing edges. Independent function CSV membership and beta correlations are recorded below; beta similarity supports entry identity rather than proving a historical source boundary.

### `src/game/game_F9430.c`

Range `0xcbf80:0xccd90`; 6 entries, 3,600 bytes.
SHA-1: `fc8bd1873bd421bf3d1ff292d62b200ebc8231d5`.
debug: 6 correlations, 3 strong.
ects: 3 correlations, 1 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150CBF80` | `0x6b8` |
| `func_150CC638` | `0x80` |
| `func_150CC6B8` | `0x21c` |
| `func_150CC8D4` | `0x1a8` |
| `func_150CCA7C` | `0x238` |
| `func_150CCCB4` | `0xdc` |

## Integration result

Integrated on the first attempt. The complete US game overlay remains byte-identical: 2,072,880 bytes, SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All six entries remain raw ASM; no C matches were added.
