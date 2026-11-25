# US resource-handler address tables

Four contiguous arrays at `80088420`, `8008845C`,
`80088498` and `800884D4` each contain 15 four-byte function addresses: 240
bytes in total. Of their 60 slots, 39 name distinct functions and 21 are NULL.

## Independent extent and pointer evidence

The complete registered interpreter span `150ADAF0..150AE280` is 1,936 bytes,
SHA-1 `71289db6b6c195a4238ed75271181abe79c461da`. Its four entry paths at
`150AE0F8..150AE134` select these exact bases. The common path masks `F000`,
shifts right 12, returns early for zero, and otherwise subtracts one before
indexing four-byte entries. This establishes indices 0 through 14 without
using the address of the next symbol to infer an array length.

The two variadic resource APIs at `1509BE40` and `1509BFB0` independently use
the latter two tables, with descriptor, operation and argument-buffer inputs.
All nonzero original table words are registered GAME function entrypoints.

## C representation and scope

`resource_handlers.c` is a data-only reconstruction owner, not a claim about
an original compilation unit. It uses symbolic references to the existing
functions. Those functions and their consumers are unchanged. The linker
retains the compiled table in an INFO section for independent comparison with
the original GAME data archive; the archive remains runtime backing.

These are heterogeneous callback addresses. The address-holder type is never
called by this unit. Each initializer explicitly converts the individually
declared function address to that holder type; this does not impose a common
calling convention or generate adapter code. Existing source declarations
are retained, including void returns and unused narrow arguments. Existing
tagged argument structures need only opaque declarations. The anonymous
`GameCB3D0Query` record retains its source-local six-word layout.

For the ten functions still represented only by assembly, the dispatcher and
callee prologues establish two or three integer-register arguments: a
descriptor, an optional operation and an argument-buffer pointer. Their
return paths use `v0`, including `mfc1` when returning float bits. The new
declarations describe those ABI inputs without inventing a buffer layout or
changing any implementation. No shared header or function inventory changes.

The four symbols have explicit 60-byte extents. Null entries remain null;
every other slot must retain an R_MIPS_32 relocation to its named function
with zero addend. No raw numeric code addresses or filler arrays generate the
candidate.

## Accepted validation

The four tables add **240 matched data bytes**, taking Data to
**63,194,512 / 65,120,512 (97.0424%)**, with **1,926,000 bytes remaining**.
Complete Data remains 63,148,384 because the original GAME archive still
provides runtime backing. Code and function measures are unchanged.

The actual compiler object contains exactly 240 zero-addend bytes, 39 named
R_MIPS_32 relocations and four 60-byte symbols. Every linked function address
agrees with the original ROM entrypoint. The full 2,072,880-byte GAME code
image is unchanged. An independently assembled 189,088-byte GAME data image
also matches the original, and its table reference agrees with the candidate's
scalar bytes and all 39 symbolic destinations. Native objdiff matches 240/240.
All 60 individual slot mutations fail both semantic and native comparisons;
both full-interpreter endpoint mutations fail the consumer check.

The full Docker suite passed 2,965 tests in 181.411 seconds, with eight skips.
`./conker build --assets` reproduced the complete 67,108,864-byte US ROM,
SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, in 142 seconds including
setup and Docker. Fresh report preparation took 348.1 seconds; native comparison
and validation took 26.1 seconds, with no compilation errors. Progress and
whitespace checks passed. All 27,249 prior editable asset-source hashes remain
unchanged. The former 38,224-byte raw unit is replaced by this 240-byte owner
and an uncredited 37,984-byte suffix; every other unit's measures are unchanged.

Tested base: `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7` plus local changes.
Source fingerprint:
`a348c075afdab45889e154f65f9230e29d509b58109c768252c09e4a6572e6bf`.
Report SHA-256:
`57a62c6b8112e8eb50c4ba86d7f6f21509d7830078718f5def3821f84f499bcf`.
See [machine-readable evidence](us_resource_handlers.json).
