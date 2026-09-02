# Additional US Rare-modified libultra object boundaries

This note records complete Rare-modified library object boundaries recovered
from the US main executable. The ranges were initially registered as raw-ASM
work items for boundary review. They now link from the bounded
`lib/libultrare` source snapshot, and the temporary generic `src/libultrare`
work items have been retired. This archive integration does not claim that an
independently authored project C implementation matched the functions.

## Inputs and method

- Canonical US ROM SHA-1: `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
- Authoritative bytes: US main ROM `0x1050:0x292F0`, independently represented
  by `config/reference/us.yaml` and `reference/us/asm/`.
- GoldenEye revision: `c4356466796c697dfd298010b9bed261f9ed8c6a`.
  Its `src/libultrare` sources were compiled for US with the project's IDO 5.3
  recompiler, `-mips2 -32 -O1 -G 0`, `NDEBUG`, `TARGET_N64`, and the
  project's recorded US/Rare defines.
- The complete `.text` section of every resulting Rare object was scanned at
  every 16-byte-aligned position in Conker's raw main executable. Relocated
  words were excluded from the byte scan and then decoded individually against
  the named ELF relocation and linked US call/data target.
- Each retained object is the only complete masked occurrence in the main
  executable. Every start and end is also a raw instruction boundary, and each
  object fills an existing unmapped range exactly. Alignment was not used as
  identity evidence.

The rebuilt object `.text` MD5 for every row equals GoldenEye's checked-in
`scripts/ge007.u-test_basis.csv`. This verifies that the comparison used the
project's accepted US object output rather than a merely similar source build.
Perfect Dark and libreultra contain the same named source families. Banjo-
Kazooie's reviewed US archive map independently places all eleven families;
its order is corroboration only, while Conker's raw bytes determine the ranges.
MK64 and SM64 contain the controller-RAM and Leo families where applicable;
OOT's boot library independently retains the initialization family.

## Archive-member ranges

| US ROM range | VRAM range | Size | Bounded Rare source | Member functions | Sections | Confidence |
|---|---|---:|---|---|---|---|
| `0x22790:0x22A30` | `0x80022790:0x80022A30` | `0x2A0` | `lib/libultrare/src/libultrare/os/initialize.c` | `osInitialize` | `.text=0x2A0`, `.data=0x20`, `.bss=0x10` | relocation-and-section-resolved |
| `0x23930:0x23A10` | `0x80023930:0x80023A10` | `0xE0` | `lib/libultrare/src/libultrare/io/epirawdma.c` | `osEPiRawStartDma` | `.text=0xE0` | relocation-resolved |
| `0x24BC0:0x24E20` | `0x80024BC0:0x80024E20` | `0x260` | `lib/libultrare/src/libultrare/io/contreaddata.c` | `osContStartReadData`, `osContGetReadData`, `__osPackReadData` | `.text=0x260` | relocation-resolved |
| `0x24FD0:0x25340` | `0x80024FD0:0x80025340` | `0x370` | `lib/libultrare/src/libultrare/io/pfsisplug.c` | `osPfsIsPlug`, `__osPfsRequestData`, `__osPfsGetInitData` | `.text=0x370`, `.bss=0x40` | relocation-and-section-resolved |
| `0x25340:0x25700` | `0x80025340:0x80025700` | `0x3C0` | `lib/libultrare/src/libultrare/io/controller.c` | `osContInit`, `__osContGetInitData`, `__osPackRequestData` | `.text=0x3C0`, `.data=0x10`, `.bss=0x90` | relocation-and-section-resolved |
| `0x25870:0x25C20` | `0x80025870:0x80025C20` | `0x3B0` | `lib/libultrare/src/libultrare/io/contramwrite.c` | `__osContRamWrite`, `__osPackRamWriteData` | `.text=0x3B0` | relocation-resolved |
| `0x25C20:0x25FD0` | `0x80025C20:0x80025FD0` | `0x3B0` | `lib/libultrare/src/libultrare/io/contramread.c` | `__osContRamRead`, `__osPackRamReadData` | `.text=0x3B0` | relocation-resolved |
| `0x26150:0x26250` | `0x80026150:0x80026250` | `0x100` | `lib/libultrare/src/libultrare/os/destroythread.c` | `osDestroyThread` | `.text=0x100` | relocation-resolved |
| `0x26B10:0x273D0` | `0x80026B10:0x800273D0` | `0x8C0` | `lib/libultrare/src/libultrare/io/leointerrupt.c` | `__osLeoInterrupt`, `__osLeoAbnormalResume`, `__osLeoResume` | `.text=0x8C0`, `.bss=0x1000` | relocation-and-section-resolved |
| `0x27660:0x27820` | `0x80027660:0x80027820` | `0x1C0` | `lib/libultrare/src/libultrare/io/pfsinit.c` | `osPfsInit`, `__osPfsGetStatus` | `.text=0x1C0` | relocation-resolved |
| `0x27820:0x27910` | `0x80027820:0x80027910` | `0xF0` | `lib/libultrare/src/libultrare/io/leodiskinit.c` | `osLeoDiskInit` | `.text=0xF0`, `.bss=0x80` | relocation-and-section-resolved |

The eleven text sections cover `0x20E0` (8,416) bytes and contain 22 member
functions. IDO does not emit sized ELF function symbols for the six static
helpers, so their names are established by source order, internal call
relocations, and the corresponding raw entry points rather than by alignment.

## Complete non-text ownership

The five objects with non-text allocations also have complete placement
evidence:

| Object section | US placement | Evidence |
|---|---|---|
| `initialize.o .data=0x20` | ROM/VRAM `0x2BD10:0x2BD30` / `0x8002BD10:0x8002BD30` | All 32 bytes equal the GoldenEye object (MD5 `971e604c39e630a3c5b4f0d039381f82`); symbol offsets identify `osClockRate`, `__osShutdown`, `__OSGlobalIntMask`, and `osDiskExist`. |
| `initialize.o .bss=0x10` | `0x800428E0:0x800428F0` | `__osFinalRom` resolves to the section start; the next reviewed allocation is `piacs.o` at `0x800428F0`. |
| `pfsisplug.o .bss=0x40` | `0x800429D0:0x80042A10` | All `__osPfsPifRam` references resolve across the raw labels at `0x800429D0` and `0x80042A0C`; the allocation ends exactly at controller BSS. |
| `controller.o .data=0x10` | ROM/VRAM `0x2BE10:0x2BE20` / `0x8002BE10:0x8002BE20` | All 16 bytes equal the object (MD5 `4ae71336e44bf9bf79d2752e234818a5`); `__osContinitialized` resolves to the start and the next reviewed allocation is `siacs.o .data`. |
| `controller.o .bss=0x90` | `0x80042A10:0x80042AA0` | Raw references reproduce every relative symbol: PIF RAM `+0x00`, last command `+0x40`, controller count `+0x41`, EEPROM timer `+0x48`, queue `+0x68`, and message `+0x80`; `siacs.o .bss` starts at the exact end. |
| `leointerrupt.o .bss=0x1000` | `0x80042AC0:0x80043AC0` | The sole symbol is the `0x1000`-byte `leoDiskStack`; the range begins after `siacs.o` and ends at `LeoDiskHandle`. |
| `leodiskinit.o .bss=0x80` | `0x80043AC0:0x80043B40` | `LeoDiskHandle` occupies `+0x00:0x74`, while all consumers resolve `__osDiskHandle` at `+0x74`; the raw BSS ends at `+0x80`. |

Representative decoded targets include `osVirtualToPhysical=0x800233C0`,
`__osSiRawStartDma=0x800257C0`, `__osPfsPifRam=0x800429D0`,
`__osContPifRam=0x80042A10`, `__osContLastCmd=0x80042A50`,
`__osMaxControllers=0x80042A51`, `__osDiskHandle=0x80043B34`,
`__osRunningThread=0x8002BE00`, and the expected message, timer, cache,
interrupt, CRC, linked-list, and controller helpers. Local static calls land at
the raw entry points listed as member functions above.

## Integration result

`lib/libultrare` contains only these eleven sources and the exact dependent
headers needed to reproduce GoldenEye's accepted US IDO 5.3 output. Its
`verify` target checks the complete object MD5 for every member before the US
build stages `libultrare.a`. The working map assigns all eleven text sections
and all seven non-text allocations to that archive; the reference map remains
raw assembly/data/BSS throughout.

One link adapter is required for `initialize.o`: Rare's source stores the
physical callback address for `__osLeoInterrupt`, `0x10026B10`, while the
function executes at virtual address `0x80026B10`. The verified source object
is left unchanged. Only the staged copy of `initialize.o` renames that
relocation to `__osLeoInterruptPhysical`, which the US link defines as
`0x10026B10`. This preserves both the accepted object MD5 and the target word.

After the complete archive link produced a byte-identical US ROM, the 22
temporary `raw_asm` function records and eleven generated source-unit skeletons
were retired with the supported atomic inventory command. They were not marked
matched C. The three separately reviewed formatting candidates remain under
`src/libultrare/libc` because they do not have an exact archive replacement.

## Rejected leads

The other compiled GoldenEye `libultrare` objects were not promoted. Their
complete relocation-masked `.text` sections do not occur in Conker's main
executable. In particular, `aisetnextbuf.o`, `devmgr.o`, `pimgr.o`, `sptask.o`,
`vi.o`, and `vimgr.o` have related SDK functionality but materially different
code, object membership, or constants. The EEPROM, audio, and formatting
objects likewise provide no new complete-object match in the unmapped ranges;
the separately reviewed formatting boundaries remain structural candidates.
No partial function resemblance or alignment-only split was registered.
