# Scene 59 material and bank-09 entry 447 frontier

A bounded ROM review on 2026-10-01 leaves these two assets unresolved. It adds
no texture defaults, semantic classification, extracted meshes or gallery cards.
The input is normalized US ROM SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. Captures and previously exported
models are not inputs to the accompanying audit. Recovery branch
`4f80ae55eeb322a170837319257ed0ab9da58c97` has no changes to the relevant scene
binding or emission-point modules.

## Scene `04:0059:23`

The 760-byte model has SHA-1 `42e87cbf9632220af0badc1bb2d4ed585d1227b2`,
32 vertices and 40 faces. Its display list occupies `+0x228..+0x2F8`. The sole
material loads 64 x 64 CI4 pixels from segment 4 and a 16-entry RGBA16 palette
from segment 5, both at offset zero. It explicitly selects combiner
`FC121824 FF33FFFF` and OtherMode `EF08AC3F 00504A50`.

Bank-11 scene-59 placement record 18 selects dispatch kind 1, model index 23,
position `[-5170, -2018, 6019]` and updater index zero. Its SHA-1 is
`60a63a5ff6a99cab7985c7aa25844eaa921a2e86`. The twelve-byte updater-zero row at
`80088C90` is all zero; initial placement flags select the ordinary direct
renderer. This establishes the placement, not the inherited texture binding.

The reviewed animation helper `1511A494` has only three scene-59 rows at
`80089378`, `80089384` and `80089390`, for models 7, 9 and 11. They select the
same fifteen water frames from `8009177C`; no scene-59 row admits model 23.
Its four direct call sites are `1511A720`, `1511A7A8`, `1511AEEC` and
`1511D9C8`. Merely assigning one of those updaters would not satisfy the
helper's model-selector comparison for model 23.

The segment replay helper `1510D8C0` compares a registry entry's object pointer
with the current object at `1510D8E0..1510D8E8`. A match emits the registered
pixel segment and optional palette segment; no match leaves inherited segment
values untouched. Thus a compatible water-frame layout does not establish
which prior draw supplied segments 4/5 or whether those bindings survive.
The complete current-ROM hashes match the existing guards:

| Consumer | Size | SHA-1 |
| --- | ---: | --- |
| `1510D874` segment registration | 76 | `ca5d61ecce77fe21f7b613e7d2c8a3e3860c6fe1` |
| `1510D8C0` segment replay | 176 | `93a912bad5e9ddc0bebe3f683c48b2a06d31a773` |
| `1511A494` animation selection | 616 | `c896da27caa019639fe040e1d5bf9034f2663673` |

**Next evidence:** a positive scene-59/model-23 submission with the preceding
`DB060010` and `DB060014` segment writes, pointed pixel/TLUT bytes and complete
submission order. A ROM match for those bytes could support a captured-context
material binding; it would not establish a universal default. See the
[placed-object renderer](us_object_material_consensus.md) and
[texture-animation proof](us_object_texture_animation.md).

## Bank-09 entry 447

The indexed archive range is decimal `[19240024, 19240762)`: 738 compressed
bytes decode to 864 bytes with SHA-1
`a07cd25655ac322412d3553515b39c2b5191afa3`. These bytes can be parsed syntactically
as 54 sixteen-byte `B3s3f` records. The floats are finite, all three reserved
bytes are zero, and the leading-byte frequencies are
`0:4, 1:27, 2:14, 3:6, 4:3`. These facts alone do not establish matrix slots,
particle emission or other semantic meaning.

The ROM-verified twenty-entry emission selector table at `800AB140` excludes
447. Existing `151D2AB0` loader and `1518F8E0` consumer guards pass, and
`test_unproven_entry_and_changed_consumers_are_not_accepted` deliberately
preserves the exclusion. A single targeted constant check found no game-code
`addiu` or `ori` loading literal 447 from zero into `a0..a3`. This bounded
negative result excludes neither computed selection nor indirect references.

**Next evidence:** an actual load of resource `[9,447]` and its downstream
consumer. The consumer must establish field widths, stride and use before
entry 447 joins the [classified emission-point sets](us_bank09_effect_models.md#twenty-non-mesh-point-sets).
No selector or semantic format is inferred from adjacent archive entries.

## Reproduction

The ignored task checkpoint contains a read-only ROM audit and its JSON result:
`build/assets/models/reference/continuation-20261001/runtime-frontier/audit.py`
and `audit.json`. The script prints only metadata, checks the authorized ROM
identity and existing consumer guards, and reproduces the two bounded constant
checks without generating exports. From the repository root:

```sh
PYTHONDONTWRITEBYTECODE=1 python3 build/assets/models/reference/continuation-20261001/runtime-frontier/audit.py
```

Raw assembly review is additional evidence for the consumer interpretation;
record syntax and negative constant scans are not semantic proof.

## Scene-59 loaded-surface gate, 2 October 2026

Controlled source-proven scene requests on an isolated copied state tested
entries 0, 3 and 15. Entry positions and camera-offset records came from the
scene's normal ROM entrance table; no object visibility or camera transform
was forced. Twelve complete submitted graphics tasks contained no geometry
correlation candidate for `04:0059:23`, including ambiguous matches, and no
execution of its exact 208-byte source display list.

The entry-15 object pool positively contains the target at `80191830`, selector
`8017`, position `(-5170,-2018,6019)`, list `8016E408` and vertices `8016E208`.
The 208 list bytes and 512 vertex bytes match the fresh ROM source exactly.
Its render flags are `object+0x4F = 0x50`, leaving bit 0 clear; `+0x6E` and
`+0x70` are zero. The candidate builder at `15112B98..15112BA4` requires bit 0
before spatial eligibility, explaining why a closer entrance alone did not
submit the surface.

This flag is authored: bank-0B scene-59 placement 18 has byte `+0x32 = 0x50`,
and the constructor at `15004170/174` copies it to object `+0x4F`. Its unique
object ID is `E6`; the captured update and interaction callbacks are zero.
A generic class-3, operation-13 event setter can update the flags through
`(flags & ~packet[+0xC]) | packet[+8]`, resolving the target by ID through
`151149AC`. However, the five declared scene-59 event programs contain neither
that operation nor a direct `E6`/`30E6` operand. This bounded result does not
prove the surface permanently unused, and no normal activation is established.

The inherited segment-4/5 materials remain unresolved for this source: sibling
water submissions cannot establish the disabled target's material. Preserve
the geometry and blocked status; obtain a proved activation before recapturing.
Full reports and reproducers are in
`build/assets/models/reference/resolution-goal-20261002/runtime/`, including
`scene59-bounded-result.json` and `scene59-activation-source/audit.json`.
