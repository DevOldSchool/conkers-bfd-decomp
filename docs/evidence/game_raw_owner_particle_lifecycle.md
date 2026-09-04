# US owner-linked particle lifecycle

Evidence type: `structural_analysis`

Working source family `0x190770:0x191BE0` is a narrower core within the older
`0x18CD20:0x191BE0` navigation interval from local `mkst/conker` commit
`3adf229175c037c771f251f169f9dd80ca306924`, `conker/conker.us.yaml`
(combined base `0x2D4B0`). Original filenames and exact historical source
units remain unknown.

## Owner controller and retry path

Constructor `15190770` allocates type `0x20`, base size `0x300` plus custom
storage, copies a twelve-byte owner/identity descriptor to `+0x10`, and sets
the child list pointer `+0x24` to a `0x2D0`-byte array at `+0x30`.
The owned type row `8008BB28` selects local update `15190898`, event
`15191980`, and cleanup wrappers `15190840/1519086C`. Both cleanup
wrappers call local `15191400`, which processes that same child array.

If the owner's model is absent, the update creates a retry object through
`151491F4` with update `0xD`, event 8, and twelve bytes of owner state copied
to `+0x28` (`0x190F28:0x190F4C`). Owned slots `8008A51C/8008A8F8`
select local `151918BC/15191A84`. The retry checks owner identity and model
availability, calls `15190770` again, then releases itself. Both local event
paths validate and update the corresponding copied owner records.

Local helper `15191B8C`, called by the constructor with event `0xE`, broadcasts
through the generic retry engine and type list `800A8010 = [0x20]`, agreeing
exactly with the constructor's type.

## Particle creation, rendering and detachment

The controller creates children through `1513D524` at `0x190E50`, selecting
update `0xC` and draw `0xD`, and copies `0x60` bytes of custom state to
child `+0x110`. The wrapper passes these selectors to `1513D2F0`, which
stores them at `+0x70/+0x73`. Engine update dispatch uses `80089CB8`
(`0x13D04C/0x13D058`); owned slot `0xC`, `80089CE8`, is local
`15190F9C`. Engine draw dispatch uses `80089E1C`
(`0x13DC18/0x13DC24`); owned slot `0xD`, `80089E50`, is local
`1519108C`. Both consume the child's copied state and model coordinates.

The cleanup helper does more than free an array: at `0x191474:0x191494`
it calls `1513F680` to change each live child's update/step/draw selectors
to `0xD/0x12/0xD`, clears its motion and gives it an independent lifetime.
`1513F680` writes these fields directly at `+0x70/+0x71/+0x73`.
The resulting update slot `80089CEC` is local `15191520`; step slot
`80089DA8` is local `1519187C` (engine dispatch `0x13D084/0x13D090`).
This concrete detach transition connects those otherwise separate callbacks
to the owner lifecycle and accounts for every entry in the core.

## Validation

All 13 labels agree with the independent US index. The 5,232-byte range
matches owned US instructions, delay slots and padding. Both endpoints follow
complete returns; no decoded conditional branch crosses either endpoint in
either direction. No data, rodata or BSS ownership is assigned. Complete US
overlay byte equality gates integration. All members remain raw ASM, not C.

### `src/game/game_1BDC20.c`

Range `0x190770:0x191be0`; 13 entries, 5,232 bytes.
SHA-1: `1b37fa0e496b566116d2ed6a4b18f99c72825a76`.
debug: 10 correlations, 7 strong.
ects: 3 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15190770` | `0xd0` |
| `func_15190840` | `0x2c` |
| `func_1519086C` | `0x2c` |
| `func_15190898` | `0x704` |
| `func_15190F9C` | `0xf0` |
| `func_1519108C` | `0x374` |
| `func_15191400` | `0x120` |
| `func_15191520` | `0x35c` |
| `func_1519187C` | `0x40` |
| `func_151918BC` | `0xc4` |
| `func_15191980` | `0x104` |
| `func_15191A84` | `0x108` |
| `func_15191B8C` | `0x54` |

## Integration result

The first full US overlay gate passed: 2,072,880 identical bytes, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. This group is integrated
as mixed C/ASM, with all 13 entries remaining raw ASM.
