# Game mapping search until the 3% usage boundary

Scope: continue reviewed raw-assembly game source-family mapping on `feature/mappings`, stopping at 97% weekly Codex usage or when the defensible call/pointer frontier is exhausted. Generic names identify ROM offsets, not recovered historical filenames. No new matching C implementations are claimed.

At the start, reviewed source intervals and exact library text covered 1,450,784 of 2,237,392 tracked US code bytes (64.8426%); the game overlay covered 1,352,272 of 2,072,880 (65.2364%). The run started at 94% weekly usage.

## Results and evidence

| Evidence | Accepted groups | Raw entries | Bytes |
| --- | ---: | ---: | ---: |
| [Internal-call and callback clusters](game_raw_internal_call_callback_clusters.md) | 15 | 42 | 9,600 |
| [Direct helper pairs](game_raw_direct_helper_pairs.md) | 11 | 24 | 13,200 |
| [Callback-table runs](game_raw_callback_table_runs.md) | 4 | 45 | 10,736 |
| [Complete callback clusters](game_raw_complete_callback_clusters.md) | 18 | 81 | 27,696 |
| [Table-selected collections](game_raw_table_selected_collections.md) | 2 | 9 | 3,968 |
| [Pointer-selected subranges](game_raw_pointer_selected_subranges.md) | 10 | 33 | 12,240 |
| [Pointer-table runs](game_raw_pointer_table_runs.md) | 24 | 104 | 34,512 |
| [Pointer-selected singletons](game_raw_pointer_singletons.md) | 12 | 12 | 13,552 |
| [Continued pointer-selected singletons](game_raw_pointer_singletons_continued.md) | 20 | 20 | 9,808 |
| [Final pointer-selected singletons](game_raw_pointer_singletons_final.md) | 24 | 24 | 2,960 |
| Total | 140 | 394 | 138,272 |

All 394 functions remain raw assembly inside generated source wrappers. The multi-function ranges require complete membership through owned callback pointers or direct local calls. After those ranges were exhausted, the singleton batches used exact independently indexed function spans selected by owned-ROM callback pointers. The singleton bounds are minimal working units and do not claim recovered historical compilation units.

## Exclusions and remaining leads

The following ranges receive no new boundary credit:

- `0xA6210:0xA6360`, `0xAA9A0:0xAB1F0`, `0x15BAE0:0x15BE50` and `0xAC9C0:0xAD770` disagree with the independent function CSV. Their raw-only or index-only entries must be reconciled first.
- `0xBF760:0xBFFE0` was removed from the pointer-table batch because an owned pointer selected a function outside the proposed two-member range.
- `0xD8A20:0xD8B10` was removed because both functions already belong to the reviewed `game_105D90` source range.
- `0xEB20:0xEB30` was withdrawn after the repository identity gate confirmed that the existing named `game_3BFD0` raw split must remain ASM in the comparison map. Its raw function work item is retained.
- `0x1DD140:0x1DD3A0` remains a possible Rare EEPROM library override and is not assigned to game code.
- `0x183D0:0x186D0` contains unusual Huffman-like routines and labels; its direct call alone is insufficient to distinguish game ownership from a library-derived unit.
- The remaining raw groups contain unselected members or relationships that do not establish a complete source family. Similar neighbors, shared constants or beta-version resemblance alone are insufficient boundary evidence.

The bounded beta-index review produced navigation correlations only. Project policy correctly treats those correlations as insufficient source-boundary evidence without a separate complete-membership signal.

## Coverage and validation

The 140 accepted units raise reviewed source boundaries plus exact library text to 1,589,056 / 2,237,392 US code bytes (71.0227%). Game-overlay coverage is 1,490,544 / 2,072,880 (71.9069%). Overall, 648,336 bytes remain without reviewed ownership. The instruction-matched byte count remains 150,564; this run adds mapping evidence rather than C implementations.

All ten mapping batches passed complete-overlay integration. The overlay is 2,072,880 bytes with SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`, and each integrated output compared byte-identically. After withdrawing the named raw split, all 176 repository tests pass, generated progress is current, `git diff --check` passes, and `./conker build --profile us` reports `build/us/conker.us.z64: OK` for the corrected complete US ROM.

The run stopped at 97% weekly Codex usage, leaving 3% as requested. The conservative mapping frontier had also been exhausted before the final validation gates. Existing branch work was preserved; nothing was staged or committed.
