# Deferred matching: 2026-10-04

Latest eight-function checkpoints; US, manual only. Shared change: approved ROM-backed linker table mapping.

| Function | Source under src/game/ | Result | Revisions |
| --- | --- | --- | --- |
| 1509C7C8 | game_C98F0.c | Matched5950→0; ROM table placement verified | 1 |
| 1509C440 | game_C98F0.c | Candidate5371→3026; boolean returns restored | 2 |
| 1511AF30 | game_1483E0.c | Candidate791; float intrinsic/call repaired | 2 + compile repair |
| 1512DD50 | game_15B200.c | Candidate5756→4780; vector ABI/storage repaired | 2 |
| 150ADA20 | game_DAE50.c | Valid candidate3600; 64-bit instruction barrier | 1 |
| 150AD9A0 | game_DAE50.c | Candidate2775 retained; trapping-opcode barrier | 0 |
| 151BE558 | game_1EB6C0.c | Candidate2322→275; branch/exit scheduling remains | 2 |
| 151BE210 | game_1EB6C0.c | Valid candidate2480→1010; shared float snapshot restored | 2 |

Clean verify-batch: BATCH_COMPLETE; full GAME and external rodata match ROM.
Layout, progress and whitespace passed; 1,823 tests passed, 37 skipped.
Seven best candidates remain deferred; no shared headers or compiler changes.
Owning-source matches151BE4B8/151BE604 rechecked at0 and clean-verified; no new credit.

Workflow findings:
- Audit raw returns, case coverage and callee inputs before trusting m2c starters.
- Audit vector storage, intrinsic declarations and global snapshot timing.
- Triage handwritten opcode barriers before revisions; rank valid candidates first.
- Report external table placement during ready/finish; focused zero cannot prove linking.

Details: [table evidence](game_c98f0_jump_table.md). Task commits use DevOldSchool-AI-Agent.
