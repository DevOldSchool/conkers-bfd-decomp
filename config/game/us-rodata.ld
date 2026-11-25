/* Reviewed external game data; see docs/evidence/data-layout/game_61950_jump_table.md.
 * INFO retains linked bytes for verification without appending them to the
 * code-only payload. The original game-data archive supplies these bytes.
 * Read before the generated code linker script so this input is consumed here.
 */
SECTIONS
{
    /* Weighted vector tables: us_weighted_vectors.md. */
    .game_rodata_weighted_vectors_800A24B0 0x800A24B0 (INFO) : SUBALIGN(4)
    {
        *weighted_vectors_800A24B0.o(.data)
    }
    .game_rodata_weighted_vectors_800A2520 0x800A2520 (INFO) : SUBALIGN(4)
    {
        *weighted_vectors_800A2520.o(.data)
    }
    .game_rodata_weighted_vectors_800A2568 0x800A2568 (INFO) : SUBALIGN(4)
    {
        *weighted_vectors_800A2568.o(.data)
    }
    .game_rodata_weighted_vectors_800A25BC 0x800A25BC (INFO) : SUBALIGN(4)
    {
        *weighted_vectors_800A25BC.o(.data)
    }
    /* Native floating-point data and creation records: us_native_fp_control.md. */
    .game_rodata_native_fp_control_8008CF00 0x8008CF00 (INFO) : SUBALIGN(4)
    {
        *native_fp_control_8008CF00.o(.data)
    }
    .game_rodata_native_fp_control_80095C64 0x80095C64 (INFO) : SUBALIGN(4)
    {
        *native_fp_control_80095C64.o(.data)
    }
    /* Native float data and bounded records: us_native_float_address_flow.md. */
    .game_rodata_native_float_data_80088724 0x80088724 (INFO) : SUBALIGN(4)
    {
        *native_float_data_80088724.o(.data)
    }
    .game_rodata_native_float_data_800A49C0 0x800A49C0 (INFO) : SUBALIGN(4)
    {
        *native_float_data_800A49C0.o(.data)
    }
    .game_rodata_native_float_data_800A4A2C 0x800A4A2C (INFO) : SUBALIGN(4)
    {
        *native_float_data_800A4A2C.o(.data)
    }
    .game_rodata_weighted_record_800A2504 0x800A2504 (INFO) : SUBALIGN(4)
    {
        *weighted_record_800A2504.o(.data)
    }
    /* Native type-nine texture: us_two_frame_effect_data.md. */
    .game_rodata_two_frame_effect_texture 0x8009060C (INFO) : SUBALIGN(4)
    {
        *two_frame_effect_texture.o(.data)
    }
    /* Native literal effect descriptors and callbacks: us_literal_effect_data.md. */
    .game_rodata_effect_texture_callbacks 0x8008CB64 (INFO) : SUBALIGN(4)
    {
        *effect_texture_callbacks.o(.data)
    }
    .game_rodata_literal_effect_texture_800903B8 0x800903B8 (INFO) : SUBALIGN(4)
    {
        *literal_effect_texture_800903B8.o(.data)
    }
    .game_rodata_literal_effect_texture_800903E0 0x800903E0 (INFO) : SUBALIGN(4)
    {
        *literal_effect_texture_800903E0.o(.data)
    }
    .game_rodata_literal_effect_texture_80090558 0x80090558 (INFO) : SUBALIGN(4)
    {
        *literal_effect_texture_80090558.o(.data)
    }
    .game_rodata_literal_effect_texture_80091840 0x80091840 (INFO) : SUBALIGN(4)
    {
        *literal_effect_texture_80091840.o(.data)
    }
    /* Explicit glyph frame domains: us_glyph_texture_reconstruction.md. */
    .game_rodata_glyph_texture_data 0x800915D8 (INFO) : SUBALIGN(4)
    {
        *glyph_texture_data.o(.data)
    }
    /* Native effect texture roots, descriptors and frames: us_effect_textures.md. */
    .game_rodata_effect_texture_roots_8008CA4C 0x8008CA4C (INFO) : SUBALIGN(4)
    {
        *effect_texture_roots_8008CA4C.o(.data)
    }
    .game_rodata_effect_texture_frames_80090358 0x80090358 (INFO) : SUBALIGN(4)
    {
        *effect_texture_frames_80090358.o(.data)
    }
    .game_rodata_effect_texture_descriptors_80090388 0x80090388 (INFO) : SUBALIGN(4)
    {
        *effect_texture_descriptors_80090388.o(.data)
    }
    .game_rodata_effect_texture_descriptors_800903C8 0x800903C8 (INFO) : SUBALIGN(4)
    {
        *effect_texture_descriptors_800903C8.o(.data)
    }
    .game_rodata_effect_texture_descriptors_80090420 0x80090420 (INFO) : SUBALIGN(4)
    {
        *effect_texture_descriptors_80090420.o(.data)
    }
    .game_rodata_effect_texture_frames_80090480 0x80090480 (INFO) : SUBALIGN(4)
    {
        *effect_texture_frames_80090480.o(.data)
    }
    .game_rodata_effect_texture_descriptors_80090494 0x80090494 (INFO) : SUBALIGN(4)
    {
        *effect_texture_descriptors_80090494.o(.data)
    }
    .game_rodata_effect_texture_frames_800904A0 0x800904A0 (INFO) : SUBALIGN(4)
    {
        *effect_texture_frames_800904A0.o(.data)
    }
    .game_rodata_effect_texture_descriptors_800904B4 0x800904B4 (INFO) : SUBALIGN(4)
    {
        *effect_texture_descriptors_800904B4.o(.data)
    }
    .game_rodata_effect_texture_frames_80090538 0x80090538 (INFO) : SUBALIGN(4)
    {
        *effect_texture_frames_80090538.o(.data)
    }
    .game_rodata_effect_texture_descriptors_8009053C 0x8009053C (INFO) : SUBALIGN(4)
    {
        *effect_texture_descriptors_8009053C.o(.data)
    }
    .game_rodata_effect_texture_descriptors_800905A8 0x800905A8 (INFO) : SUBALIGN(4)
    {
        *effect_texture_descriptors_800905A8.o(.data)
    }
    .game_rodata_effect_texture_frames_800905FC 0x800905FC (INFO) : SUBALIGN(4)
    {
        *effect_texture_frames_800905FC.o(.data)
    }
    .game_rodata_effect_texture_descriptors_80090600 0x80090600 (INFO) : SUBALIGN(4)
    {
        *effect_texture_descriptors_80090600.o(.data)
    }
    .game_rodata_effect_texture_frames_80090620 0x80090620 (INFO) : SUBALIGN(4)
    {
        *effect_texture_frames_80090620.o(.data)
    }
    .game_rodata_effect_texture_descriptors_80090634 0x80090634 (INFO) : SUBALIGN(4)
    {
        *effect_texture_descriptors_80090634.o(.data)
    }
    .game_rodata_effect_texture_frames_80090640 0x80090640 (INFO) : SUBALIGN(4)
    {
        *effect_texture_frames_80090640.o(.data)
    }
    .game_rodata_effect_texture_descriptors_80090660 0x80090660 (INFO) : SUBALIGN(4)
    {
        *effect_texture_descriptors_80090660.o(.data)
    }
    .game_rodata_effect_texture_frames_8009069C 0x8009069C (INFO) : SUBALIGN(4)
    {
        *effect_texture_frames_8009069C.o(.data)
    }
    .game_rodata_effect_texture_descriptors_800906C4 0x800906C4 (INFO) : SUBALIGN(4)
    {
        *effect_texture_descriptors_800906C4.o(.data)
    }
    .game_rodata_effect_texture_frames_800906D0 0x800906D0 (INFO) : SUBALIGN(4)
    {
        *effect_texture_frames_800906D0.o(.data)
    }
    .game_rodata_effect_texture_descriptors_800906F8 0x800906F8 (INFO) : SUBALIGN(4)
    {
        *effect_texture_descriptors_800906F8.o(.data)
    }
    .game_rodata_effect_texture_frames_8009071C 0x8009071C (INFO) : SUBALIGN(4)
    {
        *effect_texture_frames_8009071C.o(.data)
    }
    .game_rodata_effect_texture_descriptors_80090730 0x80090730 (INFO) : SUBALIGN(4)
    {
        *effect_texture_descriptors_80090730.o(.data)
    }
    .game_rodata_effect_texture_descriptors_8009075C 0x8009075C (INFO) : SUBALIGN(4)
    {
        *effect_texture_descriptors_8009075C.o(.data)
    }
    .game_rodata_effect_texture_frames_80090768 0x80090768 (INFO) : SUBALIGN(4)
    {
        *effect_texture_frames_80090768.o(.data)
    }
    .game_rodata_effect_texture_descriptors_8009077C 0x8009077C (INFO) : SUBALIGN(4)
    {
        *effect_texture_descriptors_8009077C.o(.data)
    }
    .game_rodata_effect_texture_frames_80090788 0x80090788 (INFO) : SUBALIGN(4)
    {
        *effect_texture_frames_80090788.o(.data)
    }
    .game_rodata_effect_texture_descriptors_8009078C 0x8009078C (INFO) : SUBALIGN(4)
    {
        *effect_texture_descriptors_8009078C.o(.data)
    }
    .game_rodata_effect_texture_descriptors_800907EC 0x800907EC (INFO) : SUBALIGN(4)
    {
        *effect_texture_descriptors_800907EC.o(.data)
    }
    .game_rodata_effect_texture_frames_800907F8 0x800907F8 (INFO) : SUBALIGN(4)
    {
        *effect_texture_frames_800907F8.o(.data)
    }
    .game_rodata_effect_texture_descriptors_800907FC 0x800907FC (INFO) : SUBALIGN(4)
    {
        *effect_texture_descriptors_800907FC.o(.data)
    }
    .game_rodata_effect_texture_frames_80090808 0x80090808 (INFO) : SUBALIGN(4)
    {
        *effect_texture_frames_80090808.o(.data)
    }
    .game_rodata_effect_texture_descriptors_8009080C 0x8009080C (INFO) : SUBALIGN(4)
    {
        *effect_texture_descriptors_8009080C.o(.data)
    }
    .game_rodata_effect_texture_descriptors_80091834 0x80091834 (INFO) : SUBALIGN(4)
    {
        *effect_texture_descriptors_80091834.o(.data)
    }
    .game_rodata_effect_texture_descriptors_8009184C 0x8009184C (INFO) : SUBALIGN(4)
    {
        *effect_texture_descriptors_8009184C.o(.data)
    }
    /* Native CPU texture frame storage: us_cpu_texture_frames.md. */
    .game_rodata_cpu_texture_frames_800901F0 0x800901F0 (INFO) : SUBALIGN(4)
    {
        *cpu_texture_frames_800901F0.o(.data)
    }
    .game_rodata_cpu_texture_frames_8009073C 0x8009073C (INFO) : SUBALIGN(4)
    {
        *cpu_texture_frames_8009073C.o(.data)
    }
    .game_rodata_cpu_texture_frames_800907A4 0x800907A4 (INFO) : SUBALIGN(4)
    {
        *cpu_texture_frames_800907A4.o(.data)
    }
    .game_rodata_cpu_texture_frames_80090818 0x80090818 (INFO) : SUBALIGN(4)
    {
        *cpu_texture_frames_80090818.o(.data)
    }
    .game_rodata_cpu_texture_frames_80091520 0x80091520 (INFO) : SUBALIGN(4)
    {
        *cpu_texture_frames_80091520.o(.data)
    }
    .game_rodata_cpu_texture_frames_800915BC 0x800915BC (INFO) : SUBALIGN(4)
    {
        *cpu_texture_frames_800915BC.o(.data)
    }
    .game_rodata_cpu_texture_frames_800917E4 0x800917E4 (INFO) : SUBALIGN(4)
    {
        *cpu_texture_frames_800917E4.o(.data)
    }
    /* Native menu and CPU texture tables: us_menu_texture.md. */
    .game_rodata_ui_digit_columns 0x8009006C (INFO) : SUBALIGN(4)
    {
        *ui_digit_columns.o(.data)
    }
    .game_rodata_menu_primary_resources 0x800900BC (INFO) : SUBALIGN(4)
    {
        *menu_primary_resources.o(.data)
    }
    .game_rodata_menu_secondary_resources 0x800900D8 (INFO) : SUBALIGN(4)
    {
        *menu_secondary_resources.o(.data)
    }
    .game_rodata_menu_rotating_resources 0x800900FC (INFO) : SUBALIGN(4)
    {
        *menu_rotating_resources.o(.data)
    }
    .game_rodata_cpu_texture_descriptors 0x80090B60 (INFO) : SUBALIGN(4)
    {
        *cpu_texture_descriptors.o(.data)
    }
    .game_rodata_model_extra_scales 0x800A18CC (INFO) : SUBALIGN(4)
    {
        *model_extra_scales.o(.data)
    }
    /* Native scene preload and UI tables: us_scene_ui.md. */
    .game_rodata_scene_preload_roots 0x80082B20 (INFO) : SUBALIGN(4)
    {
        *scene_preload_roots.o(.data)
    }
    .game_rodata_ui_decimal_tables 0x80090074 (INFO) : SUBALIGN(4)
    {
        *ui_decimal_tables.o(.data)
    }
    .game_rodata_ui_model_graphics 0x80090110 (INFO) : SUBALIGN(4)
    {
        *ui_model_graphics.o(.data)
    }
    .game_rodata_scene_preload_lists 0x80090150 (INFO) : SUBALIGN(4)
    {
        *scene_preload_lists.o(.data)
    }
    /* Native model-effect selection: us_model_effect.md. */
    .game_rodata_model_fragment_roots 0x80089A20 (INFO) : SUBALIGN(4)
    {
        *model_fragment_roots.o(.data)
    }
    .game_rodata_model_fragment_extra 0x800A18C0 (INFO) : SUBALIGN(4)
    {
        *model_fragment_extra.o(.data)
    }
    .game_rodata_model_effect_lookup 0x800A3880 (INFO) : SUBALIGN(4)
    {
        *model_effect_lookup.o(.data)
    }
    .game_rodata_model_fragment_scales 0x800A3C30 (INFO) : SUBALIGN(4)
    {
        *model_fragment_scales.o(.data)
    }
    .game_rodata_model_fragment_selectors 0x800A3C6C (INFO) : SUBALIGN(4)
    {
        *model_fragment_selectors.o(.data)
    }
    .game_rodata_model_fragment_counts 0x800A3F14 (INFO) : SUBALIGN(4)
    {
        *model_fragment_counts.o(.data)
    }
    .game_rodata_model_fragment_codes 0x800A3F64 (INFO) : SUBALIGN(4)
    {
        *model_fragment_codes.o(.data)
    }
    .game_rodata_model_effect_profiles 0x800A3FD8 (INFO) : SUBALIGN(4)
    {
        *model_effect_profiles.o(.data)
    }
    /* Native particle variant prefixes: us_particle_variants.md. */
    .game_rodata_particle_variants_8008F2C0 0x8008F2C0 (INFO) : SUBALIGN(4)
    {
        *particle_variants_8008F2C0.o(.data)
    }
    .game_rodata_particle_variants_8008F2F0 0x8008F2F0 (INFO) : SUBALIGN(4)
    {
        *particle_variants_8008F2F0.o(.data)
    }
    .game_rodata_particle_variants_8008F368 0x8008F368 (INFO) : SUBALIGN(4)
    {
        *particle_variants_8008F368.o(.data)
    }
    .game_rodata_particle_variants_8008F3E0 0x8008F3E0 (INFO) : SUBALIGN(4)
    {
        *particle_variants_8008F3E0.o(.data)
    }
    .game_rodata_particle_variants_8008F428 0x8008F428 (INFO) : SUBALIGN(4)
    {
        *particle_variants_8008F428.o(.data)
    }
    .game_rodata_particle_variants_8008F470 0x8008F470 (INFO) : SUBALIGN(4)
    {
        *particle_variants_8008F470.o(.data)
    }
    .game_rodata_particle_variants_8008F4A0 0x8008F4A0 (INFO) : SUBALIGN(4)
    {
        *particle_variants_8008F4A0.o(.data)
    }
    .game_rodata_particle_variants_8008F4E8 0x8008F4E8 (INFO) : SUBALIGN(4)
    {
        *particle_variants_8008F4E8.o(.data)
    }
    .game_rodata_particle_variants_8008F518 0x8008F518 (INFO) : SUBALIGN(4)
    {
        *particle_variants_8008F518.o(.data)
    }
    .game_rodata_particle_variants_8008F590 0x8008F590 (INFO) : SUBALIGN(4)
    {
        *particle_variants_8008F590.o(.data)
    }
    .game_rodata_particle_variants_8008F608 0x8008F608 (INFO) : SUBALIGN(4)
    {
        *particle_variants_8008F608.o(.data)
    }
    .game_rodata_particle_variants_8008F638 0x8008F638 (INFO) : SUBALIGN(4)
    {
        *particle_variants_8008F638.o(.data)
    }
    .game_rodata_particle_variants_8008F668 0x8008F668 (INFO) : SUBALIGN(4)
    {
        *particle_variants_8008F668.o(.data)
    }
    .game_rodata_particle_variants_8008F698 0x8008F698 (INFO) : SUBALIGN(4)
    {
        *particle_variants_8008F698.o(.data)
    }
    .game_rodata_particle_variants_8008F6C8 0x8008F6C8 (INFO) : SUBALIGN(4)
    {
        *particle_variants_8008F6C8.o(.data)
    }
    .game_rodata_particle_variants_8008F6F8 0x8008F6F8 (INFO) : SUBALIGN(4)
    {
        *particle_variants_8008F6F8.o(.data)
    }
    /* Native particle configuration and selection: us_particle_settings.md. */
    .game_rodata_particle_category_roots 0x8008D5E0 (INFO) : SUBALIGN(4)
    {
        *particle_category_roots.o(.data)
    }
    .game_rodata_particle_point_8008E5F0 0x8008E5F0 (INFO) : SUBALIGN(4)
    {
        *particle_point_8008E5F0.o(.data)
    }
    .game_rodata_particle_parameters 0x8008E940 (INFO) : SUBALIGN(4)
    {
        *particle_parameters.o(.data)
    }
    .game_rodata_particle_descriptors 0x8008ED80 (INFO) : SUBALIGN(4)
    {
        *particle_descriptors.o(.data)
    }
    .game_rodata_particle_filter_lists 0x8008F728 (INFO) : SUBALIGN(4)
    {
        *particle_filter_lists.o(.data)
    }
    .game_rodata_particle_categories 0x8008F780 (INFO) : SUBALIGN(4)
    {
        *particle_categories.o(.data)
    }
    /* Native particle coordinate prefixes: us_particle_points.md. */
    .game_rodata_particle_points_8008D690 0x8008D690 (INFO) : SUBALIGN(4)
    {
        *particle_points_8008D690.o(.data)
    }
    .game_rodata_particle_points_8008D9D0 0x8008D9D0 (INFO) : SUBALIGN(4)
    {
        *particle_points_8008D9D0.o(.data)
    }
    .game_rodata_particle_points_8008DBA0 0x8008DBA0 (INFO) : SUBALIGN(4)
    {
        *particle_points_8008DBA0.o(.data)
    }
    .game_rodata_particle_points_8008E020 0x8008E020 (INFO) : SUBALIGN(4)
    {
        *particle_points_8008E020.o(.data)
    }
    .game_rodata_particle_points_8008E3B0 0x8008E3B0 (INFO) : SUBALIGN(4)
    {
        *particle_points_8008E3B0.o(.data)
    }
    .game_rodata_particle_points_8008E490 0x8008E490 (INFO) : SUBALIGN(4)
    {
        *particle_points_8008E490.o(.data)
    }
    .game_rodata_particle_points_8008E540 0x8008E540 (INFO) : SUBALIGN(4)
    {
        *particle_points_8008E540.o(.data)
    }
    .game_rodata_particle_points_8008E600 0x8008E600 (INFO) : SUBALIGN(4)
    {
        *particle_points_8008E600.o(.data)
    }
    /* Native drawing commands and model defaults: us_model_draw_data.md. */
    .game_rodata_direct_graphics_80084160 0x80084160 (INFO) : SUBALIGN(4)
    {
        *direct_graphics_80084160.o(.data)
    }
    .game_rodata_direct_graphics_80084190 0x80084190 (INFO) : SUBALIGN(4)
    {
        *direct_graphics_80084190.o(.data)
    }
    .game_rodata_direct_graphics_80084350 0x80084350 (INFO) : SUBALIGN(4)
    {
        *direct_graphics_80084350.o(.data)
    }
    .game_rodata_direct_graphics_800859A0 0x800859A0 (INFO) : SUBALIGN(4)
    {
        *direct_graphics_800859A0.o(.data)
    }
    .game_rodata_direct_graphics_80086B80 0x80086B80 (INFO) : SUBALIGN(4)
    {
        *direct_graphics_80086B80.o(.data)
    }
    .game_rodata_direct_graphics_80087390 0x80087390 (INFO) : SUBALIGN(4)
    {
        *direct_graphics_80087390.o(.data)
    }
    .game_rodata_direct_graphics_8008CFA0 0x8008CFA0 (INFO) : SUBALIGN(4)
    {
        *direct_graphics_8008CFA0.o(.data)
    }
    .game_rodata_direct_graphics_8008D018 0x8008D018 (INFO) : SUBALIGN(4)
    {
        *direct_graphics_8008D018.o(.data)
    }
    .game_rodata_direct_graphics_8008D448 0x8008D448 (INFO) : SUBALIGN(4)
    {
        *direct_graphics_8008D448.o(.data)
    }
    .game_rodata_direct_graphics_80090028 0x80090028 (INFO) : SUBALIGN(4)
    {
        *direct_graphics_80090028.o(.data)
    }
    .game_rodata_model_defaults 0x800A26C0 (INFO) : SUBALIGN(4)
    {
        *model_defaults.o(.data)
    }
    /* Native segment-8 rendering records: us_render_state_tables.md. */
    .game_rodata_render_state_80082FC0 0x80082FC0 (INFO) : SUBALIGN(4)
    {
        *render_state_80082FC0.o(.data)
    }
    .game_rodata_render_state_80083140 0x80083140 (INFO) : SUBALIGN(4)
    {
        *render_state_80083140.o(.data)
    }
    .game_rodata_render_state_800832C0 0x800832C0 (INFO) : SUBALIGN(4)
    {
        *render_state_800832C0.o(.data)
    }
    .game_rodata_render_state_80083440 0x80083440 (INFO) : SUBALIGN(4)
    {
        *render_state_80083440.o(.data)
    }
    .game_rodata_render_state_800835C0 0x800835C0 (INFO) : SUBALIGN(4)
    {
        *render_state_800835C0.o(.data)
    }
    .game_rodata_render_state_80083740 0x80083740 (INFO) : SUBALIGN(4)
    {
        *render_state_80083740.o(.data)
    }
    .game_rodata_render_state_800838C0 0x800838C0 (INFO) : SUBALIGN(4)
    {
        *render_state_800838C0.o(.data)
    }
    .game_rodata_render_state_80083A40 0x80083A40 (INFO) : SUBALIGN(4)
    {
        *render_state_80083A40.o(.data)
    }
    .game_rodata_render_state_80083BC0 0x80083BC0 (INFO) : SUBALIGN(4)
    {
        *render_state_80083BC0.o(.data)
    }
    .game_rodata_render_state_80083D40 0x80083D40 (INFO) : SUBALIGN(4)
    {
        *render_state_80083D40.o(.data)
    }
    .game_rodata_render_state_80083EC0 0x80083EC0 (INFO) : SUBALIGN(4)
    {
        *render_state_80083EC0.o(.data)
    }
    /* Native effect graphics: docs/evidence/data-layout/us_effect_graphics.md. */
    .game_rodata_effect_graphics_800873D0 0x800873D0 (INFO) : SUBALIGN(4)
    {
        *effect_graphics_800873D0.o(.data)
    }
    .game_rodata_effect_graphics_80088768 0x80088768 (INFO) : SUBALIGN(4)
    {
        *effect_graphics_80088768.o(.data)
    }
    .game_rodata_effect_graphics_80088828 0x80088828 (INFO) : SUBALIGN(4)
    {
        *effect_graphics_80088828.o(.data)
    }
    .game_rodata_effect_graphics_800889E0 0x800889E0 (INFO) : SUBALIGN(4)
    {
        *effect_graphics_800889E0.o(.data)
    }
    .game_rodata_effect_graphics_80088BE0 0x80088BE0 (INFO) : SUBALIGN(4)
    {
        *effect_graphics_80088BE0.o(.data)
    }
    .game_rodata_effect_graphics_800890C0 0x800890C0 (INFO) : SUBALIGN(4)
    {
        *effect_graphics_800890C0.o(.data)
    }
    .game_rodata_effect_graphics_80089470 0x80089470 (INFO) : SUBALIGN(4)
    {
        *effect_graphics_80089470.o(.data)
    }
    .game_rodata_effect_graphics_80089700 0x80089700 (INFO) : SUBALIGN(4)
    {
        *effect_graphics_80089700.o(.data)
    }
    .game_rodata_effect_graphics_80089BC0 0x80089BC0 (INFO) : SUBALIGN(4)
    {
        *effect_graphics_80089BC0.o(.data)
    }
    .game_rodata_effect_graphics_80089EB8 0x80089EB8 (INFO) : SUBALIGN(4)
    {
        *effect_graphics_80089EB8.o(.data)
    }
    .game_rodata_effect_graphics_8008A1D0 0x8008A1D0 (INFO) : SUBALIGN(4)
    {
        *effect_graphics_8008A1D0.o(.data)
    }
    .game_rodata_effect_graphics_8008A470 0x8008A470 (INFO) : SUBALIGN(4)
    {
        *effect_graphics_8008A470.o(.data)
    }
    .game_rodata_effect_graphics_8008AC70 0x8008AC70 (INFO) : SUBALIGN(4)
    {
        *effect_graphics_8008AC70.o(.data)
    }
    .game_rodata_effect_graphics_8008AD30 0x8008AD30 (INFO) : SUBALIGN(4)
    {
        *effect_graphics_8008AD30.o(.data)
    }
    .game_rodata_effect_graphics_8008AD60 0x8008AD60 (INFO) : SUBALIGN(4)
    {
        *effect_graphics_8008AD60.o(.data)
    }
    .game_rodata_effect_graphics_8008ADD0 0x8008ADD0 (INFO) : SUBALIGN(4)
    {
        *effect_graphics_8008ADD0.o(.data)
    }
    .game_rodata_effect_graphics_8008AE60 0x8008AE60 (INFO) : SUBALIGN(4)
    {
        *effect_graphics_8008AE60.o(.data)
    }
    .game_rodata_effect_graphics_8008AF38 0x8008AF38 (INFO) : SUBALIGN(4)
    {
        *effect_graphics_8008AF38.o(.data)
    }
    .game_rodata_effect_graphics_8008B050 0x8008B050 (INFO) : SUBALIGN(4)
    {
        *effect_graphics_8008B050.o(.data)
    }
    .game_rodata_effect_graphics_8008B3A0 0x8008B3A0 (INFO) : SUBALIGN(4)
    {
        *effect_graphics_8008B3A0.o(.data)
    }
    .game_rodata_effect_graphics_8008B3E0 0x8008B3E0 (INFO) : SUBALIGN(4)
    {
        *effect_graphics_8008B3E0.o(.data)
    }
    .game_rodata_effect_graphics_8008B480 0x8008B480 (INFO) : SUBALIGN(4)
    {
        *effect_graphics_8008B480.o(.data)
    }
    .game_rodata_effect_graphics_8008CB70 0x8008CB70 (INFO) : SUBALIGN(4)
    {
        *effect_graphics_8008CB70.o(.data)
    }
    .game_rodata_effect_graphics_8008CC30 0x8008CC30 (INFO) : SUBALIGN(4)
    {
        *effect_graphics_8008CC30.o(.data)
    }
    .game_rodata_effect_graphics_8008CD90 0x8008CD90 (INFO) : SUBALIGN(4)
    {
        *effect_graphics_8008CD90.o(.data)
    }
    .game_rodata_effect_graphics_8008D4F0 0x8008D4F0 (INFO) : SUBALIGN(4)
    {
        *effect_graphics_8008D4F0.o(.data)
    }
    .game_rodata_effect_graphics_8008D5B0 0x8008D5B0 (INFO) : SUBALIGN(4)
    {
        *effect_graphics_8008D5B0.o(.data)
    }
    .game_rodata_effect_graphics_8008F910 0x8008F910 (INFO) : SUBALIGN(4)
    {
        *effect_graphics_8008F910.o(.data)
    }
    .game_rodata_effect_graphics_8008FB18 0x8008FB18 (INFO) : SUBALIGN(4)
    {
        *effect_graphics_8008FB18.o(.data)
    }
    .game_rodata_effect_graphics_800A6080 0x800A6080 (INFO) : SUBALIGN(4)
    {
        *effect_graphics_800A6080.o(.data)
    }
    .game_rodata_effect_graphics_800A6170 0x800A6170 (INFO) : SUBALIGN(4)
    {
        *effect_graphics_800A6170.o(.data)
    }
    /* Native effect-type records: docs/evidence/data-layout/us_effect_types.md. */
    .game_rodata_effect_types 0x8008B4A8 (INFO) : SUBALIGN(4)
    {
        *effect_types.o(.data)
    }
    /* Native byte-opcode dispatch: us_command_handlers.md. */
    .game_rodata_command_handlers 0x800844B0 (INFO) : SUBALIGN(4)
    {
        *command_handlers.o(.data)
    }
    /* Native inline font: docs/evidence/data-layout/us_inline_font.md. */
    .game_rodata_inline_font_characters 0x800848D0 (INFO) : SUBALIGN(4)
    {
        *inline_font_characters.o(.rodata)
    }
    .game_rodata_inline_font 0x80084930 (INFO) : SUBALIGN(4)
    {
        *inline_font.o(.rodata)
    }
    /* Heterogeneous resource callbacks: us_resource_handlers.md. */
    .game_rodata_resource_handlers 0x80088420 (INFO) : SUBALIGN(4)
    {
        *resource_handlers.o(.data)
    }
    /* Resource metadata: docs/evidence/data-layout/us_resource_descriptors.md. */
    .game_rodata_resource_descriptors 0x80087430 (INFO) : SUBALIGN(4)
    {
        *resource_descriptors.o(.data)
    }
    .game_rodata_resource_dependencies_0 0x8009E470 (INFO) : SUBALIGN(4)
    {
        *resource_dependencies_0.o(.rodata)
    }
    .game_rodata_resource_dependencies_1 0x8009E5F4 (INFO) : SUBALIGN(4)
    {
        *resource_dependencies_1.o(.rodata)
    }
    .game_rodata_resource_dependencies_2 0x8009E618 (INFO) : SUBALIGN(4)
    {
        *resource_dependencies_2.o(.rodata)
    }
    .game_rodata_resource_names 0x8009E834 (INFO) : SUBALIGN(4)
    {
        *resource_names.o(.rodata)
    }
    /* Shared loader metadata: docs/evidence/data-layout/us_flat_asset_sizes.md. */
    .game_rodata_flat_asset_sizes 0x80091D20 (INFO) : SUBALIGN(4)
    {
        *flat_asset_sizes.o(.rodata)
    }
    /* ROM-backed scalar literals: docs/evidence/data-layout/game_second_batch_literals.md. */
    .game_rodata_camera_camera 0x800A352C (INFO) : SUBALIGN(4)
    {
        *camera_camera.o(.rodata)
    }
    .game_rodata_18a8f0 0x800A6520 (INFO) : SUBALIGN(4)
    {
        *game_18A8F0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_32740_float_constants.md. */
    .game_rodata_32740 0x800959E0 (INFO) : SUBALIGN(4) { *game_32740.o(.rodata) }
    /* Entrypoint dispatch: docs/evidence/data-layout/entrypoint_jump_table.md. */
    .game_rodata_entrypoint 0x80095A30 (INFO) : SUBALIGN(4)
    {
        *entrypoint.o(.rodata)
    }
    /* Forty-five switch targets: docs/evidence/data-layout/game_34f20_jump_table.md. */
    .game_rodata_34f20 0x80095A50 (INFO) : SUBALIGN(4) { *game_34F20.o(.rodata) }
    /* Dispatch table, leading and constructor literals:
       docs/evidence/data-layout/game_981e0_constructor_literal_pool.md. */
    .game_rodata_981e0_0 0x80099D54 (INFO) : SUBALIGN(4) { *game_981E0.o(.rodata.981e0_0) }
    .game_rodata_981e0_38 0x80099D8C (INFO) : SUBALIGN(4) { *game_981E0.o(.rodata.981e0_38) }
    .game_rodata_981e0_144 0x80099EAC (INFO) : SUBALIGN(4) { *game_981E0.o(.rodata.981e0_144) }
    /* ROM-verified constant: docs/evidence/data-layout/game_10bc70_float_constant.md. */
    .game_rodata_10bc70 0x800A0D5C (INFO) : SUBALIGN(4)
    {
        *game_10BC70.o(.rodata)
    }
    /* Point pan and particle speed scales: docs/evidence/data-layout/game_114b80_float_constant.md. */
    .game_rodata_114b80_0 0x800A1350 (INFO) : SUBALIGN(4) { *game_114B80.o(.rodata.114b80_0) }
    .game_rodata_114b80_4 0x800A1374 (INFO) : SUBALIGN(4) { *game_114B80.o(.rodata.114b80_4) }
    /* Effect spin literals: docs/evidence/data-layout/game_115f30_float_constants.md. */
    .game_rodata_115f30_0 0x800A1384 (INFO) : SUBALIGN(4) { *game_115F30.o(.rodata.115f30_0) }
    .game_rodata_115f30_2c 0x800A13B8 (INFO) : SUBALIGN(4) { *game_115F30.o(.rodata.115f30_2c) }
    /* Burst and emitter constants: docs/evidence/data-layout/game_116d40_float_constant.md. */
    .game_rodata_116d40 0x800A13F0 (INFO) : SUBALIGN(4)
    {
        *game_116D40.o(.rodata)
    }
    /* Burst spread scale: docs/evidence/data-layout/game_1188e0_float_constant.md. */
    /* ROM-verified constants: docs/evidence/data-layout/game_10d7b0_float_constants.md. */
    .game_rodata_10d7b0 0x800A0FBC (INFO) : SUBALIGN(4)
    {
        *game_10D7B0.o(.rodata)
    }
    .game_rodata_1188e0 0x800A14FC (INFO) : SUBALIGN(4)
    {
        *game_1188E0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_133190_float_constants.md. */
    .game_rodata_133190 0x800A2418 (INFO) : SUBALIGN(4)
    {
        *game_133190.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_1355d0_float_constants.md. */
    .game_rodata_1355d0 0x800A2438 (INFO) : SUBALIGN(4) { *game_1355D0.o(.rodata) }
    /* ROM-verified constants: docs/evidence/data-layout/game_135780_float_constants.md. */
    .game_rodata_135780 0x800A2460 (INFO) : SUBALIGN(4) { *game_135780.o(.rodata) }
    /* ROM-verified constants: docs/evidence/data-layout/game_191c30_float_constants.md. */
    .game_rodata_191c30 0x800A6B20 (INFO) : SUBALIGN(4)
    {
        *game_191C30.o(.rodata)
    }
    /* ROM-verified constant: docs/evidence/data-layout/game_197120_float_constant.md. */
    .game_rodata_197120 0x800A6CB0 (INFO) : SUBALIGN(4)
    {
        *game_197120.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_1d4ac0_float_constants.md. */
    .game_rodata_1d4ac0 0x800A8DC8 (INFO) : SUBALIGN(4)
    {
        *game_1D4AC0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_1e58b0_float_constants.md. */
    .game_rodata_1e58b0 0x800AA4CC (INFO) : SUBALIGN(4)
    {
        *game_1E58B0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_1e37d0_float_constant.md. */
    .game_rodata_1e37d0_0 0x800AA470 (INFO) : SUBALIGN(4) { *game_1E37D0.o(.rodata.1e37d0_0) }
    .game_rodata_1e37d0_4 0x800AA484 (INFO) : SUBALIGN(4) { *game_1E37D0.o(.rodata.1e37d0_4) }
    /* ROM-verified constant: docs/evidence/data-layout/game_1e6260_float_constant.md. */
    .game_rodata_1e6260 0x800AA564 (INFO) : SUBALIGN(4)
    {
        *game_1E6260.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_1e9820_float_constants.md. */
    .game_rodata_1e9820 0x800AA834 (INFO) : SUBALIGN(4)
    {
        *game_1E9820.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_11d830_float_constant.md
       and docs/evidence/data-layout/game_rodata_literal_sub_pools.md. */
    .game_rodata_11d830_0 0x800A1854 (INFO) : SUBALIGN(4) { *game_11D830.o(.rodata.11d830_0) }
    .game_rodata_11d830_4 0x800A1878 (INFO) : SUBALIGN(4) { *game_11D830.o(.rodata.11d830_4) }
    /* ROM-verified constants: docs/evidence/data-layout/game_122b60_float_constants.md. */
    .game_rodata_122b60 0x800A1B60 (INFO) : SUBALIGN(4)
    {
        *game_122B60.o(.rodata)
    }
    /* func_151BB61C templates and literal: docs/evidence/data-layout/game_rodata_literal_sub_pools.md. */
    .game_rodata_1e73b0_0 0x800AA718 (INFO) : SUBALIGN(4) { *game_1E73B0.o(.rodata.1e73b0_0) }
    .game_rodata_1e73b0_48 0x800AA7F4 (INFO) : SUBALIGN(4) { *game_1E73B0.o(.rodata.1e73b0_48) }
    /* func_151DC97C colour tables and literals: docs/evidence/data-layout/game_rodata_literal_sub_pools.md. */
    .game_rodata_209b50_0 0x800AB500 (INFO) : SUBALIGN(4) { *game_209B50.o(.rodata.209b50_0) }
    .game_rodata_209b50_18 0x800AB538 (INFO) : SUBALIGN(4) { *game_209B50.o(.rodata.209b50_18) }
    /* ROM-verified constants: docs/evidence/data-layout/game_eee70_float_constants.md. */
    .game_rodata_eee70 0x800A0210 (INFO) : SUBALIGN(4)
    {
        *game_EEE70.o(.rodata)
    }
    /* Burst velocity literals: docs/evidence/data-layout/game_burst_velocity_literals.md. */
    /* Split pools: docs/evidence/data-layout/game_burst_velocity_literals.md. */
    .game_rodata_f3270_0 0x800A041C (INFO) : SUBALIGN(4) { *game_F3270.o(.rodata.f3270_0) }
    .game_rodata_f3270_4 0x800A043C (INFO) : SUBALIGN(4) { *game_F3270.o(.rodata.f3270_4) }
    /* Split pools: docs/evidence/data-layout/game_burst_velocity_literals.md. */
    .game_rodata_f3ba0_0 0x800A045C (INFO) : SUBALIGN(4) { *game_F3BA0.o(.rodata.f3ba0_0) }
    .game_rodata_f3ba0_4 0x800A047C (INFO) : SUBALIGN(4) { *game_F3BA0.o(.rodata.f3ba0_4) }
    .game_rodata_1179b0 0x800A143C (INFO) : SUBALIGN(4)
    {
        *game_1179B0.o(.rodata)
    }
    /* Split pools: docs/evidence/data-layout/game_burst_velocity_literals.md. */
    .game_rodata_1d6e80_0 0x800A8FE0 (INFO) : SUBALIGN(4) { *game_1D6E80.o(.rodata.1d6e80_0) }
    .game_rodata_1d6e80_c 0x800A8FF4 (INFO) : SUBALIGN(4) { *game_1D6E80.o(.rodata.1d6e80_c) }
    /* Particle speed literals: docs/evidence/data-layout/game_1d8de0_float_constants.md. */
    .game_rodata_1d8de0 0x800A9018 (INFO) : SUBALIGN(4) { *game_1D8DE0.o(.rodata) }
    /* ROM-verified constants: docs/evidence/data-layout/game_111670_float_constants.md. */
    .game_rodata_111670_0 0x800A1060 (INFO) : SUBALIGN(4) { *game_111670.o(.rodata.111670_0) }
    .game_rodata_111670_4 0x800A112C (INFO) : SUBALIGN(4) { *game_111670.o(.rodata.111670_4) }
    /* ROM-verified constants: docs/evidence/data-layout/game_1fa770_float_constants.md. */
    .game_rodata_1fa770_0 0x800AAFC0 (INFO) : SUBALIGN(4) { *game_1FA770.o(.rodata.1fa770_0) }
    .game_rodata_1fa770_8 0x800AAFE4 (INFO) : SUBALIGN(4) { *game_1FA770.o(.rodata.1fa770_8) }
    /* Rain emitter literals: docs/evidence/data-layout/game_1fbb80_float_constants.md. */
    .game_rodata_1fbb80 0x800AAFF0 (INFO) : SUBALIGN(4) { *game_1FBB80.o(.rodata) }
    /* Gust literals: docs/evidence/data-layout/game_1fc5d0_float_constants.md. */
    .game_rodata_1fc5d0 0x800AB014 (INFO) : SUBALIGN(4) { *game_1FC5D0.o(.rodata) }
    /* Smoke emitter literals: docs/evidence/data-layout/game_188440_float_constants.md. */
    .game_rodata_188440 0x800A6438 (INFO) : SUBALIGN(4) { *game_188440.o(.rodata) }
    /* Particle literals: docs/evidence/data-layout/game_1b8b60_float_constants.md. */
    .game_rodata_1b8b60 0x800A7400 (INFO) : SUBALIGN(4) { *game_1B8B60.o(.rodata) }
    /* Debris burst literals: docs/evidence/data-layout/game_e4ff0_float_constants.md. */
    .game_rodata_e4ff0 0x8009FD68 (INFO) : SUBALIGN(4) { *game_E4FF0.o(.rodata) }
    /* ROM-verified constant: docs/evidence/data-layout/game_20a290_float_constant.md. */
    .game_rodata_20a290 0x800AB558 (INFO) : SUBALIGN(4)
    {
        *game_20A290.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_rodata_literal_sub_pools.md. */
    /* func_15146970 ids and switch table: docs/evidence/data-layout/game_173d40_switch_table.md. */
    .game_rodata_173d40_0 0x800A56D0 (INFO) : SUBALIGN(4) { *game_173D40.o(.rodata.173d40_0) }
    .game_rodata_173d40_14 0x800A56E4 (INFO) : SUBALIGN(4) { *game_173D40.o(.rodata.173d40_14) }
    .game_rodata_173d40_38 0x800A5708 (INFO) : SUBALIGN(4) { *game_173D40.o(.rodata.173d40_38) }
    .game_rodata_173d40_50 0x800A5728 (INFO) : SUBALIGN(4) { *game_173D40.o(.rodata.173d40_50) }
    .game_rodata_173d40_58 0x800A573C (INFO) : SUBALIGN(4) { *game_173D40.o(.rodata.173d40_58) }
    /* ROM-verified constants: docs/evidence/data-layout/game_64120_float_constant.md
     * and docs/evidence/data-layout/game_rodata_literal_sub_pools.md. */
    .game_rodata_64120_0 0x80098648 (INFO) : SUBALIGN(4) { *game_64120.o(.rodata.64120_0) }
    .game_rodata_64120_4 0x800986EC (INFO) : SUBALIGN(4) { *game_64120.o(.rodata.64120_4) }
    /* ROM-verified constants: docs/evidence/data-layout/game_f9430_float_constants.md. */
    .game_rodata_f9430 0x800A06D0 (INFO) : SUBALIGN(4)
    {
        *game_F9430.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/holtenrope_float_constants.md. */
    .game_rodata_holtenrope_0 0x800AA394 (INFO) : SUBALIGN(4) { *holtenrope.o(.rodata.holtenrope_0) }
    .game_rodata_holtenrope_c 0x800AA3A0 (INFO) : SUBALIGN(4) { *holtenrope.o(.rodata.holtenrope_c) }
    .game_rodata_holtenrope_18 0x800AA3B8 (INFO) : SUBALIGN(4) { *holtenrope.o(.rodata.holtenrope_18) }
    .game_rodata_holtenrope_24 0x800AA3C4 (INFO) : SUBALIGN(4) { *holtenrope.o(.rodata.holtenrope_24) }
    /* ROM-verified constants: docs/evidence/data-layout/characterflamethrower_float_constants.md
       and docs/evidence/data-layout/game_rodata_literal_sub_pools.md. */
    .game_rodata_characterflamethrower_0 0x800A8ADC (INFO) : SUBALIGN(4) { *characterflamethrower.o(.rodata.characterflamethrower_0) }
    .game_rodata_characterflamethrower_4 0x800A8AF4 (INFO) : SUBALIGN(4) { *characterflamethrower.o(.rodata.characterflamethrower_4) }
    .game_rodata_characterflamethrower_8 0x800A8AFC (INFO) : SUBALIGN(4) { *characterflamethrower.o(.rodata.characterflamethrower_8) }
    /* func_151C9BA0 switch and interpolation constant:
     * docs/evidence/data-layout/effects_sight_float_constant.md. */
    .game_rodata_effects_sight_0 0x800AAC58 (INFO) : SUBALIGN(4) { *effects_sight.o(.rodata.effects_sight_0) }
    .game_rodata_effects_sight_24 0x800AADBC (INFO) : SUBALIGN(4) { *effects_sight.o(.rodata.effects_sight_24) }
    .game_rodata_effects_sight_f0 0x800AAEBC (INFO) : SUBALIGN(4) { *effects_sight.o(.rodata.effects_sight_f0) }
    /* ROM-verified constants: docs/evidence/data-layout/game_e7970_float_constants.md. */
    .game_rodata_e7970 0x8009FE30 (INFO) : SUBALIGN(4)
    {
        *game_E7970.o(.rodata)
    }
    /* ROM-verified constant: docs/evidence/data-layout/game_1cbe20_float_constant.md. */
    .game_rodata_1cbe20 0x800A8CD4 (INFO) : SUBALIGN(4)
    {
        *game_1CBE20.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_f15d0_float_constants.md. */
    .game_rodata_f15d0 0x800A03B8 (INFO) : SUBALIGN(4) { *game_F15D0.o(.rodata) }
    /* ROM-verified constants: docs/evidence/data-layout/game_f21d0_float_constants.md. */
    .game_rodata_f21d0 0x800A03F0 (INFO) : SUBALIGN(4)
    {
        *game_F21D0.o(.rodata)
    }
    /* ROM-verified constant: docs/evidence/data-layout/game_12c1e0_float_constant.md. */
    .game_rodata_12c1e0 0x800A2120 (INFO) : SUBALIGN(4)
    {
        *game_12C1E0.o(.rodata)
    }
    /* ROM-verified constant: docs/evidence/data-layout/game_1dd500_float_constant.md. */
    .game_rodata_1dd500 0x800AA2FC (INFO) : SUBALIGN(4)
    {
        *game_1DD500.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_1def60_float_constants.md. */
    .game_rodata_1def60 0x800AA300 (INFO) : SUBALIGN(4) { *game_1DEF60.o(.rodata) }
    /* ROM-verified constants: docs/evidence/data-layout/game_71820_float_constants.md. */
    .game_rodata_71820 0x80098D60 (INFO) : SUBALIGN(4)
    {
        *game_71820.o(.rodata)
    }
    /* ROM-verified constant: docs/evidence/data-layout/game_2062d0_float_constant.md. */
    .game_rodata_2062d0_0 0x800AB470 (INFO) : SUBALIGN(4) { *game_2062D0.o(.rodata.2062d0_0) }
    .game_rodata_2062d0_10 0x800AB480 (INFO) : SUBALIGN(4) { *game_2062D0.o(.rodata.2062d0_10) }
    .game_rodata_2062d0_28 0x800AB49C (INFO) : SUBALIGN(4) { *game_2062D0.o(.rodata.2062d0_28) }
    /* ROM-verified constants: docs/evidence/data-layout/game_360a0_float_constants.md. */
    .game_rodata_360a0 0x80095B40 (INFO) : SUBALIGN(4)
    {
        *game_360A0.o(.rodata)
    }
    /* Sixteen switch targets: docs/evidence/data-layout/game_36680_jump_table.md. */
    .game_rodata_36680 0x80095B78 (INFO) : SUBALIGN(4) { *game_36680.o(.rodata) }
    /* ROM-verified constants: docs/evidence/data-layout/game_113d60_float_constants.md. */
    .game_rodata_113d60 0x800A1304 (INFO) : SUBALIGN(4)
    {
        *game_113D60.o(.rodata)
    }
    /* ROM-verified prompt string and constant: docs/evidence/data-layout/game_fd1d0_prompt_constants.md. */
    .game_rodata_fd1d0 0x800A0880 (INFO) : SUBALIGN(4)
    {
        *game_FD1D0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_1a20a0_float_constants.md. */
    .game_rodata_1a20a0_0 0x800A7174 (INFO) : SUBALIGN(4) { *game_1A20A0.o(.rodata.1a20a0_0) }
    .game_rodata_1a20a0_4 0x800A71AC (INFO) : SUBALIGN(4) { *game_1A20A0.o(.rodata.1a20a0_4) }
    /* ROM-verified constants: docs/evidence/data-layout/game_1199d0_float_constants.md. */
    .game_rodata_1199d0 0x800A1570 (INFO) : SUBALIGN(4)
    {
        *game_1199D0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_155c90_float_constants.md. */
    .game_rodata_155c90 0x800A35B0 (INFO) : SUBALIGN(4) { *game_155C90.o(.rodata) }
    /* ROM-verified constants: docs/evidence/data-layout/game_13d350_float_constants.md. */
    .game_rodata_13d350 0x800A2F24 (INFO) : SUBALIGN(4) { *game_13D350.o(.rodata) }
    /* ROM-verified constants: docs/evidence/data-layout/game_156160_float_constants.md. */
    .game_rodata_156160 0x800A3614 (INFO) : SUBALIGN(4)
    {
        *game_156160.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_1eb6c0_float_constants.md. */
    .game_rodata_1eb6c0 0x800AA89C (INFO) : SUBALIGN(4) { *game_1EB6C0.o(.rodata) }
    /* ROM-verified constant: docs/evidence/data-layout/game_1ed0f0_float_constant.md. */
    .game_rodata_1ed0f0 0x800AA9C4 (INFO) : SUBALIGN(4)
    {
        *game_1ED0F0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_135d00_float_constants.md. */
    .game_rodata_135d00 0x800A2498 (INFO) : SUBALIGN(4)
    {
        *game_135D00.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_1368c0_float_constants.md. */
    .game_rodata_1368c0 0x800A268C (INFO) : SUBALIGN(4)
    {
        *game_1368C0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_eeb70_float_constants.md. */
    .game_rodata_eeb70 0x800A01F0 (INFO) : SUBALIGN(4)
    {
        *game_EEB70.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_476d0_float_constants.md. */
    .game_rodata_476d0 0x800968F4 (INFO) : SUBALIGN(4)
    {
        *game_476D0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_ddf10_float_constants.md. */
    .game_rodata_ddf10 0x8009F874 (INFO) : SUBALIGN(4)
    {
        *game_DDF10.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_e35c0_float_constants.md. */
    .game_rodata_e35c0 0x8009FCBC (INFO) : SUBALIGN(4)
    {
        *game_E35C0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_fc5f0_float_constants.md. */
    .game_rodata_fc5f0 0x800A0840 (INFO) : SUBALIGN(4)
    {
        *game_FC5F0.o(.rodata)
    }
    /* Five switch targets: docs/evidence/data-layout/game_1a6360_jump_table.md. */
    .game_rodata_1a6360 0x800A71F0 (INFO) : SUBALIGN(4) { *game_1A6360.o(.rodata) }
    /* ROM-verified table and constant: docs/evidence/data-layout/game_1a7260_literal_pool.md. */
    .game_rodata_1a7260 0x800A7210 (INFO) : SUBALIGN(4)
    {
        *game_1A7260.o(.rodata)
    }
    /* ROM-verified table and constants: docs/evidence/data-layout/game_ffba0_literal_pool.md. */
    .game_rodata_ffba0 0x800A0990 (INFO) : SUBALIGN(4)
    {
        *game_FFBA0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_100810_float_constants.md. */
    .game_rodata_100810_0 0x800A09E8 (INFO) : SUBALIGN(4) { *game_100810.o(.rodata.100810_0) }
    .game_rodata_100810_1c 0x800A0A18 (INFO) : SUBALIGN(4) { *game_100810.o(.rodata.100810_1c) }
    /* ROM-verified constant: docs/evidence/data-layout/game_1cc440_float_constant.md. */
    .game_rodata_1cc440 0x800A8CF0 (INFO) : SUBALIGN(4)
    {
        *game_1CC440.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_177b50_float_constants.md
       and docs/evidence/data-layout/game_rodata_literal_sub_pools.md. */
    .game_rodata_177b50_0 0x800A57B0 (INFO) : SUBALIGN(4) { *game_177B50.o(.rodata.177b50_0) }
    .game_rodata_177b50_1c 0x800A5808 (INFO) : SUBALIGN(4) { *game_177B50.o(.rodata.177b50_1c) }
    /* ROM-verified constants: docs/evidence/data-layout/game_12b7d0_float_constants.md. */
    .game_rodata_12b7d0 0x800A1FF0 (INFO) : SUBALIGN(4)
    {
        *game_12B7D0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_12bd10_float_constants.md. */
    .game_rodata_12bd10 0x800A2030 (INFO) : SUBALIGN(4) { *game_12BD10.o(.rodata) }
    /* ROM-verified constants: docs/evidence/data-layout/game_c2350_float_constants.md. */
    .game_rodata_c2350 0x8009DEC0 (INFO) : SUBALIGN(4)
    {
        *game_C2350.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_dc6b0_float_constants.md. */
    .game_rodata_dc6b0_0 0x8009F7B8 (INFO) : SUBALIGN(4) { *game_DC6B0.o(.rodata.dc6b0_0) }
    .game_rodata_dc6b0_18 0x8009F7D8 (INFO) : SUBALIGN(4) { *game_DC6B0.o(.rodata.dc6b0_18) }
    /* ROM-verified constants: docs/evidence/data-layout/game_97aa0_float_constants.md. */
    .game_rodata_97aa0 0x80099A10 (INFO) : SUBALIGN(4)
    {
        *game_97AA0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_de5a0_float_constants.md. */
    .game_rodata_de5a0 0x8009F8A0 (INFO) : SUBALIGN(4)
    {
        *game_DE5A0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_df2d0_float_constants.md. */
    .game_rodata_df2d0 0x8009F8E0 (INFO) : SUBALIGN(4) { *game_DF2D0.o(.rodata) }
    /* ROM-verified constants: docs/evidence/data-layout/game_a28b0_float_constants.md. */
    .game_rodata_a28b0 0x8009A144 (INFO) : SUBALIGN(4)
    {
        *game_A28B0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_3e890_float_constants.md. */
    .game_rodata_3e890 0x800964C0 (INFO) : SUBALIGN(4) { *game_3E890.o(.rodata) }
    /* ROM-verified constant: docs/evidence/data-layout/game_3f820_float_constant.md. */
    .game_rodata_3f820 0x80096570 (INFO) : SUBALIGN(4) { *game_3F820.o(.rodata) }
    /* ROM-verified constants: docs/evidence/data-layout/game_40490_float_constants.md. */
    .game_rodata_40490 0x80096688 (INFO) : SUBALIGN(4)
    {
        *game_40490.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_rodata_literal_sub_pools.md. */
    .game_rodata_1f2730_0 0x800AAAB4 (INFO) : SUBALIGN(4) { *game_1F2730.o(.rodata.1f2730_0) }
    .game_rodata_1f2730_8 0x800AAACC (INFO) : SUBALIGN(4) { *game_1F2730.o(.rodata.1f2730_8) }
    .game_rodata_1f2730_14 0x800AAADC (INFO) : SUBALIGN(4) { *game_1F2730.o(.rodata.1f2730_14) }
    /* ROM-verified constants: docs/evidence/data-layout/game_1e9a30_float_constants.md. */
    .game_rodata_1e9a30 0x800AA868 (INFO) : SUBALIGN(4) { *game_1E9A30.o(.rodata) }
    /* ROM-verified constants: docs/evidence/data-layout/game_49d30_float_constants.md
       and docs/evidence/data-layout/game_rodata_literal_sub_pools.md. */
    .game_rodata_49d30_0 0x800969C0 (INFO) : SUBALIGN(4) { *game_49D30.o(.rodata.49d30_0) }
    .game_rodata_49d30_4 0x800969D0 (INFO) : SUBALIGN(4) { *game_49D30.o(.rodata.49d30_4) }
    .game_rodata_49d30_8 0x80096A14 (INFO) : SUBALIGN(4) { *game_49D30.o(.rodata.49d30_8) }
    /* Camera literals with an aligned double: docs/evidence/data-layout/game_rodata_literal_sub_pools.md. */
    .game_rodata_197f20_0 0x800A6DBC (INFO) : SUBALIGN(4) { *game_197F20.o(.rodata.197f20_0) }
    .game_rodata_197f20_8 0x800A6DC8 (INFO) : SUBALIGN(4) { *game_197F20.o(.rodata.197f20_8) }
    /* ROM-verified constants: docs/evidence/data-layout/game_f44d0_float_constants.md. */
    .game_rodata_f44d0 0x800A0494 (INFO) : SUBALIGN(4)
    {
        *game_F44D0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_127060_float_constants.md. */
    .game_rodata_127060_0 0x800A1D60 (INFO) : SUBALIGN(4) { *game_127060.o(.rodata.127060_0) }
    .game_rodata_127060_34 0x800A1DC0 (INFO) : SUBALIGN(4) { *game_127060.o(.rodata.127060_34) }
    /* ROM-verified constants: docs/evidence/data-layout/game_6b320_float_constants.md. */
    .game_rodata_6b320_0 0x80098918 (INFO) : SUBALIGN(4) { *game_6B320.o(.rodata.6b320_0) }
    .game_rodata_6b320_8 0x80098928 (INFO) : SUBALIGN(4) { *game_6B320.o(.rodata.6b320_8) }
    /* ROM-verified constants: docs/evidence/data-layout/game_124920_float_constants.md. */
    .game_rodata_124920 0x800A1BDC (INFO) : SUBALIGN(4)
    {
        *game_124920.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_1ef500_float_constants.md. */
    .game_rodata_1ef500_0 0x800AAA38 (INFO) : SUBALIGN(4) { *game_1EF500.o(.rodata.1ef500_0) }
    .game_rodata_1ef500_4 0x800AAA7C (INFO) : SUBALIGN(4) { *game_1EF500.o(.rodata.1ef500_4) }
    /* ROM-verified constants: docs/evidence/data-layout/game_e8c10_float_constants.md. */
    .game_rodata_e8c10 0x8009FEBC (INFO) : SUBALIGN(4)
    {
        *game_E8C10.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_19e040_float_constants.md. */
    .game_rodata_19e040 0x800A6F80 (INFO) : SUBALIGN(4)
    {
        *game_19E040.o(.rodata)
    }
    /* Camera clamp and fade literals: docs/evidence/data-layout/game_1ac2f0_float_constants.md. */
    .game_rodata_1ac2f0_0 0x800A7280 (INFO) : SUBALIGN(4) { *game_1AC2F0.o(.rodata.1ac2f0_0) }
    .game_rodata_1ac2f0_c 0x800A7294 (INFO) : SUBALIGN(4) { *game_1AC2F0.o(.rodata.1ac2f0_c) }
    /* ROM-verified constants: docs/evidence/data-layout/game_14ee80_float_constants.md. */
    .game_rodata_14ee80 0x800A3420 (INFO) : SUBALIGN(4) { *game_14EE80.o(.rodata) }
    /* ROM-verified constant: docs/evidence/data-layout/game_ac030_float_constant.md. */
    .game_rodata_ac030 0x8009BD04 (INFO) : SUBALIGN(4) { *game_AC030.o(.rodata) }
    /* ROM-verified constant: docs/evidence/data-layout/game_1b5370_float_constant.md. */
    .game_rodata_1b5370 0x800A7398 (INFO) : SUBALIGN(4)
    {
        *game_1B5370.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_1b81d0_float_constants.md. */
    .game_rodata_1b81d0 0x800A73E0 (INFO) : SUBALIGN(4)
    {
        *game_1B81D0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_fa360_float_constants.md. */
    .game_rodata_fa360 0x800A0710 (INFO) : SUBALIGN(4)
    {
        *game_FA360.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_fb600_float_constant.md. */
    .game_rodata_fb600 0x800A0800 (INFO) : SUBALIGN(4)
    {
        *game_FB600.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_123d40_float_constants.md. */
    .game_rodata_123d40 0x800A1B74 (INFO) : SUBALIGN(4)
    {
        *game_123D40.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_1dbd40_float_constants.md. */
    .game_rodata_1dbd40 0x800A9D8C (INFO) : SUBALIGN(4)
    {
        *game_1DBD40.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_200930_float_constants.md. */
    .game_rodata_200930_0 0x800AB1D4 (INFO) : SUBALIGN(4) { *game_200930.o(.rodata.200930_0) }
    .game_rodata_200930_28 0x800AB21C (INFO) : SUBALIGN(4) { *game_200930.o(.rodata.200930_28) }
    /* ROM-verified constants: docs/evidence/data-layout/game_12ccf0_float_constants.md. */
    .game_rodata_12ccf0 0x800A2170 (INFO) : SUBALIGN(4)
    {
        *game_12CCF0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_11d030_float_constants.md. */
    .game_rodata_11d030 0x800A1824 (INFO) : SUBALIGN(4)
    {
        *game_11D030.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_131f30_float_constants.md. */
    .game_rodata_131f30_0 0x800A23B4 (INFO) : SUBALIGN(4) { *game_131F30.o(.rodata.131f30_0) }
    .game_rodata_131f30_c 0x800A23EC (INFO) : SUBALIGN(4) { *game_131F30.o(.rodata.131f30_c) }
    /* ROM-verified constants: docs/evidence/data-layout/game_1865d0_float_constants.md. */
    .game_rodata_1865d0_0 0x800A63C4 (INFO) : SUBALIGN(4) { *game_1865D0.o(.rodata.1865d0_0) }
    .game_rodata_1865d0_20 0x800A6414 (INFO) : SUBALIGN(4) { *game_1865D0.o(.rodata.1865d0_20) }
    /* ROM-verified constants: docs/evidence/data-layout/game_17caf0_float_constants.md. */
    .game_rodata_17caf0_0 0x800A5FF0 (INFO) : SUBALIGN(4) { *game_17CAF0.o(.rodata.17caf0_0) }
    .game_rodata_17caf0_8 0x800A5FFC (INFO) : SUBALIGN(4) { *game_17CAF0.o(.rodata.17caf0_8) }
    /* ROM-verified constants: docs/evidence/data-layout/game_183640_float_constants.md. */
    .game_rodata_183640 0x800A6040 (INFO) : SUBALIGN(4) { *game_183640.o(.rodata) }
    /* ROM-verified constants: docs/evidence/data-layout/game_83300_float_constants.md
     * and docs/evidence/data-layout/game_rodata_literal_sub_pools.md. */
    .game_rodata_83300_0 0x800994DC (INFO) : SUBALIGN(4) { *game_83300.o(.rodata.83300_0) }
    .game_rodata_83300_c 0x8009962C (INFO) : SUBALIGN(4) { *game_83300.o(.rodata.83300_c) }
    .game_rodata_83300_14 0x80099694 (INFO) : SUBALIGN(4) { *game_83300.o(.rodata.83300_14) }
    /* ROM-verified constants: docs/evidence/data-layout/game_1ce2f0_float_constants.md. */
    .game_rodata_1ce2f0 0x800A8D20 (INFO) : SUBALIGN(4)
    {
        *game_1CE2F0.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_1d2b10_float_constants.md. */
    .game_rodata_1d2b10 0x800A8D80 (INFO) : SUBALIGN(4) { *game_1D2B10.o(.rodata) }
    /* ROM-verified constants: docs/evidence/data-layout/game_1d3ab0_float_constants.md. */
    .game_rodata_1d3ab0 0x800A8DA0 (INFO) : SUBALIGN(4)
    {
        *game_1D3AB0.o(.rodata)
    }
    /* Reviewed tables: docs/evidence/data-layout/game_1bc650_jump_tables.md. */
    .game_rodata_1bc650 0x800A7B7C (INFO) : SUBALIGN(4)
    {
        *game_1BC650.o(.rodata)
    }
    .game_rodata_61950 0x80097D1C (INFO) : SUBALIGN(4)
    {
        *game_61950.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_623d0_float_constants.md. */
    .game_rodata_623d0 0x80097D70 (INFO) : SUBALIGN(4) { *game_623D0.o(.rodata) }
    /* Glyph switch and constants: docs/evidence/data-layout/game_6ea90_glyph_rodata.md. */
    .game_rodata_6ea90 0x80098AB0 (INFO) : SUBALIGN(4)
    {
        *game_6EA90.o(.rodata)
    }
    /* ROM-verified floating constants used by the recovered effect helpers. */
    .game_rodata_1dc720 0x800A9DD4 (INFO) : SUBALIGN(4)
    {
        *game_1DC720.o(.rodata)
    }
    .game_rodata_1e2490 0x800AA3E8 (INFO) : SUBALIGN(4)
    {
        *game_1E2490.o(.rodata)
    }
    .game_rodata_1e2180 0x800AA3D0 (INFO) : SUBALIGN(4)
    {
        *game_1E2180.o(.rodata)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_1e26f0_float_constants.md. */
    .game_rodata_1e26f0 0x800AA41C (INFO) : SUBALIGN(4) { *game_1E26F0.o(.rodata) }
    /* ROM-verified constants: docs/evidence/data-layout/game_1e34c0_float_constants.md. */
    .game_rodata_1e34c0 0x800AA450 (INFO) : SUBALIGN(4) { *game_1E34C0.o(.rodata) }
    .game_rodata_75c90 0x80099000 (INFO) : SUBALIGN(4)
    {
        *game_75C90.o(.rodata)
    }

    /* 51-entry format switch table; the final word is object alignment. */
    .game_rodata_70200 0x80098B98 (INFO) : SUBALIGN(4)
    {
        *game_70200.o(.rodata)
    }
    /* Reviewed automation tables: docs/evidence/data-layout/automation_jump_tables.md. */
    .game_rodata_433f0 0x800966C0 (INFO) : SUBALIGN(4) { *game_433F0.o(.rodata) }
    .game_rodata_58f80_0 0x80096DF8 (INFO) : SUBALIGN(4) { *game_58F80.o(.rodata.58f80_0) }
    .game_rodata_58f80_100 0x80096F04 (INFO) : SUBALIGN(4) { *game_58F80.o(.rodata.58f80_100) }
    .game_rodata_58f80_118 0x80096F1C (INFO) : SUBALIGN(4) { *game_58F80.o(.rodata.58f80_118) }
    .game_rodata_58f80_134 0x80096F38 (INFO) : SUBALIGN(4) { *game_58F80.o(.rodata.58f80_134) }
    .game_rodata_aeb40 0x8009CC40 (INFO) : SUBALIGN(4) { *game_AEB40.o(.rodata) }
    .game_rodata_b4080_0 0x8009DA18 (INFO) : SUBALIGN(4) { *game_B4080.o(.rodata.b4080_0) }
    .game_rodata_b4080_8 0x8009DA24 (INFO) : SUBALIGN(4) { *game_B4080.o(.rodata.b4080_8) }
    .game_rodata_b4080_28 0x8009DA44 (INFO) : SUBALIGN(4) { *game_B4080.o(.rodata.b4080_28) }
    .game_rodata_b4080_40 0x8009DA60 (INFO) : SUBALIGN(4) { *game_B4080.o(.rodata.b4080_40) }
    .game_rodata_b4080_48 0x8009DA94 (INFO) : SUBALIGN(4) { *game_B4080.o(.rodata.b4080_48) }
    .game_rodata_b4080_144 0x8009DB90 (INFO) : SUBALIGN(4) { *game_B4080.o(.rodata.b4080_144) }
    .game_rodata_16ee20_0 0x800A5218 (INFO) : SUBALIGN(4) { *game_16EE20.o(.rodata.16ee20_0) }
    .game_rodata_16ee20_b4 0x800A52CC (INFO) : SUBALIGN(4) { *game_16EE20.o(.rodata.16ee20_b4) }
    .game_rodata_16ee20_218 0x800A5430 (INFO) : SUBALIGN(4) { *game_16EE20.o(.rodata.16ee20_218) }
    .game_rodata_16ee20_258 0x800A5648 (INFO) : SUBALIGN(4) { *game_16EE20.o(.rodata.16ee20_258) }
    .game_rodata_16ee20_26c 0x800A565C (INFO) : SUBALIGN(4) { *game_16EE20.o(.rodata.16ee20_26c) }
    /* func_1514470C literal: docs/evidence/data-layout/game_rodata_literal_sub_pools.md. */
    .game_rodata_16ee20_2a4 0x800A56A0 (INFO) : SUBALIGN(4) { *game_16EE20.o(.rodata.16ee20_2a4) }
    .game_rodata_1c1150_0 0x800A8258 (INFO) : SUBALIGN(4) { *game_1C1150.o(.rodata.1c1150_0) }
    .game_rodata_1c1150_14 0x800A826C (INFO) : SUBALIGN(4) { *game_1C1150.o(.rodata.1c1150_14) }
    /* func_15194408 table and literals: docs/evidence/data-layout/game_rodata_literal_sub_pools.md. */
    .game_rodata_1c1150_28 0x800A8280 (INFO) : SUBALIGN(4) { *game_1C1150.o(.rodata.1c1150_28) }
    .game_rodata_1c1150_3c 0x800A8294 (INFO) : SUBALIGN(4) { *game_1C1150.o(.rodata.1c1150_3c) }
    .game_rodata_1c1150_64 0x800A82BC (INFO) : SUBALIGN(4) { *game_1C1150.o(.rodata.1c1150_64) }
    /* func_15194FF4 switch tables: docs/evidence/data-layout/game_1c1150_jump_tables.md. */
    .game_rodata_1c1150_78 0x800A82D0 (INFO) : SUBALIGN(4) { *game_1C1150.o(.rodata.1c1150_78) }
    .game_rodata_1c1150_8c 0x800A82F0 (INFO) : SUBALIGN(4) { *game_1C1150.o(.rodata.1c1150_8c) }
    .game_rodata_1c1150_200 0x800A8464 (INFO) : SUBALIGN(4) { *game_1C1150.o(.rodata.1c1150_200) }
    .game_rodata_1c1150_25c 0x800A84C0 (INFO) : SUBALIGN(4) { *game_1C1150.o(.rodata.1c1150_25c) }
    .game_rodata_1c1150_444 0x800A86A8 (INFO) : SUBALIGN(4) { *game_1C1150.o(.rodata.1c1150_444) }
    /* Reviewed manual switch tables: docs/evidence/data-layout/manual_batch_jump_tables.md. */
    .game_rodata_49be0 0x800969A0 (INFO) : SUBALIGN(4) { *game_49BE0.o(.rodata) }
    .game_rodata_cd860 0x8009F550 (INFO) : SUBALIGN(4) { *game_CD860.o(.rodata) }
    /* ROM-verified constant: docs/evidence/data-layout/game_cde80_float_constant.md. */
    .game_rodata_cde80 0x8009F5A8 (INFO) : SUBALIGN(4) { *game_CDE80.o(.rodata) }
    /* game_179F30 switch tables, setup literals and switch table:
     * docs/evidence/data-layout/game_179f30_jump_tables.md and
     * docs/evidence/data-layout/game_179f30_float_constants.md. */
    .game_rodata_179f30_0 0x800A59AC (INFO) : SUBALIGN(4) { *game_179F30.o(.rodata.179f30_0) }
    .game_rodata_179f30_2ec 0x800A5C98 (INFO) : SUBALIGN(4) { *game_179F30.o(.rodata.179f30_2ec) }
    .game_rodata_179f30_3c4 0x800A5D70 (INFO) : SUBALIGN(4) { *game_179F30.o(.rodata.179f30_3c4) }
    .game_rodata_179f30_410 0x800A5DBC (INFO) : SUBALIGN(4) { *game_179F30.o(.rodata.179f30_410) }
    .game_rodata_179f30_438 0x800A5DF4 (INFO) : SUBALIGN(4) { *game_179F30.o(.rodata.179f30_438) }
    .game_rodata_179f30_448 0x800A5E20 (INFO) : SUBALIGN(4) { *game_179F30.o(.rodata.179f30_448) }
    .game_rodata_179f30_470 0x800A5E48 (INFO) : SUBALIGN(4) { *game_179F30.o(.rodata.179f30_470) }
    /* Recovered blocked switches: docs/evidence/data-layout/blocked_switch_jump_tables.md. */
    .game_rodata_5d2c0 0x80096F40 (INFO) : SUBALIGN(4) { *game_5D2C0.o(.rodata) }
    /* Literal pool before the table: docs/evidence/data-layout/game_1bf090_literal_pool.md. */
    .game_rodata_1bf090 0x800A80FC (INFO) : SUBALIGN(4) { *game_1BF090.o(.rodata) }
    /* Five switch targets after the 1BF090 table: docs/evidence/data-layout/game_1bfcb0_jump_table.md. */
    .game_rodata_1bfcb0 0x800A8160 (INFO) : SUBALIGN(4) { *game_1BFCB0.o(.rodata) }
    /* Emitter literals: docs/evidence/data-layout/game_1bfdd0_float_constants.md. */
    .game_rodata_1bfdd0 0x800A8180 (INFO) : SUBALIGN(4) { *game_1BFDD0.o(.rodata) }
    /* Four switches and two literals: docs/evidence/data-layout/game_a9d90_jump_table.md. */
    .game_rodata_a9d90 0x8009B690 (INFO) : SUBALIGN(4) { *game_A9D90.o(.rodata) }
    /* Eighteen switch targets: docs/evidence/data-layout/game_1ba670_jump_table.md. */
    .game_rodata_1ba670 0x800A7B14 (INFO) : SUBALIGN(4) { *game_1BA670.o(.rodata) }
    /* Six switch targets: docs/evidence/data-layout/game_11f780_jump_table.md. */
    .game_rodata_11f780 0x800A192C (INFO) : SUBALIGN(4) { *game_11F780.o(.rodata) }
    /* ROM-verified constants: docs/evidence/data-layout/game_11ff10_float_constants.md. */
    .game_rodata_11ff10 0x800A1968 (INFO) : SUBALIGN(4) { *game_11FF10.o(.rodata) }
    /* ROM-verified constants: docs/evidence/data-layout/game_121a20_float_constants.md. */
    .game_rodata_121a20_0 0x800A1A64 (INFO) : SUBALIGN(4) { *game_121A20.o(.rodata.121a20_0) }
    .game_rodata_121a20_20 0x800A1A98 (INFO) : SUBALIGN(4) { *game_121A20.o(.rodata.121a20_20) }
    /* Nested light switches: docs/evidence/data-layout/effects_light_jump_tables.md. */
    .game_rodata_light 0x800A6A18 (INFO) : SUBALIGN(4) { *light.o(.rodata) }
    /* Nine switch targets: docs/evidence/data-layout/game_1b8f40_jump_table.md. */
    .game_rodata_1b8f40 0x800A7410 (INFO) : SUBALIGN(4) { *game_1B8F40.o(.rodata) }
    /* Forty and forty-two switch targets: docs/evidence/data-layout/game_ca630_jump_table.md. */
    .game_rodata_ca630 0x8009F1AC (INFO) : SUBALIGN(4) { *game_CA630.o(.rodata) }
    /* Ten switch targets: docs/evidence/data-layout/game_e4070_jump_table.md. */
    .game_rodata_e4070 0x8009FD00 (INFO) : SUBALIGN(4) { *game_E4070.o(.rodata) }
    /* Literals and forty-one switch targets: docs/evidence/data-layout/game_12f400_jump_table.md. */
    .game_rodata_12f400 0x800A228C (INFO) : SUBALIGN(4) { *game_12F400.o(.rodata) }
    /* Thirty switch targets: docs/evidence/data-layout/game_15bd90_jump_table.md. */
    .game_rodata_15bd90 0x800A376C (INFO) : SUBALIGN(4) { *game_15BD90.o(.rodata) }
    /* Two adjacent switches: docs/evidence/data-layout/game_15d730_jump_tables.md. */
    .game_rodata_15d730 0x800A3800 (INFO) : SUBALIGN(4) { *game_15D730.o(.rodata) }
    /* Actor command dispatcher: docs/evidence/data-layout/game_61490_jump_table.md. */
    .game_rodata_61490 0x80097C80 (INFO) : SUBALIGN(4) { *game_61490.o(.rodata) }
    /* Seven selector targets: docs/evidence/data-layout/game_b21b0_jump_table.md. */
    .game_rodata_b21b0 0x8009D9A0 (INFO) : SUBALIGN(4) { *game_B21B0.o(.rodata) }
    /* Particle scale literals: docs/evidence/data-layout/game_10c170_float_constants.md. */
    .game_rodata_10c170 0x800A0F28 (INFO) : SUBALIGN(4) { *game_10C170.o(.rodata) }
    /* Range limits: docs/evidence/data-layout/game_b3020_float_constants.md. */
    .game_rodata_b3020 0x8009D9C0 (INFO) : SUBALIGN(4) { *game_B3020.o(.rodata) }
    /* Seven mode targets: docs/evidence/data-layout/game_cbbe0_jump_table.md. */
    .game_rodata_cbbe0 0x8009F3D0 (INFO) : SUBALIGN(4) { *game_CBBE0.o(.rodata) }
    /* Seventeen query targets: docs/evidence/data-layout/game_cbdb0_jump_table.md. */
    .game_rodata_cbdb0 0x8009F43C (INFO) : SUBALIGN(4) { *game_CBDB0.o(.rodata) }
    /* Two switch tables and one constant: docs/evidence/data-layout/game_c3e20_jump_table.md. */
    .game_rodata_c3e20 0x8009DED0 (INFO) : SUBALIGN(4) { *game_C3E20.o(.rodata) }
    /* Pending actor actions: docs/evidence/data-layout/game_90840_jump_table.md. */
    .game_rodata_90840_0 0x800996D8 (INFO) : SUBALIGN(4) { *game_90840.o(.rodata.90840_0) }
    /* ROM-verified constants: docs/evidence/data-layout/game_rodata_literal_sub_pools.md. */
    .game_rodata_90840_b8 0x800997E8 (INFO) : SUBALIGN(4) { *game_90840.o(.rodata.90840_b8) }
    /* Sound-event switch: docs/evidence/data-layout/game_1483e0_jump_table.md. */
    .game_rodata_1483e0 0x800A3218 (INFO) : SUBALIGN(4) { *game_1483E0.o(.rodata) }
    /* ROM-verified constants: docs/evidence/data-layout/game_147470_float_constants.md. */
    .game_rodata_147470 0x800A3170 (INFO) : SUBALIGN(4) { *game_147470.o(.rodata) }
    /* ROM-verified constants: docs/evidence/data-layout/game_147c70_float_constants.md. */
    .game_rodata_147c70 0x800A3180 (INFO) : SUBALIGN(4) { *game_147C70.o(.rodata) }
    /* Actor callback dispatcher: docs/evidence/data-layout/game_169510_jump_table.md. */
    .game_rodata_169510 0x800A5188 (INFO) : SUBALIGN(4) { *game_169510.o(.rodata) }
    /* Slot-type switch and scale constants: docs/evidence/data-layout/game_1b0740_jump_table_constants.md. */
    .game_rodata_1b0740 0x800A72F0 (INFO) : SUBALIGN(4) { *game_1B0740.o(.rodata) }
    /* Character blood-profile switch: docs/evidence/data-layout/game_blood_jump_tables.md;
     * spray literals: docs/evidence/data-layout/game_rodata_literal_sub_pools.md. */
    .game_rodata_blood_0 0x800A4350 (INFO) : SUBALIGN(4) { *blood.o(.rodata.blood_0) }
    .game_rodata_blood_204 0x800A4554 (INFO) : SUBALIGN(4) { *blood.o(.rodata.blood_204) }
    .game_rodata_blood_260 0x800A45B8 (INFO) : SUBALIGN(4) { *blood.o(.rodata.blood_260) }
    .game_rodata_blood_2b4 0x800A4650 (INFO) : SUBALIGN(4) { *blood.o(.rodata.blood_2b4) }
    .game_rodata_blood_480 0x800A4874 (INFO) : SUBALIGN(4) { *blood.o(.rodata.blood_480) }
    .game_rodata_blood_4d0 0x800A48C4 (INFO) : SUBALIGN(4) { *blood.o(.rodata.blood_4d0) }
    .game_rodata_blood_504 0x800A4900 (INFO) : SUBALIGN(4) { *blood.o(.rodata.blood_504) }
    .game_rodata_blood_53c 0x800A4950 (INFO) : SUBALIGN(4) { *blood.o(.rodata.blood_53c) }
    /* Six ROM-proven targets: docs/evidence/data-layout/game_c98f0_jump_table.md. */
    .game_rodata_c98f0 0x8009E458 (INFO) : SUBALIGN(4) { *game_C98F0.o(.rodata) }
    /* ROM-verified constants: docs/evidence/data-layout/game_39750_float_constants.md. */
    .game_rodata_39750 0x800960F0 (INFO) : SUBALIGN(4) { *game_39750.o(.rodata) }
    /* Sixteen ROM-proven entries: docs/evidence/data-layout/game_3ba70_jump_table.md. */
    .game_rodata_3ba70 0x800961D0 (INFO) : SUBALIGN(4) { *game_3BA70.o(.rodata) }
    .game_rodata_quarter_wave_8009A220 0x8009A220 (INFO) : SUBALIGN(4)
    {
        *quarter_wave_8009A220.o(.data)
    }
    .game_rodata_inverse_angle_80098E00 0x80098E00 (INFO) : SUBALIGN(4)
    {
        *inverse_angle_80098E00.o(.data)
    }
    /* ROM-verified constants: docs/evidence/data-layout/game_3c740_float_constants.md. */
    .game_rodata_3c740 0x80096250 (INFO) : SUBALIGN(4) { *game_3C740.o(.rodata) }
    /* Ten ROM-proven entries: docs/evidence/data-layout/game_20bda0_jump_table.md. */
    .game_rodata_20bda0 0x800AB9BC (INFO) : SUBALIGN(4) { *game_20BDA0.o(.rodata) }
    /* Thirty-five ROM-proven entries: docs/evidence/data-layout/game_138b40_jump_table.md. */
    .game_rodata_138b40 0x800A2C2C (INFO) : SUBALIGN(4) { *game_138B40.o(.rodata) }
    /* ROM-verified constants: docs/evidence/data-layout/game_10e510_float_constants.md. */
    .game_rodata_10e510 0x800A1014 (INFO) : SUBALIGN(4) { *game_10E510.o(.rodata) }
    /* Beam scale bounds: docs/evidence/data-layout/game_108320_float_constants.md. */
    .game_rodata_108320 0x800A0BE4 (INFO) : SUBALIGN(4) { *game_108320.o(.rodata) }
    /* Switch table and constants: docs/evidence/data-layout/game_109220_rodata.md. */
    .game_rodata_109220 0x800A0C40 (INFO) : SUBALIGN(4) { *game_109220.o(.rodata) }
    /* ROM-verified constant: docs/evidence/data-layout/game_10a350_float_constant.md. */
    .game_rodata_10a350 0x800A0CF4 (INFO) : SUBALIGN(4) { *game_10A350.o(.rodata) }
    /* ROM-verified constants: docs/evidence/data-layout/game_dba60_float_constants.md. */
    .game_rodata_dba60 0x8009F774 (INFO) : SUBALIGN(4) { *game_DBA60.o(.rodata) }
    /* ROM-verified constants: docs/evidence/data-layout/game_ec420_float_constants.md. */
    .game_rodata_ec420_0 0x800A0110 (INFO) : SUBALIGN(4) { *game_EC420.o(.rodata.ec420_0) }
    .game_rodata_ec420_14 0x800A014C (INFO) : SUBALIGN(4) { *game_EC420.o(.rodata.ec420_14) }
}
__game_rodata_b4080_0_base = ADDR(.game_rodata_b4080_0);
__game_rodata_b4080_8_base = ADDR(.game_rodata_b4080_8) - 0x8;
__game_rodata_b4080_28_base = ADDR(.game_rodata_b4080_28) - 0x28;
__game_rodata_b4080_40_base = ADDR(.game_rodata_b4080_40) - 0x40;
__game_rodata_b4080_48_base = ADDR(.game_rodata_b4080_48) - 0x48;
__game_rodata_b4080_144_base = ADDR(.game_rodata_b4080_144) - 0x144;
__game_rodata_58f80_0_base = ADDR(.game_rodata_58f80_0);
__game_rodata_58f80_100_base = ADDR(.game_rodata_58f80_100) - 0x100;
__game_rodata_58f80_118_base = ADDR(.game_rodata_58f80_118) - 0x118;
__game_rodata_58f80_134_base = ADDR(.game_rodata_58f80_134) - 0x134;
__game_rodata_16ee20_0_base = ADDR(.game_rodata_16ee20_0);
__game_rodata_16ee20_b4_base = ADDR(.game_rodata_16ee20_b4) - 0xB4;
__game_rodata_16ee20_218_base = ADDR(.game_rodata_16ee20_218) - 0x218;
__game_rodata_16ee20_258_base = ADDR(.game_rodata_16ee20_258) - 0x258;
__game_rodata_16ee20_26c_base = ADDR(.game_rodata_16ee20_26c) - 0x26C;
__game_rodata_16ee20_2a4_base = ADDR(.game_rodata_16ee20_2a4) - 0x2A4;
__game_rodata_1c1150_0_base = ADDR(.game_rodata_1c1150_0);
__game_rodata_1c1150_14_base = ADDR(.game_rodata_1c1150_14) - 0x14;
__game_rodata_1c1150_28_base = ADDR(.game_rodata_1c1150_28) - 0x28;
__game_rodata_1c1150_3c_base = ADDR(.game_rodata_1c1150_3c) - 0x3C;
__game_rodata_1c1150_64_base = ADDR(.game_rodata_1c1150_64) - 0x64;
__game_rodata_1c1150_78_base = ADDR(.game_rodata_1c1150_78) - 0x78;
__game_rodata_1c1150_8c_base = ADDR(.game_rodata_1c1150_8c) - 0x8C;
__game_rodata_1c1150_200_base = ADDR(.game_rodata_1c1150_200) - 0x200;
__game_rodata_1c1150_25c_base = ADDR(.game_rodata_1c1150_25c) - 0x25C;
__game_rodata_1c1150_444_base = ADDR(.game_rodata_1c1150_444) - 0x444;
__game_rodata_209b50_0_base = ADDR(.game_rodata_209b50_0);
__game_rodata_209b50_18_base = ADDR(.game_rodata_209b50_18) - 0x18;
__game_rodata_1e73b0_0_base = ADDR(.game_rodata_1e73b0_0);
__game_rodata_1e73b0_48_base = ADDR(.game_rodata_1e73b0_48) - 0x48;
__game_rodata_11d830_0_base = ADDR(.game_rodata_11d830_0);
__game_rodata_11d830_4_base = ADDR(.game_rodata_11d830_4) - 0x4;
__game_rodata_83300_0_base = ADDR(.game_rodata_83300_0);
__game_rodata_83300_c_base = ADDR(.game_rodata_83300_c) - 0xC;
__game_rodata_83300_14_base = ADDR(.game_rodata_83300_14) - 0x14;
__game_rodata_1f2730_0_base = ADDR(.game_rodata_1f2730_0);
__game_rodata_1f2730_8_base = ADDR(.game_rodata_1f2730_8) - 0x8;
__game_rodata_1f2730_14_base = ADDR(.game_rodata_1f2730_14) - 0x14;
__game_rodata_49d30_0_base = ADDR(.game_rodata_49d30_0);
__game_rodata_49d30_4_base = ADDR(.game_rodata_49d30_4) - 0x4;
__game_rodata_49d30_8_base = ADDR(.game_rodata_49d30_8) - 0x8;
__game_rodata_197f20_0_base = ADDR(.game_rodata_197f20_0);
__game_rodata_197f20_8_base = ADDR(.game_rodata_197f20_8) - 0x8;
__game_rodata_1865d0_0_base = ADDR(.game_rodata_1865d0_0);
__game_rodata_1865d0_20_base = ADDR(.game_rodata_1865d0_20) - 0x20;
__game_rodata_64120_0_base = ADDR(.game_rodata_64120_0);
__game_rodata_64120_4_base = ADDR(.game_rodata_64120_4) - 0x4;
__game_rodata_90840_0_base = ADDR(.game_rodata_90840_0);
__game_rodata_90840_b8_base = ADDR(.game_rodata_90840_b8) - 0xB8;
__game_rodata_111670_0_base = ADDR(.game_rodata_111670_0);
__game_rodata_111670_4_base = ADDR(.game_rodata_111670_4) - 0x4;
__game_rodata_114b80_0_base = ADDR(.game_rodata_114b80_0);
__game_rodata_114b80_4_base = ADDR(.game_rodata_114b80_4) - 0x4;
__game_rodata_200930_0_base = ADDR(.game_rodata_200930_0);
__game_rodata_200930_28_base = ADDR(.game_rodata_200930_28) - 0x28;
__game_rodata_dc6b0_0_base = ADDR(.game_rodata_dc6b0_0);
__game_rodata_dc6b0_18_base = ADDR(.game_rodata_dc6b0_18) - 0x18;
__game_rodata_1a20a0_0_base = ADDR(.game_rodata_1a20a0_0);
__game_rodata_1a20a0_4_base = ADDR(.game_rodata_1a20a0_4) - 0x4;
__game_rodata_1fa770_0_base = ADDR(.game_rodata_1fa770_0);
__game_rodata_1fa770_8_base = ADDR(.game_rodata_1fa770_8) - 0x8;
__game_rodata_6b320_0_base = ADDR(.game_rodata_6b320_0);
__game_rodata_holtenrope_0_base = ADDR(.game_rodata_holtenrope_0);
__game_rodata_holtenrope_c_base = ADDR(.game_rodata_holtenrope_c) - 0xC;
__game_rodata_holtenrope_18_base = ADDR(.game_rodata_holtenrope_18) - 0x18;
__game_rodata_holtenrope_24_base = ADDR(.game_rodata_holtenrope_24) - 0x24;
__game_rodata_characterflamethrower_0_base = ADDR(.game_rodata_characterflamethrower_0);
__game_rodata_characterflamethrower_4_base = ADDR(.game_rodata_characterflamethrower_4) - 0x4;
__game_rodata_characterflamethrower_8_base = ADDR(.game_rodata_characterflamethrower_8) - 0x8;
__game_rodata_2062d0_0_base = ADDR(.game_rodata_2062d0_0);
__game_rodata_2062d0_10_base = ADDR(.game_rodata_2062d0_10) - 0x10;
__game_rodata_2062d0_28_base = ADDR(.game_rodata_2062d0_28) - 0x28;
__game_rodata_1d6e80_0_base = ADDR(.game_rodata_1d6e80_0);
__game_rodata_1d6e80_c_base = ADDR(.game_rodata_1d6e80_c) - 0xC;
__game_rodata_f3ba0_0_base = ADDR(.game_rodata_f3ba0_0);
__game_rodata_f3ba0_4_base = ADDR(.game_rodata_f3ba0_4) - 0x4;
__game_rodata_f3270_0_base = ADDR(.game_rodata_f3270_0);
__game_rodata_f3270_4_base = ADDR(.game_rodata_f3270_4) - 0x4;
__game_rodata_ec420_0_base = ADDR(.game_rodata_ec420_0);
__game_rodata_ec420_14_base = ADDR(.game_rodata_ec420_14) - 0x14;
__game_rodata_115f30_0_base = ADDR(.game_rodata_115f30_0);
__game_rodata_115f30_2c_base = ADDR(.game_rodata_115f30_2c) - 0x2C;
__game_rodata_17caf0_0_base = ADDR(.game_rodata_17caf0_0);
__game_rodata_17caf0_8_base = ADDR(.game_rodata_17caf0_8) - 0x8;
__game_rodata_121a20_0_base = ADDR(.game_rodata_121a20_0);
__game_rodata_121a20_20_base = ADDR(.game_rodata_121a20_20) - 0x20;
__game_rodata_100810_0_base = ADDR(.game_rodata_100810_0);
__game_rodata_100810_1c_base = ADDR(.game_rodata_100810_1c) - 0x1C;
__game_rodata_127060_0_base = ADDR(.game_rodata_127060_0);
__game_rodata_127060_34_base = ADDR(.game_rodata_127060_34) - 0x34;
__game_rodata_1ef500_0_base = ADDR(.game_rodata_1ef500_0);
__game_rodata_1ef500_4_base = ADDR(.game_rodata_1ef500_4) - 0x4;
__game_rodata_6b320_8_base = ADDR(.game_rodata_6b320_8) - 0x8;
__game_rodata_179f30_0_base = ADDR(.game_rodata_179f30_0);
__game_rodata_179f30_2ec_base = ADDR(.game_rodata_179f30_2ec) - 0x2EC;
__game_rodata_179f30_3c4_base = ADDR(.game_rodata_179f30_3c4) - 0x3C4;
__game_rodata_179f30_410_base = ADDR(.game_rodata_179f30_410) - 0x410;
__game_rodata_179f30_438_base = ADDR(.game_rodata_179f30_438) - 0x438;
__game_rodata_179f30_448_base = ADDR(.game_rodata_179f30_448) - 0x448;
__game_rodata_179f30_470_base = ADDR(.game_rodata_179f30_470) - 0x470;
__game_rodata_981e0_0_base = ADDR(.game_rodata_981e0_0);
__game_rodata_981e0_38_base = ADDR(.game_rodata_981e0_38) - 0x38;
__game_rodata_981e0_144_base = ADDR(.game_rodata_981e0_144) - 0x144;
__game_rodata_131f30_0_base = ADDR(.game_rodata_131f30_0);
__game_rodata_131f30_c_base = ADDR(.game_rodata_131f30_c) - 0xC;
__game_rodata_173d40_0_base = ADDR(.game_rodata_173d40_0);
__game_rodata_173d40_14_base = ADDR(.game_rodata_173d40_14) - 0x14;
__game_rodata_173d40_38_base = ADDR(.game_rodata_173d40_38) - 0x38;
__game_rodata_173d40_50_base = ADDR(.game_rodata_173d40_50) - 0x50;
__game_rodata_173d40_58_base = ADDR(.game_rodata_173d40_58) - 0x58;
__game_rodata_blood_0_base = ADDR(.game_rodata_blood_0);
__game_rodata_blood_204_base = ADDR(.game_rodata_blood_204) - 0x204;
__game_rodata_blood_260_base = ADDR(.game_rodata_blood_260) - 0x260;
__game_rodata_blood_2b4_base = ADDR(.game_rodata_blood_2b4) - 0x2B4;
__game_rodata_blood_480_base = ADDR(.game_rodata_blood_480) - 0x480;
__game_rodata_blood_4d0_base = ADDR(.game_rodata_blood_4d0) - 0x4D0;
__game_rodata_blood_504_base = ADDR(.game_rodata_blood_504) - 0x504;
__game_rodata_blood_53c_base = ADDR(.game_rodata_blood_53c) - 0x53C;
__game_rodata_effects_sight_0_base = ADDR(.game_rodata_effects_sight_0);
__game_rodata_effects_sight_24_base = ADDR(.game_rodata_effects_sight_24) - 0x24;
__game_rodata_effects_sight_f0_base = ADDR(.game_rodata_effects_sight_f0) - 0xF0;
__game_rodata_177b50_0_base = ADDR(.game_rodata_177b50_0);
__game_rodata_177b50_1c_base = ADDR(.game_rodata_177b50_1c) - 0x1C;
__game_rodata_1e37d0_0_base = ADDR(.game_rodata_1e37d0_0);
__game_rodata_1e37d0_4_base = ADDR(.game_rodata_1e37d0_4) - 0x4;
__game_rodata_1ac2f0_0_base = ADDR(.game_rodata_1ac2f0_0);
__game_rodata_1ac2f0_c_base = ADDR(.game_rodata_1ac2f0_c) - 0xC;
ASSERT(SIZEOF(.game_rodata_433f0) == 0xA0, "game_433F0 rodata extent changed")
ASSERT(SIZEOF(.game_rodata_58f80_0) == 0x100, "game_58F80 table at 80096DF8 extent changed")
ASSERT(SIZEOF(.game_rodata_58f80_100) == 0x18, "game_58F80 table at 80096F04 extent changed")
ASSERT(SIZEOF(.game_rodata_58f80_118) == 0x1C, "game_58F80 table at 80096F1C extent changed")
ASSERT(SIZEOF(.game_rodata_58f80_134) == 0x8, "game_58F80 literals at 80096F38 extent changed")
ASSERT(SIZEOF(.game_rodata_aeb40) == 0x190, "game_AEB40 rodata extent changed")
ASSERT(SIZEOF(.game_rodata_b4080_0) == 0x8, "game_B4080 literal pool at 8009DA18 extent changed")
ASSERT(SIZEOF(.game_rodata_b4080_8) == 0x20, "game_B4080 table at 8009DA24 extent changed")
ASSERT(SIZEOF(.game_rodata_b4080_28) == 0x18, "game_B4080 func_15089F9C literal extent changed")
ASSERT(SIZEOF(.game_rodata_b4080_40) == 0x8, "game_B4080 func_1508B9BC literal extent changed")
ASSERT(SIZEOF(.game_rodata_b4080_48) == 0xFC, "game_B4080 table at 8009DA94 extent changed")
ASSERT(SIZEOF(.game_rodata_b4080_144) == 0xE4, "game_B4080 table at 8009DB90 extent changed")
ASSERT(SIZEOF(.game_rodata_16ee20_0) == 0xB4, "game_16EE20 table at 800A5218 extent changed")
ASSERT(SIZEOF(.game_rodata_16ee20_b4) == 0x164, "game_16EE20 table at 800A52CC extent changed")
ASSERT(SIZEOF(.game_rodata_16ee20_218) == 0x40, "game_16EE20 table at 800A5430 extent changed")
ASSERT(SIZEOF(.game_rodata_16ee20_258) == 0x14, "game_16EE20 table at 800A5648 extent changed")
ASSERT(SIZEOF(.game_rodata_16ee20_26c) == 0x38, "game_16EE20 table at 800A565C extent changed")
ASSERT(SIZEOF(.game_rodata_16ee20_2a4) == 0x4, "game_16EE20 func_1514470C literal extent changed")
ASSERT(SIZEOF(.game_rodata_1c1150_0) == 0x14, "game_1C1150 first table extent changed")
ASSERT(SIZEOF(.game_rodata_1c1150_14) == 0x14, "game_1C1150 second table extent changed")
ASSERT(SIZEOF(.game_rodata_1c1150_28) == 0x14, "game_1C1150 func_15194408 table extent changed")
ASSERT(SIZEOF(.game_rodata_1c1150_3c) == 0x28, "game_1C1150 func_15194408 and func_151945CC literal extent changed")
ASSERT(SIZEOF(.game_rodata_1c1150_64) == 0x14, "game_1C1150 func_15194794 table extent changed")
ASSERT(SIZEOF(.game_rodata_1c1150_78) == 0x14, "game_1C1150 func_15194810 table extent changed")
ASSERT(SIZEOF(.game_rodata_1c1150_8c) == 0x174, "game_1C1150 func_15194BF0 first table extent changed")
ASSERT(SIZEOF(.game_rodata_1c1150_200) == 0x5C, "game_1C1150 func_15194BF0 second table extent changed")
ASSERT(SIZEOF(.game_rodata_1c1150_25c) == 0x1E8, "game_1C1150 func_15194FF4 first table extent changed")
ASSERT(SIZEOF(.game_rodata_1c1150_444) == 0x5C, "game_1C1150 func_15194FF4 second table extent changed")
ASSERT(SIZEOF(.game_rodata_49be0) == 0x20, "game_49BE0 table extent changed")
ASSERT(SIZEOF(.game_rodata_cd860) == 0x20, "game_CD860 table extent changed")
ASSERT(SIZEOF(.game_rodata_cde80) == 0x10, "game_CDE80 func_150A0D8C literal extent changed")
__game_rodata_cde80_payload_size = 0x4;
ASSERT(SIZEOF(.game_rodata_179f30_0) == 0x2EC, "game_179F30 func_1514CA80 first table extent changed")
ASSERT(SIZEOF(.game_rodata_179f30_2ec) == 0xD8, "game_179F30 func_1514CA80 second table extent changed")
ASSERT(SIZEOF(.game_rodata_179f30_3c4) == 0x4C, "game_179F30 func_1514CA80 third table extent changed")
ASSERT(SIZEOF(.game_rodata_179f30_410) == 0x28, "game_179F30 func_1514CA80 fourth table extent changed")
ASSERT(SIZEOF(.game_rodata_179f30_438) == 0x10, "game_179F30 func_1514D64C literal extent changed")
ASSERT(SIZEOF(.game_rodata_179f30_448) == 0x28, "game_179F30 table extent changed")
ASSERT(SIZEOF(.game_rodata_179f30_470) == 0x10, "game_179F30 func_1514EECC literal extent changed")
__game_rodata_49be0_payload_size = 0x1C;
__game_rodata_cd860_payload_size = 0x18;
ASSERT(SIZEOF(.game_rodata_5d2c0) == 0x1A0, "game_5D2C0 table extent changed")
ASSERT(SIZEOF(.game_rodata_1bf090) == 0x70, "game_1BF090 literal and table extent changed")
__game_rodata_5d2c0_payload_size = 0x19C;
__game_rodata_1bf090_payload_size = 0x64;
__game_rodata_aeb40_payload_size = 0x18C;
ASSERT(SIZEOF(.game_rodata_61950) == 0x20,
       "game_61950 external rodata extent changed")
ASSERT(SIZEOF(.game_rodata_623d0) == 0x10, "game_623D0 surface literal extent changed")
__game_rodata_623d0_payload_size = 0x8;
ASSERT(SIZEOF(.game_rodata_6ea90) == 0x60,
       "game_6EA90 glyph rodata extent changed")
ASSERT(SIZEOF(.game_rodata_1dc720) == 0x10,
       "game_1DC720 external rodata extent changed")
ASSERT(SIZEOF(.game_rodata_1e34c0) == 0x10, "game_1E34C0 literal extent changed")
__game_rodata_1e34c0_payload_size = 0x10;
ASSERT(SIZEOF(.game_rodata_1e2490) == 0x10,
       "game_1E2490 external rodata extent changed")
ASSERT(SIZEOF(.game_rodata_1e2180) == 0x10,
       "game_1E2180 external rodata extent changed")
ASSERT(SIZEOF(.game_rodata_1e26f0) == 0x10, "game_1E26F0 literal extent changed")
__game_rodata_1e26f0_payload_size = 0x10;
ASSERT(SIZEOF(.game_rodata_75c90) == 0x20,
       "game_75C90 external rodata extent changed")
ASSERT(SIZEOF(.game_rodata_70200) == 0xD0,
       "game_70200 external rodata extent changed")
__game_rodata_70200_payload_size = 0xCC;
ASSERT(SIZEOF(.game_rodata_1ba670) == 0x50, "game_1BA670 table extent changed")
__game_rodata_1ba670_payload_size = 0x48;
ASSERT(SIZEOF(.game_rodata_11f780) == 0x20, "game_11F780 table extent changed")
__game_rodata_11f780_payload_size = 0x18;
ASSERT(SIZEOF(.game_rodata_11ff10) == 0x10, "game_11FF10 func_150F2D14 literal extent changed")
__game_rodata_11ff10_payload_size = 0x8;
ASSERT(SIZEOF(.game_rodata_121a20_0) == 0x20, "game_121A20 func_150F4570 literal extent changed")
ASSERT(SIZEOF(.game_rodata_121a20_20) == 0x14, "game_121A20 func_150F4DEC literal extent changed")
ASSERT(SIZEOF(.game_rodata_15d730) == 0x50, "game_15D730 table extent changed")
__game_rodata_15d730_payload_size = 0x44;
ASSERT(SIZEOF(.game_rodata_15bd90) == 0x80, "game_15BD90 table extent changed")
__game_rodata_15bd90_payload_size = 0x78;
ASSERT(SIZEOF(.game_rodata_e4070) == 0x30, "game_E4070 table extent changed")
__game_rodata_e4070_payload_size = 0x28;
ASSERT(SIZEOF(.game_rodata_1bfcb0) == 0x20, "game_1BFCB0 table extent changed")
__game_rodata_1bfcb0_payload_size = 0x14;
ASSERT(SIZEOF(.game_rodata_1bfdd0) == 0x20, "game_1BFDD0 emitter literal extent changed")
__game_rodata_1bfdd0_payload_size = 0x14;
ASSERT(SIZEOF(.game_rodata_12f400) == 0xB0, "game_12F400 literal and table extent changed")
__game_rodata_12f400_payload_size = 0xB0;
ASSERT(SIZEOF(.game_rodata_ca630) == 0x150, "game_CA630 table extent changed")
__game_rodata_ca630_payload_size = 0x148;

ASSERT(SIZEOF(.game_rodata_a9d90) == 0x210, "game_A9D90 table extent changed")
__game_rodata_a9d90_payload_size = 0x20C;

ASSERT(SIZEOF(.game_rodata_10bc70) == 0x10,
       "game_10BC70 constant pool extent changed")
__game_rodata_10bc70_payload_size = 0x4;

ASSERT(SIZEOF(.game_rodata_122b60) == 0x10,
       "game_122B60 constant pool extent changed")
__game_rodata_122b60_payload_size = 0x10;
ASSERT(SIZEOF(.game_rodata_209b50_0) == 0x18,
       "game_209B50 func_151DC97C table extent changed")
ASSERT(SIZEOF(.game_rodata_209b50_18) == 0xC,
       "game_209B50 func_151DC97C literal extent changed")
ASSERT(SIZEOF(.game_rodata_1e73b0_0) == 0x48,
       "game_1E73B0 func_151BB61C template extent changed")
ASSERT(SIZEOF(.game_rodata_1e73b0_48) == 0x4,
       "game_1E73B0 func_151BB61C literal extent changed")
ASSERT(SIZEOF(.game_rodata_11d830_0) == 0x4,
       "game_11D830 func_150F0A24 literal extent changed")
ASSERT(SIZEOF(.game_rodata_11d830_4) == 0x20,
       "game_11D830 func_150F1170 literal extent changed")

ASSERT(SIZEOF(.game_rodata_1bc650) == 0x490,
       "game_1BC650 table extent changed")
__game_rodata_1bc650_payload_size = 0x488;

ASSERT(SIZEOF(.game_rodata_1483e0) == 0xE0, "game_1483E0 table extent changed")
__game_rodata_1483e0_payload_size = 0xD8;
ASSERT(SIZEOF(.game_rodata_147470) == 0x10, "game_147470 constant pool extent changed")
__game_rodata_147470_payload_size = 0x10;
ASSERT(SIZEOF(.game_rodata_147c70) == 0x10, "game_147C70 literal extent changed")
__game_rodata_147c70_payload_size = 0x8;

ASSERT(SIZEOF(.game_rodata_61490) == 0xA0, "game_61490 table extent changed")
__game_rodata_61490_payload_size = 0x94;
ASSERT(SIZEOF(.game_rodata_b21b0) == 0x20, "game_B21B0 table extent changed")
__game_rodata_b21b0_payload_size = 0x1C;
ASSERT(SIZEOF(.game_rodata_b3020) == 0x10, "game_B3020 range literal extent changed")
__game_rodata_b3020_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_10c170) == 0x30, "game_10C170 particle literal extent changed")
__game_rodata_10c170_payload_size = 0x2C;
ASSERT(SIZEOF(.game_rodata_cbbe0) == 0x20, "game_CBBE0 table extent changed")
__game_rodata_cbbe0_payload_size = 0x1C;
ASSERT(SIZEOF(.game_rodata_cbdb0) == 0x50, "game_CBDB0 table extent changed")
__game_rodata_cbdb0_payload_size = 0x44;
ASSERT(SIZEOF(.game_rodata_c3e20) == 0x80, "game_C3E20 table extent changed")
__game_rodata_c3e20_payload_size = 0x80;

ASSERT(SIZEOF(.game_rodata_981e0_0) == 0x38, "game_981E0 func_1506DE84 table extent changed")
ASSERT(SIZEOF(.game_rodata_981e0_38) == 0x10C, "game_981E0 leading and constructor literal extent changed")
ASSERT(SIZEOF(.game_rodata_981e0_144) == 0x80, "game_981E0 func_15070898 literal extent changed")

ASSERT(SIZEOF(.game_rodata_entrypoint) == 0x20, "entrypoint table extent changed")
__game_rodata_entrypoint_payload_size = 0x14;
ASSERT(SIZEOF(.game_rodata_32740) == 0x10, "game_32740 constant pool extent changed")
__game_rodata_32740_payload_size = 0x10;
ASSERT(SIZEOF(.game_rodata_34f20) == 0xC0, "game_34F20 table extent changed")
__game_rodata_34f20_payload_size = 0xB4;

ASSERT(SIZEOF(.game_rodata_c98f0) == 0x20, "game_C98F0 table extent changed")
__game_rodata_c98f0_payload_size = 0x18;

ASSERT(SIZEOF(.game_rodata_3ba70) == 0x40, "game_3BA70 table extent changed")
__game_rodata_3ba70_payload_size = 0x40;
ASSERT(SIZEOF(.game_rodata_3c740) == 0xD0, "game_3C740 descriptor literal extent changed")
__game_rodata_3c740_payload_size = 0xCC;
ASSERT(SIZEOF(.game_rodata_39750) == 0xE0, "game_39750 table and literal pool extent changed")
__game_rodata_39750_payload_size = 0xD4;

ASSERT(SIZEOF(.game_rodata_20bda0) == 0x30, "game_20BDA0 table extent changed")
__game_rodata_20bda0_payload_size = 0x28;

ASSERT(SIZEOF(.game_rodata_138b40) == 0x90, "game_138B40 table extent changed")
__game_rodata_138b40_payload_size = 0x8C;

ASSERT(SIZEOF(.game_rodata_10e510) == 0x20, "game_10E510 emitter literal extent changed")
__game_rodata_10e510_payload_size = 0x14;

ASSERT(SIZEOF(.game_rodata_109220) == 0xB0, "game_109220 table and literal extent changed")
__game_rodata_109220_payload_size = 0xB0;
ASSERT(SIZEOF(.game_rodata_10a350) == 0x10, "game_10A350 literal extent changed")
__game_rodata_10a350_payload_size = 0x4;
ASSERT(SIZEOF(.game_rodata_dba60) == 0x20, "game_DBA60 literal extent changed")
__game_rodata_dba60_payload_size = 0x14;
ASSERT(SIZEOF(.game_rodata_108320) == 0x10, "game_108320 constant pool extent changed")
__game_rodata_108320_payload_size = 0xC;

ASSERT(SIZEOF(.game_rodata_ec420_0) == 0x14, "game_EC420 func_150BF21C literal extent changed")
ASSERT(SIZEOF(.game_rodata_ec420_14) == 0x24, "game_EC420 func_150C01DC literal extent changed")

ASSERT(SIZEOF(.game_rodata_90840_0) == 0xB8, "game_90840 table extent changed")
ASSERT(SIZEOF(.game_rodata_90840_b8) == 0x98,
       "game_90840 func_15064B94 literal extent changed")
ASSERT(SIZEOF(.game_rodata_173d40_0) == 0x14,
       "game_173D40 func_15146970 id extent changed")
ASSERT(SIZEOF(.game_rodata_173d40_14) == 0x24,
       "game_173D40 func_15146970 table extent changed")
ASSERT(SIZEOF(.game_rodata_173d40_38) == 0x18,
       "game_173D40 func_15146A98 literal extent changed")
ASSERT(SIZEOF(.game_rodata_173d40_50) == 0x8,
       "game_173D40 func_15146D60 literal extent changed")
ASSERT(SIZEOF(.game_rodata_173d40_58) == 0x18,
       "game_173D40 emitter literal extent changed")

/* Burst velocity literals own one word; remaining input bytes are zero alignment. */
ASSERT(SIZEOF(.game_rodata_f3270_0) == 0x4,
       "game_F3270 velocity literal extent changed")
ASSERT(SIZEOF(.game_rodata_f3270_4) == 0x8,
       "game_F3270 state literal extent changed")
ASSERT(SIZEOF(.game_rodata_f3ba0_0) == 0x4,
       "game_F3BA0 velocity literal extent changed")
ASSERT(SIZEOF(.game_rodata_f3ba0_4) == 0x8,
       "game_F3BA0 state literal extent changed")
ASSERT(SIZEOF(.game_rodata_1d6e80_0) == 0xC,
       "game_1D6E80 func_151AADF8 literal extent changed")
ASSERT(SIZEOF(.game_rodata_1d6e80_c) == 0x4,
       "game_1D6E80 velocity literal extent changed")
ASSERT(SIZEOF(.game_rodata_1d8de0) == 0x10, "game_1D8DE0 particle speed literal extent changed")
__game_rodata_1d8de0_payload_size = 0x8;
ASSERT(SIZEOF(.game_rodata_1fbb80) == 0x20, "game_1FBB80 rain emitter literal extent changed")
__game_rodata_1fbb80_payload_size = 0x18;
ASSERT(SIZEOF(.game_rodata_1fc5d0) == 0x10, "game_1FC5D0 func_151CF120 literal extent changed")
__game_rodata_1fc5d0_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_188440) == 0x40, "game_188440 literal extent changed")
__game_rodata_188440_payload_size = 0x34;
ASSERT(SIZEOF(.game_rodata_1b8b60) == 0x10, "game_1B8B60 literal extent changed")
__game_rodata_1b8b60_payload_size = 0x10;
ASSERT(SIZEOF(.game_rodata_e4ff0) == 0x20, "game_E4FF0 literal extent changed")
__game_rodata_e4ff0_payload_size = 0x20;
ASSERT(SIZEOF(.game_rodata_1cbe20) == 0x10,
       "game_1CBE20 scale literal extent changed")
__game_rodata_1cbe20_payload_size = 0x8;

ASSERT(SIZEOF(.game_rodata_f15d0) == 0x30, "game_F15D0 func_150C44A4 literal extent changed")
__game_rodata_f15d0_payload_size = 0x2C;
ASSERT(SIZEOF(.game_rodata_f21d0) == 0x10, "game_F21D0 wave literal extent changed")
__game_rodata_f21d0_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_12c1e0) == 0x10, "game_12C1E0 ray literal extent changed")
__game_rodata_12c1e0_payload_size = 0x4;
ASSERT(SIZEOF(.game_rodata_1dd500) == 0x10, "game_1DD500 quad literal extent changed")
__game_rodata_1dd500_payload_size = 0x4;
ASSERT(SIZEOF(.game_rodata_1def60) == 0x20, "game_1DEF60 literal extent changed")
__game_rodata_1def60_payload_size = 0x1C;
ASSERT(SIZEOF(.game_rodata_71820) == 0x10, "game_71820 look-at literal extent changed")
__game_rodata_71820_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_2062d0_0) == 0x10, "game_2062D0 func_151DA08C literal extent changed")
ASSERT(SIZEOF(.game_rodata_2062d0_10) == 0x18, "game_2062D0 func_151DA368 literal extent changed")
ASSERT(SIZEOF(.game_rodata_2062d0_28) == 0x4, "game_2062D0 effect literal extent changed")
ASSERT(SIZEOF(.game_rodata_360a0) == 0x20, "game_360A0 descriptor literal extent changed")
__game_rodata_360a0_payload_size = 0x18;
ASSERT(SIZEOF(.game_rodata_36680) == 0x40, "game_36680 table extent changed")
__game_rodata_36680_payload_size = 0x40;
ASSERT(SIZEOF(.game_rodata_113d60) == 0x10, "game_113D60 emitter literal extent changed")
__game_rodata_113d60_payload_size = 0x8;
ASSERT(SIZEOF(.game_rodata_fd1d0) == 0x10, "game_FD1D0 prompt literal extent changed")
__game_rodata_fd1d0_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_1a20a0_0) == 0x4, "game_1A20A0 func_15174BF0 literal extent changed")
ASSERT(SIZEOF(.game_rodata_1a20a0_4) == 0x10, "game_1A20A0 radian literal extent changed")
ASSERT(SIZEOF(.game_rodata_1199d0) == 0x20, "game_1199D0 smoke literal extent changed")
__game_rodata_1199d0_payload_size = 0x20;
ASSERT(SIZEOF(.game_rodata_156160) == 0x10, "game_156160 camera literal extent changed")
__game_rodata_156160_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_155c90) == 0x20, "game_155C90 camera blend literal extent changed")
__game_rodata_155c90_payload_size = 0x20;
ASSERT(SIZEOF(.game_rodata_13d350) == 0x10, "game_13D350 func_15111858 literal extent changed")
__game_rodata_13d350_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_1ed0f0) == 0x10, "game_1ED0F0 trace epsilon literal extent changed")
__game_rodata_1ed0f0_payload_size = 0x4;
ASSERT(SIZEOF(.game_rodata_1eb6c0) == 0x10, "game_1EB6C0 constant pool extent changed")
__game_rodata_1eb6c0_payload_size = 0x10;
ASSERT(SIZEOF(.game_rodata_135d00) == 0x10, "game_135D00 billboard literal extent changed")
__game_rodata_135d00_payload_size = 0x10;
ASSERT(SIZEOF(.game_rodata_1368c0) == 0x10, "game_1368C0 func_1510A40C literal extent changed")
__game_rodata_1368c0_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_eeb70) == 0x20, "game_EEB70 motion literal extent changed")
__game_rodata_eeb70_payload_size = 0x14;
ASSERT(SIZEOF(.game_rodata_476d0) == 0x20, "game_476D0 view literal extent changed")
__game_rodata_476d0_payload_size = 0x14;
ASSERT(SIZEOF(.game_rodata_ddf10) == 0x30, "game_DDF10 spawn literal extent changed")
__game_rodata_ddf10_payload_size = 0x24;
ASSERT(SIZEOF(.game_rodata_e35c0) == 0x10, "game_E35C0 effect literal extent changed")
__game_rodata_e35c0_payload_size = 0x10;
ASSERT(SIZEOF(.game_rodata_fc5f0) == 0x20, "game_FC5F0 particle literal extent changed")
__game_rodata_fc5f0_payload_size = 0x18;
ASSERT(SIZEOF(.game_rodata_1a6360) == 0x20, "game_1A6360 table extent changed")
__game_rodata_1a6360_payload_size = 0x14;
ASSERT(SIZEOF(.game_rodata_1a7260) == 0x10, "game_1A7260 index table extent changed")
__game_rodata_1a7260_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_ffba0) == 0x30, "game_FFBA0 colour table and literal extent changed")
__game_rodata_ffba0_payload_size = 0x28;
ASSERT(SIZEOF(.game_rodata_100810_0) == 0x1C, "game_100810 func_150D3360 literal extent changed")
ASSERT(SIZEOF(.game_rodata_100810_1c) == 0x14, "game_100810 func_150D4D58 literal extent changed")
ASSERT(SIZEOF(.game_rodata_holtenrope_0) == 0xC, "holtenrope func_151B3A7C literal extent changed")
ASSERT(SIZEOF(.game_rodata_holtenrope_c) == 0xC, "holtenrope func_151B3CF0 literal extent changed")
ASSERT(SIZEOF(.game_rodata_holtenrope_18) == 0xC, "holtenrope func_151B42A4 literal extent changed")
ASSERT(SIZEOF(.game_rodata_holtenrope_24) == 0x8, "holtenrope point literal extent changed")
ASSERT(SIZEOF(.game_rodata_characterflamethrower_0) == 0x4,
       "characterflamethrower func_151987CC literal extent changed")
ASSERT(SIZEOF(.game_rodata_characterflamethrower_4) == 0x4,
       "characterflamethrower func_1519B4B8 literal extent changed")
ASSERT(SIZEOF(.game_rodata_characterflamethrower_8) == 0x8,
       "characterflamethrower preset literal extent changed")
ASSERT(SIZEOF(.game_rodata_effects_sight_0) == 0x24, "effects_sight func_151C899C and func_151C8FCC literal extent changed")
ASSERT(SIZEOF(.game_rodata_effects_sight_24) == 0xCC, "effects_sight func_151C9BA0 table extent changed")
ASSERT(SIZEOF(.game_rodata_effects_sight_f0) == 0x4, "effects_sight interpolation constant extent changed")
ASSERT(SIZEOF(.game_rodata_e7970) == 0x30, "game_E7970 particle literal extent changed")
__game_rodata_e7970_payload_size = 0x2C;
ASSERT(SIZEOF(.game_rodata_1cc440) == 0x10, "game_1CC440 constant pool extent changed")
__game_rodata_1cc440_payload_size = 0x4;
ASSERT(SIZEOF(.game_rodata_177b50_0) == 0x1C,
       "game_177B50 func_1514AB5C literal extent changed")
ASSERT(SIZEOF(.game_rodata_177b50_1c) == 0x80,
       "game_177B50 func_1514B034/func_1514B364/func_1514B8E4 literal extent changed")
ASSERT(SIZEOF(.game_rodata_17caf0_0) == 0x8, "game_17CAF0 func_1514FF44/func_15150178 literal extent changed")
ASSERT(SIZEOF(.game_rodata_17caf0_8) == 0x8, "game_17CAF0 func_15153CCC/func_15153F18 literal extent changed")
ASSERT(SIZEOF(.game_rodata_183640) == 0x20, "game_183640 constant pool extent changed")
__game_rodata_183640_payload_size = 0x14;
ASSERT(SIZEOF(.game_rodata_1865d0_0) == 0x20, "game_1865D0 func_15159C08 literal extent changed")
ASSERT(SIZEOF(.game_rodata_1865d0_20) == 0xC, "game_1865D0 literal extent changed")
ASSERT(SIZEOF(.game_rodata_1ef500_0) == 0x4, "game_1EF500 func_151C2734 literal extent changed")
ASSERT(SIZEOF(.game_rodata_1ef500_4) == 0x4, "game_1EF500 func_151C436C literal extent changed")
ASSERT(SIZEOF(.game_rodata_e8c10) == 0x40,
       "game_E8C10 particle literal extent changed")
__game_rodata_e8c10_payload_size = 0x3C;
ASSERT(SIZEOF(.game_rodata_19e040) == 0x40,
       "game_19E040 particle literal extent changed")
__game_rodata_19e040_payload_size = 0x40;
ASSERT(SIZEOF(.game_rodata_eee70) == 0x20, "game_EEE70 constant pool extent changed")
__game_rodata_eee70_payload_size = 0x14;
ASSERT(SIZEOF(.game_rodata_1ac2f0_0) == 0xC, "game_1AC2F0 func_1517F814 literal extent changed")
ASSERT(SIZEOF(.game_rodata_1ac2f0_c) == 0x18, "game_1AC2F0 func_151814FC literal extent changed")
ASSERT(SIZEOF(.game_rodata_ac030) == 0x10, "game_AC030 constant pool extent changed")
__game_rodata_ac030_payload_size = 0x4;
ASSERT(SIZEOF(.game_rodata_14ee80) == 0x10, "game_14EE80 constant pool extent changed")
__game_rodata_14ee80_payload_size = 0x8;
ASSERT(SIZEOF(.game_rodata_1b5370) == 0x10, "game_1B5370 constant pool extent changed")
__game_rodata_1b5370_payload_size = 0x4;
ASSERT(SIZEOF(.game_rodata_1b81d0) == 0x20,
       "game_1B81D0 particle literal extent changed")
__game_rodata_1b81d0_payload_size = 0x14;
ASSERT(SIZEOF(.game_rodata_fa360) == 0xA0,
       "game_FA360 drift literal extent changed")
__game_rodata_fa360_payload_size = 0x94;
ASSERT(SIZEOF(.game_rodata_fb600) == 0x10,
       "game_FB600 remap bound literal extent changed")
__game_rodata_fb600_payload_size = 0x4;
ASSERT(SIZEOF(.game_rodata_123d40) == 0x10,
       "game_123D40 spawn literal extent changed")
__game_rodata_123d40_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_1dbd40) == 0x10,
       "game_1DBD40 emission literal extent changed")
__game_rodata_1dbd40_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_200930_0) == 0x28,
       "game_200930 func_151D4408 literal extent changed")
ASSERT(SIZEOF(.game_rodata_200930_28) == 0x2C,
       "game_200930 effect literal extent changed")
ASSERT(SIZEOF(.game_rodata_12ccf0) == 0x30,
       "game_12CCF0 sparkle literal extent changed")
__game_rodata_12ccf0_payload_size = 0x2C;
ASSERT(SIZEOF(.game_rodata_11d030) == 0x10,
       "game_11D030 motion literal extent changed")
__game_rodata_11d030_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_131f30_0) == 0xC,
       "game_131F30 func_151050B0 literal extent changed")
ASSERT(SIZEOF(.game_rodata_131f30_c) == 0x18,
       "game_131F30 func_151058B4 literal extent changed")
ASSERT(SIZEOF(.game_rodata_6b320_0) == 0x8,
       "game_6B320 func_1503E5F8 literal extent changed")
ASSERT(SIZEOF(.game_rodata_6b320_8) == 0x8,
       "game_6B320 func_1503ECA0 literal extent changed")
ASSERT(SIZEOF(.game_rodata_124920) == 0x10,
       "game_124920 literal extent changed")
__game_rodata_124920_payload_size = 0x4;
ASSERT(SIZEOF(.game_rodata_127060_0) == 0x34, "game_127060 func_150F9BB0 literal extent changed")
ASSERT(SIZEOF(.game_rodata_127060_34) == 0x4, "game_127060 func_150FB188 literal extent changed")
ASSERT(SIZEOF(.game_rodata_f44d0) == 0x20,
       "game_F44D0 literal extent changed")
__game_rodata_f44d0_payload_size = 0x14;
ASSERT(SIZEOF(.game_rodata_1f2730_0) == 0x8,
       "game_1F2730 func_151C5280 literal range changed")
ASSERT(SIZEOF(.game_rodata_1f2730_8) == 0xC,
       "game_1F2730 func_151C577C first literal range changed")
ASSERT(SIZEOF(.game_rodata_1f2730_14) == 0x14,
       "game_1F2730 func_151C577C second literal range changed")
ASSERT(SIZEOF(.game_rodata_1e9a30) == 0x40, "game_1E9A30 func_151BD828 literal extent changed")
__game_rodata_1e9a30_payload_size = 0x34;
ASSERT(SIZEOF(.game_rodata_49d30_0) == 0x4,
       "game_49D30 func_1501D044 literal extent changed")
ASSERT(SIZEOF(.game_rodata_49d30_4) == 0x4,
       "game_49D30 func_1501F72C literal extent changed")
ASSERT(SIZEOF(.game_rodata_49d30_8) == 0x4,
       "game_49D30 func_15022024 literal extent changed")
ASSERT(SIZEOF(.game_rodata_197f20_0) == 0x8, "game_197F20 func_1516CC58 float literal extent changed")
ASSERT(SIZEOF(.game_rodata_197f20_8) == 0x1C, "game_197F20 func_1516CC58 double literal extent changed")
ASSERT(SIZEOF(.game_rodata_40490) == 0x30,
       "game_40490 literal extent changed")
__game_rodata_40490_payload_size = 0x2C;
ASSERT(SIZEOF(.game_rodata_3e890) == 0x50, "game_3E890 constant pool extent changed")
__game_rodata_3e890_payload_size = 0x48;
ASSERT(SIZEOF(.game_rodata_3f820) == 0x10, "game_3F820 literal extent changed")
__game_rodata_3f820_payload_size = 0x4;
ASSERT(SIZEOF(.game_rodata_a28b0) == 0x10,
       "game_A28B0 literal extent changed")
__game_rodata_a28b0_payload_size = 0x4;
ASSERT(SIZEOF(.game_rodata_dc6b0_0) == 0x18,
       "game_DC6B0 func_150AF328 literal extent changed")
ASSERT(SIZEOF(.game_rodata_dc6b0_18) == 0x4,
       "game_DC6B0 literal extent changed")
ASSERT(SIZEOF(.game_rodata_c2350) == 0x10,
       "game_C2350 literal extent changed")
__game_rodata_c2350_payload_size = 0x4;
ASSERT(SIZEOF(.game_rodata_12b7d0) == 0x10,
       "game_12B7D0 particle literal extent changed")
__game_rodata_12b7d0_payload_size = 0x8;
ASSERT(SIZEOF(.game_rodata_12bd10) == 0x10, "game_12BD10 func_150FE860 literal extent changed")
__game_rodata_12bd10_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_83300_0) == 0xC,
       "game_83300 velocity literal extent changed")
ASSERT(SIZEOF(.game_rodata_83300_c) == 0x8,
       "game_83300 func_1505F188 literal extent changed")
ASSERT(SIZEOF(.game_rodata_83300_14) == 0x4,
       "game_83300 func_150623F4 literal extent changed")
ASSERT(SIZEOF(.game_rodata_1d2b10) == 0x20, "game_1D2B10 func_151A5660 literal extent changed")
__game_rodata_1d2b10_payload_size = 0x18;
ASSERT(SIZEOF(.game_rodata_1d3ab0) == 0x10,
       "game_1D3AB0 constant pool extent changed")
__game_rodata_1d3ab0_payload_size = 0x10;
ASSERT(SIZEOF(.game_rodata_1ce2f0) == 0x10,
       "game_1CE2F0 scale literal extent changed")
__game_rodata_1ce2f0_payload_size = 0x8;
ASSERT(SIZEOF(.game_rodata_f9430) == 0x10,
       "game_F9430 particle literal extent changed")
__game_rodata_f9430_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_64120_0) == 0x4,
       "game_64120 degree literal extent changed")
ASSERT(SIZEOF(.game_rodata_64120_4) == 0x4,
       "game_64120 func_1503B708 literal extent changed")
ASSERT(SIZEOF(.game_rodata_20a290) == 0x10,
       "game_20A290 spawn literal pool extent changed")
__game_rodata_20a290_payload_size = 0x10;
ASSERT(SIZEOF(.game_rodata_1fa770_0) == 0x8,
       "game_1FA770 particle gravity literal extent changed")
ASSERT(SIZEOF(.game_rodata_1fa770_8) == 0xC,
       "game_1FA770 func_151CDB94 literal extent changed")
ASSERT(SIZEOF(.game_rodata_111670_0) == 0x4,
       "game_111670 func_150E42F8 literal extent changed")
ASSERT(SIZEOF(.game_rodata_111670_4) == 0x34,
       "game_111670 effect literal pool extent changed")

ASSERT(SIZEOF(.game_rodata_1179b0) == 0x10,
       "game_1179B0 velocity literal extent changed")
__game_rodata_1179b0_payload_size = 0x4;

ASSERT(SIZEOF(.game_rodata_169510) == 0x40, "game_169510 table extent changed")
__game_rodata_169510_payload_size = 0x34;
ASSERT(SIZEOF(.game_rodata_1b0740) == 0x60, "game_1B0740 table and literal extent changed")
__game_rodata_1b0740_payload_size = 0x54;

ASSERT(SIZEOF(.game_rodata_blood_0) == 0x204, "effects/blood first table extent changed")
ASSERT(SIZEOF(.game_rodata_blood_204) == 0x5C, "effects/blood second table extent changed")
ASSERT(SIZEOF(.game_rodata_blood_260) == 0x54, "effects/blood func_151356D4/func_15135DD0 literal extent changed")
ASSERT(SIZEOF(.game_rodata_blood_2b4) == 0x1CC, "effects/blood func_15137610 table extent changed")
ASSERT(SIZEOF(.game_rodata_blood_480) == 0x50, "effects/blood func_15138C80 table extent changed")
ASSERT(SIZEOF(.game_rodata_blood_4d0) == 0x34, "effects/blood func_15138E98 literal extent changed")
ASSERT(SIZEOF(.game_rodata_blood_504) == 0x38, "effects/blood func_15139768/func_15139D74 literal extent changed")
ASSERT(SIZEOF(.game_rodata_blood_53c) == 0x68, "effects/blood spray and burst literal extent changed")

ASSERT(SIZEOF(.game_rodata_camera_camera) == 0x10,
       "camera_camera angle literal extent changed")
__game_rodata_camera_camera_payload_size = 0x4;
ASSERT(SIZEOF(.game_rodata_18a8f0) == 0x10,
       "game_18A8F0 clamp literal extent changed")
__game_rodata_18a8f0_payload_size = 0x8;

ASSERT(SIZEOF(.game_rodata_1b8f40) == 0x30, "game_1B8F40 table extent changed")
__game_rodata_1b8f40_payload_size = 0x24;

ASSERT(SIZEOF(.game_rodata_114b80_0) == 0x4, "game_114B80 func_150E7C9C literal extent changed")
ASSERT(SIZEOF(.game_rodata_114b80_4) == 0x4, "game_114B80 func_150E8470 literal extent changed")
ASSERT(SIZEOF(.game_rodata_115f30_0) == 0x2C, "game_115F30 func_150E8B1C/func_150E8D5C literal extent changed")
ASSERT(SIZEOF(.game_rodata_115f30_2c) == 0x10, "game_115F30 func_150E9178 literal extent changed")

ASSERT(SIZEOF(.game_rodata_116d40) == 0x20, "game_116D40 constant pool extent changed")
__game_rodata_116d40_payload_size = 0x20;

ASSERT(SIZEOF(.game_rodata_10d7b0) == 0x20, "game_10D7B0 constant pool extent changed")
__game_rodata_10d7b0_payload_size = 0x18;

ASSERT(SIZEOF(.game_rodata_1188e0) == 0x10, "game_1188E0 constant pool extent changed")
__game_rodata_1188e0_payload_size = 0x4;

ASSERT(SIZEOF(.game_rodata_97aa0) == 0x20, "game_97AA0 constant pool extent changed")
__game_rodata_97aa0_payload_size = 0x18;

ASSERT(SIZEOF(.game_rodata_de5a0) == 0x20, "game_DE5A0 constant pool extent changed")
__game_rodata_de5a0_payload_size = 0x1C;
ASSERT(SIZEOF(.game_rodata_df2d0) == 0x20, "game_DF2D0 func_150B1F90 literal extent changed")
__game_rodata_df2d0_payload_size = 0x20;

ASSERT(SIZEOF(.game_rodata_133190) == 0x10, "game_133190 constant pool extent changed")
__game_rodata_133190_payload_size = 0x10;
ASSERT(SIZEOF(.game_rodata_1355d0) == 0x10, "game_1355D0 constant pool extent changed")
__game_rodata_1355d0_payload_size = 0x10;
ASSERT(SIZEOF(.game_rodata_135780) == 0x10, "game_135780 constant pool extent changed")
__game_rodata_135780_payload_size = 0x8;

ASSERT(SIZEOF(.game_rodata_191c30) == 0x20, "game_191C30 constant pool extent changed")
__game_rodata_191c30_payload_size = 0x18;
ASSERT(SIZEOF(.game_rodata_197120) == 0x20, "game_197120 constant pool extent changed")
__game_rodata_197120_payload_size = 0x1C;

ASSERT(SIZEOF(.game_rodata_1d4ac0) == 0x10, "game_1D4AC0 constant pool extent changed")
__game_rodata_1d4ac0_payload_size = 0xC;

ASSERT(SIZEOF(.game_rodata_1e58b0) == 0x10, "game_1E58B0 constant pool extent changed")
__game_rodata_1e58b0_payload_size = 0x10;

ASSERT(SIZEOF(.game_rodata_1e37d0_0) == 0x4, "game_1E37D0 func_151B6420 literal extent changed")
ASSERT(SIZEOF(.game_rodata_1e37d0_4) == 0x4, "game_1E37D0 func_151B7998 literal extent changed")

ASSERT(SIZEOF(.game_rodata_1e6260) == 0x10, "game_1E6260 constant pool extent changed")
__game_rodata_1e6260_payload_size = 0x4;

ASSERT(SIZEOF(.game_rodata_1e9820) == 0x20, "game_1E9820 constant pool extent changed")
__game_rodata_1e9820_payload_size = 0x14;

ASSERT(SIZEOF(.game_rodata_light) == 0xC0, "light switch table extent changed")
__game_rodata_light_payload_size = 0xBC;

ASSERT(SIZEOF(.game_rodata_flat_asset_sizes) == 0x3CB0, "flat asset size table extent changed")
__game_rodata_flat_asset_sizes_payload_size = 0x3CA4;

ASSERT(SIZEOF(.game_rodata_resource_descriptors) == 0xFF0, "resource_descriptors extent changed")
__game_rodata_resource_descriptors_payload_size = 0xFF0;
ASSERT(SIZEOF(.game_rodata_resource_dependencies_0) == 0x180, "resource_dependencies_0 extent changed")
__game_rodata_resource_dependencies_0_payload_size = 0x180;
ASSERT(SIZEOF(.game_rodata_resource_dependencies_1) == 0x20, "resource_dependencies_1 extent changed")
__game_rodata_resource_dependencies_1_payload_size = 0x20;
ASSERT(SIZEOF(.game_rodata_resource_dependencies_2) == 0x220, "resource_dependencies_2 extent changed")
__game_rodata_resource_dependencies_2_payload_size = 0x21C;
ASSERT(SIZEOF(.game_rodata_resource_names) == 0x890, "resource_names extent changed")
__game_rodata_resource_names_payload_size = 0x890;

ASSERT(SIZEOF(.game_rodata_resource_handlers) == 0xF0, "resource handler table extent changed")
__game_rodata_resource_handlers_payload_size = 0xF0;

ASSERT(SIZEOF(.game_rodata_inline_font_characters) == 0x50, "inline font character count changed")
__game_rodata_inline_font_characters_payload_size = 0x50;
ASSERT(SIZEOF(.game_rodata_inline_font) == 0x1000, "inline font texture extent changed")
__game_rodata_inline_font_payload_size = 0x1000;

ASSERT(SIZEOF(.game_rodata_command_handlers) == 0x400, "command handler table extent changed")
__game_rodata_command_handlers_payload_size = 0x400;

ASSERT(SIZEOF(.game_rodata_effect_types) == 0x1520, "effect-type record extent changed")
__game_rodata_effect_types_payload_size = 0x1520;

ASSERT(SIZEOF(.game_rodata_effect_graphics_800873D0) == 0x40, "effect_graphics_800873D0 extent changed")
__game_rodata_effect_graphics_800873D0_payload_size = 0x40;
ASSERT(SIZEOF(.game_rodata_effect_graphics_80088768) == 0x50, "effect_graphics_80088768 extent changed")
__game_rodata_effect_graphics_80088768_payload_size = 0x50;
ASSERT(SIZEOF(.game_rodata_effect_graphics_80088828) == 0x30, "effect_graphics_80088828 extent changed")
__game_rodata_effect_graphics_80088828_payload_size = 0x30;
ASSERT(SIZEOF(.game_rodata_effect_graphics_800889E0) == 0x20, "effect_graphics_800889E0 extent changed")
__game_rodata_effect_graphics_800889E0_payload_size = 0x20;
ASSERT(SIZEOF(.game_rodata_effect_graphics_80088BE0) == 0x30, "effect_graphics_80088BE0 extent changed")
__game_rodata_effect_graphics_80088BE0_payload_size = 0x30;
ASSERT(SIZEOF(.game_rodata_effect_graphics_800890C0) == 0x60, "effect_graphics_800890C0 extent changed")
__game_rodata_effect_graphics_800890C0_payload_size = 0x60;
ASSERT(SIZEOF(.game_rodata_effect_graphics_80089470) == 0x40, "effect_graphics_80089470 extent changed")
__game_rodata_effect_graphics_80089470_payload_size = 0x40;
ASSERT(SIZEOF(.game_rodata_effect_graphics_80089700) == 0x60, "effect_graphics_80089700 extent changed")
__game_rodata_effect_graphics_80089700_payload_size = 0x60;
ASSERT(SIZEOF(.game_rodata_effect_graphics_80089BC0) == 0x60, "effect_graphics_80089BC0 extent changed")
__game_rodata_effect_graphics_80089BC0_payload_size = 0x58;
ASSERT(SIZEOF(.game_rodata_effect_graphics_80089EB8) == 0x30, "effect_graphics_80089EB8 extent changed")
__game_rodata_effect_graphics_80089EB8_payload_size = 0x30;
ASSERT(SIZEOF(.game_rodata_effect_graphics_8008A1D0) == 0x30, "effect_graphics_8008A1D0 extent changed")
__game_rodata_effect_graphics_8008A1D0_payload_size = 0x30;
ASSERT(SIZEOF(.game_rodata_effect_graphics_8008A470) == 0x50, "effect_graphics_8008A470 extent changed")
__game_rodata_effect_graphics_8008A470_payload_size = 0x50;
ASSERT(SIZEOF(.game_rodata_effect_graphics_8008AC70) == 0x60, "effect_graphics_8008AC70 extent changed")
__game_rodata_effect_graphics_8008AC70_payload_size = 0x58;
ASSERT(SIZEOF(.game_rodata_effect_graphics_8008AD30) == 0x30, "effect_graphics_8008AD30 extent changed")
__game_rodata_effect_graphics_8008AD30_payload_size = 0x28;
ASSERT(SIZEOF(.game_rodata_effect_graphics_8008AD60) == 0x30, "effect_graphics_8008AD60 extent changed")
__game_rodata_effect_graphics_8008AD60_payload_size = 0x30;
ASSERT(SIZEOF(.game_rodata_effect_graphics_8008ADD0) == 0x30, "effect_graphics_8008ADD0 extent changed")
__game_rodata_effect_graphics_8008ADD0_payload_size = 0x30;
ASSERT(SIZEOF(.game_rodata_effect_graphics_8008AE60) == 0x80, "effect_graphics_8008AE60 extent changed")
__game_rodata_effect_graphics_8008AE60_payload_size = 0x80;
ASSERT(SIZEOF(.game_rodata_effect_graphics_8008AF38) == 0x90, "effect_graphics_8008AF38 extent changed")
__game_rodata_effect_graphics_8008AF38_payload_size = 0x90;
ASSERT(SIZEOF(.game_rodata_effect_graphics_8008B050) == 0x30, "effect_graphics_8008B050 extent changed")
__game_rodata_effect_graphics_8008B050_payload_size = 0x28;
ASSERT(SIZEOF(.game_rodata_effect_graphics_8008B3A0) == 0x40, "effect_graphics_8008B3A0 extent changed")
__game_rodata_effect_graphics_8008B3A0_payload_size = 0x38;
ASSERT(SIZEOF(.game_rodata_effect_graphics_8008B3E0) == 0xA0, "effect_graphics_8008B3E0 extent changed")
__game_rodata_effect_graphics_8008B3E0_payload_size = 0x98;
ASSERT(SIZEOF(.game_rodata_effect_graphics_8008B480) == 0x30, "effect_graphics_8008B480 extent changed")
__game_rodata_effect_graphics_8008B480_payload_size = 0x28;
ASSERT(SIZEOF(.game_rodata_effect_graphics_8008CB70) == 0x30, "effect_graphics_8008CB70 extent changed")
__game_rodata_effect_graphics_8008CB70_payload_size = 0x30;
ASSERT(SIZEOF(.game_rodata_effect_graphics_8008CC30) == 0x40, "effect_graphics_8008CC30 extent changed")
__game_rodata_effect_graphics_8008CC30_payload_size = 0x40;
ASSERT(SIZEOF(.game_rodata_effect_graphics_8008CD90) == 0x120, "effect_graphics_8008CD90 extent changed")
__game_rodata_effect_graphics_8008CD90_payload_size = 0x118;
ASSERT(SIZEOF(.game_rodata_effect_graphics_8008D4F0) == 0x90, "effect_graphics_8008D4F0 extent changed")
__game_rodata_effect_graphics_8008D4F0_payload_size = 0x88;
ASSERT(SIZEOF(.game_rodata_effect_graphics_8008D5B0) == 0x10, "effect_graphics_8008D5B0 extent changed")
__game_rodata_effect_graphics_8008D5B0_payload_size = 0x10;
ASSERT(SIZEOF(.game_rodata_effect_graphics_8008F910) == 0x30, "effect_graphics_8008F910 extent changed")
__game_rodata_effect_graphics_8008F910_payload_size = 0x30;
ASSERT(SIZEOF(.game_rodata_effect_graphics_8008FB18) == 0x50, "effect_graphics_8008FB18 extent changed")
__game_rodata_effect_graphics_8008FB18_payload_size = 0x50;
ASSERT(SIZEOF(.game_rodata_effect_graphics_800A6080) == 0x90, "effect_graphics_800A6080 extent changed")
__game_rodata_effect_graphics_800A6080_payload_size = 0x90;
ASSERT(SIZEOF(.game_rodata_effect_graphics_800A6170) == 0x90, "effect_graphics_800A6170 extent changed")
__game_rodata_effect_graphics_800A6170_payload_size = 0x90;

ASSERT(SIZEOF(.game_rodata_render_state_80082FC0) == 0x180, "render_state_80082FC0 extent changed")
__game_rodata_render_state_80082FC0_payload_size = 0x180;
ASSERT(SIZEOF(.game_rodata_render_state_80083140) == 0x180, "render_state_80083140 extent changed")
__game_rodata_render_state_80083140_payload_size = 0x180;
ASSERT(SIZEOF(.game_rodata_render_state_800832C0) == 0x180, "render_state_800832C0 extent changed")
__game_rodata_render_state_800832C0_payload_size = 0x180;
ASSERT(SIZEOF(.game_rodata_render_state_80083440) == 0x180, "render_state_80083440 extent changed")
__game_rodata_render_state_80083440_payload_size = 0x180;
ASSERT(SIZEOF(.game_rodata_render_state_800835C0) == 0x180, "render_state_800835C0 extent changed")
__game_rodata_render_state_800835C0_payload_size = 0x180;
ASSERT(SIZEOF(.game_rodata_render_state_80083740) == 0x180, "render_state_80083740 extent changed")
__game_rodata_render_state_80083740_payload_size = 0x180;
ASSERT(SIZEOF(.game_rodata_render_state_800838C0) == 0x180, "render_state_800838C0 extent changed")
__game_rodata_render_state_800838C0_payload_size = 0x180;
ASSERT(SIZEOF(.game_rodata_render_state_80083A40) == 0x180, "render_state_80083A40 extent changed")
__game_rodata_render_state_80083A40_payload_size = 0x180;
ASSERT(SIZEOF(.game_rodata_render_state_80083BC0) == 0x180, "render_state_80083BC0 extent changed")
__game_rodata_render_state_80083BC0_payload_size = 0x180;
ASSERT(SIZEOF(.game_rodata_render_state_80083D40) == 0x180, "render_state_80083D40 extent changed")
__game_rodata_render_state_80083D40_payload_size = 0x180;
ASSERT(SIZEOF(.game_rodata_render_state_80083EC0) == 0x180, "render_state_80083EC0 extent changed")
__game_rodata_render_state_80083EC0_payload_size = 0x180;

ASSERT(SIZEOF(.game_rodata_direct_graphics_80084160) == 0x30, "direct_graphics_80084160 extent changed")
__game_rodata_direct_graphics_80084160_payload_size = 0x30;
ASSERT(SIZEOF(.game_rodata_direct_graphics_80084190) == 0x30, "direct_graphics_80084190 extent changed")
__game_rodata_direct_graphics_80084190_payload_size = 0x28;
ASSERT(SIZEOF(.game_rodata_direct_graphics_80084350) == 0x30, "direct_graphics_80084350 extent changed")
__game_rodata_direct_graphics_80084350_payload_size = 0x30;
ASSERT(SIZEOF(.game_rodata_direct_graphics_800859A0) == 0x30, "direct_graphics_800859A0 extent changed")
__game_rodata_direct_graphics_800859A0_payload_size = 0x28;
ASSERT(SIZEOF(.game_rodata_direct_graphics_80086B80) == 0x20, "direct_graphics_80086B80 extent changed")
__game_rodata_direct_graphics_80086B80_payload_size = 0x20;
ASSERT(SIZEOF(.game_rodata_direct_graphics_80087390) == 0x20, "direct_graphics_80087390 extent changed")
__game_rodata_direct_graphics_80087390_payload_size = 0x20;
ASSERT(SIZEOF(.game_rodata_direct_graphics_8008CFA0) == 0x50, "direct_graphics_8008CFA0 extent changed")
__game_rodata_direct_graphics_8008CFA0_payload_size = 0x48;
ASSERT(SIZEOF(.game_rodata_direct_graphics_8008D018) == 0x40, "direct_graphics_8008D018 extent changed")
__game_rodata_direct_graphics_8008D018_payload_size = 0x38;
ASSERT(SIZEOF(.game_rodata_direct_graphics_8008D448) == 0x50, "direct_graphics_8008D448 extent changed")
__game_rodata_direct_graphics_8008D448_payload_size = 0x50;
ASSERT(SIZEOF(.game_rodata_direct_graphics_80090028) == 0x30, "direct_graphics_80090028 extent changed")
__game_rodata_direct_graphics_80090028_payload_size = 0x30;
ASSERT(SIZEOF(.game_rodata_model_defaults) == 0x560, "model_defaults extent changed")
__game_rodata_model_defaults_payload_size = 0x558;

ASSERT(SIZEOF(.game_rodata_particle_points_8008D690) == 0x340, "particle_points_8008D690 extent changed")
__game_rodata_particle_points_8008D690_payload_size = 0x340;
ASSERT(SIZEOF(.game_rodata_particle_points_8008D9D0) == 0x1D0, "particle_points_8008D9D0 extent changed")
__game_rodata_particle_points_8008D9D0_payload_size = 0x1D0;
ASSERT(SIZEOF(.game_rodata_particle_points_8008DBA0) == 0x480, "particle_points_8008DBA0 extent changed")
__game_rodata_particle_points_8008DBA0_payload_size = 0x480;
ASSERT(SIZEOF(.game_rodata_particle_points_8008E020) == 0x390, "particle_points_8008E020 extent changed")
__game_rodata_particle_points_8008E020_payload_size = 0x390;
ASSERT(SIZEOF(.game_rodata_particle_points_8008E3B0) == 0xE0, "particle_points_8008E3B0 extent changed")
__game_rodata_particle_points_8008E3B0_payload_size = 0xE0;
ASSERT(SIZEOF(.game_rodata_particle_points_8008E490) == 0xB0, "particle_points_8008E490 extent changed")
__game_rodata_particle_points_8008E490_payload_size = 0xB0;
ASSERT(SIZEOF(.game_rodata_particle_points_8008E540) == 0xB0, "particle_points_8008E540 extent changed")
__game_rodata_particle_points_8008E540_payload_size = 0xB0;
ASSERT(SIZEOF(.game_rodata_particle_points_8008E600) == 0x340, "particle_points_8008E600 extent changed")
__game_rodata_particle_points_8008E600_payload_size = 0x340;

ASSERT(SIZEOF(.game_rodata_particle_category_roots) == 0x40, "particle_category_roots extent changed")
__game_rodata_particle_category_roots_payload_size = 0x40;
ASSERT(SIZEOF(.game_rodata_particle_point_8008E5F0) == 0x10, "particle_point_8008E5F0 extent changed")
__game_rodata_particle_point_8008E5F0_payload_size = 0x10;
ASSERT(SIZEOF(.game_rodata_particle_parameters) == 0x440, "particle_parameters extent changed")
__game_rodata_particle_parameters_payload_size = 0x440;
ASSERT(SIZEOF(.game_rodata_particle_descriptors) == 0x540, "particle_descriptors extent changed")
__game_rodata_particle_descriptors_payload_size = 0x540;
ASSERT(SIZEOF(.game_rodata_particle_filter_lists) == 0x60, "particle_filter_lists extent changed")
__game_rodata_particle_filter_lists_payload_size = 0x58;
ASSERT(SIZEOF(.game_rodata_particle_categories) == 0xC0, "particle_categories extent changed")
__game_rodata_particle_categories_payload_size = 0xC0;

ASSERT(SIZEOF(.game_rodata_particle_variants_8008F2C0) == 0x30, "particle_variants_8008F2C0 extent changed")
__game_rodata_particle_variants_8008F2C0_payload_size = 0x30;
ASSERT(SIZEOF(.game_rodata_particle_variants_8008F2F0) == 0x80, "particle_variants_8008F2F0 extent changed")
__game_rodata_particle_variants_8008F2F0_payload_size = 0x78;
ASSERT(SIZEOF(.game_rodata_particle_variants_8008F368) == 0x80, "particle_variants_8008F368 extent changed")
__game_rodata_particle_variants_8008F368_payload_size = 0x78;
ASSERT(SIZEOF(.game_rodata_particle_variants_8008F3E0) == 0x50, "particle_variants_8008F3E0 extent changed")
__game_rodata_particle_variants_8008F3E0_payload_size = 0x48;
ASSERT(SIZEOF(.game_rodata_particle_variants_8008F428) == 0x50, "particle_variants_8008F428 extent changed")
__game_rodata_particle_variants_8008F428_payload_size = 0x48;
ASSERT(SIZEOF(.game_rodata_particle_variants_8008F470) == 0x30, "particle_variants_8008F470 extent changed")
__game_rodata_particle_variants_8008F470_payload_size = 0x30;
ASSERT(SIZEOF(.game_rodata_particle_variants_8008F4A0) == 0x50, "particle_variants_8008F4A0 extent changed")
__game_rodata_particle_variants_8008F4A0_payload_size = 0x48;
ASSERT(SIZEOF(.game_rodata_particle_variants_8008F4E8) == 0x30, "particle_variants_8008F4E8 extent changed")
__game_rodata_particle_variants_8008F4E8_payload_size = 0x30;
ASSERT(SIZEOF(.game_rodata_particle_variants_8008F518) == 0x80, "particle_variants_8008F518 extent changed")
__game_rodata_particle_variants_8008F518_payload_size = 0x78;
ASSERT(SIZEOF(.game_rodata_particle_variants_8008F590) == 0x80, "particle_variants_8008F590 extent changed")
__game_rodata_particle_variants_8008F590_payload_size = 0x78;
ASSERT(SIZEOF(.game_rodata_particle_variants_8008F608) == 0x30, "particle_variants_8008F608 extent changed")
__game_rodata_particle_variants_8008F608_payload_size = 0x30;
ASSERT(SIZEOF(.game_rodata_particle_variants_8008F638) == 0x30, "particle_variants_8008F638 extent changed")
__game_rodata_particle_variants_8008F638_payload_size = 0x30;
ASSERT(SIZEOF(.game_rodata_particle_variants_8008F668) == 0x30, "particle_variants_8008F668 extent changed")
__game_rodata_particle_variants_8008F668_payload_size = 0x30;
ASSERT(SIZEOF(.game_rodata_particle_variants_8008F698) == 0x30, "particle_variants_8008F698 extent changed")
__game_rodata_particle_variants_8008F698_payload_size = 0x30;
ASSERT(SIZEOF(.game_rodata_particle_variants_8008F6C8) == 0x30, "particle_variants_8008F6C8 extent changed")
__game_rodata_particle_variants_8008F6C8_payload_size = 0x30;
ASSERT(SIZEOF(.game_rodata_particle_variants_8008F6F8) == 0x30, "particle_variants_8008F6F8 extent changed")
__game_rodata_particle_variants_8008F6F8_payload_size = 0x30;

ASSERT(SIZEOF(.game_rodata_model_fragment_roots) == 0x50, "model_fragment_roots extent changed")
__game_rodata_model_fragment_roots_payload_size = 0x50;
ASSERT(SIZEOF(.game_rodata_model_fragment_extra) == 0x10, "model_fragment_extra extent changed")
__game_rodata_model_fragment_extra_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_model_effect_lookup) == 0x3B0, "model_effect_lookup extent changed")
__game_rodata_model_effect_lookup_payload_size = 0x3A4;
ASSERT(SIZEOF(.game_rodata_model_fragment_scales) == 0x40, "model_fragment_scales extent changed")
__game_rodata_model_fragment_scales_payload_size = 0x3C;
ASSERT(SIZEOF(.game_rodata_model_fragment_selectors) == 0x2B0, "model_fragment_selectors extent changed")
__game_rodata_model_fragment_selectors_payload_size = 0x2A8;
ASSERT(SIZEOF(.game_rodata_model_fragment_counts) == 0x50, "model_fragment_counts extent changed")
__game_rodata_model_fragment_counts_payload_size = 0x50;
ASSERT(SIZEOF(.game_rodata_model_fragment_codes) == 0x50, "model_fragment_codes extent changed")
__game_rodata_model_fragment_codes_payload_size = 0x50;
ASSERT(SIZEOF(.game_rodata_model_effect_profiles) == 0x140, "model_effect_profiles extent changed")
__game_rodata_model_effect_profiles_payload_size = 0x140;

ASSERT(SIZEOF(.game_rodata_scene_preload_roots) == 0x20, "scene_preload_roots extent changed")
__game_rodata_scene_preload_roots_payload_size = 0x14;
ASSERT(SIZEOF(.game_rodata_ui_decimal_tables) == 0x50, "ui_decimal_tables extent changed")
__game_rodata_ui_decimal_tables_payload_size = 0x44;
ASSERT(SIZEOF(.game_rodata_ui_model_graphics) == 0x30, "ui_model_graphics extent changed")
__game_rodata_ui_model_graphics_payload_size = 0x28;
ASSERT(SIZEOF(.game_rodata_scene_preload_lists) == 0xA0, "scene_preload_lists extent changed")
__game_rodata_scene_preload_lists_payload_size = 0xA0;

ASSERT(SIZEOF(.game_rodata_ui_digit_columns) == 0x10, "ui_digit_columns extent changed")
__game_rodata_ui_digit_columns_payload_size = 0x4;
ASSERT(SIZEOF(.game_rodata_menu_primary_resources) == 0x20, "menu_primary_resources extent changed")
__game_rodata_menu_primary_resources_payload_size = 0x18;
ASSERT(SIZEOF(.game_rodata_menu_secondary_resources) == 0x20, "menu_secondary_resources extent changed")
__game_rodata_menu_secondary_resources_payload_size = 0x20;
ASSERT(SIZEOF(.game_rodata_menu_rotating_resources) == 0x20, "menu_rotating_resources extent changed")
__game_rodata_menu_rotating_resources_payload_size = 0x14;
ASSERT(SIZEOF(.game_rodata_cpu_texture_descriptors) == 0x9C0, "cpu_texture_descriptors extent changed")
__game_rodata_cpu_texture_descriptors_payload_size = 0x9B4;
ASSERT(SIZEOF(.game_rodata_model_extra_scales) == 0x10, "model_extra_scales extent changed")
__game_rodata_model_extra_scales_payload_size = 0xC;

ASSERT(SIZEOF(.game_rodata_cpu_texture_frames_800901F0) == 0x20, "cpu_texture_frames_800901F0 extent changed")
__game_rodata_cpu_texture_frames_800901F0_payload_size = 0x14;
ASSERT(SIZEOF(.game_rodata_cpu_texture_frames_8009073C) == 0x20, "cpu_texture_frames_8009073C extent changed")
__game_rodata_cpu_texture_frames_8009073C_payload_size = 0x20;
ASSERT(SIZEOF(.game_rodata_cpu_texture_frames_800907A4) == 0x10, "cpu_texture_frames_800907A4 extent changed")
__game_rodata_cpu_texture_frames_800907A4_payload_size = 0x8;
ASSERT(SIZEOF(.game_rodata_cpu_texture_frames_80090818) == 0x350, "cpu_texture_frames_80090818 extent changed")
__game_rodata_cpu_texture_frames_80090818_payload_size = 0x348;
ASSERT(SIZEOF(.game_rodata_cpu_texture_frames_80091520) == 0x50, "cpu_texture_frames_80091520 extent changed")
__game_rodata_cpu_texture_frames_80091520_payload_size = 0x44;
ASSERT(SIZEOF(.game_rodata_cpu_texture_frames_800915BC) == 0x20, "cpu_texture_frames_800915BC extent changed")
__game_rodata_cpu_texture_frames_800915BC_payload_size = 0x1C;
ASSERT(SIZEOF(.game_rodata_cpu_texture_frames_800917E4) == 0x10, "cpu_texture_frames_800917E4 extent changed")
__game_rodata_cpu_texture_frames_800917E4_payload_size = 0x8;

ASSERT(SIZEOF(.game_rodata_effect_texture_roots_8008CA4C) == 0x120, "effect_texture_roots_8008CA4C extent changed")
__game_rodata_effect_texture_roots_8008CA4C_payload_size = 0x118;
ASSERT(SIZEOF(.game_rodata_effect_texture_frames_80090358) == 0x30, "effect_texture_frames_80090358 extent changed")
__game_rodata_effect_texture_frames_80090358_payload_size = 0x30;
ASSERT(SIZEOF(.game_rodata_effect_texture_descriptors_80090388) == 0x10, "effect_texture_descriptors_80090388 extent changed")
__game_rodata_effect_texture_descriptors_80090388_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_effect_texture_descriptors_800903C8) == 0x20, "effect_texture_descriptors_800903C8 extent changed")
__game_rodata_effect_texture_descriptors_800903C8_payload_size = 0x18;
ASSERT(SIZEOF(.game_rodata_effect_texture_descriptors_80090420) == 0x60, "effect_texture_descriptors_80090420 extent changed")
__game_rodata_effect_texture_descriptors_80090420_payload_size = 0x60;
ASSERT(SIZEOF(.game_rodata_effect_texture_frames_80090480) == 0x20, "effect_texture_frames_80090480 extent changed")
__game_rodata_effect_texture_frames_80090480_payload_size = 0x14;
ASSERT(SIZEOF(.game_rodata_effect_texture_descriptors_80090494) == 0x10, "effect_texture_descriptors_80090494 extent changed")
__game_rodata_effect_texture_descriptors_80090494_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_effect_texture_frames_800904A0) == 0x20, "effect_texture_frames_800904A0 extent changed")
__game_rodata_effect_texture_frames_800904A0_payload_size = 0x14;
ASSERT(SIZEOF(.game_rodata_effect_texture_descriptors_800904B4) == 0x90, "effect_texture_descriptors_800904B4 extent changed")
__game_rodata_effect_texture_descriptors_800904B4_payload_size = 0x84;
ASSERT(SIZEOF(.game_rodata_effect_texture_frames_80090538) == 0x10, "effect_texture_frames_80090538 extent changed")
__game_rodata_effect_texture_frames_80090538_payload_size = 0x4;
ASSERT(SIZEOF(.game_rodata_effect_texture_descriptors_8009053C) == 0x10, "effect_texture_descriptors_8009053C extent changed")
__game_rodata_effect_texture_descriptors_8009053C_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_effect_texture_descriptors_800905A8) == 0x60, "effect_texture_descriptors_800905A8 extent changed")
__game_rodata_effect_texture_descriptors_800905A8_payload_size = 0x54;
ASSERT(SIZEOF(.game_rodata_effect_texture_frames_800905FC) == 0x10, "effect_texture_frames_800905FC extent changed")
__game_rodata_effect_texture_frames_800905FC_payload_size = 0x4;
ASSERT(SIZEOF(.game_rodata_effect_texture_descriptors_80090600) == 0x10, "effect_texture_descriptors_80090600 extent changed")
__game_rodata_effect_texture_descriptors_80090600_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_effect_texture_frames_80090620) == 0x20, "effect_texture_frames_80090620 extent changed")
__game_rodata_effect_texture_frames_80090620_payload_size = 0x14;
ASSERT(SIZEOF(.game_rodata_effect_texture_descriptors_80090634) == 0x10, "effect_texture_descriptors_80090634 extent changed")
__game_rodata_effect_texture_descriptors_80090634_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_effect_texture_frames_80090640) == 0x20, "effect_texture_frames_80090640 extent changed")
__game_rodata_effect_texture_frames_80090640_payload_size = 0x20;
ASSERT(SIZEOF(.game_rodata_effect_texture_descriptors_80090660) == 0x40, "effect_texture_descriptors_80090660 extent changed")
__game_rodata_effect_texture_descriptors_80090660_payload_size = 0x3C;
ASSERT(SIZEOF(.game_rodata_effect_texture_frames_8009069C) == 0x30, "effect_texture_frames_8009069C extent changed")
__game_rodata_effect_texture_frames_8009069C_payload_size = 0x28;
ASSERT(SIZEOF(.game_rodata_effect_texture_descriptors_800906C4) == 0x10, "effect_texture_descriptors_800906C4 extent changed")
__game_rodata_effect_texture_descriptors_800906C4_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_effect_texture_frames_800906D0) == 0x30, "effect_texture_frames_800906D0 extent changed")
__game_rodata_effect_texture_frames_800906D0_payload_size = 0x28;
ASSERT(SIZEOF(.game_rodata_effect_texture_descriptors_800906F8) == 0x30, "effect_texture_descriptors_800906F8 extent changed")
__game_rodata_effect_texture_descriptors_800906F8_payload_size = 0x24;
ASSERT(SIZEOF(.game_rodata_effect_texture_frames_8009071C) == 0x20, "effect_texture_frames_8009071C extent changed")
__game_rodata_effect_texture_frames_8009071C_payload_size = 0x14;
ASSERT(SIZEOF(.game_rodata_effect_texture_descriptors_80090730) == 0x10, "effect_texture_descriptors_80090730 extent changed")
__game_rodata_effect_texture_descriptors_80090730_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_effect_texture_descriptors_8009075C) == 0x10, "effect_texture_descriptors_8009075C extent changed")
__game_rodata_effect_texture_descriptors_8009075C_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_effect_texture_frames_80090768) == 0x20, "effect_texture_frames_80090768 extent changed")
__game_rodata_effect_texture_frames_80090768_payload_size = 0x14;
ASSERT(SIZEOF(.game_rodata_effect_texture_descriptors_8009077C) == 0x10, "effect_texture_descriptors_8009077C extent changed")
__game_rodata_effect_texture_descriptors_8009077C_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_effect_texture_frames_80090788) == 0x10, "effect_texture_frames_80090788 extent changed")
__game_rodata_effect_texture_frames_80090788_payload_size = 0x4;
ASSERT(SIZEOF(.game_rodata_effect_texture_descriptors_8009078C) == 0x20, "effect_texture_descriptors_8009078C extent changed")
__game_rodata_effect_texture_descriptors_8009078C_payload_size = 0x18;
ASSERT(SIZEOF(.game_rodata_effect_texture_descriptors_800907EC) == 0x10, "effect_texture_descriptors_800907EC extent changed")
__game_rodata_effect_texture_descriptors_800907EC_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_effect_texture_frames_800907F8) == 0x10, "effect_texture_frames_800907F8 extent changed")
__game_rodata_effect_texture_frames_800907F8_payload_size = 0x4;
ASSERT(SIZEOF(.game_rodata_effect_texture_descriptors_800907FC) == 0x10, "effect_texture_descriptors_800907FC extent changed")
__game_rodata_effect_texture_descriptors_800907FC_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_effect_texture_frames_80090808) == 0x10, "effect_texture_frames_80090808 extent changed")
__game_rodata_effect_texture_frames_80090808_payload_size = 0x4;
ASSERT(SIZEOF(.game_rodata_effect_texture_descriptors_8009080C) == 0x10, "effect_texture_descriptors_8009080C extent changed")
__game_rodata_effect_texture_descriptors_8009080C_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_effect_texture_descriptors_80091834) == 0x10, "effect_texture_descriptors_80091834 extent changed")
__game_rodata_effect_texture_descriptors_80091834_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_effect_texture_descriptors_8009184C) == 0x90, "effect_texture_descriptors_8009184C extent changed")
__game_rodata_effect_texture_descriptors_8009184C_payload_size = 0x90;

ASSERT(SIZEOF(.game_rodata_glyph_texture_data) == 0x1A0, "glyph texture extent changed")
__game_rodata_glyph_texture_data_payload_size = 0x198;

ASSERT(SIZEOF(.game_rodata_effect_texture_callbacks) == 0x10, "effect_texture_callbacks extent changed")
__game_rodata_effect_texture_callbacks_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_literal_effect_texture_800903B8) == 0x10, "literal_effect_texture_800903B8 extent changed")
__game_rodata_literal_effect_texture_800903B8_payload_size = 0x10;
ASSERT(SIZEOF(.game_rodata_literal_effect_texture_800903E0) == 0x20, "literal_effect_texture_800903E0 extent changed")
__game_rodata_literal_effect_texture_800903E0_payload_size = 0x20;
ASSERT(SIZEOF(.game_rodata_literal_effect_texture_80090558) == 0x50, "literal_effect_texture_80090558 extent changed")
__game_rodata_literal_effect_texture_80090558_payload_size = 0x50;
ASSERT(SIZEOF(.game_rodata_literal_effect_texture_80091840) == 0x10, "literal_effect_texture_80091840 extent changed")
__game_rodata_literal_effect_texture_80091840_payload_size = 0xC;

ASSERT(SIZEOF(.game_rodata_two_frame_effect_texture) == 0x20, "two_frame_effect_texture extent changed")
__game_rodata_two_frame_effect_texture_payload_size = 0x14;


ASSERT(SIZEOF(.game_rodata_weighted_record_800A2504) == 0x20, "weighted_record_800A2504 extent changed")
__game_rodata_weighted_record_800A2504_payload_size = 0x1C;

ASSERT(SIZEOF(.game_rodata_native_float_data_80088724) == 0x10, "native_float_data_80088724 extent changed")
__game_rodata_native_float_data_80088724_payload_size = 0xC;
ASSERT(SIZEOF(.game_rodata_native_float_data_800A49C0) == 0x70, "native_float_data_800A49C0 extent changed")
__game_rodata_native_float_data_800A49C0_payload_size = 0x6C;
ASSERT(SIZEOF(.game_rodata_native_float_data_800A4A2C) == 0x50, "native_float_data_800A4A2C extent changed")
__game_rodata_native_float_data_800A4A2C_payload_size = 0x48;

ASSERT(SIZEOF(.game_rodata_native_fp_control_8008CF00) == 0xA0, "native_fp_control_8008CF00 extent changed")
__game_rodata_native_fp_control_8008CF00_payload_size = 0xA0;
ASSERT(SIZEOF(.game_rodata_native_fp_control_80095C64) == 0x40, "native_fp_control_80095C64 extent changed")
__game_rodata_native_fp_control_80095C64_payload_size = 0x40;

ASSERT(SIZEOF(.game_rodata_weighted_vectors_800A24B0) == 0x60, "weighted_vectors_800A24B0 extent changed")
__game_rodata_weighted_vectors_800A24B0_payload_size = 0x54;
ASSERT(SIZEOF(.game_rodata_weighted_vectors_800A2520) == 0x50, "weighted_vectors_800A2520 extent changed")
__game_rodata_weighted_vectors_800A2520_payload_size = 0x48;
ASSERT(SIZEOF(.game_rodata_weighted_vectors_800A2568) == 0x60, "weighted_vectors_800A2568 extent changed")
__game_rodata_weighted_vectors_800A2568_payload_size = 0x54;
ASSERT(SIZEOF(.game_rodata_weighted_vectors_800A25BC) == 0x50, "weighted_vectors_800A25BC extent changed")
__game_rodata_weighted_vectors_800A25BC_payload_size = 0x48;

ASSERT(SIZEOF(.game_rodata_quarter_wave_8009A220) == 0x110, "quarter_wave_8009A220 extent changed")
__game_rodata_quarter_wave_8009A220_payload_size = 0x104;
ASSERT(SIZEOF(.game_rodata_inverse_angle_80098E00) == 0x200, "inverse_angle_80098E00 extent changed")
__game_rodata_inverse_angle_80098E00_payload_size = 0x200;
