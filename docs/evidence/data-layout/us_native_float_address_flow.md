# US native float addresses and bounded records

This batch reconstructs 192 bytes in three C owners: a three-float record and
two nine-entry tables walked by one native loop. Each is a named object with a
proven consumer; contiguous grouping does not infer source-file boundaries or
runtime immutability.

## Record contracts

- `80088724`: three float components, 12 bytes. Native loads use all three in
  single-precision subtraction. The initializer stores zero at offsets 0, 4 and
  8, including the final store in a call delay slot. The existing float-array
  declaration is retained; explicit initialization emits `.data` with pinned IDO.
- `800A49C0`: nine `Vec3f` position records, 108 bytes, using the existing shared
  vector type. `800A4A2C`: nine signed `{ first, count }` records, 72 bytes.
  Native function `1513BBFC` initializes both pointers and an explicit range
  endpoint, advances them by 12 and 8 bytes, and compares the range pointer with
  that endpoint. Both inner-loop paths advance the range pointer exactly once;
  the outer branch delay slot advances the vector pointer. All three float
  components and both signed range fields are consumed. Original ranges contain
  12 entries followed by eight groups of 16. This is native loop-bound evidence,
  not an extent inferred from neighboring symbols or a claim of gameplay activation.

## Withdrawn scalars

The original batch also defined 280 scalar owners and the polynomial
coefficient words at `80099024` and `80099050`. Each was a single function's
`lui`/`lwc1` constant: an IDO per-function literal that is credited when its
function matches. They were withdrawn under the project rule against
reconstructing literal pools as data.

Each owner is INFO verification storage; the original GAME archive continues
supplying runtime data. There are no pointer relocations. No existing function
body, shared header, assembly, function inventory or source-unit inventory
changes.
