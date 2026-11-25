# US segment-8 rendering-state records

The sources in `src/game/data/render_state/` reconstruct 4,224 bytes at
`0x80082FC0..0x80084040`: 264 independently terminated display lists. Each
list contains one SDK `gsDPSetOtherMode` command and one
`gsSPEndDisplayList` command. They contain no pointers, vertices or executable
CPU instructions.

## Native evidence and scope

Five complete ROM-checked renderers establish all eleven segment-8 bases:

| Native renderer | Base addresses |
| --- | --- |
| `func_1502CCFC` | `80082FC0`, `80083140`, `800832C0` |
| `func_150911F4` | `80083440`, `800835C0` |
| `func_15132B80` | `80083740`, `800838C0` |
| `func_15157420` | `80083740`, `800838C0`, `80083A40`, `80083BC0` |
| `func_151137D4` | `80083D40`, `80083EC0` |

The evidence records each full function's size and SHA-1, together with the
instructions that form the address and `DB060020` command and store both
words in the display-list stream. This proves actual segment binding, rather
than just a nearby reference to an address. The renderers select different
groups according to opacity and rendering mode or flags.

Adjacent native base addresses are 384 bytes apart. Each intervening span
decodes completely into 24 sixteen-byte `EF`/`DF` records. The final group
ends with `DF000000 00000000` at `80084038`; the following word at `80084040`
is `80096928`, outside this command family. Each record has its own terminator.
The C declarations group these records as `Gfx[24][2]` for readable storage;
they do not establish Rare's original C-array boundaries.

Storage reconstruction and runtime reachability are separate claims. A
ROM-checked scan of 1,487 model segments from banks 01, 03, 04 and 09 parsed
without failures and found eleven distinct segment-8 offsets: `00`, `10`,
`30`, `40`, `50`, `70`, `C0`, `D0`, `100`, `110` and `130`. It does not prove
that every slot is called, or that every model can use every base. The other
thirteen offsets remain unobserved in that scan. Their stored command format
is nonetheless explicit and terminated; no inferred usage is needed to
reconstruct those commands. This batch makes no new model/material assignment
or runtime appearance claim.

## Build representation

Each source uses the pinned SDK's `Gfx` type and command macros. There are no
raw byte arrays or copied object payloads in the source. The compiler emits
exactly 384 data bytes per source, with no pointer relocations or tail padding.
The symbol map marks the command words as scalars, preventing accidental
pointer inference from rendering-mode bits.

The linker places the eleven objects at their native addresses in INFO
sections with exact-size assertions. The original GAME archive continues to
supply runtime data. These sources can earn matched-data credit, not
complete-data credit. The accepted previous report classified the whole
range as unassigned; no previously matched data is counted again.

## Validation

Base commit: `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7`, plus uncommitted
work. The GAME build passes, and all 756 prior GAME objects preserve their
allocated bytes, symbols and relocation destinations. The complete
2,072,880-byte GAME code image and the function/source-unit inventories are
unchanged. All eleven temporary report copies compile and agree with the
actual linked objects.

Independent native objdiff matches all eleven units, 4,224 of 4,224 bytes.
Changing each payload byte in turn produces 4,224 rejected comparisons.
There are no pointer fields or compiler tail bytes in these owners.

The full Docker suite passes 3,033 tests with eight skips in 320.292 seconds.
The reconstructed-assets build passes in 193 seconds wall time (189.032
seconds for its build stage; 163.487 seconds for compile/link/verification).
An independent extraction from the rebuilt ELF reproduces all 67,108,864 US
ROM bytes, SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`. Progress and tracked
and new-file whitespace checks pass.

The final full report has no compile errors. Matched Data increases by
**4,224 bytes** to **63,309,407 / 65,120,512 (97.21884%)**, leaving 1,811,105
bytes unmatched. Complete Data remains 63,245,911 bytes. Code and function
matching are unchanged. The report has 12,891 units, with 12,143 complete.
The original unassigned range is partitioned into eleven reconstructed owners
and two unassigned gaps; every other prior unit's measures are unchanged.

All 27,301 prior editable asset input hashes and 11,836 asset object hashes
are preserved. Independently linked CPU code/data images and the original
runtime ELF are unchanged. The report snapshot is current. Preparation took
524.6 seconds, followed by 31.2 seconds for reporting and validation.

Report SHA-256:
`a81a34e7feb2c275eab5c0fe45ab3f8322b8f7046145cd0a2a4321822f35b72f`.
Source fingerprint:
`c1744fbef0c4e6d428bb0d4f16607d0c061c684831a5d08be2ff73a38b7ee3a1`.

The companion JSON records the native bindings, full-function checksums,
storage extents and payload hashes. Temporary audit logs and detailed model
scan evidence are retained under `build/us/data-completion/`.
