# US event-program reconstruction

The complete bank-14 allocation at `0x1304F00..0x132E698` reconstructs
**169,880 ROM bytes** from 203 event programs: 62,491 typed instructions and
272 constant strings. Slot 106 of the 204-entry index is empty. The original
compressed programs and index bytes are comparison targets, never encoder inputs.

## Native format evidence

The full original-ROM consumer and table spans in
`scripts/model_event_activation.py` gate the loader, interpreter, instruction
arity, operand-mode dispatch and native-call dispatch. The loader's
`func_1509B950` initializes runtime state storage; the interpreter reads the
constant-section offset at header `+8`, state offset at `+A`, and five entrypoints.
`1509B5AC` tests the `0x1000` and `0x0800` flag bits; `1509BBA0` tests `0x2000`.
Only these source flag bits are accepted. Runtime pointers, scene and unused
header fields regenerate as zero. Program size and constant offset are derived.

Instructions contain opcode, operand modes and one explicit wide-immediate
flag. The first immediate operand in modes 3, 4 or 6 consumes that flag and
uses a signed word; other operands use signed halfwords. The opcode arity table
is checked against the pinned original bytes. Program-relative operands and
entrypoints use instruction labels, so widening a preceding instruction
relocates them. Frame/state offsets, literal values, return storage operands
and native indices retain their native typed integer domains. Unused selector
bits cannot survive as unexplained raw instruction words.

All constant-address operands are PUSH operands. The interpreter forms their
addresses from the header's constant base and pushes pointers. The 272
referenced constants cover contiguous ASCII strings with NUL terminators,
including newlines and escape sequences; the section ends with one to four
zero bytes to the next four-byte boundary. String labels regenerate their
relative offsets. Embedded NULs, unreferenced constants, unexplained gaps and
nonzero tails are rejected. Native slots 1/2 target the full pinned 16-byte
stubs `1509DD20`/`1509DD30`; stored diagnostic text does not establish runtime
printing or event activation.

## Editable build and exact storage

`scripts/event_codec.py` generates each program from semantic fields, then
fresh zlib level-6 raw DEFLATE with the native decoded-length prefix. Level 6
matches all 203 stored entries; level 9 matched only 171 in the bounded pilot.
The bank encoder generates all offsets, sizes, compressed/terminal flags,
the empty slot and eight-byte zero alignment. The whole bank equals the ROM.

`./conker event-assets build` initializes
`build/assets/event-build/us/{manifest,programs}.json` once. Later builds
freshly encode and independently compare the entire original bank. Missing,
malformed or changed inputs fail without being overwritten.
`./conker event-assets recover` backs up the source directory before restoring
reviewed records. The source contains no raw header words, instruction words,
compressed payloads or backing-bank copy.

`ASSETS=1` links the actual `asset_bank_14.o` from the reconstructed part. Make
tracks the typed source, decoder evidence and codec dependencies and rejects
missing inputs even if an old object remains. Native objdiff compares that
actual object with fresh encoding and an independent original-ROM target.
Complete-bank credit replaces exactly the former raw-storage allocation;
337,192 decoded program bytes add no second Data allocation.

[Machine-readable evidence](us_event_reconstruction.json) records all 203
programs and their decoded hashes. Independent mutations cover flags, literal
operands, instruction or entrypoint labels, and the first/last characters of
all strings: **1,153 mutations** change the fresh encoding. All 34 endpoint
mutations across the twelve full code spans and five table spans are rejected.
Editable source hashes remain unchanged. Tests cover label relocation,
wide signed values, strict schema and padding, empty index slots, source
preservation/recovery, Make invalidation and stale native objects.

## Accepted validation

The asset build reconstructs all 67,108,864 ROM bytes exactly (SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`). The full Docker suite passes
2,521 tests with eight skips; native objdiff has no compile errors. Progress
and whitespace checks pass.

Native matched Data increases by **169,880 bytes** to **60,434,090 /
65,120,512 (92.80346%)**. Complete Data is 60,433,322 bytes (92.80228%).
Code totals and all 10,622 previous asset proofs remain unchanged; all
25,501 previous source-file hashes are preserved. The report has 11,637
units, 10,947 complete.

Validated source fingerprint:
`6fab955d13893bc983f7c530090a66947b8b5b345589aef290e62d5f86ba708b`.
Report SHA-256:
`63591c5c612c87078ce5274c4630a21b7ed14c93f036fdacc2b886e245bf75f1`.
The local report was current when independently audited; this is a local
result and has not been published to decomp.dev.
