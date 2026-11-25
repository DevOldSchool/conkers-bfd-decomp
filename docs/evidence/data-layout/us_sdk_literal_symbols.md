# US SDK literal and VI symbol metadata

This batch compares existing SDK data reconstructed by the actual linked archive
members. It adds no new storage owner, changes no SDK source or runtime archive,
and does not adjust any byte denominator. The full suite, reconstructed-ROM
build and fresh native report passed on 2026-10-30.

## Anonymous literals

The following reviewed owners have relocation-free `.rodata` whose entire
compiled section, including padding, already matches the independently checked
US ROM. The report re-extracts the archive member and requires exact identity
with its candidate before creating a comparison copy.

| Overlay / archive | Member | Section bytes |
| --- | --- | ---: |
| GAME / libultrare | `perspective.o` | 16 |
| main / libultrare | `xldtob.o` | 96 |
| main / libultrare | `osc.o` | 16 |
| main / libultrare | `n_synthesizer.o` | 16 |
| main / libultra_2_0G_d | `cents2ratio.o` | 16 |
| main / libultrare | `n_drvrNew.o` | 32 |
| main / libultrare | `n_synfx.o` | 16 |
| main / libultrare | `n_auxbus.o` | 16 |
| main / libultrare | `n_resample2.o` | 16 |
| main / libultrare | `n_resample.o` | 16 |

The candidate's own HI16/LO16 relocations and LWC1/LDC1 loads establish 23
anonymous four- or eight-byte literals. Actual mapped section bases supply only
addresses for names. No reference object, ROM bytes or target symbol names are
read by the recognizer. Existing symbols, instruction/data bytes, relocations
and section headers are invariant; only new symbol/string entries are appended.

IDO sometimes schedules independent operations between LUI and the floating
load. The recognizer accepts a maximum 32-byte straight-line span, requires the
same base register at the load, and checks each intervening instruction against
a narrow whitelist. Writes to that register, control transfers and unknown
instructions fail closed. It does not follow branches or infer coefficient-array
extents from the next symbol. Tests mutate intervening integer/FPU-transfer
writes, calls, branches, indirect jumps and unsupported operations.

Canonical reference symbols record exact load widths. Subsequent zero section
alignment remains anonymous through the existing checked padding normalizer;
all alignment bytes remain in the assembled reference and ROM digest proof.
The previous decoder annotation remains supported with its original strict
whole-section guard. The expanded hook has an explicit reviewed owner list.

## Video-mode symbol extent

The three `vimode{ntsc,pal,mpal}lan1.o` objects describe `OSViMode` data at
`8002BED0`, `8002BE30` and `8002BE80`, respectively. Their physical `.data`
sections contain 80 bytes, but their ELF object symbols report 78. The last two
bytes belong to the nonzero `vIntr` word and cannot be discarded as padding.
The existing independent reference correctly retains all 80 bytes.

The report compiles a layout probe using the pinned compiler and current SDK
headers. It requires the following exact results:

- `sizeof(OSViMode) = 80`;
- `offsetof(OSViMode, fldRegs) = 40`;
- `sizeof(fldRegs[0]) = 20`;
- `offsetof(OSViMode, fldRegs[1].vIntr) = 76`;
- `sizeof(fldRegs[1].vIntr) = 4`.

Only these three named SDK members qualify. Each candidate must equal the
actual archive member, contain exactly the expected data object with no
relocations or extra allocated storage, and pass the complete 80-byte ROM
payload hash. Only then may a comparison copy correct its symbol size from
78 to 80. An already-correct 80-byte symbol is accepted unchanged. All other
symbol fields, headers, section bytes, relocations and file bytes remain
identical. The runtime archive and original candidate are never rewritten.

Tests cover the exact metadata-only change, nonzero final word, idempotence,
incorrect ABI layouts, symbols, sizes, offsets, stale candidates and missing
whole-section proofs. A real pinned-compiler test verifies the header layout.

## Accepted validation

The isolated native report matches all 496 bytes across the 13 owners above.
Twenty-six single-field mutations (23 literals and the final word of each VI
record) each lose a perfect native data match. The full Docker suite passes
2,947 tests with eight expected skips (176.267 seconds). The rebuilt-asset US
ROM is byte-identical across all 67,108,864 bytes (48 seconds including setup),
with SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`.

These checks use base commit `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7` plus
the uncommitted workspace changes. The fresh native report and preservation
audits accept **496 additional matching bytes**, bringing Data to
**63,123,584 / 65,120,512 (96.93349%)**, with **1,996,928 bytes remaining**.
Only the 13 intended units change. All 26,809 prior editable asset-input hashes
and all 13 actual SDK archive members are preserved. Code/function metrics,
complete data (63,079,392 bytes), unit counts and denominators are unchanged.
The completed-data count is independently proven linked storage; this batch
resolves comparison metadata and claims no new storage completion.

Fresh preparation took 289.0 seconds and native comparison/validation 24.7
seconds, with zero compile errors. Progress and whitespace checks pass; the
validated snapshot is current. Full metrics and hashes are recorded in
[the acceptance record](us_sdk_literal_symbols.json).

Report SHA-256:
`f991e363793978098b82f84ea93285e6984d70d9a6c39ba6e8ab1b4fb59e272b`.
Source fingerprint:
`f933c206bdb6dbf7293a6f782d3f78358fcdc10f43248bf9857a7c07f5147a5f`.
