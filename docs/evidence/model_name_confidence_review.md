# Model label confidence correction

This correction preserves the original 267-record registry byte for byte
(SHA-256 `b4ebcee9f60a2eb345ea6de56055ffa1b4ce5912e6a59a47605daed6a1caf364`).
It adds no identities, families, model labels, consumer mappings or runtime claims.
The count is source records, not distinct characters or newly discovered names.
264 records already had gallery rows; the other three are appearance-only bat
records (bank 01 entries 154, 155 and 162). Existing gallery text, categories and
reference links are provenance, not individually recorded human confirmation.

The exact-key confidence sidecar classifies all 267 records:

| Classification | Records | Meaning |
| --- | ---: | --- |
| `earlier_reviewed_character_label` | 17 | Earlier character-label review is retained; this correction does not establish an individual human-confirmation receipt |
| `historical_character_label_pending_confirmation` | 74 | Historical character/family wording is retained, pending individual confirmation |
| `appearance_only_description` | 176 | Appearance description only; proper or gameplay identity remains unknown or inapplicable |

These are record-level classes, not a census of distinct characters. Multiple
models, variants and subparts must not inflate novelty or character counts.
Prior recognition of a character or family does not confirm an outfit, color,
variant, subpart, alternate identity, LOD, state, scene or role qualifier. Such
qualifiers remain separately unconfirmed in every class. Existing MODEL enum
spellings inherit the corresponding record's classification; an enum spelling
supplies no additional identity or confirmation evidence.

## Resolver and coverage contract

`config/model-name-confidence.json` is independently byte-pinned by
`scripts/model_semantic_names.py`. It binds every exact bank/entry/segment to its
source size, both model hashes and a SHA-256 of the complete original registry
record. That record digest uses sorted-key compact UTF-8 JSON with
`ensure_ascii=False`; it includes the original label, evidence and limitations.
The sidecar also binds the original registry-file digest and ROM identity.
Missing, extra, duplicate, stale or malformed classifications fail closed.
No private audit paths or gallery-provenance payloads are copied into the sidecar.

A successful lookup returns the class as `status`, a separate
`semantic_identity_status`, and `semantic_identity_confirmed: false`. The
`descriptor` holds the retained wording. For compatibility, `name` is an alias
for this legacy descriptive label, explicitly marked by
`kind: legacy-descriptive-model-label`; its presence is not confirmation.
Human and qualifier confirmation are each reported as `not_individually_audited`.
The original unknown-model response is unchanged.

Coverage counts the three confidence classes separately, reports zero confirmed
semantic identities under this reviewed contract, and records the confidence
sidecar's SHA-256 among its input hashes. CLI output describes source-verified
model-description records and confidence counts rather than “verified names.”
Model/ROM hashes verify source identity; consumer hashes and conditional roles
verify bounded code mappings. Neither establishes semantic identity, exclusive
actor ownership, successful creation, runtime activation, visibility or unused
status. No runtime or appearance revalidation is implied by this correction.

Production loaders retain independent immutable byte guards. Unit tests with
synthetic model or ROM payloads explicitly construct matching in-memory
classifications and run the same structural and binding checks; there is no
production fixture bypass or opt-out flag.
