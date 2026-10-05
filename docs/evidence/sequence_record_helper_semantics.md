# Sequence-record volume and FX-bus helpers

Five existing matched helpers in `src/main/init_B1B0.c` use source-local
aliases. Numeric linked symbols, ABIs, partial fields, operation order and
complete registered spans remain unchanged. No song/scene class identity,
new C implementation or raw/deferred match is inferred.

| Symbol | C name | Bytes |
| --- | --- | ---: |
| `8000CBF0` | `sequence_slots_set_ducking_ramp` | 100 |
| `8000CC54` | `sequence_slot_update_volume` | 236 |
| `8000CD40` | `sequence_volume_step_toward` | 96 |
| `8000E40C` | `sequence_record_set_base_volume` | 96 |
| `8000E704` | `sequence_record_set_channels_fx_bus` | 88 |

## Ducking factor and step

The ramp setter examines slot-mask bits 0..2, skips null records and stores
target at +0x5A and step at +0x5C. If the original s32 step argument is zero,
it also copies target into current factor +0x58. A nonzero step that narrows
to zero does not take that special path. Both values narrow to 16 bits without
clamping, and the helper does not itself queue player-volume changes.

Original `8000D758` attenuates other slots to 0x1770 or 0x1F4 while restoring
selected classes to unity 0x8000; another branch uses 0x36B0. This supports
ducking without assigning music, dialogue or song identities. The original
update at `8000D6C8..8000D6DC` advances this factor, and `8000CC54` incorporates
it in output volume.

The step helper multiplies its third argument by engine update counter
`D_800BE9E4`, moves current toward target and clips crossings using the original
branches. Original calls `8000D698/8000D6B4/8000D6D0` update the three factor
triplets at +0x4C, +0x52 and +0x58. This argument is a step, not duration.
The decreasing branch also tests for a negative result; the increasing branch
does not. Arithmetic/overflow behavior is unchanged, without a general
saturation, monotonicity or arbitrary-input guarantee.

## Applying the composed volume

`8000CC54` looks up a slot without bounds validation and ignores a null record.
It composes unsigned halfword factors +0x4C/+0x52/+0x58 with base +0x2C,
using the original low-32-bit products and logical shifts by 15. It is not
saturating or generally overflow-safe. Original callers include normal update
`8000D6E8`, activation `8000D52C` and first-factor adjustment `8000DFB0`.

Unchanged cached value +0x30 suppresses downstream work. Zero-to-nonzero
changes enable `flags38 ^ 0xFFFF` in the note-enabling channel mask;
nonzero-to-zero changes disable that selection. Other nonzero changes leave
the mask alone. These are mask edits, not channel fade-volume changes or an
immediate stop of existing voices. The helper updates the mask and cache
before queueing player volume. Queue failure is not reported, and a subsequent
unchanged value does not automatically retry. Record lookup uses the original
slot argument while the downstream player selector uses its low byte.

## Record base volume and FX bus

The base-volume setter clamps its signed volume input to 0..32767 and uses
`8000B1FC` to search direct records first, then their linked +0x60 records.
When found it writes +0x2C; a negative player index also causes a +0x30 write.
Initialization at `8000B354..8000B394` takes this base from metadata/default
while all three factors start at unity 0x8000, corroborating its role.
Original `8000B874/8000B898` alternate levels and `8000CAC0` supplies a computed
level. The setter does not mask the ID, create a record, change ramp factors,
call the volume updater or queue audio. Missing records are silently ignored.
A stored value in an unassigned record does not establish audible application.

The FX-bus wrapper instead uses `8000B1B0` to search only occupied direct
slots by sequence ID. A found record with nonnegative index supplies the player
selector to `sequence_channels_set_fx_bus`. Return one means that call occurred,
even for an empty channel mask. It does not prove queue acceptance or a valid
bus; missing/negative-index cases return zero.

## Evidence and acceptance

Original `reference/us/asm/B1B0.s`, initialization and controller call paths
support these roles; lower-level behavior is documented in
[sequence transport evidence](sequence_transport_helper_semantics.md).
Opaque metadata categories, shared callback flags, selector mappings and
other record policies remain numeric. All 616 target bytes require full-span
CURRENT (0), existing layout, clean batch, tests, progress, whitespace, RSP
and exact main/game images. No source-unit completion is claimed.
