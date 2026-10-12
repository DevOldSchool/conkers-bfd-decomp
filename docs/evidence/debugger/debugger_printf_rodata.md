# Debugger formatter source-data integration

The formatter source unit now supplies both of its initialized sections to the
actual US ROM link. The loader-proven original image and independently assembled
references remain the comparison inputs.

| Source section | Loaded range | ROM range | Bytes |
| --- | --- | --- | ---: |
| `.data` | `0x16003C70–0x16003CE0` | `0x1A26F8–0x1A2768` | 112 |
| `.rodata` | `0x16004800–0x16004960` | `0x1A3288–0x1A33E8` | 352 |

The [source-unit review](us_debugger_source_units.md) establishes these blocks.
The [access map](us_debugger_data_objects.json) records their independently
checksum-validated contents and consumers. Definitions in
`src/done/debugger/debugger_1AD0.c` reconstruct padding strings, integer digits,
format qualifiers/flags, flag masks, floating powers of ten and special-value
strings. `config/symbols/us.txt` records their payload sizes; ordinary compiler
alignment remains anonymous and is still included in byte comparisons.

The Putfld switch naturally emits its 52 relocated cases at
`0x1600487C–0x1600494C` (208 bytes, SHA-1
`d1df6f79b540cfcccfc89d76dd0783f081156d03`). The expression
`(ldval - lo) * 1e8` naturally emits the following double at `0x16004950`.
The original table gap and terminal alignment are produced by IDO. No candidate
section is resized and no artificial table or literal symbol is added.

`config/profiles/us.yaml` owns both allocated placements. The old INFO selector
is removed; the generated `.debugger` output consumes the actual C object's
sections. `verify_debugger_rodata.py` checks all 14,064 code bytes and 4,720 data
bytes in that allocated image against the checked US ROM. The ordinary full-ROM
comparison remains required. The reporter rebuilds the runtime image and compares
fresh candidate storage, symbols and relocations to the actual linker input before
allowing either section to be considered for completion. Native matching remains
a separate gate, and the existing per-unit completion downgrade still applies.

## Native anonymous data comparison

The unmodified objdiff release performs its native symbol-based comparison.
Anonymous switch tables and trailing literals can leave native data matching
below the independently verified allocated byte count. The debugger reference
still includes original rodata context for real switch destinations. Full ROM
verification checks all 464 bytes; native percentages are reported unchanged.

The [UI data reconstruction](us_debugger_data_reconstruction.md) supplies the
other 4,256 bytes. The [TLB routine](us_debugger_tlb.md) remains verified original
assembly. Its maintained source can earn native matching and linked completion
without changing C-only inventory credit.

## Remaining native comparison blocker

The official objdiff v3.8.1 data comparison bounds the displayed/compared byte
range by the last non-hidden, non-section symbol. See upstream
[`diff_data_section`](https://github.com/encounter/objdiff/blob/v3.8.1/objdiff-core/src/diff/data.rs).
The actual formatter candidate has 352 `.rodata` bytes, but its last ELF data
symbol ends at offset `0x7A` (the string at `0x16004878`). The independently
assembled reference's last payload ends at `0x158` (the double at `0x16004950`).
IDO emits the intervening switch table and double without ELF object symbols.
They remain in the actual candidate section and in the verified runtime image.
The stock comparison therefore treats their reference bytes as unmatched; this
is not evidence that those allocated runtime bytes differ.

Two bounded, ignored source experiments tested an explicit C definition for the
existing `1e8` literal. A named scalar moved storage into `.data`; a one-element
constant array moved the double before the switch table and changed instruction
scheduling. Both failed exact object comparison and were discarded. The canonical
formatter source and compiler settings remain unchanged. No hand-written switch
assembly, invented comparison symbol, shortened section or relaxed completion
rule was adopted. The native 100% linked goal remains unmet until the formatter
can satisfy the stock comparison without compromising its independent match.

The same saved formatter objects were also compared with the official v3.8.2
macOS ARM64 release, downloaded separately and checked against its published
SHA-256 `767c67e13b7b5e6ca545e7d2235e47c7bceac07d47a52776f74a52914cb4085a`.
It produced the same 34.52381% section comparison for `.rodata`. The repository
pin remains v3.8.1; upgrading to the tested release does not resolve this blocker.
