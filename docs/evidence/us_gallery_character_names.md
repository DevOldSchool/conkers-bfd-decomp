# Gallery character-name review

The inspection labels in `config/model-inspection.json` are visual identifications,
not recovered source symbols. Bank/entry IDs, render cases and exported filenames
remain unchanged. This review compares rendered ROM exports with the public
[Conker Wiki](https://conker.fandom.com/wiki/Conker_Wiki) descriptions and the
[Textures Resource catalog](https://textures.spriters-resource.com/nintendo_64/conkersbadfurday/).
Catalog thumbnails were reviewed; no third-party model or texture files were
imported. The [public character-model research list](https://github.com/mkst/conker/wiki/Research#character-models-listtxt)
provides an independent informal ID cross-check (its IDs are hexadecimal; the
entry numbers below are decimal). It is supporting evidence, not authority for
runtime behavior.

## Corrected and refined labels

All entries below are in bank 01. Previous display labels remain searchable as
explicit **Former label** aliases, rather than alternative character identities.

| Entry | Reviewed label | Visible evidence and public reference |
| --- | --- | --- |
| 0005 | Wasp | Black/yellow angular insect, distinct from the bee models; [Wasp](https://conker.fandom.com/wiki/Wasp) |
| 0010 | Mrs. Catfish | Cat-faced fish with yellow glasses; [Mrs. Catfish](https://conker.fandom.com/wiki/Mrs._Catfish) |
| 0014 | Corn Bag — unused | Sack marked CORN with eyes; [Corn Bag](https://conker.fandom.com/wiki/Corn_Bag) |
| 0015 | Lady Cog — red | Toothed wheel, central hole, lashes and lips; [Lady Cogs](https://conker.fandom.com/wiki/Lady_Cogs) |
| 0024 | Jack — metal box | Gray riveted box and blue eyes, matching the catalog metal crate; [Jack](https://conker.fandom.com/wiki/Jack) |
| 0026 | Catfish — skeletal remains | Catfish face/fins with exposed dorsal bones; [Catfish](https://conker.fandom.com/wiki/Catfish) |
| 0052 | TNT Imp | Purple imp carrying a keg marked TNT, not a dinosaur; [TNT Imp](https://conker.fandom.com/wiki/TNT_Imp) |
| 0068 | Dung Beetle | Red/black beetle with open wing covers; [Dung Beetle](https://conker.fandom.com/wiki/Dung_Beetle) |
| 0070 | Lady Cog — blue | Same cog form in blue; [Lady Cogs](https://conker.fandom.com/wiki/Lady_Cogs) |
| 0076 | Lady Cog — green | Same cog form in green; [Lady Cogs](https://conker.fandom.com/wiki/Lady_Cogs) |
| 0107 | Electric Eel | Elongated blue-green body and yellow eyes; [Electric Eel](https://conker.fandom.com/wiki/Electric_Eel) |
| 0125 | Franky the Pitchfork — broken upper part | Same face and wooden handle as 0012, without the metal fork; [Franky](https://conker.fandom.com/wiki/Franky_the_Pitchfork) |
| 0173 | Wayne — cigar | Wasp with visible cigar; [Wayne and the Wankas](https://conker.fandom.com/wiki/Wayne_and_the_Wankas) |
| 0174 | Wanka — fat wasp | Broad-bodied member of the wasp trio; [Wayne and the Wankas](https://conker.fandom.com/wiki/Wayne_and_the_Wankas) |
| 0175 | Wanka — skinny wasp | Thin-bodied member of the wasp trio; [Wayne and the Wankas](https://conker.fandom.com/wiki/Wayne_and_the_Wankas) |

## Dinosaur distinction and limits

Entry 0165 retains **Red Dinosaur**, now with an explicit
[Red Dinosaurs](https://conker.fandom.com/wiki/Red_Dinosaurs) reference and search
aliases. Its orange-red skin, yellow eyes and reptilian body support that
identification. The reference also discusses the baby raptor in multiplayer;
this does not make it the purple [Dino Baby](https://conker.fandom.com/wiki/Dino_Baby)
(0054). Do not rename it to Fangy or Fire Imp from color alone.

The labels describe appearance. They do not prove runtime use, native lighting,
material fidelity, animation state, source-variable names or unique actor
ownership. Existing export/appearance caveats remain intact. Other unreviewed
variants, generic missiles and detached parts retain their existing labels;
no blanket naming inference is made from an adjacent entry number.
