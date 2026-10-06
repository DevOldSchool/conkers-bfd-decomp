# US game-overlay Rare controller objects

Three more complete text sections, eight functions, and `0x7E0` (2,016)
bytes map to the existing verified `lib/libultrare` archive. This changes
archive ownership only; no SDK sources, instructions, or source skeletons
are added. No registered source units or function records occupy these ranges.

## Complete-object evidence

The authority is the US ROM with SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a` and its extracted game code with
SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. Objects are the existing
`lib/libultrare/build/libultrare/io/` files checked by
`lib/libultrare/object-md5s.txt` before game-archive staging.

| Member | Complete game text range | Bytes | Function offsets within object |
| --- | --- | ---: | --- |
| `controller.o` | `0x1EF090:0x1EF450` | 960 | `0`, `0x1F8`, `0x2C8` |
| `pfsinit.o` | `0x1EF450:0x1EF610` | 448 | `0`, `0xB4` |
| `contreaddata.o` | `0x1EFAA0:0x1EFD00` | 608 | `0`, `0xC4`, `0x16C` |

Each complete relocation-masked text section, including its padding, has
exactly one occurrence in the entire game image. The comparison uses
`scripts/audit_library_boundaries.py`; relocation masks retain opcodes and
register fields. The raw entries in `reference/game/us/asm/` agree with
the object function offsets. The static read-data packer at `+0x16C` is
identified by its section-relative call and the source's third function.
All three ends coincide with existing independently reviewed map boundaries.

The controller and Pak-init sections also equal their main-executable copies
byte for byte, at ROM `0x25340:0x25700` and `0x27660:0x27820` respectively.
The read-data section equals main ROM `0x24BC0:0x24E20` except for the single
call word at relative `0x28`: that section-relative relocation calls the
overlay's static packer at `0x151EFC0C`.

## Relocations and shared allocations

`controller.o` retains main-target calls to `osGetTime=0x10024F40`,
`__ll_mul=0x10026968`, `__ull_div=0x10026868`,
`osCreateMesgQueue=0x10023790`, `osSetTimer=0x10024A40`,
`osRecvMesg=0x10023440`, `__osSiRawStartDma=0x100257C0`, and
`__osSiCreateAccessQueue=0x10025700`. Its own global helpers also retain
main addresses: `__osPackRequestData=0x10025608` and
`__osContGetInitData=0x10025538`. The clock-rate reference is
`osClockRate=0x8002BD10` (low word at `+4`). Explicit linker bindings retain
these targets even when another overlay archive member defines the same name.

The controller object's complete initialized `.data` is 16 zero bytes,
identical to main ROM `0x2BE10:0x2BE20`. Its initialization flag resolves
to `0x8002BE10`. Its complete `.bss` is `0x90` bytes at
`0x80042A10:0x80042AA0`, already archive-backed in `config/profiles/us.yaml`.
Its exported object offsets are:

| Symbol | Object BSS offset | Runtime address |
| --- | --- | --- |
| `__osContPifRam` | `0` | `0x80042A10` |
| `__osContLastCmd` | `0x40` | `0x80042A50` |
| `__osMaxControllers` | `0x41` | `0x80042A51` |
| `__osEepromTimer` | `0x48` | `0x80042A58` |
| `__osEepromTimerQ` | `0x68` | `0x80042A78` |
| `__osEepromTimerMsg` | `0x80` | `0x80042A90` |

Decoded overlay references agree with these offsets, including the PIF
status word at `+0x3C`. The EEPROM timer has no text reference in this
object; its placement follows the complete already reviewed main BSS section.
`config/game/us-sdk.ld` binds both entire sections with `NOLOAD` and exact
size assertions, preserving the shared allocations without emitting code-image
bytes or allocating replacement runtime buffers.

`contreaddata.o` uses that same controller state and the existing main SI,
DMA, and message-receive bindings. Its static packer remains local.
`pfsinit.o` retains main calls to `__osPfsGetStatus=0x10027714`,
`__osGetId=0x10027F84`, `osPfsChecker=0x10028670`,
`__osPfsRequestData=0x10025170`, and `__osPfsGetInitData=0x1002526C`,
plus the existing SI, DMA, and message-receive bindings. Its PIF buffer
resolves to the previously bound `__osPfsPifRam=0x800429D0`.
Neither object has additional nonempty data, rodata, or BSS sections.

## Search scope and retained candidates

The full existing Rare text-object corpus was scanned against the entire
game image. Six distinct templates matched; the other three were integrated
in the preceding pass. A separate scan of stock I/J/K/L text sections shorter
than 32 bytes found the already mapped `sqrtf` and generic return/padding
templates. Their many occurrences do not establish library ownership.

At the time of this pass, the adjacent matrix utility range
`0x1EFD00:0x1EFF70` remained raw. Stock
2.0I `mtxutil.o` has the same `0x270` extent, function order, and first three
functions, but its final `guMtxL2F` implementation uses a reciprocal multiplier
where the retail code uses division, changing instruction scheduling as well.
That is partial lineage evidence, not a complete stock-object match.
The follow-up in `game_sdk_mtxutil_variant.md` resolves this range with the
existing Rare header and a complete, exact reconstructed object.
The SI access wrappers were subsequently reconstructed with explicit external
state references; see [`game_sdk_si_access_variant.md`](game_sdk_si_access_variant.md).
Their text is exact, while the surrounding original game-buffer BSS extent
remains unclaimed.

Every integrated library range is still converted to raw ASM by
`scripts/prepare_game_reference.py` for independent candidate comparisons.

## Validation

On 2026-09-02, `./conker game-build --refresh` produced a complete
byte-identical game image with SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. The ELF `.game` section was
independently checked against that digest. Both controller output sections
are `SHT_NOBITS`, at the exact addresses and sizes above.
`./conker build --profile us` passed the complete original US ROM checksum.
All 150 tests passed; generated progress, whitespace, and shell syntax checks
passed. The canonical inventory still has 433 function records and 131 source
units. Total archive-backed text increases from 39,168 to 41,184 bytes;
total instruction-matched code increases from 43,428 to 45,444 bytes.
