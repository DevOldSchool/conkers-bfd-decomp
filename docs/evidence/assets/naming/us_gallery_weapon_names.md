# Gallery weapon identification

Visual review on 2026-10-04 maps the nine gun types in the supplied
[Deathmatch weapon list](https://conker.fandom.com/wiki/Deathmatch#Weapons)
to the ROM model gallery. Crossbows are included as a separate ranged-weapon
family. These are appearance-based identifications, not recovered developer
symbols or independently established gameplay mappings.

Bank numbers are hexadecimal; padded entry and segment numbers are decimal.
All IDs below use segment `00`. Stable render cases, filenames and source IDs
are retained. Earlier gallery labels remain searchable as `Former label` aliases.
The [inspection configuration](../../../../config/model-inspection.json) owns these
visual labels; the byte-pinned semantic registry and confidence sidecar are
unchanged. Neither consumer evidence nor historical registry wording is upgraded.

## Identified families

| Weapon | Bank 01 | Bank 03 | Bank 09 | Visible distinguishing evidence |
| --- | --- | --- | --- | --- |
| [Bazooka](https://conker.fandom.com/wiki/Bazooka_(Bad_Fur_Day)) | | 0058 | 0062 (review only) | Green tube, ring sight, silver top and yellow/black band; the public Bazooka render matches 03:0058. Entry 09:0062 has the same distinctive palette and launcher silhouette, in a shorter stored mesh. |
| [Rifle](https://conker.fandom.com/wiki/Rifle) | | 0054 (compact), 0092 | 0101 | 0054 has the compact receiver, stock, short silver muzzle, magazine and sling shown in the Heist gameplay references. 0092/0101 have the longer M16-style carrying handle, perforated barrel, magazine and stock. |
| [Sniper Rifle](https://conker.fandom.com/wiki/Sniper_Rifle) | | 0086 | 0077 | Long silver barrel, dark stock, scope and red upper fitting. |
| [Flamethrower](https://conker.fandom.com/wiki/Flamethrower_(Multi)) | | 0059 | 0048 | Broad nozzle with hazard band, long black body and pale underbody bottle; matches the multiplayer firing screenshot. |
| [Submachine Guns](https://conker.fandom.com/wiki/Submachine_Guns) | | 0057 | 0026, 0027, 0107 | Short rectangular receiver and muzzle, long curved magazine: the Uzi-shaped form. Attachment letters distinguish records, not left/right hands. |
| [Shotgun](https://conker.fandom.com/wiki/Shotgun) | | 0094 | 0103 | Two parallel dark barrels with brown rear stock. |
| [Revolver](https://conker.fandom.com/wiki/Revolver) | | 0083 | 0065 | Cylinder, long silver barrel, upper scope and curved grip. The original manual calls this family Hand Cannon. |
| [Machine Gun](https://conker.fandom.com/wiki/Machine_Gun) | 0138 | | | Two perforated barrel jackets, yellow ammunition belts and green housing match the mounted gun in the public gameplay images. |
| [Tommy Gun](https://conker.fandom.com/wiki/Tommy_Gun) | | 0093 | 0095, 0127 | Stock, magazine, forward vertical grip and long barrel. A fresh side view resolves the misleading default orientation of 09:0095. |
| [Crossbow](https://conker.fandom.com/wiki/Crossbow) | 0029, 0047, 0110 | 0061, 0107 | Transverse limbs/string, bolt and stock. Bone and wooden forms remain separate source records. |
| [Katana](https://conker.fandom.com/wiki/Katana) | | 0082 | 0058 | Curved silver blade, orange circular guard and brown/orange diamond-patterned grip match the N64 render. |

The original configuration update covered 24 curated records, including existing obvious labels
that previously lacked reference provenance. The 09:0062 review model is recorded
here, without promoting its acceptance state or adding a new curated export.

## Remaining candidates and related equipment

| ID | Retained gallery description | Finding / next discriminating evidence |
| --- | --- | --- |
| 01:0018:00 | Mounted weapon with beams | A mounted twin-barrel gun with two pale beams; similar family to 01:0138. Exact weapon, beam purpose and runtime relationship remain unresolved. |
| 01:0078:00 | Twin gun barrels | Two detached dark barrels. Do not assign them to the mounted gun or beehive from neighboring IDs. |
| 09:0146:00 | Firearm attachment 4 | Rigged firearm with five joints; neutral joint state collapses the recognizable gun silhouette. It shares the exact linked image set of the visually identified compact Rifle 03:0054, supporting a candidate relationship, not proving semantic identity or the assembled pose. Requires an evidenced assembled pose. |
| 09:0147:00 | Black weapon attachment - first texture preset | Another five-joint firearm, with a collapsed neutral pose and two texture alternatives. The guarded action-70 preset proves material selection, not weapon identity. Requires an evidenced pose and comparison of both texture presets. |
| 09:0087:00 | Compact firearm | A shallow black receiver/barrel form. Uzi-family appearance is a candidate, but the defining magazine/grip is not visible; leave unnamed. |
| 03:0070:00; 09:0060:00 | Black-and-green tube prop; Green launcher | Shared black tube / green grips appearance. Bazooka-family candidate only: their geometry differs from the clearly identified hazard-striped Bazooka. No identity inferred from colour alone. |
| 09:0047:00 (review only) | Bank 09 / 0047 / 00 | Green two-port attachment. Weapon association is unresolved. |
| 09:0102:00 | Dark rectangular case | Brown-ended dark form, visually related to the Shotgun; shares its six linked texture images and 57-triangle count with 03:0094. Stored pose/source relationship must be resolved before assigning a weapon or receiver role. |
| 09:0277:00; 09:0280:00 (review only) | Single-eye gun turret; Bank 09 / 0280 / 00 | Turret and elongated perforated metal component. Do not substitute either for the Deathmatch mounted Machine Gun without assembly/consumer evidence. |

Paired fuel containers (03:0071, 03:0100, 09:0061), armed beehive 01:0035,
tanks, missiles and detached ammunition remain related equipment, not additional
gun types. Their existing descriptions and categories are preserved.

## Review and reproduction

Reviewed the current curated and extracted-review thumbnails for banks 01, 03
and 09, with close views of the ambiguous firearm exports. Public references
were inspected as article text and available N64 renders/gameplay thumbnails;
no third-party model or texture payload was imported. The original
[N64 manual](https://www.videogamemanual.com/n64/Conker%27s%20Bad%20Fur%20Day%20%28USA%29.pdf)
was visually reviewed, particularly printed pages 15-16 and 24-25. It provides
alternative vocabulary (Machine Guns, Semi-Auto Rifle, Turret Gun, Hand Cannon),
not numeric model IDs. Later Xbox renders and promotional art do not establish
an N64 asset match.

Local per-record source/dependency/preview fingerprints, source-manifest identity
and the before/after labels are retained under
`build/assets/models/reference/weapon-identification-20261004/`. Additional left
views of 09:0095, 09:0146 and 09:0147 were rendered from existing ROM exports;
no mesh, material, pose or source data was altered. Neutral-pose diagnostics of
146/147 did not resolve identity. Equal face counts or shared textures alone
are not mesh-equality, actor-ownership or semantic proof.

This review does not re-decode the entire ROM or validate native rendering.
Existing ROM/source evidence, materials, rig, visibility, lighting, alpha,
placement, animation and native-appearance limitations remain in force.

Recheck gallery metadata and regenerate through the existing publisher:

```sh
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s tests -p 'test_model_inspection_names.py'
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s tests -p 'test_model_inspection.py'
./conker model-assets inspect --inspection-config config/model-inspection.json
```

The publisher independently rechecks current validated source fingerprints and
preview hashes. A failed publication is a blocker, not a reason to rewrite
validation reports or weaken acceptance.

## Publication result

The metadata scope audit confirmed exactly 24 changed records; all 895 other
inspection records and all non-label fields remain unchanged. The 14 existing
gallery tests and whitespace checks passed.

The main checkout now contains the reviewed configuration and this report.
The existing main gallery's `manifest.json`, `index.html` and `README.md` were
updated for exactly these 24 records (19 guns and five crossbows). The page uses
the existing gallery renderer. Old labels remain searchable aliases and each
identification retains its appearance-based reference.

Before and immediately before publication, all 3,030 existing model, download
and preview files were hash-checked against the original published manifest.
Their bytes remain unchanged. Each of the 24 weapon sources also passed fresh
source/dependency fingerprint, ROM source identity and GLB packaging comparisons
against the previously reviewed records. All other published metadata,
acceptance states, provenance records, counts and extracted-review records remain
unchanged. This is a presentation metadata update to the existing publication;
it does not admit newly generated source assets or assert fresh full-corpus
validation. The main gallery retains 893 curated and 623 review cards.

The full asset refresh remains a separate blocker. Its stale assembly export
was regenerated through `./conker model-assets scene-assemblies`, producing the
44 currently configured scenes. The subsequent authoritative
`./conker model-assets validate` stopped with
`ROM guarded model proof differs: rom_ui_material_state`. The failed report
is retained. No verifier, validation report or existing regression baseline was
edited to accept that disagreement. Configured animated character66 and scene55
Blender artifacts were also generated and passed their existing checks; they
were not substituted into the existing main publication.

Local evidence includes `main-publication-baseline.json`,
`main-publication-result.json`, the bounded
`update-main-gallery-metadata.py` script and `main-gallery.jpg` under the review
directory. Browser verification of the main gallery's All models tab and `guns`
search showed 19 of 1,516 cards with the expected names.

The main gallery is at `build/assets/models/inspect/index.html`. A dedicated
weapon gallery also remains at `build/assets/models/inspect-weapons/index.html`;
it was generated with the original publisher's source, ROM, image and packaging
checks, scoped to the same 24 records. Its reproduction selection remains in
`build/assets/models/reference/weapon-identification-20261004/inspection-config.json`.

## Weapons category

The main gallery now has a dedicated Weapons tab. The category contains 50
existing curated records: all 24 guns/crossbows from this review plus 26 already
described weapon props, including unresolved firearms, mounted weapons, knives,
swords, chainsaws, grenades and projectiles. Grouping does not resolve the exact
identity or gameplay role of an unnamed firearm. Existing labels, references,
uncertainty notes and model IDs are retained.

`config/model-inspection.json` assigns the category explicitly, and the publisher's
category registry renders the tab and supports future full regeneration.
The 50 records moved from Scene items (44) and Parts & effects (6); All models
still contains 1,516 cards, and extracted-review decisions remain unchanged.
The dedicated 24-record weapon gallery was updated consistently.

This follow-up changes only category assignments and category presentation.
All 3,030 published main-gallery asset files and 48 dedicated-gallery asset files
were checked against their previous hashes before publication and remain
unchanged. The 14 existing inspection tests and whitespace checks passed.
Browser checks confirmed 50 cards on Weapons, 19 gun results within that tab,
and no console warnings or errors. The local category baseline, target IDs,
publication hashes and screenshot are retained under
`build/assets/models/reference/weapon-tab-20261004/`.

## Katana and compact Rifle follow-up

User-supplied gallery screenshots prompted a closer comparison of 03:0082 and
03:0054. The Katana article's N64 render visibly matches the curved silver blade,
orange circular guard and diamond-patterned grip of 03:0082 and 09:0058. Both
records are now named Katana; the second retains its attachment qualifier.
The Xbox Katana image was not used as identification evidence.

The earlier firearm pass relied on the Rifle page's M16-style render and left
03:0054 unresolved because its stored shape differs. The same page also includes
Heist gameplay images, notably [Weasel holding a rifle](https://conker.fandom.com/wiki/File:AAAAAAD.png).
The short square silver muzzle, compact black receiver and stock support naming
03:0054 `Rifle - compact model` by visual comparison. A fresh side view confirms
the carrying handle, magazine and sling. This identifies an appearance-based
weapon family; it does not recover a developer name, establish actor ownership
or prove the game selects this exact record in Heist. Rigged 09:0146 remains
unresolved because its collapsed neutral pose has not been independently matched.

These three metadata updates reached the main gallery's Weapons tab and the
focused weapon gallery. Earlier labels remain searchable aliases. The focused
view now contains 27 records: 20 guns, five crossbows and two Katanas. Main gallery
membership/counts and all 3,030 existing model/download/preview hashes are
unchanged. The three sources also passed fresh fingerprint, ROM identity and
GLB packaging comparisons. No acceptance or validation evidence was promoted.
The 14 existing inspection tests, metadata scope audit and whitespace checks
passed. Browser searches showed two Katana cards and the compact Rifle card.
Baselines, comparison images and publication hashes are retained under
`build/assets/models/reference/weapon-followup-20261004/`.

## Skeletal remains correction

The user identified the former `Antlered weapon` (01:0038) and `Clawed weapon`
(01:0182) as post-explosion rib cages. Visible pale paired ribs, red central
tissue and attached tails support skeletal remains. The second model's pale
tail has a brown/orange tuft. Both records now belong to Parts & effects,
with names `Rodent remains - rib cage and tail (candidate)` and
`Cow remains - rib cage and tail (candidate)`.

Animal attribution remains tentative. The [Marvin the Mouse reference](https://conker.fandom.com/wiki/Marvin_the_Mouse)
describes his explosion and remaining tail; the [cow reference](https://conker.fandom.com/wiki/The_Cows)
describes explosive deaths. These establish contextual leads, not these numeric
model identities. No independently matched N64 gameplay frame or verified ROM
consumer currently links either record to the proposed animal/event. Marvin is
a mouse, so the first record uses the broader word rodent rather than claiming
a rat identity. The incorrect weapon descriptions survive only as explicitly
marked former-label aliases.

The two category/name corrections reached the main gallery. Weapons now contains
48 cards and Parts & effects 173; total membership and all 3,030 existing asset
hashes are unchanged. Source fingerprints, ROM identity and GLB packaging checks
passed for both records. The 14 existing inspection tests and whitespace checks
passed. Browser filtering confirmed both candidate labels in Parts & effects.
Local baselines, publication evidence and screenshot are retained in
`build/assets/models/reference/remains-correction-20261004/`.
