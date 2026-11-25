# US particle attachment coordinates

Eight typed coordinate tables reconstruct 4,768 bytes in the GAME data
image. Their counts come from the native particle descriptors consumed by
`func_1518D6E0`, independently of generated assembly labels.

| Address | Records | Bytes | Example category | Descriptor |
| --- | ---: | ---: | ---: | --- |
| `8008D690` | 52 | 832 | 1 | `8008EDF0` |
| `8008D9D0` | 29 | 464 | 7 | `8008F090` |
| `8008DBA0` | 72 | 1,152 | 2 | `8008EE98` |
| `8008E020` | 57 | 912 | 10 | `8008F170` |
| `8008E3B0` | 14 | 224 | 11 | `8008F1A8` |
| `8008E490` | 11 | 176 | 12 | `8008F1E0` |
| `8008E540` | 11 | 176 | 13 | `8008F218` |
| `8008E600` | 52 | 832 | 15 | `8008F288` |

## Native consumer and layout

The original constructor dispatch `func_1518D1C0` has 18 calls that supply
categories 1 through 15. The category byte is stored at stack offset `46`
inside the argument at `3C`. `func_1518E3C4` copies that twelve-byte argument
to the particle object at `18`, putting the category at object offset `22`.
The full registered native function spans are ROM-checked and hashed in the
companion JSON; the constructor's original 220 bytes are read directly from
the checksum-validated archive.

`func_1518D6E0` reads category `22`, multiplies by four and indexes the root
pointer table at `8008D5E0`. The category record supplies a variant table and
a signed filter count. The native default selection is
`variant_table[actor_variant * (filter_count + 2) + filter_count]`.
Every coordinate table above is present in variant row zero. Native
`func_1502FBE8` includes a reset path that stores zero to actor variant `1C8`.
No six-row table boundary is inferred from neighbouring labels.

Each selected descriptor has a signed count at `04`, a coordinate pointer at
`08` and mode at `19`. The attachment path uses a zero-based loop while its
index is less than that count. It scales the index by sixteen, loads a signed
halfword at point offset `0C`, scales that joint index by 64 and selects a
matrix from the actor's pointer at `1D4`. The point is passed to
`func_15143134`, whose native instructions read three floats at offsets
`00`, `04` and `08`. The spawn path independently uses the same point stride,
joint field and transformation helper. Mode 2 and the path without an
attachment matrix use dynamic positions instead.

The C record uses the existing `Vec3f` followed by `s16 joint`. Its natural
two-byte tail padding makes the native sixteen-byte stride. All 296 records
have zero in those padding bytes; the compiler supplies them without an
explicit padding field. Float literals preserve the exact native float bits.
There are no pointers, raw-word patches or compiler tail bytes in these
eight objects.

This proves the storage format and consuming access paths. It does not claim
original C-array boundaries or runtime execution of every category, variant
or record.

## Unresolved neighbouring data

The sixteen bytes at `8008D9C0` and `8008E930` are a 52nd coordinate record,
`{ -32, -14, -6 }` on joint 25, mirroring the 51st. Each reaches the next object
exactly, so both arrays are declared with 52 records even though the native
counts are 51.

Category 14's descriptor at `8008F250` has count 72 and points to `8008E5F0`.
That apparent extent overlaps the independently referenced array at
`8008E600` and reaches parameter data beginning at `8008E940`. The first
record has subsequently been reconstructed as a sixteen-byte prefix in
[the particle-settings batch](us_particle_settings.md), using the native base,
positive count, stride and typed first-record loads. The full 72-record extent
and its runtime validity remain unresolved. The original count and pointer
are preserved; neither batch repairs or reinterprets them.

## Validation

Base commit: `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7`, plus uncommitted work.
Actual pinned-compiler pilot objects reproduce all 4,736 bytes. An independent
whole-GAME reference image is exact, and native objdiff matches all eight
candidate objects. Integrated objects reproduce the same bytes, and all 778
prior GAME objects retain identical allocated bytes, symbols and relocations.
The entire 2,072,880-byte GAME code image and the function/source-unit
inventories are unchanged. All 4,736 individual payload-byte mutations are
rejected by native comparison.

The full suite passes: 3,033 tests, eight skips, 385.016 seconds. The US
`./conker build --assets` passes; independent extraction of the linked ELF
reproduces the 67,108,864-byte original ROM with SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. Build wall time was 286 seconds,
including 258.812 seconds for compile/link/verify. Full report preparation
took 493.4 seconds, followed by 32.3 seconds for comparison and validation,
with zero compile errors. Progress and whitespace pass.

Accepted matched data is **63,316,007 / 65,120,512 bytes (97.22898%)**, a gain
of 4,736 bytes; **1,804,505 bytes remain**. Complete data stays at 63,245,911
bytes. Code and function measures are unchanged. All 27,301 prior asset input
hashes and 11,836 asset object hashes are preserved. The eight actual INFO
objects agree with the report's copied-source candidates. The runtime data
graph and original-assets ELF are unchanged.

Report SHA-256:
`dbcee3ee662128daa5cbc812e524be23c0681c8e0b55883aa806a4f669a77a0d`.
Source fingerprint:
`93797e9907ece4f6f5621f097f343fcdcca59d4deb8c73983b758d63d33ca3cc`.

The objects use INFO sections for verification. The original archive still
supplies runtime GAME data, so this batch adds matched data only. Temporary
scripts, snapshots and audit results are under
`build/us/data-completion/particle-points-*`.
