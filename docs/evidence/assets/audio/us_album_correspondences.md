# Retail US album correspondence review

The original two supplied listings were checked on 2026-10-04. All 18 soundtrack and 27
unreleased entries were downloaded locally and searched against the 149 retail US
sequence renders and all 453 sanitized MP3 streams. Downloads, full rankings,
fingerprints and channel renders remain under ignored `build/reference/all-albums/`.
No reference recording is included in the generated listening desk.

The table records **candidate material/segment correspondences**, not verified
full recording identities. None has been independently confirmed by listening in
this review. Numeric IDs remain the ROM identities; confidence of the original
contributor labels is unchanged. Scores are similarity measures, not probabilities.
Reference track order was never used to identify a ROM entry. Runtime selection
and claims of unused content require separate evidence.

| Album | Verified full identities | Tentative entries | Unresolved |
| --- | ---: | ---: | ---: |
| Soundtrack | 0 | 18 | 0 |
| Unreleased Tracks | 0 | 25 | 2 |
| Additional site-labelled gamerip | 0 | 71 | 0 |

## Per-entry candidates

`S` identifies CSeq bank 0x17, entry 3; `M` identifies MP3 bank 0x16.
An entry can combine several segments, or share material with another entry.
The detailed offsets, reference recording SHA-1, source hashes, roles, competing
primary candidates and unresolved reasons are in
[soundtrack-reference.json](../../../../config/soundtrack-reference.json).

| Album entry | Candidate IDs | Status |
| --- | --- | --- |
| Soundtrack 01: Conker The King | S0024 | tentative |
| Soundtrack 02: Windy & Co. | S0001 | tentative |
| Soundtrack 03: Beardy Erm, Birdy | S0111 | tentative |
| Soundtrack 04: Poo | S0053 | tentative |
| Soundtrack 05: Ole`!!! | S0098, S0099, S0100 | tentative |
| Soundtrack 06: The Old Chap | S0010 | tentative |
| Soundtrack 07: Sloprano | S0066, M0238, M0239, M0240, M0241, M0242, M0271, M0272 | tentative |
| Soundtrack 08: The Uggas | S0087, S0088, M0253 | tentative |
| Soundtrack 09: Rock Solid | S0061, S0121, S0062 | tentative |
| Soundtrack 10: Don Weazo | S0128, S0129, S0140 | tentative |
| Soundtrack 11: Surf Punks | S0065 | tentative |
| Soundtrack 12: Bats | S0090, S0148 | tentative |
| Soundtrack 13: Undead | S0091 | tentative |
| Soundtrack 14: War | M0354 | tentative |
| Soundtrack 15: Exit The Beach | S0064 | tentative |
| Soundtrack 16: Enter The Vertex | S0085, S0086, S0067 | tentative |
| Soundtrack 17: Conker The King (Reprise) | S0145, S0113, M0408 | tentative |
| Soundtrack 18: Heist | S0030 | tentative |
| Unreleased Tracks 01: nintendo & rare logos | S0054 | tentative |
| Unreleased Tracks 02: the fabled panther king | S0071, S0140 | tentative |
| Unreleased Tracks 03: sad mrs. bee | S0002, S0119 | tentative |
| Unreleased Tracks 04: barn boss fight | S0103, S0004 | tentative |
| Unreleased Tracks 05: haybot wars | S0104 | tentative |
| Unreleased Tracks 06: electric wires | No accepted candidate | unresolved |
| Unreleased Tracks 07: slam dunk | S0120 | tentative |
| Unreleased Tracks 08: near bats tower | S0001 | tentative |
| Unreleased Tracks 09: you brute! | S0013 | tentative |
| Unreleased Tracks 10: bats tower | S0015, S0018 | tentative |
| Unreleased Tracks 11: conker drunk | S0055, S0011 | tentative |
| Unreleased Tracks 12: getting sober | S0011 | tentative |
| Unreleased Tracks 13: the brute attacks! | S0056 | tentative |
| Unreleased Tracks 14: sweet corn drowning | S0115 | tentative |
| Unreleased Tracks 15: sneezing statue | S0127 | tentative |
| Unreleased Tracks 16: bomb run | S0094 | tentative |
| Unreleased Tracks 17: danger lurks | S0003 | tentative |
| Unreleased Tracks 18: inside the wasp's fortress | S0001 | tentative |
| Unreleased Tracks 19: boss fight | S0004, S0103 | tentative |
| Unreleased Tracks 20: windy graveyard | S0031, S0089 | tentative |
| Unreleased Tracks 21: zombie attack | No accepted candidate | unresolved |
| Unreleased Tracks 22: it's war | S0101, S0135 | tentative |
| Unreleased Tracks 23: tediz attack | S0032 | tentative |
| Unreleased Tracks 24: casualty department | S0048 | tentative |
| Unreleased Tracks 25: mines chasing conker | S0052 | tentative |
| Unreleased Tracks 26: elevator music | M0138 | tentative |
| Unreleased Tracks 27: let's leg it | S0049 | tentative |

## Interpretation and unresolved work

- `Windy & Co.`, `near bats tower` and `inside the wasp's fortress` share
  sequence 0001 material. The album edits may use different layers and loops.
  This comparison does not collapse them into one full recording.
- `barn boss fight` primarily resembles 0103, while `boss fight` primarily
  resembles 0004. Their reused theme explains cross-matches.
- `Sloprano`: 0066 retains the contributor's instrumental description. The
  seven MP3 candidates are separate streamed segments. Vocal content and the
  correct assembly remain unclassified; the preview does not invent a vocal mix.
- `War` is strongly represented by MP3 0354 across about 49 seconds, rather than
  assigning its name to scene-related sequence 0068 on context alone.
- `Conker The King (Reprise)` has opening/credits leads in 0145, 0113 and MP3
  0408. Broad-spectrum 0113 excerpts align near album 69.2 seconds; its pitch
  results are weaker. Exact edit and stream content require listening.
- `you brute!`: channels 2 and 3 of 0013 align at the opening and later sections.
  Original brute-labelled 0057–0060 are not supported as this entry.
- `casualty department` aligns with 0048. Its prior contributor note suggesting
  electrical wiring is retained as uncertain, not used to label `electric wires`.
- `bomb run` is a short loop/cue candidate (0094), not a 110-second full render.
- `windy graveyard`: 0031 supplies a musical lead; 0089 is an ambience component,
  not a full song. Prior graveyard-labelled IDs do not establish this recording.
- `tediz attack` and `sneezing statue` rely partly on broad-spectrum results.
  Their candidates remain especially dependent on listening/runtime mixing.

`electric wires` remains unresolved. Primary music/stream candidates are weak;
short-window, channel and modest tempo/pitch checks did not produce a reliable
music lead. Sample 0206 resembles a 2.60-second portion by broad spectrum, but
other unrelated samples have similar scores. It is an effect/timbre lead only.

`zombie attack` remains unresolved. Pitch results and channel/tempo checks are
weak. Broad results for 0093 and stream 0211 compete with unrelated effects and
envelope patterns; they do not establish a complete soundtrack identity.

Neither unresolved result establishes absence from retail US or runtime non-use.
Native mixing, controller changes, channel muting, filters, reverb and loop
expansion are not reproduced by the approximation.

## Comparison scope

The primary comparison uses 61 semitone power bands, a 11025 Hz STFT with
2048-sample windows / 1024-sample hops, adjacent frame averaging, frame
normalization and stationary per-band component removal. It slides up to 11.89
seconds through each reference. Source windows advance by half a window and
include the terminal window; sources below 2.23 seconds are excluded there.

Follow-ups searched shorter cues across the full sequence/MP3 banks, rendered
individual channels of 22 candidate/context sequences for six weak entries,
checked five entries at speeds 0.90–1.10 and pitch shifts -2..+2 semitones, and
searched 32 broad logarithmic bands (20–5513 Hz) across 1,175 eligible sequence,
MP3 and sample sources of at least one second. Broad timbre/envelope results
also match unrelated effects and were not accepted alone as identities.
Double-precision variance avoids false correlations in nearly silent windows.

The metadata retains the exact hashes of the local comparison scripts. Full
rankings and raw windows are preserved locally. Selected evidence windows and
counts are copied into the review metadata, with source/hash guards preventing
their transfer to changed extracted bytes.

## Local preview and validation

The separate `build/assets/soundtracks/us-albums/index.html` embeds metadata
and uses local relative audio/CSS/JS paths. Earlier `us` and `us-review` outputs
are preserved. Album entries expose candidate sequence/stream controls and
explicit tentative/unresolved status. Browser drafts keep the same ROM/ID keys.
Reference recordings are not served by or copied into the listening desk.

The targeted audio, soundtrack and model preview tests cover render behavior,
portable HTML, preserved outputs, MP3 compatibility, all 45 reviews and totals,
shared-theme aliases and changed-source/ROM evidence rejection. Browser/static
validation results are recorded in the local QA file after completion.
Function matching remains paused.

## Additional gamerip comparison

The [71-track Unofficial Soundtrack listing](https://downloads.khinsider.com/game-soundtracks/album/conker-s-bad-fur-day-gamerip)
was checked and all 71 recordings downloaded locally on 2026-10-04. Each was searched
against all 149 sequence renders and 453 sanitized MP3 streams using the same method.
All original 45 recordings were also searched against all 71 new recordings. Rankings,
fingerprints and inbound downloads remain under ignored `build/reference/gamerip/`.
The [site info file](https://vgmtreasurechest.com/soundtracks/conker-s-bad-fur-day-gamerip/khinsider.info.txt)
confirms the public classification and 2025-01-24 update, but gives no ROM revision,
extraction method, recording chain or source checksums. Technical provenance is unverified.

The table gives candidate material IDs, with exact album-specific titles. All remain
**tentative**, including scores near 1.0: approximate excerpt alignment is not independent
listening, complete recording identity, or proof of runtime selection. Detailed selected
windows, competing candidates, source/render/reference hashes and roles are retained in
`additional_albums` and `additional_comparisons` in the metadata. The original two album
inventories and their 43 tentative / two unresolved coverage are retained separately.

| Gamerip entry | Candidate IDs | Best primary excerpt score |
| --- | --- | ---: |
| 01: Nintendo & Rare Logos | S0054 | 0.939 |
| 02: The Cock and Plucker | S0034 | 0.966 |
| 03: The Cock and Plucker (Alternate) | S0034 | 0.991 |
| 04: Conker the King | S0024 | 0.992 |
| 05: Doesn’t Look Too Good Tonight | S0069 | 0.991 |
| 06: The Fairy Panther King | S0071, S0072 | 0.968 |
| 07: Beardy Erm, Birdy | S0111 | 0.834 |
| 08: Windy & Co. | S0001 | 0.805 |
| 09: Windy & Co. (Whistling) | S0001 | 0.802 |
| 10: Sad Mrs. Bee | S0002 | 0.994 |
| 11: Stealthy Conker | S0003 | 0.974 |
| 12: The Mad Chase | S0004 | 0.992 |
| 13: Got the Beehive! | S0005 | 0.932 |
| 14: Windy & Co. (Bees) | S0001 | 0.704 |
| 15: Windy & Co. (Barn Boys) | S0001 | 0.767 |
| 16: Mad Pitchfork | S0006 | 1.000 |
| 17: Haybot | S0114 | 0.968 |
| 18: Buff You | S0103 | 0.995 |
| 19: Haybot Wars | S0104 | 0.935 |
| 20: Broken Franky | S0119 | 0.995 |
| 21: Frying Tonight | S0134 | 0.790 |
| 22: Poo | S0053 | 0.994 |
| 23: Poo (Instrumental) | S0053 | 0.999 |
| 24: Ole!!! | S0098 | 0.999 |
| 25: Windy & Co. (Catfish Pond) | S0001 | 0.691 |
| 26: Bullfish Territory | S0013 | 0.711 |
| 27: The Cognitive Cogs | S0018 | 0.996 |
| 28: Bats Tower | S0015 | 0.994 |
| 29: Totally Tanked | S0055 | 0.912 |
| 30: The Old Chap | S0010 | 0.998 |
| 31: The Catfish Swindle | S0056 | 1.000 |
| 32: Bullfish’s Revenge | S0057 | 0.963 |
| 33: Catfish Dinner | S0058 | 0.972 |
| 34: Under Pressure | S0059 | 0.983 |
| 35: Sloprano | S0066, M0272 | 0.976 |
| 36: Sloprano (Instrumental) | S0066 | 0.994 |
| 37: Mysterious Land | S0009 | 0.987 |
| 38: The Ugas | S0088 | 0.938 |
| 39: The Ugas (Chant) | S0088 | 0.989 |
| 40: Rock Solid | S0061, S0121, S0062 | 0.998 |
| 41: Don Weazo | S0128 | 0.987 |
| 42: Bomb Run | S0094 | 0.852 |
| 43: Surf Punks | S0065 | 0.998 |
| 44: Brown Loincloth Time | S0029 | 0.984 |
| 45: Raptor vs. Cavemen | S0027 | 0.996 |
| 46: Sad Fangy | S0130 | 0.973 |
| 47: Sad Jugga | S0131 | 0.990 |
| 48: Bats | S0090 | 0.998 |
| 49: Undead | S0091 | 0.983 |
| 50: Call to Arms | S0068 | 0.990 |
| 51: It’s War | S0101 | 0.992 |
| 52: The Eel | S0135 | 0.831 |
| 53: Sole Survivor | S0037 | 0.983 |
| 54: Assault | S0044 | 0.990 |
| 55: Kill the Enemy! | S0045 | 0.906 |
| 56: The Mine Chase | S0052 | 0.908 |
| 57: Casualty Department | S0048 | 0.961 |
| 58: The Cavalry | S0079 | 0.956 |
| 59: Chemical Warfare | S0049 | 0.911 |
| 60: The Experiment | S0102 | 1.000 |
| 61: Rodent Down | S0139 | 0.978 |
| 62: Countdown | S0136 | 0.590 |
| 63: Exit the Beach | S0064 | 0.980 |
| 64: Enter the Vertex | S0085, S0086 | 0.980 |
| 65: The Panther and the Weasel | S0140 | 0.998 |
| 66: Berri Bites the Bullet | S0141 | 0.824 |
| 67: The Alien | S0142 | 1.000 |
| 68: Conker the King Reprise | S0145 | 0.934 |
| 69: Credits | S0113 | 0.851 |
| 70: Credits (Alternate) | S0113 | 0.453 |
| 71: Heist | S0030 | 0.985 |

The closer reference adds 25 preferred candidate sequence IDs (78 total). Four were
originally unknown: 0027 Raptor vs. Cavemen, 0045 Kill the Enemy, 0134 Frying Tonight
(ending only), and 0136 Countdown (cue only). No original contributor label or confidence
is changed. `title_resolutions` explains four preferred-name changes: 0018 from related
bats tower material to The Cognitive Cogs, 0113 from the older Reprise composite to
Credits, 0119 from shared sad mrs. bee material to Broken Franky, and 0140 from related
Don Weazo material to The Panther and the Weasel. Earlier titles remain aliases and
album correspondences, with their uncertainty retained.

Important distinctions:

- Sloprano and Sloprano (Instrumental) share 0066 backing material (best scores 0.976
  and 0.994 respectively). Stream 0272 supplies a short separate lead. Vocal content
  and full vocal assembly remain unclassified. Poo and Poo (Instrumental) similarly
  share 0053 instrumental material; the reference’s variant label is not a vocal render.
- Fairy Panther King aligns with 0071 and 0072 at different positions. Shared themes
  also appear across the Windy variants, Broken Franky / Sad Fangy, Don Weazo / Panther,
  The Experiment / Alien, and Sole Survivor / Rodent Down. Strongest variants remain
  distinct; related excerpts do not prove interchangeability.
- Call to Arms strongly aligns with 0068, while the original War aligns with MP3 0354.
  Both are retained with different album-specific titles and numeric source identities.
- New Reprise aligns with 0145 and Credits with 0113. Credits (Alternate) has weaker
  partial 0113 leads but overlaps the older Reprise edit strongly (0.914, 42 windows).
  Exact layering, loops, edits and alternate recording identity remain unverified.
- Frying Tonight aligns with only the 3.53-second 0134 ending near reference 41.98s.
  The Eel aligns with only 11.89s at the 0135 opening; Countdown has a 6.87-second
  0136 cue near 60s. These are segment leads, not complete render reconstructions.
- Electric wires resembles the early portion of Frying Tonight (bridge 0.475 for
  12.07s; shorter windows up to 0.616), while 0134 aligns with the late ending. Direct
  0134 vs electric wires is only 0.201. Transferring the ending ID across different
  portions would be unsupported, so electric wires remains unresolved.
- Zombie attack has no reliable new counterpart (best bridge 0.135). Tediz attack
  has a weak Assault bridge, but direct 0044 correspondence remains weak (0.333 over
  4.09s); the earlier qualified 0032 lead remains and no new ID is accepted.

No recording or asset was uploaded. The listening desk contains only locally derived
owned-ROM assets; public comparison recordings remain outside its static serving root.

## Canonical vocabulary and final unresolved checks

The user selected the 71-entry gamerip listing’s exact titles/capitalization as
canonical. Of 78 sequence title candidates, 68 now use that vocabulary; ten remain
qualified older-reference leads with no established gamerip counterpart. Seven MP3
candidates use Sloprano; the other four retain qualified source-specific older titles.
Older album inventories retain their original public titles; those are aliases and
source references, not competing canonical names. `canonical_title_resolutions`
records the transitions. 0066 prefers Sloprano (Instrumental), 0053 Poo (Instrumental),
and 0088 The Ugas (Chant), each still qualified as material correspondence rather
than complete recording identity. No generic title-case transformation was used.

A final phase-sensitive check compared 2,187 decoded native samples at least 0.1s
long against the two unresolved references. It used mono11025Hz, a third-order
100–4000Hz bandpass, zero-mean normalized waveform correlation, four source positions,
up to0.5s sample windows, and up to2s windows for selected sequence/stream leads.
Seven broad-spectrum sample leads also received speeds0.5/0.75/1.25/1.5/2 checks.
An exact-offset synthetic control passed; known 0068 vs gamerip Call to Arms aligned
at0.997 over2s, demonstrating sensitivity for that known correspondence.

Electric wires’ highest tiny match was sample2106 (0.754 over0.100s); the best
half-second sample result was1736 (0.432). The earlier broad sample0206 lead gave
only0.194 waveform correlation. Instrument141 uses the tiny2106/2109/2110 samples
in sequence0027; rendering its eight relevant channels produced best pitch0.266,
with no strong window. These are generic short fragments, not an electric wires ID.

Zombie attack’s highest tiny match was sample1871 (0.643 over0.120s), a sample
reused by many unrelated sequences. Its best half-second sample result was2149
(0.339); selected0093 gave0.279 over2s and stream0211 only0.080. The extra0027
channels stayed below0.157. The earlier broad-spectrum0.761/0.805 leads therefore
lack corresponding distinctive waveform support. Both entries remain unresolved.
Full results are ignored local `build/reference/gamerip/unresolved-waveforms.json`
and `unresolved-channels27.json`; concise evidence is retained in the metadata.

This does not exclude filtered, layered, looped, repitched or dynamically modulated
runtime audio. Existing contributor notes do not establish scene-level ID selection;
named source searches and bank/instrument links did not supply such provenance.
Native runtime capture/scene tracing has not been performed. Function matching remains
paused. Browser tools can start playback and inspect decoding state, but do not deliver
its sound to model perception; no listening/transcription tool is exposed. Independent
listening was technically unavailable in this session, not merely deferred.

Useful listening shortlist:

- Compare original electric wires (15s) with gamerip Frying Tonight’s early0–20s
  and its late ending near42s; listen to0134 separately. The ending ID cannot be
  transferred to the earlier effects portion. Sample0206 is only a weak effect lead.
- Compare original zombie attack (19s), especially9–17s, with sequence0093 (5.57s),
  stream0211 near41–49s, and sample0661. These remain competing effect/timbre leads.
- For weaker partial naming, review gamerip Credits (Alternate) against0113 and
  the older Reprise edit; Countdown near60s against0136; The Eel opening against0135.

No UI expansion or duplicate preview audio was needed for these checks. Identity
changes still require distinctive sustained alignment, independent listening and/or
runtime evidence; titles alone do not settle them.
