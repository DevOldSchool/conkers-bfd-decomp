# US main system-wrapper working boundaries

Evidence kind: `structural_analysis`. Ten working source units cover fourteen
entries and 3,616 bytes. These offset-derived names do not claim recovered
historical filenames. All implementations and both canonical/raw maps remain
unchanged assembly; registration adds reviewed membership and source skeletons.
No matching-C or archive implementation credit is claimed.

## Independent inputs and checks

- Owned US ROM SHA-1: `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
- Decompressed game-code SHA-1: `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
- Separately generated main raw assembly: `reference/us/asm/`.
- Independent unsplit CPU index: spimdisasm 1.33.0, IDO mode, entire
  `0x1050:0x290D0` CPU range; no map splits or supplied function symbols.
- Legacy grouping corroboration: [mkst/conker at
  3adf229175c037c771f251f169f9dd80ca306924](https://github.com/mkst/conker/blob/3adf229175c037c771f251f169f9dd80ca306924/conker/conker.us.yaml).
  This is corroboration, not independent proof of original object ownership.

Every listed instruction word equals the owned ROM. Raw-assembly membership
and the unsplit index agree on every start and complete span, including final
alignment words; members exactly cover each interval. All outer endpoints are
16-byte aligned. Decoding conditional branches over all main CPU words finds
no branch crossing any proposed endpoint in either direction. Direct-call
checks cover both the complete main CPU range and decompressed game code,
normalizing the main runtime address alias. Dynamic entry selections are
reviewed explicitly below; absence of a direct call alone is not a rejection.
These checks establish bounded working units, not original data/BSS ownership.

## Accepted complete memberships

| Working source | US ROM range | Complete entry starts | Bytes | Range SHA-1 |
| --- | --- | --- | ---: | --- |
| `src/main/init_2DB0.c` | `0x2DB0:0x2E50` | `func_80002DB0` | 160 | `a51aea37a3500a8d828efba17515c35448578b72` |
| `src/main/init_2E50.c` | `0x2E50:0x30A0` | `func_80002E50` | 592 | `af1230ec9aca968871852af33c38df0436e3665a` |
| `src/main/init_30A0.c` | `0x30A0:0x3220` | `func_800030A0` | 384 | `d19c5caf542b11b74d3f9419f8c6e2371ecc3bdc` |
| `src/main/init_3220.c` | `0x3220:0x34E0` | `func_80003220`, `func_80003330`, `func_8000349C` | 704 | `2d3613323588ad83f329fb0648df4de61303d51c` |
| `src/main/init_34E0.c` | `0x34E0:0x37F0` | `func_800034E0`, `func_80003658` | 784 | `6dcbd6357a68a1997e878debaca752a1b7daf2fb` |
| `src/main/init_37F0.c` | `0x37F0:0x38C0` | `func_800037F0` | 208 | `bb236528bcf8c2e82c54c6d71f30c754fab26191` |
| `src/main/init_3920.c` | `0x3920:0x3930` | `func_80003920` | 16 | `f3fe959b6f4c545d9512a7392df704d95e801a96` |
| `src/main/init_3930.c` | `0x3930:0x39B0` | `func_80003930` | 128 | `3708d86739fae9d6f2d94b8a0d2223e8a479a59b` |
| `src/main/init_39C0.c` | `0x39C0:0x3BD0` | `func_800039C0`, `func_80003ACC` | 528 | `efe749bd80649d348a4a72e30e0f111749586676` |
| `src/main/init_3BD0.c` | `0x3BD0:0x3C40` | `func_80003BD0` | 112 | `3e6cbb76c16359ccec3910b6a5eb993a6e9322ac` |

## Why these memberships are complete

- `0x2DB0:0x2E50`: one audio-buffer submission routine, directly called at main
  `0x95FC`. Its preceding endpoint is anchored by the independently reconstructed
  `xprintf` object. AI register writes and two SDK calls corroborate the legacy
  `aisetnextbuf` lineage, without asserting an exact stock archive match.
- `0x2E50:0x30A0`: one queue-processing thread routine. Main
  `0x3194:0x31B4` constructs `0x10002E50`, passed as the entry argument to the
  thread constructor at `0x31C8`. The seven-entry switch table at ROM
  `0x2C080:0x2C09C` selects labels within this routine; it adds no function entry
  or data-ownership claim.
- `0x30A0:0x3220`: one manager initializer, directly called at `0x4498`.
  It constructs the preceding thread entry but has a distinct complete indexed
  span and the same separate working boundary in the legacy map.
- `0x3220:0x34E0`: the complete three-entry task preparation/load/start family.
  `0x3330` calls the local preparation helper at `0x334C`. External scheduling
  paths pair calls to `0x3330` and `0x349C`, for example at `0x4C14/0x4C20`
  and `0x4F20/0x4F30`; the last member starts the same SP task after waiting
  for the SP interface. The legacy map independently groups all three under
  its task source. This is stronger than mere adjacency or shared SDK calls.
- `0x34E0:0x37F0`: a manager initializer and its owned thread entry. The first
  is directly called at `0x1284`; it constructs the `0x10003658` entry at
  `0x35D0:0x35F4` and passes it to the thread constructor at `0x3604`.
  The complete two-entry membership agrees with the legacy manager grouping.
- `0x37F0:0x38C0`: one thread constructor, externally called from seven main
  locations including `0x10D4`, `0x31C8` and `0x3604`. It has a complete
  independently indexed span and a distinct following varargs-style stub.
- `0x3920:0x3930` and `0x3930:0x39B0`: separate complete singleton spans,
  called in sequence at bootstrap `0x121C` and `0x1224`. The first clears
  `0x80038080`; the second reads that flag to select workspace limits.
  Existing aligned endpoints and legacy singleton placement are retained.
- `0x39C0:0x3BD0`: a framebuffer initializer and its local filling helper.
  The initializer is called at `0x5138`, calls the helper at `0x3A54`, and
  both use the same framebuffer/size state. The helper also has game callers
  at overlay offsets `0x7CEC` and `0x7D08`. Both complete indexed members
  agree with the legacy grouping.
- `0x3BD0:0x3C40`: one heap-state initializer, directly called at `0x122C`.
  It initializes the linked record and allocator globals; the following range
  begins the allocation operations. Its exact singleton span is independently
  indexed and separately placed in the legacy map.

## Withheld ranges

- `0x38C0:0x38E0`: a 32-byte varargs-style stub. No direct caller was found;
  shape, alignment and its legacy filename alone do not establish ownership.
- `0x38E0:0x3920`: two indexed entries at `0x38E0` and `0x390C`, neither
  directly called in the scanned CPU images. There is no reviewed relationship
  connecting the hardware-writing routine to its adjacent zero-return entry.
- `0x39B0:0x39C0`: an ambiguous no-op return. The earlier
  [library audit](libultra_us_residual_boundary_audit.md) also rejected assigning
  `ackramromread` or `ackramromwrite` solely from this common template.

At this checkpoint these 112 bytes remained unreviewed. The subsequent
[owned beta comparison](main_boundary_beta_comparison.md) supplies positive
structural-family evidence for the complete 64-byte hardware pair, now reviewed;
the other 48 bytes remain unresolved. The bounded negative call scan is not proof
that they are unreachable, and no original source or library identity is assigned.

## Reproduction and integration limits

Generate the independent unsplit index with the pinned toolchain:

```sh
mkdir -p build/main-boundary-review
python3 -m spimdisasm.singleFileDisasm roms/baserom.us.z64 \
  build/main-boundary-review/main.s --start 0x1050 --end 0x290D0 \
  --vram 0x80001050 --function-info build/main-boundary-review/functions.csv \
  --compiler IDO --no-libultra-syms --no-hardware-regs --no-ique-syms --quiet
```

Register each table row with its exact listed bounds using
`./conker register-source-unit --overlay main --register-members`, the listed
source, `--evidence-kind structural_analysis`, and this document as
`--evidence-reference`. The transaction derives members from the independent
raw assembly and preserves all existing matches. Review the complete membership
before replaying registration onto a branch with other changes.

Main mixed C/ASM integration is not supported. These units remain `raw_asm`
until every member independently matches and the supported complete-unit
integration passes. Neither canonical main map nor raw reference map changes.
The present checkpoint validates metadata, generated progress and whitespace;
it does not claim a new full-main or game-overlay build. The cloud CPU toolchain
currently lacks the RSP extension required for the complete main build.

Validation at this checkpoint: all 75 project-state tests and 13 segment-map
tests pass; generated progress is current and whitespace checks pass.
