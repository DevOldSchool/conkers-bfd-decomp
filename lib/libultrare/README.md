# Rare-modified libultra objects

This directory builds the eleven complete Rare-modified libultra objects
identified in Conker's US main executable. The bounded source and header
snapshot comes from n64decomp/007 revision
`c4356466796c697dfd298010b9bed261f9ed8c6a` and retains its US IDO 5.3 flags.

Only objects whose complete text and allocated non-text sections are mapped in
`docs/evidence/libultrare_us_additional_object_bounds.md` are included. The
checked-in MD5 list is the upstream project's accepted US object output and is
verified before the archive is staged for the Conker link.

This is deliberately separate from the pinned Nintendo `lib/ultralib`
submodule: these members are Rare variants and must not be represented as stock
SDK objects.
