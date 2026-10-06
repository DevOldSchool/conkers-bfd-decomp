# Model material coverage

Coverage distinguishes static ROM texture availability, optional inspection
presets, runtime observations, extraction and visual validation. It does not
infer appearance acceptance from a texture filename or a preview manifest. The
active ROM target is US SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`.

## ROM consumer fallbacks

Coverage recomputes the exporter's guarded material policy, rather than calling
only `choose_preview_texture`. It loads checksum-validated consumer contexts,
applies the attachment/UI/special material updates, and follows object state-
consensus, animation, binding, scene and particle texture fallbacks. The final
texture-enabled/coordinate-proof guard remains required. Preview material status
and texture filenames cannot independently grant resolution.

Both original and material-updated geometry must retain source faces,
face-command identities, vertex positions/colours/flags and material-run face
spans. Authorized UV updates are allowed. Material resolution uses updated runs
while runtime, composition and report accounting keep full-source run
identities. Static ROM coverage does not depend on optional runtime observation
catalogs.

## Optional character inspection presets

The keyword-only Python option `rom_character_presets=True`, exposed by
`--rom-character-presets`, adds a separate bank01 `rom_preset_texture`
dimension. It is off by default. Every preset row carries full-source face
indices, not compacted primary-preview indices. A selected preview's source
hash, exact face mapping and selected count are verified against freshly parsed
ROM geometry and reconstructed primary draw selection. A primary preview can
therefore contain fewer faces than its complete source model without becoming
invalid.

Schema version2 adds weighted static face counts and optional weighted preset
counts. Existing full-source totals keep their meaning. Secondary-only material
rows excluded from a primary preset remain explicit; missing export roots leave
extraction and Blender evidence absent, even if static texture data is complete.

## Reproduction

```sh
./conker model-assets coverage \
  --output build/assets/models/us-coverage.json
./conker model-assets coverage --rom-character-presets \
  --output build/assets/models/us-coverage-with-presets.json
./conker model-assets batch

PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s tests \
  -p 'test_model_coverage*.py'
```

Use authenticated local ROM and texture inputs as described in the [appearance
guide](../../../model-appearance.md). The normal CLI uses the integrated ROM-consumer
contexts; no development import bridge or capture input is needed. Generated
reports remain under ignored `build/` paths.

Tests exercise fallback order and coordinate vetoes, source-domain preservation,
primary hash/mapping/count mutations, duplicate/out-of-range/cross-run indices,
sparse primary indices and forged preview statuses. The CLI option cannot enable
presets for commands other than coverage. Run the checks on the current checkout
and report actual results and dependency-gated skips.

## Interpret the measurements separately

- Static `missing` means no PNG resolved under the guarded policy. It is not proof
  that a texture or capture is required: some known combiners never sample TEXEL
- The batch material backlog is combiner-aware, so it can be smaller than the
  static missing-PNG count
- Full-source faces include faces omitted from an ordinary preview. Compare them
  with exported faces only after applying the same source mapping and omission
  policy
- Optional ROM character presets cover selected source faces. Their resolved
  counts are a separate scope and must not be added to static availability
- Runtime coverage is existential within the supplied corpus. It does not prove
  every state was observed, all source faces were submitted or an event ran
- Constructor requests are metadata inventory. Five expression action programs
  contain six ordered requests for four attachment models; these do not add
  resolved faces, observed instances or animation playback
- A material-complete export still needs independent visual review. Texture,
  colour, transforms, lighting, blending and framebuffer parity are separate
  claims

For the currently guarded bank09 consumers, the source scopes are entry 162: 108
faces, entry 164:65, entry 165:65, entry 185:170 and entry 203:20. The proven
consumer bindings cover all faces of 162/164/165/203 and 112 of entry 185's170;
entry 185's58 external-texture faces remain outside the new bindings. These are
bounded consumer facts, not a global current-backlog certificate. Regenerate the
coverage and batch reports after exporter, contract, catalog or source changes.

## Verified default material backlog

On **1 October 2026**, fresh previews from the authenticated ROM and all six
texture catalogs reproduce **25 models, 54 runs and 933 faces** under
`model_batch.missing_material`:

| Bank | Affected models | Material runs | Faces |
| --- | ---: | ---: | ---: |
| 01 | 4 | 32 | 594 |
| 03 | 2 | 2 | 38 |
| 04 | 5 | 5 | 168 |
| 09 | 14 | 15 | 133 |
| Total | 25 | 54 | 933 |

This is the default export's combiner-aware backlog. Explicit capture-scoped
presets remain separate and do not silently reduce these counts. It is not the
static missing-PNG count or a full native appearance/visual-validation result.
Recompute from fresh bank previews with `./conker model-assets batch` after
changes rather than treating these dated counts as permanent acceptance gates.
