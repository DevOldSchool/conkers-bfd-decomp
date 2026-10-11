# Native objdiff full initialized-data comparison

`objdiff-full-data.patch` applies to encounter/objdiff v3.8.1, commit
`fba10a617154f19b3fc25c8817dc81f81d8489b5`. The source archive and patch SHA-256
are pinned in `tools.lock.json`; Cargo uses the upstream lockfile. This is a
locally maintained patch, not an upstream release. Rust/Cargo and host curl are
required for its first build. The installer runs synthetic positive and negative
native-report regressions before caching the executable and its checksum.

The opt-in `data_diff_full_section` property compares every initialized byte,
including anonymous switch tables, literals, and padding. It does not use named
symbols as section boundaries or grant a perfect section from a matching named
prefix. Equivalent MIPS `R_MIPS_32` relocations compare their final section-relative
destinations; only matching whole-field relocations mask encoded addends. Missing,
extra, or changed relocations remain mismatches. Partial-field relocations retain
upstream comparison behavior. Existing default comparison behavior is unchanged. The report fallback also
limits its assumption that completion means matching to the documented case
where no target exists. A verified target with no source candidate may be complete
without receiving fabricated matching credit. Maintained original assembly with
a verified source candidate is compared normally and may earn matching credit.

The debugger's report units enable this option. Reference disassembly also receives
original data context, so real switch destinations survive as reference labels.
No candidate symbol, section length, or generated report measure is fabricated.

The patch is independently authored; its context is from objdiff by Luke Street,
used under objdiff's MIT option. The upstream notice is retained in
`objdiff-LICENSE-MIT`. Extracted upstream sources and binaries stay ignored.
