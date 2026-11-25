# US particle configuration and selection

Six data-only C owners reconstruct 2,792 bytes and 89 symbolic pointer
references. They describe the configuration graph used by the original
particle updater, together with a single bounded coordinate prefix.

| Address | Contents | Payload bytes |
| --- | --- | ---: |
| `8008D5E0` | 16 category pointers | 64 |
| `8008E5F0` | First coordinate record only | 16 |
| `8008E940` | 17 parameter records, 64 bytes each | 1,088 |
| `8008ED80` | 24 descriptors, 56 bytes each | 1,344 |
| `8008F728` | Six byte lists and six count/pointer filter records | 88 |
| `8008F780` | 16 category records, 12 bytes each | 192 |

These are verification groups, not claims of original C object boundaries or
runtime execution of every entry. The original GAME archive remains runtime
backing. Matching these INFO objects increases matched data, not complete data.

## Native configuration graph

The full original `func_1518D1C0`, `func_1518D6E0`, `func_1518E3C4`,
`func_15143134`, `func_1502FBE8` and `func_150A7960` spans are checked against
the checksum-validated US ROM. Their hashes and instruction anchors are in
the companion JSON.

The constructor supplies categories 1 through 15. The updater reads the
category byte at effect offset `22` and indexes `8008D5E0` with a four-byte
stride. This establishes the table prefix through entry 15; runtime use of
entry zero is not demonstrated. Each pointer names one of the sixteen
12-byte records at `8008F780`.

A category record supplies a variant-pointer table at `00`, a signed filter
count at `04`, and a filter pointer at `08`. The default descriptor is selected
with `variant * (filter_count + 2) + filter_count`; the alternative path uses
the following slot. A matching filter can select an earlier slot. Row zero
of these tables names all 24 descriptor records. Native actor-variant reset
can supply zero. Sixteen external variant-table symbols identify destinations
without declaring their sizes or claiming any bytes from their contents.

The filter loop uses eight-byte records: a signed halfword count, two bytes
of natural alignment, and a byte-list pointer. It reads each list element as
an unsigned byte and compares it with the actor selector. The six list counts
are 7, 1, 6, 10, 2 and 1. Their 27 bytes and six filter records occupy an
88-byte block with thirteen bytes of normal inter-array compiler alignment.
The compiler reproduces every internal gap without explicit padding fields.
Its final eight alignment bytes are outside the payload and receive no credit.

## Parameter and descriptor fields

The descriptor contains a parameter pointer at `00`, signed point count at
`04`, coordinate pointer at `08`, float at `0C`, signed word at `10`, signed
halfwords at `14` and `16`, and unsigned bytes at `18` and `19`. Floats occupy
`1C`, `20`, `24`, `28`, `2C` and `30`; an unsigned byte occupies `34`. Padding
at `1A..1B` and `35..37` is naturally supplied by the compiler and is zero.

The floats at `28..30` are loaded through integer registers into
`func_150A7960`. Its first three instructions transfer those arguments to
floating registers, followed by single-precision multiplication. The signed
word at `10` is independently confirmed by native signed-to-float conversion.
The category-14 descriptor's original count and pointers are preserved.

Every byte in each 64-byte parameter record has a typed native load: twelve
floats, four signed halfwords and eight unsigned bytes. The updater first
loads the parameter pointer into `s6`. It also stores that pointer in the
spawned object's work area through the native memcpy call. Subsequent loads
through that saved pointer establish the remaining halfwords and colour
bytes. Both pointer paths are recorded in the instruction evidence.

All pointers use actual C symbols and, where needed, array-element addends.
There are 44 references in the descriptors, six in the filter records,
23 in the category records and sixteen in the root array. Internal references
to the byte arrays remain real relocations to their defined symbols.

## Extent limitations

Category 14's descriptor at `8008F250` says 72 points beginning at `8008E5F0`.
That apparent range overlaps the independently referenced coordinate array
at `8008E600` and the native parameter records at `8008E940`. This batch
represents only its first sixteen-byte point. The native base pointer,
positive count, sixteen-byte index stride and typed first-record loads support
that prefix. Its C declaration does not adopt 72 as an array extent, claim
that the remaining 71 records are valid, or repair the original descriptor.
The independently typed parameter records distinguish the later storage from
coordinate data. Full runtime validity of this descriptor remains unresolved.

The additional apparent point records at `8008D9C0` and `8008E930` remain
unassigned: the other native descriptor counts establish 51 records, not 52.
The variant tables' full row counts remain unproven. A subsequent
[variant-table batch](us_particle_variants.md) reconstructs prefixes through
a native ordinal-five producer; it does not infer full extents from neighbours.

## Validation

Base commit: `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7`, plus uncommitted work.
Actual pinned-compiler pilot objects reproduce all 2,792 bytes, including all
89 pointer destinations and addends. The independent whole-GAME reference
image is exact and native objdiff matches all six owners. Integrated-object
preservation passed for all 786 prior GAME objects, including allocated bytes,
symbols and relocations. Function and source-unit inventories are unchanged.

Negative checks exercised every payload byte and all 89 pointer destinations
and addends: 2,970 mutations in total. Native objdiff rejected 2,957; it ignores
thirteen inter-symbol alignment bytes in the grouped filter owner. The
independent ROM-byte verifier rejected every one of the 2,792 payload-byte
mutations, including those thirteen gaps. Thus every mutation was rejected
by at least one independent gate; native objdiff alone does not cover the gaps.

The full suite passed 3,033 tests with eight skips (295.689 seconds).
`./conker build --assets` passed (216 seconds wall time), and the independently
extracted 67,108,864-byte US ROM is byte-identical. The full report passed with
zero compile errors, adding exactly 2,792 matched bytes: 63,318,799 of
65,120,512 (97.23326%), leaving 1,801,713. Complete data remains 63,245,911;
code and function measures are unchanged. All 27,301 prior asset source hashes
and 11,836 asset object hashes are preserved.

Report SHA-256: `38dcdcad052251fe6587af86228e686f1f07d9cf3c714137eeebaddfbde7072f`.
Source fingerprint: `633f9bfa3672954f052b92afc4a1d2563fbede1763a9800d68d08bf023a73ad9`.
Report preparation took 436.0 seconds; reporting and validation took 31.4 seconds.

Temporary scripts and snapshots are under
`build/us/data-completion/particle-settings-*`. The earlier individual
byte-list pilot exposed truncation of a reference section ending between
words. The grouped filter block preserves the entire native interval without
changing the assembler output, compiler options or shared reference tooling.
