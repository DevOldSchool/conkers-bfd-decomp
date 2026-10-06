# Actor animation-model representative

`func_15084D00` has descriptive role `actor_get_animation_model_representative`.
The 112-byte helper remains raw with its unchanged disabled `CURRENT (1665)`
candidate. [Shared provenance](model_name_confidence_review.md) records the
full original-ROM support spans; this is a resource-sharing role, not character
identity or LOD evidence.

## Animation-model representative: exact selection

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
model labels come from the existing source-bound model registry; no additional
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

The representative helper is `func_15084D00`, 112 bytes, role
`actor_get_animation_model_representative`. Its comment leaves the disabled
`CURRENT (1665)` candidate intact. Decompressed game-code SHA-1 is
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5` (2,072,880 bytes); loaded game-data
SHA-1 is `42bbe7f02702ca7af5da499fb5cf2f34b7d3d23b` (189,088 bytes).
The seven-byte count-table SHA-256 is
`d0f0777946a33dcf07ba684c4df647a57f77cfe02c14eb049a3fa476dc2d84a9`.
