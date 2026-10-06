# US event activation diagnostics

`scripts/model_event_activation.py` produces bounded static reports for scenes
30 and 60. Scene 30 event 144 contains six conditional native creation requests
whose combined spawn records select bank 01 model 66. Scene 60 has eight literal
script-start requests in its five declared event programs; four request scripts
with initial model 162 actor tracks.

This is source-consumer evidence, not observed execution. It provides no
appearance preset, runtime visibility claim or gameplay instructions.

## Model identity

Model 66 is the purple flamethrower imp. The bank 01 model 66 link here is
established numerically from the ROM; it does not identify a playable tank or
establish a real-world area name for scene 30.

## Reviewed input and fail-closed boundaries

Only normalized US SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a` is admitted.
Every report also verifies complete consumer code spans, dispatch/arity tables,
scene-list ROM spans and decoded hashes, event-program ROM spans and decoded
hashes, spawn payloads and the shared five-record prefix. The executable
constants contain all exact hashes; they are fixed review inputs, not hashes
computed and accepted from an arbitrary replacement ROM.

| Scene | Bank 15 scene-list ROM span | Declared bank 14 event IDs |
| --- | --- | --- |
| 30 | `0x132F4F0..0x132F558` | 144 |
| 60 | `0x1330130..0x13301A0` | 169, 170, 171, 172, 173 |

| Event | ROM span | Decoded bytes | Instructions |
| --- | --- | ---: | ---: |
| 144 | `0x13176A8..0x1317B71` | 3390 | 709 |
| 169 | `0x131C658..0x131C738` | 410 | 93 |
| 170 | `0x131C738..0x131CBA7` | 2280 | 455 |
| 171 | `0x131CBA8..0x131D53A` | 5316 | 986 |
| 172 | `0x131D540..0x131D8B2` | 1530 | 251 |
| 173 | `0x131D8B8..0x131DBD7` | 1660 | 344 |

The scene-list loader `func_15002FB4` requests `[0x15, scene]` through
`func_1502B6BC`. Its first child is the scene header; header byte `+0x12`
supplies `D_800D2F3C`, and the second child's pointer supplies `D_800D2F40`. The
parser verifies the first child starts at 0x10 with size 0x4C, the second starts
at 0x60 with a terminated descriptor, and its extent is exactly twice the
declared count. Padding, incomplete lists and duplicate IDs are rejected.

`func_1509B4A0` iterates those halfword IDs, calls `func_1509CBD4` for
admission, and conditionally calls `func_1509B5AC`. The latter resolves existing
events or loads bank 14 through `func_1509B8FC`; `func_1509B950` expands and
initializes state storage. The initial VM call is at `0x1509B684`. The report
preserves **declared** IDs: loader checks can alter admission/count, and the
listing is not proof all events ran. `func_1509BBA0` has additional
disabled/completion, scene, initialization and update-mode gates around its VM
calls, including `0x1509BD98`. No gate is assumed to have passed.

## VM and packet derivation

The pinned `func_150ADAF0` span starts at `0x150ADAF0` and is 1936 bytes. The
interpreter reads five entrypoints: fixed bytecode offset 0x20 and the halfwords
at header offsets 0x0E,0x10,0x12,0x14. Unrelocated source headers have zero
data/state pointers at 0x08/0x0A. The source bytecode extent comes from the
halfword at 0x04; runtime loading later rewrites these header fields.

At `0x150ADBC4`, the interpreter fetches a halfword and masks opcode with 0x3F.
The 31-byte arity table at `0x80087358` stores operand count plus one. Opcode 0
has a null dispatch and is rejected. Operand selectors occupy bits 13..15,
10..12 and 7..9. The mode tables at `0x800885D4`, `0x800885F0` and `0x8008860C`
distinguish frame words, state words, data addresses, program immediates,
literal values, return storage and native indices. Encoded offsets and normal
immediates are signed halfwords. Bit 0x40 widens the first encountered immediate
operand (mode 3,4 or6) to a signed word and is then consumed. The decoder does
not evaluate values loaded from runtime storage.

The opcode dispatch table is `0x80088628`. The relevant handlers are:

| Opcode | Handler | Bounded meaning |
| ---: | --- | --- |
| 14 | `0x150ADEF4` | Copy second value to first destination |
| 15 | `0x150ADEFC` | Jump to program-relative target |
| 16 | `0x150ADF08` | Jump if first value is zero |
| 17 | `0x150ADF1C` | Jump if first value is nonzero |
| 22 | `0x150ADF68` | Equality comparison |
| 24 | `0x150ADF88` | Push argument, increment pending argument count |
| 25 | `0x150ADFBC` | Call; mode 6 dispatches native, mode 3 calls internal code |
| 26 | `0x150AE054` | Return with value |
| 27 | `0x150AE040` | Establish frame and allocate locals |
| 28 | `0x150AE070` | Return/frame unwind |

Native mode dispatch uses `0x800886A4`; only its 14 reviewed entries are
accepted. The VM records pending arity in `D_800D3840` and resets the pending
count `D_800D3844` on calls/returns. PUSH decrements the stack before storing,
so contiguous pushes are reversed to recover native argument order.

Packet certification is deliberately structural. Conservative control flow
follows both conditional edges, seeds all event entries and internal callees
with zero pending arguments, and propagates pending counts. A packet is complete
only when all propagated counts agree with its adjacent PUSH run and no branch,
entrypoint or internal call enters the middle. Nonadjacent pushes, conflicting
counts, unbounded push loops and computed argument values cannot certify a
literal request. Branches/calls into operands or outside the instruction extent
fail closed. This analysis does not establish feasibility of a branch path.

## Scene 30 event 144 and model 66

Decoded SHA256 is
`947236f9d506dd1dd43e6345d831a4d46ad41475b74be0e46e3da341e63950e7`. The update
entry at 0x138 calls internal controller0x430 at 0x144. Its jump at 0x434
reaches the phase dispatch at 0xC50. Equality opcode 22 compares event state
word `+0x2C` to literal phases; opcode 17 selects the matching block.

| Phase | Region selector | Query call | Create call | Spawn selector | Combined record |
| ---: | ---: | --- | --- | ---: | ---: |
| 2 | 20 | `0x5C8` | `0x5DC` | 6 | 5 |
| 3 | 21 | `0x61C` | `0x630` | 7 | 6 |
| 5 | 22 | `0x6F8` | `0x70C` | 8 | 7 |
| 10 | 23 | `0x98C` | `0x9A0` | 9 | 8 |
| 11 | 24 | `0x9E0` | `0x9F4` | 10 | 9 |
| 12 | 25 | `0xA34` | `0xA48` | 11 | 10 |

Each query packet calls native 5 with `[0x2000,172,0x4000+region]`. Native 5's
wrapper `0x150AE118` uses the class table at `0x80088498`; class 2 selects
`func_15099C14`. Its operation 172 switch entry at `0x8009E1B4+(172-145)*4`
resolves to `0x1509A15C`. It resolves the actor via `func_1505EEF4`, derives the
actor index and calls `func_150A2AEC` at `0x1509A1A8` with one region argument.
The region helper checks cached membership or calls `func_150A1DA0`; a
successful region is returned as `0x4000|region`, and failure as zero. The
consumer checks include the full helper/callee spans.

The following copy takes return storage (mode 5), then opcode 16 skips creation
when it is zero. Each surviving creation packet calls native 3 with the literal
`0x2000+selector`. Native 3's wrapper `0x150AE0F8` uses `0x80088420`; class 2
selects `func_15097910`. That function first tries the existing-actor path
through `func_15083E90`. If no actor is reused, it clears the spawn gate at
`0x1509796C` and calls `func_15082A44` at `0x15097980`.

The scene 30 bank 0E payload has 1344 bytes and SHA256
`ab38baf18478d0b573d253cbf4995601b8cd056cce8f47aa0da83635ef647eac`. The checked
scene switch selects the 240-byte prefix at ROM `0x1A33F0..0x1A34E0`, SHA256
`c00f174e84c2718bda836eab7ed50ccb5598f766207758e0a105f9a00c3433be`. Combined
records 5..10 uniquely match selectors 6..11. All have model byte 66 and initial
gate byte 1, which skips ordinary spawning. Their numeric model identity is
`[1,66,0]`. None of this proves the stated phases, region membership, new
creation or model 66 visibility occurred in a preserved capture.

## Scene 60 script requests

Native 6's class 1 entry in `0x800884D4` selects `func_1509C440`. Its operation
1 path checks slot 0 byte `0x800C35EA`, takes the current scene from
`0x800BE9F0` for a two-argument packet, and calls `func_1501D348` at
`0x1509C520`. Other arity/operation cases can override the scene or use
different behavior; the classifier admits only complete two-literal-argument
operation 1 packets.

| Event | Call offset | Conditional script asset | Initial matches among 154/155/162 |
| ---: | --- | --- | --- |
| 169 | `0xC6` | `[6,60,1]` | None |
| 170 | `0x60C` | `[6,60,8]` | 162 |
| 170 | `0x7B0` | `[6,60,10]` | 162 |
| 170 | `0x7CE` | `[6,60,11]` | 162 |
| 170 | `0x88E` | `[6,60,12]` | 162 |
| 171 | `0x76C` | `[6,60,15]` | None |
| 171 | `0x7FC` | `[6,60,16]` | None |
| 171 | `0x89C` | `[6,60,13]` | None |

The existing `scene_scripts` consumer parser independently links initial,
nonzero-counter type 2 tracks to the first matching combined spawn record. For
scripts 8/10/11/12 this is selector 14, combined record 13, model 162. Scripts
7/14 elsewhere in the scene directory have initial model 154 tracks; these are
not among the eight admitted event requests. No initial model 155 match occurs
in this bounded scene 60 route report. These absences say nothing about later
tracks, borrowed animation, dynamic selectors, direct native actor changes or
other activation routes.

For a later capture, the source provides concrete observations to seek: scene 30
event 144/controller phase, region-query result, selector resolution and
new-versus-existing actor outcome; or scene 60 event 170's listed packet and
slot/pending-script gate outcome, followed by the model 162 actor and submitted
draw. It does not supply a proven save state, controller sequence, room name,
phase progression strategy or natural activation recipe. Those remain the next
evidence gap.

## Reproduction and verification

```sh
PYTHONDONTWRITEBYTECODE=1 python3 -m scripts.model_event_activation --scene 30 \
  --output build/assets/models/event-activation-scene30.json
PYTHONDONTWRITEBYTECODE=1 python3 -m scripts.model_event_activation --scene 60 \
  --output build/assets/models/event-activation-scene60.json
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s tests \
  -p 'test_model_event_activation.py'
```

The report includes exact code/table/source identities, all decoded
instructions, entrypoints, branch/call targets, call packet identities,
conditional requests and bounded script/spawn links. It never starts an emulator
or modifies models.

The focused tests cover operand width/sign, reversed push order, invalid
headers/opcodes/modes/targets, partial packets, control-flow joins and loops,
exact scene 60 request sets, scene 30 semantic guards and both real reports.
Mutating every pinned consumer/table span is rejected. Actual scene 30 bytecode
mutations are also decoded under test-only replacement input hashes, proving
phase, query, controller and selector checks reject changes beyond the outer
hash guard. The three ROM integration tests skip if no reviewed local ROM is
available; no ROM, decompressed bytecode or generated report belongs in the code
commit.
