# Consumer-proven effect record extents

These local layouts describe bytes consumed across effect-helper calls. They do
not establish original type names, meanings for unknown bytes, or historical
source-file boundaries. A caller's last explicit store does not bound an object
when a callee copies or reads farther.

The source representations below were checked at repository revision
`7a5ed61c2112a9ff3ebd5e48092ccb8f728cfce6`. Raw instruction-address observations
come from the recorded investigations in
commits [9d411be](https://github.com/DevOldSchool/conkers-bfd-decomp/commit/9d411be2469e10efa47a798570530b393867079c),
[7f6eff9](https://github.com/DevOldSchool/conkers-bfd-decomp/commit/7f6eff9d5674faa88c14ea50aeac01c43acda502)
and [a5e21d3](https://github.com/DevOldSchool/conkers-bfd-decomp/commit/a5e21d3f258521645b208a32f10f1314853c562c).
No ROM comparison or compilation was rerun for this note.

## The constructor copies 0x7C bytes

`func_15132A4C` forwards its first pointer unchanged to `func_1513264C`, as shown
in [game_15F680.c](../../../src/game/game_15F680.c). The recorded raw analysis places
the provider's exact 0x7C-byte copy at `151328BC..151328C8`. That extent applies
even when the caller initializes named fields only through halfword `+0x74`.

Two local caller representations retain the complete object:

| Caller | Current source type | Recorded raw object interval |
| --- | --- | --- |
| `func_15154884` | `Game154884Descriptor` in [game_17CAF0.c](../../../src/game/game_17CAF0.c) | `SP+0x40..SP+0xBB` |
| `func_150BB498` | `GameE8710Packet` in [game_E8710.c](../../../src/done/game/game_E8710.c) | `SP+0x2C..SP+0xA7`; address formed at `150BB6C4`, forwarding call at `150BB6D8` |

Both types end with `u8 unknown76[6]`, covering offsets `0x76..0x7B` and giving
the full 0x7C extent. The former two-byte tail described only 0x78 bytes and
left part of the provider's copy outside the standalone object. The current
callers do not initialize the unknown tail; no field semantics or extra writes
were invented to explain it.

This is distinct from the 0x70-byte descriptor consumed by `func_15130280`.
Descriptor extents follow each actual forwarding chain, not a common name or
similar-looking caller frame.

## Configuration and enclosing records

`func_151BFC40` writes two leading words, a series of scalar fields and six
halfwords through `+0x4E`, then writes a signed byte at `+0x50`. Its retained
source in [game_1ED0F0.c](../../../src/game/game_1ED0F0.c) also writes the separate
float output through its second argument. Under the target's four-byte natural
alignment, the configuration occupies **0x54 bytes**. Its embedded position is
three words at `+0x08..+0x13`; the recorded consumer review follows that exact
12-byte extent through to `func_151A26EC`.

The caller must represent the complete enclosing object passed downstream:

| Record | Member offsets | Extent |
| --- | --- | ---: |
| Upper | velocity `+0x00` (12 bytes), triangle `+0x0C` (18 bytes), natural alignment gap `+0x1E..0x1F`, float `+0x20`, configuration `+0x24` | `0x78` |
| Lower | velocity `+0x00` (12 bytes), float `+0x0C`, configuration `+0x10` | `0x64` |

The triangle contains nine signed halfwords, with size 0x12 and alignment two.
The recorded `func_15144E80` review establishes those nine reads and its three
12-byte vector outputs. The natural two-byte gap in the upper record aligns
the following float; it is not a new initialized field.

The existing forwarding implementations corroborate these member boundaries:

- `func_1514FBFC` passes input `+0x0C` to `func_15144E80`, reads the float at
  `+0x20`, and supplies configuration at `+0x24` to `func_1514F8F8`.
- `func_1514FB98` derives its basis through `func_15146078`, reads the float at
  `+0x0C`, and supplies configuration at `+0x10` to `func_1514F8F8`.

Both wrappers are in [game_17CAF0.c](../../../src/game/game_17CAF0.c). The position
and triangle facts are byte-layout contracts; a word-copy position view does
not imply numeric conversion, and the basis helpers do not make the two record
forms interchangeable.

## Caller copy order and limits

The retained `func_151BFE84` and `func_151BFDA0` forms in
[game_1ED0F0.c](../../../src/game/game_1ED0F0.c), and `func_150D728C` in
[game_1045D0.c](../../../src/game/game_1045D0.c), use these enclosing records rather
than adjacent independent scratch locals. In the upper branch, velocity,
triangle and position are written before configuration initialization. In the
lower branch, velocity precedes that call and position follows it. These
different orders remain explicit. The older 0x20-byte configuration scratch
array in `func_150D728C` could not contain a writer reaching byte 0x50.

These source repairs preserve unknown bytes and original initialization limits;
they are not padding added to force a frame. They do not establish a C match.
Subsequent source work still requires independent full-span comparison and
source-unit layout checks through the [ordinary focused gate](../../decompilation-workflow.md#match-one-function).
