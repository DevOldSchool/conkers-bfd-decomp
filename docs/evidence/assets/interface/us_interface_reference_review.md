# US interface extraction and reference coverage

The initial review checked **92 HUD/menu selectors (97 PNGs)** and **95 font glyphs** against seven supplied sheets. Those exports are coherent after the loader correction. This validated existing outputs; it did not establish that every reference image was exported. The full reverse audit includes all **12 sheets** listed by the game page on 2026-10-02. Its historical evidence is retained below, with coverage updated after exporting the 18 verified menu/icon groups. The gallery now has **40 additional groups from 74 resources**, including **12 individual 16×16 crops**: **52 additional PNGs** and **132 gallery cards** in total.

## Full game-page coverage audit

The [game index](https://www.spriters-resource.com/nintendo_64/conkersbadfurday/)
lists ten general sheets and two unused/beta sheets. All twelve were visually
reviewed against the current HUD/font galleries. A bounded cross-check also
reviewed 1,342 existing standalone texture PNGs and 35 tiled composites in the
primary checkout. The 2,534 individual tiled-source PNGs and all embedded model
material images were not exhaustively compared. The McYum sheet-credit panels
are attribution graphics and are excluded.

**Eighteen previously missing menu/icon groups are now exported from 49
verified US runtime resources.** Other reference gaps are recorded below.
“Not located” means no verified match in these checked exports, not absence from
the ROM. There is no
single completion percentage: the sheets contain shared artwork, rotations,
smaller raster variants, packed atlases and beta alternatives.

| Reference sheet | Current coverage and remaining work |
|---|---|
| [Bees](https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62738/) | Eight bee images not located in checked exports. |
| [Bomb Plan Photos](https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62739/) | Five photos each have one existing 64×64 tile. Complete compositions of the six retail photos are missing; the sixth photo and separate ECTS replacement were not located. |
| [Haybot Screen](https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62740/) | Fifteen wireframe poses, screen frame, waveform and text not located. Haybot model coverage does not establish screen artwork coverage. |
| [Intro Credits](https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62741/) | Nintendo oval and tiny Rare are present. Missing 13 other title/credit/logo images: red/gold NINTENDO, PRESENTS, A, RAREWARE, GAME, STARRING, CONKER, ampersand, BERRI, full game logo, two GAME OVER variants and Dolby Surround. |
| [Main Menu Text & Icons](https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/) | All fifteen groups identified in the audit are now exported: GAME1–3, CHAPTERS, OPTIONS, MULTI, large HEIST/RAPTOR/BEACH/BACK/RACE/TANK/WAR headings, skull and dark START. These preserve the larger source artwork alongside existing chapter labels and menu buttons; this batch does not assert whole-sheet completeness. |
| [Multiplayer Icons](https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62743/) | Weapon/ammunition/status pixel art, circular counter and white track/map outline are missing from the named gallery; resource IDs unresolved. Four head identities already have larger exports; smaller sheet variants are not pixel-equated. |
| [Pause Menu & Multi Results](https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62744/) | Coloured digits 0–9 and dollar are complete. PAUSED is now exported. The two packed groups use three native resources, with full atlas previews and twelve individual small P1–P4/statistics PNGs. These close the three group gaps identified in the audit. |
| [Story Icons](https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62745/) | Forty-two chapter thumbnails and decorative frame remain not located. The four overlapping small statistics icons are now available as native 16×16 crops from the packed-statistics group. |
| [Text](https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62746/) | Main font, A/B family, six analog-stick frames and dark START are covered. Compact block font, ordinal suffixes, gold icon, L/Z buttons and five white effects remain missing from the reviewed gallery. C-up/down can reuse existing source pixels as rotations. |
| [ECTS menu](https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62893/) | Some retail matches exist: ON/OFF, QUIT, directional arrows, oval A/B, one Rare frame. Remaining rotating Rare frames, beta headings, small status variants, suffixes and distinct controller buttons are separate beta gaps. |
| [2D Villager](https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62894/) | Ten poses not located; classified unused/beta by the reference site. This does not establish a retail US extraction failure. |

### Completed export batch from the confirmed menu resources

The original audit decoded these groups into diagnostics. All eighteen are now
in the production gallery under Additional artwork, with full previews and raw
source downloads. All 49 payloads were rechecked against the US ROM, including
compressed extents and decoded hashes. The original match evidence is retained.
RGB matches use all opaque pixels; the translucent reticle uses maximum-alpha
pixels. Source
alpha is retained, and visual matches do not establish runtime placement.

| Exported group | Runtime resource IDs |
|---|---|
| START-dark | 2206 |
| BEACH | 1977, 1978, 1979 |
| skull | 1980, 1981, 1982, 1983 |
| CHAPTERS | 1994, 1995, 1996 |
| GAME1 | 2011, 2012, 2013 |
| GAME2 | 2014, 2015, 2016 |
| GAME3 | 2017, 2018, 2019 |
| OPTIONS | 2035, 2036, 2037 |
| RACE | 2056, 2057, 2058 |
| RAPTOR | 2059, 2060, 2061 |
| WAR | 2082, 2083, 2084 |
| BACK | 2097, 2098 |
| small P badges | 2115 |
| HEIST | 2180, 2181, 2182 |
| small stats atlas | 2183, 2184 |
| MULTI | 2188, 2189, 2190 |
| PAUSED | 2193, 2194, 2195 |
| TANK | 2212, 2213, 2214 |

The exported skull uses a **column-major 2×2** tile layout: resources 1980,
1981, 1982 and 1983 occupy top left, bottom left, top right and bottom right.
TANK uses three horizontal tiles. Resource 2115 packs four 16×16 P badges;
resources 2183–2184 pack eight 16×16 statistics images. Both packed groups retain
full atlas previews and now have **twelve individual 16×16 crop downloads**.
Each crop preserves the decoded RGBA bytes and alpha exactly. Its `x`/`y`
coordinates refer to the composed atlas; `source_resource_id` identifies the
original raw resource in the preview manifest.
These include smaller raster versions of some already exported identities, so
they are not twelve wholly new artwork identities. C-up/down match exact
rotations of selector 59 and need no new raw source.

The diagnostic contact is saved at
`build/hud-reference-review/full-site-audit/missing-menu-contact.png`. The
[machine-readable audit](us_interface_reference_review.json) records all twelve
sheet hashes, source coordinates, runtime IDs, ROM extents, payload hashes and
per-group limitations. Reference copies and diagnostics are under
`build/hud-reference-review/full-site-audit/`.

### Existing partial photo exports

Five complete 64×64 I4 tiles match every RGB pixel of the corresponding photo
region, but their source alpha equals intensity while the reference is opaque.
They are not complete 192×128 photo exports. The old texture filenames use
physical stream ordinals; the runtime IDs below were reconciled by ROM extent.

| Retail photo | Existing primary-checkout PNG | Runtime ID |
|---:|---|---:|
| 1 | `build/assets/textures/us-native-proven/4539.i4.png` | 4541 |
| 2 | `build/assets/textures/us-native-proven/4548.i4.png` | 4550 |
| 3 | `build/assets/textures/us-native-proven/1790.i4.png` | 1792 |
| 4 | `build/assets/textures/us-native-proven/3452.i4.png` | 3454 |
| 5 | `build/assets/textures/us-native-proven/3469.i4.png` | 3471 |

The eighteen-group menu/icon export batch is complete. Further work can resolve
intro graphics, secondary fonts and buttons, story thumbnails and complete photo
compositions, followed by unresolved multiplayer weapon/status artwork, aiming
overlays, effects, bees and Haybot screen elements. Beta variants remain a
separate scope. None of those unresolved families is promoted by this batch.

## Resource indexing correction

`D_80091D20` contains 7,762 runtime slots, including zero-sized slots 1767 and 1768. The HUD extractor previously enumerated 7,760 physical streams and treated their ordinals as runtime IDs. Every HUD lookup therefore selected the wrong payload. The corrected loader preserves empty slots and validates every compressed extent; it does not apply a hardcoded subtraction.

This removes the apparent chopped words, mixed animation frames, inconsistent formats, and raw-only assets. All 159 referenced resources now decode with the original renderer dimensions and RGBA32 TMEM layout. The six joystick frames are six joystick images. Selectors 59 and 60 are the two 16x16 C-button sources. There are no per-resource format, size, rotation, or extra-tile overrides.

The user correctly identified the *pictured* Uga Buga head icon and Rare logo. Their old selector associations were caused by the indexing bug: Uga Buga belongs to **selector 10 / runtime resource 2220**; selector 56 is the tank turret icon. Selector 57 is radar. The Rare logo is **runtime resource 2204 / physical stream 2202**, outside this selector table. Rare and the other previously named images are now restored under **Additional artwork**, separately from the 92 selectors. Every previous export also remains in the recovery snapshot.

The complete prior source and gallery were copied and hash-verified under `build/hud-reference-review/before-index-fix/` before replacement. This snapshot is historical and uses the invalid ordinal-to-selector associations.

## Reference coverage

**85 selectors have visual reference matches.** Seven have no matching artwork in these sheets: 63 (snowy mountains/clouds), 68 (BATSTOWER), 80 (SQUIRRELS), 81 (TEDIZ), 83 (UGAS), 84 (RAPTORS), and 85 (FRENCHYS). Their images are coherent; names describe readable text or visible shapes. The user identified selectors 8–11 as Tediz, SHC Soldier, Uga Buga and Raptor head icons, respectively. Other character icons without a confirmed name retain descriptive names.

Selectors 7, 17 and 18 match the ECTS demo sheet visually. Their presence in retail US is independently established by the extracted ROM bytes; the beta reference is not used to infer runtime use. Intro Credits and 2D Villager were checked but provide no additional matches in the corrected 92-selector set.

The font has **66 exact alpha/intensity matches** and **29 glyphs absent from the Text sheet**. All 95 were visually inspected. No glyph pixels or mapping were changed. The absent set is indices 47, 53, 63–79, 82–83 and 86–93. Byte labels are the ROM input map, not necessarily Unicode labels for the pictured symbols.

The initial seven-sheet output review used:

- [Main Menu Text & Icons](https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/)
- [Multiplayer Icons](https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62743/)
- [Intro Credits](https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62741/)
- [Pause Menu & Multi Results](https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62744/)
- [Text](https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62746/)
- [Main/Pause Menu Text & Icons (ECTS Demo)](https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62893/) (unused/beta)
- [2D Villager](https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62894/) (unused/beta)

## Restored additional artwork

The gallery now includes 40 additional groups from 74 runtime resources outside
this selector table. The initial 22 groups cover Nintendo, Rare, A/B buttons, a
red circular button, all ten coloured digits, the dollar symbol, Dang..., Dino,
Poops, question mark and Total. The completed eighteen-group batch adds the
menu headings, dark START, skull and packed badges/statistics listed above.
Forty group previews and twelve native crops produce 52 additional PNGs. Together
with the unchanged 92 selector cards, the gallery contains 132 cards; individual
crops are listed within their two atlas cards.

The 0–9 and dollar images each match every opaque pixel in their reference crop
on the Pause Menu & Multi Results sheet; ROM alpha is retained. The digit order
is also established by the game's decimal rendering tables. The
[additional artwork inventory](us_hud_menu_assets.md#additional-artwork-outside-the-selector-table)
records their IDs, dimensions, formats and evidence limits. Five small labels or
symbols use IA8 to preserve their source transparency; Nintendo uses I8.
Restoration leaves every current selector image and raw source byte-identical.
The 85-selector reference-match count above is unchanged.

## Selector checklist

All frames and variants were individually viewed. Coordinates and PNG hashes are recorded in the [machine-readable review](us_interface_reference_review.json). Approximate HUD reference boxes are visual locators, not pixel-equality claims. Font matches separately record exact pixel coordinates.

| Selector | Corrected artwork | Reference sheet |
|---:|---|---|
| 1 | Red P1 badge | 62742 |
| 2 | Blue P2 badge | 62742 |
| 3 | Green P3 badge | 62742 |
| 4 | Yellow P4 badge | 62742 |
| 5 | Purple figure icon | 62742 |
| 6 | Ai label | 62742 |
| 7 | Four directional arrows | 62893 |
| 8 | Tediz head icon | 62742 |
| 9 | SHC Soldier head icon | 62742 |
| 10 | Uga Buga head icon | 62742 |
| 11 | Raptor head icon | 62742 |
| 12 | CONT... label (dark) | 62744 |
| 13 | CONT... label (bright) | 62744 |
| 14 | QUIT label (dark) | 62744 |
| 15 | QUIT label (bright) | 62744 |
| 16 | CHEATS label | 62742 |
| 17 | OFF speech bubble | 62893 |
| 18 | ON speech bubble | 62893 |
| 19 | Speaker pair | 62742 |
| 20 | Five-speaker arrangement | 62742 |
| 21 | Single speaker | 62742 |
| 22 | PLAY label (dark) | 62742 |
| 23 | PLAY label (bright) | 62742 |
| 24 | ERASE label (dark) | 62742 |
| 25 | ERASE label (bright) | 62742 |
| 26 | Analog stick animation | 62742 |
| 27 | SET-UP label (dark) | 62742 |
| 28 | SET-UP label (bright) | 62742 |
| 29 | N button (dark) | 62742 |
| 30 | N button (bright) | 62742 |
| 31 | Y button (dark) | 62742 |
| 32 | Y button (bright) | 62742 |
| 33 | RESTART label (dark) | 62744 |
| 34 | RESTART label (bright) | 62744 |
| 35 | RACE A label (dark) | 62742 |
| 36 | RACE A label (bright) | 62742 |
| 37 | RACE B label (dark) | 62742 |
| 38 | RACE B label (bright) | 62742 |
| 39 | TEMPLE label (dark) | 62742 |
| 40 | TEMPLE label (bright) | 62742 |
| 41 | THE VAULT label (dark) | 62742 |
| 42 | THE VAULT label (bright) | 62742 |
| 43 | TOTAL WAR label (dark) | 62742 |
| 44 | TOTAL WAR label (bright) | 62742 |
| 45 | COLORS label (dark) | 62742 |
| 46 | COLORS label (bright) | 62742 |
| 47 | BUNKER label (dark) | 62742 |
| 48 | BUNKER label (bright) | 62742 |
| 49 | NEW GAME label (bright) | 62742 |
| 50 | RESTART label (bright) | 62744 |
| 51 | QUIT label (bright) | 62744 |
| 52 | Gray character with brown hat | 62742 |
| 53 | Blue group of player pieces | 62742 |
| 54 | LAP checkered flag | 62742 |
| 55 | Red running figures | 62742 |
| 56 | Tank turret icon | 62742 |
| 57 | Green radar | 62742 |
| 58 | Gold balance scales | 62742 |
| 59 | N64 C-left button | 62742 |
| 60 | N64 C-right button | 62742 |
| 61 | Stopwatch | 62742 |
| 62 | Two opposed red arrows | 62742 |
| 63 | Snowy mountains and clouds | Absent from supplied sheets |
| 64 | Money bag | 62742 |
| 65 | SCORE circular icon | 62742 |
| 66 | HUNGOVER label | 62742 |
| 67 | WINDY label | 62742 |
| 68 | BATSTOWER label | Absent from supplied sheets |
| 69 | BARN BOYS label | 62742 |
| 70 | SLOPRANO label | 62742 |
| 71 | UGA BUGA label | 62742 |
| 72 | SPOOKY label | 62742 |
| 73 | IT'S WAR label | 62742 |
| 74 | HEIST label | 62742 |
| 75 | STATS label | 62744 |
| 76 | REDS label | 62742 |
| 77 | BLUES label | 62742 |
| 78 | GREENS label | 62742 |
| 79 | YELLOWS label | 62742 |
| 80 | SQUIRRELS label | Absent from supplied sheets |
| 81 | TEDIZ label | Absent from supplied sheets |
| 82 | YOU label | 62744 |
| 83 | UGAS label | Absent from supplied sheets |
| 84 | RAPTORS label | Absent from supplied sheets |
| 85 | FRENCHYS label | Absent from supplied sheets |
| 86 | WIN label | 62744 |
| 87 | LOSE label | 62744 |
| 88 | DRAW label | 62744 |
| 89 | REDS label (smaller display scale) | 62742 |
| 90 | BLUES label (smaller display scale) | 62742 |
| 91 | GREENS label (smaller display scale) | 62742 |
| 92 | YELLOWS label (smaller display scale) | 62742 |

## Validation

The corrected PNGs reproduce the independently reviewed probe byte-for-byte. Tests cover empty runtime slots, exact ROM extents, changed loader instructions, stale provenance, PNG corruption and named exports. Additional tests compare asymmetric source pixels through the skull composition and all twelve crops, including transparent RGB and alpha, and reject changed crop pixels or stale crop metadata. `hud-assets verify` checks ROM bytes, resource identity, renderer dimensions, decoded pixels, metadata, crop outputs and gallery output. Font validation checks all 99 preview files against the ROM.
