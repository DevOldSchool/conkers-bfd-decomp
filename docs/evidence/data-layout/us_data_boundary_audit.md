# US initialized-data boundary audit

Reproduce with `./conker objdiff data-audit`. The command validates the US ROM
size and SHA-1, reads the canonical placements, and writes the evidence-only
partition to ignored `build/us/data-boundaries/audit.json`. It needs host Python
and the configured ROM, but neither Docker nor objdiff installation. It does not
change source-unit registration, linker maps, matching records or report credit.

## Current audit

Validated against main `e7d4eb3` and US ROM SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a` on 2026-10-09.
All ends are exclusive; addresses below are loaded virtual addresses.

| Image | Interval | Loaded bytes | Existing mapped bytes | Unassigned bytes |
| --- | --- | ---: | ---: | ---: |
| Main | `0x8002AAD0–0x8002C960` | 7,824 | 3,152 | 4,672 |
| Game | `0x80082B20–0x800B0DC0` | 189,088 | 26,284 | 162,804 |
| Debugger | `0x160036F0–0x16004960` | 4,720 | 208 | 4,512 |
| Total | | 201,632 | 29,644 | 171,988 |

Mapped bytes describe placement evidence, not newly verified C data matches or
recovered original object boundaries. SDK ranges are the intervals reserved by
canonical mappings; their current archive sections have not been rebuilt or
compared by this audit. External pools can belong to provisional C collections.

The partition has 39 main mappings (35 SDK placements, two private sections and
two external pools), 48 game payload mappings and one debugger payload mapping.
Every unassigned byte remains visible, including zero-filled bytes. Each range
has a payload SHA-256 and each image reconciles mapped plus unassigned bytes
with its complete loaded size. BSS, RSP payloads and other ROM assets are excluded.

Image SHA-256 values:

- Main: `567ddfce08da889c8be296589c03eeab2df3de3ec6739aa84da26ff265c69499`
- Game: `0bbc00e1adfac5ffe6117f5be9c941575f87b341a77d808004603ac1cb87c670`
- Debugger: `31f6bf74dc652e614d5c0c9f9aca552773a3967a2ede4e6a6a09d37f7af6ad95`

## Boundary sources and findings

Main's initialized interval starts after the final RSP code payload and ends
before RSP data. Both endpoints agree with `config/profiles/us.yaml`, and all
RSP payload MD5s are checked against the validated ROM. Main SDK section
placements come from that canonical map, preserving the input section type even
when linker order places `.rodata` among `.data`. Private storage comes from
`config/main/private-data.json`, including its ownership evidence and payload
hashes. External tables come from `config/main/us-rodata.ld`.

Game data comes from the archive parser's complete decompressed data stream,
using `config/rzip_layouts.json`. The separate compressed code stream and archive
padding are excluded. Placements come from `config/game/us-rodata.ld` and
`config/game/us-sdk.ld`. `NOLOAD` alone does not identify BSS: several SDK
initialized sections use it to bind relocations into the preserved data stream.
The two actual `.bss` bindings are listed separately in `excluded_bindings`.

The game SDK controller's `.data` binds to main `[0x8002BE10,0x8002BE20)`.
It is recorded as a shared placement on main's existing controller range;
it creates no second game-data allocation or denominator credit. Partial
cross-image overlap and placements outside loaded images fail the audit.

Explicit linker payload extents take precedence over compiler section size.
For example, the [constructor pool](game_981e0_constructor_literal_pool.md)
owns `[0x80099DAC,0x80099E98)` (236 bytes). Its four compiler-alignment bytes
are not assigned to the pool: `0x80099E98` is an independently referenced ROM
constant. The audit retains that following range as unassigned. Other explicit
payload/padding exceptions receive the same treatment.

Debugger uses the [loader-proven image](../debugger/us_debugger_overlay.md) through
`rom_span.debugger_image`. Only the [208-byte formatter table](../debugger/debugger_printf_rodata.md)
is presently mapped. The detailed debugger access map is useful research
input, but observed access widths, strings and zero runs do not establish
original section or object ownership and are not promoted to mappings.

## Published report integration

`./conker objdiff report` includes all three initialized-data images, the
rebuilt font and [6,175 reviewed textures](us_texture_reconstruction.md) in the artifact used by decomp.dev. See the
[report scope and validation rules](../../objdiff.md#scope). Ownership is recorded in `config/data/us.json` by overlay, hexadecimal address
and input section. It contains no duplicate boundaries: those come from the
canonical YAML, private-data configuration and linker placements. The audit
rejects missing, extra or conflicting owners before use. Independent target
helpers live in `scripts/objdiff_data_targets.py`; generation, native count
validation and completion policy live in `scripts/objdiff_report.py`.

Unassigned loaded bytes remain in the denominator with no base or matching
credit. Main's largest unresolved range is `0x8002AB50–0x8002B9D0` (3,712 bytes);
GAME has 38 unassigned intervals. Accesses and zero runs alone do not establish
ownership for an entire surrounding range.

## Main data references

Splat receives the independently validated original main CPU code as analysis
context and the complete main initialized-data image. The RSP interval remains
a separate binary segment. Every audited range gets an assembled data target,
including all eight unassigned ranges. References use the canonical symbol names
and payload sizes. Proven unreferenced zero padding after explicitly sized
payloads stays anonymous; section contents and relocations remain intact. See
[SDK symbol evidence](us_sdk_data_symbols.md). The data-only link asserts each extent and
must reproduce all 7,824 original bytes, including zeros and padding.

Main's execution aliases can cause splat to emit jump labels without undefined
address assignments. The reference builder derives link-only `PROVIDE` definitions from
bare symbolic `.word` rows whose offset, virtual address and encoded value
match the validated ROM. It records those definitions separately and does not
modify object symbols, add candidate-derived relocations or assign addresses
from a candidate. The linked-image comparison remains mandatory.

Candidates are built from all 35 mapped SDK sections and four C source mappings.
`GLOBAL_ASM` placeholders are removed in generated C copies; deferred code stays
disabled. Complete base objects retain other sections and relocation metadata.
Missing or wrong-size candidate sections retain their reference denominator and
make the command fail. Targets without candidates never receive a base object,
even if a stale object exists from an earlier run. Loaded data receives matching credit from native objdiff; placement alone
does not establish completed-source ownership.

Native data matching depends on symbols and relocations as well as bytes.
For example, the AI flag's 16-byte initialized section is byte-identical but its
candidate lacks an ordinary data symbol. Reference extents follow explicit
declarations; candidate symbols are never resized or fabricated to eliminate
these differences. Literal equality is not
substituted for native credit.

## Asset boundaries are the larger next coverage source

The existing extractors already supply asset boundaries. Refresh the raw
storage inventory without writing decoded payloads:

```sh
./conker rzip-extract --profile us --manifest-only \
  --output build/us/data-boundaries/assets
```

The fresh US manifest on 2026-10-08 contains these disjoint payload intervals:

| Collection | Entries | Stored ROM bytes | Decoded bytes |
| --- | ---: | ---: | ---: |
| Flat RZIP | 7,760 | 9,494,881 | 16,305,205 |
| Indexed assets | 2,518 | 55,386,337 | 60,507,058 |
| Total | 10,278 | 64,881,218 | 76,812,263 |

These counts were recomputed from each manifest entry's `rom_start`, `rom_end`
and `decoded_size`, with a sorted overlap check across both collections.
9,430 entries are compressed. The table does not include the separate 144-byte
raw block, bank/index metadata, inter-entry gaps or other ROM regions. It is
storage coverage, not an asset reconstruction percentage.

Use these established coordinates as the physical storage layer, then attach
model, texture, audio and other semantic inventories through their existing
bank/entry identifiers. A texture inside a decoded model is a child range,
not another allocation of the compressed ROM bytes. Multiple consumers of one
payload likewise do not multiply the denominator. Keep stored ROM intervals,
decoded container intervals, metadata/gaps and independently verified rebuild
status distinct. The detailed [RZIP and asset guide](../../rzip-assets.md)
links the format-specific extractors and round-trip verifiers.

This supplies a much larger boundary foundation than inferring asset ownership
from C files. Asset reconstruction can be reported alongside code and initialized
data once unique backing ranges and rebuild criteria are reconciled; extraction
alone must not be counted as reconstructed source.


## Debugger data references

The report covers the entire 4,720-byte loader-proven debugger data image,
using the existing `config/debugger/us-rodata.ld` mapping.

| Loaded range | Bytes | Report role |
| --- | ---: | --- |
| `0x160036F0–0x1600487C` | 4,492 | Unassigned reference; no base or matching credit |
| `0x1600487C–0x1600494C` | 208 | Reviewed formatter table; fresh C candidate |
| `0x1600494C–0x16004960` | 20 | Unassigned reference; no base or matching credit |

The independently disassembled input combines the loader-validated debugger
code and data at their loaded addresses. The complete code supplies analysis
context; only the three data target objects enter the data report. Original
pointer definitions are checked against the image's byte offsets and loaded
origin, without borrowing candidate symbols or relocation information.

Data ranges can end or begin inside a compiler-aligned section. References use
GNU as `-no-pad-sections` to avoid adding trailing bytes beyond a range and
`.align 0` to disable implicit directive alignment. For example, the last range
starts at `0x1600494C`: its double at `0x16004950` belongs at object offset four,
not eight. Original symbol extents and relocations stay intact. Every target
section still has to equal its audited extent, and all targets must relink to
the complete original image byte for byte. This affects reference assembly only;
C compiler flags and emitted candidate sections remain unchanged.

The formatter base is freshly compiled from `src/debugger/debugger_1AD0.c`, with
GLOBAL_ASM placeholders removed and deferred C disabled. Its `.rodata` is 208
bytes with 52 relocations. Before source grouping native objdiff awarded it zero
matching bytes; no symbols are fabricated or resized to change that result. The two
unassigned ranges also receive zero credit.

## GAME data references

GAME contributes 86 reference ranges spanning exactly 189,088 bytes: 48 mapped
ranges and 38 unassigned ranges. The latter retain all 162,804 unassigned bytes,
including zero-filled storage. Shared main/controller backing remains counted
once in the main category; BSS is excluded.

Independent references use original decompressed GAME code at `0x15000000` as
analysis context and its separate data image at `0x80082B20`. These have distinct
loaded origins even though the temporary analysis input concatenates them.
Pointer-word definitions are checked against the corresponding original data
row and image offset. Code context never enters the data denominator. Each
physical data target keeps the canonical input section name; split `.rodata.*`
sections are disassembled independently from their original addresses. The
complete data-only link must equal the ROM's decoded data stream byte for byte.

Candidates use fresh C-only compilations or freshly built GAME SDK archive
members. GLOBAL_ASM is removed and deferred C remains disabled. Forty
GAME ranges have candidates. Eighteen emitted sections contain 152 trailing
compiler-alignment bytes in total. Their explicit linker contracts distinguish
these bytes from their owned payloads. The report verifies the exact emitted
extent and requires that padding be zero with no relocation or ordinary symbol
in or across the tail. Full base objects, section sizes and symbols stay intact;
only the independently bounded target payload contributes to the denominator.
In particular, the constructor's four compiler-alignment bytes do not claim
`0x80099E98`, which remains in the separate unassigned ROM range.

Eight split tables from `game_16EE20` and `game_1C1150`, totaling 736 bytes,
currently have reference-only report units. The existing runtime splitter
validates instruction sites in complete mixed objects; deleting GLOBAL_ASM
changes those sites. The report does not borrow that mixed output or enable
deferred C to create candidate credit. `candidate_unavailable` in coverage and
`unavailable_candidates` in validation record the limitation. Proving a C-only
partition for these tables is separate follow-up work.

## Verified data counts

The source-grouped report regenerated on 2026-10-09 from `35193f6` plus the
[SDK symbol correction](us_sdk_data_symbols.md), with the native completion gate
enabled, has these data measures. Its validated source fingerprint is
`5f4d0dcca454b995af4472563b5430709a5b6b06d6df4a8935e6dd21bb335cf5`.

| Storage | Total bytes | Native matched bytes | Completed bytes |
| --- | ---: | ---: | ---: |
| Main initialized data | 7,824 | 592 | 336 |
| GAME initialized data | 189,088 | 512 | 0 |
| Debugger initialized data | 4,720 | 0 | 0 |
| Stored font asset | 5,440 | 5,440 | 5,440 |
| Total | 207,072 | 6,544 | 5,776 |

All 201,632 loaded initialized-data bytes are represented: 171,988 unassigned
and 29,644 mapped. Font adds 5,440 stored bytes to the ordinary Data category.
Completion requires both real build integration and complete native data matching
within each unit. Matching preserved GAME data still does not qualify because it
is not rebuilt into the compressed stream. SDK data with different native symbol
metadata also remains incomplete even when its linked bytes match the ROM.

The earlier report downgraded 22 SDK units, removing 17,584 fully-linked code
bytes. Correct names, payload sizes and anonymous alignment padding restore eight
units: 2,196 fully-linked code bytes and 208 matched/completed data bytes.
`complete_code` is now 117,284; native matched code remains 513,144 bytes (22.843681%).
Native matched data is 6,544 bytes (3.1602535%), of which 5,776 bytes are complete
(2.789368%). Fourteen units still lose completion: 15,388 code bytes and 608 data
bytes. Eleven contain anonymous constants; three VI tables have SDK symbol sizes
that truncate their true payloads. These are native comparison limitations, not
new differences in their ROM-identical data sections. All final units satisfy
`complete_data <= matched_data`; aggregate or category totals cannot conceal a
violation. The validation file records the affected units in `completion_downgrades`.

All three complete data reference images relink exactly to the checked US ROM.
The final grouped objects also independently relink to the complete original
code and data images for all three overlays; `owned/verification.json` records
these six byte-for-byte checks.
`build/us/objdiff-report/coverage.json` records provenance, target/base hashes,
candidate errors, relocation counts and literal-byte observations. Validation
reconciles native per-unit and aggregate denominators, rechecks all inputs and
records whole-image proofs. The completed font additionally requires verified
editable source inputs and all 96 actual ROM link objects. Generated reports and
proofs remain ignored; CI uploads only the validated native report.
