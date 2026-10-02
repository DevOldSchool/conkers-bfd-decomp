# Particle callback storage matching and raw-ABI follow-ups (US)

## `func_150B2570`, `game_DF930.c`

The existing reviewed callback has a full 15-word input contract. The raw body
homes a0-a3, reads float coordinates from input words 2-4, the direction from
word 8, and the byte selector from word 14. Unused intervening words remain
full-width parameters; they are not removed from the ABI.

A working 0x3C-byte particle packet expresses the actual position, velocity,
color, lifetime and sprite fields. The first candidate scored 1070. Placing
the used scale scalar before the packet recovered the original local layout.
Explicit byte angle conversions recovered the original integer argument
sequence. Separating the sine call from its multiplication by 10.0f recovered
the original floating operand order. The second candidate passed full-span
`CURRENT (0)` for all 464 registered bytes.

The required source-unit transition moved the unit to
`src/done/game/game_DF930.c`. Full integrated US game code and mapped external
rodata remained byte-identical. The clean boundary batch returned
`BATCH_COMPLETE`, with 1,068 tests passing, 12 skipped, and metadata,
generated-progress and whitespace checks passing. No assembly, compiler flags,
shared headers, artificial padding or volatile accesses were added.

## Corrected callback contract candidate

`func_151572D0` in `game_1844C0.c` previously retained a 3363 candidate because
live a1/a2 were assumed to be callback arguments. The independent caller instead
shows its owner pointer and stopped byte saved/restored around calls. Every
target of the two relevant tables consumes only its first argument.

Checksum-validated retail table words are:

- `0x8008AD90`: `15157AA8`, `151BECB8`, `151B8C54`, `150FB29C`
- `0x8008ADA0`: `15157860`, `15157918`, `151BEB20`, `151D6E60`,
  `150FB188`, `15157DC8`, `150C52CC`

Six targets already have matched one-argument definitions. The other raw bodies
also overwrite or ignore incoming a1/a2. The raw cleanup helper `1503F4B0`
overwrites them at `1503F4DC` and `1503F4E0`, before any read. Relevant caller
and target references are `reference/game/us/asm/157010.s`, `1BEB20.s`,
`3F4B0.s`, and `asm/nonmatchings/game_127060/func_150FB188.s`.

Corrected source-local contracts with nested callback-result tests improved
3363 to 2291. Narrower scopes scored 2511 and were discarded. The second
callback still runs if the first changes the stopped flag. Register allocation,
byte spills and control scheduling remain different, so the corrected candidate
is deferred and contributes no match. No artificial save/restore locals were
introduced merely to force stack layout.

## Raw items excluded from the ordinary C loop

The supported `block-raw` transaction preserved these original sources unchanged:

- `func_150A7790` uses `cvt.w.s`, whose rounding follows FCSR, for all sixteen
  matrix components. m2c emits ordinary C integer casts, which truncate instead.
  No evidenced supported high-level rounding intrinsic is available in this
  pass; substituting truncation or changing compiler flags would be invalid.
- `func_150AA644` is a custom-register geometry span with an interior exported
  entry, incoming f3-f12/v1 state and return addresses retained in t9/t8.
  The ready step cannot interpret its nonstandard return as ordinary C.

These are queue blockers, not new C matches or original-assembly proof claims.

## Independently checked sibling `func_150B3C0C`

The 452-byte sibling in `game_E0F60.c` uses the same packet but two supplied
angles, distinct constants and two submission calls. Its old 1478 candidate
had exhausted address-spelling probes. Applying explicit byte conversions,
separating the sine result from its multiplication, and placing the used scale
before the packet restored the exact local offsets and improved it to 520.

The remaining difference was an unnecessary saved/reloaded packet address.
Both source-local submission declarations treated the packet as an integer.
The independent `func_15156190` saves incoming a0 as its packet pointer and
reads its fields; `func_15156388` forwards that pointer unchanged. Declaring
those first parameters as `void *` and passing `&particle` directly removed the
integer-expression spill and produced full-span `CURRENT (0)`. This is a new
argument-type correction, not a repeat of the earlier address-spelling probes.

The source unit moved to `src/done/game/game_E0F60.c`. Its required clean
boundary batch returned `BATCH_COMPLETE`: full US game code and external
rodata identical, 1,068 tests passing with 12 skipped, and metadata, progress
and whitespace gates passing. The two related callbacks add 916 verified bytes
and complete two reviewed source units.
