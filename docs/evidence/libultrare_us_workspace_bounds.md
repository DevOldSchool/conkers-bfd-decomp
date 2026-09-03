# US Rare library workspace review

This library-only review separates address ranges actually used by the matched
code from the original source object's BSS allocation. The former can be
bounded further; the latter cannot yet be assigned safely. No BSS map, archive
allocation or progress count changes in this pass.

Inputs are the US ROM with SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, ROM-derived game code with SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`, and the already exact Rare
sound-player, playback, stream and decoder objects. Runtime addresses below
are not offsets into the compressed ROM.

## MP3 storage

| Runtime interval | Used storage | Evidence and limit |
| --- | --- | --- |
| `0x800E0D80:0x800E0E1A` | Playback fields | The last accessed byte is `dualchannel` at `+0x99`; the local C view rounds up to `0x9C`. This does not assign the gap before `0x800E0E20`. |
| `0x800E0E20:0x800E0E2C` | Three asset pointers | Matched playback and utility loads/stores identify the table, lookup and Huffman base pointers. |
| `0x800E0E2C:0x800E0E2D` | Assets-loaded byte | Matched playback initialization and lazy-load checks. |
| `0x800E0E30:0x800E0E34` | Allocated power-table pointer | Playback allocates `0x8000` bytes and the decoder fills 8,192 floats through the pointer. The allocation is dynamic, not BSS here. |
| `0x800E0E38:0x800E1078` | Four 36-float window slots | The matched decoder uses a `0x90` row stride and initializes through element 35 of row 3. Row 2 is reserved by this layout; initialization does not write it. |
| `0x800E1078:0x800E107C` | Decoder power-table pointer | Initialization copies the allocation pointer into this slot. |
| `0x800E1080:0x800E1480` | First scaling table | Matched initialization writes indices 0 through 255 as floats. |
| `0x800E1480:0x800E1880` | Second scaling table | Same complete 256-float loop, ending at the stream base. |
| `0x800E1880:0x800E9D00` | Stream view, `0x8480` bytes | Matched stream code uses callbacks at `+0x8478` and `+0x847C`, with the latter occupying the final four bytes. |

The stream starts at the address loaded by `mp3main_start_file`. Its final
callback ends exactly where a separately used global begins at `0x800E9D00`.
For example, the adjacent `lui`/`lw` pair at main `0x80007DC0:0x80007DC8`
loads that global, and game `0x151EEFF0:0x151EEFF8` clears it. These are
independent neighbor references, not inferred padding or another stream field.

The stream's exact used extent is stronger evidence than a guessed allocation
size. It still does not reveal which original object declared it. Initialization
clears only the `unk6a64[0]` subarray, not an allocation identified by a
whole-stream `sizeof` or memset. The independent Perfect Dark source instead
allocates its stream dynamically, so its storage ownership cannot be copied
into Conker. The gaps between the other globals likewise remain unassigned.

The external bindings in `config/game/us-sdk.ld` are retained. The matched
objects continue to emit no BSS for this workspace. That reconstructed layout
does not prove the original objects had the same extern declarations.

## Sound-player storage

The initialized `g_SndPlayer` pointer fixes the instance base at `0x80042850`.
The matched constructor and consumers access `waveBase` at offset `0x54`,
establishing a used view through `0x800428A8` (`0x58` bytes). The separately
accessed volume-table pointer occupies `0x800428B8:0x800428BC`. The surrounding
raw allocation ends at the independently matched surround BSS at `0x800428C0`.

Neither the `0x10` gap after the player view nor the final four bytes have an
independently identified owner. The constructor's heap allocation with stride
`0x58` is for `struct sndstate` voice records, not this static player instance;
coincidentally equal sizes are not allocation evidence.

Perfect Dark revision `169ed48bdcbfb3b568b028bd5bebb27680073514` declares its
player instance in `src/lib/naudio/osc.c`, alongside an oscillator array and
unused words. Its `n_sndplayer.c` separately declares an unused word before
the volume-table pointer. Conker's matched oscillator uses a heap pool and
has only its already mapped 16-byte BSS section, followed by the independently
matched sequence-player BSS. That materially different layout prevents using
Perfect Dark's source ordering to assign the remaining Conker gap.

The complete `0x80042850:0x800428C0` interval therefore stays raw. A future
promotion needs independent allocation/ownership evidence, not an array of
padding added solely to fill the desired range.
