# Additional US game-overlay SDK archive objects

This pass maps eight complete library text sections: 14 recovered functions
and `0xF60` (3,936) bytes. Five objects come from the pinned stock libultra 2.0I
ROM build; three come from the existing verified Rare archive. No SDK sources
or object instructions are changed, and no SDK skeletons are added under `src`.

## Evidence and ownership

- US ROM SHA-1: `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
- US game-code SHA-1: `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
- Stock objects: `lib/ultralib/build/I/libultra_rom/src/`, built with
  `MODERN_LD=1` from revision `e24c836796df4bf520ff8b11a5c9d2cea3a66cbd`.
- Rare objects: `lib/libultrare/build/libultrare/io/`, checked against the
  existing `lib/libultrare/object-md5s.txt` before archive staging.
- Raw authority: the hash-checked retail game image and independently
  generated `reference/game/us/asm/` instruction words.

Every object has exactly one complete relocation-masked `.text` occurrence in
the US game image, including padding. The comparison uses
`read_object_templates` and `find_occurrences` from
`scripts/audit_library_boundaries.py`, preserving opcodes and registers in
relocated instructions. All relocation targets were decoded separately.
`mtxcatf`, `sqrtf`, and `crc` have no text relocations: their complete sections
equal the target without masking. ELF function offsets agree with raw entries.

| Archive | Member | US game range | Bytes | Raw member entry points |
| --- | --- | --- | ---: | --- |
| `libultra_2_0I` | `piread.o` | `0x1EF040:0x1EF080` | 64 | `func_151EF040` |
| `libultra_2_0I` | `sqrtf.o` | `0x1EF080:0x1EF090` | 16 | `func_151EF080` |
| `libultra_2_0I` | `mtxcatf.o` | `0x1F0140:0x1F0350` | 528 | `func_151F0140`, `func_151F01E0` |
| `libultra_2_0I` | `sirawdma.o` | `0x1F0410:0x1F04C0` | 176 | `func_151F0410` |
| `libultrare` | `pfsisplug.o` | `0x1F1D10:0x1F2080` | 880 | `func_151F1D10`, `func_151F1EB0`, `func_151F1FAC` |
| `libultrare` | `contramread.o` | `0x1F2080:0x1F2430` | 944 | `func_151F2080`, `func_151F22C4` |
| `libultrare` | `contramwrite.o` | `0x1F2430:0x1F27E0` | 944 | `func_151F2430`, `func_151F2660` |
| `libultra_2_0I` | `crc.o` | `0x1F27E0:0x1F2960` | 384 | `func_151F27E0`, `func_151F2890` |

Two exact object ends add new map splits. `0x1EF080` separates `piread.o`
from the complete 16-byte `sqrtf.o` (return, delay-slot square root, and two
padding words). `0x1F2960` ends `crc.o` and is also the next recovered function
entry; the following code remains raw through the existing `0x1F3DE0` boundary.
Neither split is inferred from alignment alone.

## Relocation and non-text review

`piread.o` calls the main executable's `__osPiGetAccess=0x10023720`,
`osPiRawReadIo=0x100267A0`, and `__osPiRelAccess=0x10023764`.

`sirawdma.o` calls `__osSiDeviceBusy=0x10027630`,
`osWritebackDCache=0x10023D20`, `osVirtualToPhysical=0x100233C0`, and
`osInvalDCache=0x10022D10`. Its complete text also equals main-ROM
`0x257C0:0x25870` byte for byte, including the calls.

`pfsisplug.o` places its three functions at relative offsets `0`, `0x1A0`,
and `0x29C`. Its complete text equals main-ROM `0x24FD0:0x25340`. Its helper
calls retain main addresses `0x10025170` and `0x1002526C`. All PIF RAM
references resolve to `0x800429D0`, including the status word at `+0x3C`.
The complete `0x40`-byte BSS occupies the already reviewed main allocation
`0x800429D0:0x80042A10`; a `NOLOAD` output section binds this shared allocation
without adding code-image bytes or creating a second runtime buffer.

The RAM pair appears in read-then-write order in the overlay, unlike the
main executable. Complete object comparisons establish those identities.
Section-relative calls to their static packers remain local, at
`0x151F22C4` (read) and `0x151F2660` (write). Both use the same main PIF RAM
and retain these external targets:

- `__osSiGetAccess=0x10025750`, `__osSiRelAccess=0x10025794`;
- `__osSiRawStartDma=0x100257C0`, `osRecvMesg=0x10023440`;
- `__osContAddressCrc=0x10025FD0`, `__osContDataCrc=0x10026080`;
- `__osPfsGetStatus=0x10027714`;
- `__osContLastCmd=0x80042A50`, `__osMaxControllers=0x80042A51`.

These bindings are explicit in `config/game/us-sdk.ld`. Newly linked library
definitions do not redirect existing main-target calls into overlay copies.
The seven objects other than `pfsisplug` have no additional non-empty allocated
sections; no data/rodata/BSS extent is silently discarded.

## Source retirement and remaining lead

The untouched `game_21D5F0.c` skeleton is exactly the two-function `mtxcatf.o`
range. Its older boundary hypothesis is superseded by this object evidence.
The command below retires only that source and its two raw work items; the
other units sharing the older evidence note remain intact:

```sh
./conker retire-library-units \
  --evidence-reference docs/evidence/game_final_compact_units.md \
  --source src/game/game_21D5F0.c
```

The access-queue range `0x1F0350:0x1F0410` was subsequently resolved as SI
from its actual relocation targets. A reconstructed text object now uses
external declarations for the main queue and game buffer; it does not claim
an original game-BSS extent. See
[`game_sdk_si_access_variant.md`](game_sdk_si_access_variant.md).
Exact reconstruction does not establish an original archive version or linker
map. Every library range still becomes raw ASM in the independent reference.

## Validation

On 2026-09-02, `./conker game-build --refresh` passed with the complete game
image byte-identical to SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
The ELF game section was independently checked against the same digest, and
its PIF RAM section is `SHT_NOBITS` at `0x800429D0`, with size `0x40`.
`./conker build --profile us` also passed the complete original US ROM checksum.
All 150 tests, progress output, whitespace, and shell syntax checks passed.
The source-filter tests verify that retirement preserves other units sharing
the evidence note and rejects unknown source paths without changing inventory.
