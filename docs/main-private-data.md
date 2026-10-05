# Reviewed main initialized data

A private initializer needs independent storage ownership and ROM evidence,
as well as matching text. `config/main/private-data.json` contains reviewed
mappings; `scripts/main_private_data.py` supplies focused comparison and build
verification through that same contract. It supports initialized `.data`,
`.sdata` and `.rodata` sections whose emitted bytes need no relocations.
Private BSS, pointer initializers and GP-relative relocations require separate
reviewed support.

For a new mapping, first document original instruction accesses, original data
boundaries, source-unit ownership and the checksum-validated US bytes under
`docs/evidence/`. A low diff score or a zero-filled region alone proves none
of these. Normal matching scope prohibits editing this shared manifest to force
a match; obtain a task scope override for a reviewed integration change.

Each unit records raw/completed `sources` aliases, an `evidence_reference`, and
`sections`. Each section records its compiler `input`, unique INFO `output`,
hexadecimal `vram` and `rom_offset`, full emitted `size`, power-of-two
`alignment`, ELF `flags` (2 read-only or 3 writable allocated input; `.sdata` also
permits writable MIPS GPREL flags `0x10000003`), and the
SHA-256 of the entire original ROM payload, including compiler padding.
Current main mappings require `vram = 0x80000000 + rom_offset`. Duplicate aliases,
outputs, inputs, overlapping ranges and missing evidence fail closed.

Focused proof consumes actual candidate sections at the reviewed addresses,
leaves their defined symbols for natural linker resolution, and independently
links the raw reference. Both full registered text spans must equal original
ROM bytes. Comparison-only MIPS ABI metadata is excluded from the linked proof
image to prevent orphan metadata from overlapping reviewed small data; neither text nor
initialized storage is discarded. Candidate and reference objects remain
unchanged. Unmapped emitted storage is rejected, and same-unit text/layout checks remain in force.

Build generation chooses only the exact active source object. INFO sections
carry no second runtime allocation; existing allocated main bytes remain the
ROM backing. Verification checks ownership, mapping metadata, original payload,
allocated backing and every linked text byte of the entire reviewed unit.
`finish`, integration and clean `verify-batch` remain required, including the
whole-US-ROM comparison. A manifest entry does not itself mark a match.
