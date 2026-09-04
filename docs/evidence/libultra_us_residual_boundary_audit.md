# US residual library-boundary audit

The first sections record the historical stock I/J/K/L complete-template scan
for the then-current US main map. Their counts describe that snapshot, not the
current archive totals. The final section extends the residual scan to both
CPU images and the game-data payload after the formatter and RSP integrations.
Neither scan proves the absence of modified or otherwise unknown libraries. Subsequent
N-audio reconstructions are recorded in
[continued library reconstruction](libultrare_us_continued_reconstruction.md).

## Scope and inputs

- Target ROM: US SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
- Search ranges: executable text `0x1050:0x292F0` and initialized data through
  the end of the main segment at `0x2D4B0`.
- Stock source: pinned decompals/ultralib revision
  `e24c836796df4bf520ff8b11a5c9d2cea3a66cbd`.
- Built variants: I, J, K, and L, for `libultra`, `libultra_d`, and
  `libultra_rom`.
- Rare-source surveys: GoldenEye revision
  `c4356466796c697dfd298010b9bed261f9ed8c6a`, Perfect Dark revision
  `169ed48bdcbfb3b568b028bd5bebb27680073514`, and the Banjo-Kazooie,
  Banjo-Tooie, DK64, and libreultra evidence linked from the companion notes.
- Audit date: 2026-09-02. GoldenEye's public default branch still resolved to
  the pinned revision on that date, and its complete `src/libultrare` tree was
  included in the source-name/function survey.

The game overlay was outside the original main-only scan. It also contains
SDK and Rare libraries, surveyed separately and included in the follow-up
below. EU/PAL remains a future regional mapping target.

## Reproducible object scan

Run this after building all three research targets for I-L:

```sh
./conker library-audit
```

`scripts/audit_library_boundaries.py` reads every ELF32 big-endian object and
extracts each complete non-empty loadable `.text`, `.data`, `.rodata`, `.sdata`,
`.lit4`, and `.lit8` section. It masks only the bits affected by each MIPS
relocation. HI16/LO16-family relocations retain the opcode/register halfword,
and MIPS26 relocations retain the six-bit jump opcode. The scanner searches at
each input section's required alignment and excludes ranges already linked as
library sections in `config/profiles/us.yaml`.

The final scan covers:

- 5,940 object instances;
- 6,906 non-empty loadable section instances;
- 1,305 unique complete relocation-masked section templates;
- 104 already mapped loadable library section ranges;
- 15 raw matching templates;
- zero distinctive raw templates.

The remaining raw templates are repeated or otherwise ambiguous constants and
padding. The only occurrence that also fills one exact existing raw map range
is the debug/non-debug 16-byte `ackramromread.o`/`ackramromwrite.o` no-op return
body at `0x39B0:0x39C0`:

```asm
jr    $ra
nop
nop
nop
```

There is no direct call site and neither `0x800039B0` nor `0x100039B0` appears
as a ROM pointer. Its neighbors are Conker-specific video/memory setup code.
Consequently `0x39B0` remains raw padding/no-op code; assigning either SDK
member name would be unsupported.

## Non-archive boundaries

The complete Rare formatting ranges are already mapped as source units:

- `xldtob`: `0x1550:0x2070`;
- `syncprintf`: `0x2070:0x20D0`;
- `xprintf`: `0x20D0:0x2DB0`.

No surveyed stock archive object was byte-identical at this audit. Later,
`syncprintf` was reconstructed and integrated exactly; `xldtob` and `xprintf`
remain raw implementation work with reviewed boundaries. Their complete `xldtob`/`xprintf` data sections, plus the independently
identified `syncputchars` and `exceptasm` data, were integrated after the
section scan exposed them; see
[`libultra_us_data_object_bounds.md`](libultra_us_data_object_bounds.md).

The RSP tail is also fully bounded by task pointers and the target blob's own
overlay descriptors:

- `rspboot`: `0x290D0:0x291A0`;
- `n_aspMain` overlay 0: `0x291A0:0x2A110`;
- `n_aspMain` overlay 1 / MP3: `0x2A110:0x2AAD0`;
- `n_aspMain` data: `0x2C960:0x2D4B0`.

These are raw RSP binaries until they are reproduced by an RSP assembler; they
must not be counted as decompiled CPU source merely because their bounds are
known.

## Scope of the conclusion

The complete stock I-L corpus yielded no further distinctive raw matches in
this scan. That result applies to unchanged stock templates. Conker-specific
N-audio, formatting, MP3 and RSP implementations require source reconstruction
and separate section-ownership review; they are not ruled out by this scan.
The library-only work continues while those actionable leads remain.

## Residual scan after formatter integration, 2026-09-03

Both formatters and the RSP payloads described above have since been reproduced
and integrated. At that scan, the remaining known implementation leads were the Rare power
candidate and MP3 bit/Huffman utility variant; original static-storage ownership
also remains unresolved. The old raw-formatter and raw-RSP descriptions above
are historical.

The current `./conker library-audit --json` run covers all 5,940 I-L stock object
instances, 6,906 loadable section instances and 1,305 unique section templates.
It now excludes 173 mapped ROM-backed library sections. Dictionary-form library
entries are recognized by their real input section, including the two formatter
`.rodata` entries with `.data` link order; BSS is not treated as ROM payload.
A regression test prevents those constants from being proposed again as raw
library matches. There are still 15 residual main templates and zero distinctive
ones. Six templates coincide with a current raw boundary, but their contents
are ambiguous constants, masked pointer tables, padding or no-op code.

### Complete CPU text corpus

A separate read-only scan combines the 5,940 stock instances with all 78 active
Rare objects in the checked MD5 list. Historical unlisted candidate objects are
excluded. The 6,018 objects yield 5,157 nonempty text-section instances and
1,201 distinct relocation-masked text templates, including sections shorter
than 32 bytes. It scans the entire CPU main range `0x1050:0x290D0` and all
2,072,880 game-code bytes. Contiguous raw ranges are merged for searching so
an internal navigation split cannot hide a whole-object match; existing
library and C placements remain excluded from raw ownership proposals.

Only two 16-byte templates occur in still-raw text: the ROM and debug
`ackramromread`/`ackramromwrite` no-op/return forms. They occur 143 and 18 times
across the two complete images, respectively; 98 and 12 occurrences lie in raw
ranges. Only the first form also fills complete existing raw splits, at main
`0x39B0:0x39C0` and game `0xEB20:0xEB30`. Neither form contains information that
distinguishes SDK ownership from an unrelated empty callback or return body.
No new object name or archive mapping is justified.

### Separately compressed game-data corpus

The same active object corpus yields 1,859 nonempty nontext-section instances
and 204 distinct `.data`/`.rodata`/other supported loadable-section templates.
The scan covers the complete 189,088-byte decompressed data image, excluding
the 12 existing library data/rodata placements inside it. Main-address and BSS
bindings in the overlay linker file are excluded from this payload calculation.

Twenty-two templates have residual hits. Nineteen repeat and mainly consist
of common numeric values, padding or relocation-masked pointer tables. Three
occur once in this payload; the shared `find_occurrences` matcher independently
confirms all three without any relocation masking:

| Game-data offset | RAM address | Template identity | Complete 16-byte contents |
| --- | --- | --- | --- |
| `0x6AA0` | `0x800895C0` | `syncputchars.o .data` | `00000000 00000001 00000000 00000000` |
| `0x7630` | `0x8008A150` | J-L `contramread.o .data` | `FFFFFFFF 00000000 00000000 00000000` |
| `0x28FF0` | `0x800ABB10` | `libm_vals.o .rodata` | `7F810000 00000000 00000000 00000000` |

Uniqueness in one payload does not establish object identity for a padded
sentinel or scalar. A bounded reference check found no matching LUI/address
pair within 16 instructions for these addresses in either CPU image, and no
aligned direct pointers to them in either initialized-data image. That check
does not rule out indirect or more distant address construction. The already
identified sine/cosine implementations explicitly reference the main
`__libm_qnan_f` at `0x8002C920`. There is no supporting code/object-boundary
evidence for assigning any of the three new data hits to its template's SDK
owner. They remain unassigned, with no archive or progress credit.

### Inputs, verification and remaining action

The target hashes remain:

- Full US ROM: `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
- Decompressed game code: `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
- Decompressed game data: `42bbe7f02702ca7af5da499fb5cf2f34b7d3d23b`.

The stock revision remains `e24c836796df4bf520ff8b11a5c9d2cea3a66cbd`.
The supplemental scans reuse the repository ELF reader and relocation masks,
match entire sections at their required alignment, and compare all unmasked
bytes rather than strings or instruction mnemonics. Detailed scan reports were
temporary JSON outputs produced by the same repository readers and relocation
masks. The SDK command above reruns the main scan.

All 170 Python tests pass, generated progress is current and whitespace checks
pass. This audit changes no runtime source, archive membership or ROM map;
the preceding byte-identical full-ROM and overlay results remain applicable.
Exact CPU library text stays at 145,152 bytes.

This closes the unchanged-template leads in the surveyed corpus, not every
possible Rare variant. The power implementation remains a preserved nonzero
candidate after its documented bounded trials. The independently identified
MP3 utility has four verified table-access changes; adapting its assembly
requires the requested explicit override of the current `AGENTS.md` prohibition.
External workspace accesses still do not establish original BSS ownership.
No ordinary game-code work is part of this library-only goal.

The subsequent explicit MP3 authorization permitted the four reviewed assembly
changes. The complete utility now matches and links from `libultrare`; see
[MP3 utility integration](libultrare_us_mp3_util_boundaries.md). The original
scan counts above remain historical. This resolves its pending approval lead
and raises exact CPU library text to 146,304 bytes; the preserved power
candidate and original workspace ownership remain unresolved.

## Constant-data follow-up, 2026-09-03

The three unique scalar matches were reviewed against surrounding data and
bounded address-construction references in both CPU images. The expanded
search paired LUI instructions with supported low-half accesses up to 64
instructions later; reported pairs were then inspected where used as evidence.
This heuristic is a discovery aid, not a proof that an address is unreferenced.

The `contramread` resemblance at `0x8008A150` is rejected as an object-boundary
lead. It is the second word of the final `{0, -1}` entry in an eight-byte game
callback table beginning at `0x8008A0B4`. Nineteen preceding entries contain
game function pointers and numeric parameters. At `0x15141DF8`, code multiplies
the index by eight; `0x15141DFC:0x15141E04` constructs and indexes that table
base. It reads the callback at offset zero and the signed parameter at offset
four. Thus the matching `FFFFFFFF` is part of an independently referenced game
data structure, followed by zero padding, rather than evidence of an SDK
`contramread` allocation. No game source was implemented or registered.

The other two scalar matches remain insufficiently identified:

- `0x800895C0` (`syncputchars` pattern) lies between a float global referenced
  at `0x1512C408`, `0x1512C43C` and `0x1512C45C`, and a byte table whose base
  is constructed at `0x1512D784:0x1512D78C`. Those neighboring references do
  not establish an owner for the isolated `0, 1, 0, 0` pattern.
- `0x800ABB10` (`libm_vals` pattern) follows float literals directly loaded at
  `0x151ECE30`, `0x151EE8F8` and `0x151EE964`, and immediately precedes the
  exact MP3 decoder rodata at `0x800ABB20`. The NaN word could be a separate
  scalar/object, but its value and alignment alone cannot distinguish those
  possibilities. The known trigonometric code still binds to the main NaN.

No new supporting direct reference was found for either isolated scalar in
this bounded check. Both remain unassigned. The storage review now records
the MP3 stream's used `0x8480`-byte extent, window and scaling-table extents,
and the sound player's used view, while retaining unresolved original BSS
ownership; see [workspace bounds](libultrare_us_workspace_bounds.md).
The [power follow-up](libultrare_us_math_helpers.md) records four further
compiler-mode candidates without an exact match. Exact CPU library text
remains 146,304 bytes; this pass claims no new archive member.

After removing the temporary power build, `./conker libultrare` passes all
79 accepted object checksums. The 34-object reconstruction audit again passes
all complete relocated comparisons, covering 175 functions and 95,680 text
bytes. The accepted Makefile is byte-identical to its pre-trial snapshot and
the archive contains no power candidate. Progress is current and whitespace
checks pass. Existing full-ROM and integrated-overlay output hashes were
rechecked against the hashes above; full image builds were not repeated for
this evidence/comment-only final change.
