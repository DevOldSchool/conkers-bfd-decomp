# 2.0G reclassification of former Rare mappings

This note records the follow-up comparison performed after source-derived
libultra 2.0G objects became available. Earlier surveys correctly established
the complete object boundaries but could only match these ranges to the
available Rare snapshot. Comparing those same complete sections against 2.0G
shows that part of the snapshot is stock G output.

The audit compared every loadable section currently mapped from `libultrare`
against the normal and available debug 2.0G objects. It used complete section
sizes and relocation-masked bytes, then checked relocation targets and
non-text ownership before testing the replacements in full links. Of 108
loadable mapped rows, 31 matched G, 77 did not, and eight BSS rows required
structural and full-link validation rather than byte comparison.

## Main executable

The following thirteen objects now come from `libultra_2_0G`:

- `os/initialize`
- `os/destroythread`
- `io/epirawdma`
- `io/vi`
- `io/contreaddata`
- `io/pfsisplug`
- `io/controller`
- `io/contramwrite`
- `io/contramread`
- `io/leointerrupt`
- `io/pfsinit`
- `io/leodiskinit`
- `vimodes/vimodepallan1`

Together they own twelve text sections, four initialized-data sections, and
five BSS sections in the US map. `initialize.o` retains the existing link
adapter which renames its `__osLeoInterrupt` reference to
`__osLeoInterruptPhysical`; the underlying object is built from the G source.
With all thirteen substitutions applied, `./conker build` reports
`build/us/conker.us.z64: OK`.

## Game overlay

Seven complete game text mappings also match normal 2.0G objects:

- `controller`
- `pfsinit`
- `contreaddata`
- `mtxutil`
- `pfsisplug`
- `contramread`
- `contramwrite`

Their mapped text totals 5,408 bytes. The controller data/BSS and PFS BSS
bindings continue to use the independently reviewed main-executable storage,
but their input sections now come from the G archive. `./conker game-build`
reports the 2,072,880-byte integrated payload as byte-identical, with SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.

## Retained Rare and Conker objects

`libultrare` remains required for the nonmatching audio, formatting, EEPROM,
GU/math, MP3, and SI-access objects. In particular, `siacs_game.o` has the same
instruction template as G `siacs.o`, but it is not a direct archive replacement:
stock G places its private SI message buffer and queue in one contiguous BSS
section, while the game overlay reuses the main queue and places its buffer in
separate game storage. The explicit `siacs_game` adapter preserves that split.
