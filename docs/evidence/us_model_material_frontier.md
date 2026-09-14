# Remaining model material evidence

Current US investigation targets, checked 13 September 2026. These findings
do not grant export eligibility or change the 850-model inspection gallery.
The checksum-validated ROM is `4cbadd3c4e0729dec46af64ad018050eada4f47a`.

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
match the attachment's 32 x 32 layout and palette offset `0x400`. Resolve the
expression/texture state and segment lifetime for animation 24 before export.
An updater-zero action is not permission to choose a flat by appearance.

Attachments 165 and 185 and scene `04:0059:23` also remain in the runtime
segment group. Attachments 165 and 185 have no create/remove references in
the scanned animation-event lists. No new material binding is admitted.
