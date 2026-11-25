# US bank-03 model 66: a short normal table

Model 66 is the last unmatched bank-03 payload after the
[direct auxiliary model batch](us_direct_auxiliary_models.md). Its native
index selects ROM `0xF958A0..0xF959F7`: 343 stored bytes, decoding to 696 bytes.
The direct loader/header and normal-command relocation consumers are the same
full spans authenticated by that batch. The original directory independently
checks this entry's compressed flag and exact extent on every review.

## Format and consumer evidence

The ten header words are `(296, 312, 608, 32, 640, 48, 0, 0, 0, 0x80000000)`.
The payload contains 16 vertices, 39 display-list commands, 16 signed normal
XY pairs, 12 native face words, and eight checked trailing zero bytes. Z comes
from each vertex's flag byte under the existing normal interpretation. No new
meaning is assigned to the face words.

At decoded offset `0x190`, `DC38000E 00000260` selects the normal table. The
only vertex load, `01010020 01000000` at `0x1A8`, loads 16 vertices into cache
slots 0–15. All 12 triangles refer to those initialized slots. Independent
command replay checks every pair's address: `608 + 2 * slot`, covering exactly
`608..640`. The face table begins at 640 and is disjoint.

The pinned GLideN64 implementation independently supports this interpretation:
[F3DEX2CBFD_MoveMem](https://github.com/gonetz/GLideN64/blob/41c7ba273a6c9afb43c0574cf3cf5d139182d070/src/uCodes/F3DEX2CBFD.cpp#L69)
sets a normal base, and
[gSPLoadCBFDVertexData](https://github.com/gonetz/GLideN64/blob/41c7ba273a6c9afb43c0574cf3cf5d139182d070/src/gSP.cpp#L1344)
reads signed XY components by cache slot when lighting is enabled. This is
emulator implementation evidence, not a new hardware trace. A fixed 64-byte
normal DMA or an overlap with the face table is **not** established or required.

The existing extended-model codec deliberately requires full 32-pair tables.
`model_short_normals.py` instead accepts an explicit short table only when all
pairs are referenced and every vertex load stays inside it. It rejects missing
normal setup, other base addresses, unread pairs, overlapping regions, unknown
header regions, nonzero tails, and table/count disagreements. The existing
extended-model codec and all its accepted sources remain unchanged.

## Build and ownership

Two new editable files live below the existing part source:
`build/assets/direct-models/us/00F954D8/short-normals/{manifest,model}.json`.
The parent manifest, models and backing are preserved byte-for-byte. The builder
combines the new typed model with the existing reconstructed spans, freshly
compresses it with bounded DEFLATE, and requires both decoded and stored hashes
to agree with the independent ROM. Its original raw-object extent is unchanged.

Make tracks both child files, including deletion. Modified or missing inputs
fail without overwriting them. The existing `direct-models recover --part
00F954D8` operation backs up the complete parent and child tree before recovery.
The report verifies the actual linker object, current source hashes, and the
independent ROM ranges. The added range is checked for overlap with all prior
owners; only the remaining 343 bank-03 bytes become newly owned.

## Validation

Accepted on base `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7`
plus uncommitted changes. The independent pilot reproduces all 696 decoded and
343 compressed bytes exactly. All 32 normal-component and 12 face-word
mutations affect only their intended decoded fields. All 343 individual stored
byte mutations reject a perfect native match. The expanded six-object pilot
matches 18,926 bytes.

- 57 focused and Make integration tests pass, including source preservation,
  recovery, invalid normal reads, independent report references and missing inputs.
- The full Docker suite passes 3,020 tests with eight skips (257.274 seconds).
- `./conker build --assets` reproduces the complete 67,108,864-byte US ROM
  exactly (171 seconds including setup; 143.309 seconds compile/link/verify).
  An independent extraction from the current linked ELF also matches the ROM.
- Full native report: zero compile errors; 396.6 seconds preparation and
  40.5 seconds report/validation. Progress and whitespace checks pass.
- All 27,291 previous editable source hashes and 11,835
  previous asset-object hashes are preserved. Only two child inputs are added.
  Code, functions, denominators and linked runtime code/data are unchanged.

Matched data increases by **343 bytes** to **63,281,392 / 65,120,512
(97.175821%)**; complete data increases to 63,235,264. **1,839,120 bytes
remain unmatched.** The existing direct-model unit grows from 3,297 to 3,640
bytes, and the now-empty bank-03 unmatched remainder disappears. No other
prior unit changes. Bank 03 has no unmatched storage remaining.

Report SHA-256:
`6549a5cebf6a1478fe6ac86de1be24cca6037def45678b44654b033a799939a8`.
Input fingerprint:
`59352486774ea6129aa77d4bd2ec9e3aa305c168f41da0967df7de9f4f0f7007`.
