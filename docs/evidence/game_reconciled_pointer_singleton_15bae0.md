# Reconciled US pointer-selected singleton at `0x15BAE0`

Evidence kind: `structural_analysis`. This review narrows the previously
excluded `0x15BAE0:0x15BE50` range to the first independently indexed function.
The generic source name is derived from its retail-ROM offset and does not
claim a recovered historical filename. The function remains raw assembly.

## Reviewed boundary

| Source | US range | Bytes | Function | Owned selection |
| --- | --- | ---: | --- | --- |
| `src/game/game_188F90.c` | `0x15BAE0:0x15BBF0` | 272 | `func_1515BAE0` | `0x8008C85C` -> `func_1515BAE0` |

The owned US game-data word at runtime address `0x8008C85C` contains
`0x1515BAE0`. The independent US function CSV records `func_1515BAE0` at
`0x15BAE0` with length `0x110`, giving the exact end `0x15BBF0`. The raw
reference exposes the same entry and span. Both endpoints are 16-byte aligned.

All branches in the function target labels inside the reviewed span. The final
epilogue returns at `0x15BBE8`, its delay slot is at `0x15BBEC`, and the next
raw function begins at `0x15BBF0`. The range SHA-1 is
`d347b9ee34a002cc25b3566b31d7cd5932867864`.

The independent debug-beta correlation maps the complete 272-byte function to
`func_1515FD80` with `strong` confidence and a 29-function matching sequence.
The ECTS index also maps the complete span to `func_1514B500`; that correlation
is supporting navigation evidence only.

## Reconciliation of the earlier exclusion

The earlier broad candidate ended at `0x15BE50`, where the independent CSV also
identifies the unlabelled eight-byte entry `func_1515BE48`. That discrepancy is
outside the narrowed `0x15BAE0:0x15BBF0` range. The neighboring family was
later reconciled and mapped separately in
`docs/evidence/game_raw_reconciled_empty_stub_splits.md`.
