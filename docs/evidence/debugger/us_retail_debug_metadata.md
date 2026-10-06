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

A subsequent independent loader and instruction review confirms version 163
for US and 19 for Europe. The renderer arguments are at US ROM `0x19EC58`
and European ROM `0x19EFB8`. The US strings belong to the separately loaded
debugger image `[0x19EA88, 0x1A33E8)`, mapped at `0x16000000`, with entry
`0x16000B14`. Its code/data boundary and remaining ownership limits are
recorded in [US retail debugger overlay](us_debugger_overlay.md).
The image boundary does not establish original source-unit boundaries.

The screenshot's cheat `XFYHIJERPWAL IELWZS`, A-button menu entry, and
GameShark pair `D0042A15 0008` / `800E0B94 0002` are unverified activation
leads. These particular activation leads have not been executed. A later bounded
emulator attempt using independently identified fault/loader flags did not
establish live debugger entry; see the overlay report. The target byte
`0x800E0B94` is already used as an index
by the [reviewed state/drawing dispatchers](../boundaries/game/families/game_raw_connected_controller_groups.md#game_215960c),
so it must not be renamed as a dedicated debug-enable flag from this report.
`0x80042A15` lies inside the mapped libultra controller BSS object beginning
at `0x80042A10`; the exact byte's role is not established here.

The independently confirmed name at `0x8009E834` and its consuming table are
documented in [Resource descriptors](../boundaries/game/families/game_raw_resource_dependency_core.md#recovered-taskscene-names).
That address is a runtime data address, unlike the ROM offsets above.
