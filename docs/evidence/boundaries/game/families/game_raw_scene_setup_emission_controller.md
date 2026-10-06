# US scene setup and emission-controller families

Evidence kind: `structural_analysis`. Existing raw navigation ranges are used as working source families, with generic offset filenames. Original filenames and precise historical compilation units remain unknown.

## Three scene setup ranges

- `0xF290:0xF9D0`: setup callback `1500F40C`, owned pointer `80082DB0`, directly calls local helper `1500F378` twice and `1500F290` four times before placing several objects. Every entry participates in this setup routine.
- `0xF9D0:0xFE30`: setup callback `1500FA64`, owned pointer `80082DBC`, directly calls local timer/object helper `1500F9D0` five times and initializes scene-owned state around `800DCD20`. Both entries are one setup/helper pair.
- `0xFE30:0x10110`: setup callback `1500FFCC`, owned pointer `80082DC0`, directly calls local `1500FE30` and `1500FF9C`. The former allocates and initializes the ten-record array at `800BE4E0` then invokes its separately mapped rate helper; the latter supplies the setup's resource preparation. The different setup callback identities and helper graphs support keeping these three existing ranges separate.

## Indexed controller: `0x1827D0:0x183290`

`151827D0` updates controller state `800DDE50/54/60` and the 24-byte parameter records beginning at `8008D050`; it calls local `15182FDC`. Callback `15182C5C` consumes that same indexed state and calls local `15182F58`. The latter computes/clamps a value using the index at `800DDE54` and parameter at `8008D058`. `15182FDC` also calls that helper and uses the same record and owner state. The connected call graph and exact shared records account for all four entries.

## Emission controller and child: `0x1B9690:0x1B9F00`

`151B9BF0` creates type 7, size `0x2C`, initializes its `+0x14:+0x2A` parameters and stores owner state at `+0x10`. The owned type-7 update slot `8008B614` points to local `151B9CB0`, which calls local child factory `151B9690` twice.

The child factory creates a type-5 element through `15167D84`, copying its descriptor from stack `0x58` to object `+0x10`. It writes zero at stack `0x77`, which becomes the callback selector at object `+0x2F`. The type-5 update dispatcher at `0x167E80:0x167EAC` reads this selector and indexes table `8008C9C8`; slot zero is local `151B9964`. This ties the fourth entry to the created child rather than merely to the same generic allocation engine.

## Checks

All ranges retain existing 16-byte-aligned endpoints. Every raw word matches the owned US image, entry spans cover each range, and whole-image conditional-branch scanning finds no crossing edges. The independent CSV membership check and beta correlations are listed below. All members remain generated ASM and no new C matches are claimed.

### `src/game/game_3C740.c`

Range `0xf290:0xf9d0`; 3 entries, 1,856 bytes.
SHA-1: `0507c72730536cfed4abeb298476235a76ae7f1e`.
debug: 3 correlations, 2 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1500F290` | `0xe8` |
| `func_1500F378` | `0x94` |
| `func_1500F40C` | `0x5c4` |

### `src/game/game_3CE80.c`

Range `0xf9d0:0xfe30`; 2 entries, 1,120 bytes.
SHA-1: `eaeb8b136e161c6b0555cf5c09f72d001322de0f`.
debug: 2 correlations, 1 strong.
ects: 2 correlations, 1 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1500F9D0` | `0x94` |
| `func_1500FA64` | `0x3cc` |

### `src/game/game_3D2E0.c`

Range `0xfe30:0x10110`; 3 entries, 736 bytes.
SHA-1: `83e80972730fa2b8f507d94d8a9a16bf83457f18`.
debug: 2 correlations, 2 strong.
ects: 1 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1500FE30` | `0x16c` |
| `func_1500FF9C` | `0x30` |
| `func_1500FFCC` | `0x144` |

### `src/game/game_1AFC80.c`

Range `0x1827d0:0x183290`; 4 entries, 2,752 bytes.
SHA-1: `d5563ebb71a3912d37c960ba38f11062ff60665d`.
debug: 2 correlations, 2 strong.
ects: 2 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151827D0` | `0x48c` |
| `func_15182C5C` | `0x2fc` |
| `func_15182F58` | `0x84` |
| `func_15182FDC` | `0x2b4` |

### `src/game/game_1E6B40.c`

Range `0x1b9690:0x1b9f00`; 4 entries, 2,160 bytes.
SHA-1: `22cbc8fd0f5188a539eafaf3fa3845875f838ad4`.
debug: 2 correlations, 2 strong.
ects: 2 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151B9690` | `0x2d4` |
| `func_151B9964` | `0x28c` |
| `func_151B9BF0` | `0xc0` |
| `func_151B9CB0` | `0x250` |

## Integration result

All five reviewed source units integrated as raw ASM wrappers. The complete 2,072,880-byte US game overlay is byte-identical (SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`). No C match is claimed.
