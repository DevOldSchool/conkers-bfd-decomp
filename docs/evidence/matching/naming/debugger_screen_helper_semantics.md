# Debugger menu, register and stack pages

Source: `src/debugger/debugger_0000.c`; collection boundaries remain
provisional. See [overlay evidence](../../debugger/us_debugger_overlay.md) and [the
original data map](../../debugger/us_debugger_data_objects.json).

| Symbol | C name | Bytes |
| --- | --- | ---: |
| `16000058` | `debugger_draw_main_menu` | 460 |
| `16000224` | `debugger_handle_main_menu_input` | 240 |
| `16000314` | `debugger_draw_register_page` | 112 |
| `16000384` | `debugger_handle_register_page_input` | 160 |
| `16000424` | `debugger_draw_exception_summary` | 364 |
| `16000590` | `debugger_draw_float_register_page` | 316 |
| `160006CC` | `debugger_draw_general_registers` | 192 |
| `1600078C` | `debugger_draw_stack_view` | 720 |
| `16000A5C` | `debugger_handle_stack_view_input` | 184 |

## Page dispatch and menu

Original display table `16003AF8` is `[16000000,16000058,16000314,1600078C]`;
input table `16003B08` is `[16000028,16000224,16000384,16000A5C]`. Entry selects
both with `D_16003AF4`: slots 1/2/3 pair menu, register and stack-page callbacks.
Input result 1 requests drawing, result 3 also clears the framebuffer, and
result 4 exits the loop. These are static routes, not runtime-activation proof.

The main menu draws original `MAIN MENU`, `REGISTERS`, `STACK`, highlighted
selection, conditional `CONTINUE` / `HOSTDEBUG` / `RETRY CODE`, and build text.
`HOSTDEBUG` is only a menu label, not proof of host communication. Synthetic
stick up/down edge bits cycle three selections; A enters register page 2,
stack page 3 or returns 4. Empty bodies `16000304/1600030C` remain numeric and
unchanged inside the main-menu input's registered span.

Register-page mode zero draws exception summary and general registers;
modes one/two select the floating-register display. C-down/right advances
three modes, C-up/left goes backward, and B chooses main-menu page 1. The
C-button paths return early, preserving their precedence over simultaneous B.

## Saved thread context

Original labels and loads in `16000424` establish PC at thread+0x11C, cause
at +0x120, status at +0x118, bad virtual address at +0x124 and thread ID at
+0x14, plus optional `Lockup_Now`. Exception text indexes the 16-entry table
at `16003848` with `(cause >> 2) & 0xF`; exception 11 also displays the
coprocessor number. Preserve that four-bit mask rather than claiming complete
architectural exception decoding.

The float page draws FPCSR at +0x12C, six cause descriptions for bits 12..17
and sixteen `fp` rows. Mode one labels fp0..fp15 and reads +0x134+8*i; mode two
labels fp16..fp31 and reads +0x1B4+8*i. These are the low 32-bit words of this
game's 32 individually saved 64-bit floating-register slots. The original US
exception code, not a generic SDK structure, proves the relationship:
ROM `[0x736C,0x73EC)` saves f0..f31 at thread+0x130+8*n, and
`[0x7B2C,0x7BAC)` restores them. All 64 save/restore instructions were checked.
The stock SDK's 16 paired-slot context must not replace this observed layout.
The numeric helper's mode 2 interprets each selected word as f32 for display;
it does not display the full saved 64-bit value.

General-register display uses 28 three-byte descriptors at
`[160037F0,16003844)`, followed by a zero sentinel. They select v0/v1, a0..a3,
t0..t9, s0..s8, sp/gp/ra, loading the low word at thread+4*(index+1) for hex
rendering. This is a selected low-32-bit display, not all 64-bit register values.

## Stack memory viewer

`STACK-VIEW`, saved SP's low word at thread+0xF4 and the word offset at
`16003B4C` establish this role. It draws 22 consecutive memory words with
addresses, hexadecimal values and decimal interpretations; color depends on
address ranges/value high bytes. It is not an unwinder. Only the initial
aligned address is checked against the inclusive range
`0x80000000..0x80800000`, not the full read span.

Held stick Y above 40 or C-up edge decrements the word offset; stick Y below
-40 or C-down edge increments it. The input helper clamps the offset to
0..200 and B selects main-menu page 1. Original asymmetric redraw results at
the lower and upper clamps remain unchanged.

## Evidence and acceptance

All 687 original instruction words (2,748 bytes) agree with the checksum-
validated US ROM. Twenty-five relevant data-map hashes and literal strings
were rechecked, together with original callback tables and exception-save
layout. References are `reference/us/asm/debugger/debugger.s` and `71D0.s`. No
new C match, source ownership or live debugger execution is claimed.
