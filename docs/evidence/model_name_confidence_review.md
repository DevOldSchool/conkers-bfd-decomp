# Semantic naming: confidence and evidence contract

These notes consolidate the naming evidence by domain. They describe authored
labels and roles, not recovered developer symbols. Registry source identity,
semantic confidence, code behavior, matching, and runtime appearance are separate
claims. Consolidation does not constitute a new visual review or ROM/build check.

The [model registry](../../config/model-semantic-names.json) owns exact
bank/entry/segment keys, source sizes and hashes, full consumer spans, descriptive
labels, and limitations. The [confidence sidecar](../../config/model-name-confidence.json)
owns their confidence classes. Both complete files are independently byte-pinned
by [the resolver](../../scripts/model_semantic_names.py). Evidence-link maintenance
must update the registry pin and sidecar record bindings without altering labels,
source identities, consumer mappings, limitations, or classifications.

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

264 of the 267 records have gallery rows; bank-01 entries 154, 155 and 162
instead use direct appearance evidence. Gallery wording, categories, and reference
links are provenance, not individual human-confirmation receipts.

## Resolver and coverage contract

`config/model-name-confidence.json` is independently byte-pinned by
`scripts/model_semantic_names.py`. It binds every exact bank/entry/segment to its
source size, both model hashes and a SHA-256 of the complete source registry
record. That record digest uses sorted-key compact UTF-8 JSON with
`ensure_ascii=False`; it includes the original label, evidence and limitations.
The sidecar also binds the source registry-file digest and ROM identity.
Missing, extra, duplicate, stale or malformed classifications fail closed.
No private audit paths or gallery-provenance payloads are copied into the sidecar.

A successful lookup returns the class as `status`, a separate
`semantic_identity_status`, and `semantic_identity_confirmed: false`. The
`descriptor` holds the retained wording. For compatibility, `name` is an alias
for this legacy descriptive label, explicitly marked by
`kind: legacy-descriptive-model-label`; its presence is not confirmation.
Human and qualifier confirmation are each reported as `not_individually_audited`.
The unknown-model response is unchanged.

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

## Identity, provenance and reproduction

All ROM evidence refers to the normalized 67,108,864-byte US ROM, SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, SHA-256
`32e6a8b970ec12ac5f782344945aa0c98a193832eefb687529d03bab6948714b`.
Independent audits compared complete registered spans, including branches, delay
slots and terminal padding, to original ROM/reference bytes. A candidate
compilation is not an independent reference. Full source-record and consumer pins
already in the registry are not repeated in each domain note.

Visual provenance joins an actual preview manifest's numeric bank/entry/segment
to independently decoded ROM bytes and canonical inspection/validation records.
Explicit equivalent-root mappings select available ROM-only exports without
changing configured paths. glTF buffers/images and reviewed renders were
fingerprinted. Filenames, sheet captions, neighboring IDs, or external
decompilation name lists supply neither numeric nor semantic authority. Existing
canonical public-reference links are inherited provenance; unless stated otherwise,
these reviews did not inspect fresh public-reference pixels. ROM-only previews
are not native frames, and absent captures were not replayed.

The common registry validator rejects unknown/missing fields, duplicate JSON
keys and numeric identities, Boolean/noninteger indices, unsupported banks,
invalid sizes/digests, empty/nonrelative evidence paths, and conflicting consumer
spans. An optional model-specific branch must identify its model and fit in its
complete declared consumer; only Haybot entry 75 has one. Every listed bank is
audited; unrelated banks, entries and segments remain unknown even for equal bytes.

Run the current source/consumer audit with an owned reviewed ROM:

```sh
python3 -m scripts.model_semantic_names --rom roms/baserom.us.z64
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s tests -p 'test_model_semantic_names.py'
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s tests -p 'test_model_name_confidence.py'
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s tests -p 'test_model_coverage.py'
```

The [contribution rules](../../CONTRIBUTING.md#acceptance-and-integration) own C
matching and integration gates. Naming does not add C matches or source-unit
credit. Roles may be comments on raw functions or disabled candidates; their
status remains authoritative in the inventories. Numeric linked symbols,
source-local layouts, ABI widths, executable operations and candidate guards
are not changed by a descriptive interpretation. Source inverse checks and
bounded instruction harnesses support scope, not runtime activation.

The independent reference instruction-word comments have an unrelated gap at
`150A9C40..150AA470`; none of the renderer/representation audits crosses it.
Their full original reference-binary equality was checked separately.

## Supporting full-span provenance

The following original-ROM support spans are not consumer entries in the model
registry. The recorded extents are registered unless explicitly marked
reference/raw body; the latter are not source-boundary registrations. Repeated
pins have been collapsed. These retain the original audits' provenance rather
than claiming a fresh current-checkout verification.

| Symbol | Bytes | SHA-1 or SHA-256 | Extent exception |
| --- | ---: | --- | --- |
| `func_150028BC` | 1668 | `cffdfd5fb609badb5d60111edaf1c040c4e727cc` | reference/raw body |
| `func_1500390C` | 164 | `db44c54f402b6ef45a864efe5de985d4751f69c2` |  |
| `func_150045C4` | 992 | `37dee925089b4581e1686a4aabefd610ad02694f` |  |
| `func_15004A4C` | 96 | `87f97f9b889fba82269bb7776e8200310b5fecf8` |  |
| `func_15004BF0` | 240 | `15e1c9c9fc16add33571bf01d2bac5efc1a896a6` |  |
| `func_15007B3C` | 1704 | `5897d750e22cca5cfd3807a70361042faaf11c86` |  |
| `func_15019130` | 740 | `3a4612c396cab4d5fea684c240da2c509477bdac` |  |
| `func_150195A0` | 860 | `387af6476d77ef09b7b3251fc9c3743cdcadf0e0` |  |
| `func_1502460C` | 8128 | `363af55b580310f7cfa3dee99c50a0065274dffd` |  |
| `func_1502AC88` | 636 | `24f02469c9605e212ed65a4c75b216d50ef8577e` |  |
| `func_1502AF04` | 284 | `b8f786b34a0b0f6db12c039c68a860a08bd52d1b` |  |
| `func_1502B020` | 240 | `cf808816ca9e3df778eb77490c317e7eb4b57c02` |  |
| `func_1502B110` | 276 | `34a60e9d42e7e0e2a914bc3a2f37c13d0aba4f8a` |  |
| `func_1502B4A8` | 288 | `d1a82190ae64677a9404302b5a61653a5770a7dc` |  |
| `func_1502B6BC` | 308 | `91ed9cccb2168331f871d0b5b3597f9cfc8f558f` |  |
| `func_1502C6E8` | 652 | `a168f14ac1b2fe5bb064d8e6194c3b486dc00023` |  |
| `func_1502C974` | 704 | `166b05f7f97b828a9ebad3c9a7e51e8a6b748eea` |  |
| `func_1502CC34` | 200 | `c4fa4d82300818f349512dcc7d9a8cbba96d026a` |  |
| `func_1502D824` | 764 | `e4854df5924f1d8f104a242c76187da4401a88b2` |  |
| `func_1502DB84` | 948 | `a2c545e39bfb534f09979e2d431919fedbe62f20` |  |
| `func_1502EE8C` | 104 | `39abe4f6339af44beba31d4d2ab7603b2530ff22` |  |
| `func_1502EEF4` | 296 | `2da422b7989f9b16b67dc448f60332131031e4f0` |  |
| `func_1502F9FC` | 492 | `cf59732557feef6b94d12cf90dc99c728f582097` |  |
| `func_1502FBE8` | 392 | `86363abf6467595cc9d78c3c1b6577bb4374835f` |  |
| `func_1502FD70` | 160 | `d88f7df50a833ec02f2c1086371360004e018238` |  |
| `func_15030F94` | 220 | `244e8f3ea6dd995d239f1b7a561547fa9eb94543` |  |
| `func_15035FE8` | 352 | `9cc4055fa7f2aaa872df8f2b0af7f5865cf0e11f` |  |
| `func_1503D368` | 208 | `abef1711e0dda14ca8b45eb3689aa144f101bb5f` |  |
| `func_1503D438` | 36 | `add9aec5cb5ff6df58ba80704156c1463b4a2071` |  |
| `func_1503D484` | 140 | `40f757370bbf19e10e675591d24421010455453d` |  |
| `func_1503D510` | 224 | `fcd02fbf98cbada218432bd315b28508048f85d0` |  |
| `func_1503D5F0` | 112 | `6b19502694fdcbcee75fc751b4d136adc57685df` |  |
| `func_1503D660` | 276 | `698addad07c12e755805e484a22441109dd90252` |  |
| `func_1503D774` | 144 | `546821f215679e4d341cd39d98c9a9d6256110d2` |  |
| `func_1503D804` | 384 | `486bab26201a574421a430fed7e156346e60b68e` |  |
| `func_1503D984` | 184 | `56cdd8e4b82b2a4222f4e661e22b08cdca30d293` |  |
| `func_1503DA9C` | 416 | `c45efcf48e1487e1c0401c7592c959cd2ddb6898` |  |
| `func_1503DC3C` | 224 | `4d0a13f114d5f3ecad9c56068bdde74a052935af` |  |
| `func_1503DD1C` | 180 | `8488f03d16dd306923361422c315a5db5ec5c746` |  |
| `func_15042D78` | 28 | `38fc2a649e741f130d03ae9158e9b5e15fb80981` |  |
| `func_15042D94` | 168 | `a2b953e07350ede14afc773966ea4f658dec1f91` |  |
| `func_15042E3C` | 144 | `66a68b65b070ce34fad5125d65ab84433be65a38` |  |
| `func_15042ECC` | 1008 | `79a05875c18667f06098187ba5cffc5a58463bbc` |  |
| `func_150432BC` | 16 | `2bdb9d828c000138badbbc7a8f8650dc01738ea5` |  |
| `func_150432CC` | 48 | `5f0352a1700b304bb94dedc6f389d046e3800498` |  |
| `func_150432FC` | 48 | `f10d1c316b6cbc684d92a840f3f2cf86d8bfdecb` |  |
| `func_1504332C` | 88 | `1d976bd9d669e23482346fac2b64b57bdc64041f` |  |
| `func_15043384` | 1660 | `7cac7bc6fe71941e6513d45d18caf1b83f99dc02` |  |
| `func_1504A730` | 1696 | `cc2b08465267b571c76efcafa9a65573047775e6` |  |
| `func_1504ADD0` | 292 | `4af7dbe53fe4c060205be766f8efb2afd7b39701` |  |
| `func_1505E0C4` | 1420 | `3e17bb649f54edb53a448676e71fbea0adce0e10` |  |
| `func_1505E650` | 380 | `7ff7faebb700286719b32f4b7390b9c9f772236b` |  |
| `func_1505F188` | 272 | `c4b6d2297e2dc2c7f3c7c5724781e9042b9d3204` |  |
| `func_150627D4` | 44 | `c3fd4d04b4ecfd0f07acb2628b040150aaf7709b` |  |
| `func_15065A5C` | 19348 | `7f60cbcdfdc421e08122fd361bcebabd913da9dc` |  |
| `func_150791F0` | 56 | `4211581561b3dcc5ec600d3a413aacdf8c7b49a4` |  |
| `func_1507BC14` | 412 | `e04f71fcd2150534ad374b1be8b77050eb1be2bd` |  |
| `func_1507E2B0` | 272 | `25c3adf8ab6e48111023c6f0a7dfcb74cbdb2f80` |  |
| `func_1507E500` | 200 | `a2a542a0b6aea78ccbc269507a5ee977e6443ccf` |  |
| `func_1507E6B8` | 132 | `059fe16ca29114f79874eb5bba055de0c5c3b12c` |  |
| `func_1507E73C` | 168 | `9454da6931491edc5fb0cca9ea911b19f6ac70e8` |  |
| `func_1507E7E4` | 292 | `064a319797f11d4c28456b90634bb51481889bcc` |  |
| `func_1507E908` | 96 | `c602e20a2b335d94feb349539cbdb76d69957d50` |  |
| `func_1507E968` | 128 | `94fb99b2aabedd05d7d1404d8013af047b86a5af` |  |
| `func_1507E9F8` | 76 | `31fcadb16432eb6925dc6fcf17d561857102493d` |  |
| `func_1507EA44` | 120 | `c4818df6a7fca422de2d463163d68866d05b090f` |  |
| `func_1507EABC` | 112 | `27ec4fab9d1d702ca425ce9c513356ac032b71e8` |  |
| `func_1507EB2C` | 32 | `cb97140a9e2b5a1832f8869e6c2b105743ab4ab9` |  |
| `func_1507EB4C` | 52 | `0bea04c46acdb0648becca735aff57ee5f402765` |  |
| `func_15083AC8` | 728 | `03be5dc12ab3c26e354c7a830572be800c3b9dc6` |  |
| `func_15084044` | 776 | `f738e7d7f7530302ba4dade50252079f56071472` |  |
| `func_15084488` | 208 | `73e99fd512f1d521f6620a98947843257844411d` |  |
| `func_150849A0` | 44 | `62d89a7ec36b39096dfd2c98896619b96b71866a` |  |
| `func_150849CC` | 76 | `f406a1972f5f0f73bdcce7b9fb373af650daf567` |  |
| `func_15084D00` | 112 | `ff9dc54618c437070a653923b6cedc81f1484759` |  |
| `func_15093818` | 96 | `1142c92237dec6384ab2461097c44dc21bba37e5` |  |
| `func_15097A8C` | 8584 | `652bb7dc25c580be9d73f138b68687333da7ce6d` |  |
| `func_150A7A48` | 312 | `50a10c8988bdedf7c044f28a9c22e9edbb43e1c6` |  |
| `func_150A7CB0` | 80 | `9b41e5a7ae2b80ac7139471fe9dcc4016d16937b` |  |
| `func_150A8050` | 336 | `9d826a49f8529b88a58d6e5c9455f61c87f6244c` |  |
| `func_1510D374` | 144 | `b56e9f67e46ac44069b229680a76dde3e42baba0` |  |
| `func_1510D608` | 40 | `c8d0d9a81517e56fbe70ad2b5c00e8faa8e19a83` |  |
| `func_1510D864` | 16 | `3a6d8325150a08f6fe3ea9f0ea7dc37235ac6db4` |  |
| `func_1510D8C0` | 176 | `93a912bad5e9ddc0bebe3f683c48b2a06d31a773` |  |
| `func_15113180` | 152 | `240ebd2300a14589b1a43df6572d0d161014fedb` |  |
| `func_15113218` | 940 | `0eaadfc90c71ef62b8d64a04db07167432812e90` |  |
| `func_15114050` | 116 | `9b5c4e91d95b8961111576d69dcdcf1af92f2cb9` |  |
| `func_151140C4` | 196 | `d32672c225acb89d77c3adbadbb2261e3fd7d58a` |  |
| `func_151148A8` | 100 | `982eaba37b6c1dba097b1c79a4acafeb014eead9` |  |
| `func_1511490C` | 160 | `629429fa4dce5a8dfb8eab6df18755a557d07775` |  |
| `func_151149AC` | 112 | `a831c20eb614451ce4fc3c1acbd67b004a69cf0a` |  |
| `func_15134070` | 252 | `87c6650f4d53ddcc1a52b24bcf502d38175637e9f42275f90d9046895338e5a6` |  |
| `func_151380B4` | 108 | `7fb98757d8bef9d592831be2ec68857e43f6234a` |  |
| `func_15141C0C` | 180 | `94e412a0d3fc5d286a38dfc6d4cab08ce7bfa4dd0c1a82fa8d912dab0c0c0c8d` |  |
| `func_15141DA4` | 148 | `1c3bdd2386e3f79123844688a5a63b02ef766dd60bd06faa03bdd0758527640a` |  |
| `func_15149130` | 196 | `59e729dd3894013d736f5be8800f6150cc222cfd` |  |
| `func_151491F4` | 112 | `1005ff2639fcb1610f3923942a985db537659dcd` |  |
| `func_15149264` | 180 | `2db6209a1a8c9a38d88fa0ec61fe95b84b0bbea2` |  |
| `func_1515D914` | 2404 | `a0ca1f285c354276fa25543fe54a68ef023f1813` |  |
| `func_1517AD00` | 2048 | `a16226b408961566109c7c0088fd15ae34c76f1c` |  |
| `func_15184FA4` | 1200 | `87e9098d44db54c3a41260244ceea5997557bd69` |  |
| `func_151897A4` | 284 | `2412bfe0600cf8fe34f5f15008a364d76bd80464` |  |
| `func_15194B1C` | 120 | `967fd90bccec5f4df296d293e57419c446139520bc0956fc05f86a76767b5d89` |  |
| `func_151B01B8` | 512 | `a90836585e44bade9aa06afdd5023793100ede7f90409175573ca66279c83611` |  |
| `func_151ED430` | 1244 | `900522a88e522f04c6834172be22b92ee7cfe7cd` |  |
| `func_151EDB58` | 132 | `b4ca5861b440d0051774f539120029dfae355c43` |  |
| `func_151EEBE8` | 1032 | `da2a4cf8dc9ed491c7637a6e9f7aef16c878dab43c4b5c66eee435c904a13722` |  |
| `func_151EFD00` | 256 | `8c96268b9cafd0f7e12c9df375e2feadda57a659` | reference/raw body |
| `func_151EFE00` | 136 | `7c13fb05d050330f14f1bfea0340c49362420b40` | reference/raw body |
| `func_151EFE88` | 48 | `fef97dc8413dff2d4e193eb0791fb9cc5ed1a906` | reference/raw body |
