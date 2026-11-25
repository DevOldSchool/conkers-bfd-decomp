# US inline I4 font and character map

The native renderer selects a 64-by-128 I4 atlas at `0x80084930`, occupying
4,096 bytes, and searches an 80-byte character map at `0x800848D0`.
These two ranges add 4,176 source-owned bytes. The intervening 16 bytes at
`80084920..80084930` are excluded; no alignment or ownership claim is made
for that gap.

## Independent consumer and format evidence

All 200 original instruction words of the existing complete source unit
`150412C0..150415E0` are compared against the checksum-validated US ROM and
its raw assembly. The four complete registered functions are:

| Function | Bytes | SHA-1 |
| --- | ---: | --- |
| `150412C0` | 316 | `4b1e5f70a3f7e434ff616bb14d0d897ab7ee57e2` |
| `150413FC` | 132 | `4e2cef09eeee15982877ca423104512fddcf2215` |
| `15041480` | 136 | `75a1d9069a14a70b397f2bda6caf77b430f45ec6` |
| `15041508` | 216 | `4bff24c22eb60353c895efaf9edb877195bfe10a` |

A bounded interpreter executes the original instructions of `150412C0` and
recovers its twelve emitted display-list commands. Both image-address commands
select `80084930`. The 16-bit load-block transfer covers 2,048 units, or 4,096
bytes. The render tile selects I4, a 32-byte line, and dimensions 64 by 128.
These independent transfer and geometry bounds agree; no adjacent symbol is
used to infer the bitmap's extent.

The same interpreter executes `15041480` for every possible input byte. Every
result agrees with the first matching character-map index, or 80 when absent.
All 80 source bytes are exercised, and no read leaves that exact range. The
native draw helper uses eight glyph columns with eight-by-twelve pixel cells.
The map retains its original order, including duplicate characters; it has no
terminating NUL byte.

The existing I4 image codec independently decodes the bitmap and re-encodes a
PNG to the exact original 4,096 bytes. Its observed intensities are 0, 8, 9,
10, 11, 12 and 15; it is not a one-bit bitmap. The PNG inspection uses that
codec's vertical-flip convention and is not a new runtime rendering claim.

## Readable source and placement

`src/game/data/inline_font.c` records 128 source-image rows. Each hexadecimal
word spells eight four-bit intensity samples; `I4_PIXELS` expands those samples
into four big-endian bytes. The typed array remains `const u8[4096]`.
`inline_font_characters.c` uses character literals in ten groups of eight,
with an exact `const u8[80]` extent. These are data-only reconstruction owners,
not claims about Rare's original translation-unit boundaries.

Both actual compiled `.rodata` sections have independently addressed INFO
placements, explicit payload sizes and exact linker extent assertions. The
reference symbols are byte arrays with exact extents, preventing pixel words
from being interpreted as pointer relocations. The existing renderer's two
extern declarations gain const qualification and explicit array sizes; its
function bodies are unchanged.

The original GAME archive continues to supply runtime storage. This change
can increase matched data, but does not increase complete data or claim a
reconstructed GAME archive.

## Validation

Accepted at base `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7` plus
uncommitted changes. [Machine-readable evidence](us_inline_font.json) records
the source/object hashes, complete native consumers and report fingerprint.

The independent source audit parses all 1,024 pixel words and 80 character
literals. Both actual compiler objects and linked INFO sections reproduce the
original 4,176 bytes without padding or relocations. The full 2,072,880-byte
GAME code image remains exact. The renderer's 800 compiled instruction bytes,
function extents and relocation sites/kinds/destinations are unchanged; only
four external-symbol size records gain the explicit 4,096/80-byte extents.
All eight consumer endpoint mutations fail the native guards.

Native objdiff compares the two actual compiler objects against independently
assembled ROM references: 4,176 of 4,176 bytes match. Mutating each byte position
separately produces 4,176 rejected perfect matches. The 59 focused tests pass
(two skips), and the full Docker suite passes all 3,028 tests (eight skips,
288.629 seconds). The US asset build passes in 209 seconds, including a
165.095-second compile/link/verification stage. Independent extraction of the
linked ELF reproduces the complete 67,108,864-byte ROM with SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`.

The full native report adds exactly 4,176 matched data bytes and zero complete
data bytes. Matched data is 63,294,279 / 65,120,512 (97.19561%); 1,826,233 bytes
remain. Code measures and all previous unit measures except the split raw data
range are unchanged. The original 13,184-byte raw range becomes a 7,600-byte
prefix, the two typed owners, a 16-byte unclaimed gap and a 1,392-byte suffix.
All 27,295 prior editable asset input hashes and 11,836 prior asset object hashes
are preserved. GAME object containers were rebuilt; full GAME image equality
and unchanged native per-unit results establish preservation without claiming
identical container metadata. The snapshot is current, compile errors are zero,
and progress/whitespace gates pass.
