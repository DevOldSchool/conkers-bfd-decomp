# US slot controller and paired attachment families

Evidence type: `structural_analysis`

These working source families use older navigation intervals from local
`mkst/conker` commit `3adf229175c037c771f251f169f9dd80ca306924`,
`conker/conker.us.yaml`, combined base `0x2D4B0`. The first range is narrowed
to a complete controller core; the two attachment families retain their older
separate intervals. Original filenames and historical compilation units remain
unknown. No semantic function renames are claimed.

## Slot-managed controller: `0xE3020:0xE4010`

Constructor `150E3020` allocates type `0x27`, size `0x80`, initializes
position/motion fields and audio handle `+0x4A`, and scans eight slots in
`800D99D0`, storing a selected index at object `+0x48`. Wrappers
`150E3208/150E32D0/150E3340/150E3414` call that constructor with related
position, timing and motion arguments. The audio variant `150E3414` passes
the address of local `150E33CC` to `1000FA64` at `0xE34A4:0xE34E8`
and stores the returned handle at `+0x4A`.

Cleanup `150E3514` clears a slot only if it still points to this object, stops
that audio handle and releases the controller. Bulk helper `150E35DC` walks
type lists at `800DCE50 + 0x9C` (`0x27 * 4`), stride `0x1A0`, calling the
same cleanup for matching slot indices. Query `150E36BC` reads `800D99D0`,
checks type `0x27`, and returns that object's position.
Update `150E3738`, referenced by owned type slot `8008BC94`, consumes the
same object fields and calls `150E3514` on termination. All ten entries belong
to this lifecycle; the following actor-effect callbacks are excluded.

## First attachment family: `0xFDDA0:0xFE320`

Opening `150FDDA0` calls local `150FDF38`. That routine transforms model
anchors `800A1F70/800A1F88` using model node selector `80088B80`, with a
fallback to actor position when no model is present. It passes the resulting
positions to common attachment helpers and then local `150FE0B8/150FE288`.
`150FE0B8` uses the same anchor and node selector when creating its effect;
`150FE288` constructs a related owner-mask event from actor `+0x318`.

The remaining local adapter `150FE248`, owned callback slot `8008FC7C`,
passes exactly anchor `800A1F70` and selector `80088B80` to `151D3E04`.
This connects it to the family independently of adjacency or a guessed name.

## Second attachment family: `0xFE320:0xFE860`

Opening `150FE320` calls local `150FE49C`, which resolves its own anchor pair
`800A1FC8/800A1FD4` through selector `80088B94`, then calls
`150FE604/150FE7D4`. The former uses those same model-anchor inputs to
create effects; the latter builds the related owner-mask event.
Adapter `150FE794`, owned slot `8008FC78`, passes the same `800A1FC8`
anchor and `80088B94` selector to `151D3E04`. The two five-entry families
have similar call shapes but distinct anchor data and effect parameters.
There are no beta correlations for these two groups; structural evidence is
the basis for their grouping.

## Validation

All twenty labels agree with the independent US index. The ranges total
6,832 bytes and match owned US instructions, delay slots and padding. All
endpoints follow complete returns; no decoded conditional branch crosses a
range boundary in either direction. No data, rodata or BSS ownership is
assigned. Full US overlay byte equality gates integration. All entries remain
raw ASM, not matched C.

### `src/game/game_1104D0.c`

Range `0xe3020:0xe4010`; 10 entries, 4,080 bytes.
SHA-1: `2977e8bbd9e3befc3c2cc11a935a95f14f7df46c`.
debug: 3 correlations, 0 strong.
ects: 3 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150E3020` | `0x1e8` |
| `func_150E3208` | `0xc8` |
| `func_150E32D0` | `0x70` |
| `func_150E3340` | `0x8c` |
| `func_150E33CC` | `0x48` |
| `func_150E3414` | `0x100` |
| `func_150E3514` | `0xc8` |
| `func_150E35DC` | `0xe0` |
| `func_150E36BC` | `0x7c` |
| `func_150E3738` | `0x8d8` |

### `src/game/game_12B250.c`

Range `0xfdda0:0xfe320`; 5 entries, 1,408 bytes.
SHA-1: `0dfa3ad4eea53c3ac0682f6dbad2e47c8f67ed87`.
debug: 0 correlations, 0 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150FDDA0` | `0x198` |
| `func_150FDF38` | `0x180` |
| `func_150FE0B8` | `0x190` |
| `func_150FE248` | `0x40` |
| `func_150FE288` | `0x98` |

### `src/game/game_12B7D0.c`

Range `0xfe320:0xfe860`; 5 entries, 1,344 bytes.
SHA-1: `15a9deb01cc68d5a5f1f24bff24f372fa69b75ff`.
debug: 0 correlations, 0 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150FE320` | `0x17c` |
| `func_150FE49C` | `0x168` |
| `func_150FE604` | `0x190` |
| `func_150FE794` | `0x40` |
| `func_150FE7D4` | `0x8c` |

## Integration result

All three groups integrated on the first build attempt. The complete US game
overlay is byte-identical: 2,072,880 bytes, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All twenty entries remain raw ASM.
