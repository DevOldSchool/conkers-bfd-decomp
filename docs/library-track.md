# Library track

The project builds Nintendo 64 library code from `lib/` separately from
Conker-specific `src/` code. Stock SDK objects come from the pinned ultralib
submodule, while verified Rare variants live in a bounded Rare source snapshot.

## Current US integration

`lib/ultralib` is pinned to commit
`e24c836796df4bf520ff8b11a5c9d2cea3a66cbd` of decompals/ultralib. The US
profile links two trimmed archives built from that checkout:

- `libultra_2_0L`: 40 unique objects and 48 mapped sections.
- `libultra_2_0I`: 31 unique objects and 34 mapped sections.

The 2.0L survey covers 6,592 text bytes; see
[`evidence/libultra_us_2_0L_object_bounds.md`](evidence/libultra_us_2_0L_object_bounds.md).
The 2.0I survey covers `0x2DE0` (11,744) text bytes and 48 functions; see
[`evidence/libultra_us_2_0I_additional_object_bounds.md`](evidence/libultra_us_2_0I_additional_object_bounds.md).
Those ranges are archive-owned and therefore no longer appear as generic
`src/libultra` source units or function work items.

`lib/libultrare` is a bounded snapshot of eleven Rare-modified objects from
n64decomp/007 revision `c4356466796c697dfd298010b9bed261f9ed8c6a`. Its
accepted US IDO 5.3 object MD5s are checked before the `libultrare` archive is
staged. The archive contributes 18 mapped sections, covers `0x20E0` (8,416)
text bytes, and owns 22 member functions. See
[`evidence/libultrare_us_additional_object_bounds.md`](evidence/libultrare_us_additional_object_bounds.md).
These eleven objects likewise no longer have generic `src/libultrare` work
items.

Together, the active US profile links 82 unique library objects through 100
mapped `.text`, `.data`, `.rodata`, and `.bss` sections. The independently
generated US comparison map in `config/reference/us.yaml` remains raw assembly.
The complete rebuilt US ROM is byte-identical. EU/PAL mapping remains future
work.

The formatting block remains tracked separately as three structural
Rare-library candidates: `xldtob`, `syncprintf`, and `xprintf`. GoldenEye
provides the closest source lineage, but no tested object is an exact archive
replacement. These are the only remaining `src/libultrare` source units; see
[`evidence/libultrare_us_formatting_boundaries.md`](evidence/libultrare_us_formatting_boundaries.md).

## Contributor commands

Build complete pinned stock archives for SDK-version research with:

```sh
./conker libultra
./conker libultra --version I
./conker libultra --version J
./conker libultra --version K
```

Build the bounded Rare snapshot and verify every object checksum with:

```sh
./conker libultrare
```

Regenerate the raw target and validate the actual library integration with:

```sh
./conker _prepare-reference --profile us
./conker build --profile us
```

A candidate should move into a library archive only after its complete object
boundary, section ownership, symbols, and relocations are reviewed. Keep the
same range as raw assembly in `config/reference/us.yaml`; a relocation-masked
object resemblance is not a substitute for a byte-identical US rebuild.
