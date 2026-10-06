# US bank09 model213 script consumer

The guarded script-object material context is implemented in
`scripts/model_script_object_materials.py` and consumed by the ordinary bank09
preview exporter. It admits a proved initial state, not every runtime object
state.

## Source and consumer

The guarded US ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`. Bank06
path `[6,1,8]` spans ROM `[0x11867B8,0x1186A48)`, decodes to 1,600 bytes, and
has SHA256 `964e3c6a56a067b613bc2ad7eff537c64ce0e1d938659079ea5bec773f939baf`.
Child36 selects stream 8 `[0x5D8,0x640)`; the command at 0x5F8 is operation95,
suboperation14, signed selector 13 at byte 5. Header counts 9/9/9/0, descriptor
at 0x1C0, directory boundaries and the entire script identity are checked.

The guarded route is `1502A8A0 -> 150265CC/15028D94 -> 1519EA78 -> 15152190 ->
15132A4C -> 15132B80`. The earlier dispatcher1502460C returns zero for this
command under both global-gate arms without calls. Selector13 indexes model 213
in the table at 800A38B4. Initial flags 0x29E8 leave texture callback bit 16
clear; kind 25/72 draw dispatch, downstream constructors, code spans and tables
are independently guarded by the active module.

This proves a stored command's consumer and the initial callback-disabled
ordinary object material context. Gameplay activation, later flag changes,
visibility, opacity, colors, animation and native raster parity remain unknown.

## Export and verification

```sh
./conker model-assets preview --bank 09 --rom roms/baserom.us.z64 \
  --output build/assets/models/us-bank-09
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s tests \
  -p 'test_model_script_object_materials.py'
```

Model213 retains 10 vertices/UVs, four faces, one material run, zero joints and
zero stored clips. The output status is
`rom-state-consensus-runtime-composed-direct-ci4-texture`.

Model decoded SHA1: `0e839656358777ef96e6c45a737691b9adfa0a1a`. Flat4536 decoded
payload: 1,536 bytes, SHA1 `2d59d0fc642ac0fe4e1b299ae5a1eb66212e5d08`. The 32x64
CI4 base image uses pixel offset 0 and TLUT offset 1504; output PNG SHA1 is
`0597808abcc13fbe610e3e72e3f3aee69b2e2f92`. The material retains its source
mip/tile commands and combiner `FC26A004/1F1493FF`. Texture lookup agrees across
the guarded segment 8 tables; this is not full render-state consensus.

An independent read of emitted glTF buffers with
`model_validation.compare_geometry` checks all four faces and 12 UV corners
against the ROM parser. Focused tests cover full-source mutations, independent
structure mutations, invalid signed selectors and an unverified-ROM rejection.
These checks do not launch a renderer. Entries407–412 remain unresolved; this
proof does not admit them.
