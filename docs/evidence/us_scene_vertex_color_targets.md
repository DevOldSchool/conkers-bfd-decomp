# ROM scene vertex-color targets

The standalone vertex-color export recovers ordered RGB target data for five
bank-04 models: fourteen target descriptors and 302 vertex references. Of those
references, 139 have target RGB different from the stored source RGB. The
source indices, source RGBA and target RGB remain explicit; no geometry,
textures, alpha or gallery defaults change.

The source is normalized US ROM SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. Captures, previous exports and
reference models are not extraction inputs. The relevant descriptor parser and
consumer path are independent of recovery branch
`4f80ae55eeb322a170837319257ed0ab9da58c97`.

## Stored arrays and consumer

`15003120` registers the header-word-8 descriptor table, rebases its first two
words and counts twelve-byte records until a zero first word. `151739B0` reads
the first pointer as an ordered RGB-triplet array, the second as ordered big-endian
`u16` vertex indices and the third as their count. Existing geometry extraction
recorded these offsets and counts; the new exporter also preserves their contents.

For each referenced vertex and RGB channel, `151739B98..15173C08` computes:

```text
result = base + (((target - base) * factor) >> 8)
```

The multiply's low word is followed by an arithmetic right shift, then a byte
store to vertex offsets `+12`, `+13` and `+14`. No alpha store occurs. The helper
`interpolate_rgba` accepts explicit byte-valued RGBA/RGB and integer factor
`0..255`, where products cannot overflow. Negative products round downward.
Factor 255 is not normalized to 1.0: an increasing channel can remain one below
its target. For example, base 10 and target 11 yield 10 at factor 255; reversing
those values yields 10. Stored target values are therefore kept separate from
samples of this native formula.

`150127B0`, together with `15012C84`, initializes RGB snapshots from vertex
bytes. Scene configuration byte `+0x21` selects whole-array or descriptor-specific
snapshots and admission paths. `151739B0` chooses these runtime snapshots;
`stored_source_rgba` in the export denotes original ROM bytes, not an observed
current snapshot. Descriptor selector 255 requests all descriptors in source
order. The export does not assign those descriptors a timeline.

## Source identities

| ROM model | Targets | References | Model SHA-1 |
| --- | ---: | ---: | --- |
| `04:0001:00` | 2 | 15 | `8e4b1cadd343a8f5f4eb1846c98909adda41e577` |
| `04:0001:11` | 1 | 10 | `a3d8bed02f4ef2346aa7c8c567ed13989295bf07` |
| `04:0004:00` | 4 | 67 | `15bc17e0a6b647b1caaecac2b9cea1cc226cb521` |
| `04:0007:09` | 1 | 8 | `fb4228093a63353e7a7f484441dbced5c88bd39c` |
| `04:0028:00` | 6 | 202 | `c5847056b7dec44a298a6b4de6884787477d0877` |

The exporter guards nine complete ROM function spans: `15003120`, `150031EC`,
`150039E0`, `150127B0`, `15012C84`, `15113E54`, `1511C638`, `151739B0` and
`15173C60`. Full sizes and SHA-1 values are retained in the manifest and module.
All five complete model identities are pinned. Every descriptor table, including
its terminator's remaining words, is reconstructed byte-for-byte. Ordered index,
target RGB and stored source RGBA arrays round-trip through JSON without sorting,
deduplication or altered alpha. Per-array SHA-256 values accompany the records.

## Conditional controller links

Updater index 17 at `80088D5C` is exactly
`1511C638 00000000 00000000`. `150039E0` copies placement `+0x18` into object
`+0x3C`, initializes object `+0x73` to 4 and object `+0x80` to zero, and installs
the selected updater. The conditional dispatcher is `15113E54`.

Eleven pinned placement records link that updater to terrain RGB targets:

| Scene | Placement record -> target selector |
| --- | --- |
| 4 | `6 -> 3`, `9 -> 2`, `12 -> 1`, `15 -> 0`, `19 -> 0` |
| 28 | `0 -> 0`, `2 -> 1`, `4 -> 2`, `6 -> 3`, `22 -> 4`, `24 -> 5` |

Scene-4 record 19 has initial inactive byte `+0x34 = 1`; the other ten have zero.
These are source controller links, not proof of activation. Each record retains
its exact SHA-1, controller model, terrain target and initial inactive byte.

The reset arm of `1511C638` invokes the selected terrain target with factor zero
when object `+0x73 & 3` equals one. Its rising arm at
`1511CAA4..1511CAE8` adds `30 * s32[800BE9E4]` to object `+0x80`, clamps signed
values at or above 255 to 255 and invokes `15173C60`. Selector 255 suppresses
these calls in this updater. `15173C60` selects terrain slot zero and forwards
the factor and selector to `151739B0`. The full state machine, branch admission,
delta range and tick frequency are not reconstructed. Other models' controller
links remain outside this bounded review.

## Reproduction and verification

```sh
./conker model-assets vertex-color-targets
./conker model-assets vertex-color-targets --verify
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s tests -p 'test_model_vertex_color_targets.py'
```

`--rom` selects the local authorized ROM. `--output` defaults to
`build/assets/models/vertex-color-targets`; generation requires a new directory.
Verification derives the expected manifest from the ROM and compares its exact
bytes without writing. The real-ROM export and verification both pass.

Nine focused tests cover signed rounding, factor bounds, alpha preservation,
ordered duplicate indices, unknown terminator words, source/table truncation,
invalid indices, every complete consumer guard, dispatch and placement changes,
and edited-output rejection. A separate raw-ROM audit compares all 302 exported
references directly with indexed archive bytes and checks all 256 supported
factors using a nonnegative weighted-sum formulation.

This output is source-authentic target data with bounded interpolation semantics.
It does not establish a playback timeline, runtime base snapshots, gameplay
activation, visibility, lighting or native raster equivalence.
