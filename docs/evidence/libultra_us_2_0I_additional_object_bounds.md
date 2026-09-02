# Additional US libultra 2.0I object boundaries

This note records additional stock-library object boundaries recovered from the
US main executable. It extends the 2.0L survey. The ranges were initially
registered as `raw_asm` work items for review; after complete-section and link
validation, they were moved to the pinned 2.0I archive and the temporary
generic `src/libultra` inventory entries were retired. This archive integration
does not claim that separately authored project C has matched these functions.

## Inputs and method

- Canonical US ROM SHA-1: `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
- Authoritative bytes: US main ROM `0x1050:0x292F0`, represented independently
  by the raw map in `config/reference/us.yaml` and `reference/us/asm/`.
- Pinned ultralib revision: `e24c836796df4bf520ff8b11a5c9d2cea3a66cbd`.
- Compared archives: 2.0I, 2.0J, 2.0K, and 2.0L `libultra_rom`, built with
  IDO and `MODERN_LD=1`. Version I uses `-O1` for the reviewed IO/OS C objects
  and `-O3` for the two libc objects; `interrupt.s` uses the archive's normal
  assembly optimization settings.

For each archive member, the complete ELF `.text` section was compared at every
16-byte-aligned position in the US main executable. Relocated instruction words
were excluded from the byte comparison, then checked separately by decoding the
linked US word and confirming the named call/data target and addend. A candidate
was retained only when its start and end were existing raw instruction
boundaries and its complete object membership agreed with the raw assembly.

Twenty-nine of the 31 registered objects have only a non-empty `.text`
allocatable section. `seteventmesg.o` additionally owns `.bss=0x80`, while
`timerintr.o` owns `.data=0x10` and `.bss=0x40`; their exact non-text placements
are recorded below.
`exact` means the complete `.text`, including tail padding, is byte-identical.
`relocation-resolved` means every non-relocated byte is identical and every
relocation resolves to the expected US function or datum. `dependency-resolved`
is used for the otherwise identical VI current/next-framebuffer objects.

The 2.0I `.text` MD5 for every row also equals GoldenEye's US object-section
checksum in `scripts/ge007.u-test_basis.csv`. This independently corroborates
the archive version, object naming, source family, and compiler output rather
than merely a similar C implementation.

## Archive-member ranges

Each source path identifies the pinned 2.0I archive member now used by the US
link. The archive's `os/interrupt.o` is assembled from `interrupt.s`.

| US ROM range | VRAM range | Size | Pinned archive source | Member functions | Confidence |
|---|---|---:|---|---|---|
| `0x22DC0:0x22E00` | `0x80022DC0:0x80022E00` | `0x40` | `lib/ultralib/src/os/interrupt.s` | `__osDisableInt`, `__osRestoreInt` | exact |
| `0x22EC0:0x22F60` | `0x80022EC0:0x80022F60` | `0xA0` | `lib/ultralib/src/libc/string.c` | `memcpy`, `strlen`, `strchr` | exact |
| `0x22F60:0x230F0` | `0x80022F60:0x800230F0` | `0x190` | `lib/ultralib/src/libc/ldiv.c` | `lldiv`, `ldiv` | relocation-resolved |
| `0x23390:0x233C0` | `0x80023390:0x800233C0` | `0x30` | `lib/ultralib/src/io/ai.c` | `__osAiDeviceBusy` | exact |
| `0x237C0:0x23830` | `0x800237C0:0x80023830` | `0x70` | `lib/ultralib/src/os/seteventmesg.c` | `osSetEventMesg` | relocation-and-section-resolved |
| `0x23850:0x23930` | `0x80023850:0x80023930` | `0xE0` | `lib/ultralib/src/io/pirawdma.c` | `osPiRawStartDma` | relocation-resolved |
| `0x23DB0:0x23DF0` | `0x80023DB0:0x80023DF0` | `0x40` | `lib/ultralib/src/io/spsetpc.c` | `__osSpSetPc` | exact |
| `0x23DF0:0x23E80` | `0x80023DF0:0x80023E80` | `0x90` | `lib/ultralib/src/io/sprawdma.c` | `__osSpRawStartDma` | relocation-resolved |
| `0x23E80:0x23EB0` | `0x80023E80:0x80023EB0` | `0x30` | `lib/ultralib/src/io/sp.c` | `__osSpDeviceBusy` | exact |
| `0x23EB0:0x242B0` | `0x80023EB0:0x800242B0` | `0x400` | `lib/ultralib/src/os/timerintr.c` | `__osTimerServicesInit`, `__osTimerInterrupt`, `__osSetTimerIntr`, `__osInsertTimer` | relocation-and-section-resolved |
| `0x24410:0x24770` | `0x80024410:0x80024770` | `0x360` | `lib/ultralib/src/io/viswapcontext.c` | `__osViSwapContext` | relocation-resolved |
| `0x247C0:0x24830` | `0x800247C0:0x80024830` | `0x70` | `lib/ultralib/src/io/visetmode.c` | `osViSetMode` | relocation-resolved |
| `0x24830:0x24880` | `0x80024830:0x80024880` | `0x50` | `lib/ultralib/src/io/viswapbuf.c` | `osViSwapBuffer` | relocation-resolved |
| `0x24920:0x24A30` | `0x80024920:0x80024A30` | `0x110` | `lib/ultralib/src/io/pidma.c` | `osPiStartDma` | relocation-resolved |
| `0x24A40:0x24B20` | `0x80024A40:0x80024B20` | `0xE0` | `lib/ultralib/src/os/settimer.c` | `osSetTimer` | relocation-resolved |
| `0x24B20:0x24BA0` | `0x80024B20:0x80024BA0` | `0x80` | `lib/ultralib/src/io/sptaskyielded.c` | `osSpTaskYielded` | relocation-resolved |
| `0x24E20:0x24E60` | `0x80024E20:0x80024E60` | `0x40` | `lib/ultralib/src/io/vigetcurrframebuf.c` | `osViGetCurrentFramebuffer` | dependency-resolved |
| `0x24E60:0x24EA0` | `0x80024E60:0x80024EA0` | `0x40` | `lib/ultralib/src/io/vigetnextframebuf.c` | `osViGetNextFramebuffer` | dependency-resolved |
| `0x24EA0:0x24F10` | `0x80024EA0:0x80024F10` | `0x70` | `lib/ultralib/src/io/visetevent.c` | `osViSetEvent` | relocation-resolved |
| `0x257C0:0x25870` | `0x800257C0:0x80025870` | `0xB0` | `lib/ultralib/src/io/sirawdma.c` | `__osSiRawStartDma` | relocation-resolved |
| `0x25FD0:0x26150` | `0x80025FD0:0x80026150` | `0x180` | `lib/ultralib/src/io/crc.c` | `__osContAddressCrc`, `__osContDataCrc` | exact |
| `0x26250:0x262C0` | `0x80026250:0x800262C0` | `0x70` | `lib/ultralib/src/io/viblack.c` | `osViBlack` | relocation-resolved |
| `0x263D0:0x26530` | `0x800263D0:0x80026530` | `0x160` | `lib/ultralib/src/io/aisetfreq.c` | `osAiSetFrequency` | relocation-resolved |
| `0x26700:0x26750` | `0x80026700:0x80026750` | `0x50` | `lib/ultralib/src/io/sirawread.c` | `__osSiRawReadIo` | dependency-resolved |
| `0x26750:0x267A0` | `0x80026750:0x800267A0` | `0x50` | `lib/ultralib/src/io/sirawwrite.c` | `__osSiRawWriteIo` | dependency-resolved |
| `0x267A0:0x26800` | `0x800267A0:0x80026800` | `0x60` | `lib/ultralib/src/io/pirawread.c` | `osPiRawReadIo` | relocation-resolved |
| `0x26AC0:0x26B10` | `0x80026AC0:0x80026B10` | `0x50` | `lib/ultralib/src/os/sethwinterrupt.c` | `__osSetHWIntrRoutine` | relocation-resolved |
| `0x275F0:0x27620` | `0x800275F0:0x80027620` | `0x30` | `lib/ultralib/src/io/pigetcmdq.c` | `osPiGetCmdQueue` | relocation-resolved |
| `0x27630:0x27660` | `0x80027630:0x80027660` | `0x30` | `lib/ultralib/src/io/si.c` | `__osSiDeviceBusy` | exact |
| `0x27910:0x28670` | `0x80027910:0x80028670` | `0xD60` | `lib/ultralib/src/io/contpfs.c` | `__osSumcalc`, `__osIdCheckSum`, `__osRepairPackId`, `__osCheckPackId`, `__osGetId`, `__osCheckId`, `__osPfsRWInode`, `__osPfsSelectBank` | relocation-resolved |
| `0x28670:0x290D0` | `0x80028670:0x800290D0` | `0xA60` | `lib/ultralib/src/io/pfschecker.c` | `osPfsChecker`, `corrupted_init`, `corrupted` | relocation-resolved |

The decoded relocation targets include `__ll_div=0x8002690C`,
`__ll_mul=0x80026968`, `osRomBase=0x80000308`,
`__osPiDevMgr=0x8002AB50`, `__osViCurr=0x8002BDE0`,
`__osViNext=0x8002BDE4`, `osViClock=0x8002BDE8`, and the already reviewed
PI/SI/SP, cache, message, interrupt, and timer routines at their raw US
addresses. The current/next framebuffer pair is distinguished specifically by
the `__osViCurr` versus `__osViNext` relocation. The SI raw read/write pair is
distinguished from the byte-identical SP templates by both calls targeting
`__osSiDeviceBusy` at `0x80027630`.

The two objects with non-text allocations are also complete-section matches:

- `seteventmesg.o .bss=0x80` maps to
  `0x80042910:0x80042990`. Its sole named datum, the `0x78`-byte
  `__osEventStateTab`, is at section offset zero, and every raw reference
  resolves to `0x80042910`.
- `timerintr.o .data=0x10` maps to ROM/VRAM
  `0x2BD70:0x2BD80` / `0x8002BD70:0x8002BD80`. The archive's relocation at
  section offset zero links `__osTimerList` to `__osBaseTimer`; the US word is
  exactly `0x80042990`, followed by the same 12 zero bytes.
- `timerintr.o .bss=0x40` maps to `0x80042990:0x800429D0`. The raw labels
  reproduce every archive-relative symbol: `__osBaseTimer=+0x00` (size
  `0x20`), `__osCurrentTime=+0x20`, `__osBaseCounter=+0x28`,
  `__osViIntrCount=+0x2C`, and `__osTimerCounter=+0x30`.

Together the 31 registered 2.0I objects cover `0x2DE0` (11,744) text bytes
and contain 48 functions.

## Integration result

The working US map now assigns all 31 text sections, `timerintr.o .data`, and
the two reviewed BSS allocations to `libultra_2_0I`. The build stages only
these members from the pinned 2.0I `libultra_rom` archive and links the trimmed
archive as a complete unit. `config/reference/us.yaml` retains the same text
ranges as named raw assembly and retains independent raw data/BSS ownership.

After a byte-identical full-ROM link established the archive placement, the 48
temporary `raw_asm` function records and 31 generated `src/libultra` skeleton
units were retired with the supported atomic inventory command. They were not
marked matched C and no hand-written source replaced the archive members.

## External comparison

The compared source trees were pinned at these revisions: GoldenEye
`c4356466796c697dfd298010b9bed261f9ed8c6a`, libreultra
`1aca5c13ca041cef86f8dc194b727361dad9c09b`, Perfect Dark
`169ed48bdcbfb3b568b028bd5bebb27680073514`, Mario Kart 64
`58cfcb022e10f83bc3b889d7e97508cae6837098`, Super Mario 64
`9921382a68bb0c865e5e45eb594d9c64db59b1af`, and Ocarina of Time
`e619fc0e6224ade7d3d9c991763e712a81ddaa31`. The local Banjo-Kazooie checkout
was at `9db90a003fff15d13d29505d571aff2543b50383`.

- GoldenEye and Perfect Dark contain the same standard IO/OS/libc source-unit
  names; GoldenEye additionally supplies exact US object-section checksums.
- libreultra confirms the functions, private dependency names, and the
  current/next and SI/SP source distinctions.
- MK64, SM64, and OOT independently retain the `string.c` and `ldiv.c` pairing;
  their project layouts do not provide stronger evidence for the other objects.
- Banjo-Kazooie's reviewed archive map independently places these same objects,
  including the VI, PI, SI, SP, timer, CRC, PFS, and libc families. Its order is
  corroboration only; Conker's raw bytes determine every boundary above.

## Rejected or withheld leads

| US range | Lead | Decision |
|---|---|---|
| `0x26700:0x26750` | `io/sprawread.o` | Same unrelocated template as `sirawread.o`; rejected because the linked call targets `__osSiDeviceBusy`, not `__osSpDeviceBusy`. |
| `0x26750:0x267A0` | `io/sprawwrite.o` | Same unrelocated template as `sirawwrite.o`; rejected for the same SI dependency evidence. |
| Many 16-byte return/padding stubs | `pigettype.o`, `viextendvstart.o`, `vigetcurrcontext.o`, `vigetnextcontext.o`, `getactivequeue.o`, `getcurrfaultthread.o` | Weak lookalikes: the masked text occurs at more than 50 unrelated locations and carries no distinctive relocation, call, or data evidence. |

Alignment alone was not used for any promotion. The rejected rows remain
speculative and are not registered as their proposed alternative identities.
