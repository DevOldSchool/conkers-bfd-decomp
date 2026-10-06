# US standard audio object boundaries

This note records three complete standard audio-library members recovered from
the US main executable. They are linked from the pinned ultralib source tree's
debug archive because these audio-player objects are not members of the ROM
archive. The authoritative reference map remains raw assembly and data.

## Inputs and search method

- Canonical US ROM SHA-1: `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
- Pinned ultralib revision: `e24c836796df4bf520ff8b11a5c9d2cea3a66cbd`.
- Local Banjo-Kazooie map revision:
  `9db90a003fff15d13d29505d571aff2543b50383`.
- The I, J, K, and L `libultra` and `libultra_d` targets were built with the
  repository's IDO toolchain. This produced 3,462 object instances and 1,110
  unique complete `.text` templates.
- Each complete text section was scanned against the US main executable after
  masking only words named by ELF relocations. Every retained candidate was
  then checked at its exact raw boundary, including padding, relocations, and
  any non-text section.

The exhaustive scan reproduced every already-mapped standard object and found
only the following three additional unique text ranges.

## Archive-member ranges

| US ROM/VRAM range | Size | L debug member | Complete object MD5 | Evidence |
|---:|---:|---|---|---|
| `0x17A80:0x17AA0` / `0x80017A80:0x80017AA0` | `0x20` | `audio/cspgetstate.o` / `alCSPGetState` | `377559de826edff07a1664abce2ab267` | Exact `.text`, including trailing padding |
| `0x17EC0:0x17F10` / `0x80017EC0:0x80017F10` | `0x50` | `audio/cspgettempo.o` / `alCSPGetTempo` | `eeae63f1cddc8679f01cef1243453a3c` | Exact complete `.text` |
| `0x19AB0:0x19B50` / `0x80019AB0:0x80019B50` | `0xA0` | `audio/cents2ratio.o` / `alCents2Ratio` | `fba99810cc2be49fa3213e5b0e687216` | Exact `.text` and `.rodata=0x10` |

The three text sections contribute `0x110` (272) archive-backed bytes.
`cents2ratio.o` also owns `0x2C760:0x2C770`; all 16 bytes of its constants and
padding equal the linked object. Isolating that section leaves
`0x2C770:0x2C850` as raw rodata. Two words in the raw remainder are pointers to
raw code at `0x1001EDF4` and `0x1002078C`, so the working link binds those
destinations while leaving the raw bytes and the reference map unchanged.

The `cspgetstate.o` machine code is also byte-identical to
`seqpgetstate.o`, so bytes alone cannot select the public name. Its placement
inside the compressed-sequence player cluster, the surrounding calls using the
same CS-player objects, and the adjacent exact `cspgettempo.o` resolve the
member as `alCSPGetState`. This is a contextual identity decision recorded
explicitly rather than an overclaim from the shared instruction template.

The J, K, and L debug objects for these members are byte-identical. The exact
SDK revision is therefore indeterminate within J-L; L is selected only because
it is the repository's pinned reproducible late archive. Banjo-Kazooie's
reviewed map independently names `cspgettempo.o` and `cents2ratio.o`, which
corroborates the audio-family identities but does not determine Conker's
boundaries.

## Integration result

The US profile builds a bounded `libultra_2_0L_d.a` containing only these three
members, links the three complete text sections and the `cents2ratio` constants,
and preserves the neighboring raw ranges. `./conker build --all` produces the
byte-identical `build/us/conker.us.z64`.

No other complete standard CPU-library member was found in the remaining raw
US main ranges across the full I-L ROM/debug archive survey. The unresolved
library-shaped work is now the separately documented Rare formatting family
and the RSP `rspboot`/`n_aspMain` microcode, which require matching source or
microcode build outputs rather than additional stock-archive relabelling.
