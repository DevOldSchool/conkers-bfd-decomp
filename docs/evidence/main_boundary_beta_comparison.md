# Main boundary frontier: owned beta comparison

The 2026-10-01 comparison resolves **64 US bytes** as one reviewed
hardware-initialization/probe working family. Main now has 28 reviewed working
units, 229 registered spans and 64,112 reviewed source bytes. The remaining
frontier is **three ranges, 1,280 bytes**. No original filename, historical
object map, matching C, or beta-to-US byte match is claimed.

The two complete US members are retained, including their alignment words:

| Working source | US ROM range | Complete members | Bytes | Range SHA-1 |
| --- | --- | --- | ---: | --- |
| `src/main/init_38E0.c` | `0x38E0:0x3920` | `func_800038E0` (44), `func_8000390C` (20) | 64 | `272c3aa69a716245585148db44b6f5b5e7165ab8` |

Evidence kind: `structural_analysis`. This is the same deliberately limited
working-family standard used by the existing main reviews, not recovery of an
original compilation unit. The beta correlations supply new selected-entry and
hardware-domain evidence; independent US raw/index/span checks establish the
retained US membership. Neither canonical nor independent reference map changes.

## Independently validated inputs

Each owned beta input is 67,108,864 bytes and uses V64 byte order. The
independently computed SHA-1s below identify ROM content before and after
normalization to Z64 byte order. Neither ROM nor extracted payload is committed.

| Input | Raw SHA-1 | Normalized Z64 SHA-1 |
| --- | --- | --- |
| `baserom.us.beta.v64` (debug) | `6956bd77351a91cdd22af454a8d410a3b9c829f0` | `3b99222ee76f6277a963142cd807b3df25d5174f` |
| `baserom.us.beta.ects.v64` | `92575eed941324b9cd7d29df61e720b04d8b26cb` | `06597dc935651f8995bfacc30fde6e621d44c3e1` |

Both normalized hashes match `config/rzip_layouts.json`. US and PAL hashes
remain those in [the regional comparison](main_boundary_pal_comparison.md).
The existing `load_game_image`/RZIP helpers decode debug and the loader-proven
[raw ECTS layout](ects_game_layout.md), rather than guessing archive signatures.

| Decoded input | Bytes | SHA-1 |
| --- | ---: | --- |
| Debug game code | 2,145,856 | `a1c41378211a6e50c60fd16ffeccedb3909d7bf1` |
| Debug game data | 193,568 | `3f08585ea52db330fcb2e60084bd7cfe584d4d4d` |
| ECTS game code | 2,023,664 | `b4f9b6d9e4f93b85fbecbf3e68fc416c7b1d3b4a` |
| ECTS game data | 188,208 | `df1e5e1e03b607581c1b0da030df521400b3363a` |

The complete 208-byte US RSP boot payload occurs exactly once in each beta,
at debug `0xA4E0` and ECTS `0x9DB0`. CPU decoding stops before those payloads.
Conservative literal-pointer checks also cover the initialized main-image tail
through the boot-cleared BSS start: debug `0xA4E0:0xD2B0` and ECTS
`0x9DB0:0xCAF0`. These tail windows include RSP payloads and initialized data;
they are not described as CPU instructions or assigned to any source object.
The BSS starts are independently constructed by each ROM's entry code.

## Accepted hardware working family

| Member or neighbor | US | Debug | ECTS |
| --- | --- | --- | --- |
| Preceding varargs stub | `38C0:38E0` | `37D0:37F0` | `35D0:35F0` |
| Hardware initializer | `38E0:390C` | `37F0:381C` | `35F0:361C` |
| Inferred probe counterpart | `390C:3920` | `381C:38F0` | `361C:36B0` |
| Following memory-flag initializer | `3920:3930` | `38F0:3940` | `36B0:36F0` |
| Following memory-range setup | `3930:39B0` | `3940:39C0` | `36F0:3770` |

The initializer is 44 bytes in all builds, with the same operations except
relocated RAM-global operands. It forms `0xBC000C02`, records that pointer and
an adjacent `0x4040` halfword, writes `0x4040` to the hardware address, and
returns. Its recorded globals are US `0x80038070/4`, debug `0x80017ED0/4` and
ECTS `0x80013EC0/4`.

Both betas select both members independently:

| Build | Main initializer caller | Game probe caller | Game target alias |
| --- | --- | --- | --- |
| Debug | `0x80001070` → `0x800037F0` | `0x15007A44` | `0x1000381C` |
| ECTS | `0x80001070` → `0x800035F0` | `0x15006A74` | `0x1000361C` |

The initializer is selected during startup. Each game caller tests the probe's
return and skips an infinite self-branch only when it is zero. These two beta
members are also the **only** `LUI 0xBC00` constructions in each complete main
CPU plus game-code image. The expanded probes form `0xBC000000` and contain
halfword-signature comparisons/loads at that base and `+2`. This supplies a
specific initialization/probe relationship within the same hardware block,
beyond simple adjacency or unrelated uses of a common SDK call.

There are important limits. The probe does not consume the initializer's RAM
globals, and neither member calls the other. Both owned beta probes force the
result to zero: ECTS's initial halfword reads are overwritten; debug has NOPs
at those read positions; later alternative-signature paths are skipped under
the forced value. Thus the report does not assert active hardware detection.
US `0x390C` itself has no hardware access. Its compact-probe identity is an
inference from the invariant `+0x2C` position, corresponding selected beta
bodies and distinct flanking memory functions, consistent with its zero return.
The full US range remains a reviewed working family, with historical object,
filename and non-text ownership unclaimed.

Independent unsplit spimdisasm 1.33.0 IDO analyses, without supplied symbols,
recover US starts `0x38E0` and `0x390C` with lengths `0x2C` and `0x14`.
Fresh split raw assembly agrees and its 64 instruction bytes equal the ROM.
The complete tails stay included. No conditional main branch crosses the US
outer endpoints. Whole-pair beta checks found only the two expected direct
selections, no extra direct/interior or external relative-branch entry, and no
initialized-data pointer to the pair's interior. As always, these bounded
checks do not rule out computed or encoded selectors.

Registration uses the existing aligned enclosing map range, without inventing
a source boundary at the unaligned `0x390C`:

```sh
./conker register-source-unit --overlay main --source src/main/init_38E0.c \
  --register-members --us-start 0x38E0 --us-end 0x3920 \
  --evidence-kind structural_analysis \
  --evidence-reference docs/evidence/main_boundary_beta_comparison.md
```

## What remains unresolved

- **`0x38C0:0x38E0`, 32 bytes.** The varargs stub is byte-identical and unique
  at debug `0x37D0` and ECTS `0x35D0`. Neither beta adds a direct/relative
  selector, literal pointer or matching ADDI/ADDIU/ORI low half. Repeated
  placement and empty shape still do not establish ownership.
- **`0x39B0:0x39C0`, 16 bytes.** Neither corresponding beta neighborhood has
  an extra empty body. Debug `0x39B0` and ECTS `0x3760` are ordinary epilogues
  inside the preceding memory-range routine, not counterparts of the separate
  US stub. Exact matching of this common return/padding template would be a
  false correspondence. A moved counterpart elsewhere remains possible.
- **`0x50A0:0x5570`, 1,232 bytes.** Three scheduler APIs have selected beta
  counterparts, but the pre-NMI initializer/thread and extra `0x5298` return
  have no established complete beta counterpart. The five raw spans versus
  six index proposals remain unreconciled. No US span is shortened.

The scheduler correspondence demonstrates why main-only beta matching is
insufficient:

| US main start | Debug game start (caller) | ECTS game start (caller) |
| --- | --- | --- |
| `0x50A0` | `0x150171A0` (`0x1500791C`) | `0x150152A0` (`0x1500694C`) |
| `0x51C8` | `0x150172E0` (`0x15108854`) | `0x150153C8` (`0x150F51EC`) |
| `0x51E8` | `0x15017300` (`0x15007A68`) | `0x150153E8` (`0x15006A98`) |

The beta initializers preserve the queue initialization, linked-list head,
completion message and thread-ID-20 relationships, while adding/changing
operations. The two following API bodies preserve their instruction structure
apart from address operands. Debug's three-entry range ends at `0x17330`;
ECTS's ends at `0x15420`, including its final alignment. Neither is followed by
the retail pre-NMI family. The beta initializers already install event 14 with
message 5 on their scheduler queue; retail installs it separately in `0x5218`.
This explains changed organization but supplies no selector for the disputed
retail empty return. Similar epilogues elsewhere are not enough to pair it.

## Reproduction and verification

Place the owned inputs at the canonical ignored paths in `roms/`, then run:

```sh
mkdir -p build
python3 scripts/audit_main_beta_frontier.py > build/main-beta-frontier.json
python3 -m unittest tests.test_main_beta_frontier -v
```

The read-only helper revalidates all four ROMs, decodes the game inputs, verifies
the CPU/BSS bounds, and emits hashes plus direct selections, aligned literal
pointers, low-half candidates, whole-pair entry/branch checks and BC00-construction
coordinates. It emits no
ROM words, registrations or progress state. A low-half candidate is not a
reaching-definition proof: the debug probe's extra candidate `0x151BE0F4`
resolves to unrelated `0x8008381C` via its LUI at `0x151BE0EC`.

For independent function indexing, extract only the CPU window above and use
spimdisasm 1.33.0 with `--vram 0x80001050 --compiler IDO --no-libultra-syms
--no-hardware-regs --no-ique-syms --function-info <csv>`. CSV VROM offsets are
relative to the extracted `0x1050` origin. Regenerate the split US reference
through `./conker _prepare-reference --profile us`; never reuse a C-generated
object as boundary or matching evidence.

Final local validation after registration:

- The complete US ROM was rebuilt through `./conker build --profile us`,
  including all four matching RSP payloads. Rebuilt SHA-1 is
  `4cbadd3c4e0729dec46af64ad018050eada4f47a`; byte comparison with the owned
  ROM also passes.
- All 1,081 Python tests pass with 12 declared skips, including ten new
  ROM-free scanner tests. Metadata validation, generated-progress consistency,
  shell syntax and whitespace gates pass.
- Both newly registered members remain `raw_asm`. Main matched-C counts and
  byte totals, existing original-assembly proofs, and all game records are
  unchanged. There is no pending matching batch and no mixed main integration.
- Only evidence, its read-only reproducer/tests, the transactional raw skeleton
  and inventory/progress outputs change. Private ROMs, raw disassembly,
  decoded binaries, research output and build artifacts remain ignored.
