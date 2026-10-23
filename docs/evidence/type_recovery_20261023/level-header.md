# D_800B0DF0 level-header investigation (US, 2026-10-23)

Both evidence-backed type trials were **score-neutral and fully reverted**.
No C, header, assembly or inventory change is retained. This continuation fixes
no lead and claims **zero score reduction and zero new matches**. The commit
records the rejected proposals so later passes do not repeat them.

Baseline commit: `ada3727be41ccb7492f5d0617103384bc1803bef`.
Baseline: [sdk-gfx-16ee20-final.tsv](sdk-gfx-16ee20-final.tsv), SHA-256
`96ff868459831b1849228a61b9ebf564cd7906f01838ea29f64170756e40af5f`.
Every comparison uses measured `new` values, not saved CURRENT annotations.
The direct D_800B0DF0 cohort is **13 candidates / 43,380 points**.

| Trial | Files | Candidates rescored | Score sum before -> after | Decision |
| --- | ---: | ---: | ---: | --- |
| Shared matched-backed header prefix | 4 | 8 | 21,666 -> 21,666 | Rejected: no reduction |
| Signed transition-settings contract | 2 | 4 | 14,518 -> 14,518 | Rejected: no reduction |
| Restored full deferred population | 452 | 1,383 rows / 1,335 scores | 2,791,612 -> 2,791,612 | Unchanged |

The two trial cohorts overlap. All trial candidates compile; every measured
score and frame is unchanged. No new zero appears. The final sweep retains
48 existing compiler errors and the same four pre-existing zeros. Its 1,383
isolated compiles took 128.9 scorer seconds, excluding research and delivery.
The PR remains at **3,367 points reduced and one earlier match**; the earlier
353-point restored-coverage addition still receives no reduction credit.
[Trial rows](level-header-trials.tsv), [full final sweep](level-header-final.tsv).

## Evidence and rejected proposals

The fresh declaration report finds 25 declarations across 25 files, with 12
pointer variants. It classifies the root as a **pointee-size disagreement,
ABI risk false**: these are differently sized partial views, not a demonstrated
pointer/integer ABI conflict. No full allocation size or array stride is proved.

The first trial adopted a conservative prefix in `game_2D540.c`,
`game_32740.c`, `game_1AB530.c` and `game_1A0790.c`. It used only fields backed
by matched readers: header values 00/02, RGB bytes 05..07, position-table index
10, signed halfwords 3A/3C/3E/40, bytes 42..45 and signed selector 46.
Matched `151732E0` reads 00/02 with `lhu` at `1517337C`/`15173384` and selector
46 with `lb` at `1517338C`. Transition fallback reads retained explicit signed
conversions. No control flow, local lifetime or statement order was changed.
[Reproducible rejected patch](level-header-prefix-rejected.patch). Both saved
patches pass `git apply --check` against the restored baseline.

Several tempting promotions lack the needed matched-reader evidence: count18,
capacity1C, flags21, palette29, resource2B and assetList4B remain supported only
by deferred/raw readers. Callback fields 0A..0F are byte indices into external
tables, not function pointers. Private members called `mode` refer to different
offsets (08 versus14), so matching names do not establish matching roles.
The additional deferred consumer of matched-backed field0x3E in
`game_58F80.c` was excluded from
adoption because that file has unrelated candidate compiler failures. The
broader 83300 and 49D30 cohorts also contain existing compile failures.

The second trial addressed a concrete adjacent signedness disagreement.
`game_1A0790.c` declares D_800DD2F2/F4 and preset fields C/E unsigned, although
matched `1510B070` in `game_138520.c` reads the globals with `lh` and signed
`cvt.s.w` (`1510B090`, `1510B098`, `1510B0A8`, `1510B0B8`). Raw `151733E4`
also uses signed preset reads at `1517377C`, `151737C0`, `1517381C`,
`15173844`, checks -1, and stores halfwords at `15173804`/`15173890`.

That trial shared the two signed global declarations and a preset type with
signed C/E members, changing their output pointers accordingly. It retained
all explicit conversions, including deliberate unsigned interpolation of
fields4/6/8/A, and preserved the constructor's unsigned header bit copies.
It also produced no gain. [Reproducible rejected patch](level-header-signed-rejected.patch).
No further statement reshaping or permutation followed these neutral results.

## Validation scope

The score-reduction gate rejected both proposals before acceptance. Every
trial source was restored byte-for-byte to the baseline, both temporary headers
were removed, and tracked code/inventory had no differences. The fresh full
sweep confirms identical score, frame and error populations.

No new matched rechecks or clean batch are claimed for this evidence-only
commit. The prior **BATCH_COMPLETE at ada3727b** remains applicable to exactly
the same source/build inputs; its log and source restoration were checked.
The existing US GAME image still equals independent ROM extraction:
2,072,880 bytes, SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
No source change can introduce a new cfe warning. No pending batch IDs,
`finish` transactions, assembly edits, permutations or parallel builds.
Two workers performed read-only review. [Validation record](level-header-validation.json).

## Next five investigations

1. `func_151A8B20`: two candidates / 5,439; recover the matched pointer-return,
   signed-short and byte argument contract across callers.
2. Actor31C / owner3D4 child: `150BDB70` at 1,520; resolve conflicting child
   roles using initialization and matched camera readers.
3. Allocator `80003C40 -> 80003C6C`: 42 dependents / 89,251; establish the
   inner return contract before reconciling GAME declarations.
4. `game_18A8F0.c` qualifier blocker: eight scores / 21,931 plus one ERR;
   reconcile 1515E278's volatile-pointer declaration before render adoption.
5. `func_1515E544`: three candidates / 4,256; its matched pointer-return,
   byte-argument contract disagrees with three caller declarations. Candidate
   scores are 150368C4=686, 151135C4=60 and 151462C8=3,510.
