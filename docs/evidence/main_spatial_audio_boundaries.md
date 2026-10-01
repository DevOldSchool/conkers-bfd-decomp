# Main spatial-audio calculation working family

Evidence kind: `structural_analysis`. The existing aligned raw range
`0xA420:0xB1B0` contains three complete entries (`0xA420`, `0xA750`, `0xB060`),
3,472 bytes. Split raw assembly and the independent unsplit CPU index agree
on all three exact spans. Every raw word matches the checksum-validated US
ROM and no main conditional branch crosses the outer endpoints.

## Positive relationship of all three members

`0xA750` selects spatial records from the indexed pointers/counts at
`0x800D2104/0x800D2108`, calculates the listener/source relationship, and calls
`0xA420` at `0xB034`. That helper produces attenuation and a packed pan/flag
result for the sound-record APIs; direct callers include `0xF838`, `0x115E8`
and game `0x1C2A30`.

The otherwise disconnected `0xB060` is the angular pan-only form of the same
operation. Both `0xA420` and `0xB060` call game angle helper `0x487E0`, use the
same `0.01f` threshold and identical double-angle scale bits
`0x40445F306DC9C883`, fold a signed angular result around the same pan extrema,
and encode it as `(pan + 0x40) | flag`, with the separate flag value `0x80`.
The constants occupy adjacent slots at main `0x2C200/0x2C208` and
`0x2C214/0x2C218`. Constant adjacency alone is not ownership evidence; the
specific algorithm/output format and consuming audio API provide the link.

The game caller at `0x1C2248` takes `0xB060`'s result, shifts it into the
packed command at `0x1C226C`, and submits it to the reviewed sequence control
at main `0xE7A0` through the call at `0x1C2284`. The `0xA420` game caller at
`0x1C2A30` separately masks the returned low seven bits and `0x80` flag before
calling reviewed sound-record operations at `0x1C2A68`, `0x1C2A80` and later
in the same caller. The relevant game raw words from `0x1C2050:0x1C2AD0` were
checked against the independently decompressed owned game overlay.

These concrete encoding/consumer relationships support the existing
three-member working family, rather than a new speculative file split at
`0xB060`. They do not establish an original filename, original static-data
ownership, or an exact stock-library identity. The legacy raw map is only
corroborating navigation context.

## Full spans and reproduction

| Member | US ROM span | Bytes |
| --- | --- | ---: |
| `func_8000A420` | `0xA420:0xA750` | 816 |
| `func_8000A750` | `0xA750:0xB060` | 2,320 |
| `func_8000B060` | `0xB060:0xB1B0` | 336 |

```sh
./conker register-source-unit --overlay main --source src/main/init_A420.c \
  --register-members --us-start 0xA420 --us-end 0xB1B0 \
  --evidence-kind structural_analysis \
  --evidence-reference docs/evidence/main_spatial_audio_boundaries.md
```

All members remain raw C candidates; no source implementation or C matching
credit changes. Canonical and reference maps retain their existing range.

The final full US ROM rebuild remains byte-identical. The whole range SHA-1
is `2607c2daad98189a0eec9d95d63aec0e1720607e`.

The final suite passes 1,071 tests (12 declared skips); metadata/progress and
whitespace checks pass. Existing function and source-unit records are preserved.
