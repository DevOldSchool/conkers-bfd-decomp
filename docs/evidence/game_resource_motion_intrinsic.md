# Resource-motion absolute-value helper (US)

`func_15133B98` in `game_15F680.c` is a 192-byte helper that scales six
float fields, updates another float field, and clears the scaled fields and
selected flags when the resulting `+0x48` magnitude is below 4.0f.

Its independent raw body in `reference/game/us/asm/1321D0.s` uses `abs.s`
at `15133BFC`, with no function call or stack frame. The previous block-scope
float declaration for `fabsf` compiled an ordinary call.

Moving `f32 fabsf(f32);` to file scope and adding the existing project-standard
`#pragma intrinsic(fabsf)` restores the frameless absolute-value instruction.
The same declaration/directive pair is already used by matched `func_15117518`
in `game_1449A0.c`.
Only `15133B98` calls `fabsf` in this unit. No compiler flag or tool changed.

The accepted source orders the independent updates by actual field position:
`+0x3C`, `+0x44`, `+0x48`, `+0x4C`, `+0x50`, `+0x54`, and `+0x58`, followed
by the magnitude test on the updated `+0x48` field. All fields are distinct
four-byte locations, the scale remains captured from `+0x14`, and the same
arithmetic operations, cleanup stores, flag mask, return value, and established
six-argument interface are retained. This produced full-span `CURRENT (0)`
and preserved the reviewed mixed-unit symbol layout.

The accepted direct callers `15133C58` and `15133D20` keep their existing
six-argument calls. Independent source review found no narrowed formals,
arithmetic reassociation, artificial storage, aliasing workaround, or
unrelated source changes.

This adds one 192-byte C match. The source unit remains mixed; the match does
not complete its other assembly-backed members.

## Acceptance and existing terminal diagnostic

The canonical clean batch for all 18 accepted members returned
`BATCH_COMPLETE`. The new helper and 16 existing members independently
reported focused `CURRENT (0)`. The unchanged terminal member `15133FD8`
reported `CURRENT (100)`: its focused C-only object lacks the last registered
NOP. An isolated copy of baseline commit `0eeee099437ad6a5c4ce57ab73d35f8836821879`
has the identical diagnostic, so this is not introduced by the new helper.
No tool, comparison gate, terminal source, or padding was changed to suppress it.

Independent production-object checks preserve all 31 member offsets and
extents, the complete `0x1EA0` text extent, and every registered linked span
against the checksum-validated ROM, including all 152 bytes of `15133FD8`.
The full US ROM, RSP payloads, GAME image, and mapped external rodata remain
identical; no data, rodata, or BSS storage was added. All 1,703 tests passed
in the ordinary suite (37 tool-dependent skips) and pinned toolchain/ROM
suite (one skip). Progress and whitespace checks passed.
