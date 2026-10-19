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
  (`150045BC`, `15040A4C`, `1507DB34`, `1507DB3C`, `1513E134`) were not
  promoted by this first pass. They sat inside spans that had no accepted C
  definition, so the compiler argument above had not yet been exercised for
  them. `150045BC`, `15040A4C` and `1513E134` were split later, once their
  parents' C reproduced every other word; see
  [the deferred-parent splits](#deferred-parent-splits) below.
  `1507DB34` and `1507DB3C` remain inside their raw span.

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

## Deferred-parent splits

Five deferred US game parents had preserved C candidates that reproduced
every word of their registered span except a final unlabelled `jr $ra; nop`
after the candidate's own complete epilogue. Their deferred scores (200, or
220 for `func_1513E084`) were exactly that missing pair, apart from two
branch-operand rows in `func_1513E084` that were fixed in C separately. This
exercises the compiler argument above for each parent: a single C function
cannot yield a second return sequence after its epilogue, so the eight bytes
are a separate empty function.

| Parent | Old span | New span | Split symbol | Source |
| --- | ---: | ---: | --- | --- |
| `func_15004574` | `0x50` | `0x48` | `func_150045BC` | `src/game/game_30E90.c` |
| `func_15040A40` | `0x14` | `0xC` | `func_15040A4C` | `src/game/game_6D800.c` |
| `func_1513E084` | `0xB8` | `0xB0` | `func_1513E134` | `src/game/game_169510.c` |
| `func_1516E8CC` | `0x3E0` | `0x3D8` | `func_1516ECA4` | `src/game/game_19A8B0.c` |
| `func_151957B0` | `0x7C` | `0x74` | `func_15195824` | `src/game/effects/characterflamethrower.c` |

The beta index independently proposes `150045BC` as an entry (see
[the remaining upstream C groups](game_remaining_upstream_c_groups.md)).
`15040A4C` and `1513E134` are the interior entry proposals that the
[dispatcher evidence](game_dispatcher_callback_groups.md#resolving-the-function-index-disagreements)
retained inside the preceding raw spans. `1516ECA4` and `15195824` have no
index proposal; they rest on the compiler argument alone. As above, no
callback identity or historical name is claimed, and no reference to any of
the five addresses exists in retail game data or code.

Each split added the label to `config/symbols/game-us.txt`, regenerated the
reference with `./conker game-asm` (only the five labels changed), resumed the
deferred parent and ran
`./conker split-game-function --parent <parent> --id <stub> --us <stub>`.
Each source then gained `void <stub>(void) {}` directly after its parent.
All ten spans scored `CURRENT (0)` through `./conker finish` and passed one
clean `./conker verify-batch` with the rest of the round-10 batch. The
source-unit boundaries are unchanged, and all five units remain mixed.
