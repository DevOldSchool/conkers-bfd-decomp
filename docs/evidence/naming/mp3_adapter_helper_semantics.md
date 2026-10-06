# Main MP3 adapter and text-record helpers

Source: `init_12560.c`. The conditional stop helper and mismatched game ring
reader remain numeric.

| Symbol | C name | Span |
| --- | --- | --- |
| `80012560` | `mp3_text_enqueue_callback` | `0x28` |
| `80012588` | `mp3_adapter_init` | `0x44` |
| `8001263C` | `mp3_play_asset` | `0xAC` |
| `800126E8` | `mp3_text_read_record` | `0x30` |
| `80012718` | `mp3_play_asset_spatial` | `0xB8` |
| `800127D0` | `mp3_is_playing_paused_or_loading` | `0x50` |

## Initialization and text records

The initializer first invokes substantial MP3 state initialization at runtime
`85016170`, then initializes `D_800427A0` with storage `D_800427B0` and capacity
0x40 and installs runtime callback `D_10012560`. The first callee clears the
0xA0-byte playback state, allocates envelope/sample/filter storage, establishes
volume/pan defaults and installs the DMA callback. Original caller `80008FC0`
supplies `D_8003E370`; this is broader than text-transport initialization alone.

The text callback ignores its first argument, forwards its payload and length
to the record writer and discards the writer's result. The matched MP3 producer
in `lib/libultrare/src/libultrare/mp3/main.c` reads an embedded record and invokes
the callback with `strlen(message)+1`. "Text" follows that API; it does not
identify the records as subtitles or attach a speaker identity.

The read wrapper forwards destination/capacity and the ring reader's result
unchanged. Original consumer `15080228` reads at `15080250/15080314` with
capacity 0x100 until zero is returned, interpreting structured fields in
records beginning with byte 0x4C. The [record-ring audit](record_ring_helper_semantics.md)
proves the transport's important limits:

- A four-byte header stores the payload length rounded up to four bytes. The
  writer copies that rounded payload count; it does not generate padding
- Insufficient space returns one, silently discarded by this callback
- An empty read returns zero; other reads return the stored rounded payload
  length, not the number of bytes copied
- Truncation copies capacity minus one bytes, appends NUL, and consumes the
  whole record. Positive capacity is an implicit precondition on that path
- A nontruncated read appends no NUL. The wrapper does not guarantee a general
  NUL-terminated string API

The retained full-span mismatch in `15043CA4` remains untouched.

## Asset playback and spatial parameters

`8001263C` resolves resource path (bank 0x16, asset ID) through `1502B020`;
this resolves a ROM address without allocating or loading the MP3 payload. It stores
the requested ID in `D_800427F4` before testing lookup success. A nonzero address
and size lead to volume, immediate-pan and filter setup, then `mp3_play_file`.
Asset 0xD2 selects filter parameters (0,0), versus (0xA,0x2AF8) otherwise.
Caller `8001A3FC` supplies volume 0x7FFF and pan 0x40 at `8001A43C`. No music, speaker
or scene identity is inferred from these IDs or values.

The spatial wrapper obtains XYZ from object +0x14/+0x18/+0x1C, truncates them
to integers and computes pan/volume through `800114D0`. A nonzero field +0x318
bypasses that calculation, using the supplied volume and centered pan 0x40.
That field's identity is unresolved. Calls `1506BB90/15077ED4` supply the object
selected by `D_800D154C`. Return one is unconditional, even if downstream lookup
or playback cannot succeed; it must not be interpreted as a success report.

## Enumerated playback-state predicate

`800127D0` returns true exactly for states 1 (playing), 2 (paused) and 5
(loading). The [matched playback reconstruction](../libultrare_us_mp3_playback_reconstruction.md)
and original code `1F2960.s` establish these states: starting writes 5 at
`151F2B8C`, successful opening changes 5 to 1 at `151F2FF8`, and pausing writes
2 except that loading state 5 becomes load-paused state 6. The underlying
`mp3_is_busy` also recognizes 6 and 7 (unpausing), which this wrapper excludes.
The explicit enumerated name avoids calling it a general busy/active predicate.
Original caller `1501DF20` uses the result before invoking `mp3_stop`.

`800125CC` remains numeric. Its exception for argument 0x1E and
`D_800BE9F8 == 0x1B` is retained without assigning an incompletely established transition
role.

## Full-span evidence

Original main reference `12560.s` covers all 592 registered target bytes,
including the final predicate's padding, and agrees with the
checksum-validated US ROM. Original game code and the existing fully matched
MP3 reconstruction support the roles above.
