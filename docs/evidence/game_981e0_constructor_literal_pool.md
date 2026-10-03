# Constructor literal pool in game_981E0

The source-valid `func_1506F1A8` and `func_1506F54C` constructors have registered
US text spans of 892 and 884 bytes, respectively:
`[0x1506F1A8,0x1506F524)` and `[0x1506F54C,0x1506F8C0)`.
Their natural floating literals contribute 30 and 29 four-byte constants to one
input section. The existing INFO mapping in `config/game/us-rodata.ld` recreates
their original addresses without appending bytes to the game code image.

## Descriptor and signed-byte contracts

Both constructors pass a complete `Game981E0FlameDescriptor`, extent `0x11C`,
to the unchanged four-word provider `func_151994B8`. Its finite copies establish
the input representation: `[+004,+050)`, `[+058,+09C)`, `[+09C,+0E0)`, and
`[+0E0,+11C)`, including the final halfwords. The internal gaps remain uninitialized
and unchanged. The complete type and provider prototype are visible before
`func_1506F1A8`; function-definition order and the provider ABI are unchanged.

Each callback receives one full word through `func_15071D38` and
`D_80086150`; the ROM table entry at `0x80086174` names `func_1506F1A8`.
Its unused argument therefore remains `s32`. Each constructor requests 15 records.
The provider and allocator establish a `0x450`-byte owner allocation, a state
pointer at owner `+0x98`, and `0x158` bytes of state storage at owner `+0xA0`.
The constructor's input object is distinct from this transformed state.

Only descriptor bytes `+038` and `+03A` change from `u8` to `s8` in this recovery.
This follows actual signed sentinel/index consumers, independently of compiler
score:

- Provider `15199514..1519954C` copies input `+004` to local `sp+06C`.
  Thus input `+038` reaches `sp+0A0`. At `151997A0` the provider loads this
  byte with `lb`, compares it with `-1`, and skips the indexed callback through
  `D_8008F8A4` for that sentinel
- Input `+03A` reaches `sp+0A2`. Provider `15199754..15199764` copies
  `0x154` bytes from `sp+06C` into the state pointer loaded from owner `+98`;
  the byte becomes state `+36`. The accepted 144-byte `func_15199980` loads
  that state pointer at `15199988`, uses `lb` at `151999C0`, and compares
  with `-1` at `151999C4..151999CC`. The sentinel skips the callback indexed
  through `D_8008F8B4`. The accepted `CharacterFlamethrowerState.unk36`
  declaration is already `s8`

Provider, allocator and consumer instruction spans were independently checked
against the checksum-validated ROM. Ordinary `-1` assignments express these
protocol values. No other descriptor types, extents, caller signatures, storage,
or accepted function bodies change. In particular, `+03E` remains unsigned.

## ROM and current complete-object evidence

The normalized US ROM has SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`; its decompressed game code is
2,072,880 bytes, SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
Game data has SHA-1 `42bbe7f02702ca7af5da499fb5cf2f34b7d3d23b` and starts
at `0x80082B20`. The existing extractor verifies the ROM checksum first.

The complete source object emits exactly one `.rodata` input section, size
`0xF0`, alignment 16. Its first `0xEC` bytes equal ROM
`[0x80099DAC,0x80099E98)` exactly, with no gap or deduplicated address:

- `func_1506F1A8`: 120 bytes, `[0x80099DAC,0x80099E24)`, SHA-256
  `b19c6340402e3581fc4928b57483f991392d43a96cb87f235b29892316ab3d20`
- `func_1506F54C`: 116 unchanged bytes, `[0x80099E24,0x80099E98)`, SHA-256
  `f98ce2c7f9f3b7115d7451a1a605c61f723c56c41c0fbbbdb3a9fd80f47ae1a2`
- Combined payload SHA-256:
  `62409fa04043ffb56800a5a68b73330c9ae3835a3c87011f839d48a6db047d9a`

The final four compiler-alignment bytes are zero. All 118 incoming relocations
are 59 MIPS HI16/LO16 pairs, owned only by these constructors (30 and 29 pairs).
Their addends are exactly `0,4,...,0xE8`; every independently decoded original
address equals `0x80099DAC + addend`. No relocation targets the zero tail and
there are no relocations in the pool. All 329 registered member starts and the
`0xA6D0` text extent remain unchanged. Registered spans, including their tails,
remain authoritative even when ELF symbol annotations are shorter.

## Padding and neighboring ownership

The unchanged whole-input selector is `*game_981E0.o(.rodata)`. The mapping uses
base `0x80099DAC`, `SUBALIGN(4)`, exact section assertion `0xF0`, and the explicit
absolute payload symbol and assertion `0xEC`. Its non-ALLOC INFO extent ends
at `0x80099E9C`, while owned payload ends at `0x80099E98`.

The four informational zero-tail bytes do not own or replace the independently
referenced ROM constant at `0x80099E98`. The original game-data archive supplies
runtime data. These five real neighboring constants remain external:

- `0x80099E98`: `4424C000`, used by `func_1506F8F0`
- `0x80099E9C`: `C42A4000`, used by `func_1506FA90`
- `0x80099EA0`: `43AC8000`, used by `func_1506FD30`
- `0x80099EA4`: `4020C49C`, used by `func_15070300`
- `0x80099EA8`: `4065C290`, used by `func_15070300`

All 46 other explicit game/SDK mapping intervals are disjoint from both the
payload and the full 240-byte informational extent. This remains an explicit
ownership audit: the production verifier has no generic cross-section overlap
guard. No historical whole-file rodata boundary, unobserved array capacity, or
absence of every possible computed alias is inferred. The separate constructor
at `func_15070898` is not included in this recovery.

## Historical F54C-only recovery

The earlier accepted F54C-only mapping at `0x80099E24` verified payload `0x74`
(116 bytes) in section `0x80` (128 bytes), with 12 excluded zero-tail bytes.
That proof and the unchanged 116-byte subpayload remain valid historical
evidence; the current combined 236/240/4 geometry supersedes that mapping.
The original unmapped natural-literal candidate reached focused zero but
failed image placement, appending 128 bytes with the pool at `0x151FA130`.
The alternative explicit-external-scalar form reached CURRENT 1162 and was
preserved separately. Neither failed outcome was relabeled as accepted when
the original mapping recovery passed. Their source/object and failure records
remain distinct from this later sibling trial.

## Verification and bounded history

The initial unchanged-type trial reached CURRENT 10: only two immediates
materially differed, `0xFF` instead of `-1`, at `1506F3A4` and `1506F3AC`.
Its source, objects and failure records remain separate. The original mapping
correctly rejected that enlarged section. One semantic type revision and the
separately reviewed exact mapping expansion reached full-span CURRENT 0 and
preserved layout. The accepted 884-byte `func_1506F54C` and 572-byte
`func_15070D24` independently retain CURRENT 0.

The normal game build verifies all 236 linked payload bytes against ROM and the
four excluded alignment bytes as zero. The actual linked ELF contains one
non-ALLOC section at the required address and one absolute payload symbol equal
to 236. The complete game image equals the ROM-derived image. Every one of the
275 previously accepted same-unit registered spans remains byte-identical, as
does the new 892-byte span. The 275 prior source bodies are unchanged.

Separate ignored linker fixtures reject missing object selection, removed
`SUBALIGN`, changed payload assertion, shortened/grown section and doubled input.
The unchanged verifier rejects wrong base, missing/wrong payload symbol, changed
payload byte and nonzero alignment. Exact positive links pass before and after
these 11 negatives. Explicit overlap tests reject 141 conflicting cases and
accept 92 exact-boundary cases. Production configuration is unchanged during
these fixtures. The full US ROM and all four RSP payloads verify exactly.
The clean 276-member same-unit batch completes with `BATCH_COMPLETE`, including
1,655 tests (23 skipped), metadata, progress and whitespace checks. These gates
remain required on replay; focused zero alone grants no acceptance.

No compiler, linker implementation, verifier, comparator, Makefile, shared header,
assembly, or source-unit boundary mechanism is changed.
