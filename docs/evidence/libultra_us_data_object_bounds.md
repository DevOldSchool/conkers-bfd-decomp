# US libultra initialized-data object boundaries

This note records five complete stock-library data sections found by extending
the I-L residual scan beyond `.text`. All five are built from C in the bounded
`libultrare` snapshot and are byte-identical in the complete US ROM.

## Evidence and boundaries

The scanner compared every non-empty loadable `.data` and `.rodata` section
from I, J, K, and L `libultra`, `libultra_d`, and `libultra_rom` objects. Each
range below was the only raw occurrence of its complete relocation-masked
section before integration.

| US ROM range | Size | Stock identity | Built source | Complete object MD5 |
|---:|---:|---|---|---|
| `0x2AAF0:0x2AB40` | `0x50` | `xprintf.o .data` | `src/libultra/libc/xprintf_data.c` | `2afe0878a3d6bd9a4019c7f38505d57d` |
| `0x2B9D0:0x2B9E0` | `0x10` | `syncputchars.o .data` | `src/libultra/os/syncputchars_data.c` | `891f7cd450c961a9ad4917a786b86baa` |
| `0x2BF20:0x2BF80` | `0x60` | `xldtob.o .rodata` | `src/libultra/libc/xldtob_data.c` | `b8c6ef63c44197b1d22b820dbdb0b87f` |
| `0x2BF80:0x2C080` | `0x100` | `xprintf.o .rodata` | `src/libultra/libc/xprintf_rodata.c` | `37e3c3a5defdf8a75cbfc88d1667d528` |
| `0x2C1B0:0x2C200` | `0x50` | `exceptasm.o .rodata` | `src/libultra/os/exceptasm_data.c` | `9e97a8327d7b576ca80f0234f2b2492d` |

The `xprintf` initialized strings are the 32-character space and zero pads.
Its read-only section contains the qualifier/flag tables and the complete
`_Putfld` switch table. The latter is relocated to Conker's `0x10000000`
execution aliases, so the local source records the target values while the
nonmatching Rare formatting text stays raw.

The `exceptasm` section contains the 32-byte interrupt-offset table followed
by the nine-entry handler table. Its handler addresses likewise use the target
execution aliases while the exception body remains raw. `syncputchars` owns
the initialized debugger state words `__osRdbSendMessage` and
`__osRdbWriteOK`.

## Build representation

The original SDK classifications are shown in the table. The three original
`.rodata` payloads are emitted as dedicated initialized-data archive members in
this project because Conker interleaves them with a larger raw data block;
placing them in the linker's later aggregate `.rodata` output would move the
bytes. This is a build-layout adaptation, not a claim that the stock objects
used a different section.

Every reconstructed section was compared directly with the target range before
linking. `lib/libultrare/object-md5s.txt` pins each complete build object, and
`./conker build --all` finishes with `build/us/conker.us.z64: OK`.

These five initialized sections total `0x210` (528) bytes. They are genuinely
produced by the archive build, but they do not increase the code progress
metrics because those metrics intentionally count executable `.text` bytes.
