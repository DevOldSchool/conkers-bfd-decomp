# Character expression semantic names

These are inferred descriptive names; linked symbols, widths, offsets, padding
and operation order remain unchanged. See [shared provenance](model_name_confidence_review.md)
for independent full-span support and the distinction from matching/runtime proof.

## Record and representation contracts

Bank `0x11` holds a default header and an optional expression segment. The
[expression and morph evidence](us_character_morph_targets.md) establishes the
ten-byte expression records. `func_1507E908` indexes them; it does not check the
requested index. `func_1507E968` divides the relocated descriptor byte size by
ten. The existing eight-byte `GameAB760ValueRecord` therefore names its `s32`
fields `dataAddress` and `sizeBytes`, without changing their representation.
The predecrement from the defaults pointer accesses the second descriptor at
bundle offset eight; `func_1502B4A8` has already masked its size flags.

The lookup uses `func_150849A0`, which selects an override-or-base model through
actor `+0x1C9` and `+0x2C4`. Selector zero chooses the first list entry; a nonzero
selector chooses entry `selector - 1`. It never reads the applied ordinal at
`+0x1C8`, and neither normalizes the `0xFF` reset request nor checks list bounds.
This lookup can differ from the mutable applied model byte at actor `+0x04`.
The expression-count helper preserves its special `+0x04 == 0x96` case and its
`0xFF` model sentinel. `func_1507E6B8` retains its existing argumentless call to
`func_150849A0`; naming does not change that calling convention. See the
[selection refinement](actor_representation_selection_semantics.md).

## Function roles

| Symbol | Descriptive role | Boundary |
| --- | --- | --- |
| `func_1507E500` | `actor_set_expression` | Handles the old action, stores the requested index, applies it and sets morph duration; no lower-bound check is claimed |
| `func_1507E5C8` | `actor_apply_current_expression` | Applies action, morph shape/duration, blink codes and texture selectors |
| `func_1507E6B8` | `actor_can_update_blink` | Its result gates the blink-control update in `func_1507E73C` |
| `func_1507E908` | `actor_get_expression_record` | Address lookup using the override-or-base model, with ten-byte stride |
| `func_1507E968` | `actor_get_expression_count` | Expression segment byte size divided by ten |
| `func_1507E9F8` | `actor_get_expression_action_table` | Override-or-base model zero exposes five action IDs |
| `func_1507EA44` | `actor_dispatch_expression_action` | One-based selector resolves an action ID before dispatch |
| `func_1507EABC` | `actor_restore_default_expression` | Requests the default and clears priority/timer and direct blink codes |
| `func_1507EB2C` | `actor_set_default_expression_zero` | Delegates with zero; an unchanged default does not force a reset |
| `func_1507EB4C` | `actor_set_default_expression` (evidence only; C unchanged) | Changes the default index and requests restoration when it differs |

`morphDurationOverride` names the caller override for actor `+0x135`, distinct
from the expression timer. Record byte two selects the morph shape at `+0x134`;
byte three supplies transition duration. The shared local `value` remains
unspecialized because it later holds both texture selectors. `actionParameterRaw`
is the record's big-endian `u16` value at offset six, converted to float and
scaled before dispatch. It is not named an animation index or attachment
lifetime: the reviewed attachment constructors ignore it. See the
[constructor evidence](us_expression_attachment_constructors.md).

## Existing source-local actor fields

| Offset | Name | Consumer evidence |
| --- | --- | --- |
| `+0x6A`, `+0x6B` | `blinkControl0`, `blinkControl1` | `func_1507E2B0` toggles the controls; `func_1502EE8C` normalizes them |
| `+0x6C`, `+0x6D` | `blinkCode0`, `blinkCode1` | `func_1502EEF4` updates low codes; expression application writes descriptor index plus ten |
| `+0x70` | Default expression index; C keeps `field_70` | Restored by `func_1507EABC`, changed by `func_1507EB4C` |
| `+0x71` | `expressionPriority` | Requested priority three bypasses comparison; otherwise higher priority can replace the current request |
| `+0x72` | `expressionTimer` | Decrements by `D_800BE9E4`; expiry requests the default expression |

Channel numbers are used because left/right orientation is not proven.
`func_1502EE8C` maps controls 0/1 unchanged, 2/3 to 0/1 and values at least four
to two. `func_1502EEF4` uses the normalized value to move a code toward zero,
toward two when below two, or to one. For normalized control one, codes 3–9
remain unchanged. `func_1502F01C` interprets codes below ten through the
three-byte default blink tables and codes at least ten as direct descriptor
indices after subtracting ten; the current expression may override a low-code
table result. Controls are not texture descriptor indices.

Timer `0xFFFE` returns before updates. `0xFFFF` suppresses decrement but still
allows later blink processing. Timer units remain unnamed, and the two-byte
`pad6E` stays intact. Names are propagated into the two existing excluded C
candidates only for field consistency; neither candidate is promoted.

## Held terminal-function naming

`func_1507EB4C` has a registered 52-byte span. The baseline and
identifier-only audit both produced `CURRENT (100)`: the focused candidate
ends before the final registered NOP at offset `0x30`. No instructions, compiler
settings, comparator policy or boundary records were changed to conceal this.
Its C definition and the shared `field_70` spelling remain unchanged. The independent semantic role above is retained as evidence only.
