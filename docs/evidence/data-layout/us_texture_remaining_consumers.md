# Remaining US texture consumer research

This note records bounded exclusions after the passing texture batch at
`b6a07200276891d06b4a84f7023a217a8b60daa1`. It adds no reconstructed assets or
matching credit. That batch contains 6,865 textures; its validation is recorded
in [texture reconstruction](us_texture_reconstruction.md).

All addresses below refer to the original US ROM, SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. Runtime resource IDs include the two
empty slots at 1767 and 1768; physical stream ordinals do not.

## Direct loader coverage

A fresh word-aligned J/JAL scan of the checksum-validated CPU intervals returned
by `scripts/rom_span.py` found the following direct calls:

| Target | GAME calls | Main calls | Debugger calls |
| --- | ---: | ---: | ---: |
| `1510D0EC` flat loader | 64 | 0 | 0 |
| `1510CE60` display-list resource resolver | 10 | 0 | 0 |
| `150950D4` CPU texture upload | 5 | 0 | 0 |

There were no J tail calls to these targets. No aligned literal pointers to
these three functions occur in GAME or debugger data. A bounded lexical search
for a matching LUI plus ADDIU/ORI within 32 instructions found no additional
function-address construction leads. This is not proof against arbitrary
computed indirect calls, and the pointer scan does not cover main data.

## Descriptor-only character resources

The complete native display-list regions in models 7, 30, 35 and 62 contain
90 SetTextureImage commands and produce 63 parsed material runs. Every image
command addresses a direct flat resource. None uses texture segments 6, 7,
10 or 11. Thus a missed segmented image command in these models does not explain
these unused descriptor entries:

| Resource | Model / descriptor | Declared dimensions | Payload bytes |
| --- | --- | --- | ---: |
| 944 | 7 / 2; 35 / 13 | 32 by 32 | 1,536 |
| 1938 | 7 / 3; 35 / 14 | 32 by 32 | 1,536 |
| 1973 | 30 / 7 | 44 by 44 | 2,624 |
| 4599 | 62 / 4 | 16 by 32 | 1,216 |
| 7717 | 62 / 3 | 16 by 32 | 1,216 |

This does not exclude another CPU consumer or runtime command mutation. The
sizes and descriptor dimensions alone do not establish an image format.

## Resource 3775 and source-plane offsets

Pointer-table selector 66 identifies descriptor `80091858`: resource 3775,
count 1, flags 0, I4, 64 by 64. Its payload is 4,096 bytes. The reviewed upload
uses 1,024 16-bit transfer words, covering 2,048 bytes.

`15095060` copies the descriptor into the compact upload structure. The upload
at `150951BC..150951D0` can advance its source by twice the transfer count times
argument 4. A value of one would reach a second 2,048-byte plane, but all five
direct upload call sites explicitly pass zero:
`15094FD0`, `15095048`, `150D1970`, `151481B0` and `1517E8DC`.
The pointer-table effect route `1516D738 -> 15142E24 -> 15094FE8` also uses zero.
A second plane therefore needs different consumer or mutation evidence; this
route does not establish one. Nonzero bytes in the tail must not be called
padding merely to obtain a complete contract.

## HUD selectors

`150911F4` loads four resource halfwords from `800D2578..800D257E` at
`15091430`, `15091464`, `15091498` and `150914CC`. Reviewed stores in
`1509093C` choose among these original-ROM values, according to counter
thresholds 480, 960 and 1200:

| Original halfword | Runtime resource | Physical stream | Already selected |
| --- | ---: | ---: | --- |
| `8009025A` | 1937 | 1935 | yes |
| `80090262` | 1946 | 1944 | yes |
| `80090266` | 1942 | 1940 | yes |
| `8009026E` | 3649 | 3647 | yes |
| `80090272` | 3657 | 3655 | yes |

This source-store review does not exclude arbitrary later alias writes.

The three direct callers of `15091534` pass argument 1 as zero, zero and one
at `1509227C`, `15092448` and `15092830`. Its `3350 + argument1` resources are
both already selected.

The timer renderer `150938BC` forms its resource as `4525 + signed remainder
modulo 10`. Even allowing negative timer values, the conservative resource
range is 4516 through 4534. Only 4522, 4523 and 4524 in that range remain
unselected; their payloads are 2,560, 1,440 and 1,536 bytes respectively. None
is a complete instance of the timer model's 16-by-32 IA4 image (256 bytes).
This excludes a new full-payload timer contract without asserting that negative
timers are reachable or that these resources lack other uses.

## Boat appearance table and command queue

The seven words at `80090214` are resources 4195, 4197, 4196, 4198, 7180,
7181 and 7182. Script opcode 13, suboperations 2 and 3, reads a signed table
index from command byte 5. The loads at `15024AFC` and `15024B20` store the
selected resource into attachment halfwords `+18` and `+1A`. Attachment lookup
`1503195C` receives the command's signed halfword at `+2`, plus one; a null
lookup skips the store.

A census of all 483 decoded bank-06 scripts completed without errors and found
seven opcode-13 texture commands:

| Bank / entry / script | Command bytes | Attachment | Field | Table index |
| --- | --- | ---: | --- | ---: |
| 6 / 4 / 9 | `0d32004902000000` | 74 | `+18` | 0 |
| 6 / 4 / 9 | `0d00004903000000` | 74 | `+1A` | 0 |
| 6 / 4 / 9 | `0d00004903030000` | 74 | `+1A` | 3 |
| 6 / 4 / 9 | `0d0e004902030000` | 74 | `+18` | 3 |
| 6 / 6 / 38 | `0d37003a02050000` | 59 | `+18` | 5 |
| 6 / 20 / 4 | `0d07003a02060000` | 59 | `+18` | 6 |
| 6 / 37 / 9 | `0d5900ab02040000` | 172 | `+18` | 4 |

None selects index 1 or 2, which would identify resources 4197 and 4196.
This is a stored-command census, not proof that every listed command executes.

The reviewed native queue forwards command pointers rather than manufacturing
new opcode-13 packets. Track processor `150242F8` calls insertion routine
`150241B4` at `150244B8`. Queue records are 12 bytes; their first word is the
command pointer. Drain routine `15024130` calls wrapper `1502A8A0` at
`15024180`; that wrapper calls command dispatcher `1502460C` at `1502A9C0`
and `1502AA8C`. The two direct drain calls are `150241F0` and `150245B4`.

A fresh scan of all three checksum-validated CPU code intervals found exactly
these six JAL calls to the insertion, drain, wrapper and dispatcher functions.
It found no J tail calls, aligned function-address literals in those code
intervals, or lexical LUI plus ADDIU/ORI address-construction leads within
32 preceding instructions. This bounded scan does not cover literal pointers
in data, arbitrary computed dispatch, or later mutation of script bytes.

The nearby light table at `80090204` is a separate consumer. Light renderer
`150DE458` forms a pair address using object `+7C` times eight. Hypothetical
selectors 2 and 3 would overlap the boat words, but the reviewed model
`4:28:12` uses 32-by-64 CI8 sources with a 512-byte palette: 2,560 bytes.
Resources 4196 and 4197 each contain 1,536 decoded bytes. This neighboring
lookup therefore does not establish a complete light-material storage
contract, even before proving either hypothetical selector reachable.

Neither resource is newly admitted. A different binding or concrete mutation
witness is required before revisiting these exclusions.

## Event operation domains and object property writes

The class-3 setter `1509E900` must be distinguished from the class-2 actor
setter. Its jump table at `8009F3F0` sends operation 4 to `1509EAD8`, which
writes arguments 2, 3 and 4 into object words `+7C`, `+80` and `+84`, skipping
each argument equal to `INT_MAX`. Operation 8 enters at `1509EB80`: it replaces
the upper halfword of object `+3C` with argument 2 and writes argument 3 to
object `+7C`, without that sentinel check. Operation 8 cannot be dismissed as
only a coordinate update for every handle class.

The research event decoder recovered 203 stored programs and 5,093 calls to
native dispatch slot 6, with no syntax errors under its documented header and
data-section extensions. Twelve calls have a nonliteral operation operand.
All twelve read frame argument `+8` in three internal helpers. Their stored
callers supply these exact literal domains:

| Event | Helper byte offset | Setter calls | Operation values |
| ---: | ---: | ---: | --- |
| 10 | 2820 | 2836, 2852, 2868 | 5, 6 |
| 44 | 3188 | 3204, 3220, 3236 | 5, 6 |
| 73 | 3150 | 3162, 3174, 3186, 3198, 3210, 3222 | 0, 1 |

The helpers do not write frame argument `+8`. No other explicit branch or
internal call enters their interiors, and none is a header entrypoint. Thus
these stored call paths add neither actor texture operations 110/111 nor
class-3 property operations 4/8. This is a stored control-flow argument, not a
proof against runtime modification of event code or frames.

Thirty-two additional slot-6 packets have empty pending-argument-count sets
in the decoder's graph, which starts at all five header entrypoints and every
stored internal callee. The empty sets mean no path was found
in that graph. This observation does not establish
unconditional runtime unreachability.

Three previously unresolved actor-handle producer domains are also bounded:

| Event | Counter test byte offset | Counter body values | Constructor input |
| ---: | ---: | --- | --- |
| 73 | 110 | 0 through 4 | `0x2006..0x200A` |
| 150 | 2552 | 0 through 3 | `0x2013..0x2016` |
| 167, initial loop | 214 | 0 through 3 | `0x2007..0x200A` |
| 167, update loop | 1238 | 0 through 9 | `0x2007..0x2010` |

Each counter starts at zero, increments by one, and exits on the failed signed
less-than test. Event 150's helper returns a counter value or -1; its caller
rejects the negative result before adding `0x2013`. The reviewed constructor
inputs therefore select class 2, not the class-3 object setter. Events 73 and
150 pass the production syntax decoder. Event 167 retains the research-only
constant-data boundary at byte 1786. Native interpreter words were checked
for addition, copy, signed comparison and conditional branch semantics.

A separate initial-placement join examined literal class-3 operations 4/8
that can write `+7C`. It produced 142 packet/placement associations covering
43 distinct models. Their parsed pixel and palette sources are all direct
resources already selected by the validated texture batch. The join preserves
scene-list count and extent checks but allows empty lists and duplicate IDs:
13 scenes declare zero events, and scene 6 declares 37 entries with event 29
listed twice. The duplicate must not cause the entire scene to be omitted.

Nineteen associations still lack an explicit initial placement: event 99 in
scene 67 targets IDs 227/228; event 142 in scene 4 targets IDs
245/248/249/250/251; event 173 in scene 61 targets IDs 252/253. Runtime-created
objects, scene aliases, later mutations and rewritten display lists require
separate evidence. These checks admit no new texture contracts.

## Remaining uncertainty

These checks narrow specific consumer hypotheses. They do not prove global
texture exhaustion. Further matches require a verified full-payload storage
contract, including any palette, extra plane, mip level or nonzero tail, and
an exact PNG inverse and fresh compression result. Broader dynamic resource
bindings, later mutations and indirect consumers remain distinct research
questions. Repeating the exclusions above without new evidence is not a new
matching attempt.
