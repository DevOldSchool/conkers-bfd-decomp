# Expression attachment constructors

Derived from the checksum-validated US ROM SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. The active integration reports this
metadata without changing source models.

## Integration

`load_character_defaults(include_expressions=True)` authenticates the
constructor report. `load_character_expression_manifest` exposes it under
`attachment_constructors`, adds canonical action field names and explicitly
lists legacy compatibility aliases. Native verification checks the ordered
six-operation inventory. Stored expression bytes and model exports are
unchanged.

## Independently proved operations

| Expression selector | Native action | Program address | Ordered constructor models |
| --- | --- | --- | --- |
| 1 | 5 | `8009CE50` | bank09 entry 132, kind 2, updater 6, attachment animation selector 1 |
| 2 | 6 | `8009CE60` | bank09 entry 15, kind 1, updater 0, signed selector -1 |
| 3 | 7 | `8009CE70` | bank09 entry 16, kind 1, updater 0, signed selector -1 |
| 4 | 10 | `8009CEB0` | bank09 entry 18, kind 1, updater 0, signed selector -1 |
| 5 | 11 | `8009CED0` | bank09 entry 132 then entry 18, same per-entry fields as above |

These are six ordered constructor **requests**, not six observed runtime
instances. Ten stored nonzero expression-selector references were found in
character 0 presets 21, 22, 23, 30, 31, 32, 42, 43, 54, 63. Their literal action
parameters include 0, 10, 1000. All six constructors ignore that parameter
regardless of value.

## Read/modify semantics and proof boundary

`1507E5C8` reads expression byte+4 and big-endian u16+6, calls `1507EA44`, and
separately updates the actor's morph/blink/texture-selection fields. Those actor
writes are distinct from attachment creation. `1507EA44` converts u16+6 to f32,
multiplies it by ROM f32 at `8009B8A0` (`3A83126F`, approximately 0.001), and
passes it as `15083568` argument 2. It sets argument 3 to zero.

`1507E9F8` exposes selector bytes `[5,6,7,10,11]` at `8009D910` only when
`150849A0` returns zero. That gate reads actor+`1C9` and the current
representation array at actor+`2C4`; it is not a direct check of static actor
model byte+4. Static character 0 ownership of the ten stored references is
independently observed in bank11, not a substitute for the runtime gate.

`15083568` reads header pointer and u8 count from `80086CC4 + (action-1)*8`,
iterating 16-byte records in source order. Kind0 calls `15083AC8` and passes the
scaled float. Kinds 1/2 call `15030AF4`; neither passes or reads that float. The
dispatcher attempts every record even if an earlier constructor returns zero;
there is no rollback, and only the last record result is returned. Thus the
expression field should be an action parameter, not an animation duration,
attachment lifetime, or clip selector.

At `15083634` through `1508367C`, the constructor receives record bytes+0,+1,+7
as model, next u8 field, and flags. Record+4/+5 are stack arguments 4/5; caller
argument 3 (zero) is stack argument 6; the native action is argument 7; record+2
is updater argument 8; record+8 points to three halfwords; kind 2 passes
record+6 as argument 10 and kind 1 passes-1; record+E/+F are the final
arguments. The helper exposes all these exact descriptor storage fields without
inventing names for unproved parameters.

`15030AF4` reads parent+`3B` as owner ID and returns zero if it is zero. For
these flags 0 records, it also returns zero if an existing descriptor has the
same owner, action and model. Successful creation allocates/inserts a runtime
attachment descriptor; it does not edit the stored expression/action records.
Expression caller argument 3=0 becomes descriptor u16+`1C`=`FFFF`; this is
independent of expression u16+6. The constructor initializes texture halfwords
+`18`/+`1A` to zero. Their zero state is not a texture/material binding.

`1502FFD8` reads signed descriptor byte+`17`. Its-1 path uses `1502FE10`; its
other path uses `1503F62C`, which delegates bank09 geometry loading to
`1502FE10` and records the attachment animation selector. `1502FE10`'s call at
`1502FE80` explicitly supplies bank 9 and the model index. These full functions
are pinned. `15031A50`'s initializer is a no-op for 15/16/18; model 132's
indirect target at `80096F48` is pinned to the same no-op return `15031C00`.
Later updater 6 playback, attachment matrices, visibility, and material state
are outside this metadata decoder's claims.

## Source and consumer identity

`model_expression_constructors.py` pins 11 complete functions and 13 data spans:
selector table, scale, initializer branch target, all five action headers, and
all six records in five contiguous programs. Every byte of each header and
record participates in SHA1 guards, including reserved and unused bytes.
Parent-modification kind 0, unknown kinds, changed/relocated/truncated evidence,
and unreviewed signed animation selectors fail closed.

The module does not run a constructor, modify geometry, create an export
context, rebind textures, or assert runtime reachability. It reads only the
supplied byte buffers and returns fresh metadata.

## Validation and invariants

Portable focused tests cover every byte of the 149 pinned source-data bytes
changed individually, record order, unsigned halfword endianness, signed-1
loader semantics, consumer/truncation rejection, parent-modification exclusion,
and nonmutation/repeated-call independence. The live ROM audit rejects 72
further mutations at each consumer/data span's first, middle and last byte.

| bank09 entry | Source bytes | Vertices / UVs | Faces | Source joints |
| --- | --- | --- | --- | --- |
| 15 | 392 | 7 / 7 | 5 | 0 |
| 16 | 392 | 7 / 7 | 5 | 0 |
| 18 | 1224 | 44 / 44 | 54 | 0 |
| 132 | 2840 | 96 / 96 | 108 | 9 |

All four source SHA1 identities are pinned in the audit. Native attachment
encode/decode round trips reproduce every byte; parsed geometry/layout values
remain equal across metadata decoding. No model, image, capture or ROM payload
is written. The audit report contains proof hashes, counts, constructor field
values and scope only. See [the audit
command](us_model_evidence_audits.md#expression-constructors-rom-only-audit) for
reproduction from the ROM.

Run the portable tests with:

```sh
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s tests \
  -p 'test_model_expression_constructors.py'
```

Runtime activation, placement, playback and complete material resolution require
separate evidence.
