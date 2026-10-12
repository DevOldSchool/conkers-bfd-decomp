# US script bank reconstruction

Bank 06 is reconstructed from 483 script sources across 50 populated scene
slots. Its 542,048 stored bytes include fresh zlib level-6 compression and
newly generated outer and inner directories. No encoded program bytes or raw
backing supply the candidate. The independent inventory is
[us_script_reconstruction.json](us_script_reconstruction.json).

## Native format

func_1501D1D4 loads bank 06 using scene and script indices. func_1501D348 reads
four unsigned halfword counts from the first child, then assigns five groups
of child segments. The source derives those counts and all directory offsets,
lengths and final/compression flags. Every child starts at an eight-byte boundary;
zero alignment is generated, including before empty segments. The outer scene
list has 69 slots, with absent scenes represented explicitly by `null`.

| Group | Native fields | Evidence |
| --- | --- | --- |
| Position tracks | Three signed 16-bit coordinates and a 16-bit interpolation control | func_1501F72C, func_1501FC8C, func_1501FE68, func_1501FFE8 and func_15020388 use an eight-byte stride; the control at +6 selects the interpolation branch |
| Bindings | 16-bit kind, byte selector, signed byte target, signed 16-bit height offset | func_15020EC4 reads +0/+2/+3/+4; func_15022BA4 applies relative target binding; actor and model selectors are also consumed by func_1502A8A0 |
| Value tracks | Float value, byte interpolation selector, byte destination channel, signed 16-bit time | func_1501EC38 reads +0/+4/+5/+6 and dispatches channels 0 through 14 |
| Commands | Signed byte opcode, byte time delta, signed halfword selector, two signed byte arguments, signed halfword argument | func_15023BB0 scans eight-byte commands after four header records; func_1502460C and func_150265CC consume the operand union |
| Text | Native encoded text, a zero terminator and two-byte word alignment | func_1501D348 installs text pointers; func_1502460C and func_150265CC select them by command operands, including native BE/BF prefix controls |

The binding segment is eight bytes, and its reviewed native fields occupy the
first six. The fixed two-byte zero tail is regenerated rather than exposed as
an opaque source field. All 4,343 stored bindings have that tail. The proof pins
all 18 direct references to the binding table, including selector updates and
actor/model lookup paths; the codec rejects any nonzero tail. The classification
as packing padding is inferred from the field reads, native eight-byte stride
and uniform zero tail. It does not establish an original C structure definition.

All 887 nonempty text segments have one zero terminator and at most one further
zero word-alignment byte. The other 40 are zero-length segments, represented
by `null`, distinct from an empty terminated string. Latin-1 is used only as a
reversible JSON mapping for the game's encoded glyph/control bytes; it does not
claim the game's display character set. Embedded terminators or unexplained
trailing bytes are rejected.

The command source retains the native operand union and its signed widths.
The first four records retain their negative/zero header opcodes and time fields;
no new meanings are assigned to individual game operations. Native opcode
interpretation, scene activation and complete gameplay timelines are unchanged.
This is storage reconstruction and static consumer evidence, not a gameplay test.

## Build and provenance

`./conker script-assets build` initializes ignored `manifest.json` and
`scripts.json` under `build/assets/script-build/us/`. Later builds read those
saved sources, regenerate all uncompressed fields, freshly compress each script,
and compose the actual `asset_bank_06.o` ROM link input. Missing, malformed,
edited or concurrently changed sources fail without being overwritten.
`./conker script-assets recover` explicitly backs up existing inputs first.

Thirty-two full registered consumer spans, totaling 45,056 code bytes, are
checked against the independent ROM. Their hashes are recorded in the manifest.
The native report uses the actual linked bank object and compares it with fresh
semantic output and independent ROM bytes. Complete bank reconstruction replaces
its raw-storage report unit without changing the denominator.

## Independent audit

The independent reader checks all 6,620 position keys, 4,343 bindings, 47,913
value keys, 52,316 command records and 927 text slots against their original
native offsets and widths. All 27,868 endpoint field mutations change exactly
the expected native bytes. All 64 consumer endpoint mutations are rejected.
All 26,055 prior unique editable-source hashes are unchanged.

Fresh reconstruction covers 1,119,912 decoded script bytes and the complete
542,048-byte bank, SHA-256
`0af0b7e65db3fa3fc33d00d1b1eacbe5d98fb7722845c84a4a2cb26152a893c3`.
Nine focused tests cover native widths, text/empty distinctions, derived
boundaries, padding rejection, source preservation/recovery, races and actual
linked-object credit. Full ROM, Docker suite, report, progress and whitespace
acceptance are recorded after the completed batch below.

## Accepted batch

On base commit `094102644c4c2f5aefaa0fc4b609416918f66f58`, the asset build
reproduced the complete 67,108,864-byte US ROM in 111 seconds. All 2,609 Docker
tests passed in 133.792 seconds (8 skips). Progress and whitespace checks passed.
The current native report independently adds exactly 542,048 Data bytes, bringing
matched Data to **63,018,049 / 65,120,512 (96.77142%)**. Code remains unchanged.
All prior unit measures, asset proofs and 26,055 unique source hashes are intact.

Source fingerprint: `66c20fc86ea7d92cef7360456debb24ab096dcac4e95f16c2e297cecaa2dacba`.
Report SHA-256: `11efdd15ec36bf0ffebd11042e1db985565b45714098264502ae23723fb21e15`.
