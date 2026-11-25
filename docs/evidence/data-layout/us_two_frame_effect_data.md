# US two-frame effect texture

The 20-byte range `8009060C..80090620` contains two resource words, 2990 and
2988, followed by a twelve-byte descriptor pointing back to them. Its stored
count is two, dimensions are 32 by 44, and format/size fields are two/one.
Descriptor byte five is natural zero alignment.

The original `1517AA20` masks the random result with one before passing it to
`1517A644`. That constructor saves the argument, allocates effect type nine,
and copies the argument's low byte to object offset `9F`. The native allocator
and list insertion retain the type. Type nine's original callback record
selects renderer `1517A3A0`, which forwards offset `9F` to `1517A9A8`. On a
cache miss, that wrapper passes descriptor `80090614` and the selector shifted
left eight to `15094F70`; the common frame consumer shifts it back right eight.
Thus this constructor/render path selects both frame words.

All eleven involved native functions are checked over their complete registered
spans against original ROM instructions. The producer window is executed for
1,024 inputs covering every low byte across four high-word patterns. Its exact
AND instruction independently establishes that higher bits cannot affect the
selector. This proof assumes successful allocation and the existing ABI. It
does not claim gameplay activation, global lifetime invariance, or bounds for
other callers and constructors.

The C definition retains a real pointer to its own frame array. It is an INFO
verification owner; runtime storage still comes from the original GAME archive.
Twelve compiler-tail bytes are excluded from its twenty-byte payload. Neither
the aggregate grouping nor its name claims the original source-object boundary.

Base commit: `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7`, plus uncommitted work.
The pinned scratch object and independent native comparison match 20/20 bytes
and the symbolic pointer. Integrated acceptance passed.

The actual linked INFO object matches all twenty bytes and its pointer; all
875 prior GAME objects retain identical allocated bytes, symbols and
relocations. The complete 2,072,880-byte GAME code image remains exact. All
22 native byte/pointer/addend corruptions and twenty independent ROM-byte
mutations are rejected. The full suite passes 3,038 tests with eight skips.
The dedicated GAME and asset builds pass, and independent extraction matches
the entire 67,108,864-byte ROM.

The final report credits 63,332,753 / 65,120,512 data bytes, leaving 1,787,759.
Complete data and all code/function measures are unchanged. All 27,323 prior
asset source hashes and 11,847 asset object hashes are preserved. Report SHA-256:
`7c9e4ea5489e3c74111d37ebb14fa0382222b6c994b8496d5ffa175315f74436`.
