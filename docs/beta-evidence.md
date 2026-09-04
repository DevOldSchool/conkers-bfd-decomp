# Beta evidence index

The debug and ECTS beta ROMs are evidence sources, not build or progress
targets. Retail US remains the only profile that can satisfy function matching,
source-unit integration, and progress completion.

The owned ROMs use these canonical ignored paths:

```text
roms/baserom.us.beta.v64
roms/baserom.us.beta.ects.v64
```

The ECTS raw code/data boundaries come from its executable ROM loader. See
[ECTS game layout](evidence/ects_game_layout.md) for the correction to the
older upstream offsets and the resulting evidence-address changes.

Run the index through the pinned toolchain:

```sh
./conker beta-index
```

The first run disassembles all three game overlays and caches function metadata
under `build/beta-index/<profile>/`. Later runs reuse an index while its game
code SHA-1, code VRAM, pinned toolchain identity, disassembly options, and index
format remain unchanged. Pass `--refresh` to deliberately rebuild every cached
index.

`build/beta-index/report.json` contains:

- normalized ROM and decompressed game-code SHA-1s;
- order-preserving, relocation-insensitive function correlations;
- retained original source paths and their direct code references;
- beta source anchors transferred to retail only through strong correlations;
- explicit flags confirming that the report changes no progress state.

Confidence has deliberately narrow meaning:

- `strong`: a fingerprint is unique in both builds and belongs to a matching
  sequence of at least two functions;
- `candidate`: an isolated unique fingerprint or a repeated neighbour inside a
  strongly anchored sequence;
- ambiguous fingerprints are counted but never arbitrarily paired.

These fingerprints ignore relocation-sensitive instruction bits, so even a
strong correlation is a navigation aid rather than byte-match evidence. A
source path can identify likely original ownership, but it does not establish
where the corresponding object begins or ends. Register a source unit only
after reviewing separate US boundary evidence.
