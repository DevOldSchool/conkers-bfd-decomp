# Conker US compact-sequence engine reconstruction

This library-only pass adds two complete objects, nine functions and 8,832
text bytes. The active library search now accounts for 23 integrated objects,
118 functions and 49,344 text bytes. Earlier evidence files retain their
historical checkpoint counts.

| Member | ROM text interval | Bytes | Functions | Compiler-object MD5 |
| --- | --- | ---: | ---: | --- |
| `audio/n_csplayer.o` | `0x13320:0x15550` | 8,752 | 8 | `53f3e26783a1dab0814ccc0f2b047cf8` |
| `audio/n_cspsetbank.o` | `0x15550:0x155A0` | 80 | 1 | `fddc846f5d5e3ed215468f59db584a3b` |

## Complete-object and boundary evidence

Perfect Dark revision `169ed48bdcbfb3b568b028bd5bebb27680073514` provides the
independent source families `src/lib/naudio/n_csplayer.c` and
`src/lib/naudio/n_cspsetbank.c`. Conker's raw instructions establish the
differences described below. Both objects use the existing IDO `-O1 -g2`
configuration, with only non-runtime `.mdebug` metadata removed. These are
Conker/Rare reconstructions, not stock libultra matches. Source-family names
do not establish the original Conker filenames.

All eight sequence-engine functions match in their complete original order:

| ROM start | Function | Bytes |
| --- | --- | ---: |
| `0x13320` | `n_alCSPNew` | 632 |
| `0x13598` | `__n_CSPVoiceHandler` | 2,736 |
| `0x14048` | `__n_CSPHandleNextSeqEvent` | 276 |
| `0x1415C` | `__n_CSPHandleMIDIMsg` | 3,816 |
| `0x15044` | `__n_CSPHandleMetaMsg` | 716 |
| `0x15310` | `__n_CSPRepostEvent` | 340 |
| `0x15464` | `__n_setUsptFromTempo` | 72 |
| `0x154AC` | `__n_CSPPostNextSeqEvent` | 152 |

The complete text includes twelve final padding bytes. Its resolved SHA-1 is
`cda6f2992441dde6064cd0bf2e85c2b38a79d7a4`; the whole template has exactly one
occurrence in the main executable, at `0x13320`. The 80-byte bank-change
object likewise occurs only at `0x15550`. Its boundary is supported by the
independent one-function source unit, complete compiler extent and following
sound-player constructor at aligned address `0x155A0`. The raw comparison map
continues to hold both functions in its existing assembly block.

The sequence engine owns the following complete nontext sections:

| Section | Interval | Bytes | Resolved SHA-1 |
| --- | --- | ---: | --- |
| `.data` | ROM `0x2BA50:0x2BBE0` | 400 | `e3f9ba8d69beeb631bc97a403a4963b5320cc089` |
| `.rodata` | ROM `0x2C460:0x2C6B0` | 592 | `badc339c29f3bf60759ac8b52c2f259fdd3b1bc9` |
| `.bss` | RAM `0x80042810:0x80042850` | 64 | NOBITS; no ROM payload |

Data contains a 93-entry control dispatch table and a four-entry high-control
table, followed by alignment. All eighteen non-null entries target functions
in the already exact channel-control object. The high controls select the
four fade operations with index `255 - controller`. The rodata consists of
three compiler jump tables with 27, 21 and 97 entries, then twelve padding
bytes. The BSS allocation is exactly sixteen channel note-duration words:
its references, compiler allocation and neighboring RAM bounds agree. There
is no COMMON allocation. The bank-change member owns only text, with no
data, rodata, BSS or COMMON storage.

All 277 sequence-engine relocations are reviewed: 94 text calls, ten HI/LO
pairs, eighteen data pointers and 145 rodata jump-table pointers. Independent
comparison resolves every relocation and compares all allocated ROM bytes,
including padding. The canonical map consumes complete archive sections;
target assembly and raw comparison mappings remain unchanged.

## Conker behavior and type views

Conker inserts pause event 16 and uses player state 3 for paused playback.
Pause removes queued sequence-reference events and records the returned delta
at player +0x88. Resume restores that delta. Stopping handles both playing and
paused states, releases remaining voices and instrument references, and
restores channel fade masks. The empty debug branches visible in the ROM are
retained as C control flow.

MIDI processing retries events after 33,333 microseconds while a channel's
instrument acquisition is pending. Program changes invoke the already
matched instrument-index helper and schedule a retry when needed. Voice
allocation uses Conker's extra release-data member. The source preserves the
seven-argument oscillator callback call sites; the ordinary oscillator may
ignore the additional time-index argument. Sustain begins at value 64.
Suppressed note-ons and regular note-offs retain their distinct event types.
The bank-change wrapper posts event 14 with Conker flag 2.

The shared player view now exposes the next event at +0x38 and paused delta
at +0x88 without changing any existing offsets. The player's event dispatch
loads an unsigned halfword, whereas queued events use signed halfword loads;
separate event views preserve both proven access patterns and the common
16-byte storage layout. Four compilations resolved the sequence engine:
source-family reconstruction, event/default corrections and two effects-loop
forms. The final form reproduces the raw loop's reload and branch behavior.
The bank-change wrapper matched on its first compile. Previously pinned
library objects retain their hashes after the shared-header rebuild.

## Link integration

Conker links main code at `0x80000000` while its callback and jump-table
pointers use the `0x10000000` runtime mapping. A staged copy of the compiler
object passes through the existing `prepare_main_library_object.py`, with
exactly 145 code-pointer relocations expected. Only their allocated-rodata
addends are rebased; text instructions, relocation records, symbol values,
section extents and the pinned original compiler object are unchanged.

The voice-handler callback and eighteen control-table pointers use link
aliases derived from their real definitions minus `0x70000000`. Three old
raw jump-table-label bindings are retired because this object now owns their
tables. The sound player's remaining raw table binding is preserved.

The first integration link reported an undefined `n_alSynAddSeqPlayer`.
This checkout already provides its verified call target under the neutral
name `__conker_audio_add_player_2`, at `0x8001C700`. A symbol-to-symbol alias
resolves that existing definition; no instruction or address extent changes
were needed. The corrected sequence-engine build reproduces the full US ROM.

## Verification

After adding the bank-change wrapper, `./conker build --profile us` again
reports `build/us/conker.us.z64: OK`. The complete 67,108,864-byte ROM has
SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`. The canonical main map now
links 140 unique library objects through 176 sections, with 83,456 exact
library text bytes. Main and game library mappings together contain 99,968
exact text bytes. No function inventory entries were added or retired: these
raw ranges had no registered work items or source units.

All 23 complete objects from the active search pass the independent text and
nontext comparison. All 157 repository tests pass, generated progress is
current and `git diff --check` is clean. Existing staged and dirty user work
remains preserved.

`./conker game-build --profile us` also reproduces the existing integrated
payload after the shared event-view changes: 2,072,880 bytes, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. This verifies existing overlay
library integration without adding game-code implementations.

## Remaining library work

The raw sound-player object begins at `0x155A0` and continues to `0x17870`.
The first function at the old `0x15550` boundary was the separately matched
bank-change wrapper. Formatting helpers, MP3 CPU library routines in the game
overlay and bounded RSP microcode remain additional leads. The library search
is active; ordinary game-code matching is outside the current goal scope.
