# Remaining model material evidence

Current US investigation targets, checked 16 September 2026. These findings
do not grant export eligibility; scene publication is tracked separately.
The checksum-validated ROM is `4cbadd3c4e0729dec46af64ad018050eada4f47a`.

## Resolved decoder gap: bank-09 entry 110

`09:0110:00` now has complete material coverage: all 20 faces, including the
last eight that previously reported `no-proven-texture`. A four-bit selected
tile retains earlier TMEM indices while using one bank of the latest full
256-entry palette. The shared replay now preserves lower TMEM across a
16-entry palette upload and retains the full palette for four-bit fetches.
See [the exact loads and independent pixel check](us_partial_tmem_loads.md#four-bit-tile-with-a-full-palette-entry-110).
The remaining material frontier contains **26 records**. Native appearance
and runtime attachment placement are separate from this texture fix.

## Short RGBA16 loads

The five `direct-rgba16-full-payload-unresolved` records are two distinct
segments. Their failure is a source-span conflict, not missing support for an
ordinary complete RGBA16 image.

| Model records | Flat asset | Available bytes | Requested bytes | Distinct geometry |
| --- | ---: | ---: | ---: | --- |
| `03:0038:00` | 882 | 2,560 | 4,096 | 50 vertices, 39 raw triangle records |
| `04:0005:00`, `04:0008:00`, `04:0032:00`, `04:0037:00` | 2814 | 2,560 | 4,096 | One identical 25-vertex surface, 36 raw triangle records |

Raw triangle records include degenerate records and are not gallery face
counts. The four bank-04 segments are byte-identical, including all 840 bytes
of geometry, commands and auxiliary data; their SHA-1 is
`eb08ec3a86b9f2fd77390945dae46197530cd7f2`. Each is a flat grid at Y=0,
with X and Z bounds -10,000 to 10,000. Their initial scene slot is zero.
The scene-consumer report contains no placements for these four scenes and
no placed-object association for bank-03 entry 38. This does not establish
that the records are unused.

Each failing material has one texture load and no preceding load whose bytes
could fill the short source. Its stored commands include:

```text
FD100000 <flat ID>         RGBA16 image
F5100000 07000000          RGBA16 load tile, TMEM base zero
F3000000 077FF000          2,048 16-bit texels, DXT zero
F5101000 00018050          RGBA16 render tile, 64-byte row stride
F2402402 0047E4FE          32 x 64 tile bounds
```

The requested span exceeds the asset by 1,536 bytes. Both stored OtherMode
states disable TLUT: `EF182C2F C8112078` for bank 03 and
`EF082C3F 00552078` for bank 04. The payload hashes are
`b57d880a5b8f923e8da6f32d791ca828aab6c2af` (882) and
`8e870c76eaafd6481ae5a346efa8189490e1afe8` (2814).

Other ROM lists independently establish flat 882 as a 32 x 64 CI8 image with
2,048 index bytes and a trailing 512-byte palette: bank-09 entries 196 and
197 explicitly select CI8, load 2,048 bytes and use trailing-palette mode 1.
The indexed-texture manifest also records four references in bank-04 entry 4.
This is evidence about those lists, not permission to replace entry 38's
stored RGBA16 state. Flat 2814 has no equivalent proven CI8 reference in the
current texture catalogue; size alone is insufficient.

### Reviewed loading path

- `150031EC` loads the bank-04 scene bundle, relocates its model header and
  installs the first four display-list slots. Slot zero reaches texture
  relocation at `150033E4–150033F8`.
- `15003120` relocates auxiliary table pointers. `150049A4` relocates vertex,
  display-list and selected MoveMem pointers; it does not rewrite texture
  image formats, tile formats or load sizes.
- `1510CE60` resolves FD arguments to loaded flat pointers or trailing palette
  offsets. It preserves the FD command word, F3 loads and F5 tile definitions.
- `1510D0EC` loads/decompresses and caches flat assets. It does not expand CI8
  pixels into RGBA16.

These are bounded static findings. Scene-specific writes, a different runtime
consumer, or memory read beyond the decompressed allocation have not been
established. Do not pad the payload, inherit absent TMEM bytes or reinterpret
the image merely to produce a preview. Reopen these five only with a concrete
conversion, display-list rewrite or complete ROM-backed source-span proof.

The reproducible local audit is
`build/assets/models/batch/rgba16-span/audit.py`; it checks all five stored
loads, the duplicate segments, the two CI8 reference lists and the action
record below. Run it from the repository root with Python. `audit.json`
records exact material state and hashes of the reviewed code spans. It is
read-only with respect to exporters and gallery assets.

## Bank-09 renderer candidates

Entry 213 maps to ordinary-object selector 13 at `800A38B4`. Entries 407–412
map to selectors 162–167 at `800A3B08–800A3B1C`. The latter six use flat 3182
and segment-8 offset `0x100`; entry 213 uses flat 4536 and offset `0x110`.
Texture decoding agrees across the verified state tables, but a reviewed
submission path still needs to establish the segment-8 binding.

The constructor argument report has no submission candidate for these seven.
A bounded reverse-reference pass also found no sufficient consumer. Matching
integer values are not model identities: for example, `15032B84–15032BAC`
select animation indices, `151941D0–151941EC` compare actor types, and the
value 213 in `800A3EBC/800A3EC0` belongs to a selector array, rather than a
direct bank-09 ID field. Keep the distinction between the 233-entry model
lookup's input selectors and its output model IDs.

Local raw candidate references are saved in
`build/assets/models/batch/rgba16-span/bank09-references.json`. They are
search leads, not admitted contexts. Further work should follow a new indirect
submission or runtime table-write lead instead of repeating these constant
searches. No unused-status claim follows from a bounded negative search.

### Bounded indirect-dispatch follow-up

The retained constructor report marks `151D3480` incomplete at the indirect
jump `151D34C0`. This is a six-case switch through `800AB170`, guarded by
the unsigned range check at `151D34A8`. Fresh checksum-validated ROM bytes
resolve cases 0–5 to `151D34EC`, `151D34F8`, `151D34D4`, `151D34E0`,
`151D34C8`, and `151D3504`. Their selectors are respectively 52, 77, 87, 88,
12 and zero. The five nonzero selectors map to bank-09 entries 301, 302, 346,
347 and 348; zero skips this submission branch.

The value stored at stack `+0x190` reaches template halfword `+0x56`
(stack `+0xE6`, template base `+0x90`) at `151D3A60`. The two submissions
call wrapper `15132A4C` at `151D3BCC` and `151D3CB0`. This resolves one
previously unexplained indirect selector path, but supplies none of selectors
13 or 162–167. It does not admit a new material binding or establish that
the seven target models are unused.

The bounded audit verifies all 564 stored instructions in this function against
the ROM, plus the switch and model lookup words. Its script and JSON evidence
are retained under `build/assets/models/reference/scene-review-20260915/`
as `indirect-audit.py` and `indirect-audit.json`. Further work should target
runtime writes to the constructor template selector and callback fields;
rerunning this switch audit or the previous constant scans cannot close the
remaining renderer/segment-8 proof by itself.

### Runtime object-cache and submission follow-up

The constructor's model cache provides a narrower runtime test than searching
for matching integers. `1513264C` reads template selector `+0x56`, tests its
signed halfword reference count at `800DC468 + selector * 2`, and walks the
cache from `800DC460` through wrapper `+4`. Wrapper `+0xC` stores the selector;
wrapper `+0` points to the loaded model header. The constructor increments the
reference count at `151328B4`, installs the wrapper at object `+0x8C`, and
copies the template to object `+0x10`. This places the selector at object
`+0x66`, full flags at `+0x60`, and callback byte at `+0x79`.

A read-only audit of the 26 existing OpenEmu-derived saved states finds zero
reference counts and no cache wrappers for selectors 13 or 162–167. Each state
is anchored by the complete 233-word ROM model lookup and independently checked
against the switch table at `800AB170`. Their saved RDRAM starts at file offset
`0x1BC` with little-endian 32-bit words. The audit checks linked-list bounds,
backlinks, tail and nonzero-count membership. It also verifies the stored
constructor, loader and renderer instructions against the checksum-validated
ROM. These are observations of the saved caches, not proof that the models
are unused or cannot be constructed later.

The reusable `config/model-trace-object-selectors.json` hooks constructor
templates, selector-reference writes, callback dispatch and the primary-list
submission write. It retains selectors separately from bank-09 model IDs,
full flags, callback bytes, wrapper pointers and constructor return addresses.
Callback byte 255 is the signed disabled sentinel -1. The graphics-task hook
provides a bounded stopping point; no capture data becomes an extraction input.

A software-renderer run from `save-game-26.st` reaches two graphics-submission
hooks and records 27 object submission-write hits, one constructor template
and one reference-count increment. The observed selectors are 7, 8, 45, 46,
82, 149, 168, 169, 170, 171 and 191. Every recorded submission has matching
object/cache selectors and the disabled callback sentinel. None is a target
selector. Nearby selectors 168–171 reaching this renderer do not establish
the segment-8 binding for 162–167. A callback-control attempt from
`save-game-10.st` times out at the debugger prompt before recording a draw
event; it supplies no additional negative consumer evidence.

The precise remaining requirement is a gameplay trigger or fresh capture that
constructs selector 13 or 162–167, followed through its callback state to
primary-list submission. Repeating idle traces of these unchanged states
cannot establish that trigger. Keep all seven material bindings unresolved.
The snapshot audit script, per-state hashes, raw traces and summary are under
`build/assets/models/reference/triage-consumers-20260915/`.

## Runtime texture lead: attachment 47

Action 74 has header `80086F0C = 8009D250 01000000` and one record at
`8009D250`: `2F170001000000000000000000000000`. The reviewed action protocol
selects bank-09 entry 47, kind 1 and updater index zero.

Its first 28 faces have flat texture references. The final eight use segment
7 and segment 6, each with eight-bit pixels at offset zero and a 256-entry
TLUT at offset 1024. Their raw render tiles say RGBA8; indexed interpretation
also needs inherited TLUT state. This action supplies no updater to populate
the missing texture fields.
The [animation-event report](us_attachment_animation_events.md) establishes
SHC Soldier entry 88 as a parent: animation 24 creates action 74 at time 1.0,
and animation 25 removes it. The initializer is a no-op, both texture fields
remain zero, and the renderer preserves inherited segment bindings. The
parent's default eye image is 40 x 40 with palette offset `0x640`; it does not
match the attachment's 32 x 32 layout and palette offset `0x400`. Neither the normal blink tables nor either stored expression changes this
layout: all select 40 x 40 images. Attachment 47 is also absent from all 26
saved attachment lists. Obtain a fresh animation-24 submission and trace the
preceding segment writes and effective TLUT state. The attachment trace now
includes the alternate per-parent list write at `15035F60`; its new hook has
ROM and synthetic-test evidence, but no positive live hit yet.
An updater-zero action is not permission to choose a flat by appearance.

Attachments 165 and 185 and scene `04:0059:23` also remain in the runtime
segment group. Attachments 165 and 185 have no create/remove references in
the scanned animation-event lists. No new material binding is admitted.

## Bank-01 zero-alpha character group

Entries 0154, 0155 and 0162 retain 174, 186 and 210 blocked textured faces.
The [character alpha audit](us_character_alpha_frontier.md) establishes the
conditional renderer table selection and coverage-alpha distinction directly
from ROM. It does not establish their actual caller state or approve opacity
overrides. Use `./conker model-assets alpha-frontier` for the bounded report.
The guarded caller audit identifies nine bank-0E spawn records in scene 60
covering all three models, plus player-selection cases 35/36 for 155/154.
Mode 4 through `1502C974` always produces opacity below 255; constructor
defaults do not establish a later draw's state. The existing 26-state corpus
has no target identity in any of its four character evidence sets. A fresh
scene-60 draw after natural activation of ROM script `[6,60,7]` is the next
shared lead for 154/162. Its upstream event conditions remain unresolved;
the scene's 120 ROM trigger records have no direct script-start class.
Repeat captures of the unchanged corpus
or blanket palette scans provide no new evidence.
