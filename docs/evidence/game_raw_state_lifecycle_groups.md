# US callback lifecycle and selected-state groups

Evidence type: `structural_analysis`

Four reviewed working groups contain 87 existing raw entries and 34,672
bytes. The offset-derived names identify reviewed ranges, not recovered
historical filenames. All code remains ASM-backed. One range is narrower than
its upstream raw split, excluding two separate numeric wrappers at its tail.

## Extents and provenance

The local upstream input is `mkst/conker` at
`3adf229175c037c771f251f169f9dd80ca306924`, `conker/conker.us.yaml`.
Its combined base is `0x2D4B0`. Both endpoints of three ranges occur there;
`game_CDE80.c` ends at a newly reviewed internal boundary, `0xA34B0`,
instead of adopting the full upstream extent through `0xA3A70`.
The owned US payload SHA-1 is
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.

| Source under `src/game/` | US range | Raw entries | Bytes | Debug correlations (strong) | ECTS correlations (strong) |
| --- | --- | ---: | ---: | ---: | ---: |
| `game_6B320.c` | `0x3de70:0x3f4b0` | 22 | 5,696 | 15 (10) | 14 (10) |
| `game_CDE80.c` | `0xa09d0:0xa34b0` | 26 | 10,976 | 21 (20) | 0 (0) |
| `game_19A8B0.c` | `0x16d400:0x170b90` | 30 | 14,224 | 25 (22) | 24 (18) |
| `game_1B0740.c` | `0x183290:0x184150` | 9 | 3,776 | 3 (0) | 3 (0) |

The beta counts use the corrected ECTS extraction. They supplement the
retail relationships and do not independently establish original file bounds.

## Retail evidence

### `game_6B320.c`

Opening `1503DE70` converts an object address to a `0x32C` pool index
and calls `1503DF0C`, which updates the root at `800C6660`.
`1503DF48` allocates/initializes state, calls `1503E1F4`, `1503E3C4`,
`1503EA54` and `1503E82C`, and dispatches through three adjacent tables.
It loads `80084430` and calls the selected initializer at `0x3E13C`, uses
`8008443C` at `0x3E174`, and uses `80084448` at `0x3E1AC`.

Those tables select late functions `1503F078/1503F0AC/1503F0D8`,
`1503EFC4/1503F108/1503F16C`, and `1503EEC0/1503F2B0`.
The late wrappers share `1503EB78`, `1503ECA0`, and `1503EF4C`;
`1503F2B0` also reuses early cleanup `1503E260`. Final `1503F404` calls
middle numeric helper `1503E5F8`. Twenty-one direct inter-function calls,
nine owned table pointers and repeated roots `800C6660/800C6664/800C6668`
connect the setup, update, callback and cleanup family across the range.

### `game_CDE80.c`

The connected core repeatedly accesses the selected-state roots at
`800D3094/800D3098`. Early `150A09D0` and `150A0D8C` use the shared
processor `150A1DA0`; large controller `150A11C4` calls it along with
`150A104C`, `150A23E4`, `150A24C0` and `150A25D4`.
Later wrappers `150A278C`, `150A29C8`, `150A2AEC`, `150A2D84`,
`150A3058`, `150A3194` and `150A32B4` reuse `150A1DA0`.
`150A2EE4/150A2FA4` share the alternate helper `150A2E4C`.

The final three short accessors `150A3330/150A3398/150A3444` still use
`800D3098`; the last stores three halfwords through that root and returns
immediately before `0xA34B0`. The following `150A34B0/150A3504` form a
separate numeric wrapper/implementation pair, with their own inputs and
constants rather than this selected-state root. No direct call joins that pair
to the reviewed core. They stay unregistered while the 26-entry core becomes
an independently usable working group. The distinction is supported by state
and calls, without claiming that the newly chosen split is a recovered linker
object boundary.

### `game_19A8B0.c`

Opening `1516D400` updates the four state bytes at
`800DD2A0/800DD2A1/800DD2A2/800DD2A3`; the same state feeds later
constructor wrapper `1516EED4`. Shared constructors `1516D4E8` and
`1516D99C` allocate related objects through `15167A68` and are reused
throughout the range. Early `1516DB90` and final `151709B4` both use
`15170034` and `1516D4E8`, connecting the two ends directly.

The early lifecycle callback `1516D678` indexes `8008CBA0` by object
byte `+0x23`, loads the pointer at `0x16D6BC`, and executes `jalr` at
`0x16D6C0`. Seven consecutive slots select `1516E8CC`, `1516ECAC`,
`1516F024`, `1516F9C4`, `1516FBCC`, `1516FD50` and `151707E0`.
Late handlers share `1516F864` and the paired field helpers
`1516F8EC/1516F91C`; several constructors also return to `1516D99C`.
Thirty direct inter-function call sites and fifteen owned callback pointers
support the family. Two engine descriptors select its early callbacks in
parallel at `8008B81C:8008B85C` and `8008C960:8008C9A0`.

### `game_1B0740.c`

The opening controller `15183290` repeatedly calls `15183ACC` and its
wrappers `151838B0`, `15183974` and `151839F0`. These helpers share
root `800DDE80` and state `800DDF68/800DDF69/800DDF78`.
The late controller `15183D28` uses the same roots and calls cleanup
`15183C28`, which frees the shared resources. Nine runtime descriptors
select `15183BA4`, which also uses `800DDF78`.

The final predicate `15184118` tests an object's custom pointer at `+0x31C`
and byte `+0x57`; it is called by the opening controller at `0x183490`.
Nineteen direct inter-function calls and the common resource/state lifecycle
support the complete short extent. Sparse weak beta correlations receive no
independent boundary weight.

## Anonymous return sequences and limits

The standalone beta index proposes eight-byte return sequences at
`1503EB70` and `1516ECA4`. Both contain `jr ra; nop` immediately after
another routine's completed return. Neither address has a direct J/JAL caller
in the US game code or an aligned pointer in owned game data. There is no
independent callback identity evidence, so neither is assigned a new symbol
or a separate function work item. Their bytes remain inside the existing raw
spans for `1503EA54` and `1516E8CC` respectively.

Thus raw membership has 22 entries versus 23 index candidates in the first
range, and 30 versus 31 in the third. These deliberate differences are not
silently treated as discovered functions. They do not affect byte coverage,
and the raw skeletons preserve the full spans. Existing named raw return-only
members are also preserved without a historical name or C-match claim.

Every raw word, delay slot and padding word equals the owned US payload.
Member spans cover all four ranges exactly; aside from the two anonymous
sequences just described, raw and indexed entry labels agree. No decoded
conditional branch crosses an endpoint in either direction. Preceding/final
returns and following prologues were inspected. These are working source
families, and finer historical subdivisions remain possible. No data, rodata
or BSS ownership is assigned.

## Integration result

All four groups integrate on the first complete-overlay attempt. The complete
2,072,880-byte US game binary remains byte-identical with SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All 87 entries remain
`raw_asm`, the four units have `mixed` integration state, and both anonymous
return sequences retain their exact bytes within the existing raw spans.
The comparison map remains raw assembly.

## Membership and integration gate

The supported command creates ordered ASM-backed skeletons and registers
membership after the reviewed raw boundary is present. Complete US overlay
byte equality gates integration. The comparison map remains raw assembly.

### `src/game/game_6B320.c`

Range SHA-1: `60f735bd8ddcd2bc6593796fda4e6b871a084276`. Spans include preserved padding and anonymous bytes.

| Entry | Raw span |
| --- | ---: |
| `func_1503DE70` | `0x9c` |
| `func_1503DF0C` | `0x3c` |
| `func_1503DF48` | `0x2ac` |
| `func_1503E1F4` | `0x6c` |
| `func_1503E260` | `0x164` |
| `func_1503E3C4` | `0x234` |
| `func_1503E5F8` | `0x234` |
| `func_1503E82C` | `0x228` |
| `func_1503EA54` | `0x124` |
| `func_1503EB78` | `0x128` |
| `func_1503ECA0` | `0x218` |
| `func_1503EEB8` | `0x8` |
| `func_1503EEC0` | `0x8c` |
| `func_1503EF4C` | `0x78` |
| `func_1503EFC4` | `0xb4` |
| `func_1503F078` | `0x34` |
| `func_1503F0AC` | `0x2c` |
| `func_1503F0D8` | `0x30` |
| `func_1503F108` | `0x64` |
| `func_1503F16C` | `0x144` |
| `func_1503F2B0` | `0x154` |
| `func_1503F404` | `0xac` |

### `src/game/game_CDE80.c`

Range SHA-1: `39b46ede286d40478bde99bb9d6d6e07f1180a82`. Spans include preserved padding and anonymous bytes.

| Entry | Raw span |
| --- | ---: |
| `func_150A09D0` | `0x344` |
| `func_150A0D14` | `0x78` |
| `func_150A0D8C` | `0x2b4` |
| `func_150A1040` | `0xc` |
| `func_150A104C` | `0x178` |
| `func_150A11C4` | `0xbdc` |
| `func_150A1DA0` | `0x644` |
| `func_150A23E4` | `0xdc` |
| `func_150A24C0` | `0x114` |
| `func_150A25D4` | `0x1b8` |
| `func_150A278C` | `0xd8` |
| `func_150A2864` | `0xdc` |
| `func_150A2940` | `0x88` |
| `func_150A29C8` | `0x124` |
| `func_150A2AEC` | `0x1b8` |
| `func_150A2CA4` | `0xe0` |
| `func_150A2D84` | `0xc8` |
| `func_150A2E4C` | `0x98` |
| `func_150A2EE4` | `0xc0` |
| `func_150A2FA4` | `0xb4` |
| `func_150A3058` | `0x13c` |
| `func_150A3194` | `0x120` |
| `func_150A32B4` | `0x7c` |
| `func_150A3330` | `0x68` |
| `func_150A3398` | `0xac` |
| `func_150A3444` | `0x6c` |

### `src/game/game_19A8B0.c`

Range SHA-1: `2c1a5566365b86cdde52322a0f68d41720baa841`. Spans include preserved padding and anonymous bytes.

| Entry | Raw span |
| --- | ---: |
| `func_1516D400` | `0xe8` |
| `func_1516D4E8` | `0x190` |
| `func_1516D678` | `0xc0` |
| `func_1516D738` | `0x264` |
| `func_1516D99C` | `0x1f4` |
| `func_1516DB90` | `0xbe8` |
| `func_1516E778` | `0x154` |
| `func_1516E8CC` | `0x3e0` |
| `func_1516ECAC` | `0xbc` |
| `func_1516ED68` | `0x16c` |
| `func_1516EED4` | `0x150` |
| `func_1516F024` | `0x19c` |
| `func_1516F1C0` | `0x138` |
| `func_1516F2F8` | `0x250` |
| `func_1516F548` | `0x31c` |
| `func_1516F864` | `0x88` |
| `func_1516F8EC` | `0x30` |
| `func_1516F91C` | `0x30` |
| `func_1516F94C` | `0x38` |
| `func_1516F984` | `0x40` |
| `func_1516F9C4` | `0xc4` |
| `func_1516FA88` | `0x144` |
| `func_1516FBCC` | `0x184` |
| `func_1516FD50` | `0xcc` |
| `func_1516FE1C` | `0x218` |
| `func_15170034` | `0xa4` |
| `func_151700D8` | `0x428` |
| `func_15170500` | `0x2e0` |
| `func_151707E0` | `0x1d4` |
| `func_151709B4` | `0x1dc` |

### `src/game/game_1B0740.c`

Range SHA-1: `3401634a4305b3b268cf202770d1851e024ff102`. Spans include preserved padding and anonymous bytes.

| Entry | Raw span |
| --- | ---: |
| `func_15183290` | `0x620` |
| `func_151838B0` | `0xc4` |
| `func_15183974` | `0x7c` |
| `func_151839F0` | `0xdc` |
| `func_15183ACC` | `0xd8` |
| `func_15183BA4` | `0x84` |
| `func_15183C28` | `0x100` |
| `func_15183D28` | `0x3f0` |
| `func_15184118` | `0x38` |
