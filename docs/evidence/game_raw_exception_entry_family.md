# US exception-entry source family

Evidence kind: `structural_analysis`. The complete raw range
`0xADAF0:0xAE5B0` contains four callable entries: `func_150ADAF0`,
`func_150AE280`, `func_150AE35C`, and `func_150AE36C`. The raw assembly index
recognizes all four, while the independent linear CSV folds `func_150AE280`
into the preceding handwritten routine.

`func_150AE280` is an externally referenced entry: `func_1509F850` calls it
directly. Its code restores the saved stack pointer at `D_800D3858` and
branches back into the handwritten exception routine, establishing a deliberate
alternate entry rather than a speculative split. Owned game-data words select
`func_150AE35C` and `func_150AE36C` at `0x80089D14` and `0x80089E70`.

The 2,752-byte range is 16-byte aligned, no conditional branch crosses its
outer endpoints, and its SHA-1 is
`77f4adddbc625d3d881dba5c7ecd89e3f4a8a58e`. Every member remains raw assembly.
