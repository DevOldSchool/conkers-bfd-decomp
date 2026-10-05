# Actor attachment, opacity, scale and animation utilities

Five existing matched C helpers use source-local aliases, preserving numeric
linked symbols, signatures, declarations and operations. The names describe
shared actor utilities, without identifying a character or gameplay event.

| Symbol | C name | Span |
| --- | --- | --- |
| `15033E28` | `actor_collect_attachments` | `0x5C` |
| `15033E84` | `actor_find_first_attachment` | `0x40` |
| `1506196C` | `actor_get_view_opacity` | `0x3C` |
| `15062BDC` | `actor_set_scale_and_refresh_bounds` | `0x134` |
| `1507C324` | `actor_copy_animation_time_with_end_cap` | `0x4C` |

## Attachment queries

Both queries traverse `D_800C3EE0` via descriptor +0x54 and compare descriptor
byte +0 with actor byte +0x3B. Collection writes every matching descriptor to
the caller's pointer array and returns the count, without checking capacity.
The other helper returns the first matching descriptor or null. Order is
head-to-tail list order, without an age, visibility or nonzero-owner filter.

Constructor `15030AF4` allocates the 0x5C-byte descriptor, links it through
+0x54/+0x58 at `15030BC8..15030BE0`, and copies actor +0x3B to descriptor +0
at `15030BE8..15030BF4`. The [bank-09 constructor audit](us_expression_attachment_constructors.md)
independently establishes this attachment family. Caller `1508DC24` collects
attachments at `1508DF68`, then examines their +6 action/tag and sometimes
removes them. First-attachment calls at `15052FD0/150D7960` similarly check
for null before inspecting +6.

## Per-view opacity

`1506196C` multiplies unsigned actor[7] by unsigned actor[0xB + viewIndex].
If the product is 0xFE01 (255*255), it returns 255; otherwise it returns the
product shifted right eight bits. This is floor(product/256) with a full-opacity
exception, not division by 255 or nearest rounding. The caller supplies the
view index; no index check is added. Calls `1502CA50/1502CB1C` pass the draw
wrapper's view argument, and `15030EC8` passes the attachment renderer's view
register. The [alpha audit](us_character_alpha_frontier.md) corroborates these
fields; subsequent rendering can still override or modulate the result.

## Scales and bounds

`15062BDC` stores its two float scales at actor +0x14C/+0x150. Unless model
byte +4 is 0xFF, it scales signed dimensions from `D_800D1C90[model]` into
actor +0xD2/+0xD4/+0xD6 and +0xE4/+0xE6/+0xE8, then refreshes both pairs
of reciprocal dimension ratios through `15062AC4/15062B84`. The first scale
multiplies defaults +0x20/+0x1A; the second multiplies +0x22/+0x24/+0x1C/+0x1E.
Float-to-integer truncation, signed-halfword narrowing, negative scales and
existing declarations remain unchanged. Model 0xFF skips the bounds refresh
but still receives the scale stores.

Calls from model assignment at `15083884`, script scale setting at `15076DDC`
and interpolation at `15053798/150537E4/15053834/1505387C` establish its shared
role. Bounds getters `1515C1A0/1515C244` return the paired dimensions and actor
position with their respective +0xD6/+0xE8 vertical offsets. The two families
are not assigned a stronger collision/visibility distinction here.

## Animation time copying

`1507C324` obtains both actors' animation-state pointers at +0x2D0. If either
is absent, it does nothing. Otherwise it copies second actor state +8 into
first actor state +8, then caps it from above at destination state +0x18 minus
1.0, using the original <= comparison. Negative times are not clamped to zero;
there is no looping, finite-value or animation-ID compatibility check.
Frame fetch `1502D824` reads +8 at `1502D8EC`, truncates it at `1502D8F8`, then
derives interpolation values, establishing fractional animation time rather
than an integer frame index. Calls `150C33D4/15054E50` follow animation selection.

## Full-span evidence

Original references `2FE10.s`, `55E50.s` and `7BDB0.s` cover all 600 registered
bytes. Full registered CURRENT (0), existing source-unit layout and complete
US image equality gate the aliases. Raw/deferred callees and callers supply
semantic evidence only and retain their implementation status.
