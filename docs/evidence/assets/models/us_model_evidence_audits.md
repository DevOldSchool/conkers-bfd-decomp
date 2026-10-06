# Model evidence audits

The tools in `scripts/model_evidence/` audit source facts or derive bounded
appearance metadata. They are separate from the supported [model export
workflow](../../../model-appearance.md). Run them as Python modules from the
repository root; they do not start an emulator, acquire captures, publish assets
or establish native raster equivalence.

## Inputs and outputs

All ROM checks require the authenticated normalized US ROM. Capture tools also
require the exact reviewed inputs named by their options. Each role has a pinned
size/hash or an explicitly checked report identity; an arbitrary similar-looking
capture or successful report is not a replacement. Raw capture inputs are not
distributed with the repository. Without those inputs, use the shipped
appearance contracts for export and do not claim to have repeated the capture
audit.

Commands write new metadata/report files only. Create the destination parent
first. Outputs must not alias inputs or each other, and existing outputs are
rejected. Generated reports belong under ignored `build/`; no ROM or captured
memory bytes belong in a code change. Input provenance uses semantic roles and
hashes rather than machine-specific locations.

## Expression constructors: ROM-only audit

```sh
mkdir -p build/model-evidence
python3 -m scripts.model_evidence.audit_expression_constructors \
  --rom roms/baserom.us.z64 \
  --output build/model-evidence/expression-constructors.json
```

This authenticates complete consumer/data spans, checks source mutations and the
ordered constructor inventory, and verifies byte-identical attachment round
trips for models 15/16/18/132. It writes hashes, counts and constructor
metadata, not model payloads. See [the constructor
evidence](us_expression_attachment_constructors.md) for allocation and playback
limits.

## Scene60 and Library155 contracts

These tools authenticate the ROM and each explicit capture input before deriving
metadata. Required roles are packet, material proof, save state, screenshot,
save metadata and trace. Library155 additionally requires scene metadata and
topology. Use each command's help for the exact file options:

```sh
python3 -m scripts.model_evidence.derive_scene60_contract --help
python3 -m scripts.model_evidence.derive_library155_contract --help
```

For example, after setting the variables to your own reviewed input files:

```sh
python3 -m scripts.model_evidence.derive_scene60_contract \
  --rom roms/baserom.us.z64 \
  --packet "$PACKET" --material-proof "$MATERIAL_PROOF" \
  --save-state "$SAVE_STATE" --screenshot "$SCREENSHOT" \
  --save-metadata "$SAVE_METADATA" --trace "$TRACE" \
  --output build/model-evidence/scene60-contract.json

python3 -m scripts.model_evidence.derive_library155_contract \
  --rom roms/baserom.us.z64 \
  --packet "$PACKET" --material-proof "$MATERIAL_PROOF" \
  --save-state "$SAVE_STATE" --screenshot "$SCREENSHOT" \
  --save-metadata "$SAVE_METADATA" --trace "$TRACE" \
  --scene-metadata "$SCENE_METADATA" --topology "$TOPOLOGY" \
  --output build/model-evidence/library155-contract.json
```

Use the distinct, correctly scoped inputs for each command. Source/texture
identities and material-load/mip closure are checked against the authenticated
ROM. The Library155 `library155_raw_closure` helper additionally checks raw
task, fog and matrix evidence; it is an imported helper, not a standalone CLI.
Float-to-fixed conversion tolerance is explicit and is not raw-byte equality.
These checks do not establish captured pose, complete command-flow replay,
framebuffer blending or native appearance parity.

## Haybot ROM audit and contract derivation

The Haybot ROM audit requires the pinned capture packet as a comparison input,
but can run without a capture-audit report:

```sh
python3 -m scripts.model_evidence.derive_haybot_contract \
  --rom roms/baserom.us.z64 --packet "$PACKET" \
  --rom-report build/model-evidence/haybot-rom-audit.json
```

It rechecks source sections, run 16 state/load history, triangle commands,
descriptors, selector updater, independently decoded pixels and stored clips.
This is a ROM/packet audit; it does not reread the raw capture trace.

Producing contract metadata additionally requires `--capture-audit` and
`--output` together. The accepted capture-report SHA-256 is
`99e3b3f1b3eab6b7834718e7007ceff69a987147d2531e9513db7f6aac8ce382`. This
identifies one reviewed report, not any report whose checks pass. A newly
serialized or independently generated audit cannot be substituted for it. If
that exact input is unavailable, contract derivation is unavailable; ordinary
export using the shipped contract and ROM/packet auditing remain separate paths.

```sh
python3 -m scripts.model_evidence.derive_haybot_contract \
  --rom roms/baserom.us.z64 --packet "$PACKET" \
  --capture-audit "$CAPTURE_AUDIT" \
  --rom-report build/model-evidence/haybot-contract-rom-audit.json \
  --output build/model-evidence/haybot-contract.json
```

The standalone capture audit uses an explicit, independently reviewed file-hash
manifest plus the named input files. The manifest's expected SHA-256 must come
from that independent review; computing a digest of an untrusted manifest does
not authenticate it. File locations are supplied on the command line, never read
from the manifest or emitted in the report. Packet and trace also have fixed
source pins.

```sh
python3 -m scripts.model_evidence.audit_haybot_preserved_capture_portable \
  --manifest "$MANIFEST" --manifest-sha256 "$REVIEWED_MANIFEST_SHA256" \
  --packet "$PACKET" --quick-result "$QUICK_RESULT" --topology "$TOPOLOGY" \
  --selector-binding "$SELECTOR_BINDING" --source-binding "$SOURCE_BINDING" \
  --scene-metadata "$SCENE_METADATA" --save-state "$SAVE_STATE" \
  --trace "$TRACE" --output build/model-evidence/haybot-capture-audit.json
```

It checks capture-state/memory hashes, saved actor and selector 15/phase 5,
submitted command-range inclusion, target triangles, texture spans and matrix
conversion. Its newly generated report is an independent audit result, not a
replacement for the exact contract input above. See [Haybot appearance
evidence](../materials/us_haybot_appearance.md) for the proof boundaries.

## Review requirements

Derived metadata is not accepted merely because a file was generated. Review its
source identities, evidence scope and every changed byte before updating a
checked-in contract and corresponding exporter pin. Do not relax a digest guard
to admit different inputs. Run current unit checks and applicable ROM/export
verification after any change; report actual skips and failures rather than
carrying forward a prior validation count.
