# Conker US MP3 transform library objects

Two independently sourced assembly routines now link from `libultrare`.
These are original assembly-library implementations, not new C matches.
Perfect Dark revision `169ed48bdcbfb3b568b028bd5bebb27680073514` provides
`src/lib/mp3/lib_46650.s` and `lib_47550.s`. Their instruction bodies and
constant definitions reproduce Conker without instruction changes.

| Member | Complete overlay text | Function bytes | Final padding | Runtime entry |
| --- | --- | ---: | ---: | --- |
| `lib_46650.o` | `0x1F8CF0:0x1F9BF0` | 3,832 | 8 | `0x151F8CF0` |
| `lib_47550.o` | `0x1F9BF0:0x1FA130` | 1,332 | 12 | `0x151F9BF0` |

Each complete text template occurs exactly once in the ROM-derived overlay.
The first member also emits the complete `0x170`-byte rodata section at
`0x800B0C50:0x800B0DC0`, immediately following the decoder's complete tables.
This section includes constants exported to the second transform; they are
not split into a separate invented object. The second member emits only text.
Neither member allocates data, BSS or COMMON.

## Assembly and relocation evidence

The build uses the installed IDO preprocessor and GNU MIPS assembler targeting
VR4300/o32. The reference's small include files are retained, using the pinned
ultralib assembly headers. An assembly-style `#` comment is converted to a C
comment for IDO preprocessing, trailing whitespace is normalized, and ELF
function type/size directives are appended. These changes emit no instructions
or constants. The first successfully assembled instruction bodies match;
earlier build attempts only resolved missing host `cpp` and comment syntax.
No ROM bytes, target assembly bodies or instruction patches are used.

| Member | Assembler-object MD5 | Resolved full-text SHA-1 | Relocations |
| --- | --- | --- | ---: |
| `lib_46650.o` | `296cceb2e8bf96b6e9680b89176955e1` | `dcc116c384d057b815cae26041036c081ad9a138` | 134 |
| `lib_47550.o` | `eb5cee851254f947df9e55665ab66df8` | `c6584add060a272e92903841e21b49d06a5b946d` | 46 |

All 90 HI/LO pairs are resolved and compared. The first object's 67 pairs
refer to its constant exports; the second object's 23 pairs resolve to those
same real exports. The decoder's former absolute transform aliases are
removed so its calls now resolve to the actual archive functions.

The complete rodata matches game-data offsets `0x2E130:0x2E2A0`, including
its final eight alignment bytes. Its SHA-1 is
`341d3e69969db3e974b8fd350b38c47ac8fc4b57`. The verified game-data payload has
SHA-1 `42bbe7f02702ca7af5da499fb5cf2f34b7d3d23b`. `NOLOAD` placement with an
exact size assertion preserves the executable-only overlay target; it does
not claim to regenerate the separately compressed data asset.

## Bit-utility follow-up

The preceding `0x1F8870:0x1F8CF0` interval was initially raw and is now linked
from an exact reconstructed assembly member; see
[utility integration](libultrare_us_mp3_util_boundaries.md). Its five entries are
`0x1F8870`, `0x1F892C`, `0x1F8960`, `0x1F8994` and `0x1F8B4C`, corresponding
to the independent reference's bit/Huffman utility family. Conker's first
helper accesses the combined loaded lookup tables through `$s5` and offset
`0x2200`; the reference loads two separate global pointers. This concrete
instruction difference rules out promoting the unmodified reference object.
The unusual internal register convention also reflects its assembly origin.

## Integration verification

`./conker game-build --profile us` passes for the complete 2,072,880-byte
overlay, SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. The new canonical
boundary separates the bit utilities from the first transform. Independent
comparison assembly stays raw, including when the reference map is regenerated.

`./conker build --profile us` passes for the complete 67,108,864-byte US ROM,
SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`. The main build preserves
the original compressed overlay. The newly assembled overlay is separately
verified by complete payload equality above.

All 158 Python tests pass, all 30 research objects compare exactly, all pinned
archive checksums pass, progress is regenerated and whitespace checks pass.
The active search now covers 151 functions and 83,136 text bytes across those
30 objects. Exact library text totals 133,760 bytes: 92,368 in main and 41,392
in the overlay. The remaining power candidate, MP3 wrapper and utility work,
formatting, RSP microcode and static-storage ownership keep this library goal
open. Ordinary game-code implementation remains outside scope.
