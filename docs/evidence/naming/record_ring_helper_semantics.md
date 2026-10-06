# Length-prefixed record ring helpers

Source: `game_70200.c`. Signed argument widths are retained; the terminal
reader remains numeric.

| Symbol | C name | Span |
| --- | --- | --- |
| `15043A00` | `record_ring_init` | `0x20` |
| `15043A20` | `record_ring_copy_in` | `0xA8` |
| `15043AC8` | `record_ring_copy_out` | `0xA8` |
| `15043B70` | `record_ring_advance` | `0x48` |
| `15043BB8` | `record_ring_write` | `0xEC` |

The existing four-word view contains a buffer address at `+0`, byte capacity
at `+4`, read cursor at `+8` and write cursor at `+0xC`. Initialization stores
the first two and clears both cursors; a null object is a no-op. The copy
helpers split byte-counted copies at the buffer boundary and return the
advanced wrapped cursor. Their `s32 *` buffers advance in bytes, not words.
They do not update a ring object or enforce occupancy. Advance performs the
same cursor calculation without copying. Its first `s32` parameter remains
present despite being unused beyond the original ABI home store.

For positive requested payload length n, write stores a four-byte signed
count equal to round_up_4(n), then copies that rounded number of payload bytes.
It does not generate padding: it can read up to three bytes beyond the
requested length from the caller's storage. Total occupancy is four plus the
rounded count. The space test reserves a strict gap and rejects an exact fit;
equal cursors represent empty. In the observed four-byte-aligned 64-byte ring,
at least four bytes remain unused. Return one means insufficient space;
zero means a write or a null-source/zero-length no-op. These signed interfaces
do not validate general capacities, cursors, counts or memory extents.

The unchanged reader `15043CA4` supports this interpretation: equal cursors
return zero; otherwise it consumes the full record and returns the stored
rounded count. Only when destination capacity is smaller than that count does
it copy capacity minus one, append NUL and skip the rest. It does not otherwise
guarantee NUL termination. Its retained baseline `CURRENT (100)` is solely the
missing trailing NOP at registered `+0xE8`; its literal definition/body and
registered span remain untouched by this naming batch.

Complete original spans in `reference/game/us/asm/42D50.s` agree with the
checksum-validated original game image. Main ROM JALs at `12570`, `125A8` and
`12700` reach write, init and read through their `8504xxxx` runtime aliases.
Main initializes `800427A0` with buffer `800427B0` and capacity `0x40`, then
registers its text callback. The existing `init_12560.c` transport is used by
MP3 text output; the helpers retain generic names and no audio implementation
or behavior changes are introduced. Source-group boundary evidence remains in
[the existing audit](../game_remaining_upstream_c_groups.md).
