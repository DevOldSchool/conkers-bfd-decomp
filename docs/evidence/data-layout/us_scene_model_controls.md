# Bounded US scene model controls

This extends the scene-field reconstruction by **7,665 bytes**: fifteen additional
bytes in each of 511 bank-0C child-2 model-placement records. The prior transforms
and all other scene fields retain their exact values. The existing native unit
`assets/scenes/fields` grows from 34,702 to 42,367 bytes; it is not duplicated.

| Stored offset | Width | Source field | Native use |
| --- | ---: | --- | --- |
| 12 | 4 | model source kind | Select ordinary bank-03 loading or model dispatch |
| 16 | 4 | model source index | Select the model asset or dispatch entry |
| 20 | 4 | update handler | Select a 12-byte callback-table entry, or a direct pointer |
| 51 | 1 | script selector | Bind script references to the runtime model |
| 52 | 1 | initial state | Initialize runtime byte 0x6E and its state-dependent flags |
| 60 | 1 | transform flags | Initialize runtime byte 0x70, clearing bit 3 |

The full `func_150039E0` span proves the 68-byte stride, both bank-0B and bank-0C
load paths, field reads and runtime writes. Kind and index at 12/16 feed model
selection and sharing; the callback selector at 20 is converted through
`D_80088C90` when below 65535, otherwise copied as a pointer. Script selector 51
becomes runtime byte 0x72; the complete `func_151149AC` span compares that byte
when resolving a script selector. State 52 becomes byte 0x6E and contributes to
initial byte 0x6F. Flags 60 become byte 0x70; `func_150045C4` reads its low bit to
select the transformation path. These are storage and dispatch roles; the codec
does not infer the gameplay meaning of each state or callback.

All selected records use ordinary model kind zero. Other proved kind values
one and two remain valid in the bounded codec, but edited sources must still
reproduce the reviewed original bytes to pass the builder. Unknown bytes at
24–31, 44–50, 53–59 and 61–67 remain entirely uncredited, including their zeros.
The format emits slices 0–23, 32–43, 51–52 and 60 for each record, combining
these controls with the previously proved position, rotation and scale fields.

The child-2 source schema is version 2. Existing task-generated scene inputs
were first hash-checked, then upgraded with `./conker scene-fields recover`,
which backed up the entire old input directory. The independent audit checked
all three backup hashes against the preceding accepted checkpoint, compared
every old semantic field, and preserved 26,050 other source hashes. Normal
builds reject a stale version-1 source; they do not silently migrate it.

An independent direct-offset audit checks all native fields and preserves every
unknown byte. Each newly added scalar in all 511 model records was separately
mutated and checked against its exact native byte offset (3,066 mutations).
The broader scene audit additionally tests field components at child endpoints
and both endpoints of all 26 authenticated native consumer spans (52 rejected
consumer mutations). Focused tests cover native integer widths, model kinds,
handler pointers, stale schemas, source preservation, recovery, concurrent
changes and the actual linked object. The adjacent JSON contains those results.

Full ROM, Docker-suite, native-report, progress and whitespace acceptance is pending.

## Accepted checkpoint

The full US asset build reproduced all 67,108,864 ROM bytes in 27 seconds.
All 2,592 Docker tests passed in 130.015 seconds, with eight existing skips.
Native objdiff, progress and whitespace checks passed. Matched Data is
62,207,769 / 65,120,512 (95.527145%), up 7,665 bytes; code and denominators
are unchanged. All previous typed ranges and semantic values are preserved.
The three prior inputs are backed up by the recovery transaction.

Tested base commit: 094102644c4c2f5aefaa0fc4b609416918f66f58 plus uncommitted sources.
Source fingerprint: 661aa4e2857de4b1cc8abe03fc04d90450df65fe22ff11c14fefd55a9d304893.
Report SHA-256: 9680a5dba6a09b7746ed894e67a59e7651e24f04a29901c9e0b673747ee23e25.
