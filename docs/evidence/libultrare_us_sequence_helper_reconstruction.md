# Conker US sequence, heap, bank and oscillator helper reconstruction

This library-only pass adds four complete objects, 31 functions, and 8,320
text bytes. The active search now accounts for 20 integrated objects,
89 functions, and 36,528 text bytes. Earlier evidence retains its historical
checkpoint counts. No ordinary game-code source is included.

| Member | ROM text interval | Bytes | Functions | Complete compiler-object MD5 |
| --- | --- | ---: | ---: | --- |
| `audio/heap.o` | `0x12820:0x128D0` | 176 | 2 | `74b5ddf918b8072d3081b9032bba47be` |
| `audio/bnkf.o` | `0x128D0:0x12D80` | 1,200 | 7 | `aee437d015688f68249b2d99e2075241` |
| `audio/osc.o` | `0x12D80:0x13320` | 1,440 | 5 | `700cf6de91ec4b7894d950acfe41472d` |
| `audio/n_seqplayer.o` | `0x1AAE0:0x1C060` | 5,504 | 17 | `f4e020682275d622ab17653b1dd1738d` |

## Complete-object evidence

Perfect Dark revision `169ed48bdcbfb3b568b028bd5bebb27680073514` supplies the
independent source families `src/lib/ultra/audio/{heap,bnkf}.c` and
`src/lib/naudio/{n_seqplayer,osc}.c`. The reconstruction uses the established Conker
IDO `-O1 -g2` settings, removing only non-runtime `.mdebug` build metadata.
These are Conker/Rare reconstructions, not claims that the pinned stock SDK
archive objects match. Filenames describe the source families, not proven
original Conker filenames.

Each complete compiled text section has one occurrence in the owned US ROM
when scanned across the main executable. Every relocation is resolved to its
reviewed address before exact byte comparison, including all internal calls,
function order, and alignment. The heap, bank and sequence-helper objects own text only: no data,
rodata, nonempty BSS, or COMMON storage is present. The oscillator owns the
complete rodata and BSS sections described below. None allocates COMMON. No staged runtime-pointer preparation is required for these objects; the
oscillator uses explicit runtime callback aliases.

The canonical map consumes whole members. The raw comparison map remains
unchanged. The old `alHeapDBAlloc` alias is removed because `heap.o` now
provides the definition. The newly reconstructed bank sound patcher likewise
provides the sequence helper's real call target.

## Sequence helper behavior

The first fifteen source-family helpers retain voice allocation/release,
lookup, volume/mix/pan calculation, and channel initialization. Conker adds
instrument acquisition and release wrappers before oscillator cleanup, for
seventeen functions in this object. The callbacks load through reviewed
synthesizer fields; their names remain neutral where the broader contract is
not yet established.

The exact voice layout has client-private data at voice +0x10 and Conker's
additional release data at +0x14. Voice-state objects consequently contain the
sound pointer at +0x24, envelope time at +0x28, and status bytes at +0x34:0x3C.
The channel stride is 0x3C. Existing field views were expanded with verified
members, preserving all earlier offsets and every previously pinned object's
hash. Event views retain 16-byte storage with typed Conker voice pointers.
Oscillator event IDs are Conker's 23 and 24, not the stock enum values.

The ROM's instrument initialization acquires the selected bank slot, releases
any previously assigned slot through the synthesizer callback, patches sounds
whose envelope fields still contain small offsets, and copies the instrument
and envelope settings into the channel. It records the signed instrument index
at channel +0x38 and failure byte at +0x36. The acquisition wrapper validates
returned pointers against `0xFF000003 / 0x80000000`. Sound lookup handles a
null instrument. Default-channel initialization retains Conker's assignments
and omits the stock effect-ID member. These changes come from raw accesses
and branch behavior, not a near-match assumption.

Three compilations resolved the complete object: source-family reconstruction,
replacement of out-of-line list calls with the already reviewed scoped C list
operations, then removal of an unnecessary explicit return. No instructions
or target assembly were edited.

## Heap and bank relocation

The heap object contains initialization at `0x12820` and aligned allocation at
`0x12844`. Its complete first candidate matches, including the eight bytes of
final section padding. The source initializes the base, length, cursor and
count, rounds allocation size to 16 bytes, and returns null on exhaustion.

The bank object contains sequence-file relocation at `0x128D0`, bank-file
initialization at `0x12934`, bank relocation at `0x12A28`, percussion relocation
at `0x12B84`, instrument relocation at `0x12BD0`, sound relocation at `0x12C5C`,
and wave relocation at `0x12CFC`. Its complete first candidate matches.

Conker adds an encoded bank address argument. Each bank's first instrument offsets
are relocated directly; later instruments and percussion sound addresses use
`(address & ~7) << 5`. The wave patcher omits the stock early flags return and
clears Conker's ADPCM field at wave +0x14. That field remains neutrally named.
All affected structure accesses, call targets and conditionals match the ROM.

The complete bank object ends at `0x12D80`, a 16-byte boundary immediately
following the source family's final wave helper. The next function belongs to
the independently identified oscillator family. The canonical map now links
two whole library objects across the original raw `0x128D0` navigation unit;
the comparison map remains unchanged. Both complete text sections resolve
exactly and each has one occurrence.

## Oscillator family and nontext ownership

The oscillator object contains depth-to-cents conversion at `0x12D80`,
initialization at `0x12E04`, update at `0x12F94`, stop at `0x131D8`, and pooled
allocation/callback setup at `0x131FC`. Its first complete candidate matches.
Conker supports the basic tremolo and vibrato types here; PD's alternate-type
handlers are absent. The state layout is 0x2C bytes, with count/period at
+0x24/+0x22 and tremolo or vibrato values at +0x28. The setup routine allocates
states from the audio heap, constructs the free list, and installs all three
callbacks. The depth and full-circle constants reproduce the complete 16-byte
rodata section at `0x2C450:0x2C460`, including padding.

The object allocates two pointer globals: free-list head at BSS +0 and pooled
state-array pointer at +4, with a complete aligned extent of 16 bytes. Their
resolved addresses are `0x80042800` and `0x80042804`. The canonical map assigns
only `0x80042800:0x80042810`; following storage remains raw until the separately
matched surround object at `0x800428C0`. BSS has no ROM bytes: ownership rests
on source-family grouping, the compiler's complete allocation, all raw address
references, and preserved neighboring RAM extents. The state array itself is
heap-allocated and has no static BSS allocation.

The three installed callback pointers use main runtime addresses
`0x10012E04`, `0x10012F94`, and `0x100131D8`, supplied through explicit link
aliases. The sine call uses the game-library target's main-PC JAL alias
`0x85047D60`; `alCents2Ratio` and `alHeapDBAlloc` resolve to real archive
members. Whole-object comparison resolves these relocations before comparing
all text and rodata bytes against the owned ROM.

## Remaining library leads

Sequence/player engines at `0x13320:0x17870` and MIDI/channel controls at
`0x19B50:0x1AAE0` remain raw.
Formatting, MP3 CPU library routines in the game overlay, and bounded RSP
microcode also remain. Library work is not exhausted; game-code matching is
outside this goal's current scope.

## Integration checks

The first complete sequence-helper, heap and bank builds were byte-identical.
The initial oscillator integration failed the full ROM gate: 258 bytes differed.
The generated linker script showed the residual raw range `0x2C460:0x2C750`
classified as `.data`, which Splat grouped ahead of the new oscillator rodata.
That moved the oscillator constants to `0x2C740` and shifted the raw tables.
Candidate work stopped while this failure was diagnosed.

Classifying the remaining raw constant tables as `.rodata` preserves the
linker's section order and the reviewed oscillator placement. No source
instructions, target assembly, or ROM bytes were patched. A regression check
now rejects `.data` entries following `.rodata` in the main profile.

The corrected section type also exposed four raw jump-table labels that
required explicit runtime bindings: `0x100135E8`, `0x100140BC`, `0x10014B14`,
and `0x10015D84`. These remain aliases into raw library code; no ownership or
match credit is assigned to their containing functions. The oscillator rodata
SHA-1 is `4023db37c769ba68a46844b1e257043ad0f20f22`.

After both diagnosed linking corrections, `./conker build --profile us`
reports `build/us/conker.us.z64: OK`. The complete 67,108,864-byte ROM has
SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`. All twenty objects from the
active search pass independent complete-text and allocated-nontext comparison.
The canonical main profile now links 137 unique library objects through
170 sections; main and game maps total 87,152 exact library text bytes.

After the shared sequence/voice/channel layout changes,
`./conker game-build --profile us` reproduced the 2,072,880-byte game payload,
SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. The later oscillator object
and aliases are staged only into the main archive; the game archive's pinned
members are unchanged. This validation adds no game-code implementation.
All 157 repository tests pass, `./conker progress check` reports current
output, and `git diff --check` is clean. Pre-existing staged and dirty work
remains preserved.
