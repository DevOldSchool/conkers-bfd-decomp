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

The archive is not linked into either ROM yet. Library objects move into the
profile maps only after their US and EU/PAL boundaries have been identified.
See `docs/library-track.md` for the current candidates.
