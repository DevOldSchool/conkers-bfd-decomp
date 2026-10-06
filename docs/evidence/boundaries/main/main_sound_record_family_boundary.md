# US main sound-record callback and handle family

Evidence kind: `structural_analysis`. The reviewed working range
`0xEB00:0x11FA0` contains 54 complete indexed entries and 13,472 bytes,
registered as `src/main/init_EB00.c`. The name is offset-derived, not a
recovered original filename. All implementations remain raw assembly; neither
canonical nor reference map changes and no C-match credit is added.

## Range proof

The checksum-validated US ROM, unsplit spimdisasm 1.33.0 IDO index, split raw
assembly and branch checks are the same as in
[the first main batch](main_system_wrapper_boundaries.md). All raw words equal
the ROM, and both indexes agree on the complete ordered member spans. The
aligned outer endpoints have no crossing conditional branches in either
direction. The range SHA-1 is `f88236fceb6a2ba4022ef02e6c085ebdf38859d1`.
The independent [legacy source map](https://github.com/mkst/conker/blob/3adf229175c037c771f251f169f9dd80ca306924/conker/conker.us.yaml)
corroborates this same working interval; it is not the sole ownership evidence.

## Complete family relationships

Forty of the entries form a connected component under direct local calls.
The remaining fourteen are accounted for by specific callback arguments and
shared record/handle state rather than loose similarity:

- `0xEB00` and `0xEBC4` are real callback entries supplied to local record
  constructor `0xFA64` by game code. Game offsets `0x111A0:0x111A4` construct
  `0x1000EB00`, store it in the outgoing callback argument at `0x111C8`, and
  call `0x1000FA64` at `0x111E8`. Similarly, `0x16F80C:0x16F810` constructs
  `0x1000EBC4` before the constructor call at `0x16F84C`. Those referenced
  game instruction words were also compared directly with the owned,
  checksum-validated decompressed overlay.
- `0xF1A8`, `0xF248` and `0x11E88` form the initialization/reset component.
  The first initializes the same handle storage at `0x800425E0`, active-record
  count at `0x80042760`, and mode flags at `0x80041F60/0x80041F61` used by
  the connected sound-record core. `0xF248` directly calls it at `0xF258`.
- `0xF4D8` traverses handles from `0x800425E0` through `0x800426A0`, testing
  the same masked sound IDs as the core's handle operations.
- `0xF568` and `0x11EB8` form a selector/wrapper component. The wrapper
  invokes `0xF568` at `0x11F7C`; the selector reads state through
  `0x80041F5C`, initialized by `0xF248`, to select a sound identifier.
  The wrapper's constants do not create a separate data-ownership claim.
- `0x1001C` and `0x100E0` both walk the core's `0x80041FE0` sound-record array
  using its `0x80042760` active count and `0x30` stride. The first updates
  matching records' pitch/parameter fields; the second updates their positional
  fields at `+0x14/+0x18/+0x1C`. The main update path at
  `0x11CFC:0x11D28` references that same exact array/count pair.
- `0x1123C` and `0x112BC` are a connected handle-operation pair. The former
  resolves a handle against `0x800425E0`, validates its identifier and calls
  the latter; the latter uses the family's `0x80041F10/0x80041F50` state.
- `0x1147C` reads the same handle entries: it derives a twelve-byte stride
  from the low four identifier bits, checks the stored identifier, and returns
  the masked field at `+4`.
- `0x11E94` controls the mode flag at `0x80041F61`, read by the connected
  update path at `0x11BC8:0x11BD4`, `0x11DB8:0x11DBC`, and `0x11E68:0x11E6C`.

The connected core also explicitly constructs callbacks at `0xECCC`, `0xEDA0`
and `0xEE70`; these are already included in the same complete member list.
This proves a bounded working sound-record family without asserting that the
original compiler emitted it as one historical object. The adjacent state
controller starting at `0x11FA0` remains a separate reviewed working unit.
References establish use, not original data/rodata/BSS allocation.

## Complete member list

All starts below are prefixed `func_800`:
- `0EB00`, `0EBC4`, `0EC24`, `0ECCC`, `0EDA0`
- `0EE70`, `0EF40`, `0EFB4`, `0F1A8`, `0F248`
- `0F3D0`, `0F44C`, `0F4D8`, `0F568`, `0F6B8`
- `0F85C`, `0F91C`, `0F9D4`, `0FA64`, `0FC18`
- `0FD38`, `0FDF4`, `0FE88`, `0FEF0`, `0FF90`
- `1001C`, `100E0`, `10154`, `10344`, `10558`
- `10630`, `10720`, `107F8`, `10894`, `1091C`
- `109D0`, `10A3C`, `10AA8`, `10BE8`, `10E78`
- `10F30`, `10F88`, `10FFC`, `111C8`, `1123C`
- `112BC`, `11310`, `1147C`, `114D0`, `11624`
- `11BB8`, `11E88`, `11E94`, `11EB8`

## Registration and verification

Replay through `./conker register-source-unit --overlay main --register-members
--source src/main/init_EB00.c --us-start 0xEB00 --us-end 0x11FA0
--evidence-kind structural_analysis`, with this document as the evidence
reference. Do not replace complete inventories when reconciling concurrent work.

The unit remains `raw_asm`. All 75 project-state tests and 13 segment-map tests
pass; generated progress is current and whitespace checks pass. Canonical and
reference maps are unchanged. No full main build is claimed: the cloud CPU
image still lacks its RSP extension, and main mixed integration is unsupported.

A full repository test run at this checkpoint passes: 1,067 tests, including
12 declared skips. This is a test-suite result, not a ROM-build result.
