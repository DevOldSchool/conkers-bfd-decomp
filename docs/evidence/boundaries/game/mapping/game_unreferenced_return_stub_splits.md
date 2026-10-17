# Unreferenced return-only stubs split from matched parent spans

Evidence type: `structural_analysis`

Two registered US game spans each ended with an unlabelled eight-byte
`jr $ra; nop` sequence that followed the parent routine's own complete
epilogue. Their C sources already carried that sequence as a separate empty
function definition, and the complete source units built byte-identically.
This record splits the two spans at those sequences so that each registered
span equals one C definition. It adds two canonical `func_<vram>` labels and
changes no instruction word, source body, map entry or source-unit boundary.

| Parent | Old span | New span | Split symbol | Split span | Source |
| --- | ---: | ---: | --- | ---: | --- |
| `func_15073054` | `0x24` | `0x1C` | `func_15073070` | `0x8` | `src/game/game_981E0.c` |
| `func_1507DB44` | `0x28` | `0x1C` | `func_1507DB64` | `0x8` | `src/game/game_A9D90.c` |

Owned retail game code SHA-1: `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.

## Why the spans were stale

Both parents were recorded as matched when the registered-span comparison
still extracted the candidate words from the whole focused object. The
following C definition in the same object supplied the trailing `jr $ra; nop`,
so the 36- and 40-byte spans scored `CURRENT (0)`. Since the comparison was
hardened to score only the candidate symbol's own words (short interior
extents are truncated to their real instructions so missing words count),
`./conker finish` on either parent reports `CURRENT (200)` with the last two
reference rows missing, on an untouched checkout as well. The unit builds
remained byte-identical throughout, which is why `verify-batch` never failed.

## Why a split rather than a longer parent

The retained bytes at `0x73070` and `0x7DB64` are

```text
03E00008  jr   $ra
00000000  nop
```

immediately after the parent's own `jr $ra; nop`. The pinned IDO compiler
emits exactly one epilogue per C function and removes unreachable code at the
game units' optimisation level, so no single C definition can produce a second
return sequence after a completed epilogue. The only source-level construct
that yields these words at these addresses is a separate empty function, which
is what both sources have defined since their original matches. Treating the
words as parent padding would require either a C body that the compiler cannot
produce or a comparison that again borrows words from a neighbouring symbol.

## What this record does not claim

- No function-pointer table or code reference to `0x15073070` or
  `0x1507DB64` exists in retail game data or code; the earlier
  [callback-symbol review](game_return_callback_symbols.md) stands. These
  labels name address ranges whose C definition is an empty function, not
  callback identities or historical names.
- The source-unit boundaries, membership order and integration states of
  `game_981E0.c` and `game_A9D90.c` are unchanged; the new members sit between
  their parent and the parent's former successor.
- The other unreferenced return sequences retained inside raw spans
  (`150045BC`, `15040A4C`, `1507DB34`, `1507DB3C`, `1513E134`) are not
  promoted here. They sit inside spans that have no accepted C definition, so
  the compiler argument above has not yet been exercised for them; the
  [deferred `func_15040A40` caveat](../../main/main_boundary_residual_frontier.md#separate-game-function-span-caveat)
  still applies to them.

## Transaction and validation

Each split used the inventory transaction

```sh
./conker split-game-function --parent func_15073054 --id func_15073070 --us func_15073070
./conker split-game-function --parent func_1507DB44 --id func_1507DB64 --us func_1507DB64
```

after adding the two labels to `config/symbols/game-us.txt` and regenerating
the raw reference with `./conker game-asm`. The transaction requires the
regenerated reference to partition the registered span exactly at the new
symbol, records the new member as raw ASM inside the parent's source unit,
shortens the parent span and withdraws the parent's stale match evidence. The
regenerated reference added exactly the two labels and changed no instruction
word. All four spans were then re-proved through `./conker finish` and a clean
`./conker verify-batch` with the four work items.
