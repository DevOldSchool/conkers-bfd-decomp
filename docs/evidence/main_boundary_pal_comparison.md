# US main boundary frontier: bounded PAL comparison

Historical result: the 2026-09-30 comparison found a PAL counterpart for all
four unresolved US ranges, but no new entry-selection or original-grouping evidence that resolves
them. At that checkpoint the frontier remained **four ranges, 1,344 US bytes**.
The later [owned beta comparison](main_boundary_beta_comparison.md) resolves
the 64-byte hardware-init/probe family and leaves three ranges, 1,280 bytes.
The PAL-only trial changed no ownership, registration, map, implementation
or progress state.

## Independently validated inputs

- Owned US ROM SHA-1: `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
- Owned PAL ROM SHA-1: `ee7bc6656fd1e1d9ffb3d19add759f28b88df710`.
- Each ROM is 67,108,864 bytes and was hashed locally. No private ROM or
  extracted payload is committed.
- PAL game code was decoded with the existing `scripts/rzip_archive.py` parser
  from configured archive range `0x427B0:0x19EDE8`. Its 2,074,912-byte code
  SHA-1 is `e79369f8c0cad22892728a3db723092bc6856f07`, matching
  `config/overlays.json`. The 189,216-byte data SHA-1 is
  `b4ba705dce582759e189f2b5fb21606c1d9b3a1c`.
- The complete 208-byte US RSP boot payload occurs exactly once in PAL, at
  `0x29400`. The PAL CPU search therefore ends there, before RSP instructions.

The existing regional maps supplied navigation candidates, not historical
ownership proof. A relocation-insensitive instruction comparison was used only
to navigate corresponding bodies; target instructions and the relevant address
constructions were then checked in the actual ROM words.

## Corresponding unresolved ranges

| US ROM range | PAL ROM range | Observation |
| --- | --- | --- |
| `0x38C0:0x38E0` | `0x3950:0x3970` | Identical 32-byte varargs-style empty stub |
| `0x38E0:0x3920` | `0x3970:0x39B0` | Same two bodies; two global-address operands relocate |
| `0x39B0:0x39C0` | `0x3A40:0x3A50` | Identical 16-byte no-op return and alignment words |
| `0x50A0:0x5570` | `0x5380:0x5860` | Corresponding family with substantive regional changes; disputed extra return remains |

The two entries in the second row correspond as `0x38E0` to `0x3970` and
`0x390C` to `0x399C`. Repetition of their adjacency in another retail build
does not establish that the hardware-writing routine and zero-return body
share an original object owner.

## Larger family's selected entries and unresolved return

These correspondences are research anchors, not new registered boundaries:

| US start | PAL start | Positive PAL evidence |
| --- | --- | --- |
| `0x50A0` | `0x5380` | Game call at `0x15007850` |
| `0x51C8` | `0x547C` | Main call at `0x80009744` |
| `0x51E8` | `0x549C` | Game call at `0x1500797C` |
| `0x5218` | `0x54CC` | Main bootstrap call at `0x800011E8` |
| `0x52A0` | `0x5554` | Thread-entry address constructed at `0x8000550C/0x80005518`, passed to the constructor at `0x80005528` |

US `0x5218:0x5298` and PAL `0x54CC:0x554C` retain corresponding 128-byte
initializer bodies. Their ordinary epilogues end at US `0x5294` and PAL
`0x5548`. Each is followed by the same eight-byte `jr $ra; nop` sequence,
at US `0x5298:0x52A0` and PAL `0x554C:0x5554`, before the selected thread body.
That sequence's SHA-1 is `fcaee431e1f242adb7285049ca72a9c79bfa3f0e` in both.

PAL changes code around this area, rather than being a whole-family byte copy:
the first initializer is 44 bytes shorter, and the later thread body differs
substantially. Nevertheless, the extra return remains unselected by the bounded
checks below. Its survival and changed alignment do not prove original function
or object ownership. The complete US raw span `0x5218:0x52A0` stays intact.

## Targeted selection checks and their limits

The checked unresolved PAL targets were `0x3950`, `0x3970`, `0x399C`,
`0x3A40`, and `0x554C`. For these exact targets:

- Direct J/JAL decoding across PAL main CPU `0x1050:0x29400` and the entire
  checksum-validated game code found no selections, checking both main runtime
  aliases (`0x80000000 + offset` and `0x10000000 + offset`).
- Word-aligned initialized main data `0x29620:0x2D810` and the complete decoded
  game data contained neither address alias.
- ADDIU/ORI low-half candidate checks across both CPU images found only three
  coincidental suffixes. The surrounding LUI instructions resolve these to
  unrelated data addresses: game site `0x15091734` constructs `0x80083950`;
  sites `0x15022710` and `0x150228A0` construct `0x800C3970`. None selects a
  target above. There was no low-half candidate for `0x554C`.

This is a bounded negative result. It does not exclude computed or otherwise
encoded selectors, prove unreachability, identify stock-library ownership, or
establish an original object boundary. Positive selectors of the five substantive
entries corroborate those bodies but do not account for the extra empty entry.

## Result and next useful evidence

PAL does not close the main boundary frontier. Do not repeat this same retail
comparison without a new lead or reinterpret the negative checks as proof.
At this checkpoint the next planned input was the user's owned debug build.
Both beta inputs were subsequently examined on 2026-10-01; see
[the completed beta comparison](main_boundary_beta_comparison.md). The user
confirmed that no original debug map is available and cautioned that the debug build may add little information. This
is a bounded investigation opportunity, not a promised route to completion.
The existing `beta-index` correlations concern game overlays; main needs its
own targeted review.

This historical comparison used US and PAL inputs, without those prototypes or
an original symbol map. Prototype hashes and
canonical input names are documented in [beta evidence](../beta-evidence.md) and `config/rzip_layouts.json`;
their bytes were not available for this trial. A prototype correlation would
still require positive entry/grouping evidence before changing US spans.

This evidence-only update requires no build or progress regeneration. It claims
no new C match, original-assembly verification, or full-ROM rebuild; the prior
verification in [the frontier](main_boundary_residual_frontier.md) is unchanged.
