# Blocked-function recovery evidence (US)

The two recovered switch layouts are documented separately in
[blocked_switch_jump_tables.md](blocked_switch_jump_tables.md).

## Return and argument declarations

`func_1513264C` returns zero on allocation failure and returns its object pointer
in `v0` at `0x15132A34`. Its wrapper, `func_15132A4C`, forwards that value.
`func_150121C0` tests and dereferences it after the call at `0x150122F4`.
The wrapper and its source-local declaration now return `void *`, consistent
with the existing pointer-returning declarations of the underlying allocator.
The caller in `game_E8710.c` has the same declaration. Both the wrapper and that
existing caller retain focused `CURRENT (0)` and their source-unit layouts.

`func_100257C0` is the verified SDK address of `__osSiRawStartDma` in
`config/game/us-sdk.ld`. The SDK implementation and declaration return `s32`
and take `(s32, void *)`. `func_151DD710` saves and tests this result after both
DMA calls. Its previous `void` declaration was incorrect. The command byte
`D_80042A50` is unsigned in this source, retaining the raw `0xFE` immediate.

`func_150A7BC0` is a raw identity-matrix leaf which reads only `a0` and never
reads `a1`. The two calls in `func_15157010` pass only a matrix address, whereas
the existing matched `func_15157860` also forwards an ignored `a1`. An
unspecified argument list in this source preserves these legacy assembly call
forms without adding a second argument to the one-argument calls. Both callers
pass focused `CURRENT (0)`. The resource helper `func_1503F62C` also receives
full-width words here: its raw entry forwards `a0` through `s0` and stores `a1`
as a word. Its local declaration preserves those widths.

## Additional recovered C functions

`func_150121C0` passes focused `CURRENT (0)` and layout. An explicit `for`
increment with the original unsigned-byte narrowing reproduces the initialization
schedule. The supported `finish` transaction recorded the match; its single-function
source unit is complete at `src/game/done/game_3F670.c`, with a byte-identical
integrated US image.

`func_151DD710` also passes authoritative `CURRENT (0)` and layout. Its preserved
best candidate required no further instruction changes. Four symbolic operand
rows used `D_800E0A30 + 0x40` versus `D_800E0A70`, and `D_800E0A30 + 1` versus
`D_800E0A31`. Independently linking the candidate and raw-reference objects at
the registered address produces identical 432-byte text spans. Both equal the
same span in the checksum-validated US ROM, with SHA-256
`c51a23bbe7fe6165730dfb1124f21b86f4db02ac06250af4cbc1960d36e18206`.

The explicitly authorized verifier correction in `scripts/linked_aliases.py`
uses this full-span proof before feeding independent linked bytes to bounded
asm-differ. It supports only address-bearing external bootstrap relocations;
unsupported cases retain the normal symbolic comparison. Original objects still
supply switch-table evidence. Neither the original assembly nor compiler flags
are changed, and match inventory is recorded only through `finish`.

Regression checks cover wrong addresses, signed-low carry, word-aligned entry
addresses, final-instruction changes, incorrect extents, unsupported symbols,
and disagreement between linked raw reference and ROM. Live watch mode keeps
its original symbolic objects and requires a fresh `finish`.

## Verified original assembly

Both spans below are classified as `original_asm` through
`conker verify-original-asm`. Each unchanged canonical assembly body is assembled
with the existing GLOBAL_ASM context, linked at its registered address, and
compared across the entire registered span with checksum-validated US ROM bytes.
The host transaction records the ROM, span, and assembly hashes. `verify-batch`
repeats these proofs. They are excluded from C-match counts and matched bytes;
their source units retain original assembly and are not declared complete C units.

`func_150A7360` (`0x150A7360:0x150A751C`) belongs to the reviewed handwritten
entry family. It uses trapping `add`/`sub`/`addi`, deliberate interior entry
labels at `0x150A745C` and `0x150A74CC`, and restores saved registers from
negative stack offsets after increasing `sp`. This is not an ordinary IDO C
function that can be recovered by declaration changes.

The word-only span named `func_150AA814` is not entirely data. Disassembly of
its raw words establishes instructions through `0x150AA988`, followed at
`0x150AA98C` by the ASCII debug format `%s%sv %f %f %f\n` and zero padding to
`0x150AA9A0`. The code consumes live floating registers including `f23` through
`f31`, saves `ra` in `t9` at `0x150AA828`, calls `0x150AA778` three times, and
returns through `jr t9`. Merely decoding the words or trimming the string
would not turn this custom register convention into a compiler-compatible C
function. Its complete 396-byte registered span remains unchanged.

The verified spans are 444 and 396 bytes respectively. Their registered extents
and original source placeholders are unchanged; no new handwritten assembly was
introduced.
