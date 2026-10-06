# Debugger session, prompt and numeric rendering

Source: `src/debugger/debugger_0000.c`; ownership remains provisional. Empty
and identity helpers stay numeric. See [debugger
overlay](../us_debugger_overlay.md),
[framebuffer/controller](debugger_io_helper_semantics.md) and
[screen](debugger_screen_helper_semantics.md) evidence.

| Symbol | C name | Bytes |
| --- | --- | ---: |
| `16000000` | `debugger_draw_button_prompt` | 40 |
| `16000028` | `debugger_handle_button_prompt_input` | 48 |
| `16000B14` | `debugger_run_session` | 1144 |
| `16000F8C` | `debugger_draw_f32` | 184 |
| `16001044` | `debugger_draw_numeric_value` | 620 |
| `16001390` | `debugger_fill_rect` | 352 |
| `16001A6C` | `debugger_f32_is_subnormal_or_nonfinite` | 68 |

## Prompt and session

The prompt draws original `PRESS BUTTON` at text position 0x116. Page-zero
slots in `D_16003AF8/D_16003B08` select this draw/input pair. Input accepts
newly pressed A/B bits 0xC000, selects main-menu page 1 and returns 3 for
redraw/clear; otherwise zero. It does not accept every button. Other main-code
references to `16000000` use the overlay base, not a call to the prompt body.

The session entry is independently established by JAL word 0x0D8002C5 at main
ROM 0x8070, interpreted through main's 0x1000xxxx runtime alias. After early
exit checks, it captures TLB state, selects a thread and framebuffer, and
dispatches page drawing/controller input until an exit result. It records
button edges and synthetic stick-direction bits for the input callbacks.
The existing TLB capture, saved-entry substitution, thread-selection logic,
framebuffer fallback and first-iteration behavior are unchanged.

On applicable exit paths it changes selected-thread state or advances saved
PC by four, returning one; other paths return zero. The alias does not promise
successful execution resumption. Early-gate purpose and live entry/resumption
remain unresolved, as documented by the overlay evidence. No new exception,
privileged-state or thread behavior is introduced.

## Numeric rendering and binary32 classification

`16000F8C` applies the original text-position bounds and renders a binary32
input. Normal encodings and both signed zeros reach `cvt.d.s` promotion and
formatting through the ROM string `%s%s%f` with two empty strings. Subnormal,
infinity and NaN encodings all draw literal `NaN`. That placeholder does not
mean every rejected encoding is mathematically NaN.

`16001044` supports mode zero for eight uppercase hexadecimal digits, mode one
for signed decimal, and mode two for binary32 interpretation of the supplied
word with the same placeholder policy. Mode two reinterprets bits, rather
than converting an integer's numeric value to float. The signed-decimal
arithmetic, including its INT_MIN edge behavior, remains unchanged; no
standard-formatting conformance is claimed. Menu, register and stack displays
provide concrete callers.

`16001A6C` stores its binary32 input, tests for either signed zero by shifting
away the sign bit, then examines exponent bits 23..30. It returns zero for
signed zero and finite normal encodings, one for subnormal, infinity and NaN
encodings. It is not equivalent to `isnan`, `isfinite` or `isnormal`.

## Filled rectangle

The fill helper writes the current 16-bit draw color over inclusive
left/top/right/bottom coordinates, using framebuffer width as pixel stride.
Coordinates are relative to `debugger_text_cell_address(0)`, including that
helper's origin inset. Negative left/top or reversed endpoints return early.
There is no upper clipping; signed-16-bit endpoint arithmetic is retained.

A bounded source/reference search found no direct symbolic callers for the
standalone f32 renderer, rectangle filler or classifier. Their bodies support
the generic names, without establishing runtime reachability.

## Evidence and acceptance

All 614 original instruction words across the seven registered spans (2,456
bytes) agree with the checksum-validated US ROM. Prompt, format and
placeholder strings and page-zero callback entries were also read directly
from that ROM. Sources are original debugger assembly, main `71D0.s`, loaded
debugger data and [the data map](../us_debugger_data_objects.json). No new C
matches, source-unit completion or runtime debugger execution are claimed.
