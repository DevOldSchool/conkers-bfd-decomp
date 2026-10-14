# US animation-control reconstruction

The reviewed subset of bank `0F` reconstructs **82 entries / 9,143 stored bytes**
from typed animation routes, timed events, action phases and behavior programs.
The native loader `func_1503D660` selects bank `0F`, relocates its three optional
header pointers and exposes the route table at offset 16. This evidence describes
stored native programs; it does not claim that gameplay activates every route.

## Native records

The 16-byte header contains behavior-map, collision-table and action-table
offsets, followed by the action-table byte length. All selected entries have no
collision table. The codec derives the offsets and length from editable lists.

`func_1503D484` walks eight-byte routes until descriptor 999 and relocates their
optional event pointer relative to the route-table base. `func_1505E650` and
`func_1505E0C4` consume the descriptor and duration-table halfwords. Shared event
pointers retain shared list references; the encoder creates each event stream
once in physical order.

`func_1506AD30` reads twelve-byte timed events: a float frame, opcode byte at +7,
and a full argument word at +8. The original upper opcode bytes are all zero;
they are generated, never editable opaque storage. The terminator is the native
999.0 frame with zero opcode and argument. Each selected event stream is bounded
by a route pointer and terminator; unexplained gaps are rejected.

`func_1505E7CC` establishes the 24-byte action stride and selector byte at +0.
`func_1505E874` reads the sound word at +4, response byte at +8 and three phases
at +10/+14/+18. Each phase has an animation halfword, speed percentage byte and
flags byte. `func_1505959C` independently reads the third phase's flags at +21.
Zero bytes +1..3, +9 and +22..23 are generated alignment, inferred from these
native field widths, stride and uniform zero storage. This does not establish
an original C structure declaration; nonzero alignment bytes are rejected.

`func_1507BB28` selects eight-byte behavior-map records using the byte at +4;
`func_1503D45C` relocates their pointers relative to bank payload +16. The map
ends with a zero record. Three zero alignment bytes are generated per binding.
`func_1507BC14` reads opcodes below 247 as five-byte instructions with four
parameter bytes. Bytes 247..255 are single-byte markers; `func_15075400` scans
and branches across this same grammar. Opcode 0 maps through `D_80086730` to
`func_1507735C`, a native no-op. Complete zero instructions therefore remain
explicit instructions in the editable source, including those after a branch.
Only the final 0..3 zero bytes are generated four-byte alignment. A four-byte
fragment is rejected, rather than being presented as a complete instruction.

The decoded entry ends with minimal generated 16-byte alignment. Every selected
entry also reproduces its original compressed stream using a fresh level-six
raw-DEFLATE encoder and the native four-byte decoded-length prefix.

## Sources and credit

`./conker animation-control build` creates editable `controls.json`, a checked
manifest and backing under `build/assets/animation-control/us/bank0F/`. Backing
preserves unselected entries and the outer directory; those **69,265 bytes get
no new matching credit**. Make links the generated whole-bank object. Native
objdiff compares only the 82 reconstructed physical ranges from that actual
linked object against fresh semantic output and independent ROM bytes.

Existing source edits, missing files and concurrent changes fail without being
overwritten. Explicit `recover --bank 0F` backs up the existing inputs first.
Seventeen full registered consumer spans are checked against the original ROM.
The bank's whole-file SHA-256 is
`17bbf2135d211f6934a46a66d31a765045f4f9ff39f0600a9343da4affb371fd`.

## Independent validation

An independent reader checks all 898 routes, 173 timed events in 78 streams,
27 actions, 1,366 behavior instructions, 78 markers and 173 map bindings.
All **9,720 semantic mutations** change exactly the expected original fields.
All 34 consumer endpoint mutations are rejected, and all 26,057 prior unique
editable-source hashes remain unchanged. Seven focused tests cover the format,
source preservation, recovery, races and actual linked-object credit.

The other 70 entries remain excluded: 49 contain unresolved collision fields,
17 contain incomplete instruction tails, two contain unexplained event gaps,
and two contain unexplained alignment or other storage. No rendered appearance,
activation evidence, or source format is inferred from byte size alone.

Full batch acceptance is recorded below when complete.

## Accepted batch

The full US asset build reproduced all 67,108,864 ROM bytes in 110 seconds.
All 2,617 Docker tests passed in 137.017 seconds (eight existing skips).
Native objdiff, progress and whitespace checks passed. The report adds exactly
9,143 matched and complete Data bytes, bringing matched Data to
**63,027,192 / 65,120,512 (96.78547%)**. Code and denominators are unchanged.
All prior asset proofs and 26,057 unique editable-source hashes remain intact.
The only prior unit measure change is the corresponding reduction in bank 0F's
unreconstructed storage.

Tested base commit: `094102644c4c2f5aefaa0fc4b609416918f66f58` plus uncommitted
changes. Source fingerprint:
`20a73102c5c38d31d2e18263d92206f2a5a5560f0cdb33d9744138e18f882992`.
Report SHA-256:
`8a46f1e1b8911d638fb201bc8e51b51a4b993ba21378eb42647ff3d337baaf97`.
