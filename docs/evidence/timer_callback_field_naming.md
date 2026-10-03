# Timer/callback object member naming

This narrow follow-through to [shared-helper semantic naming](shared_helper_semantic_naming.md)
renames four existing members across three source-local views in
`src/done/game/game_1765E0.c`. It describes two already-established byte offsets,
not four new physical fields or four new function roles. The names are descriptive,
not recovered original names.

- `Game1765E0EffectHeader.callback_other` and
  `Game1765E0DispatchState.field_12` become `drawCallbackIndex`
- `Game1765E0EffectHeader.field_13` and `Game1765E0State.field_13`
  become `callbackSetIndex`

## Storage, consumers and provenance

The complete constructor `15149130` stores its signed draw selector at object
+0x12 and unsigned callback-set selector at +0x13. It allocates 0x28 base bytes
plus `extraBytes`; the header remains a partial 0x24-byte view. Its 16-byte clear
covers only +0x14..+0x23. `15167A68` passes the allocation size to the allocator;
`15168A4C` records the kind and links the object into the corresponding list.
Flag bit 1 selects kind 0x5F instead of 0x23. Neither forwarded argument is renamed.

The two complete 52-byte kind records at `8008BBC4` and `8008C7F4` are identical.
The update sweep `151670C0` invokes their +0x00 entry, `15149264`, with the object.
Renderer `151674F8` invokes their +0x08 entry, `15149490`, passing the object as
its second argument. That consumer loads +0x12 with `lb`, skips exactly -1 and
otherwise indexes `D_8008A670`. Its six entries were independently checked.
The unchanged wrapper `151491F4` supplies -1 for this selector. There is no
additional draw-selector bounds check.

The same unsigned +0x13 selector indexes three different 74-entry callback
sets: `15149394` uses `D_8008A688`, `151493E4` uses `D_8008A7B0`, and
`15149434` uses `D_8008A8D8`. Each uses `lbu` and substitutes entry zero for
values at least 74. The retained negative test cannot fire for an unsigned
byte. The third consumer additionally skips a null callback; its existing raw
`u8` offset access is unchanged.

These are verified kind-record receiver paths, not phase names inferred from
table order. `1516972C` indexes kind-record +0x28 and `1516979C` indexes +0x2C,
passing the object to `15149394` and `151493E4` respectively. The object-list
walkers `15169070`, `15169260` and `1516944C` invoke kind-record +0x1C, which
points to `15149434`, with the object and forwarded arguments. No broader
initialization, destruction, timing or exclusive-character claim is added.

Fresh checks used the independently normalized US ROM with SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. They reauthenticated 247 complete
reference spans totaling 80,968 bytes, including all 12 functions in the source,
allocation/dispatch support, table targets, and all 84 constructor and 34 wrapper
direct-call sites with their complete containing functions. Main-reference
coverage independently checked 41,012 instruction words. All four callback tables
and both kind records were read from freshly decoded ROM data. Static J/JAL and
aligned-pointer coverage does not establish every computed or runtime call path.

Bounded execution of the exact four ROM dispatchers over all 256 byte inputs
(1,024 cases), including branch/call delay slots, confirms the unsigned clamps,
third-table null check and signed -1 draw sentinel. Execution stops at callback
entry; it is not runtime observation or a claim that other signed draw indices
are valid.

## Exact preservation and layout

Only nine member declaration/access tokens change. An exact member-token inverse
recovers the entire source byte-for-byte; every other lossless token, including
whitespace and comments, is identical. All 12 definitions, exact signatures,
source-discovery and declaration-recovery results remain unchanged. No new
macro collision or duplicate member is introduced. Existing same-spelling
constructor/wrapper parameters are in a separate C namespace and are unchanged.
Isolated patch apply/reverse and whitespace checks pass.

A private probe compiled with the pinned IDO toolchain and unchanged project
flags confirms identical before/after sizes and alignment: header 0x24/2,
state 0x14/1, dispatch state 0x13/1, and unchanged effect view 0x12/2. The two
renamed offsets remain +0x12 and +0x13; the draw members remain `s8` and the
callback-set members remain `u8`. All padding, order, other offsets and the
0x10-byte data array are preserved. No shared header, source type, literal,
function, exported name, volatile local or unresolved parameter changes.

Prepared against `f440e93689daf8c8425fa70279d0d2a20b3f454b`:

- Before source SHA-256: `474f0f8bddccbdd6dc0fec0842250a061b6524deec0aafd9837ee1e0102a75e2`
- After source SHA-256: `302599ba8cad7ea84b8c299fcc47c4682c5a8d1c4e615808619e73196919f161`
- Source-only patch SHA-256: `90874fd7bc8473155c0ed08f4637f3920c25db6954da74c374075a62b5930778`

## Acceptance remains separate

Preparation compiled only private layout probes. It did not compile the game
source, run focused matching, source-unit layout, a game build, a matching/queue
transaction or a clean batch. Parent integration must still verify focused
constructor/wrapper/updater/callback spans, layout, all allocated object sections
and symbol records, full US ROM equality and the required batch/tests. This adds
zero C matches and zero matched bytes. The source patch contains no ROM, asset,
generated assembly, binary or private runtime artifact.


## Accepted integration

Independent review approved the exact four-member/nine-token patch and repeated
the pinned layout probes. Full registered spans `15149130`, `151491F4`,
`15149264`, `15149394`, `151493E4`, `15149434` and `15149490` remain
`CURRENT (0)` with reviewed source-unit layout preserved. A clean nine-function
verification batch, full US ROM, integrated game/data/rodata, progress and
whitespace gates passed. Host and pinned ROM-aware suites each passed 1,764
tests (37 host skips; one optional pinned validator skip). All 30 ELF symbol
records and every allocated section of the source object are identical; only
nonallocated `.mdebug` differs. These are four names across local views of two
existing selector bytes. No function, matched-byte or source-unit credit is added.
