# Extended US code-selected source groups

Evidence kind: `structural_analysis`. These three complete raw-map ranges combine
owned data selections, exact code-constructed addresses, internal calls, and
preserved beta order. Their generic source names derive from retail-ROM offsets;
all functions remain raw assembly.

The raw assembly index and independent US function CSV agree on every member
and span. All outer endpoints are 16-byte aligned and no conditional branch
crosses an endpoint.

| Source | US range | Entries | Bytes | Range SHA-1 |
| --- | --- | ---: | ---: | --- |
| `src/game/game_130B40.c` | `0x103690:0x103800` | 3 | 368 | `a04495cf8f0501222b3c90575cfee1d7fac9ce4d` |
| `src/game/game_1D5FD0.c` | `0x1A8B20:0x1A9060` | 5 | 1,344 | `9017aade52f4cfd7c3b844677e722be3a15ccd6c` |
| `src/game/game_20F9A0.c` | `0x1E24F0:0x1E84B0` | 38 | 24,512 | `828da8ae6f552b93fdbdbd2d816823f45e203e4b` |

## `0x103690:0x103800`

Owned word `0x8008CD40` selects opening `func_15103690`. Closing
`func_151037DC` is constructed at `0x675DC:0x675E4` and passed to
`func_1000FD38` as a callback. These two independent selectors bound the sole
intervening function and the complete existing raw segment.

## `0x1A8B20:0x1A9060`

Owned words `0x8008A57C` and `0x8008A960` select `func_151A8CEC` and closing
`func_151A9024`. Inside `func_151A8CEC`, code at `0x1A8E10:0x1A8E38`
chooses between local `func_151A8F6C` and `func_151A8F1C`, then invokes the
selected pointer through `jalr $s7` at `0x1A8E48`. All five members correlate
with both beta images; four are strong in each.

## Initially withdrawn candidate at `0x1DDC20:0x1DE8F0`

Owned words `0x8008FDEC`, `0x8008FE18`, `0x8008FDF0`, and `0x8008FDF4`
select four members across the range. `func_151DE7D4` calls local
`func_151DE85C`. Code at `0x1E7F08:0x1E7F38` constructs
`func_151DDC20` and `func_151DE7D4` as the endpoints of a word scan, providing
an independent exact relationship between the early and late portions.

Registration exposed a membership disagreement. The independent CSV records the
eight-byte `func_151DE6CC` between selected functions, while the raw assembly
index folds those words into the preceding member and registers only six of the
seven entries. The boundary was initially withdrawn with the supported command.
It was later reconciled by regenerating the empty stub as an independent raw
function; current evidence is recorded in
`docs/evidence/game_raw_reconciled_empty_stub_splits.md`.

## `0x1E24F0:0x1E84B0`

This is the complete remaining raw segment after the dispatch-controller core.
Code constructs exact addresses for `func_151E2834`, `func_151E30C4`,
`func_151E327C`, `func_151E4314`, `func_151E4BD8`, and
`func_151E4E00`. Owned words in the compact `0x8008FDFC:0x8008FE14` area
select `func_151E4264`, `func_151E43DC`, `func_151E4DD8`,
`func_151E4E64`, `func_151E4EE8`, `func_151E82B8`, and
`func_151E83E8`.

The internal call graph connects the range from beginning to end:
`func_151E2834` calls opening `func_151E24F0` and late
`func_151E7EF8`; `func_151E4314` calls `func_151E2834`;
`func_151E43DC` calls `func_151E530C` and `func_151E557C`;
`func_151E50C8` calls `func_151E5034` and `func_151E6BFC`; and
`func_151E51EC` calls `func_151E6964`. Code at `0xB9EF0:0xB9F24`
also constructs `func_151E7EF8` and `func_151E7F60` as endpoints of a word
scan. Twenty-four members correlate with the debug beta, 22 strongly; fourteen
correlate with ECTS, 12 strongly.

The dense selectors, local relationships, exact complete segment, and preserved
order establish the working boundary. Beta correlations are supporting identity
evidence only.
