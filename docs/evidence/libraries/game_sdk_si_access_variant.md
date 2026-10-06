# US game-overlay SI access wrappers

The complete text at `0x1F0350:0x1F0410` is reproduced by
`libultrare:siacs_game.o`: three functions, 192 bytes. This is an explicit
reconstruction of the overlay's state bindings, not an assertion that a
stock object's entire BSS can be placed at one address.

## Identity and section ownership

PI and SI access wrappers share an instruction template. Here, the decoded
references identify SI unambiguously: the enable flag is `0x8002BE20`, the
queue is `0x80042AA8`, and the slow-path create call is `0x10025700`. Each is
already part of the main executable's verified SI object. The local message
buffer differs from the main copy: the overlay passes `0x800E0D20` to
`osCreateMesgQueue`, with a capacity of one message.

The stock object's BSS contains both its static message buffer and its global
queue. Assigning the whole section to the game buffer address would not
explain the retail queue's main address. The reconstructed source instead
declares all three existing storage references externally. The game buffer
uses an unsized array declaration: this records its pointer and required
single-slot use without claiming a boundary for the surrounding raw game BSS.
No stock BSS or data section is silently discarded, and no duplicate queue
or initialization flag is emitted. The resulting object's only runtime
section is the complete `.text`.

The bodies retain the stock SI algorithm and typed SDK interfaces from the
existing Rare headers. `__osSiCreateAccessQueue`, `__osSiGetAccess`, and
`__osSiRelAccess` occupy offsets `0`, `0x50`, and `0x94`, with sizes `0x50`,
`0x44`, and `0x2C`. The existing neighboring `mtxcatf.o` and `sirawdma.o`
boundaries fix the start and end independently. No raw work items or source
skeletons occupied the range before this archive mapping.

## Exact evidence

The authority is the US ROM SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a` and game-code SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`, with independent raw assembly
at `reference/game/us/asm/1F0350.s`. The complete object template has one
occurrence in the game image. Every relocation was resolved from these bindings:

| Symbol | Runtime address |
| --- | --- |
| `__osSiAccessQueueEnabled` | `0x8002BE20` |
| `__osSiAccessQueue` | `0x80042AA8` |
| `__conker_game_siAccessBuf` | `0x800E0D20` |
| `osCreateMesgQueue` | `0x10023790` |
| `osSendMesg` | `0x10023580` |
| `osRecvMesg` | `0x10023440` |
| `__osSiCreateAccessQueue` | `0x10025700` |

Applying the actual HI16, LO16, and MIPS26 relocation calculations to the
compiled bytes yields an exact 192-byte comparison, SHA-1
`4abb188563b5019cf842c2cb568ca6c9f8583798`. The object MD5 is
`12695c5fdd5d81324211ef94be1b533d`, labeled as a Conker reconstruction in
the archive checksum list. This proves the text and runtime references;
it does not recover the original author's declaration placement or the
original game-buffer BSS section extent.

## Validation

On 2026-09-02, the complete US ROM passed `./conker build --profile us`
with SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`. The clean
`./conker game-build --refresh` also passed, preserving all 2,072,880 game-code
bytes and SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
All 151 Python tests passed; generated progress and whitespace checks passed.
The main and game comparison maps retain independent raw assembly.
