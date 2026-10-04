# Placed-object helper semantics

Eight existing matched helpers in `game_13F9D0.c`, `game_30E90.c` and
`game_13ABD0.c` use descriptive C names through source-local macro aliases.
The linked symbols, registered IDs, types, ABI, layout and operations remain
unchanged. The names describe N64 code behavior; no model identity is inferred.

| US address | C name |
| --- | --- |
| `15114050` | `placed_object_test_actor_mask` |
| `151140C4` | `placed_object_first_actor_mask_index` |
| `151148A8` | `placed_object_build_orientation` |
| `1511490C` | `placed_object_build_transform` |
| `151149AC` | `placed_object_find_by_id` |
| `15004A4C` | `placed_object_reset_vertex_cache_slots` |
| `15004BF0` | `placed_object_choose_candidate_id` |
| `1510D864` | `placed_object_reset_texture_binding_count` |

[Shared provenance](model_name_confidence_review.md)
retains the complete original-ROM spans; original reference splits are
`reference/game/us/asm/112520.s`, `39E0.s` and `10D720.s` respectively.
Direct J/JAL and aligned-data scans found no aligned game-data pointer to these
eight targets; this does not exclude indirect callers or other overlays.

Complete supporting consumers include vertex path `150A44F0`, mask producers
`150AB1F0/1510E950`, mask consumer `15114188`, and expiry consumer `15114A1C`.

## Orientation and transform

`151148A8` builds an orientation. Loader `15003BC4..15003C04` converts signed
placement rotations at `+6/+8/+A` to object floats at `+0/+4/+8`.
`151148CC` calls `150A8050` with only Y, `151148E4` builds the local X/Z matrix,
and `151148F4` combines them through `150A7A48`. The helper multiplies its
rotation inputs by the fresh ROM constant at `8009F6C0`, bits `3c8efa35`
(approximately pi/180), at `150A8084/150A80A4/150A80C0`. This supports
`rotationXDegrees/rotationYDegrees/rotationZDegrees`, `orientation`, `rotation`,
and `xzRotation`; no yaw/pitch/roll convention is asserted.

`1511490C` builds the transform. Loader `15003BA8..15003BC0` copies signed
positions to object `+10/+12/+14`; `15114930..15114974` writes matrix
translation, adding object float `+18` only to Y. The loader initializes `+18`
to zero at `15003D50`. These are `positionX/positionY/positionZ` (still `s16`)
and `verticalOffset` (still `f32`), without a motion-mechanism claim.
Placement floats `+20/+24/+28` populate object `+2C/+30/+34` at
`15003C08..15003C28`. `15114978..15114984` passes those words unchanged to
`150A7CB0`, which stores them on the scale-matrix diagonal at `+0/+14/+28`;
`15114990` combines the matrices. The existing fields remain `s32` and are
named `scaleXBits/scaleYBits/scaleZBits`; the local is `scaleMatrix`.

Only the same `Game13F9D0MotionArgs` member spellings are propagated to the
existing disabled `15113218` candidate. Its `#if 0`, recorded `CURRENT (4727)`,
fallback `GLOBAL_ASM`, and all other tokens remain intact. The similarly
spelled `Game13F9D0Matrix` fields are untouched. Initial placement setup and
later runtime callers use `1511490C`; a static-only lifetime is not inferred.

## Placement ID lookup and candidate selection

Object byte `+72` comes from placement byte `+33`, as shown by
`15003F40/15003F48`, `15003F7C/15003F8C`, and `15004190/150041A0`.
It is an object ID, distinct from pool indices, model-bank identities, updater
selectors, and texture IDs. `151149AC` rejects zero, walks
`D_800DBEF4` at stride `0xA0`, compares `+72` at `151149EC`, and returns the
first matching address at `15114A04`, or zero on exhaustion. Its `u8` input,
`s32` result, and integer-address arithmetic remain unchanged.

`15004BF0` chooses a candidate ID. Mode zero starts at ID one and scans from
object index `D_800DBF00`; nonzero mode starts at `255 - D_800DBF00` and scans
the whole pool downward through candidate IDs. On a collision it restarts the
scan. Ascending exhaustion returns 255; descending exhaustion restores the
starting candidate. The names `objectId`, `objectIndex`, and
`candidateObjectId` preserve that distinction without promising uniqueness.
`arg0` is retained because it is reused as a scan start or fallback.
The loader uses mode one for missing IDs at `15003F94/150041A4` and mode zero
for the later pool portion at `15004518`, storing results at object `+72`.

## Binding-count and vertex-cache resets

`1510D864` only clears byte `D_800D9ED0` at `1510D868`.
`1510D874` reads it as an unsigned count, accepts at most eight 16-byte
records at `D_800D9ED8`, and appends an object pointer, pixel base, optional
palette base, and segment bytes. `1510D8C0` iterates that count, matches the
object pointer, and emits `DB06` segment-base commands. Its direct registration
callers are `150C5210`, `150DE69C`, and `1511A6C8`, consistent with
[`model_object_materials.py`](../../scripts/model_object_materials.py).
Reset's sole direct call is `1501913C`, before updater invocation. The role is
texture-binding **count** reset: no record clearing, resource freeing, cache
flush, frame visibility, or reset-frequency claim follows.

`15004A4C` zeroes each word slot in `D_800DBEF8` and paired byte in
`D_800DBEFC`. Loader `150043FC..15004440` allocates count-times-four and count
bytes respectively. `150A45CC` refreshes the byte to three; the word receives
an existing vertex pointer at `150A45F8..150A4600` or a newly allocated
vertex-count-times-16 buffer at `150A464C..150A4664`. Object vertex source
`+28` and count `+16` feed the coordinate transforms and 16-byte output stride
at `150A47C0..150A4894`. `15114AF4..15114B20` decrements the paired countdown
or releases/clears an expired pointer. This supports `objectIndex` and
`cacheSlotOffset`; the reset itself does not release geometry.

## Flag-gated actor masks

`15114050` first requires object `+4F` bit `0x80`. Argument `-1` then returns
one without reading the mask; otherwise it tests the selected bit of
`D_800DBF94[(object - D_800DBEF4) / 0xA0]`. No bounds check is added or claimed.
`1509EE1C..1509EE60` scans actors at `800CC2D0 + index * 0x32C` and passes the
same index at `1509EE38`. Producer `150ABA24..150ABA90` sets flag `0x80` and
ORs the bit derived from `(actor - 800CC2D0) / 0x32C`; consumer `15114274`
passes the corresponding actor pointer to the object callback at `+78`.
This establishes `placedObject` and `actorIndexOrAny`, without naming the
whole flags byte collision-only or claiming standing-on, hit, or player status.

`151140C4` uses the same flag gate and mask, scans all 32 bits, and returns
the first set-bit index. Zero also represents an unset gate or no set bit,
so it is not a distinct no-result sentinel. The names `actorIndex`, `actorMask`,
and `actorBit` preserve the exact scan and fallback; the separate 25-actor
consumer does not justify narrowing it.
