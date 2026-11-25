# US CPU texture frame storage

Seven C arrays reconstruct 1,004 bytes of frame resource words referenced by the
207-entry CPU texture descriptor table. The 2,484-byte descriptor source uses
those arrays and explicit element offsets. All 205 resolved pointer
destinations match the original words. These are INFO verification definitions;
the original archive still supplies runtime data. Original object boundaries
and source-unit completion are not inferred from the grouping.

| Start | Exclusive end | Bytes |
| --- | --- | ---: |
| `800901F0` | `80090204` | 20 |
| `8009073C` | `8009075C` | 32 |
| `800907A4` | `800907AC` | 8 |
| `80090818` | `80090B60` | 840 |
| `80091520` | `80091564` | 68 |
| `800915BC` | `800915D8` | 28 |
| `800917E4` | `800917EC` | 8 |

## Native extent evidence

Original effect-type record 97 at `8008B4A8 + 97 * 52` pairs updater
`func_1515BAE0` with renderer `func_1515BBF0`. The updater passes object byte
`+0x10` as texture selector, speed at `+0x1C`, phase at `+0x18`, and flags at
`+0x12` to `func_1514401C`. That helper reads descriptor byte `+4` using the
native twelve-byte stride and computes `(count << 16) - 1`. With flag bit two
set, positive overflow caps the phase to that boundary and stops the speed.

The paired renderer passes the same selector and phase to `func_15142E24`.
Its selector helper `func_1514306C` uses `phase >> 16` to index four-byte frame
words through the descriptor's first word. The drawing path also carries the
phase through two eight-bit shifts before the indexed load in `func_15095060`.
Together these consumers establish the count field and frame-word width.

Seven complete registered native function spans are authenticated against the
ROM, including raw assembly where present. A bounded interpreter additionally
executes 975 cap-path cases, covering all 189 original descriptor counts and
phase edges, for 29,787 original instructions. These checks demonstrate the
cap branch; other flags can terminate, wrap, reverse or retain negative phases.
They do not establish safety for every caller or runtime activation of all rows.

The 187 pointer-bearing descriptors yield 186 distinct pointer/count spans.
Their union is 932 bytes. Lists around `800909A0..800909C0` overlap, so defining
each as an independent array would duplicate storage. Seven union groups retain
one copy of each word and use `&D_BASE[index]` for interior references. This is
source organization based on the native accesses, not a claim about original
compiler objects. Descriptor rows 189 through 206 each point at one of the 18
words `80090B18..80090B5C`, which extend `D_80090818` to 210 entries and reach
the descriptor table. The scalar encodings 1844 and zero generate no frame-pointer relocations.

## Validation

Base commit: `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7`, plus uncommitted work.
The pinned compiler and independent native comparison match all 3,200 bytes
across the seven new arrays and descriptor replacement, including all 187
symbolic pointers. Forty-eight compiler tail bytes are excluded. All 825 other
GAME objects preserve their allocated bytes, symbols and relocations. The owned
descriptor preserves its defined symbol, layout, every resolved byte and all
187 destinations; its undefined symbol set changes exactly from 186 individual
names to seven shared bases. The full 2,072,880-byte GAME code image is unchanged.

All 3,574 byte/pointer corruption cases were rejected, together with 3,200
independent ROM-byte mutations. `./conker test` passed its 3,033-test suite with
eight skips in 223.065 seconds. `./conker build --assets` passed in 154 seconds
wall time; independent extraction reproduces all 67,108,864 US ROM bytes with
SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`.

The full report and acceptance audit passed with no compilation errors:
63,325,727 / 65,120,512 matched data bytes, a gain of 932; 1,794,785 remain.
Complete data, code and function measures are unchanged. All 27,301 prior asset
input hashes and 11,836 asset object hashes are preserved. Report SHA-256:
`f3312aaaf6317c11bbca8c722b505ae4906f95c2856b15dad735381e409bd6a3`.
Source fingerprint:
`745ea530504aa9b30afb8c5ffdb8bbd138e9316eb09bd566db7170e03381c051`.
Preparation took 371.6 seconds; report and validation took 26.8 seconds.

The accompanying JSON records the native spans, instruction anchors, pointer
intervals, union groups and candidate audit. Temporary pilots are stored under
`build/us/data-completion/cpu-frames-*`.
