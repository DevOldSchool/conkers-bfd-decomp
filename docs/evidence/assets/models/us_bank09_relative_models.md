# Bank-09 model-relative vertex addresses

The direct bank-09 loader supports a second vertex-address convention. Adding
that convention extracts 290 more models and parts directly from the US ROM:
9,193 source triangles. That pass recovered 451 models (296 direct and 155
three-pair attachments). The subsequent [effect-model extraction](us_bank09_effect_models.md)
adds eleven four-pair meshes, bringing bank 09 to 462 models and the four-bank
inventory to 1,487. Twenty other records are skeletal particle-emission point
sets; entry 447 remains unclassified. These counts include parts and props.

## Native consumer evidence

Evidence uses normalized US ROM SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a` and the decompressed executable,
independently of the current mixed C/ASM build.

- `func_1518C900` loads indexed bank 9 at `0x1518C934..0x1518C950`, obtains
  the primary list at model offset zero, and calls `func_15168E54` at
  `0x1518C9A8`, passing the model base in `a1`.
- `func_15168E54` walks to EndDL and dispatches vertex opcode 1 or the custom
  MoveMem selector 0x0E to `func_15168E34`.
- `func_15168E34` reads a command's address word, tests `0x0F000000`, and adds
  the model base only when those segment bits are zero. Its exact eight words
  are `8C820000 3C010F00 00417024 15C00002 00457821 AC8F0000 03E00008 00000000`.
  Segment-1 addresses remain relative to the separate vertex array.

The loader checks the ROM SHA-1 of all three complete function spans before
accepting a bank-09 export: 260, 180 and 32 bytes respectively. The parser
accepts unsegmented addresses only for bank 09, subtracts the native 0x28-byte
header, and retains cache/count/alignment/bounds checks. It does not search for
interior geometry signatures. Header pairs, final EndDL and auxiliary-region
rules still apply.

Entry 0 illustrates the difference: its first vertex command at offset 0xB8
is `01004008 00000028`, loading the first four vertices after the header.
The earlier six direct entries 426..431 use segment 1 instead. Both conventions
now share the same triangle, material and UV decoder without modifying the
native display-list bytes. Direct reconstruction re-encodes decoded header and
vertex fields and preserves display lists and opaque trailing data byte for
byte; three-pair models retain their existing structured reconstruction.

## ROM-only export and inspection

```sh
./conker model-assets extract --bank 09 --force
./conker model-assets preview --bank 09 --force
./conker model-assets validate
./conker model-assets inspect
```

A preview without `--runtime-materials` needs only ROM data and the ROM-derived
texture catalog. Existing captured comparison corpora are regenerated with
their original material catalogs. None of the 290 new models has a captured
material record. Their glTF, binary and image bytes also match a separately
executed export whose file-open audit rejects capture and other model-output
reads. Of their 9,193 faces, 7,129 receive a proven ROM texture; untextured and
unresolved material runs remain separately labelled.

Local evidence and logs are under
`build/assets/models/reference/rom-material-expansion/`, including
`bank09-read-audit.json`, `preservation-and-pure-ROM.json` and the batch log.
Regeneration also refreshes nine previously stale glTF metadata files in each
comparison corpus. The saved pre-change exporter reproduces those current
files exactly; all pre-existing geometry buffers and texture PNGs are unchanged.
The inspection gallery adds descriptive examples: a fanged head (0258), a head
with helmet (0238), and a light bulb (0166). These are standalone objects or
parts; their gameplay names and attachment transforms are not inferred from
appearance. Dedicated new regression references preserve all existing image
baselines. Geometry/export consistency and Blender importability do not prove
native lighting, culling, blending, animation or raster parity.
