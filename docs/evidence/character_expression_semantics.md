# Character expression semantic names

These are inferred descriptive names from the US ROM and reviewed consumers,
not recovered original source names. Linked `func_` symbols, declarations,
field widths, offsets, padding and operation order remain unchanged.

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

## Independent ROM spans

All spans below were read from the normalized US ROM SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a` using the current registered extent.
They include branches, delay slots and any registered terminal padding.

| Symbol suffix | Bytes | SHA-1 |
| --- | ---: | --- |
| `1507E500` | 200 | `a2a542a0b6aea78ccbc269507a5ee977e6443ccf` |
| `1507E5C8` | 240 | `77b08fc8d2ec99c73d27527f43df6c9952d0c5fa` |
| `1507E6B8` | 132 | `059fe16ca29114f79874eb5bba055de0c5c3b12c` |
| `1507E908` | 96 | `c602e20a2b335d94feb349539cbdb76d69957d50` |
| `1507E968` | 128 | `94fb99b2aabedd05d7d1404d8013af047b86a5af` |
| `1507E9F8` | 76 | `31fcadb16432eb6925dc6fcf17d561857102493d` |
| `1507EA44` | 120 | `c4818df6a7fca422de2d463163d68866d05b090f` |
| `1507EABC` | 112 | `27ec4fab9d1d702ca425ce9c513356ac032b71e8` |
| `1507EB2C` | 32 | `cb97140a9e2b5a1832f8869e6c2b105743ab4ab9` |
| `1507EB4C` | 52 | `0bea04c46acdb0648becca735aff57ee5f402765` |
| `1507E2B0` | 272 | `25c3adf8ab6e48111023c6f0a7dfcb74cbdb2f80` |
| `1507E73C` | 168 | `9454da6931491edc5fb0cca9ea911b19f6ac70e8` |
| `1507E7E4` | 292 | `064a319797f11d4c28456b90634bb51481889bcc` |
| `1502EE8C` | 104 | `39abe4f6339af44beba31d4d2ab7603b2530ff22` |
| `1502EEF4` | 296 | `2da422b7989f9b16b67dc448f60332131031e4f0` |
| `1502F01C` | 584 | `a9ae1253feb21fae8ecc3c314d949162c3e6afa5` |
| `1502B4A8` | 288 | `d1a82190ae64677a9404302b5a61653a5770a7dc` |
| `150849A0` | 44 | `62d89a7ec36b39096dfd2c98896619b96b71866a` |

Acceptance requires full-span focused zeros for the nine renamed matched
functions, unchanged source-unit layout, clean batch/game/data/rodata checks,
full tests, progress and whitespace. It adds no C matches or matched bytes.

## Held terminal-function naming

`func_1507EB4C` has a registered 52-byte span. Both the unchanged baseline and
the identifier-only proposal produce `CURRENT (100)`: the focused candidate
ends before the final registered NOP at offset `0x30`. No instructions, compiler
settings, comparator policy or boundary records were changed to conceal this.
Its C definition and the shared `field_70` spelling remain unchanged in this
batch. The independent semantic role above is retained as evidence only.

## Accepted naming result

All nine selected matched functions retain full-span `CURRENT (0)` and their
reviewed source-unit layouts. Clean `verify-batch` reached `BATCH_COMPLETE`;
the integrated game image, mapped rodata, full ROM, progress and whitespace
gates pass. Both complete 1,712-test suites pass: 37 host skips and one optional skip
in the ROM-enabled pinned-toolchain source fixture. Independent read-only review verified
all 18 raw-ROM spans and identifier-only equivalence of the C change.

This accepts eight newly descriptive function roles and eight existing local
field names beyond the earlier pilot. No new function or byte match is added.
