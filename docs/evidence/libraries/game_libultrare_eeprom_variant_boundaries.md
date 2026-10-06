# US game-overlay Rare EEPROM reconstruction

Evidence kind: `object_symbols`. The final 928 executable bytes before the
already reviewed `game_20A990` unit form three complete EEPROM objects.
Their control flow and shared controller state identify the source lineage, but
the complete relocation-masked sections do not match the surveyed stock I/J/K/L
objects. They are reconstructed as Rare overrides under `libultrare/io/`,
rather than assigned to game source or a stock SDK archive.

| Object | US range | Bytes | Functions | Range SHA-1 |
| --- | --- | ---: | --- | --- |
| `libultrare/io/conteepread` | `0x1DD140:0x1DD3A0` | 608 | `func_151DD140`, `func_151DD304` | `b399a27be0a4eafc41de786d9fdd46f1bfd47e9e` |
| `libultrare/io/conteeplongread` | `0x1DD3A0:0x1DD460` | 192 | `func_151DD3A0` | `3be7b9589bbf925060d2339e13d45cf82a5d3c76` |
| `libultrare/io/conteepprobe` | `0x1DD460:0x1DD4E0` | 128 | `func_151DD460` | `6b5dcdadef1b28f351bd3ec37cee18a4791a5125` |

`conteepread` performs SI access locking, EEPROM status and range checks, the
busy loop, read-command packing, two DMA operations, response copying, and SI
release. Its second local entry packs the read request. `conteeplongread`
repeatedly calls that read routine while advancing the EEPROM address and
buffer by eight bytes. `conteepprobe` acquires SI access, checks the EEPROM type,
returns the 4K/16K selector, and releases SI access.

The long-read member has three direct callers in the reviewed game overlay;
the probe has one, and the long-read member directly calls the read member.
All outer endpoints are existing 16-byte map boundaries. The read helper ends
at the next object boundary, and no conditional branch escapes any object.

All three source files compile with the pinned IDO toolchain using `-O2 -g3`.
Removing `.mdebug` leaves text-only objects whose complete `.text` sizes are
exactly 608, 192, and 128 bytes. Relocation-masked comparison has zero differing
words across every byte, including final padding.

The read object binds its PIF RAM references to `0x800E0A30`, its local helper
within the same section, and the existing SI/status/message routines. The long
read binds its two wait calls to `0x151DCFD8` and its read call to the preceding
archive member. The probe uses the same SI and status helpers. The three
reproducible object MD5s are:

| Object | MD5 |
| --- | --- |
| `conteepread.o` | `e14bcc9fc7a6fc1ca98fd2912b101c2d` |
| `conteeplongread.o` | `d1dcffbfd94bfb3cdbe9a29e146e65f2` |
| `conteepprobe.o` | `57261b07854ed6940277f6d705224536` |

The canonical map now supplies all three ranges from `libultrare.a`. A refreshed
full-overlay link is byte-identical at 2,072,880 bytes with SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
