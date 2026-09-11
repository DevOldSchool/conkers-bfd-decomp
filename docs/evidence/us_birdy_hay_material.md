# Birdy's hay transparency

The user identified bank-01 entry 139 as Birdy and supplied a visual reference
showing thin hay strands. The inspection export instead showed solid yellow
triangles. Its seven hay runs had no linked image because the direct intensity
decoder rejected their two-cycle alpha expression.

The primary ROM draw table contains 24 hay faces in runs 13, 14, 16, 18, 21,
23 and 24. They address flat texture 7272 with `FD700000`, load 2,048 bytes
through an RGBA16 transfer tile (`F5100000`), and render IA8 with tile
`F5680800 00098250` at 32 by 64 texels. The decompressed payload SHA-1 is
`53322278c58203b511eaaf8f49ee9eca072e398f`.

Combiner `FCFF9880 F514FEFF` computes first-cycle alpha as texture alpha
times shade alpha, then multiplies the combined result by environment alpha.
OtherMode `EF182C3F 04D049D8` specifies two cycles, no texture lookup table,
and blending. The alpha texture therefore remains an input to the final draw.
Discarding it exposes the triangles supporting the hay strands.

The shared direct IA/I decoder now recognizes this multiplicative alpha chain
and its 16-bit RGBA transfer tile. It retains the existing checks for source
format, load size, zero DXT, TMEM origin, complete rows, row swapping, and
payload bounds. The RGBA transfer path requires the supported texture-alpha
product even for opaque variants, preserving the separate shade-only I8
decoder and consistent texture bytes across render-state-table variants.

The resulting IA8 PNG retains 1,588 fully transparent texels, 132 fully opaque
texels and 328 intermediate-alpha texels. Its SHA-1 is
`fcbeb5e4778589786bada51ff4718f4ed37677f5`. glTF uses `BLEND`, preserving
partial alpha instead of cutting strands at a fixed threshold. Runtime
environment alpha, lighting and native raster parity remain unverified.

This is a shared material correction. It uses no Birdy-specific texture or
geometry substitution and changes no mesh vertices, faces, joints or UVs.
The supplied image is a visual comparison only. Generated exports, before/after
images, decoder impact and validation evidence are under
`build/assets/models/reference/birdy-hay-20260910/`.
