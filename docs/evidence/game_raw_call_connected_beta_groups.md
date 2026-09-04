# US call-connected and cross-version source groups

Evidence kind: `structural_analysis`. These three still-raw ranges are complete
working source families recovered from internal calls, owned selections, and
cross-version order. Generic source names derive from retail-ROM offsets and do
not claim historical filenames. All functions remain raw assembly.

The raw assembly index and independent US function CSV agree on all entries and
spans. Every outer endpoint is 16-byte aligned and no conditional branch crosses
it. The beta comparisons support preserved function order; they do not by
themselves establish a boundary.

| Source | US range | Entries | Bytes | Range SHA-1 |
| --- | --- | ---: | ---: | --- |
| `src/game/game_79F10.c` | `0x4CA60:0x52260` | 5 | 22,528 | `33b9ec9e6a80b2eaba3a742919cd15b892e9ef51` |
| `src/game/game_B3020.c` | `0x85B70:0x86BD0` | 6 | 4,192 | `3756789894a0620771cf7e16a823ab676aaf55f7` |
| `src/game/game_1CE2F0.c` | `0x1A0E40:0x1A3150` | 21 | 8,976 | `8c7f83ce16ad3f545931e115980b1805a9754596` |

## `0x4CA60:0x52260`

Owned word `0x80086018` selects the central 18,000-byte controller
`func_1504CB98`. That controller calls all four other members, directly or
through the closing helper chain: it calls opening `func_1504CA60`,
`func_15051558`, and `func_1505210C`; `func_150511E8` also calls
`func_1505210C`. The five entries therefore form one connected range rather
than a size-based guess. Three members retain beta correlations.

## `0x85B70:0x86BD0`

The opening pair is a direct local relationship:
`func_15085B70` -> `func_15085BE8`. In the remaining group,
`func_15086098` calls `func_15085DA8`, `func_15085DF8`, and
`func_15086364`; the closing function is part of that same local chain. Five
of the six functions correlate strongly and in order with both beta images.
The uncorrelated middle controller accounts for the local links between the
otherwise preserved members.

## `0x1A0E40:0x1A3150`

This range supersedes the narrower raw-only `0x1A2960:0x1A3150` boundary. The
opening four functions form a complete helper family: three wrappers call
`func_151A11CC`. Eight consecutive owned selections at
`0x8008A4CC:0x8008A4F8` and `0x8008CA08:0x8008CA14` cover the following
callback sequence through `func_151A25E0`.

The final family has owned selections for `func_151A2960` at `0x800897A4`
and `func_151A2F0C` at `0x8008F8E0`. `func_151A2A14` and
`func_151A2AD4` call `func_151A2C24`; that function calls the intervening
`func_151A26EC`. It also chooses locally constructed pointers to
`func_151A2B84` and `func_151A2BD0` at `0x1A2C7C:0x1A2C9C`. This backward
call is why the earlier split at `0x1A2960` is not retained.

Twenty of the 21 members correlate with the debug beta, 17 strongly. Nineteen
correlate with ECTS, 16 strongly. The complete pointer and call coverage,
preserved order, exact membership, and existing aligned end establish the
working boundary.
