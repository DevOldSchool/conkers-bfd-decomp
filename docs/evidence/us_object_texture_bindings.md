# US placed-object texture selectors

The ROM-only exporter resolves the ordinary object updaters `150C4E9C` and
`150DE458`. It exports an explicit loader-selector inspection preset, retaining
the original geometry and UVs. It does not infer current gameplay state.

## Consumer chain

`150039E0` reads the bank-11 placement updater index at `+0x14`, dispatches
through the twelve-byte records at `80088C90`, and stores the updater at object
`+0x38`. The same loader writes zero to object `+0x7C` at `15003D28` and four to
object `+0x73` at `15003D40`. Placement `+0x38` instead becomes object `+0x40`;
it is not the texture selector. `15113E54` calls the stored updater for eligible
objects. Visibility and later scene-script changes remain outside this proof.

The two updaters load flat ROM assets with `1510D0EC` and register pixel/palette
segment pairs with `1510D874`. The ordinary renderer `151137D4` replays those
bindings through `1510D8C0` before drawing the object. Complete consumer hashes,
the complete updater dispatch records, and the existing enumeration of all
segment-registry callers guard this interpretation. Unsupported placements and
rewritten display-list paths do not receive bindings.

## Resolved records

| ROM identity | Placement evidence | Inspection texture state |
| --- | --- | --- |
| `04:0007:15` | Scene 7, record 9, updater 37 | Object `+0x73 & 3 = 0`, flat 705 at segment 4; trailing 512-byte palette at segment 5 |
| `04:0028:12` | Scene 28, records 8, 11, 14, 17, updater 24 | Object `+0x7C = 0`, flats 1682 and 1683 at segments 4 and 6; trailing 512-byte palettes at 5 and 7 |

`150C4E9C` chooses flat 705 for selector values 0 or 2 and flat 448 otherwise.
Values 0 and 3 clear its UV-scroll accumulators. The export uses value 0 and
validates both stationary texture alternatives, without treating them as an
animation. The two-triangle model is a single-sided sign; its authored face
reads "WRONG" and is visible from the rear inspection camera.

`150DE458` checks model index 12, then indexes the pair table at `80090204` with
`object[0x7C] * 8`. Only its first eight bytes are reviewed here
(SHA-1 `3f02bf93cf3dd80ad397b01bc25e4a823608403c`). The resulting 46-face object
is labelled descriptively as a stone panel with a red center. No claim is made
about later puzzle selectors or other rows in the table.

## Validation and limits

The shared resolver requires the exact pixel/palette segment pairing, zero
segment offsets, CI8 decoding, a 512-byte palette tail and compatible dimensions
for all retained alternatives. The original material runs are not modified.
Manifest `rom_object_texture_binding` and glTF `romObjectTextureBinding` carry
placement hashes, selector state, consumer identity and decoded image hashes.
Validation independently reloads the ROM context and rejects altered provenance,
texture pixels or replacement of captured materials.

Local evidence is under
`build/assets/models/reference/object-bindings-20260912/`: the source-read audit,
independent ROM export, numeric geometry checks, pixel-by-pixel CI8 decoding,
consumer/table mutation rejection and reviewed Blender renders. Runtime captures
are not extraction inputs. Stored-selector presets, import success and matching
preview baselines do not establish native lighting, visibility or raster parity.
