# Display-list callback and state helpers

Display-list callbacks and command state; continued packet macros remain
unchanged. No scene or character identity is inferred.

| Symbol | C name | Span |
| --- | --- | --- |
| `15174AA4` | `display_list_dispatch_first_draw_callback` | `0xA4` |
| `15174B48` | `display_list_dispatch_second_draw_callback` | `0xA8` |
| `1517EA4C` | `display_list_setup_primitive_rgb_texel_modulated_alpha` | `0x60` |

## Callback envelopes

Both dispatchers append PipeSync (`E7000000/00000000`) and a matrix command
(`DA380003/80089470`), optionally invoke a callback, then append the same
matrix command. The unsigned configuration selectors are at `D_800B0DF0`
`+0x0C/+0x0D`, using `D_8008CD74/D_8008CD7C`, respectively. “First” and
“second” distinguish those selectors; they do not mean opaque/translucent or
assert a universal rendering order.

Zero skips dispatch. For nonzero indices, the callback receives the advanced
cursor and the wrapper's original third argument, and supplies the next cursor.
The middle argument remains unused apart from its ABI home store. There is no
index, null-callback or command-capacity check. The wrappers append three
commands plus any callback output; callback side effects are not bounded here.

Pinned SDK `PR/gbi.h` identifies `E7` as PipeSync. Its F3DEX2 matrix encoding
makes `DA380003` a 64-byte MODELVIEW | LOAD | NOPUSH operation: the encoding
XORs the push flag. The last command reloads the fixed matrix at `80089470`,
not an arbitrary prior matrix or a saved matrix-stack entry. No identity-matrix
claim follows. Original calls at `15018EF0/15018F24` consume renderer-produced
cursors and pass the results onward to rendering.

Existing cross-source declarations in `game_45B80.c` differ from the helper
definitions, including a void return declaration for the first dispatcher.
These declarations and all callback argument/return types remain unchanged.

## Primitive RGB with modulated texture alpha

`1517EA4C` appends exactly 24 bytes and returns the advanced cursor:

- `E7000000/00000000`: PipeSync
- `FCFFB3FF/FF65FEFF`: both combine cycles produce primitive RGB and
  primitive alpha multiplied by TEXEL0 alpha
- `EF002C0F/00504344`: the original complete other-mode words

The pinned GBI definitions decode the last mode as one-cycle, bilinear,
`G_TC_FILT` texture-conversion mode, no texture perspective correction, primitive
depth source and CLD_SURF/CLD_SURF2 blending. All raw bits, including low
high-mode bits `0x0F`, are preserved. The helper does not set primitive color,
load a texture or write global state. Caller `1517E8A0` uses it under the
`D_800DDD60 == 0` gate and forwards its cursor at `1517E8DC`; the caller owns
the later global update.

## Evidence and spans

Original references `1749A0.s` and `17E080.s` cover all 428 target bytes.
The second dispatcher includes its trailing NOP at `15174BEC`, after the
return delay slot. Opcode evidence uses the repository's unchanged pinned
SDK (`87af1e4d8ed666f2ad407dc11c6e47736094f2f8`), especially `gbi.h` matrix,
combiner and other-mode definitions. Static command/caller evidence is not a
runtime render or broader callback-behavior proof.
