# US music sequence labels

Evidence kind: listening review. [`config/audio-sequences.json`](../../config/audio-sequences.json)
attaches descriptive labels to the 149 compact sequences in indexed bank `0x17`,
entry `3`. The labels are identifications made by ear, not recovered source
names, and they do not prove which game code selects a sequence. The sequence
index remains the ROM identity; extracted filenames such as
`sequences/0061.cseq` are unchanged.

The [non-MP3 audio evidence](us_non_mp3_audio_assets.md) establishes the
sequence bank, its 149 descriptors and the single-pass MIDI preview. This
review adds no format claim.

## Method

Each sequence was rendered locally from the contributor's own ROM and listened
to. The renders used the extracted `B1` instrument graph and PCM sample
previews, assembled into a local soundfont, so instruments were recognisable.
The renders, soundfont and recordings are ROM-derived or third-party material;
they stay outside the repository and are not required to read the map.

Program selection in the local renders follows the reconstructed player:
controller 32 supplies the instrument major and the program change selects
`(major << 7) + program`. Instrument 0's key maps match no MIDI key, so notes
on it are silent. Sequence 0 has no playable notes.

The renders differ from native playback:

- each sequence plays once, without Conker's loop extensions;
- channels the game mutes or fades at runtime all sound together, so layered
  sequences are heard as one mix;
- native reverb, filters and the sequence's runtime volume are not reproduced;
- envelope timing is approximated.

These limits affect how a sequence sounds, not which sequence it is.

## Fields

| Field | Meaning |
| --- | --- |
| `index` | Sequence index in bank `0x17`, entry `3` |
| `name` | Descriptive label, or `null` when unidentified |
| `confidence` | `identified`, `tentative` or `unidentified` |
| `category` | Chapter or one of `Multiplayer`, `SFX`, `Menu`, `Other`; `null` when not assigned |
| `story`, `multiplayer` | Whether the reviewer associates the sequence with that mode |
| `note` | Reviewer's free-text recollection of where it is heard |
| `heard_at` | Automated matches against public recordings |

At this review, 112 sequences are `identified`, four are `tentative` and 33 are
`unidentified`. Unidentified sequences keep any note as a lead. A category
records where the reviewer recognised the sequence; it does not exclude use
elsewhere, and 60 sequences have none.

## Recording references

`heard_at` links 74 sequences to 213 positions in four public gameplay
recordings listed under `references`. The positions come from an automated
comparison: each local render and each recording was reduced to a coarse
pitch-band spectrogram, and render chunks were cross-correlated against the
recording. Only matches the comparison marked confident are retained.

`start_seconds` and `end_seconds` are positions in the recording, and
`sequence_offset_seconds` is the position in the single-pass render where the
match begins. These are supporting references, not proof: matches were not all
confirmed by ear, short jingles and ambient sequences can match falsely, and
the recordings are third-party material that may become unavailable. Nothing
from the recordings is stored here.

## Sequence table

This table is generated from the map and repeats its content for reading.
`Story`, `MP1`, `MP2` and `MP3` link to the matched second in the recordings
listed under `references`.

<!-- sequence-table:begin -->
| ID | Name | Confidence | Category | Story | Multiplayer | Note | Heard at |
| --- | --- | --- | --- | :-: | :-: | --- | --- |
| `0000` | Blank | identified |  | no | no |  |  |
| `0001` | MainTheme | identified | Chapter 2: Windy | no | no | Buzzing bees version | [Story 0:18:36](https://www.youtube.com/watch?v=3PftWpkdcTc&t=1116s), [Story 0:21:02](https://www.youtube.com/watch?v=3PftWpkdcTc&t=1262s), [Story 0:23:05](https://www.youtube.com/watch?v=3PftWpkdcTc&t=1385s), [Story 0:25:08](https://www.youtube.com/watch?v=3PftWpkdcTc&t=1508s), [Story 0:26:29](https://www.youtube.com/watch?v=3PftWpkdcTc&t=1589s), [Story 0:34:18](https://www.youtube.com/watch?v=3PftWpkdcTc&t=2058s), [Story 0:53:37](https://www.youtube.com/watch?v=3PftWpkdcTc&t=3217s), [Story 0:57:21](https://www.youtube.com/watch?v=3PftWpkdcTc&t=3441s), [Story 0:58:40](https://www.youtube.com/watch?v=3PftWpkdcTc&t=3520s), [Story 1:00:30](https://www.youtube.com/watch?v=3PftWpkdcTc&t=3630s), [Story 1:15:00](https://www.youtube.com/watch?v=3PftWpkdcTc&t=4500s), [Story 1:41:32](https://www.youtube.com/watch?v=3PftWpkdcTc&t=6092s), [Story 1:43:17](https://www.youtube.com/watch?v=3PftWpkdcTc&t=6197s), [Story 2:46:32](https://www.youtube.com/watch?v=3PftWpkdcTc&t=9992s), [Story 2:48:18](https://www.youtube.com/watch?v=3PftWpkdcTc&t=10098s), [Story 2:53:36](https://www.youtube.com/watch?v=3PftWpkdcTc&t=10416s) |
| `0002` | SadSong3 | identified |  | no | no | Plays when the queen bee is crying over her hive, when Frank is split into two and when Conker farewells his TRex. Possibly reprises elswhere too. | [Story 0:18:55](https://www.youtube.com/watch?v=3PftWpkdcTc&t=1135s), [Story 0:50:07](https://www.youtube.com/watch?v=3PftWpkdcTc&t=3007s), [Story 2:42:50](https://www.youtube.com/watch?v=3PftWpkdcTc&t=9770s), [Story 2:46:46](https://www.youtube.com/watch?v=3PftWpkdcTc&t=10006s) |
| `0003` |  | unidentified |  | no | no |  | [Story 0:24:29](https://www.youtube.com/watch?v=3PftWpkdcTc&t=1469s), [Story 1:42:39](https://www.youtube.com/watch?v=3PftWpkdcTc&t=6159s), [Story 2:54:35](https://www.youtube.com/watch?v=3PftWpkdcTc&t=10475s) |
| `0004` | WaspChase | identified |  | no | no |  | [Story 0:19:58](https://www.youtube.com/watch?v=3PftWpkdcTc&t=1198s), [Story 0:45:37](https://www.youtube.com/watch?v=3PftWpkdcTc&t=2737s), [Story 1:35:31](https://www.youtube.com/watch?v=3PftWpkdcTc&t=5731s), [Story 2:49:29](https://www.youtube.com/watch?v=3PftWpkdcTc&t=10169s) |
| `0005` | BeehiveJingle | identified | Chapter 2: Windy | no | no | Related to the stuff with the beehive | [Story 0:20:27](https://www.youtube.com/watch?v=3PftWpkdcTc&t=1227s), [Story 2:52:57](https://www.youtube.com/watch?v=3PftWpkdcTc&t=10377s) |
| `0006` | BeeChase | identified | Chapter 2: Windy | yes | no | Maybe | [Story 0:33:10](https://www.youtube.com/watch?v=3PftWpkdcTc&t=1990s) |
| `0007` | MarvinExplodes | identified |  | no | no | Plays when the cheese rat (Marvin?) explodes |  |
| `0008` |  | unidentified |  | no | no | Fuckin weird blank file? |  |
| `0009` | UngaBungaIntro | identified | Chapter 6: Uga Buga | yes | no | Played at the start of Unga Bunga | [Story 2:04:09](https://www.youtube.com/watch?v=3PftWpkdcTc&t=7449s) |
| `0010` | PisstasticBackground | identified |  | no | no | Plays when pissing on the fire imps | [Story 1:33:52](https://www.youtube.com/watch?v=3PftWpkdcTc&t=5632s), [Story 2:55:06](https://www.youtube.com/watch?v=3PftWpkdcTc&t=10506s) |
| `0011` | FireImpPassive | identified | Chapter 4: Bats Tower | no | no | ? |  |
| `0012` | TerminatorThing | identified | Chapter 3: Barn Boys | yes | no | Also related to the fight with the haybail |  |
| `0013` | JawsThemeThing | identified | Chapter 4: Bats Tower | yes | no | Before or after the cog thing | [Story 1:17:58](https://www.youtube.com/watch?v=3PftWpkdcTc&t=4678s), [Story 1:26:10](https://www.youtube.com/watch?v=3PftWpkdcTc&t=5170s), [Story 1:27:39](https://www.youtube.com/watch?v=3PftWpkdcTc&t=5259s) |
| `0014` |  | unidentified |  | no | no | Jingle |  |
| `0015` | BatTowerBackground | identified | Chapter 4: Bats Tower | yes | no | Plays during the bats tower/unga bunga | [Story 1:19:35](https://www.youtube.com/watch?v=3PftWpkdcTc&t=4775s), [Story 1:20:56](https://www.youtube.com/watch?v=3PftWpkdcTc&t=4856s) |
| `0016` | MultiplayerMenu1 | identified | Menu | no | yes | Where the kegs are I think |  |
| `0017` |  | unidentified |  | no | no | Jingle |  |
| `0018` | CogBackgroundMusic | identified | Chapter 4: Bats Tower | yes | no | Story mode | [Story 1:18:32](https://www.youtube.com/watch?v=3PftWpkdcTc&t=4712s) |
| `0019` | GunfireAndRicochets1 | identified | Chapter 8: It's War | yes | yes | Bullets and ricochets | [Story 3:59:15](https://www.youtube.com/watch?v=3PftWpkdcTc&t=14355s), [MP1 0:07:17](https://www.youtube.com/watch?v=EiUtagv_SaU&t=437s), [MP1 0:49:58](https://www.youtube.com/watch?v=EiUtagv_SaU&t=2998s), [MP1 1:39:06](https://www.youtube.com/watch?v=EiUtagv_SaU&t=5946s), [MP1 2:00:38](https://www.youtube.com/watch?v=EiUtagv_SaU&t=7238s), [MP2 0:50:03](https://www.youtube.com/watch?v=tYOWg_OJO14&t=3003s), [MP2 0:54:27](https://www.youtube.com/watch?v=tYOWg_OJO14&t=3267s), [MP3 0:06:08](https://www.youtube.com/watch?v=VpmG9i2-uVY&t=368s) |
| `0020` |  | unidentified |  | no | no | Death/Grim Reaper scene? |  |
| `0021` | Gameboy | identified | Other | no | no | Idle animation music; plays when no input is received from the player |  |
| `0022` | MoreGameboy | identified |  | no | no | Idle animation music; plays when no input is received from the player |  |
| `0023` | GameboyYetAgain | identified | Other | no | no | Idle animation music; plays when no input is received from the player |  |
| `0024` | IntroOST | identified | Chapter 1: Hung Over | yes | no |  | [Story 0:01:25](https://www.youtube.com/watch?v=3PftWpkdcTc&t=85s) |
| `0025` | ColosseumCrowd | identified | Chapter 6: Uga Buga | yes | no | Played during the fight with the giant |  |
| `0026` | Horn | identified | Other | no | no | Plays in the colosseum |  |
| `0027` |  | unidentified | Multiplayer | yes | yes | No fucking idea really |  |
| `0028` |  | unidentified |  | no | no | Rock a by baby thing, don't remember this at all |  |
| `0029` | TRexIntro | identified | Chapter 6: Uga Buga | yes | no | When the TRex enters the colosseum and eats a caveman | [Story 2:34:38](https://www.youtube.com/watch?v=3PftWpkdcTc&t=9278s) |
| `0030` | HeistMPBackgroundMusic | identified | Multiplayer | no | yes | Played in the background of the multiplayer minigame "Heist" | [MP1 0:13:13](https://www.youtube.com/watch?v=EiUtagv_SaU&t=793s), [MP1 0:36:47](https://www.youtube.com/watch?v=EiUtagv_SaU&t=2207s), [MP1 0:40:47](https://www.youtube.com/watch?v=EiUtagv_SaU&t=2447s), [MP1 1:43:35](https://www.youtube.com/watch?v=EiUtagv_SaU&t=6215s), [MP1 2:02:23](https://www.youtube.com/watch?v=EiUtagv_SaU&t=7343s), [MP1 2:05:03](https://www.youtube.com/watch?v=EiUtagv_SaU&t=7503s), [MP2 0:20:51](https://www.youtube.com/watch?v=tYOWg_OJO14&t=1251s), [MP2 0:23:45](https://www.youtube.com/watch?v=tYOWg_OJO14&t=1425s), [MP3 0:19:01](https://www.youtube.com/watch?v=VpmG9i2-uVY&t=1141s), [MP3 0:21:33](https://www.youtube.com/watch?v=VpmG9i2-uVY&t=1293s) |
| `0031` | GregGrimReaperCutsceneBackground | identified | Other | yes | no | From story mode | [Story 2:59:52](https://www.youtube.com/watch?v=3PftWpkdcTc&t=10792s), [Story 3:18:29](https://www.youtube.com/watch?v=3PftWpkdcTc&t=11909s) |
| `0032` | WarBackground | identified | Chapter 8: It's War | yes | yes | Background music used in story and multiplayer, war related | [Story 3:50:35](https://www.youtube.com/watch?v=3PftWpkdcTc&t=13835s), [Story 3:56:57](https://www.youtube.com/watch?v=3PftWpkdcTc&t=14217s), [Story 3:58:35](https://www.youtube.com/watch?v=3PftWpkdcTc&t=14315s), [MP1 0:06:53](https://www.youtube.com/watch?v=EiUtagv_SaU&t=413s), [MP1 0:11:53](https://www.youtube.com/watch?v=EiUtagv_SaU&t=713s), [MP1 0:43:47](https://www.youtube.com/watch?v=EiUtagv_SaU&t=2627s), [MP1 0:45:57](https://www.youtube.com/watch?v=EiUtagv_SaU&t=2757s), [MP1 0:49:58](https://www.youtube.com/watch?v=EiUtagv_SaU&t=2998s), [MP1 0:53:33](https://www.youtube.com/watch?v=EiUtagv_SaU&t=3213s), [MP1 0:58:07](https://www.youtube.com/watch?v=EiUtagv_SaU&t=3487s), [MP1 0:59:49](https://www.youtube.com/watch?v=EiUtagv_SaU&t=3589s), [MP1 1:31:32](https://www.youtube.com/watch?v=EiUtagv_SaU&t=5492s), [MP1 1:33:05](https://www.youtube.com/watch?v=EiUtagv_SaU&t=5585s), [MP1 1:38:42](https://www.youtube.com/watch?v=EiUtagv_SaU&t=5922s), [MP1 1:41:56](https://www.youtube.com/watch?v=EiUtagv_SaU&t=6116s), [MP1 1:58:40](https://www.youtube.com/watch?v=EiUtagv_SaU&t=7120s), [MP1 2:00:30](https://www.youtube.com/watch?v=EiUtagv_SaU&t=7230s), [MP2 0:27:52](https://www.youtube.com/watch?v=tYOWg_OJO14&t=1672s), [MP2 0:29:09](https://www.youtube.com/watch?v=tYOWg_OJO14&t=1749s), [MP2 0:34:26](https://www.youtube.com/watch?v=tYOWg_OJO14&t=2066s), [MP2 0:35:52](https://www.youtube.com/watch?v=tYOWg_OJO14&t=2152s), [MP2 0:52:46](https://www.youtube.com/watch?v=tYOWg_OJO14&t=3166s), [MP3 0:02:37](https://www.youtube.com/watch?v=VpmG9i2-uVY&t=157s), [MP3 0:05:28](https://www.youtube.com/watch?v=VpmG9i2-uVY&t=328s), [MP3 0:17:50](https://www.youtube.com/watch?v=VpmG9i2-uVY&t=1070s) |
| `0033` | Waves | identified | Other | no | no | Plays throughout the WW2 chapter when you are near waves | [Story 3:34:47](https://www.youtube.com/watch?v=3PftWpkdcTc&t=12887s), [Story 4:01:06](https://www.youtube.com/watch?v=3PftWpkdcTc&t=14466s) |
| `0034` | CockAndThePluckerBackgroundMusic | identified | Menu | no | no | Main menu | [Story 0:00:55](https://www.youtube.com/watch?v=3PftWpkdcTc&t=55s), [MP1 0:06:17](https://www.youtube.com/watch?v=EiUtagv_SaU&t=377s), [MP1 0:12:42](https://www.youtube.com/watch?v=EiUtagv_SaU&t=762s), [MP1 0:15:29](https://www.youtube.com/watch?v=EiUtagv_SaU&t=929s), [MP1 0:18:08](https://www.youtube.com/watch?v=EiUtagv_SaU&t=1088s), [MP1 0:33:43](https://www.youtube.com/watch?v=EiUtagv_SaU&t=2023s), [MP1 0:42:52](https://www.youtube.com/watch?v=EiUtagv_SaU&t=2572s), [MP1 0:49:07](https://www.youtube.com/watch?v=EiUtagv_SaU&t=2947s), [MP1 0:55:23](https://www.youtube.com/watch?v=EiUtagv_SaU&t=3323s), [MP1 1:01:04](https://www.youtube.com/watch?v=EiUtagv_SaU&t=3664s), [MP1 1:25:52](https://www.youtube.com/watch?v=EiUtagv_SaU&t=5152s), [MP1 1:31:01](https://www.youtube.com/watch?v=EiUtagv_SaU&t=5461s), [MP1 1:34:42](https://www.youtube.com/watch?v=EiUtagv_SaU&t=5682s), [MP1 1:38:29](https://www.youtube.com/watch?v=EiUtagv_SaU&t=5909s), [MP1 1:43:17](https://www.youtube.com/watch?v=EiUtagv_SaU&t=6197s), [MP1 1:46:36](https://www.youtube.com/watch?v=EiUtagv_SaU&t=6396s), [MP1 1:50:01](https://www.youtube.com/watch?v=EiUtagv_SaU&t=6601s), [MP1 2:01:55](https://www.youtube.com/watch?v=EiUtagv_SaU&t=7315s), [MP2 0:01:13](https://www.youtube.com/watch?v=tYOWg_OJO14&t=73s) |
| `0035` | MultiplayerMenu2 | identified | Menu | no | yes | Multiplayer Menu background maybe |  |
| `0036` | FinalBoss1 | identified | Chapter 9: The Heist | yes | no | I think this might be from the end where the alien is fighting conker |  |
| `0037` | WW2End2 | identified | Chapter 8: It's War | yes | no | Also played throughout the WW2 Chapter? | [Story 3:39:42](https://www.youtube.com/watch?v=3PftWpkdcTc&t=13182s), [Story 4:10:24](https://www.youtube.com/watch?v=3PftWpkdcTc&t=15024s) |
| `0038` | FootstepTurn4 | identified | SFX | no | no |  |  |
| `0039` | FootstepTurn3 | identified | SFX | no | no |  |  |
| `0040` | Footsteps1 | identified |  | no | no |  |  |
| `0041` | Footsteps2 | identified | SFX | no | no |  |  |
| `0042` | FootstepTurn | identified | SFX | no | no |  |  |
| `0043` | FootstepTurn2 | identified | SFX | no | no |  |  |
| `0044` | TedizDen | identified | Chapter 8: It's War | yes | no | Plays after conker makes it through the normandy landing and gets inside the Tediz "den" | [Story 3:40:19](https://www.youtube.com/watch?v=3PftWpkdcTc&t=13219s) |
| `0045` |  | unidentified |  | no | no |  |  |
| `0046` |  | unidentified |  | no | no | Jingle/alert |  |
| `0047` |  | unidentified |  | no | no | Jingle |  |
| `0048` |  | unidentified |  | no | no | I think this is played underground after the fight with the haybail and there is all the electrical wiring and piss/water streaming in |  |
| `0049` | Escape | identified | Chapter 8: It's War | no | no | Part of the WW2 chapter and escaping Tediz island | [Story 3:58:14](https://www.youtube.com/watch?v=3PftWpkdcTc&t=14294s), [Story 4:12:27](https://www.youtube.com/watch?v=3PftWpkdcTc&t=15147s) |
| `0050` | AirRaidSiren2 | identified |  | yes | yes | Another air raid siren. Maybe used seperately for Multiplayer. Total War? | [Story 3:53:17](https://www.youtube.com/watch?v=3PftWpkdcTc&t=13997s), [MP1 0:29:22](https://www.youtube.com/watch?v=EiUtagv_SaU&t=1762s), [MP1 0:48:47](https://www.youtube.com/watch?v=EiUtagv_SaU&t=2927s), [MP1 1:22:39](https://www.youtube.com/watch?v=EiUtagv_SaU&t=4959s), [MP1 1:23:58](https://www.youtube.com/watch?v=EiUtagv_SaU&t=5038s), [MP1 1:24:41](https://www.youtube.com/watch?v=EiUtagv_SaU&t=5081s), [MP1 1:28:36](https://www.youtube.com/watch?v=EiUtagv_SaU&t=5316s), [MP1 1:29:35](https://www.youtube.com/watch?v=EiUtagv_SaU&t=5375s), [MP2 0:33:43](https://www.youtube.com/watch?v=tYOWg_OJO14&t=2023s), [MP2 0:41:15](https://www.youtube.com/watch?v=tYOWg_OJO14&t=2475s), [MP2 0:42:06](https://www.youtube.com/watch?v=tYOWg_OJO14&t=2526s), [MP2 0:44:23](https://www.youtube.com/watch?v=tYOWg_OJO14&t=2663s) |
| `0051` | AirRaidSiren1 | identified | Chapter 8: It's War | yes | yes | Plays during a bombing raid in the WW2 chapter when you are with Rodent. Also total war in multiplayer. | [MP1 0:48:47](https://www.youtube.com/watch?v=EiUtagv_SaU&t=2927s), [MP1 1:23:58](https://www.youtube.com/watch?v=EiUtagv_SaU&t=5038s), [MP2 0:33:43](https://www.youtube.com/watch?v=tYOWg_OJO14&t=2023s) |
| `0052` | SpiderChase | identified |  | no | no | Plays as conker is chased deep into the Tediz bunker by robot spiders | [Story 3:42:11](https://www.youtube.com/watch?v=3PftWpkdcTc&t=13331s) |
| `0053` | Poo | identified | Chapter 2: Windy | yes | no | When you have to push shit up a hill | [Story 1:04:06](https://www.youtube.com/watch?v=3PftWpkdcTc&t=3846s), [Story 1:12:27](https://www.youtube.com/watch?v=3PftWpkdcTc&t=4347s), [Story 1:45:08](https://www.youtube.com/watch?v=3PftWpkdcTc&t=6308s) |
| `0054` | IntroMusic | identified | Menu | no | no | Played alongside the N64 logo getting chopped up with the chainsaw |  |
| `0055` | ConkerIsDrunk | identified | Chapter 4: Bats Tower | no | no | When conker gets tanked | [Story 1:33:44](https://www.youtube.com/watch?v=3PftWpkdcTc&t=5624s) |
| `0056` | BackgroundAndSuspense | identified |  | yes | no | Maybe part of cutscenes | [Story 1:39:19](https://www.youtube.com/watch?v=3PftWpkdcTc&t=5959s) |
| `0057` | BruteIsUnleashed | identified | Chapter 4: Bats Tower | no | no | The tether finally snaps and Brute is unleashed |  |
| `0058` | BruteMaims | identified | Chapter 4: Bats Tower | yes | no | Plays when Brute the bulldog fish maims one of the catfish | [Story 1:40:41](https://www.youtube.com/watch?v=3PftWpkdcTc&t=6041s) |
| `0059` | BruteChase | identified |  | no | no | Plays when Brute the bulldog catfish chases you | [Story 1:40:56](https://www.youtube.com/watch?v=3PftWpkdcTc&t=6056s) |
| `0060` |  | unidentified |  | no | no | Plays when conker is trying to climp up the slippery pier out of the reach of brute the bulldog catifsh | [Story 1:41:10](https://www.youtube.com/watch?v=3PftWpkdcTc&t=6070s) |
| `0061` | RockSolidClubMusic | identified | Chapter 6: Uga Buga | yes | no | Played while inside the club "Rock Solid" | [Story 1:59:27](https://www.youtube.com/watch?v=3PftWpkdcTc&t=7167s), [Story 2:18:42](https://www.youtube.com/watch?v=3PftWpkdcTc&t=8322s), [Story 2:19:36](https://www.youtube.com/watch?v=3PftWpkdcTc&t=8376s), [Story 2:20:59](https://www.youtube.com/watch?v=3PftWpkdcTc&t=8459s) |
| `0062` | RockSolidSoundbite | identified | Chapter 6: Uga Buga | yes | no | Related to the rock solid club music |  |
| `0063` | HangoverBackgroundMusic | identified | Chapter 1: Hung Over | yes | no | Fairly sure? | [Story 0:08:01](https://www.youtube.com/watch?v=3PftWpkdcTc&t=481s) |
| `0064` | EscapeTedizIsland | identified |  | no | no | Plays as you leave Normandy | [Story 4:12:54](https://www.youtube.com/watch?v=3PftWpkdcTc&t=15174s) |
| `0065` | RaceMP | identified | Chapter 6: Uga Buga | yes | yes | Jet/hoverboard over lava background music ory before you meet the giant in the colosseum | [Story 2:30:50](https://www.youtube.com/watch?v=3PftWpkdcTc&t=9050s) |
| `0066` | GreatMightyPoo | identified | Chapter 2: Windy | yes | no | Instrumental, no vocals | [Story 1:52:08](https://www.youtube.com/watch?v=3PftWpkdcTc&t=6728s) |
| `0067` | MatrixStartFight | identified | Chapter 9: The Heist | yes | no | From the Matrix Parody |  |
| `0068` | WW2Outbreak | identified | Chapter 8: It's War | no | no | Plays during the greyscale propaganda advertisement at the start of the WW2 chapter | [Story 3:24:41](https://www.youtube.com/watch?v=3PftWpkdcTc&t=12281s) |
| `0069` | LeavingThePlucker | identified |  | no | no | Plays when you are leaving the Cock and the Plucker and you spew on the lizard with the stone tablet | [Story 0:05:11](https://www.youtube.com/watch?v=3PftWpkdcTc&t=311s) |
| `0070` | GraveyardBackground | tentative | Chapter 7: Spooky | yes | no | Maybe it is played on to the run up to the graveyard or Dracula castle |  |
| `0071` | PantherKingOverture | identified |  | no | no | Related to the Panther King, possibly plays at the start and end of the game | [Story 0:06:22](https://www.youtube.com/watch?v=3PftWpkdcTc&t=382s) |
| `0072` | SpiltMilk | identified | Chapter 1: Hung Over | yes | no | Missing table leg from the Panther King intro | [Story 0:07:08](https://www.youtube.com/watch?v=3PftWpkdcTc&t=428s) |
| `0073` |  | unidentified |  | no | no |  |  |
| `0074` |  | unidentified |  | no | no | Jingle |  |
| `0075` | GreatMightyPooLair | identified | Chapter 2: Windy | yes | no | Inside the lair of the Great Mighty Poo |  |
| `0076` | PissSilo | tentative | Chapter 4: Bats Tower | yes | no | Seems like it might be the background sound to the bank vault at the end of Bats Towers | [Story 1:28:36](https://www.youtube.com/watch?v=3PftWpkdcTc&t=5316s), [Story 1:38:55](https://www.youtube.com/watch?v=3PftWpkdcTc&t=5935s) |
| `0077` | NormandyLandingMaybe | identified | Chapter 8: It's War | yes | no |  |  |
| `0078` | TedizBunker | identified | Chapter 8: It's War | yes | no | Fairly sure this relates to the TedizBunker |  |
| `0079` | FryingTonightPrelude | identified |  | no | no | Plays before the squirrel gets the electric chair | [Story 3:46:12](https://www.youtube.com/watch?v=3PftWpkdcTc&t=13572s) |
| `0080` |  | unidentified |  | no | no |  |  |
| `0081` | Jingle2 | identified | Other | no | no | Jingle |  |
| `0082` | Jingle | identified | Other | no | no | Wonder if these jingles are like multiplayer menu sound effects or something |  |
| `0083` |  | unidentified |  | no | no | Jingle |  |
| `0084` | TRex | identified | Chapter 6: Uga Buga | yes | yes | Might appear in MP and in Story | [MP1 0:16:00](https://www.youtube.com/watch?v=EiUtagv_SaU&t=960s), [MP1 1:50:13](https://www.youtube.com/watch?v=EiUtagv_SaU&t=6613s) |
| `0085` | MatrixFightPrelude | identified | Chapter 9: The Heist | yes | no |  | [Story 4:21:01](https://www.youtube.com/watch?v=3PftWpkdcTc&t=15661s) |
| `0086` | MatrixSoundbite | identified | Chapter 9: The Heist | yes | no | Related to the matrix parody from the story |  |
| `0087` | DinosaurStatueDramatic | identified | Chapter 6: Uga Buga | yes | no | When you first lay eyes on the dinosaur statue |  |
| `0088` | Cavemen | identified | Chapter 6: Uga Buga | yes | no |  | [Story 2:06:51](https://www.youtube.com/watch?v=3PftWpkdcTc&t=7611s), [Story 2:09:33](https://www.youtube.com/watch?v=3PftWpkdcTc&t=7773s), [Story 2:13:01](https://www.youtube.com/watch?v=3PftWpkdcTc&t=7981s), [Story 2:15:51](https://www.youtube.com/watch?v=3PftWpkdcTc&t=8151s), [Story 2:18:10](https://www.youtube.com/watch?v=3PftWpkdcTc&t=8290s) |
| `0089` | WindGales1 | identified |  | yes | no | Used throughout the game as wind | [Story 3:18:28](https://www.youtube.com/watch?v=3PftWpkdcTc&t=11908s) |
| `0090` | Dracula | identified | Chapter 7: Spooky | yes | no | Plays during the dracula parody chapter, maybe when you are flying around as a bat? | [Story 3:08:58](https://www.youtube.com/watch?v=3PftWpkdcTc&t=11338s) |
| `0091` | GraveyardCemetery | tentative | Chapter 7: Spooky | yes | no | Plays when you are inside the haunted dracula mansion | [Story 3:14:34](https://www.youtube.com/watch?v=3PftWpkdcTc&t=11674s), [Story 3:20:16](https://www.youtube.com/watch?v=3PftWpkdcTc&t=12016s) |
| `0092` |  | unidentified |  | no | no |  |  |
| `0093` |  | unidentified |  | no | no | Also maybe the pier/boardwalk getting chewed up? Not sure. |  |
| `0094` | BombRun | identified |  | no | no | Plays during the bomb run in unga bunga | [Story 2:28:09](https://www.youtube.com/watch?v=3PftWpkdcTc&t=8889s) |
| `0095` | WindGales2 | identified |  | yes | no | Used throughout the game as wind | [Story 0:57:49](https://www.youtube.com/watch?v=3PftWpkdcTc&t=3469s) |
| `0096` |  | unidentified |  | no | no |  |  |
| `0097` | GreatMightyPooLair2 | identified | Chapter 2: Windy | yes | no | Inside the lair of the Great Mighty Poo |  |
| `0098` | MatadorBackgroundMusic | identified | Chapter 2: Windy | yes | no | When Conker is trying to attract the bull | [Story 1:06:40](https://www.youtube.com/watch?v=3PftWpkdcTc&t=4000s) |
| `0099` |  | unidentified |  | no | no | Matador related |  |
| `0100` | MatadorEnd | identified | Chapter 3: Barn Boys | no | no | Matador related |  |
| `0101` | WW2Background2 | identified | Chapter 8: It's War | yes | no |  | [Story 3:28:04](https://www.youtube.com/watch?v=3PftWpkdcTc&t=12484s), [Story 3:31:23](https://www.youtube.com/watch?v=3PftWpkdcTc&t=12683s), [Story 3:32:47](https://www.youtube.com/watch?v=3PftWpkdcTc&t=12767s), [Story 3:59:05](https://www.youtube.com/watch?v=3PftWpkdcTc&t=14345s), [Story 4:02:40](https://www.youtube.com/watch?v=3PftWpkdcTc&t=14560s) |
| `0102` | WW2FinalBoss | identified | Chapter 8: It's War | no | no | Plays for the WW2 Teddiz final boss | [Story 4:05:39](https://www.youtube.com/watch?v=3PftWpkdcTc&t=14739s) |
| `0103` | RidingFranky | identified | Chapter 3: Barn Boys | yes | no | Plays when you are riding frank to attack the haybail, reprises elsewhere possibly | [Story 0:20:01](https://www.youtube.com/watch?v=3PftWpkdcTc&t=1201s), [Story 0:45:40](https://www.youtube.com/watch?v=3PftWpkdcTc&t=2740s), [Story 1:35:34](https://www.youtube.com/watch?v=3PftWpkdcTc&t=5734s), [Story 2:49:32](https://www.youtube.com/watch?v=3PftWpkdcTc&t=10172s) |
| `0104` | TerminatorHayBailBackground | identified | Chapter 3: Barn Boys | yes | no | Background music from the final fight with the terminator haybail (robot version) | [Story 0:47:03](https://www.youtube.com/watch?v=3PftWpkdcTc&t=2823s) |
| `0105` | PantherKing | identified |  | no | no | Panther King |  |
| `0106` | PantherKingNotesShort | identified |  | no | no | Panther King Fanfare |  |
| `0107` | KriplespacLaboratoryShort | identified |  | no | no | Short notes relating to von Kriplespac's laboratory |  |
| `0108` | KriplespacLaboratory2 | identified | Chapter 1: Hung Over | yes | no | Plays during the cutscene of von Kriplespac's Laboratory |  |
| `0109` | FetchMeTheSquirrel | identified |  | yes | no | Probably panther king related also | [Story 1:03:14](https://www.youtube.com/watch?v=3PftWpkdcTc&t=3794s) |
| `0110` | KriplespacLaboratory1 | identified | Chapter 1: Hung Over | no | no | Crazy Scientist Professor Von Kriplespac background sound from the cutscene with his laboratory |  |
| `0111` | BirdyHangoverBackground | identified | Chapter 1: Hung Over | no | no | Fairly sure | [Story 0:08:39](https://www.youtube.com/watch?v=3PftWpkdcTc&t=519s), [Story 0:22:08](https://www.youtube.com/watch?v=3PftWpkdcTc&t=1328s) |
| `0112` |  | unidentified |  | no | no | Fanfare |  |
| `0113` | EndCredits | identified | Other | yes | no | End Credits | [Story 4:43:00](https://www.youtube.com/watch?v=3PftWpkdcTc&t=16980s) |
| `0114` | OminousHaybale | identified | Chapter 3: Barn Boys | yes | no | Plays as the haybail descends from the rafters of the barn | [Story 0:35:59](https://www.youtube.com/watch?v=3PftWpkdcTc&t=2159s) |
| `0115` | SweetCornTaken | identified |  | no | no | Plays when the sweet corn is dragged below the surface by The Great Mighty Poo | [Story 1:50:16](https://www.youtube.com/watch?v=3PftWpkdcTc&t=6616s) |
| `0116` |  | unidentified |  | no | no |  |  |
| `0117` |  | unidentified |  | no | no | Fanfare |  |
| `0118` | TerminatorAgain | identified | Chapter 3: Barn Boys | yes | no | Also related to the fight with the haybail |  |
| `0119` | SadSong1 | identified |  | no | no | Plays when the queen bee is crying over her hive, when Frank is split into two and when Conker farewells his TRex. Possibly reprises elswhere too. | [Story 0:18:55](https://www.youtube.com/watch?v=3PftWpkdcTc&t=1135s), [Story 0:50:07](https://www.youtube.com/watch?v=3PftWpkdcTc&t=3007s), [Story 2:42:42](https://www.youtube.com/watch?v=3PftWpkdcTc&t=9762s) |
| `0120` | AnvilFanfare | identified | Chapter 3: Barn Boys | no | no | Fanfare that plays when the anvil drop after climbing all the way to the top |  |
| `0121` | BerriDanceRadio | identified | Chapter 1: Hung Over | yes | no | Pretty sure | [Story 1:59:27](https://www.youtube.com/watch?v=3PftWpkdcTc&t=7167s), [Story 2:19:55](https://www.youtube.com/watch?v=3PftWpkdcTc&t=8395s), [Story 2:21:49](https://www.youtube.com/watch?v=3PftWpkdcTc&t=8509s) |
| `0122` | BerriKidnapped | identified | Chapter 2: Windy | yes | no | When Berri is kidnapped from her apartment by one of the rock people |  |
| `0123` |  | unidentified |  | no | no |  |  |
| `0124` |  | unidentified |  | no | no | Fanfare |  |
| `0125` |  | unidentified |  | no | no |  |  |
| `0126` | DinosaurStatueOpening | identified |  | no | no | Plays when the mouth of the dinosaur statue open and the lizard priest you spewed on at the start of the game walks out and down it's tongue | [Story 2:11:36](https://www.youtube.com/watch?v=3PftWpkdcTc&t=7896s) |
| `0127` | DinosaurStatueSneezes | identified |  | no | no |  |  |
| `0128` | MafiaWeasels | identified |  | no | no | Associated with Mafia Weasels | [Story 2:23:50](https://www.youtube.com/watch?v=3PftWpkdcTc&t=8630s), [Story 2:25:20](https://www.youtube.com/watch?v=3PftWpkdcTc&t=8720s), [Story 4:29:02](https://www.youtube.com/watch?v=3PftWpkdcTc&t=16142s) |
| `0129` | WeaselMafiaSuspense | identified | Chapter 6: Uga Buga | yes | no | Plays in one of the long table scenes involving the weasel mafia | [Story 2:24:48](https://www.youtube.com/watch?v=3PftWpkdcTc&t=8688s), [Story 4:19:02](https://www.youtube.com/watch?v=3PftWpkdcTc&t=15542s) |
| `0130` | SadSong2 | identified |  | no | no | Plays when the queen bee is crying over her hive, when Frank is split into two and when Conker farewells his TRex. Possibly reprises elswhere too. | [Story 0:50:07](https://www.youtube.com/watch?v=3PftWpkdcTc&t=3007s), [Story 2:42:42](https://www.youtube.com/watch?v=3PftWpkdcTc&t=9762s) |
| `0131` | Babe | identified | Chapter 6: Uga Buga | yes | no | Plays when Conker meets Babe after defeating the giant caveman | [Story 2:44:04](https://www.youtube.com/watch?v=3PftWpkdcTc&t=9844s) |
| `0132` | BarrelBreak | identified | Chapter 7: Spooky | no | no | Plays when the barrel breaks the dam which lets you swim to spooky chapter to meet Greg where he is fishing for catfish | [Story 2:55:24](https://www.youtube.com/watch?v=3PftWpkdcTc&t=10524s) |
| `0133` | GunfireAndRicochets2 | identified | Chapter 8: It's War | yes | no | Bullets and ricochets |  |
| `0134` |  | unidentified |  | no | no | Fanfare |  |
| `0135` | WW2Background1 | identified | Chapter 8: It's War | yes | no | Plays through WW2 chapter | [Story 3:28:20](https://www.youtube.com/watch?v=3PftWpkdcTc&t=12500s), [Story 3:31:23](https://www.youtube.com/watch?v=3PftWpkdcTc&t=12683s), [Story 3:32:47](https://www.youtube.com/watch?v=3PftWpkdcTc&t=12767s), [Story 3:59:21](https://www.youtube.com/watch?v=3PftWpkdcTc&t=14361s), [Story 4:02:44](https://www.youtube.com/watch?v=3PftWpkdcTc&t=14564s) |
| `0136` |  | unidentified |  | no | no | Multiplayer? |  |
| `0137` | FinalBoss2 | identified | Chapter 9: The Heist | yes | no | Airlock open possibly | [Story 4:34:08](https://www.youtube.com/watch?v=3PftWpkdcTc&t=16448s) |
| `0138` |  | unidentified |  | no | no | French National Anthem? |  |
| `0139` | WW2End | identified | Chapter 8: It's War | yes | no | Used through the WW2 Chapter, when squirrel comrades die, when Rodent dies and at the end of the chapter a couple of times too | [Story 3:39:42](https://www.youtube.com/watch?v=3PftWpkdcTc&t=13182s), [Story 4:10:24](https://www.youtube.com/watch?v=3PftWpkdcTc&t=15024s), [Story 4:14:10](https://www.youtube.com/watch?v=3PftWpkdcTc&t=15250s), [Story 4:17:35](https://www.youtube.com/watch?v=3PftWpkdcTc&t=15455s) |
| `0140` |  | unidentified |  | no | no | Panther King related | [Story 2:23:49](https://www.youtube.com/watch?v=3PftWpkdcTc&t=8629s), [Story 4:27:44](https://www.youtube.com/watch?v=3PftWpkdcTc&t=16064s) |
| `0141` | FinalBossStem | identified | Chapter 9: The Heist | yes | no | Plays as matrix Berri dies and the Panther King starts coughing |  |
| `0142` | PantherKingAlienReveal | identified | Chapter 9: The Heist | no | no | When the Panther King turns into Alien | [Story 4:32:05](https://www.youtube.com/watch?v=3PftWpkdcTc&t=16325s) |
| `0143` |  | unidentified |  | no | no | Fanfare |  |
| `0144` | AlienReturns | tentative | Chapter 9: The Heist | no | no | Seems to be when the Alien returns after being thrown outside the airlock |  |
| `0145` | EndCutscene | identified | Other | no | no | End cutscene when conker is on the throne before the credits role | [Story 4:42:00](https://www.youtube.com/watch?v=3PftWpkdcTc&t=16920s) |
| `0146` |  | unidentified |  | no | no | No idea what this, wondering if it is part of the Greg underworld where he grabs his first tail? |  |
| `0147` | NormandyLanding2 | identified | Chapter 8: It's War | yes | no |  |  |
| `0148` |  | unidentified |  | no | no |  |  |
<!-- sequence-table:end -->

## Limits

No label asserts an original Rare title, a soundtrack track name or a runtime
trigger. Promote a label to a proven association only from a consumer: the
code that requests the sequence index for a scene, event or menu.
