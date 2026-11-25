# US weighted vectors

This batch reconstructs 312 bytes in four compatible `Vec3f` definitions:
`800A24B0` and `800A2568` each contain seven proven records (84 bytes), and
`800A2520` and `800A25BC` each contain six proven records (72 bytes).
Each table fills its storage up to the next object: the weighted record at
`800A2504`, the next table, or (for `800A25BC`) a separate run of
`{ x, -24, 43 }` vectors at `800A2604` that has a different shape and is left
unclaimed. The original source declares all four as `Vec3f[]`.

## Native consumers and extent evidence

Five complete registered native instruction spans are authenticated against the
original ROM: `150ADA68`, `151094FC`, `15109FB8`, `15143134`, and `150A7960`.
The RNG masks its integer output to sixteen bits, converts it to a single-precision
value and multiplies it by the original scale at `8009F740`. Both selectors
multiply by the original total at `800A251C`, then compare and subtract weights
starting at `800A2504`. The branch-likely delay slot subtracts only when taken.

An independent integer/rational arithmetic replay executes both original selector
instruction streams for a witness of each index zero through five in each of the
four IEEE rounding modes: 24 input/mode cases, 48 native selector executions.
Rounding uses integer division, directed rounding and ties-to-even; it does not
reuse the floating-point approximation in the earlier exhaustive research scan.
These are static input-domain witnesses, not evidence that a particular PRNG
state or gameplay path has been reached.

The native code multiplies the selected index by twelve. In `151094FC`, the
`800A24B0` loads at offsets 0/4/8 and 12/16/20 feed single-precision interpolation,
which proves the first seven vector records. `800A2520 + 12*index` is passed in
`a0` to `15143134`; the helper preserves that pointer in `s0`, performs float zero
comparisons, and passes its three fields to `150A7960` for float multiplication.
The same field layout is read for all six selected records.

In `15109FB8`, `800A2568` supplies the same six-field interpolation pattern.
`800A25BC + 12*index` supplies offsets 0/4/8 in `a1/a2/a3` to `150A7960`, whose
MTC1 and MUL.S instructions establish all three floating-point fields. The
pointer/index paths rely on normal ABI preservation; the complete helper spans
are included in the evidence. All 78 represented four-byte fields have a typed
native read witness. No extent is obtained by subtracting adjacent symbol addresses.

## Rounding and boundary limitation

The earlier exhaustive research checks all 65,536 low-sixteen-bit outputs in all
four rounding modes. Upward rounding with input 65,535 selects index six; the
independent exact-rational native replay confirms this edge case. Therefore this
batch makes no universal `index <= 5` claim. The seven-record interpolation
tables and six-record third-point tables are established by the index-zero
through index-five witnesses, independently of whether additional reads can occur.

The whole-program FCSR invariant remains unproven. It is not required for these
table claims. Original scale/weight bytes are assumed; runtime immutability,
PRNG-state reachability, gameplay activation and original object boundaries are
not asserted. This batch deferred the separate 24 weight bytes because the
existing 28-byte structure declaration overlapped an already reconstructed
total scalar. A subsequent [joint-owner reconstruction](us_weighted_record_joint.md)
replaces the total's separate owner with the full compatible record; its
validation status is recorded separately.

## Build and validation

These are INFO verification definitions. Runtime storage continues to come from
the original GAME archive. The four compiled payloads reproduce 312 original
bytes; 40 compiler-tail bytes are explicitly excluded from matching credit.
There are no pointer relocations. Existing function bodies, shared headers,
assembly, and function/source-unit inventories are unchanged.

Tested base commit: `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7`, plus uncommitted
work. Pinned pilot compilation, the independent full-GAME reference, native
312/312 byte comparison, and rejection of all 312 one-byte mutations pass.
Integrated GAME, asset, preservation, regression and final-report checks pass.
All 1,934 previous GAME objects preserve their allocated bytes, symbols and
relocations. The complete 2,072,880-byte GAME code image is unchanged. The
actual linked definitions pass independent native comparison; 312 native-byte
mutations and 312 independent ROM-byte mutations are rejected.

The regression suite passes 3,038 tests with eight skips. The reconstructed-asset
build passes, and independent ELF extraction reproduces the entire original
67,108,864-byte ROM. All 27,323 previous asset source hashes and 11,847 asset
object hashes are preserved.

The audited report credits 63,341,881 / 65,120,512 data bytes, leaving 1,778,631.
Complete-data and code/function measures are unchanged. Report SHA-256:
`37300813851df916e8cf8e5b75748e0a572b66f35dea567d32bd2908a67c7191`.
