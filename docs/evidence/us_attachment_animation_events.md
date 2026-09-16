# Attachment ownership from animation events

`./conker model-assets constructors --bank 09` includes an `attachment_events`
report. It follows ROM animation routes and create/remove events without an
emulator or image comparison. The current US scan reads 1,472 event lists and
finds 226 events referencing 49 actions, with creation records for 45 distinct
bank-09 attachments. All examined lists have bounded time sentinels.

These are stored event references, not proof that gameplay reaches every
animation. The report grants no material binding, renderer context or gallery
eligibility. Its parent lists include the representative-character groups
selected by `1503D5F0`. Event lists absent from this path, tagged pointers and
other command protocols require separate evidence.

## Reviewed path

The source is the checksum-validated US ROM, SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. The scanner pins these consumers
against the decompressed executable, independently of current C work:

- `1503D660` loads indexed bank `0x0F` for the representative character and
  passes its route-record base, payload +`0x10`, to `1503D484`.
- `1503D484` visits eight-byte routes up to the `999` descriptor sentinel.
  `1503D438` adds the route-record base to nonzero, untagged event offsets.
- `1505E650` selects a logical animation's route. `1505E0C4` copies route
  +`4` to the actor's event pointer at +`0x1C4`.
- `1506AD30` reads 12-byte events: float time at +`0`, opcode byte at +`7`
  and a 32-bit argument at +`8`. It dispatches only times below `900`, via
  `800863FC + opcode * 4`. The event cursor at actor +`0x138` is one byte.
- Dispatch slots `800865A0/800865A4` select `15072DD8/15072E38` for opcodes
  `105/106`. Their argument is the attachment action. The reviewed
  `1505BB80–1505BC20` caller span sets the current event parent to the actor
  being processed and restores the previous parent afterward.
- `15083568` resolves a referenced action header at
  `80086CC4 + (action - 1) * 8`, then its count of 16-byte records. Kind zero
  modifies the parent and is not reported as a bank-09 model; kinds one and
  two select attachment constructors. The scanner follows only referenced
  headers and does not invent an extent for the whole action table.

The parser rejects truncated lists, invalid times, unaligned or tagged
pointers, out-of-range action data and lists that would wrap the byte cursor.
Unresolved lists stay explicit in the report; they never acquire guessed
owners or materials. The existing constructor report and batch journal retain
these results for subsequent investigations.

## Attachment 47: parent established, texture state unresolved

Bank `0x0F`, entry 88 has SHA-1
`2c037575f088563b64c2686db9037dbc46f3b3be` and two relevant routes:

| Logical animation | Descriptor segment / pair | Stored event offset | Resolved payload offset | Event |
| --- | --- | --- | --- | --- |
| 24 | 46 / 23 | `0x230` | `0x240` | time 1.0, opcode 105, action 74 |
| 25 | 48 / 24 | `0x248` | `0x258` | time 1.0, opcode 106, action 74 |

The parent is character entry 88, the gallery's SHC Soldier. This character
is not redirected through a shared route representative. Both event lists end
with time `999` immediately after the attachment event. This establishes the
stored create/remove relationship, not when the character enters either
animation in gameplay.

Action 74's header is `80086F0C = 8009D250 01000000`. Its record at
`8009D250` is `2F170001000000000000000000000000`: attachment 47, kind one,
updater zero. `15030AF4` clears descriptor +`0x18/+0x1A`, `15031A50` takes
its no-op initializer arm for model 47, and `15030468` skips updater zero.
At `1503179C–150317FC`, `150311C4` skips segment-6/7 rebinding when those
fields are zero, preserving earlier display-list state.

The attachment has 50 vertices and 36 faces. Its first 28 faces use flats
4198 and 4216. The last eight use segments 7 and 6, with 32 x 32, eight-bit
render tiles, pixels at offset zero and 256-entry TLUTs at `0x400`. Their raw
tile format is RGBA8; indexed decoding also needs the inherited TLUT state.

The SHC Soldier's no-expression, blink-zero defaults select descriptor 1 for
both segments. That descriptor selects flat 4200, a 40 x 40 image. Its normal
palette offset is `0x640`, not the attachment's `0x400`. Parent ownership
therefore does not justify copying the parent's default eyes into this model.

Submission order also matters. `1502BAD0` calls the global attachment passes
after its character loop; `15030E08` does not rebind the parent eye textures.
The parent-specific path through `15030F94` instead selects `15035D6C`, which
filters a separate draw-record list. Neither path supplies an unconditional
default texture for attachment 47. Keep it material-blocked until the selected
expression/texture state and segment lifetime for animation 24 are established.

The bank-`0x0E` 48-byte spawn records and both fixed spawn prefixes contain no
action 74 at byte `0x29`. The event report is the positive ownership evidence;
the spawn search is only a bounded negative result. Attachments 165 and 185
have no create/remove references in the scanned event lists.

The local current report is
`build/assets/models/batch/attachment47/constructors-bank09.json`. Focused
parser checks cover relocation, stop boundaries, invalid/truncated inputs,
cursor wrap, and the distinction between parent changes and attachments.


## Expression and saved-state follow-up

A fresh ROM audit closes the stored-expression shortcut. SHC Soldier's two
normal blink tables both contain descriptor indices `[1, 10, 12]`. Its two
stored expressions select `[1, 1]` and `[12, 12]`, with no action-program or
other texture overrides. Descriptors 1/10/12 select flats 4200/4203/4201;
each is 40 x 40 with 2,112 payload bytes and its palette at `0x640`.
Neither normal blinking nor either stored expression supplies the attachment's
32 x 32 layout with palette at `0x400`. Other 32 x 32 descriptors in the parent
model do not establish a selection for this attachment.

All 26 existing saved states were checked through the native attachment list:
head `800C3EE0`, older link `+0x54`, newer link `+0x58`, model byte `+1`,
parent ID byte `+0`, and texture halfwords `+0x18/+0x1A`. The audit validates
bounds, cycles and reciprocal links. Parent IDs are resolved through the
26 actor slots at `800CC2D0`, stride `0x32C`, following `15083E90`.
No saved list contains attachment 47. States 18–23 contain SHC Soldier in
slot 7 with blink codes zero and a null render pointer at `+0x1D4`; that is
not an observed attachment submission. The finding is bounded saved-state
absence, not proof that animation 24 or the attachment is unused.

### Alternate submission capture

The trace specification now covers the alternate per-parent submission write
at `15035F60` in addition to ordinary write `15031870`, pairing both with
outer renderer return `15031914`. `150311C4` branches on its fifth argument
at `15031808`; the nonzero branch calls `15035D6C`. That helper filters
12-byte draw records at `800C3F08` by kind 1 and matching parent ID, then
submits selected attachment parts with each record's matrix.

At the new hook, `$a1` is the attachment, `$t8` the selected list and `$s4`
the call command address. The helper's 32-byte frame saved the outer parent
`$s2` at stack `+0xC`. The outer renderer's saved command-buffer start is at
inner stack `+0xD4` (outer `+0xB4`). These probes preserve the same pairing
key as the outer return; the draw record is retained separately. The parser
rejects mixed ordinary/alternate hooks in one invocation. Every selected call
still requires a matching submitted graphics task, ROM list bytes, vertex
positions and the matrix bound at that call. Repeated parts at distinct calls
retain their separate matrices; repeated call addresses are rejected.

The new path passes focused synthetic submission tests and its instructions
are verified against the checksum-validated ROM. It has not received a positive
live alternate-hook capture. Only saved state 10 contains matching kind-1 draw
records, for other attachments; its previously failed debugger-prompt trace is
not repeated unchanged. A fresh state exercising animation 24 and attachment
47 is still needed to identify the preceding segment-6/7 writes and effective
TLUT state. No material binding or gallery promotion follows from this audit.

The reproducible audit and hashes are under
`build/assets/models/reference/attachment47-inheritance-20260916/`.
