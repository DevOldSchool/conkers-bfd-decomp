# US resource descriptor and dependency core

Evidence type: `structural_analysis`

This working source family narrows older navigation interval
`0x9CA10:0x9DD10` to `0x9CA10:0x9D180`. The older interval comes from local
`mkst/conker` commit `3adf229175c037c771f251f169f9dd80ca306924`,
`conker/conker.us.yaml` (combined base `0x2D4B0`). The following effect-command
handlers are excluded. Original filenames and historical compilation units
remain unknown.

## Structural evidence

The first four accessors select fields `+0/+8/+0xA/+4` of the same
`0x14`-byte descriptor table at `80087430`. `1509CA98` searches `0xCC`
entries by their masked `+4` value, and `1509CB68` counts non-null `+0`
entries across that exact table (`80087430:80088420`).

### Recovered task/scene names

The supplied retail-debug screenshots provided a lead at US runtime address
`0x8009E834`. Independent decoding of the owned, checksum-validated US ROM
confirms that this is `Training - Scarecrow`, and descriptor 0's first word
points to it. The next displayed name, `Training - Jumping`, belongs to
descriptor **4**, not descriptor 1: unnamed entries must retain their indices.

All 204 records were inspected. Exactly 116 have non-null, terminated ASCII
name pointers into decoded game data; 88 have no name. These are task/scene
labels attached to resource descriptors, not evidence for 116 distinct maps.
`func_1509CA10(index)` is the nullable descriptor-name accessor. Its recovered
return type is `const char *`; its registered identifier is preserved. The
source-local `ResourceDescriptor` now names the confirmed fields:

| Offset | N64 type | Meaning established by ROM and consumers |
| --- | --- | --- |
| `+0x00` | `const char *` | Optional task/scene name |
| `+0x04` | `s32` | Packed ID; the search compares `(value & 0x1FFFFFFF) + 1` for named records |
| `+0x08` | `u16` | Raw field returned by `func_1509CA30`; semantics unassigned |
| `+0x0A` | `u16` | Raw field whose low 12 bits are returned by `func_1509CA50`; remaining semantics unassigned |
| `+0x0C` | `const u16 *` | Dependency-index list traversed by `1509CBD4` and `1509CCB4` |
| `+0x10` | `const u16 *` | Related dependency-index list traversed by `1509CCF4` |

Both lists end at `0xFFFF`. Every list terminates inside decoded US game data,
and every non-terminator is an index below 204. There are 223 references in the
`+0x0C` lists and 55 in the `+0x10` lists, counting repeated references. The two
list roles remain separate; this evidence does not establish gameplay order,
mandatory completion requirements, or original field/function names.

Examples below use decimal descriptor indices. Empty lists are shown as `[]`.

| Index | Name | `+0x0C` indices | `+0x10` indices |
| --- | --- | --- | --- |
| 0 | Training - Scarecrow | `[191]` | `[]` |
| 1 | Unnamed | `[0]` | `[]` |
| 4 | Training - Jumping | `[]` | `[1]` |
| 5 | Training - Frying Pan | `[191]` | `[4, 1]` |
| 6 | Training - The Baddie | `[4]` | `[8, 5, 1, 4]` |
| 9 | Training - Waterfall Cash | `[]` | `[]` |

For example, descriptor 6's first list reaches the named Jumping descriptor,
while its second list reaches Frying Pan and Jumping plus unnamed entries 8
and 1. Assigning invented names to the unnamed records would lose evidence.

Provenance:

- US ROM SHA-1: `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
- Decoded game-data SHA-1: `42bbe7f02702ca7af5da499fb5cf2f34b7d3d23b`.
- Descriptor-table SHA-1: `378e173d56925ab4b894d91f963d7eb2687a904e`.
- Data base: `0x80082B20`; table data offset: `0x4910`; string data offset:
  `0x1BD14`. These are decoded-data offsets, not retail-ROM file offsets.

The local report below resolves names on both dependency lists while retaining
all unnamed records and raw fields. Run from the repository root with the
owned US ROM installed. It writes only ignored research output; do not commit
the extracted names/report.

```sh
python3 -B - <<'PY'
import hashlib
import json
import struct
from pathlib import Path
from scripts.rzip_archive import parse_game_archive
from scripts.rzip_extract import load_layout

layout = load_layout("us")
rom = Path(layout["default_rom"]).read_bytes()
rom_sha1 = hashlib.sha1(rom).hexdigest()
assert rom_sha1 in layout["normalized_sha1"], "unexpected US ROM"
game = parse_game_archive(rom[layout["game_start"]:layout["game_end"]])
data, base = game.data, layout["game_data_vram"]
table = 0x80087430 - base
records = []

def read_list(address):
    offset, values = address - base, []
    while 0 <= offset <= len(data) - 2:
        value = struct.unpack_from(">H", data, offset)[0]
        offset += 2
        if value == 0xFFFF:
            return values
        assert value < 204, "dependency outside descriptor table"
        values.append(value)
    raise ValueError("unterminated or out-of-bounds dependency list")

for index in range(204):
    address, packed, f8, fa, dep, related = struct.unpack_from(
        ">IIHHII", data, table + index * 0x14)
    name = None
    if address:
        offset = address - base
        assert 0 <= offset < len(data), "name pointer outside game data"
        name = data[offset:data.index(0, offset)].decode("ascii")
    records.append(dict(index=index, name_address=f"0x{address:08X}",
        name=name, packed_id=f"0x{packed:08X}", field_8=f"0x{f8:04X}",
        field_A=f"0x{fa:04X}", dependencies=read_list(dep),
        related_dependencies=read_list(related)))

for record in records:
    for key in ("dependencies", "related_dependencies"):
        record[key] = [dict(index=i, name=records[i]["name"])
                       for i in record[key]]
assert sum(record["name"] is not None for record in records) == 116
report = dict(schema_version=1, rom_sha1=rom_sha1,
    data_sha1=hashlib.sha1(data).hexdigest(), table_address="0x80087430",
    table_sha1=hashlib.sha1(data[table:table + 204 * 0x14]).hexdigest(),
    records=records)
output = Path("build/research/resource-descriptor-names.json")
output.parent.mkdir(parents=True, exist_ok=True)
output.write_text(json.dumps(report, indent=2) + "\n")
print(f"{output}: 204 records, 116 named, 88 unnamed")
PY
```

The external screenshots are discovery leads, not source code or authority
to enable cheats. The crash-menu strings and regional build timestamps are
separate evidence, recorded in [Retail debug metadata](us_retail_debug_metadata.md).

Recursive query `1509CBD4` reads each descriptor's `+0xC` halfword dependency
list (`8008743C`, stride `0x14`), terminated by `0xFFFF`, and checks each
resource bit in the buffer addressed by `800D2E4C`. Local `1509CCB4` passes
that same list and its own function pointer to `1509CE64`, whose indirect
call recursively visits dependencies and writes state 3 into `800D2E70`
and the corresponding availability bit. `1509CC94` is a direct wrapper.

`1509CCF4` traverses the other dependency list at descriptor `+0x10`
(`80087440`), updates the same state and bitset, and calls `1509CCB4`.
`1509CDDC` repeatedly runs that traversal across all `0xCC` descriptors until
no new state is added. These are concrete links between the descriptor
accessors and dependency operations.

The final three functions own a related loaded table at `800D2FB0`:
`1509CF28` loads and relocates it; `1509D054` frees and clears it;
`1509D08C` queries its halfword resource lists and checks every referenced
resource against the same `800D2E4C` availability bitset. That shared query
contract connects this loader lifecycle to the dependency core. The next
entry `1509D180` instead begins the effect-command switch and is excluded.

## Validation

All fifteen labels agree with the independent US index. Their spans total
1,904 bytes and match owned US instructions, delay slots and padding. Both
boundaries follow complete returns; no decoded conditional branch crosses
either boundary in either direction. No data, rodata or BSS ownership is
assigned. Full US overlay byte equality gates integration. This initial review
registered raw ASM; the current function inventory records subsequent C matches.

### `src/game/game_C9EC0.c`

Range `0x9ca10:0x9d180`; 15 entries, 1,904 bytes.
SHA-1: `7f80b6659725e30b32eccb9ea7adcf84cb2ad5d9`.
debug: 10 correlations, 5 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1509CA10` | `0x20` |
| `func_1509CA30` | `0x20` |
| `func_1509CA50` | `0x28` |
| `func_1509CA78` | `0x20` |
| `func_1509CA98` | `0xd0` |
| `func_1509CB68` | `0x6c` |
| `func_1509CBD4` | `0xc0` |
| `func_1509CC94` | `0x20` |
| `func_1509CCB4` | `0x40` |
| `func_1509CCF4` | `0xe8` |
| `func_1509CDDC` | `0x88` |
| `func_1509CE64` | `0xc4` |
| `func_1509CF28` | `0x12c` |
| `func_1509D054` | `0x38` |
| `func_1509D08C` | `0xf4` |

## Integration result

Integrated on the first build attempt. The complete US game overlay is
byte-identical: 2,072,880 bytes, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All entries were raw ASM at that
initial integration. The unit is now mixed C/ASM; the naming recovery does not
claim additional matched functions or a completed source unit.

The naming recovery was verified in an isolated worktree based on commit
`8d8cc9fd8cd4ffd3f49af72e778c1ebc8619d6fb`. Both
`./conker finish func_1509CA10` and `./conker finish func_1509CA78` reported
`CURRENT (0)` and preserved the reviewed source-unit symbol layout.
`./conker verify-batch func_1509CA10 func_1509CA78` then rebuilt the complete
US game overlay byte-identically and reported `AGENT_ACTION: BATCH_COMPLETE`.
The batch ran 788 tests with one skipped; metadata, generated progress, and
whitespace checks passed. The documented extraction snippet was also run and
its hashes, record counts, and dependency totals checked against the values above.
