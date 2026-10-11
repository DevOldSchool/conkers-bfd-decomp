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

Upstream objdiff 3.8.1 bounds data comparison at the last named symbol. IDO's
anonymous switch table and trailing double therefore require the pinned local
`data_diff_full_section` patch described in `toolchain/patches/README.md`.
The debugger reference disassembly also receives the original rodata context,
retaining real switch destinations. Equivalent relocated destinations are checked
without inventing candidate symbols. The patched native report credits all 464
bytes only when anonymous bytes, full extents and relocations agree. Synthetic
negative cases cover changed bytes, destinations, missing/extra relocations and
shorter/longer storage.

The [UI data reconstruction](us_debugger_data_reconstruction.md) supplies the
other 4,256 bytes. The [TLB routine](us_debugger_tlb.md) remains verified original
assembly. Its maintained source can earn native matching and linked completion
without changing C-only inventory credit.
