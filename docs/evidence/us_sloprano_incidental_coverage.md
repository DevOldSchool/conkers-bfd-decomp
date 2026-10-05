# Sloprano incidental coverage

The seven-stream listening edit omitted at least one supported reaction. It
must not be described as complete. This pass restores ROM stream 0237 and keeps
remaining coverage gaps explicit. All outputs are local and ignored.

| Material | Soundtrack | Gamerip | Native evidence | Current output |
| --- | --- | --- | --- | --- |
| User-reported throat clear / “me me me” | Around 0:24, user description | Source equivalence unresolved | No validated source match | Missing; unresolved |
| Reaction, stream 0237 | 112.095 s, 2 s waveform correlation 0.797 | 112.099 s, correlation 0.871 | First-hit capture 23.908 s, correlation 0.875 | Restored at 112.095 s |
| Principal streams 0239, 0240, 0241, 0242, 0238 | Excerpts supported | Excerpts supported | Selected native excerpts supported | Preserved unchanged |
| Ending 0271 → 0272 | Excerpts supported; earlier than gamerip | 292.108 → 317.115 s | Captured order and 25.020 s onset separation | Editorial join preserved |
| Sequence 0074 sting | Closing role candidate | Short spectral match | Short spectral match | Candidate ending preserved; sequence title remains unknown |
| Other inter-verse speech/effects | User reports further omissions | Not exhaustively inventoried | Available captures contain mixed gameplay sound | Unresolved, not claimed restored |

Stream 0237's native source SHA-1 is
`d5e6dacd3b6bbfa457bf67171bf858b32f6a4b44`; retained MPEG-frame SHA-1 is
`32caae7c310951455486cbfb5b55774ff7c0ae35`. Native-first-hit retained request
changes at 23.783 s and the matched clip starts about 124 ms later. The native
projection gain is approximately 0.479; the reconstruction uses the established
0.47 and 22,018 Hz clock. These are excerpt estimates, not exact decoder claims.
Only one two-second match above 0.4 correlation was detected per reference;
this is not proof of exhaustive occurrences. No words were independently heard
or assigned by this pass.

The all-stream prefix search parses all 453 native streams and compares up to
one second from each against both full recordings. Internal-source searches use
450 MP3s and 835 samples at least 0.75 seconds long: 141 soundtrack templates
at two-second intervals across the track, plus ten finer opening templates from
23–27.5 seconds. The grid is deliberately bounded and can miss short, pitched,
effected or masked sounds. The opening's best raw-stream score was only 0.501;
short sample-prefix matches can be tones/percussion and are not speech proof.
No extra source beyond 0237 is validated. All 2,258 decoded samples were inventoried;
not every possible native pitch, overlap or controller state was searched.

The soundtrack 24–28-second excerpt does not show a strong waveform match in
the cached gamerip, instrumental gamerip, native opening or previous mix. This
is insufficient to call it an album-exclusive phrase. Further identification
needs time-stamped listening of each omission and native sample/voice dispatch
with actual pitch, or a coherent longer source match. Reference recordings are
comparison evidence only, never inserted into the reconstructed recording.

Current WAV SHA-1: `d473ec7b272fb9868f66f9fb1ae59ae7b0040a52`, duration
282.093 seconds. Previous SHA-1 `dc7938a4f81567b2a86d197111f9985b637f3b68`
is preserved in `us-sloprano-v1`. Only frames in 112.095–114.528 seconds change;
peak remains 29,488 PCM levels with zero clipping. Stable numeric IDs and all
149 sequence labels retain their previous confidence.
