# US model-effect selection tables

This batch reconstructs 2,244 bytes in eight data owners. Definitions retain
original values and symbolic references, use existing scalar/Vec3f types,
and do not change function bodies, shared headers or assembly. These are
INFO verification owners; the runtime archive and original source-unit
completion status remain separate.

| Storage | Address | Bytes | Native extent evidence |
| --- | --- | ---: | --- |
| Fragment-list pointers | `80089A20` | 80 | Twenty effect-profile indices |
| Additional selector list | `800A18C0` | 12 | Literal count three at `150F1FE8` |
| Bank-09 resource lookup | `800A3880` | 932 | Supplied selector 232; 233 words reach the next object |
| Fragment scales | `800A3C30` | 60 | Largest native fragment count is twelve; fifteen floats reach the next object |
| Fragment selector lists | `800A3C6C` | 680 | Union of twenty native pointer/count spans |
| Fragment counts | `800A3F14` | 80 | Twenty effect-profile indices |
| Fragment codes | `800A3F64` | 80 | Twenty indexed word loads; downstream uses the low byte |
| Model-effect profiles | `800A3FD8` | 320 | Twenty native selector results, stride sixteen |

## Native type and selector paths

The accompanying JSON pins eleven complete registered US function spans and
checks the important native instructions. Registered spans come from the
canonical function/source-unit inventories, including functions without an
explicit `size_bytes` property. Original raw assembly is checked where it
exists; matched C is not used to create the reference bytes.

`func_15134070` dispatches through two original jump tables and returns every
profile index from zero through nineteen, or sentinel 99. The jump-table
bounds and destinations are independently checked. `func_15138BC0` and
`func_15136C3C` reject the sentinel before indexing the data. Existing compiler
jump-table ownership remains unchanged.

The profile stride is sixteen. `func_151380B4` passes the first twelve bytes
to `func_15143134`, whose three float loads establish a Vec3f offset.
`func_15138424` loads an unsigned halfword at `+0xC` as the model selector
and an unsigned byte at `+0xE` as its mode. The source-local structure leaves
one natural padding byte, verified zero in all twenty native records.

The same profile index selects the fragment root, count and code words in
`func_15136C3C`. Its full-count path passes the original count; another path
subtracts two. `func_1513A24C` forwards the root/count to `func_1515080C`,
which initializes a count-sized availability array and selects list entries
without replacement. The original selector load uses a four-byte stride.
All twenty ranges are contiguous and cover precisely 680 bytes. A grouped
word array preserves them, and twenty genuine pointer relocations retain
each list's starting element. Type one's original callback is unchanged;
its separate material eligibility is not a storage-layout restriction.

The scale pointer passed in the third argument is saved at helper stack
`+0x128`, indexed by the same selected ordinal, loaded as a float at
`15150C18`, and multiplied into the spawned object's scale. The maximum
supplied count is twelve. Three further `1.0f` words follow before the
selector lists at `800A3C6C` and are included; no native count reaches them.
The word-code table is loaded at `15136D0C`; its low byte is consumed at
`1513A2D8` and copied into the helper's parameter record.

## Why selector 232 is supported

Profile fifteen's root points to `800A3E70`, with count eight. Slot four
contains 232. Even its reduced count, six, includes that slot. The native
helper copies the selected word into template halfword `+0x56` at
`15150BFC` and submits it through `func_1513264C`.

That routine loads template `+0x56` and passes it to `func_151336A8`, which
indexes `800A3880` at four bytes per selector. It loads the resource index
and calls the resource loader with bank nine. Thus the 233-word lookup
follows a concrete producer/consumer path. It does not rely on a
research module's `MODEL_COUNT` constant or a neighbouring label.

Storage reconstruction does not assert that every conditional path executes
in a session, or that these grouped C definitions recover original object
boundaries. The lookup ends at the next object, one entry past the
largest demonstrated index.

## Validation

Base commit: `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7`, plus uncommitted work.
Actual pinned-compiler pilots reproduce all 2,232 bytes and twenty symbolic
pointer destinations/addends. Twenty-four emitted tail bytes are excluded.
The independent whole-GAME reference is byte-identical, and native objdiff
matches all eight owners. All 808 prior GAME objects retain identical allocated
bytes, symbols and relocations. All 2,272 native negative checks fail as expected
(2,232 byte changes, twenty pointer destinations and twenty pointer addends);
the independent ROM-byte verifier also rejects all 2,232 byte changes.

The full suite passes: 3,033 tests, eight skips, 354.309 seconds. The local US
asset build passes (276 seconds wall time), and an independent extraction of
the linked ROM reproduces all 67,108,864 original bytes, SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`.

The accepted full report matches 63,322,159 of 65,120,512 data bytes, a gain of
2,232; 1,798,353 remain. Complete-data, code and function measures are unchanged.
All 27,301 prior asset inputs and 11,836 asset objects are preserved. Preparation
took 473.7 seconds and report validation 30.5 seconds. Report SHA-256:
`d8d150aa2870af670e9c2294b343012d71bcc6108fb976b02286f0ed78364c68`.
The accepted source fingerprint is
`98b38d1d8543f74728c43c93cc813c7ad4d368578e5f7124907dc14bb4a8ee5a`.

Temporary scripts and snapshots are under
`build/us/data-completion/model-effect-*`.
