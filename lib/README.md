# Library track

This directory contains Nintendo 64 library code that is built separately from
Conker-specific `src/` code.

## ultralib

`ultralib` is a Git submodule pinned to commit
`e24c836796df4bf520ff8b11a5c9d2cea3a66cbd` of
`https://github.com/decompals/ultralib.git`.

Initialize it after cloning:

```sh
git submodule update --init --recursive
```

Build the default 2.0L `libultra_rom` archive inside the pinned Docker image:

```sh
./conker libultra
```

The US main profile links verified 2.0L, 2.0I, debug-audio, and Rare objects.
The game overlay separately links exact 2.0I objects and Conker variants from
`libultrare`. Each mapping requires complete text and non-text ownership,
resolved relocations, and a byte-identical image. EU/PAL remains future work.
See `docs/library-track.md` for the current evidence and integration totals.

## libultrare

`libultrare` keeps the bounded Rare snapshot and reviewed Conker reconstructions
separate from the stock SDK checkout. Build and verify all member checksums with:

```sh
./conker libultrare
```

See `libultrare/README.md` for source lineage and the individual evidence notes.
