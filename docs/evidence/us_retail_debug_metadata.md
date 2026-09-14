# Retail debug metadata

The user-supplied crash-debug and build-info screenshots are discovery leads.
The following strings were independently checked in the owned US and European
retail ROMs. All offsets in this table are ROM file offsets.

| String | US offset | Europe offset |
| --- | --- | --- |
| `REGISTERS` | `0x1A3144` | `0x1A34A4` |
| `HOSTDEBUG` | `0x1A3170` | `0x1A34D0` |
| `Version` | `0x1A3188` | `0x1A34E8` |
| Build date | `0x1A3198`: `Dec 19 2000` | `0x1A34F8`: `Jan 31 2001` |
| Build time | `0x1A31A4`: `09:57:42` | `0x1A3504`: `13:29:42` |
| `STACK-VIEW` | `0x1A3238` | `0x1A3598` |

ROM SHA-1s match `config/roms.json`: US
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, Europe
`ee7bc6656fd1e1d9ffb3d19add759f28b88df710`. Europe is a research comparison;
US remains the only matching/integration gate.

The screenshots report version 163 for US and 19 for Europe. Those numeric
values have not yet been traced to the rendering code. Finding the literal
`Version` label and timestamp strings does not independently verify them.
The US strings fall after the configured game archive end (`0x19EA88`) and
before the flat-asset start (`0x1A37E0`), in the current raw-ROM portion of
the main build map. Their containing code/data ownership and runtime load
address remain unreviewed. They do not justify a new source-unit boundary.

The screenshot's cheat `XFYHIJERPWAL IELWZS`, A-button menu entry, and
GameShark pair `D0042A15 0008` / `800E0B94 0002` are unverified activation
leads. No cheat, memory patch, crash, or emulator session was executed during
this investigation. The target byte `0x800E0B94` is already used as an index
by the [reviewed state/drawing dispatchers](game_raw_connected_controller_groups.md#game_215960c),
so it must not be renamed as a dedicated debug-enable flag from this report.
`0x80042A15` lies inside the mapped libultra controller BSS object beginning
at `0x80042A10`; the exact byte's role is not established here.

The independently confirmed name at `0x8009E834` and its consuming table are
documented in [Resource descriptors](game_raw_resource_dependency_core.md#recovered-taskscene-names).
That address is a runtime data address, unlike the ROM offsets above.
