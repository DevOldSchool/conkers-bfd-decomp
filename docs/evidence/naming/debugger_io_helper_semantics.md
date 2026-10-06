# Debugger framebuffer and controller helpers

Source: `src/debugger/debugger_0000.c`. This collection remains provisional,
not a recovered source unit; see [debugger overlay
evidence](../us_debugger_overlay.md).

| Symbol | C name | Registered bytes |
| --- | --- | ---: |
| `160012B0` | `debugger_draw_text` | 136 |
| `16001338` | `debugger_set_draw_color` | 88 |
| `160014F0` | `debugger_draw_glyph` | 284 |
| `1600160C` | `debugger_text_cell_address` | 108 |
| `16001678` | `debugger_clear_framebuffer` | 124 |
| `16001700` | `debugger_read_controller_pif` | 304 |
| `16001830` | `debugger_unpack_controller_pads` | 140 |
| `160018BC` | `debugger_pack_controller_read` | 200 |
| `16001984` | `debugger_si_is_busy` | 36 |
| `160019A8` | `debugger_start_si_dma` | 196 |

## Framebuffer drawing

Text drawing rejects null text and starting positions outside
`[D_160038A0 * 32, 0x341)`, then draws bytes until NUL. It does not wrap,
interpret newline controls, or clip the remaining string. Its original calls
at `160012EC` and `16001304` resolve the starting address and emit glyphs.

The shared draw color is RGB packed as RGBA5551, with alpha fixed to one.
Both glyph and rectangle drawing consume it (`16001508` and `16001454`), so
the alias does not restrict it to text. Glyph drawing reads eight bytes from
`D_16003CE0 + (character - 0x20)*8`, writes an opaque 8-by-8 block of 16-bit
pixels, and returns destination plus 16 bytes. Set bits use the shared color;
unset bits use pixel value 1. Inputs below 0x20 become space; there is no upper
character clamp or framebuffer clipping. The ROM data map records 96 glyph
slots, which does not make out-of-range reads valid.

The address helper uses five column bits, eight-pixel columns, origin (8,2),
and row spacing eight at framebuffer width 292, otherwise ten. It uses the
original position mask and does no bounds checking. `D_16003888` selects a
buffer from `D_8002AAE8`; `D_160038A8` supplies its width.

The clear helper fills with pixel value 1 in four-word chunks, using nominal
height 215 at width 292, otherwise 264. The original loop may pass the nominal
endpoint: width 292 writes 125,568 bytes, eight beyond width*height*2. This
coverage is preserved. The debugger loop calls it at `16000DE0` before redraw.

## Controller packets and SI transfer

The debugger loop requests controller input at `16000E1C`, then unpacks it at
`16000E24`. The read wrapper packs/sends a request when the previous command
is not 1, then waits 0x30D40 counter ticks. It fills the receive area with
32-bit value 0x000000FF, clears its final execution word, starts a read,
records command 1, waits 0xC3500 ticks and returns the read-start result.
The write-start result is ignored. These fixed counter waits are not DMA
completion checks; the original unsigned deadline comparisons remain.

Packet packing clears the 64-byte PIF buffer, sets its last word to 1, writes
one `FF 01 04 01 FF FF FF FF` record per configured controller and appends
0xFE. It performs no transfer. Unpacking uses eight-byte input and six-byte
output strides, stores `(rxsize & 0xC0) >> 4`, and copies buttons/sticks only
on zero error. Failed entries retain their previous buttons/sticks. Both
helpers trust the controller count.

The busy helper reads SI status at 0xA4800018 and tests DMA-busy/read-busy
bits 0 and 1. The DMA helper rejects unaligned buffers or busy SI, converts
the buffer address, and starts a 64-byte transfer using PIF address 0x1FC007C0.
Direction zero reads and invalidates the cache; any nonzero direction selects
write, but only direction one writes back the cache. It does not wait for
completion. Its registered span also contains empty `16001A64`; that body
remains numeric, unchanged and is not counted as another name.

## Independent evidence and acceptance

All 404 original instruction words (1,616 bytes) equal the checksum-validated
US ROM. Framebuffer index, color, minimum row, width and glyph payload hashes
were rechecked against [the debugger data
map](../us_debugger_data_objects.json). Pinned N64 SDK controller, SI and
cache/address helpers corroborate the hardware roles; runtime aliases remain
encoded as before. No source-object ownership or live debugger execution is
inferred.
