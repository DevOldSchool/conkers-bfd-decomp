# US residual library-boundary audit

This audit closes the current US main-executable library-boundary discovery
pass. It combines an exhaustive scan of complete stock I/J/K/L loadable
sections with the reviewed Rare-source and RSP evidence. It does not claim that
every mapped Rare function is decompiled or matched.

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

The game overlay is deliberately out of scope: it is Conker game code rather
than the main executable's SDK/Rare library tail. EU/PAL remains a future
regional mapping target.

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

No surveyed archive object is byte-identical, so these stay raw until their C
implementations match. That is implementation work, not unresolved boundary
work. Their complete `xldtob`/`xprintf` data sections, plus the independently
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

## Conclusion

Within the current US main executable and the known complete stock/Rare source
corpus, there is no remaining library boundary that can be assigned with
object-level evidence. Future discoveries require new external object/source
evidence, a new region, or RSP/source implementation work rather than another
unstructured scan of the same I-L corpus.
