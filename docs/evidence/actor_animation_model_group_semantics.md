# Actor animation-model representative

`func_15084D00` has the descriptive role
`actor_get_animation_model_representative`. This is an inferred role, not a
recovered original developer name. The change is one comment immediately
before its existing disabled-candidate guard in `src/game/game_B21B0.c`.
No identifier, declaration, type, field, ABI, numeric symbol or expression
changes. The complete `CURRENT (1665)` candidate and raw-assembly placeholder
remain unchanged.

## Exact selection contract

The complete 112-byte function reads the unsigned current model byte at actor
`+4` at `15084D04`. It scans seven byte-counted model groups in table order,
using the pointer table at `80087240` and counts at `8009D954`. Within a
nonempty group it tests members in order. A match returns that group's first
member through the return delay slot at `15084D4C`; after all seven groups
fail, it returns the original unsigned byte at `15084D64`. A zero count skips
its group without reading that group's pointer. There are no writes or calls.

These are the initial values decoded from the checksum-validated loaded game
data. They establish neither immutable tables nor observed runtime activation.
The helper follows the current table contents on each call.

| Group | Member address | Count | First member | Complete model IDs, in stored order |
| --- | --- | ---: | ---: | --- |
| 0 | `8009D920` | 21 | 0 | 0, 1, 2, 3, 4, 59, 117, 128, 130, 136, 144, 150, 152, 156, 157, 159, 160, 176, 177, 178, 180 |
| 1 | `8009D938` | 5 | 90 | 90, 95, 116, 122, 141 |
| 2 | `8009D940` | 2 | 58 | 58, 61 |
| 3 | `8009D944` | 3 | 80 | 80, 154, 155 |
| 4 | `8009D948` | 2 | 16 | 16, 56 |
| 5 | `8009D94C` | 2 | 83 | 83, 165 |
| 6 | `8009D950` | 4 | 5 | 5, 173, 174, 175 |

All 39 listed model bytes are distinct in this initial table. Independent
instruction execution, including branch and return delay slots, agrees with
an independently expressed first-match lookup for every byte input `0..255`:
32 values change to their representative, seven representatives return
themselves, and the remaining 217 unlisted values return unchanged. In
particular, `0xFF` returns `0xFF`; there is no special reset branch. This is a
bounded synthetic execution check, not a gameplay trace or C matching result.
The 256-byte output vector in input order has SHA-256
`43f0f8c1f32a322515e161d51ddd292677c32a496320b4525e6494d9a7225cea`.
A separate synthetic all-zero-count case confirms that empty groups are
skipped and the original byte is returned.

Group membership must not be called character identity or level of detail.
For example, the first group includes Conker, Wise Guy, Uga-Buga, Tediz,
SHC Soldier, villager, zombie and Gregg models. Group five includes models
83 and 165, separately reviewed as Fangy the Raptor and Red Dinosaur. The
model labels come from the existing reviewed model registry; no additional
appearance labels or aliases are proposed here.

## Actor provenance and distinct domains

The sole direct helper call found in the scanned main, game and debugger CPU
images is `1508389C` in `150837D4`, with its delay slot passing the actor.
That caller constructs `800CC2D0 + actorIndex * 0x32C` and stores the supplied
model at actor `+4` at `15083820`. The actor-pool traversals `1504A730` and
`1504ADD0` independently corroborate the pool base, stride and current-actor
root. `1505F188` clears the `0x32C` actor and initializes model `+4` to `0xFF`.

The result is separate from the mutable model byte: `150838B0` stores it at
actor `+6`. The caller masks the returned value to eight bits at `150838A4`
before indexing the resource-count table. The helper does not read or change
immutable actor class, the representation override/control selector at
`+0x1C9`, or the applied representation ordinal at `+0x1C8`. The source-local
partial actor view stays `0x320` bytes and does not acquire the pool's final
12 bytes. No padding is split.

The assignment caller itself has four direct calls in these images:
`1502C950`, `1502FC74`, `15082FA4` and `15083D54`, in automatic representation
selection, explicit override application, actor creation and actor replacement.
Those paths confirm mutable assignment rather than immutable spawn identity.
Searches found no aligned literal address of either `15084D00` or `150837D4`
in the normalized ROM or decompressed game code/data. The seven member-list
addresses each occur once as aligned words in loaded game data, in the reviewed
pointer table. These are bounded static findings; computed aliases, unaligned
encodings, other image interpretations and runtime indirect reachability are
not resolved by these scans.

## Why the result is an animation-resource model index

The animation meaning follows the complete caller and consumer chain:

1. `150837D4` reads unsigned `D_800C5A90[result]` at `150838B8`. Only when it
   is nonzero does it call `1502B020(0, 2, 2, result)` at `150838CC` and store
   the returned archive address at actor `+0x58` at `150838D4`. A zero count
   leaves `+0x58` untouched. The helper itself neither resolves nor loads data.
2. `1502B020` walks two indexed path components from the ROM asset root
   `00AB1950`, through `1502AC88`. Here the path is `[2, result]`: bank 02,
   selected model entry. It returns the resolved ROM/archive address, or zero
   for an absent entry. It is not a bank-0F route-table loader.
3. The animation selector `1505E650` uses the current model byte at `+4` to
   choose a bank-0F route through `D_800D1588`; the route stride is eight bytes.
   It calls `1505E0C4` at `1505E7B4`. In the actor path, `1505E0C4` reads the
   separate model byte at `+6` at `1505E18C` and sets the bank component to two
   at `1505E194`. It obtains the selected segment index from route halfword
   `+0` at `1505E1AC`; route word `+4` instead becomes the event pointer at
   actor `+0x1C4` at `1505E1E8`.
4. If the actor's cached archive address at `+0x58` is nonzero, `1505E0C4`
   passes it, the route segment index and count two to `1502AF04` at
   `1505E3DC`. Otherwise it passes path `[2, actorByte6, routeSegment]` and
   count two to `1502B110` at `1505E404`. That helper resolves the first two
   components and invokes the same `1502AF04` for the final segment.
5. `1502AF04` reads consecutive eight-byte archive table entries and rebases
   their offsets to the bank-entry address. `1505E0C4` stores the second
   entry's address in animation-state `+0x28` and uses the first entry's
   address/length to fetch the descriptor into animation-state `+0x40`
   (`1505E418..1505E47C`). The complete frame-fetch routine `1502D824` then
   uses this `+0x28` base, descriptor byte `+5` as frame stride, animation time
   and descriptor spacing to read the corresponding frame data. These are
   animation descriptor/frame resources.

All seven representative bank-02 entries are present, with valid even-sized
segment tables. Every one of the 32 other group members has an empty bank-02
entry. This independently corroborates the sharing role without claiming a
common character, compatible skeleton for every use, or runtime playback.

The gating `D_800C5A90` count belongs to the separate route system:
`1503D660` resolves bank `0x0F` through the five-group helper `1503D5F0`, and
`1503D484` counts eight-byte routes before the `999` sentinel and stores the
count. `1503D510` propagates route roots/counts within those five groups.
That five-group table at `80084410`/`80098888` is distinct from the seven-group
bank-02 table reviewed here. Calling actor `+0x58` itself a route resource is
imprecise: it caches the bank-02 animation archive address, conditional on a
route-count gate. No field rename or unrelated comment repair is proposed.

The helper performs no model-domain bounds check. Its `0xFF` return must not
be described as making the caller's following indexed accesses safe. The
existing disabled helper's `s32` return and caller's `s8` declaration are
inconsistent source views and remain untouched, along with the caller's
explicit byte mask and store.

## Independent identity and preservation checks

The normalized US ROM is 67,108,864 bytes, SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, SHA-256
`32e6a8b970ec12ac5f782344945aa0c98a193832eefb687529d03bab6948714b`.
Its 2,072,880-byte decompressed game code has SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`; two local extraction
implementations and the complete independent reference binary agree. Its
189,088-byte loaded game data has SHA-1
`42bbe7f02702ca7af5da499fb5cf2f34b7d3d23b`.

Every listed complete registered span was compared against contiguous original
reference words and, where a raw placeholder remains, both raw assembly copies.
Delay slots and all terminal bytes are included. Matched support spans use the
independent original reference, never a candidate compilation. Registration
was read at checkpoint `f440e93689daf8c8425fa70279d0d2a20b3f454b`.

| Symbol | Bytes | Full-span SHA-1 |
| --- | ---: | --- |
| `func_15084D00` | 112 | `ff9dc54618c437070a653923b6cedc81f1484759` |
| `func_150837D4` | 280 | `7bd9c8414be99e3bc26944fe08eb04064933a30d` |
| `func_1502AC88` | 636 | `24f02469c9605e212ed65a4c75b216d50ef8577e` |
| `func_1502AF04` | 284 | `b8f786b34a0b0f6db12c039c68a860a08bd52d1b` |
| `func_1502B020` | 240 | `cf808816ca9e3df778eb77490c317e7eb4b57c02` |
| `func_1502B110` | 276 | `34a60e9d42e7e0e2a914bc3a2f37c13d0aba4f8a` |
| `func_1505E0C4` | 1420 | `3e17bb649f54edb53a448676e71fbea0adce0e10` |
| `func_1505E650` | 380 | `7ff7faebb700286719b32f4b7390b9c9f772236b` |
| `func_1503D438` | 36 | `add9aec5cb5ff6df58ba80704156c1463b4a2071` |
| `func_1503D484` | 140 | `40f757370bbf19e10e675591d24421010455453d` |
| `func_1503D510` | 224 | `fcd02fbf98cbada218432bd315b28508048f85d0` |
| `func_1503D5F0` | 112 | `6b19502694fdcbcee75fc751b4d136adc57685df` |
| `func_1503D660` | 276 | `698addad07c12e755805e484a22441109dd90252` |
| `func_1505F188` | 272 | `c4b6d2297e2dc2c7f3c7c5724781e9042b9d3204` |
| `func_1504A730` | 1696 | `cc2b08465267b571c76efcafa9a65573047775e6` |
| `func_1504ADD0` | 292 | `4af7dbe53fe4c060205be766f8efb2afd7b39701` |
| `func_1502D824` | 764 | `e4854df5924f1d8f104a242c76187da4401a88b2` |
| `func_150627D4` | 44 | `c3fd4d04b4ecfd0f07acb2628b040150aaf7709b` |
| `func_1502C6E8` | 652 | `a168f14ac1b2fe5bb064d8e6194c3b486dc00023` |
| `func_1502FBE8` | 392 | `86363abf6467595cc9d78c3c1b6577bb4374835f` |
| `func_15082A44` | 2152 | `df94e52b3063e063c091fac537096563d3e47620` |
| `func_15083AC8` | 728 | `03be5dc12ab3c26e354c7a830572be800c3b9dc6` |

The complete target span also has SHA-256
`3b3e792efd6c29d299a34033d671ade846af96083c28773f36a40ab1e1006588`.
The seven-byte count table has SHA-256
`d0f0777946a33dcf07ba684c4df647a57f77cfe02c14eb049a3fa476dc2d84a9`.
The pointer table and member ranges were independently bounded and hashed.
The original reference assembly's unrelated `150A9C40..150AA470` interval is
not represented by instruction-word comments; no reviewed span intersects
that gap. Full reference-binary equality is checked separately.

Removing the exact added role comment reconstructs the entire source file
byte-for-byte. All disabled-candidate guards, scores, bodies, end markers and
adjacent raw-assembly pragmas remain byte-identical. This preparation makes no
tracked source changes and runs no compiler, build, matching attempt, queue
operation, commit or publication. It adds one descriptive raw-function role
and no C match. Integration must preserve the existing raw state and must not
send this `CURRENT (1665)` candidate through matching or repair.


## Accepted integration

Independent review approved the exact role comment and full semantic proof.
The two already-matched neighbors `15085410` and `15085420` remain full-span
`CURRENT (0)` with reviewed source-unit layout preserved. A clean nine-function
verification batch, full US ROM, integrated game/data/rodata, progress and
whitespace gates passed. Host and pinned ROM-aware suites each passed 1,764
tests (37 host skips; one optional pinned validator skip). All 49 ELF symbol
records and every allocated section of the source object are identical; only
nonallocated `.mdebug` differs. The raw helper remains disabled at its existing
`CURRENT (1665)` score. This adds one descriptive raw-function role, zero C
matches, zero matched bytes and no source-unit progress.
