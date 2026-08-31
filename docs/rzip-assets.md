# RZIP and asset extraction

RZIP is a storage envelope, not an asset type. A compressed texture, model, or
other resource is still an asset after its four-byte length header and raw
deflate stream are removed.

Use the indexed layout rather than searching the ROM for deflate signatures:

```text
ROM
├── game archive
│   ├── XOR-encoded code-chunk offset table
│   ├── 4 KiB RZIP code chunks → game/code.bin
│   ├── code padding
│   ├── one RZIP data chunk     → game/data.bin
│   └── data padding
└── asset index
    ├── bank 00 index
    │   ├── compressed entry    → decoded .bin
    │   └── uncompressed entry  → copied .bin
    ├── bank 01 index
    └── …
```

The ECTS beta uses a related but distinct layout: its game code and data are
stored raw, followed by one contiguous stream of 8,427 length-prefixed RZIP
chunks and then the two-level indexed banks. The extractor records flat and
indexed entries separately; neither location determines the decoded payload's
semantic asset type.

The first game-archive word identifies the compressed data section. The
XOR-encoded table following it identifies every compressed code chunk; its last
offset is the end of compressed code. Code/data padding is therefore separated
exactly rather than treated as an asset.

The later ROM asset table contains eight-byte `(relative offset, size/flags)`
records for each bank. Each bank begins with another eight-byte table whose
flags say whether an entry is compressed. This second index is the source of
truth for individual asset boundaries. RZIP entries are decompressed; raw
entries are copied unchanged. Payload-format identification is deliberately a
later step because a `.bin` may be a model, texture, audio stream, text table,
or another nested container.

Extract the active US ROM:

```sh
./conker rzip-extract
```

Extract either supported debug dump, including byte-swapped `.v64` input:

```sh
./conker rzip-extract \
  --profile debug
```

Extract the ECTS raw game and both asset collections:

```sh
./conker rzip-extract --profile ects
```

Output defaults to `build/rzip/<profile>/` and includes `manifest.json`,
decompressed game code/data, and one decoded `.bin` per indexed asset. ECTS
also writes sequential entries below `assets/flat/`. Useful options are:

- `--manifest-only` validates and inventories every entry without writing the
  decoded payloads.
- `--keep-rzip` additionally preserves the raw compressed entries beside their
  decoded forms.
- `--output <dir>` selects a different generated directory.
- `--force` replaces that exact output directory on a repeat run.

The manifest records ROM coordinates, compression flags, decoded lengths, and
output paths so later asset-type tools never need to rediscover boundaries.
