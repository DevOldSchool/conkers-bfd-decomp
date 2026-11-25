# US SDK runtime pointer comparison metadata

The full suite, rebuilt-asset ROM, native report and preservation audit passed
on 2026-10-30. All 1,712 bytes below match natively; 256 envelope bytes were
already matched, so this batch adds 1,456 matching bytes.
No SDK source, archive, runtime input, storage owner or denominator changes.

| SDK member | Data | Read-only data | Bounded switch entries |
| --- | ---: | ---: | ---: |
| `xprintf.o` | 80 | 256 | 52 |
| `n_csplayer.o` | 400 | 592 | 27 + 21 + 97 |
| `n_reverb.o` | 0 | 48 | 8 |
| `n_env.o` | 256 | 80 | 17 |

## Independent source and instruction evidence

The existing [formatter reconstruction](../libraries/libultrare_us_xprintf_reconstruction.md)
and [sequence-engine reconstruction](../libraries/libultrare_us_sequence_engine_reconstruction.md)
record the exact object boundaries and main execution mapping. Main links at
`0x80000000` and executes through `0x10000000`; the checked library preparer
rebases compiler-generated code-pointer addends by `-0x70000000`. The report's
main data-analysis context now uses that runtime mapping. Independent code
reference objects keep their original linker coordinates. Every assembled and
grouped reference image still must reproduce the complete original ROM span.

The formatter source declares two 33-byte padding strings, a four-byte qualifier
string, six flag bytes and six 32-bit masks. Its switch at candidate code offset
`0x6A8` is bounded to 52 entries (the recognizer independently checks the actual
instruction locations, registers and bound). The canonical symbols record
source extents, including terminators. Alignment stays present and anonymous.

The sequence source declares `__n_cspControls[93]` and
`__n_cspHighControls[4]`, owning 372 and 16 bytes, followed by 12 alignment bytes.
Eighteen nonnull callbacks use existing Makefile aliases derived from their
actual linked function definitions minus `0x70000000`. The reference names
those same original pointer values; the candidate callback relocations remain
unchanged. Its three switch loads occur at object offsets `0x2BC`, `0xD90` and
`0xF40`, with explicit unsigned bounds 27, 21 and 97. Their exact extents are
108, 84 and 388 bytes, followed by 12 alignment bytes.

Reverb and envelope switches load at offsets `0x8B8` and `0xEC`, with bounds
8 and 17. Three reverb floats and one envelope float have four-byte widths
proved by LWC1 references. The ordinary compiler constants and padding are
preserved. The sound player's anonymous strings remain outside this batch.

The dispatch recognizer supports the two complete IDO shapes: shift in the
branch delay slot, or a no-op delay slot followed by the shift. It checks the
unsigned guard, out-of-range branch, index scaling, LUI/add/load register chain,
indirect jump and empty jump delay slot. Each bounded entry must relocate to
aligned code within the same object. Adjacent tables need independently
referenced starts, and all discovered spans remain nonoverlapping.

## Comparison copies and independent guards

Only the four explicitly listed main SDK owners qualify. Each must equal the
actual archive member and have complete reviewed section placements. Analysis
reverses the known staging bias in memory only, then derives all table bounds
from candidate instructions. The analysis changes must cover exactly the 222
known code-pointer words and no other bytes. No reference names, reference
objects or ROM data participate in discovering candidate table extents.

The comparison copy adds data symbols and absolute runtime destination labels,
then represents each table pointer as a zero addend relocated to that absolute
label. This is specific to the independently verified actual placement. A
separate verifier re-derives the allowed changes from the original object,
checks every effective pointer value, and rejects any change to original
symbols, other sections, headers or unrelated relocations. It does not trust
a change list produced by the transform. Existing callback relocations remain
unchanged. Generated `.L..._main_data` reference labels receive their equivalent
address-only spelling in both assembly and linker definitions.

Both the raw archive member and comparison copy are separately linked at the
actual text/data/BSS placements. Every allocated code/data byte must agree with
the runtime ELF; all data hashes must also agree with independent ROM spans,
and the entire code span is checked against the checksum-validated original
main CPU image. BSS anchors and extents must agree. Unused undefined SDK
header declarations need no linker binding; referenced externals require one
unambiguous actual definition. Archives and the runtime ELF are retained as
hashed validation inputs. Existing completion flags are preserved.

## Tests

ROM-free fixtures exercise adjacent tables and no-op delay slots, exact pointer
values and real linker equivalence, including an owned BSS variable. Mutations
cover bounds, registers, delay slots, code, addends, relocation targets, absolute
symbol values, runtime bytes and incorrect placements. Hook tests reject stale
archive copies, missing ownership, wrong extents and false ROM hashes.

## Accepted validation

The implemented canonical hook, including original-ROM and BSS guards, passes
the four-owner native pilot at 1,712 / 1,712 bytes. All 244 single-field
mutations (222 switch pointers, 18 callbacks and four floats) lose a perfect
native match and are separately rejected by the semantic verifier.

The full Docker suite passes 2,954 tests with eight expected skips (176.672
seconds). `./conker build --assets` reproduces the complete 67,108,864-byte US
ROM in 48 seconds including setup, retaining SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. These checks use base commit
`38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7` plus the uncommitted workspace
changes. The final native report and preservation audits accept
**63,125,040 / 65,120,512 matching bytes (96.93572%)**, with
**1,995,472 bytes remaining**. Only the four intended unit metrics change.
All 26,809 prior editable asset-input hashes and four original archive members
are preserved. Code/function metrics, completion totals, unit counts and
denominators are unchanged. This is matching metadata work, with no new
linked-storage completion claimed.

Preparation took 339.4 seconds and native comparison/validation 26.3 seconds,
with zero compile errors. Progress and whitespace checks pass, and the final
snapshot is current. See [the acceptance record](us_sdk_pointer_symbols.json).

Report SHA-256:
`4c2bf329ba86e54d16c2f8d10d2aa98fd9b126a123e423a066c1c217cb001a9c`.
Source fingerprint:
`7c66f9ff469b3cde1cbf7fd480257d2bf8db204c59031811da5b51c9de4021b5`.
