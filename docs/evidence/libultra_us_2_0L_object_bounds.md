# US libultra 2.0L object-boundary evidence

This note records the first independently reviewed libultra object boundaries
in the US main executable. It does not mark any function as matched and does
not yet link the library archive into the ROM.

## Inputs

- US ROM SHA-1: `4cbadd3c4e0729dec46af64ad018050eada4f47a`
- US main text: ROM `0x1050` through `0x292F0`
- ultralib revision: `e24c836796df4bf520ff8b11a5c9d2cea3a66cbd`
- archive variant: `VERSION=L TARGET=libultra_rom`
- archive: `lib/ultralib/build/L/libultra_rom/libultra_rom.a`

The archive was rebuilt through `./conker libultra` before comparison.

## Method

Each archive member's complete ELF `.text` section was compared against every
16-byte-aligned position in the verified US main text. ELF `.rel.text` entries
were treated as relocation sites: for those candidates the relocated four-byte
instruction word was excluded and every other byte in the complete `.text`
section had to agree. A candidate was retained only when the complete object
had one location in the executable and both its start and end already occurred
at instruction boundaries in `config/profiles/us.yaml`.

`exact` means that every `.text` byte matched without exclusions.
`relocation-masked` means that all non-relocated `.text` bytes matched and the
candidate was unique. `dependency-resolved` is used for the two access-queue
objects whose non-relocated code is intentionally identical: their locations
were separated using the surrounding PI versus SI callers and their distinct
relocated queue symbols.

The scan covered 402 archive members with non-empty text. It produced 35 unique
complete-text candidates: 21 exact and 14 relocation-masked. The two identical
access-queue candidates add two dependency-resolved objects. These 37 object
ranges cover `0x19C0` (6,592) bytes.

## Reviewed US object ranges

| US start | US end | Text size | ultralib object | Text symbols | Evidence |
|---:|---:|---:|---|---|---|
| `0x226F0` | `0x22790` | `0xA0` | `libc/bzero.o` | `_bzero` | exact |
| `0x22A30` | `0x22A40` | `0x10` | `os/setsr.o` | `__osSetSR` | exact |
| `0x22A40` | `0x22A50` | `0x10` | `os/getsr.o` | `__osGetSR` | exact |
| `0x22A50` | `0x22A60` | `0x10` | `os/setfpccsr.o` | `__osSetFpcCsr` | exact |
| `0x22A60` | `0x22BB0` | `0x150` | `os/startthread.o` | `osStartThread` | relocation-masked |
| `0x22BB0` | `0x22C90` | `0xE0` | `os/setthreadpri.o` | `osSetThreadPri` | relocation-masked |
| `0x22C90` | `0x22D10` | `0x80` | `os/invalicache.o` | `osInvalICache` | exact |
| `0x22D10` | `0x22DC0` | `0xB0` | `os/invaldcache.o` | `osInvalDCache` | exact |
| `0x22E00` | `0x22EC0` | `0xC0` | `os/stopthread.o` | `osStopThread` | relocation-masked |
| `0x230F0` | `0x23390` | `0x2A0` | `libc/xlitob.o` | `_Litob` | relocation-masked |
| `0x233C0` | `0x23440` | `0x80` | `os/virtualtophysical.o` | `osVirtualToPhysical` | relocation-masked |
| `0x23440` | `0x23580` | `0x140` | `os/recvmesg.o` | `osRecvMesg` | relocation-masked |
| `0x23580` | `0x236D0` | `0x150` | `os/sendmesg.o` | `osSendMesg` | relocation-masked |
| `0x236D0` | `0x23790` | `0xC0` | `io/piacs.o` | `__osPiCreateAccessQueue`, `__osPiGetAccess`, `__osPiRelAccess` | dependency-resolved |
| `0x23790` | `0x237C0` | `0x30` | `os/createmesgqueue.o` | `osCreateMesgQueue` | relocation-masked |
| `0x23830` | `0x23850` | `0x20` | `os/getthreadpri.o` | `osGetThreadPri` | relocation-masked |
| `0x23A10` | `0x23D20` | `0x310` | `libc/bcopy.o` | `_bcopy` | exact |
| `0x23D20` | `0x23DA0` | `0x80` | `os/writebackdcache.o` | `osWritebackDCache` | exact |
| `0x23DA0` | `0x23DB0` | `0x10` | `io/spsetstat.o` | `__osSpSetStatus` | exact |
| `0x24770` | `0x24780` | `0x10` | `os/getcount.o` | `osGetCount` | exact |
| `0x24780` | `0x247C0` | `0x40` | `os/thread.o` | `__osDequeueThread` | exact |
| `0x24880` | `0x24920` | `0xA0` | `os/setintmask.o` | `osSetIntMask` | relocation-masked |
| `0x24A30` | `0x24A40` | `0x10` | `io/aigetstat.o` | `osAiGetStatus` | exact |
| `0x24BA0` | `0x24BC0` | `0x20` | `io/sptaskyield.o` | `osSpTaskYield` | relocation-masked |
| `0x24F10` | `0x24F40` | `0x30` | `os/writebackdcacheall.o` | `osWritebackDCacheAll` | exact |
| `0x24F40` | `0x24FD0` | `0x90` | `os/gettime.o` | `osGetTime` | relocation-masked |
| `0x25700` | `0x257C0` | `0xC0` | `io/siacs.o` | `__osSiCreateAccessQueue`, `__osSiGetAccess`, `__osSiRelAccess` | dependency-resolved |
| `0x262C0` | `0x262D0` | `0x10` | `io/pigetstat.o` | `osPiGetStatus` | exact |
| `0x262D0` | `0x26310` | `0x40` | `os/unmaptlb.o` | `osUnmapTLB` | exact |
| `0x26310` | `0x263D0` | `0xC0` | `os/maptlb.o` | `osMapTLB` | exact |
| `0x26530` | `0x26540` | `0x10` | `gu/sqrtf.o` | `sqrtf` | exact |
| `0x26540` | `0x26700` | `0x1C0` | `gu/sinf.o` | `__sinf` | relocation-masked |
| `0x26800` | `0x26AC0` | `0x2C0` | `libc/ll.o` | `__ull_rshift`, `__ull_rem`, `__ull_div`, `__ll_lshift`, `__ll_rem`, `__ll_div`, `__ll_mul`, `__ull_divremi`, `__ll_mod`, `__ll_rshift` | exact |
| `0x273D0` | `0x27490` | `0xC0` | `os/probetlb.o` | `__osProbeTLB` | exact |
| `0x27490` | `0x274A0` | `0x10` | `os/setcompare.o` | `__osSetCompare` | exact |
| `0x274A0` | `0x275F0` | `0x150` | `os/jammesg.o` | `osJamMesg` | relocation-masked |
| `0x27620` | `0x27630` | `0x10` | `io/spgetstat.o` | `__osSpGetStatus` | exact |

## Validation and limits

- Every recorded start and end is already a US instruction boundary.
- No two recorded ranges overlap.
- These are archive-object boundary candidates, not function-match claims.
- Relocation-masked and dependency-resolved candidates still require a real
  link at their recorded positions and a byte-identical full-ROM comparison.
- The scan did not promote the other 363 archive members: most are not linked
  by Conker, while others may differ by SDK variant, compile flags, or local
  modification. Absence from this list is not evidence that a range is
  game-specific.
- The two 16-byte `ackramromread.o` and `ackramromwrite.o` bodies were rejected:
  their text appears at many return stubs and does not identify a unique range.

