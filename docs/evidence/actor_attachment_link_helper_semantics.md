# Actor attachment-link helpers

Seven already matched functions in `src/game/game_179F30.c` receive
source-local aliases. Numeric linkage, signatures and all operations remain
unchanged. Here an attachment is an auxiliary object linked through actor
+0x2F4, not a claim about a model, joint or physical attachment.

| Symbol | C name | Bytes |
| --- | --- | ---: |
| `1514D310` | `actor_attachments_request_cleanup` | 160 |
| `1514EBA4` | `attachment_link_allocate` | 120 |
| `1514EC1C` | `actor_attachment_add` | 196 |
| `1514ECE0` | `attachment_link_find_by_selector` | 92 |
| `1514ED3C` | `attachment_link_find_by_object` | 80 |
| `1514ED8C` | `actor_attachment_unlink` | 100 |
| `1514EDF0` | `actor_attachment_remove_object_links` | 128 |

## Allocation, insertion and lookup

A link is a managed kind-0x24 object in list row one. Its payload pointer is
at +0x10, attachment-chain next/previous at +0x14/+0x18, and signed selector
at +0x1C. The existing C field called `owner` at +0x10 is the linked payload,
not the actor owning the chain. These attachment-chain links are distinct
from the managed object's +4/+8 links. They also differ from the global
descriptor chain `D_800C3EE0` (+0x54/+0x58 links), whose head `15004F00`
clears. No field or type is renamed here.

The allocator requests extra-byte count +0x20 from `15167A68`, initializes
payload, selector and null chain links, and returns null on failure. It does
not insert into an actor chain. Extra size and selector are unchecked.
`1514EC1C` ignores a null payload; otherwise it allocates and prepends a link
to actor+0x2F4, repairing the previous head's backward link. The result is
returned through the existing s32 pointer-carrier ABI.

Insertion failure has a payload side effect: it reads the signed dispatch ID
at `D_8008ABE8[selector]+2`. An ID other than -1 selects a callback from
`D_8008AB58` and passes the payload; -1 instead calls `1516972C(payload)`.
The -1 sentinel belongs to the descriptor's dispatch ID, not the selector.
This is not a harmless registration failure, nor a guarantee of immediate
payload deallocation.

Both finders walk +0x14 and stop at the first match. One compares the signed
16-bit selector; the other compares the full payload word. They return 0/1
and, when the optional output pointer is nonnull, write the matching link
or null. No selector-range, chain-validity or cycle guard is introduced.

## Link removal and payload cleanup are separate

`1514ED8C` repairs the actor head and both neighbors, saves the payload,
requests removal of the link through `1516972C`, then returns the saved
payload. It does not invoke payload cleanup. Original kind-0x24 record `8008BBF8`
has a null custom-removal callback at +0x28, so this link-removal path reaches
`15169804` and moves the link to removal kind one. `1514EDF0` repeatedly searches
and unlinks every matching payload node, saving the next pointer before
removal; the payload itself is not destroyed by this helper.

`1514D310` walks the actor chain, saving each next pointer, dispatching payload
cleanup when the descriptor's dispatch ID is not -1, and requesting removal
of each link. Unlike insertion failure, dispatch ID -1 skips payload cleanup.
It returns one even for an empty chain. It does not directly clear actor+0x2F4
or repair this chain, and the name makes no synchronous-free guarantee.

## Original consumers and acceptance

Original bodies are in `reference/game/us/asm/14CA80.s`. The original
`141970.s` consumer finds selector 0x1A, reads the payload, and links a newly
created timed-handler object. `19CF70.s` tests payload membership before
adding selector 0x11. Cleanup wrappers in `158BD0.s` and `C5370.s` remove
attachment links before requesting their own payload cleanup, independently
establishing the link/payload distinction. Original cleanup callback table
`8008AB58` starts with `1514E830`, `1514E850`, `1514E87C`: these delegate
to `1516972C`, `1518E308` then `1516972C`, and `1515F10C`, respectively.
Actor removal `15060F28` in
`55E50.s` calls the bulk cleanup helper before continuing its removal path.

All 876 registered bytes require full-span CURRENT (0), existing layout,
clean batch, full tests, progress, whitespace, RSP and exact main/game images.
Raw siblings and uncertain descriptor relationships remain numeric; no
character, model or selector identity is inferred.
