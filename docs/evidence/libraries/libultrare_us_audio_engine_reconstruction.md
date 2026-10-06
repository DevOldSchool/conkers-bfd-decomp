# Conker US audio-engine library reconstruction

This library-only pass reconstructs five complete Rare audio objects: 16,656
text bytes and 24 functions. Together with the preceding eleven-object pass,
the active library search has integrated 16 objects, 58 functions, and 28,208
text bytes. No ordinary game-code source was implemented.

## Complete object bounds

Every reconstructed text template has exactly one occurrence in the owned US
ROM. Comparison resolves each relocation and includes padding, rather than
accepting masked instructions or selected matching functions. The independent
`config/reference/us.yaml` remains raw assembly/data/BSS. Source-family names
identify the reconstruction; they do not assert original Conker filenames.

| Member | Main ROM text interval | Bytes | Functions | Complete compiler-object MD5 |
| --- | --- | ---: | ---: | --- |
| `audio/alsurround.o` | `0x17870:0x17A80` | 528 | 2 | `db931ce5ab63b42d027c77f379be2c4c` |
| `audio/n_csq.o` | `0x17F80:0x18C60` | 3,296 | 7 | `97fb7d3d4f1fc363152641d50f2d5839` |
| `audio/n_reverb.o` | `0x1E530:0x1FB40` | 5,648 | 7 | `1b2e13269fc7d943f18fb0a222fdf1d5` |
| `audio/n_env.o` | `0x20000:0x210C0` | 4,288 | 5 | `f84fbccbbc51a836c00b12e46e283396` |
| `audio/n_load.o` | `0x214F0:0x22040` | 2,896 | 3 | `c56646bd5b486b23b8bd046eee2df286` |

All use the established IDO `-O1 -g2` library settings. The build removes only
non-runtime `.mdebug` hostname/time metadata before pinning these compiler
objects. Reverb and envelope then require the separately described linker
preparation; their table lists the original, reproducible compiler objects.

Perfect Dark revision `169ed48bdcbfb3b568b028bd5bebb27680073514` provides
independent source-family references under `src/lib/naudio/` and
`src/lib/alsurround.c`. Conker's raw code, data, call sites, and structure
accesses determine the changes described below.

## Runtime behavior and member order

`alsurround` contains output-mode selection at `0x17870` and reverb setup at
`0x17944`. The first candidate matches both functions and final alignment.
The four-byte output structure and consecutive routing, inversion and saved
mode arrays reproduce the source-family allocation and every raw reference.

`n_csq` contains sequence initialization at `0x17F80`, next-event selection at
`0x18100`, track-event decoding at `0x182A8`, marker restoration at `0x186DC`,
loop-marker collection at `0x18790`, byte decoding at `0x189D0`, and variable
length decoding at `0x18BC4`. Conker omits the reference's get-ticks, get-location,
and single-marker creation functions. The standard `ALCSeq` and marker layouts
match. Track-end/loop-start/loop-end use Conker IDs 19/20/21. Unlike the reference,
next-event initializes the selected track to `0xFFFFFFFF` and emits track-end
when none is found. The second complete candidate reproduces that guard and
matches all seven functions, including internal calls and padding.

`n_reverb` contains the reverb pull, parameter dispatch, output-buffer loading,
circular-buffer loading/saving, filter commands, and modulation helper. Conker
uses the first effect pointer at auxiliary-bus +0x1C, starts the pull count at
zero, and uses the reviewed Conker driver and delay layouts. Routing and
inversion select paired delay buffers; command-buffer constants and mix order
match the ROM. The first complete source candidate matches all seven functions.

`n_env` contains envelope pulling at `0x20000`, parameter dispatch at `0x20978`,
subframe pulling at `0x20ABC`, rate calculation at `0x20E18`, and volume
calculation at `0x21028`. Conker retains two low control bits in dry/wet amounts,
uses output surround/mono/headphone flags, and updates the wave-table byte at
+0xA. The field remains neutrally named because its meaning is unproven.
Unsigned sample offsets reproduce rounding, while signed parameter types and
counts retain their raw arithmetic. Removing an unnecessary unsigned cast
from the switch selector produced the exact second complete candidate.
The shared start-parameter declaration was moved into the library header;
all previously pinned objects retain their hashes.

`n_load` contains ADPCM pulling at `0x214F0`, parameter handling at `0x21C40`,
and chunk decoding at `0x21E4C`. Conker clears the buffer for a null wave,
checks the ADPCM book address, records fault `0x0F000003`, and calls the
existing fault handler when the physical address is invalid. A failed DMA
resets the envelope/decoder state and returns the current command pointer.
The RAW16 branch is absent, and reset clears the loop count. The first complete
candidate matches all three functions. The fault word at `0x8003C8E0` remains
external storage; this object does not claim its allocation.

## Nontext ownership

| Member | Section | Exact interval | Extent |
| --- | --- | --- | ---: |
| `alsurround` | BSS | RAM `0x800428C0:0x800428D0` | 16 |
| `n_reverb` | rodata | ROM `0x2C7A0:0x2C7D0` | 48 |
| `n_env` | data | ROM `0x2BC10:0x2BD10` | 256 |
| `n_env` | rodata | ROM `0x2C7D0:0x2C820` | 80 |

The surround BSS section is 16-byte aligned and contains the output structure
at +0 (4 bytes), routing at +4 (2), inversion at +6 (2), and saved bus modes at
+8 (4), followed by compiler alignment. All referenced addresses match the raw
functions and the already reconstructed mixer/reverb. The separate raw 16-byte
gap at `0x800428D0:0x800428E0` remains outside this object, followed by the exact
`initialize.o` BSS. BSS has no ROM bytes: the evidence is the compiler allocation,
source-family grouping, all resolved references, and preserved surrounding RAM
boundaries, not a claimed binary-data comparison.

The envelope data is the complete 128-entry signed-16-bit equal-power table,
ending exactly at `initialize.o` data. Reverb and envelope rodata contain their
constants, compiler switch tables, and alignment. Every initialized byte matches
the owned ROM. The loader and compact-sequence objects own text only. No other
object in this pass allocates nonempty BSS or COMMON storage.

Resolved section SHA-1 values:

| Section | SHA-1 |
| --- | --- |
| reverb rodata | `327c346e09f437813ea9cc3872fc84e0bf22f931` |
| envelope data | `6fb73c35507117ea26e2fcc6ed3eab80325be573` |
| envelope rodata | `1295309377660b2ff837355ad70deccbcd6670e6` |

## Main runtime address alias

The main link uses `0x80000000` addresses while executable main pointers use
`0x10000000`. JAL instructions encode the low address bits, but compiler
switch tables contain full pointers. A normal relocation against the main
link address would give those tables the wrong upper bits.

`scripts/prepare_main_library_object.py` stages separate copies of the reverb
and envelope objects. It adjusts only `R_MIPS_32` REL addends in allocated,
non-executable data whose symbols are defined in executable sections. The
delta is `-0x70000000`; exactly eight reverb and seventeen envelope entries
must qualify. It does not rewrite instructions, symbols, relocations, section
extents, or unrelated data and does not copy bytes from the ROM. The script
validates ELF class/endianness/type, bounds, entry formats, pointer alignment,
and duplicate relocations, and rejects in-place modification.

The prepared copies independently match the complete ROM sections when audited
with ordinary main-link `.text` addresses. Their complete-object MD5s are
`9c1d297b35dbe4be7cc238216f0b48ef` (reverb) and
`bb5abd2aa2c0223fdf70b5a42737116e` (envelope). The source objects remain intact.
The canonical archive links those complete prepared members. Former raw
function and switch-label aliases are removed; only documented external or
runtime aliases remain.

## Remaining library work

The sequence/player engines around `0x13320:0x17870` and
`0x19B50:0x1C060` remain raw library leads. The compact-sequence parser in the
formerly listed `0x17F80:0x18C60` range is now resolved. Formatting `xldtob`
and `xprintf`, MP3 CPU code in the game overlay, and RSP microcode also remain.
This checkpoint does not claim that the library search is exhausted.

## Verified integration checkpoint

With all five objects mapped, `./conker build --profile us` rebuilt the full
64 MiB US ROM and reported `build/us/conker.us.z64: OK`. Its SHA-1 remains
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. No ROM checksum failed during this
pass. The canonical main map now links 133 unique library objects through
164 mapped sections. Main and game mappings total 78,832 exact library text
bytes; the active search remains library-only.

`./conker game-build --profile us` also reports
`build/game-integrated/us/conker.game.us.integrated.bin: OK`: 2,072,880 bytes,
SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. This verifies that shared
library changes preserve the existing overlay payload; it adds no game code.
All 156 repository tests pass, including five tests of code-pointer preparation.
`./conker progress check` reports current generated output, and
`git diff --check` is clean. Existing dirty/staged work is preserved.

The subsequent [sequence helper pass](libultrare_us_sequence_helper_reconstruction.md)
resolves `0x1AAE0:0x1C060` and the heap/bank-relocation families at
`0x12820:0x12D80`. The earlier checkpoint counts above are historical.
