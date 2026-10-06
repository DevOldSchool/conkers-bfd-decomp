# US particle203 initial texture state

The guarded helper in `scripts/model_particle203_materials.py` admits only
`(bank=9, entry=203, segment=0)`. Entry203 has 12 vertices, 20 faces and one CI4
material. Its missing lookup/combiner state comes from the particle renderer,
not the ordinary-object material context.

The US normalized ROM SHA-1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
Entry203 occupies compressed ROM `0x122DE78:0x122DF88`, decodes to 392 bytes,
and has SHA-256
`a54ec90e727542926329a9e15b43153d714d0902f9e79b081603e54bbf9f3b2d`. Its complete
parsed material-run digest is
`9c1a7792abf7ef5fbe319808a69e8fa0694143969bc011e65b809745cda9f766`. Both
identities are required at material resolution; source commands, UVs, vertices,
faces, and unknown source inherited-state fields remain unchanged.

The consumer chain is independently authenticated with full function hashes and
separately checked instruction landmarks:

- `func_15169C70` loads entry203 into `a1` at `0x1516A0DC` and calls
  `func_15171200` at `0x1516A0E8`.
- `func_15171200` keeps that identifier in `s1`, passes it to
  `func_1518C900` at `0x15171384`, and saves the returned model list at
  descriptor `+0x40`. The loader selects indexed bank 9 and resolves its custom
  flat texture commands through `func_1510CE60`.
- The emitter builds its descriptor at stack `+0x7C`. Stores at
  `0x151712E0/0x151712E4` set descriptor `+0x5C/+0x5D` to 1.
  `func_15168BE4` allocates particle type 16 and copies 0x60 bytes to object `+0x90`.
  Thus object `+0xEC/+0xED` are 1, and object `+0xD0` is the loaded display list.
  `func_15167A68` and `func_15168A4C` establish the type in object byte 0.
- The complete 13-word type 16 dispatch record at `0x8008B7E8` selects
  `func_15168C4C`; its pre-list/material callback fields are zero. The full
  shared dispatcher`func_151674F8` is pinned too.
- `func_15168C4C` reads object `+0xEC` and chooses low OtherMode`0x00552230`
  for value 1. It passes high mode `0x0008ACA0` to`func_15142FBC` at
  `0x15168DA4`; that helper ORs 15 and emits or reuses matching cached state
  `EF08ACAF 00552230`.
  Object`+0xED=1` selects `FC123824 FF73FFFF`, stored at `0x15168DD0`.
  Only afterward does the renderer emit the display-list call using object `+0xD0`.

The combiner uses `TEXEL0 * SHADE` RGB and `PRIMITIVE * SHADE` alpha. It never
samples texture alpha. The helper verifies the actual flat332 payload, decodes
the unchanged CI4 RGB through the existing guarded direct decoder, and creates a
derived texture with alpha 255. It retains the original CI4 PNG hash alongside
the derived PNG hash. The original payload and its palette alpha are not
changed. Dynamic draw colour/alpha, later state, transforms, timing, and native
raster parity remain unresolved. This is an initial-constructor texture preview,
not an observed frame or a claim covering every later particle state.

Flat332 is identified through the runtime compressed-size table, not a physical
stream ordinal. Its compressed span starts at `0x226493` and is 1,687 bytes; the
decoded payload is 2,080 bytes: 2,048 CI4 bytes plus a trailing 32-byte RGBA5551
palette. Its SHA-256 is
`c31c40010a97998f387019fd5b47a50d2daec1aeadbf8f9a6d29e3df2bb4b3f8`. The run
loads that flat in mode 0 for pixels and mode 2 for the palette, selects a 64×64
CI4 tile and a complete 2,048-byte LoadBlock. Odd rows use the proven 32-bit
half-word swap. The image follows the existing PNG vertical orientation and
five-bit channel expansion (`channel*255//31`).

The derived PNG SHA-256 is
`b0837b5c2256160504d5ceca9ec284dabb05f58dfa8b2a441dd081c7fc3f7cdd`; its decoded
RGBA SHA-256 is
`5093d03502521128ae88b6f2a743426998f29dd235d719a3af0611e41d381b45`. All 4,096
pixels were compared with an independent scalar decoder. Source OBJ SHA-256
`2c5c19151138ee9e152f40b993866b81a8ec6ffd24ffe4a4996599aaac92ac6e` and
geometry/UV binary SHA-256
`52a698f83296a43a60fa1266298c1a0a724492b9fa2ee11fadfa277d1240c2ec` identify the
reviewed source buffers, which remain unchanged by this material update.

Focused tests check full consumer-span mutations, semantic guards even under
repinning, all dispatch words, source/model/payload/run changes, identity and
selector scope, unchanged inputs, every decoded pixel, and manifest-to-glTF
evidence retention. A separate real-ROM check rejects ten consumer mutations
against the actual production pins. Synthetic fixture pins are only substituted
inside tests; the production constants remain the actual ROM-derived hashes.

The integration merges this context without overlap, excludes it from the
ordinary-object segment 8 consensus path, and resolves it only in the uncaptured
unresolved-texture branch. Evidence is retained as `rom_particle_texture_state`
and glTF `romParticleTextureState`. No runtime capture, save state, Blender
output, or UI observation is an input.

## Reproduction

```sh
./conker model-assets preview --bank 09 --rom roms/baserom.us.z64 \
  --output build/assets/models/us-bank-09
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s tests \
  -p 'test_model_particle203_materials.py'
```

The guarded update preserves source OBJ and geometry/UV binary buffers.
Independent glTF comparison checks 20 faces and 60 UV corners. Regenerate
exports and run the checks for the current checkout; full-bank totals change
when other consumers are added and are not part of this isolated material proof.
