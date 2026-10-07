# Library track

Nintendo 64 library code builds from `lib/`, separately from Conker-specific
`src/` code. US is the active target; EU/PAL mapping remains future work.

## Current US boundary status

| Area | Audited bytes | Exact CPU library text | Reviewed source units | Known data/padding | Classified | Unresolved |
| --- | ---: | ---: | ---: | ---: | ---: | ---: |
| Main CPU `0x1050:0x290D0` | 163,968 | 98,512 | 64,112 | 64 | 162,688 (99.2194%) | 1,280 (0.7806%) |
| Game overlay `0x0:0x1FA130` | 2,072,880 | 48,720 | 2,022,064 | 2,096 | 2,072,880 (100%) | 0 |

**Boundary ownership is separate from matching C.** Main has 28 reviewed
working units; the game overlay has 714. These are evidence-backed working
families, not a claim that every original filename or compilation unit has
been recovered. ASM-backed members can have reviewed ownership without a C
implementation. See generated [implementation progress](progress.md) for matches.

- **Main:** reviewed source units plus exact library text cover 162,624 bytes
  (99.1803% of the audited CPU interval). Separately classifying the 64-byte
  zero tail brings classification to 99.2194%; it earns no function credit.
  Main source units remain canonically raw because mixed main C/ASM integration
  is not supported. Verified original assembly is excluded from C matches.
  See the [main boundary review](evidence/boundaries/main/main_boundary_residual_frontier.md).
- **Game:** all bytes have source or section ownership, including 38 library
  text placements and 2,096 bytes of text-resident data. There are no raw
  `asm`/`hasm` subsegments, although reviewed units still contain assembly.
  See the [mapping completion record](evidence/boundaries/game/mapping/game_mapping_residual_frontier.md).

Percentages above use each row's audited byte total. The 80-byte main entry at
`0x1000:0x1050` and all RSP payloads are outside this table. Generated progress
retains its existing 164,512-byte main denominator, which extends to `0x292F0`
and includes 544 RSP bytes; the game denominator includes its text-resident
data. Do not compare those implementation percentages directly with this
boundary classification or silently change their calculation.

### Remaining main ownership

| US ROM range | Bytes | Unresolved question |
| --- | ---: | --- |
| `0x38C0:0x38E0` | 32 | Ownership of an empty varargs-style stub |
| `0x39B0:0x39C0` | 16 | Ambiguous no-op return; no proven SDK identity |
| `0x50A0:0x5570` | 1,232 | Five retained raw spans versus six index proposals, including the unselected `0x5298` entry |

The owned [beta comparison](evidence/boundaries/main/main_boundary_beta_comparison.md) resolves
the complete 64-byte hardware-init/probe family at `0x38E0:0x3920`.
The three remaining ranges need new positive ownership or entry evidence.
Repeating the completed bounded static scans, guessing object names or shortening spans for
matching credit would not resolve them. Required evidence and entry conflicts
are recorded in the [residual review](evidence/boundaries/main/main_boundary_residual_frontier.md#remaining-exact-ranges).

## Library integration

- **Stock SDK:** the pinned [`lib/ultralib`](../lib/ultralib) submodule from
  DevOldSchool/ultralib supplies the mapped 2.0G objects through
  `libultra_2_0G` and the three required debug-audio objects through
  `libultra_2_0G_d`. See the [G reclassification evidence](evidence/libraries/libultra_2_0G_rare_reclassification.md).
- **Rare/Conker:** [`lib/libultrare`](../lib/libultrare) holds the bounded Rare
  snapshot and reviewed audio, formatting, EEPROM, math and MP3 variants.
  Complete object checksums are verified before staging. Main and game maps
  together contain **147,232 exact CPU library text bytes**, counting each
  placement once; these bytes are already included in the table above.
- **RSP:** four separately verified payloads contain 6,656 code bytes and 2,896
  initialized-data bytes, outside CPU matching. See the
  [RSP boundaries](evidence/libraries/libultra_us_vi_rsp_boundaries.md) and
  [reproduced toolchain and ROM proof](evidence/boundaries/main/main_original_assembly_verification.md).

Canonical mappings live in [`config/profiles/us.yaml`](../config/profiles/us.yaml)
and [`config/game/us.yaml`](../config/game/us.yaml), with game non-text bindings
in [`config/game/us-sdk.ld`](../config/game/us-sdk.ld). Independent comparison
maps retain raw assembly. The linked evidence records byte-identical full US
ROM and game-overlay builds; object resemblance alone is not acceptance.

The former `powf` candidate is superseded by the matched power helper in
[`game_778B0.c`](../src/done/game/game_778B0.c). Original external workspace
ownership remains under research. See the [library residual audit](evidence/libraries/libultra_us_residual_boundary_audit.md)
and [workspace review](evidence/libraries/libultrare_us_workspace_bounds.md).

## Contributor commands

Run from the repository root after [setup](../CONTRIBUTING.md#setup):

```sh
./conker libultra --version G   # Build stock G research archives
./conker libultrare            # Build Rare/Conker objects and check hashes
./conker rsp                   # Assemble and verify RSP payloads
./conker _prepare-reference --profile us
./conker build --profile us    # Verify the complete main ROM
./conker game-build            # Verify the complete game overlay
```

`./conker libultra --version I` (or `J`, `K`, `L`) builds alternative research
archives. After building the I-L normal/debug/ROM targets, use
`./conker library-audit` for the documented stock-template residual scan.

Promote a candidate into an archive only after reviewing its complete object
boundary, non-text ownership, symbols and relocations, and passing the
byte-identical full-image checks. Preserve the independent raw comparison
range. Follow [the contribution rules](../CONTRIBUTING.md#review-and-handoff)
and [workflow reference](decompilation-workflow.md) for registration and integration.
