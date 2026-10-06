# US I8 mipmap source gap

The 2026-10-01 ROM audit confirms that three bank-09 material blockers share
one incomplete mip chain. Their renderers are already proven; changing a
lookup-mode decoder cannot supply the missing source bytes. This audit adds
source evidence only and does not change exports or material admission.

The reviewed US ROM SHA-1 is
`4cbadd3c4e0729dec46af64ad018050eada4f47a`.
Recovery branch `recovery/model-extraction-20260930`, reviewed at
`4f80ae55eeb322a170837319257ed0ab9da58c97`, still lists these records as
unresolved. This note does not duplicate or modify its recovered material paths.

## Affected lists

Entry and run numbers below are decimal; command offsets are hexadecimal and
relative to the decoded model segment. Every record has segment zero.

| Record | Material run | Faces | Image command offset |
| --- | ---: | ---: | --- |
| `09:0230:00` | 4 | 3 | `0xE98` |
| `09:0248:00` | 2 | 1 | `0x6D0` |
| `09:0249:00` | 2 | 1 | `0x6D0` |

All three lists select flat 1708 with `FD900000 000006AC`, load 368 bytes with
`F3000000 070B7000`, and enable maximum mip level 3 with
`D7001802 FFFFFFFF`. Their material combiner is `FC26A004 1F9493FF`;
its first colour cycle interpolates `TEXEL0` and `TEXEL1` by `LOD_FRACTION`.
The four I8 tile declarations are:

| Level | Dimensions | SetTile command | Row stride | Source range |
| ---: | --- | --- | ---: | --- |
| 0 | 16 x 16 | `F5880400 00090240` | 16 | `[0, 256)` |
| 1 | 8 x 8 | `F5880220 0108C631` | 8 | `[256, 320)` |
| 2 | 4 x 4 | `F5880228 02088A22` | 8 | `[320, 352)` |
| 3 | 2 x 2 | `F588022C 03084E13` | 8 | `[352, 368)` |

Thus the final 16 requested bytes contain a declared mip level, not merely
unused trailing transfer padding. The complete source supplies levels 0–2;
level 3 starts exactly at the source end. This does not prove whether a runtime
draw reaches level 3 or what adjacent RDRAM bytes its load might fetch.

## Complete flat-resource framing

Flat1708 begins at ROM `0x41B17D`. The runtime compressed-size table assigns
361 bytes. Its length-prefixed raw-deflate stream consumes all 361 bytes,
declares 352 decoded bytes and produces exactly 352 bytes, with SHA-1
`ce6870cbf2581f3c64af32945759ba4615ee5fc6`. There is no unconsumed compressed
tail from which to recover another 16 decoded bytes.

A bounded comparison against the ROM flat payloads finds no longer payload
with the same complete 352-byte prefix, and no payload of at least 368 bytes
with the same 256-byte base image. This rules out those exact-copy recovery
hypotheses; it is not evidence that an approximately similar texture is valid.

## Sibling distinction

Three bank-01 runs use the same flat 1708 with a different, complete contract:

| Record | Run | Faces | Image command offset |
| --- | ---: | ---: | --- |
| `01:0112:00` | 10 | 3 | `0x3AD8` |
| `01:0178:00` | 8 | 3 | `0x2008` |
| `01:0180:00` | 18 | 1 | `0x2700` |

They load 352 bytes using `F3000000 070AF000` and set maximum mip level 2 with
`D7001002 FFFFFFFF`. Their first three I8 tiles have the same layout as above.
Entry 180 retains an unrelated tile 3 definition from earlier list state, but
its maximum level is 2. These siblings support the three-level source boundary;
they do not justify rewriting the bank-09 commands or synthesizing a fourth mip.

## Reproduction and reopening condition

The task-local read-only audit and metadata report are retained at:

- `build/assets/models/reference/continuation-20261001/i8-source-gap/audit.py`
- `build/assets/models/reference/continuation-20261001/i8-source-gap/audit.json`

From the repository root, the saved script can be rerun without changing files:

```sh
PYTHONDONTWRITEBYTECODE=1 PYTHONPATH=. python3 \
  build/assets/models/reference/continuation-20261001/i8-source-gap/audit.py
```

It validates the ROM identity, exact compressed framing, six source identities,
image-command offsets, parsed load/LOD/tile contracts and exact-prefix search.
It reads the ROM directly through existing archive/model loaders; it does not
use preview manifests, saved states, generated textures or capture inputs.
The script and report remain ignored research artifacts rather than exporter
or decoder changes. The report completed successfully on 2026-10-01.

Reopen this cohort when a submitted ordinary-object draw establishes one of
these models' relocated display list and complete 368-byte RDRAM texture source.
That evidence can reveal a runtime command rewrite or the actual overread bytes
and their provenance. An observed allocation alone would not establish a
universal ROM texture contract. Until then, retain the complete-load guard;
do not pad, generate a mip, copy a sibling's command contract or repeat the
unchanged constructor/flat-prefix searches.

Existing renderer/constructor proof is in
[US model constructor tables](../models/us_model_constructor_tables.md).
