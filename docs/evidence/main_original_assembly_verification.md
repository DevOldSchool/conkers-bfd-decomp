# Main original-assembly verification

The 2026-09-30 continuation restored the full US build before introducing any
new main map split. The unchanged canonical image at `db2ef1ac` rebuilt to
SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, identical to the independently
checksum-validated owned ROM. This supersedes the earlier cloud RSP limitation;
it does not change the historical verification reports for the first five batches.

## Reproduced toolchain

The CPU image remains the repository's locked digest
`sha256:b3e29a92f2c26f11a58fbafde2d5d3b1184416e21b635e07b2a6303591ed5c8b`.
The RSP extension follows `toolchain/rsp.Dockerfile`: the official
[armips source](https://github.com/Kingcom/armips/tree/156f78f6bccfc07498578ac491ce7fe2a1e807a6)
is checked out at exactly the locked revision, built in that CPU image with
the documented `-include limits` flag, and exposed read-only in a private
unprivileged namespace. Neither the shared image nor compiler changes.
CMake 3.30.5 came from its PyPI binary distribution; its downloaded wheel
SHA-256 is `db049e551e2f0562b3b225ac760888ee38b8ade62d74213f3611420e6b22f36d`.
The resulting local armips executable SHA-256 is
`fad4494e343abf17b1476c3ba19d228908acb4d7f6d8faa69d5c3152f5fedcf8`.
These local binary hashes are reproducibility observations, not new project locks.

The unchanged `scripts/build_rsp.py` independently verified all four configured
payloads: `rspboot` (208 bytes), `asp_overlay0` (3,952), `asp_overlay1` (2,496),
and `asp_data` (2,896). The main library dependencies were rebuilt from the pinned
`lib/ultralib` revision `87af1e4d8ed666f2ad407dc11c6e47736094f2f8` and this
repository's Rare library sources. `make build PROFILE=us` then passed its full
ROM comparison. Private ROMs, generated assembly, binaries and local adapters
are not committed.

## Narrow verifier extension

The existing game original-assembly verifier now also accepts registered main
CPU spans. Main input bytes come from the normalized, SHA-1 and size-validated
US ROM. The CPU interval starts at the raw reference profile's entry address
and ends at the first code payload in the independently reviewed RSP layout,
whose ROM checksum must agree. Thus boot bytes and RSP text cannot be silently
treated as main CPU proof inputs.

The existing gates remain: retained `GLOBAL_ASM`, exact registered full span,
independent raw-reference comparison, assembly-word comparison, actual assembly
and link at the registered address, supported external symbol resolution, and
host-side proof revalidation. Unknown overlays fail closed. The `original_asm`
state contributes no matched C functions or bytes. A main batch still runs the
full US ROM build and rechecks each original-assembly proof.

Tests cover main versus game routing, rejecting unknown overlays, main batch
selection without C credit, corrupted/incorrect-size ROMs, a mismatched RSP
layout, out-of-range CPU endpoints, RSP exclusion, actual linked-byte mismatch
rejection, and stale host proof rejection. Existing game proof, rollback,
preservation and progress tests remain in force.

This change does not create a generic alternate-entry model, integrate mixed
main source units, assign a historical SDK identity, or claim any new C match.
Each handwritten group still needs its own complete boundary and entry evidence.

## Cross-span main branch labels

The first exception-family proof exposed a real retained-span boundary:
`0x71D0` branches to `.L8000787C` inside its neighbouring span. The initial
verifier correctly rejected that external symbol form. Main-only resolution
now accepts exactly `.L` followed by eight hexadecimal address digits, and only
when that address lies inside the independently validated CPU text interval.
Suffixes, arbitrary names, nonzero undefined-symbol values and out-of-interval
targets remain rejected. The actual assembled branch relocation still must
produce the original ROM word. Game label handling is unchanged.
