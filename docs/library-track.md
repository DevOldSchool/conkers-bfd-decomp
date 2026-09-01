# Library track

The project builds Nintendo 64 library code from `lib/` separately from
Conker-specific `src/` code. This keeps standard SDK functions and headers
separate from game code.

## Current status

`lib/ultralib` is pinned to commit
`e24c836796df4bf520ff8b11a5c9d2cea3a66cbd` of the decompals/ultralib project.
Build its default 2.0L `libultra_rom` archive with:

```sh
./conker libultra
```

It is not linked into the active US ROM yet. The profile map keeps the early
executable as raw assembly until a complete library-object boundary is
identified. EU/PAL mapping remains a future goal.

The first US comparison against the pinned 2.0L archive identified 37 reviewed
object-range candidates covering 6,592 text bytes. See
[`evidence/libultra_us_2_0L_object_bounds.md`](evidence/libultra_us_2_0L_object_bounds.md)
for the byte-comparison method, exact ranges, and integration limits.

## Using it in the game build

Keep the archive separate while we map library objects out of the US ROM.
When a candidate is ready, choose the matching ultralib version and object,
record its US boundaries in the profile map, and add that object to the build.
A successful byte-for-byte US rebuild is the practical check that the
integration is correct.

## Contributor commands

Generate the immutable assembly targets before investigating a candidate:

```sh
./conker build --all
./conker m2c <work-item-id>
```

`m2c` assists with control-flow recovery only; use the rebuilt ROM to check
an actual library-object integration.
