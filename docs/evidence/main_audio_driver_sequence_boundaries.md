# US main audio-driver and sequence-state working families

Evidence kind: `structural_analysis`. Two complete working families add
65 raw entries and 19,936 bytes. Offset-derived source names do not assert
original Rare filenames. There are no C implementations, canonical-map changes,
archive promotions, data/BSS allocations or matching-byte credits in this batch.

## Inputs and range checks

The owned US ROM and decompressed game hashes, independent unsplit IDO index,
raw-word comparison, whole-main conditional-branch scan and normalized direct
call scan are the same as in
[the first main review](main_system_wrapper_boundaries.md). Both complete raw
member lists agree with the independent unsplit index, without missing spans
or unexplained entries; every instruction word matches the ROM. Outer bounds
are existing 16-byte-aligned map endpoints, with no crossing conditional branch.
The [legacy map](https://github.com/mkst/conker/blob/3adf229175c037c771f251f169f9dd80ca306924/conker/conker.us.yaml)
corroborates the same complete working intervals. Membership is independently
supported by the concrete constructor, callback and state relationships below,
not solely by that legacy map or by generic calls to shared SDK routines.

| Source | US ROM range | Entries | Bytes | Range SHA-1 |
| --- | --- | ---: | ---: | --- |
| `src/main/init_8F90.c` | `0x8F90:0xA420` | 15 | 5,264 | `fa2f672a9a4d08c995e1013c165b39a29b04cb64` |
| `src/main/init_B1B0.c` | `0xB1B0:0xEB00` | 50 | 14,672 | `ca12d22d927d29929fefe05350235511d033e7f2` |

## Audio driver, `0x8F90:0xA420`

The initializer constructs a bounded driver with owned callbacks and backing
state. At `0x8FC8:0x900C`, it installs the exact `0x10009980`, `0x10009FFC`,
`0x10009B2C`, `0x10009B90` and `0x10009B4C` callback addresses. These selections
account for members with no direct `jal` caller. The driver initializer also
constructs the `0x10009400` thread entry and passes it to the shared thread
constructor. The `0x93CC` shutdown entry uses the initializer's same
`0x8002AE40` initialized flag and `0x8003E3A0` thread object.

The `0x9980` callback explicitly returns `0x100097CC` at `0x99A8:0x99B0`.
The `0x9FFC` callback similarly returns `0x10009CBC` at `0xA02C:0xA030`.
Thus the DMA workers are owned indirectly rather than missing from the source
family. Callback `0x9B4C` directly invokes local `0x9BE4`. The thread at
`0x9400` calls task builder `0x95A0`; the latter calls local completion helper
`0x99BC` and cache-maintenance entry `0xA03C`, which calls `0xA348`.
These links, plus the explicitly installed callbacks, account for every member.
The DMA/cache paths access the same rings initialized around `0x800406B8`
and `0x80040AC8`, and the same mode/queue globals. No neighboring geometry
function beginning at `0xA420` is included.

Complete member starts (all prefixed `func_800`):
- `08F90`, `093CC`, `09400`, `095A0`, `097CC`
- `09980`, `099BC`, `09B2C`, `09B4C`, `09B90`
- `09BE4`, `09CBC`, `09FFC`, `0A03C`, `0A348`

## Sequence-state controller, `0xB1B0:0xEB00`

Forty-one of the fifty indexed entries form one connected component under
local direct calls. The nine remaining entries have explicit table or state
membership:

- `0xBC28` and `0xBCBC` are selected by the controller's callback table.
  ROM words at `0x2B20C` and `0x2B28C` contain `0x1000BC28` and `0x1000BCBC`.
  The controller at `0xD634:0xD664` loads the ID from its record, multiplies it
  by sixteen, loads the callback from `0x8002B07C + id * 16`, and invokes it.
  The two pointers occupy rows 25 and 33 of that exact indexed field.
- `0xCBA8` updates the same `0x800417B0` sequence-owner list used throughout
  the connected core, writing the linked records' fields at `+0x4E/+0x50`.
- `0xE134` classifies the same row flags at `0x8002B078 + id * 16`; the core
  reads that exact flags field at `0xCE2C:0xCE38`.
- `0xE75C` sets `0x8002B070`, the same value consumed by the connected
  `0xC7E8` path starting at `0xC810`.
- `0xE770`, `0xE7A0` and `0xE8C4` expose or modify the controller flags and
  state at `0x80041F04/0x80041F08/0x80041F0C`. The connected core reads and
  writes the same fields, including `0xB688:0xB6A4`, `0xB8F8:0xB944` and
  `0xB9A4:0xB9B8`.
- `0xE934` resets the same owner list and associated per-owner state at
  `0x800417B0`, `0x800417C0`, `0x80041880`, `0x80041890`, `0x800418A0`,
  `0x800418B0`, `0x800419A0`, `0x800419A8` and `0x80041E58` used by the core.

Together these relationships account for all fifty members. The table and
workspace references prove usage and membership; they do not establish the
original source object's allocation of either data or BSS. No table length is
inferred solely from the classifier's ID guard, and no adjacent callback family
beginning at `0xEB00` is absorbed into this range.

Complete member starts (all prefixed `func_800`):
- `0B1B0`, `0B1FC`, `0B294`, `0B2F4`, `0B3D4`
- `0B548`, `0B638`, `0B830`, `0B8B8`, `0BA18`
- `0BAFC`, `0BBE8`, `0BC28`, `0BCBC`, `0BF60`
- `0C350`, `0C530`, `0C7E8`, `0C934`, `0CA18`
- `0CAE4`, `0CBA8`, `0CBF0`, `0CC54`, `0CD40`
- `0CDA0`, `0CEAC`, `0D2F8`, `0D758`, `0D96C`
- `0DE1C`, `0DEC4`, `0DF68`, `0E054`, `0E0F8`
- `0E134`, `0E17C`, `0E2F4`, `0E40C`, `0E46C`
- `0E588`, `0E654`, `0E704`, `0E75C`, `0E770`
- `0E7A0`, `0E8C4`, `0E8F0`, `0E934`, `0EA94`

## Verification and safe replay

Register the two exact table rows with `./conker register-source-unit --overlay
main --register-members`, their listed source/bounds, `--evidence-kind
structural_analysis`, and this document as `--evidence-reference`. Preserve
concurrent game matching by replaying the registration transactions rather than
replacing complete inventory files.

Both units remain `raw_asm`; main mixed integration is unsupported. All 75
project-state tests and 13 segment-map tests pass, generated progress is current,
and whitespace checks pass. The canonical main and reference maps are unchanged.
No new full-main build is claimed; the cloud CPU image still lacks the RSP
extension required for that gate.
