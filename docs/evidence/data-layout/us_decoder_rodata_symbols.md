# US decoder read-only data symbols

The actual `libultrare` archive member `decoder.o` already reconstructs all
20,784 bytes at `0x800ABB20:0x800B0C50`. The
[decoder reconstruction evidence](../libraries/libultrare_us_mp3_decoder_reconstruction.md)
establishes the complete code and data ranges independently. This correction
lets native objdiff compare that existing reconstruction without treating scalar
Huffman offsets as pointers or anonymous compiler constants as missing source.

## Named arrays and scalar relocations

`lib/libultrare/src/libultrare/mp3/decoder.c` declares 244 global constant arrays.
Their names and compiled payload sizes are recorded in `config/symbols/game-us.txt`
at the reviewed section base plus each archive symbol's offset. They contain
20,370 payload bytes and two intervening alignment bytes. Their final payload
ends at `0x800B0AB4`. No array boundary comes from the next referenced address.

These arrays contain scalar records, integers and floating-point values. They
contain no pointers; the actual read-only section has no relocations. The
`can_reference:False` attributes prevent the reference disassembler from
interpreting small scalar offsets as pointers. Previously it emitted ten false
relocations to `D_1C0`, `D_508` and `D_830`, changing twenty literal bytes in the
relocatable reference. The corrected reference retains the original scalar words.

## Anonymous compiler objects

Only the report's comparison copy receives extra symbols. Candidate instructions
and section-relative HI16/LO16 relocations independently establish these extents:

| Address | Bytes | Candidate evidence |
| --- | ---: | --- |
| `0x800B0AB4` | 88 | `mp3dec00040164`: 84-byte three-word loop and one trailing word |
| `0x800B0B0C` | 288 | `mp3dec00041600`: 288-byte three-word loop |
| `0x800B0C2C` through `0x800B0C48` | 8 × 4 | Eight adjacent LUI/LWC1 pairs in `mp3dec_init` |

The local source declarations independently identify 22 `s32` values and a
`s32[2][3][3][4]` initializer. The recognizer checks the entire copy loop: distinct
registers, source and destination increments, load/store offsets, branch target,
delay slot, positive bound divisible by twelve, and at most two trailing words.
It rejects interior relocations, overlapping objects, invalid alignment and
extents outside the candidate section. Floating load width establishes four-byte
literals. It reads no ROM or target object, and never copies reference symbols.

The original final LWC1 at `0x151F42A4` establishes the four-byte literal at
`0x800B0C48`; its explicit reference size leaves the final four zero alignment
bytes anonymous. Existing reference normalization preserves these bytes and only
removes a disassembler-generated, unreferenced padding label. The full section
remains 20,784 bytes in both the denominator and ROM comparison.

The report hook is limited to the reviewed GAME `libultrare/decoder.o` owner.
It re-extracts the actual archive member, requires exact equality with the report
candidate and independently checks the entire relocation-free read-only payload
against its ROM-derived digest. `annotate` verifies that all original section
headers, section bytes, symbols and relocations remain unchanged. Only appended
symbol/string table entries differ. The archive and runtime linker input are
never rewritten. Archive hashes are retained as validation inputs.

## Verification scope

An isolated native objdiff 3.8.1 experiment compares all 20,784 read-only bytes
at 100%, after separately checking literal equality with the original reference.
ROM-free tests exercise instruction-derived sizes, idempotence, invariant
payloads and relocations, malformed loops, bounds, register aliasing, altered
branches, tail stores, float addressing, stale archive candidates and false
whole-section ROM proofs.

The accepted working tree based on `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7`
passes 12 focused tests and all 2,905 Docker tests (eight skips). The full
`./conker build --assets` reproduces all 67,108,864 US ROM bytes. A subsequent
native report changes only `game/sdk/libultrare/decoder.o`, adding 20,784 matched
data bytes. Global Data is 63,080,660 / 65,120,512 (96.86758%). Code totals,
completion totals, denominators and all 26,430 prior source hashes are unchanged.
Progress and whitespace checks pass.

Independent native mutations of all 254 arrays and constants remove perfect
read-only section credit. Stock objdiff ignores anonymous alignment padding;
its native score alone is insufficient for that case. The separate whole-section
ROM digest check includes and rejects changes to those padding bytes.

Accepted report SHA-256:
`0418a141b193ab3476120fddc1dd119f728d3ca4bd626796f85662aa8e7fd46d`.
Source fingerprint:
`2d3bf63c4ae065f2483ab044c68550bbb5beeb07a602b86b2bf1db28dc9c140e`.

This adds no `complete_data` claim: these GAME sections retain
their reviewed `NOLOAD` placement and preserved ROM backing. Actual asset
integration is still required before their owner can become complete.
