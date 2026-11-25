# US glyph-selector texture reconstruction

Eleven additional textures rebuild 5,130 stored bytes from PNG sources, covering
13,312 decoded bytes. This family follows the glyph renderer's explicit frame
selectors. It preserves all previous texture contracts and leaves the generic
CPU descriptor count rules unchanged.

| Runtime resource | Physical stream | Image | Stored bytes |
| ---: | ---: | --- | ---: |
| 1689 | 1689 | RGBA16, 32 by 32 | 866 |
| 2941 | 2939 | RGBA16, 32 by 16 | 476 |
| 2985 | 2983 | RGBA16, 32 by 32 | 869 |
| 3072 | 3070 | RGBA16, 16 by 16 | 70 |
| 3668 | 3666 | RGBA16, 32 by 16 | 463 |
| 3744 | 3742 | RGBA16, 32 by 32 | 869 |
| 4099 | 4097 | RGBA16, 16 by 16 | 59 |
| 4238 | 4236 | RGBA16, 16 by 16 | 63 |
| 4323 | 4321 | RGBA16, 16 by 16 | 54 |
| 4695 | 4693 | RGBA16, 32 by 32 | 849 |
| 7731 | 7729 | RGBA16, 16 by 32 | 492 |

The two empty runtime slots, 1767 and 1768, remain represented in the native
resource table. Physical stream ordinals continue to name source directories
and build parts; manifests retain each runtime resource ID.

## Native evidence

The complete 4,392-byte `func_150417AC` uses the 27-word jump table at
`80098B14` for characters `A1..BB`. Its twenty image cases are `A8..BB`.
Nine cases explicitly select frame zero, one selects a high-byte value modulo
ten, four mask the high byte with three, five select frame zero, and one masks
a shifted value with one. Original case instructions were executed for all
256 modifier bytes per image case: 5,120 checks establish 42 frame positions.

The nine first frame-zero descriptors contain zero in byte `+4`. Seven of
their resources were previously excluded by the generic positive-count rule.
The four mask-three cases select indices 0..3 despite descriptor byte `+4`
being three; their fourth words identify the other four new textures. The
stored descriptor bytes are retained unchanged in every source contract.
Neither exception changes any other caller's frame domain.

The image path is taken when the existing skip flag is zero. Character range
checks admit `A8..BB`. At `15041FC0`, the selected frame is shifted left eight;
`15041FD0` passes the selected descriptor in argument one. No instruction
changes either argument before the call at `150420E4`, including coprocessor
register transfers. `func_15094F70` forwards them to `func_15095060`, whose
right shift by eight recovers the frame index. The wrapper passes pixel-frame
offset zero to the full upload consumer `func_150950D4`.

All four complete registered consumer spans, the jump table, twenty descriptor
records, 42 selected frame words and the native transfer-size tables are
checked against the original ROM. This is a declared native-consumer proof;
it does not claim gameplay activation of every case or safety of every caller.

## Reconstruction and preservation

`scripts/texture_cpu_glyphs.py` is appended after existing catalog families.
The prior 6,161 extended contracts compare equal in the pilot. The final
selection grows from 6,865 to 6,876 textures. Twenty-two new editable source
files are published atomically, leaving all 27,301 prior asset inputs unchanged.
Only the corresponding raw flat intervals and eleven encoder entries change.

Every image covers its entire decoded payload, with no palette, extra plane,
unknown tail or partial row. The existing native storage-geometry checks and
RGBA16 PNG inverse apply. Fresh level-nine zlib encoding from the decoded PNG
reproduces every original RZIP byte; original compressed bytes are never used
as the output. Source manifests retain the original ROM, descriptor, frame,
decoded-payload and stored-byte hashes.

## Validation

Base commit: `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7`, plus uncommitted work.
The native selector audit, eleven PNG inverses and fresh compression checks
passed. Forty-six focused tests passed, including five new tests for explicit
frame selection, complete native guards, fourth-word mutations, invalid
padding, payload tails, prior exclusions and inverse failure. All eleven actual
source bundles reconstruct their original stored bytes; all 55 changed or missing
input cases are rejected. The full suite passed 3,038 tests with eight skips in
257.272 seconds. The US asset build passed in 177 seconds including setup
(172.824 seconds build, 144.902 seconds compile/link/verify). Independent ELF
extraction reproduces all 67,108,864 original ROM bytes.

The accepted report adds exactly **5,130 matched and complete data bytes**:
**63,332,173 / 65,120,512 matched**, with **1,788,339 remaining**. Complete data
is 63,251,041 bytes. All prior unit measures except the shrinking raw flat
remainder are unchanged; the eleven new texture units are complete. Raw flat
storage decreases from 1,210,189 to 1,205,059 bytes by exactly the eleven source
intervals. All 27,301 previous asset input hashes, all 11,836 previous asset
object hashes and all 869 previous GAME object hashes are preserved. The 22
new PNG/manifest inputs are checked against their integration hashes.

Three rebuilt startup objects have different whole-file hashes. Their code
contracts and data ranges remain unchanged; the full linked main code and data
match the same independent original-ROM proofs, and all 128 bytes of their
linked INFO tables independently match the ROM. This is byte-level verification
of their linked output, not a claim that their object files are identical.

Full report preparation took 381.6 seconds, with another 27.8 seconds for report
and validation. Progress, whitespace and snapshot-current gates passed.
Report SHA-256: `581f1d7730c49e2448e1076d812c8425a7bb497b7f1ea1070b4a8db238b1c455`.
Source fingerprint: `cd0d92d0473179e06be824899e9bf2b456b9a7f4843fc867f103ffbefd4596aa`.

Detailed machine evidence is in the accompanying JSON. Temporary pilots and
audit scripts are under `build/us/data-completion/glyph-*`.

## Glyph data source integration

The same twenty native glyph cases establish a contiguous 408-byte region at
`800915D8..80091770`: 42 frame words followed by their twenty twelve-byte
descriptors. `src/game/data/glyph_texture_data.c` expresses these alternating
records with typed structures and twenty pointers into the same aggregate.
The stored count values remain unchanged; each frame-array extent comes from
its specific native selector. Grouping the records does not claim an original
C-object boundary.

The pinned-compiler scratch object matches all 408 bytes against an independent
full GAME reference. All 448 byte, pointer-destination and pointer-addend
mutations lose the exact match. Eight compiler-tail bytes are excluded. The
source is integrated in an INFO verification section; the original archive
continues supplying runtime data. Its dedicated GAME build verifies the actual
linked 408-byte payload and all twenty pointer destinations. All 448 native
mutation cases and 408 independent ROM-byte mutations are rejected. All 869
previous GAME objects preserve their allocated bytes, symbols and relocations;
all 2,072,880 GAME code bytes remain identical.

The full suite passed 3,038 tests with eight skips in 254.342 seconds. The US
asset build passed in 163 seconds including setup (158.285 seconds build,
139.588 seconds compile/link/verify); independent ELF extraction reproduces the
complete original ROM. The asset build and dedicated GAME build are separate
checks: the asset build alone does not compile these GAME INFO objects.
Progress and whitespace checks passed.

The final report accepts **408 additional matched data bytes**, bringing the
current total to **63,332,581 / 65,120,512**, with **1,787,931 remaining**.
Complete data stays at 63,251,041 bytes because these are verification-only
source definitions. All 27,323 asset source hashes and all 11,847 existing asset
object hashes are preserved. Code and function measures are unchanged.
Report preparation took 372.1 seconds, with another 25.1 seconds for report and
validation. The independent comparison audit passed and the snapshot is current.

Report SHA-256: `7e98f6a9e215ed7f7fd1042173e0503aec38ff79a6eceb4171253500fa6d1917`.
Source fingerprint: `df6073d1fd53adaa612efe5f87602360967149c5f87a93f46ee8f4276a72f418`.
