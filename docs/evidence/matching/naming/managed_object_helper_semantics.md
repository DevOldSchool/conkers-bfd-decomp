# Managed-object list and lifecycle helpers

Source: `src/game/game_1944C0.c`. Heterogeneous callback-managed lists include
timer and model-resource objects; names do not imply actor-only or
particle-only ownership.

| Symbol | C name | Bytes |
| --- | --- | ---: |
| `15167A68` | `managed_object_allocate` | 112 |
| `15168A2C` | `managed_object_queue_free` | 32 |
| `15168A4C` | `managed_object_link` | 80 |
| `15168A9C` | `managed_object_unlink` | 116 |
| `15168B10` | `managed_object_change_kind` | 52 |
| `15169040` | `managed_objects_broadcast_event` | 48 |
| `15169804` | `managed_object_queue_removal` | 32 |
| `15169824` | `managed_object_unlink_and_free` | 44 |

## Allocation and kind lists

`D_800DCE50` provides two rows of 104 list heads. An object's byte +1 selects
the row, byte +0 records its kind, and pointers +4/+8 are previous/next.
Kind records at `8008B4A8` have stride 0x34.

The allocator forwards its size and remaining allocation controls to
`10003C6C`. On success it stores the row byte, links the requested kind, and
stores arg4 (the fifth parameter) at byte +0xC. That last field's meaning is not assigned.
It does not promise whole-object initialization. Row/kind bounds are unchecked;
linking uses the full kind argument for indexing but stores its low byte.

Linking inserts at the head and repairs the prior head's previous pointer.
Unlinking repairs the head and both neighbors, without freeing the allocation
or clearing the removed object's own links. Changing kind unlinks and relinks
in the same row; even an unchanged kind moves the object to the head.

The original timer constructor `15149130` calls the allocator at `15149188`
for kinds 0x23/0x5F. Their records at `8008BBC4`/`8008C7F4` identify timer
update, draw and event callbacks. The model-resource constructor `1513B5E0`
calls at `1513B6A0` for kinds 0x38/0x54; kind 0x38's record at `8008C008`
selects `1513B798`, `1513B83C` and `1513BA78`. These independent consumers
support the generic managed-object domain.

## Staged removal

Original kind-zero record `8008B4A8` selects `15169824` as its update callback;
kind-one record `8008B4DC` selects `15168A2C`. The original updater `151670C0`
loads record +0 and dispatches it while walking both list rows. The queue
helpers reclassify the object to zero or one, respectively, establishing
kind one -> kind zero -> unlink/free. The names promise no fixed number of
frames. `15169824` unlinks, then calls allocator free `10004074`; this does
not establish subordinate-resource cleanup.

Custom callback wrappers `1516972C`/`1516979C` remain numeric: their default
paths alone do not prove uniform semantics for every custom callback.

## Event broadcast

`15169040` forwards the payload and u8 event code to `15169070` with bounds
zero and 104. That worker clamps the lower bound to at least two through
`15143D18`, so the effective half-open range is kinds 2..103 in both rows.
Removal queues zero/one are excluded. It preserves next pointers while
walking, invokes common pre-handler `1516968C`, then invokes nonnull
kind-record +0x1C event callbacks. A kind without its own callback still
receives the common pre-handler. The timer records independently identify
+0x1C as established event handler `15149434`.

## Evidence and acceptance

The complete original bodies and list/event/update consumers are in
`reference/game/us/asm/167010.s`; timer/model constructors and their original
initialized callback records corroborate the domain. Registered spans total
516 bytes. No raw sibling implementation, new source boundary or
asset/character identity is claimed.
