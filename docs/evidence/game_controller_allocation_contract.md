# Controller allocation word and pointer contract (US)

The local declaration of `func_1515D480` in `game_AEB40.c` described an
integer result and a byte argument. Independent raw evidence supports the
existing `void *(s32)` contract used by other callers:

- `1515D488` saves the whole incoming word; `1515D48C` reloads it
- The helper multiplies that word by `0x60` before the allocator call
- The allocator's returned pointer is saved, passed unchanged to the clear
  helper, and restored into `v0` for return
- Existing declarations in `game_174BF0.c` and `game_1844C0.c` agree with
  the pointer result and full-word input

The selected deferred caller `func_150832AC` passes its saved word directly
at `15083320` and stores the returned address in a four-byte slot at `+0x304`.
The local declaration is corrected to `void *func_1515D480(s32)`. The result
is explicitly converted to a `u32` address word and stored through `u32 *`.
The only other same-unit user is the
untouched raw `15083AC8`; no accepted C function in this unit calls the helper.
The callee implementation and declarations in other units are unchanged.

The original post-loop `s32 *` test reads the last stored slot after a
positive iteration count, or the preceding metadata word when the count is
zero. An earlier pointer-typed store was rejected because rereading a pointer
object through an integer lvalue is not a compatible access. Equal widths
and favorable machine-code comparisons do not establish source validity.

The corrected source retains integer-word storage: corresponding signed and
unsigned integer lvalues may access the same representation. The explicit
pointer-to-word conversion is target-specific. SGI's 1994 manual documents
32-bit integer and pointer types in `-32` mode and bitwise-exact conversions
when the integer is large enough; this is not a portable ISO-C pointer
encoding. See [the SGI C manual, printed pages 114–116](https://irix7.com/techpubs/007-0701-080.pdf#page=125)
and [the C90 signed/unsigned access rule](https://www9.open-std.org/JTC1/SC22/WG14/issues/c90/issue0053.html).
No aliasing-bypass option or new storage object is used.

The source-valid corrected candidate scores `CURRENT (735)`. Both promoted
locals receive only an unsigned-byte load or constants 3 and 5, so their
value range and the final byte store are preserved. The original loop,
branches, word test at `+0x300`, byte store at `+0x301`, and unrelated final
call are unchanged. Rejected pointer-object variants are diagnostic history,
not valid intermediate candidates.

The last valid prior candidate scored 935. An older 830 record predates the
repair of an undeclared local and is stale. Exact older variant artifacts
were unavailable; the recorded generic 250-variant search was not repeated.
The pass stops after the initial contract trial, two targeted revisions, and
the required source-validity correction; no further matching search is made.

The best 735 candidate remains deferred with original assembly active. The
remaining differences concern selector-branch scheduling, pointer/index
register roles, and a shorter instruction stream. This contributes no new
match bytes and does not complete the mixed source unit. No narrow formal,
forced storage, new aggregate bounds, compiler flag, shared header, or tool
change was introduced.

The eleven accepted members independently retain full-span `CURRENT (0)`.
Their canonical clean regression batch returned `BATCH_COMPLETE`; all 31
member positions and registered linked spans, the `0x3670` text extent, and
the complete US ROM/GAME/RSP outputs remain unchanged. Allocated sections and
relocations also equal an independently compiled baseline source object.
The existing mapped rodata remains 276 ROM-identical payload bytes plus
12 zero alignment bytes. All 1,703 tests passed in the ordinary suite
(37 tool-dependent skips) and pinned toolchain/ROM suite (one skip).
Progress and whitespace checks passed. These are regression checks and
contribute no new C match credit.
