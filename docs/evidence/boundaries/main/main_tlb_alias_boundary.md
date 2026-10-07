# Main fixed TLB-alias working unit

Evidence kind: `structural_analysis`. The existing aligned range
`0x8120:0x8180` is one complete 96-byte handwritten CPU routine, retained as
original assembly rather than a portable-C candidate. The raw reference and
independently generated unsplit CPU index agree on the exact span. Every word
matches the checksum-validated US ROM and no conditional branch crosses its
endpoints. The ROM-range SHA-1 is `b773d6e0bf42f1f9a3b2346f8b76144da403b7c2`.

## Positive entry and ownership evidence

The exact linked SDK initialization object calls `0x8120` at ROM `0x22910`.
The routine saves CP0 EntryHi in `$t0`, selects TLB index 1 and page mask zero,
installs the `0xB8000000` alias with the paired EntryLo values, executes `tlbwi`,
restores EntryHi and returns through `$ra`. Its explicit CP0 operations and
required hazard-delay instructions establish the original-assembly requirement.
There are no internal alternate entries or local callees in this span.

This is a reviewed offset-named working unit, not an assertion of an original
filename or a stock SDK routine identity. It is kept separate from the sequence
player API beginning at `0x8180` and the preceding exception/control family.
Trailing no-ops through `0x817C` remain in the complete original 96-byte span.

## Reproducible registration and proof

```sh
./conker register-source-unit --overlay main --source src/main/init_8120.c \
  --register-members --us-start 0x8120 --us-end 0x8180 \
  --evidence-kind structural_analysis \
  --evidence-reference docs/evidence/boundaries/main/main_tlb_alias_boundary.md
./conker verify-original-asm func_80008120 \
  --reason "CP0 TLB setup with preserved hazard-delay instructions" \
  --evidence-reference docs/evidence/boundaries/main/main_tlb_alias_boundary.md
./conker verify-batch func_80008120
```

The proof compares independently generated raw words and the actual assembled
and linked full span against the owned ROM. Verification uses the
[restored pinned full-main toolchain](main_original_assembly_verification.md).
The source unit remains canonically `raw_asm`; its member is separately
`original_asm`. No C match, matched-byte increase or mixed main integration is
claimed. Canonical and raw-reference maps remain unchanged.

The clean batch passed full US ROM equality, fresh original-assembly proof,
1,070 tests (12 declared skips), metadata/progress and whitespace checks.
