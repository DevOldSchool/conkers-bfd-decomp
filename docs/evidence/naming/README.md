# Function naming evidence

These 38 notes explain descriptive names for already-matched C functions.
Each retains its symbol/name/span table, original instructions or ROM-data
provenance, callers and consumers, behavior, edge cases and unresolved meanings.
The tables are scoped evidence, not a complete naming inventory. For older
model/asset naming and boundary research, use the [evidence index](../README.md).

## Shared scope and verification

Names are source-local aliases for existing numeric linker symbols, not recovered
historical symbols. Naming preserves signatures and runtime/regional aliases,
types and padded layouts, volatile accesses, declarations, constants, operation
and store order, packet macros, data ownership and complete registered spans.
It does not implement raw/deferred bodies, repair ABI or behavior, establish new
boundaries, or earn new C matches or source-unit completion.

Acceptance requires independent full-span US CURRENT (0), including trailing
padding; existing source-unit layout and applicable private-data/BSS proof;
clean batch verification, tests, metadata/progress and whitespace checks; RSP
payload equality and exact main/game images. Follow the
[repository validation workflow](../../decompilation-workflow.md#builds-and-batch-verification).
The [function](../../../progress/functions.json) and
[source-unit](../../../progress/source_units.json) inventories own current status.
Recorded checks describe their original pass, not fresh validation of every
checkout. Local exceptions and held mismatches remain documented in each note.

Names describe only the proven contract. Static calls and callback registration
do not establish runtime activation, complete indirect-call coverage, final
rendering or audible results. Unresolved selectors, models, characters, scenes
and effects stay numeric; local caveats take precedence over shorthand names.

## Actors, managed objects and scripts

- [Initialization and animation sequences](actor_initialization_helper_semantics.md)
- [Animation state and model caches](actor_animation_state_helper_semantics.md)
- [Attachment links and payload cleanup](actor_attachment_link_helper_semantics.md)
- [Attachment, opacity, scale and animation utilities](actor_utility_helper_semantics.md)
- [Distances and heading-relative offsets](actor_geometry_helper_semantics.md)
- [Matrix buffers and masked bases](actor_matrix_buffer_helper_semantics.md)
- [Vertical motion and sound handles](actor_motion_sound_helper_semantics.md)
- [Resource requests and controller lifecycle](actor_resource_controller_helper_semantics.md)
- [Managed-object lists and staged removal](managed_object_helper_semantics.md)
- [Script path points and shared interpreter conventions](actor_script_path_helper_semantics.md)
- [Script program control and playback](actor_script_control_helper_semantics.md)
- [Script position and distance predicates](actor_script_geometry_helper_semantics.md)
- [Script selected-state predicates and callbacks](actor_script_dispatch_helper_semantics.md)

## Math, graphics and text

- [Matrix construction and translation](matrix_helper_semantics.md)
- [Vectors, quaternions and inverse transforms](vector_transform_helper_semantics.md)
- [Trigonometric lookup and angle deltas](trig_angle_helper_semantics.md)
- [Folded cosine and scaled directions](lookup_direction_helper_semantics.md)
- [Geometry and cubic interpolation](geometry_interpolation_helper_semantics.md)
- [Segment projection and angular profiles](projection_angle_helper_semantics.md)
- [Scalar clamps, wrapping and angular distance](scalar_range_helper_semantics.md)
- [Palette RGB and computed graphics colors](color_mode_helper_semantics.md)
- [Display-list callbacks and state](display_list_helper_semantics.md)
- [Viewport fade and tint](viewport_fade_helper_semantics.md)
- [Timed viewport flashes](viewport_flash_helper_semantics.md)
- [Text sequences and special-glyph metadata](text_sequence_helper_semantics.md)

## Main system, transport and audio

- [Startup, transfer waits and video](main_startup_helper_semantics.md)
- [AI, PI, VI/timers and threads](main_system_helper_semantics.md)
- [SP tasks, graphics scheduler and motor-pak protocol](main_io_helper_semantics.md)
- [Heap allocation and tag lifecycle](heap_helper_semantics.md)
- [Length-prefixed record rings](record_ring_helper_semantics.md)
- [MP3 adapters and text records](mp3_adapter_helper_semantics.md)
- [Audio thread and cache callbacks](audio_callback_helper_semantics.md)
- [Sequence-player state and channel controls](sequence_control_helper_semantics.md)
- [Sequence transport, markers and FX](sequence_transport_helper_semantics.md)
- [Sequence-record volume and FX buses](sequence_record_helper_semantics.md)

## Debugger

- [Framebuffer, controller packets and SI](debugger_io_helper_semantics.md)
- [Menu, saved registers and stack pages](debugger_screen_helper_semantics.md)
- [Session, prompt and numeric rendering](debugger_session_helper_semantics.md)
