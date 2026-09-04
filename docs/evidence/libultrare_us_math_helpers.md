# Conker US Rare exponential, logarithm and power helpers

The MP3 decoder calls `0x1504A400`, identifying a further Rare math-library
family outside the MP3 text cluster. Perfect Dark revision
`169ed48bdcbfb3b568b028bd5bebb27680073514` provides independent source in
`src/lib/mp3/lib_45ed0.c`, `lib_47d20.c` and `lib_47ef0.c`. Its power helper
calls exponential and logarithm helpers, as does Conker's raw power routine.
This establishes library lineage; it does not establish Conker's original
source filenames. The new descriptive sources live under the Rare archive's
`gu/` directory.

## Exact objects

| Source | Complete overlay text | Function bytes | Padding | Complete rodata RAM |
| --- | --- | ---: | ---: | --- |
| `gu/expf.c` | `0x4A2B0:0x4A400` | 324 | 12 | `0x800990A0:0x800990B0` |
| `gu/logf.c` | `0x4A620:0x4A730` | 272 | 0 | `0x800990B0:0x800990C0` |

Both complete text templates have exactly one occurrence in the ROM-derived
overlay. All instructions, alignment, five HI/LO relocation pairs and both
complete 16-byte rodata sections match. Neither object emits data, BSS or
COMMON. Exponential ends at the independently identified power routine;
logarithm ends at the next unrelated function, `0x1504A730`. The map adds that
end boundary and leaves the following raw range intact.

Both use IDO `-O2 -g3`, removing only non-runtime `.mdebug` metadata.
Exponential matched on its second candidate: Conker doubles the series value
with addition, rather than multiplying by two. Logarithm matched on its third
candidate: Conker halves with multiplication by `0.5f`, doubles with addition,
and returns explicit float zero on domain rejection. Constants and complete
nontext sections matched from the initial compile.

| Object | Compiler-object MD5 | Resolved full-text SHA-1 | Complete rodata SHA-1 |
| --- | --- | --- | --- |
| `expf.o` | `074ca7753ad8c4108317692a0652b33c` | `f9ac9d8c5e083a81634f90cb40a1239aaf34559c` | `03a40c1a72df39fcb9bf715958f0389959eb3c22` |
| `logf.o` | `56096a3e31b6d20f58365a3816235559` | `51c5a51edee56424f6463e06085e7d123bf34ad6` | `60b0ff3973219cd0ba5f05fd446cd143588fdb40` |

The rodata intervals correspond to offsets `0x16580:0x16590` and
`0x16590:0x165A0` in the separately decompressed game-data payload. All bytes,
including duplicate literals and padding, compare directly after relocation.
Linker `NOLOAD` placement and exact size assertions preserve the executable
overlay target's format; this does not claim to regenerate the data asset.

## Power remains a candidate

`0x4A400:0x4A5E0` remains raw assembly. Four bounded candidate compiles did
not reproduce its saved floating-point register allocation. The latest
candidate emits 448 text bytes instead of 480, with 106 different compared
words after resolving both calls. Its object MD5 is
`cef03357541642c8742d20609548fc15`. The C candidate is preserved, disabled,
in `src/libultrare/gu/powf.c`; it is not included in the archive or counted
as an exact match. No reference or target assembly was edited.

## Integration verification

The complete integrated overlay passes `./conker game-build --profile us`:
2,072,880 bytes, SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
The canonical map uses both archive objects; regenerated comparison maps
remain raw assembly. The existing raw power routine and adjacent completed
tangent source remain unchanged.

`./conker build --profile us` passes for the complete 67,108,864-byte US ROM,
SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`. This main build preserves
the original compressed overlay; the newly compiled overlay is independently
verified by full payload equality above.

All 158 Python tests pass, including the newly retained raw power candidate
and exact math extents. All 28 active research objects match, progress is
regenerated, and whitespace checks pass. This search now covers 149 functions
and 77,952 text bytes across 28 reconstructed objects. Exact library text
totals 128,576 bytes, including 36,208 in the overlay. The library goal remains
active; no ordinary game-code implementation was added.

## Bounded power-register follow-up

After completing both formatters, a further three source-only variants tested
Conker's saved floating-point accumulator and repeated exponent conversions:
a local register-qualified base, a register-qualified parameter, and a separate
result accumulator. None reproduced the target's saved `$f20` allocation.

| Candidate | Complete object MD5 | Text bytes | Compared word differences |
| --- | --- | ---: | ---: |
| Local register base | `0ae7906dc92185ffb6a2e40605ccbafb` | 448 | 106 |
| Register parameter | `cef03357541642c8742d20609548fc15` | 448 | 106 |
| Separate result | `7f3f5adc510cbde9bc967b9975028c25` | 448 | 107 |

All three emitted text only and were checked after resolving the two library
calls. The target extent remains 480 bytes. The explicit cast placement did
not resolve the allocation difference; the second object reproduces the
previous candidate exactly. The original disabled source is retained unchanged
under `src/libultrare/gu/powf.c`. The temporary archive source and build entry
were removed, leaving the canonical map raw and all accepted object checksums
unchanged. No power function is credited or linked from these candidates.

## Compiler-mode follow-up, 2026-09-03

The independent Perfect Dark Makefile selects IDO 7.1 and `-g` for its MP3 C
family. This differs from the IDO 5.3 `-O2 -g3` settings that exactly reproduce
Conker's adjacent exponential and logarithm objects. It is a research lead,
not proof of Conker's compiler version. The available, pinned Conker compiler
was retained; no alternate compiler was installed or claimed tested.

Four additional object-local builds compared the unchanged preserved power
body under the available compiler. Each comparison resolved the exponential
and logarithm calls before comparing against the complete 480-byte target:

| Trial | IDO 5.3 flags | Complete object MD5 | Text bytes | Compared word differences |
| --- | --- | --- | ---: | ---: |
| 8 | `-O2 -g2` | `d1ecb9107109078a052f2d2a002ffaa9` | 752 | 113 |
| 9 | `-O2` | `8c5be30af7c4424257ef195a6ea777b5` | 448 | 106 |
| 10 | `-O1 -g2` | `d1ecb9107109078a052f2d2a002ffaa9` | 752 | 113 |
| 11 | `-O1 -g3` | `f3450323540ff34f0d539aa7827df200` | 672 | 115 |

Differences count corresponding words over the shorter extent; the size
mismatch separately rejects each object. All candidates emit text only.
The target saves `$f20` at stack offset `0x10` in a `0x20`-byte frame. The
`-O2` candidate still uses the earlier unsuitable allocation; the lower
optimization/debug variants add parameter spills and a `0x38`-byte frame.
None improves the preserved candidate.

The temporary archive source and per-object settings were removed, restoring
the accepted Makefile exactly. The disabled candidate's body and raw map stay
unchanged. This brings the recorded total to eleven candidate builds; none
provides zero-difference evidence for power. Repeating these modes or the
earlier register qualifiers is not a new lead.
