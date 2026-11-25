# US scene preload and UI tables

Four data definitions reconstruct 288 bytes: a five-entry scene preload root
table (20 bytes), four terminated resource lists (160 bytes), decimal-rendering
tables (68 bytes), and two UI display lists (40 bytes). These are INFO verification
definitions; the original archive still supplies the runtime bytes. No function,
shared header, assembly, original object boundary or source-unit completion is
changed.

## Scene preload selection

The complete registered US spans of `func_15002FB4`, `func_1502B6BC` and
`func_150031EC` are checked against the checksum-validated ROM. The loader
selects bank `0x15`, loads the scene container at depth two, and stores its first
child in `D_800B0DF0`. The reader loads that child's byte `+0x4B`, skips zero,
and indexes the pointer table at `80082B20` with a four-byte stride.

All 67 nonempty original scene containers have the expected first-child
directory entry `(16, 76)`. Their decoded header selectors collectively cover
zero through four. The root prefix includes the stored null at index zero and
four genuine symbolic pointers. This establishes the stored prefix through
selector four, without asserting a universal bound for modified scene inputs.

The reader tests each resource word for zero, loads nonzero resources through
`func_1510D0EC`, and advances by four bytes. The original lists at `80090150`,
`8009016C`, `80090184` and `800901C4` contain respectively seven, six, sixteen and
eleven words including their terminators. They cover 160 contiguous bytes.
List lengths follow the native terminators, not neighbouring labels.

## UI decimal rendering and graphics

The complete 624-byte `func_151EADFC` span clamps its input to 0..9,999,999,
copies seven original power-of-ten words from `8009009C`, and processes them
in descending order using division and remainder. This bounds each texture
lookup digit to 0..9, establishing ten resource words at `80090074` and seven
power words. Arithmetic boundary checks supplement the native evidence.

The complete 880-byte `func_151EDBDC` span submits the graphics lists at
`80090110` and `80090128` using native `DE` display-list commands. The paired
command/pointer stores and the command register reload after the intervening
call are checked. Both original lists terminate with `DF`. SDK GBI2 macros
reproduce the pipe sync, texture enable/disable and list-end commands: three
commands followed by two commands, 40 bytes total.

This proof concerns stored data and its native consumers. It does not claim
that every scene or rendering path has been observed running. Nearby sprite
descriptor bytes remain excluded where their field meaning is unresolved.

## Validation

Base commit: `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7`, plus uncommitted work.
The actual pinned-compiler pilots and independent native references reproduce
288 bytes and four symbolic pointers. Thirty-two compiler tail bytes are
excluded. All 816 prior GAME objects retain identical allocated bytes, symbols
and relocations. All 296 native negative checks reject changes (288 payload
bytes, four pointer destinations and four pointer addends). The independent
ROM-byte verifier also rejects all 288 payload mutations.

The full suite passes: 3,033 tests, eight skips, 270.416 seconds. The US asset
build passes in 188 seconds including setup (183.064 seconds build,
160.310 seconds compile/link/verify). Independent extraction confirms all
67,108,864 linked ROM bytes, SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`.

The full report accepts exactly 288 additional bytes: 63,322,447 / 65,120,512
matched, with 1,798,065 remaining. Complete-data, code and function measures
are unchanged. All 27,301 prior asset inputs and 11,836 asset objects are
preserved. Preparation took 416.5 seconds and validation 27.1 seconds.
Report SHA-256:
`257ecfee793a76929ea88f9737f9cac9fb1487a2a134868c99d0a0461d248640`.

The accompanying JSON records native spans, instruction anchors, original
scene selectors and pilot evidence. Temporary scripts and snapshots are under
`build/us/data-completion/scene-ui-*`.
