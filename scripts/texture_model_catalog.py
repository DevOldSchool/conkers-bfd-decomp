"""Full-payload texture contracts from existing ROM-backed model consumers."""
from __future__ import annotations

import hashlib
from dataclasses import replace
from pathlib import Path
from types import SimpleNamespace

try:
    from scripts import (model_assets as models, model_texture_sequences as sequences,
                         texture_assets as t, texture_rgba16, texture_native, texture_model_storage)
except ModuleNotFoundError:
    import model_assets as models
    import model_texture_sequences as sequences
    import texture_assets as t
    import texture_rgba16
    import texture_native
    import texture_model_storage

FORMATS = {(2, 0): 'ci4', (2, 1): 'ci8', (0, 2): 'rgba16', (0, 3): 'rgba32',
           (3, 0): 'ia4', (3, 1): 'ia8', (3, 2): 'ia16', (4, 0): 'i4', (4, 1): 'i8'}


def full_payload_contract(preview, payload: bytes) -> dict | None:
    """A useful preview is insufficient: its inverse must recover every byte."""
    fmt = FORMATS.get((preview.format, preview.size))
    if fmt is None or preview.png_data is None:
        return None
    width, height = preview.width, preview.height
    row = t.ROW_LAYOUT_TMEM
    try:
        if fmt == 'ci4':
            decoded = t.decode_indexed_png(preview.png_data, row, width, height)
        elif fmt == 'ci8':
            decoded = t.decode_ci8_png(preview.png_data, row, width, height)
        elif fmt == 'rgba16':
            decoded = texture_rgba16.decode_png(preview.png_data, row, width, height)
        else:
            decoded = texture_native.decode_png(preview.png_data, fmt, row, width, height)
    except (ValueError, IndexError):
        # Cropped/narrow TMEM views and transformed alpha are not reversible
        # full-storage sources. No trailing bytes or palette slots are inferred.
        return None
    if decoded != payload:
        return None
    return {'format': fmt, 'width': width, 'height': height,
            'row_layout': row, 'source_origin': 'bottom-left'}


def binding_variant(run, first, variant, payloads, tables, context):
    """Reproduce a variant already decoded by the complete binding resolver."""
    resource = variant['flat_index']
    pixel = replace(run.pixel, flat_index=resource, mode=0, segment=None, offset=None)
    palette = run.palette
    if palette is not None:
        if (first.format, first.size) not in ((2, 0), (2, 1)):
            raise ValueError('binding variant has an unsupported palette format')
        palette = replace(palette, flat_index=resource, mode=2 if first.size == 0 else 1,
                          segment=None, offset=None)
    mapped = replace(run, pixel=pixel, palette=palette)
    preview, status = models.choose_preview_texture(mapped, {}, payloads)
    if preview is None:
        preview, status, _ = models.rom_object_preview_texture(mapped, {}, payloads, tables, context)
    if (preview is None or preview.flat_index != resource or preview.sha1 != variant['png_sha1']
            or (preview.width, preview.height, preview.format, preview.size)
            != (first.width, first.height, first.format, first.size)):
        raise ValueError('binding variant differs from the complete ROM binding proof')
    return preview, status


def load(root: Path, rom: bytes, entries, excluded_ids=()) -> dict[int, dict]:
    path = root / 'roms/baserom.us.z64'
    digest = hashlib.sha1(rom).hexdigest()
    payloads = {entry.index: entry.data for entry in entries}
    excluded = set(excluded_ids)
    result = {}
    source_models = []
    bank_contexts = {}

    def accept(preview, family, consumer):
        if preview is None or preview.flat_index not in payloads:
            return
        resource = preview.flat_index
        if resource in excluded or resource in result:
            return
        contract = full_payload_contract(preview, payloads[resource])
        if contract is not None:
            result[resource] = dict(contract, family=family, consumer=consumer)

    for bank in models.BANK_INDICES:
        _, _, checked, bundles, tables = models.load_model_bundles('us', path, bank)
        if checked != digest:
            raise ValueError('model texture reference ROM changed')
        bank_contexts[bank] = tables
        for bundle in bundles:
            for segment in bundle.segments:
                if not segment.data:
                    continue
                if bank == 1:
                    geometry, character = models.parse_character_model_geometry(segment.data)
                else:
                    geometry = models.parse_segment_geometry(segment, bank)
                    character = None
                source_models.append((bank, bundle.index, segment, geometry, character))
                for index, run in enumerate(geometry.material_runs):
                    if (run.pixel is None or run.pixel.flat_index not in payloads
                            or run.pixel.flat_index in excluded or run.pixel.flat_index in result):
                        continue
                    preview, status = models.choose_preview_texture(run, {}, payloads)
                    if preview is None:
                        preview, status, _ = models.rom_render_state_preview_texture(
                            run, {}, payloads, tables)
                    accept(preview, 'model-material', {
                        'model': [bank, bundle.index, segment.index], 'material_run': index,
                        'status': status, 'model_sha1': hashlib.sha1(segment.data).hexdigest()})

    manifest, files = sequences.build_export(path)
    if manifest['normalized_sha1'] != digest:
        raise ValueError('texture sequence reference ROM changed')
    for record in manifest['images']:
        preview = SimpleNamespace(
            flat_index=record['flat_index'], format=record['format'], size=record['size'],
            width=record['width'], height=record['height'], png_data=files[record['file']])
        bindings = [{'model': binding['model'], 'material_run': binding['material_run'],
                     'kind': binding['kind']}
                    for binding in manifest['bindings']
                    if any(frame['flat_index'] == record['flat_index']
                           and frame['png_sha1'] == record['png_sha1']
                           for frame in binding['frames'])]
        if not bindings:
            raise ValueError('texture sequence image lacks a verified consumer')
        accept(preview, 'model-sequence', {'bindings': bindings,
                                         'status': record['texture_status']})

    contexts = {}
    for bank in (3, 4, 9):
        context = models.load_object_material_context('us', path, digest, bank)
        contexts.update({(bank, r['entry'], r['segment']): r for r in context['models']})
    defaults = models.load_character_defaults('us', path, digest)
    for bank, entry, segment, geometry, character in source_models:
        tables = bank_contexts[bank]
        context = contexts.get((bank, entry, segment.index))
        geometry, update = models.apply_rom_attachment_preview_update(
            segment.data, geometry, context)
        geometry, ui = models.model_ui_materials.apply_preview_geometry(
            geometry, segment.data, context, payloads, {})
        for index, run in enumerate(geometry.material_runs):
            if run.pixel is None or not run.texture_enabled or not run.texture_coordinates_proven:
                continue
            if run.pixel.flat_index in excluded or run.pixel.flat_index in result:
                continue
            preview = None
            if bank == 1 and run.pixel.segment in (6, 7, 10, 11):
                default = models.model_character_defaults.preview_defaults(defaults, entry)
                if default is not None:
                    preview, status, _ = models.rom_default_preview_texture(
                        run, default, character['texture_descriptors'], payloads, tables)
            else:
                resolvers = [
                    (models.rom_object_preview_texture, (run, {}, payloads, tables, context)),
                    (models.rom_object_animation_preview_texture, (run, {}, payloads, tables, context)),
                    (models.rom_object_binding_preview_texture, (run, {}, payloads, tables, context)),
                    (models.rom_scene_preview_texture, (run, {}, payloads, context))]
                if update is not None:
                    resolvers.append((models.rom_attachment_binding_preview_texture,
                                      (run, {}, payloads, update)))
                if ui is not None:
                    resolvers.append((models.rom_direct_binding_preview_texture,
                                      (run, {}, payloads, ui)))
                for resolve, args in resolvers:
                    preview, status, _ = resolve(*args)
                    if preview is not None:
                        break
            if preview is not None:
                accept(preview, 'model-binding', {
                    'model': [bank, entry, segment.index], 'material_run': index,
                    'status': status, 'model_sha1': hashlib.sha1(segment.data).hexdigest()})
    # Preserve earlier source contracts by expanding only after all established
    # single-image, frame-set and binding consumers have been resolved.
    for bank, entry, segment, geometry, _ in source_models:
        for index, run in enumerate(geometry.material_runs):
            if (run.pixel is None or run.pixel.flat_index not in payloads
                    or run.pixel.flat_index in excluded or run.pixel.flat_index in result):
                continue
            try:
                contract = texture_model_storage.layered_contract(run, payloads[run.pixel.flat_index])
            except ValueError:
                continue  # Unresolved texture-coordinate state is not evidence.
            if contract is not None:
                result[run.pixel.flat_index] = dict(contract, family='model-storage', consumer={
                    'model': [bank, entry, segment.index], 'material_run': index,
                    'status': 'complete-declared-TMEM-storage',
                    'model_sha1': hashlib.sha1(segment.data).hexdigest()})

    if any(bank == 1 for bank, *_ in source_models):
        defaults = models.load_character_defaults('us', path, digest, include_expressions=True)
        choices = {entry: texture_model_storage.selector_choices(defaults, entry, rom)
                   for entry in defaults['entries']}
        for bank, entry, segment, geometry, character in source_models:
            if bank != 1:
                continue
            for index, run in enumerate(geometry.material_runs):
                if run.pixel is None or run.pixel.segment not in (6, 7, 10, 11):
                    continue
                for choice, default in choices.get(entry, []):
                    descriptor = models.model_character_defaults.select_descriptor(
                        default, character['texture_descriptors'], run.pixel.segment)
                    if (descriptor is None or descriptor['flat_index'] not in payloads
                            or descriptor['flat_index'] in excluded or descriptor['flat_index'] in result):
                        continue
                    preview, status, _ = models.rom_default_preview_texture(
                        run, default, character['texture_descriptors'], payloads, bank_contexts[bank])
                    accept(preview, 'model-selector', {
                        'model': [bank, entry, segment.index], 'material_run': index,
                        'selection': choice, 'status': status,
                        'model_sha1': hashlib.sha1(segment.data).hexdigest(),
                        'initializer_sha1': default['sha1'],
                        'descriptor_indices': default['descriptor_indices'],
                        'expression_texture_selection': default.get('expression_texture_selection')})
    for bank, entry, segment, geometry, _ in source_models:
        for index, run in enumerate(geometry.material_runs):
            if (run.pixel is None or run.pixel.flat_index not in payloads
                    or run.pixel.flat_index in excluded or run.pixel.flat_index in result):
                continue
            try:
                contract = texture_model_storage.layered_contract(
                    run, payloads[run.pixel.flat_index], storage_extensions=True)
            except ValueError:
                continue
            if contract is not None:
                result[run.pixel.flat_index] = dict(contract, family='model-storage-extended', consumer={
                    'model': [bank, entry, segment.index], 'material_run': index,
                    'status': 'complete-source-storage-not-rendered-appearance',
                    'model_sha1': hashlib.sha1(segment.data).hexdigest()})
    # Append new consumer classes after established contracts so existing PNG
    # bundles and their provenance never change when coverage expands.
    for bank, entry, segment, geometry, character in source_models:
        if bank != 1:
            continue
        for index, run in enumerate(geometry.material_runs):
            if run.pixel is None or run.pixel.segment not in (6, 7, 10, 11):
                continue
            for choice, default in choices.get(entry, []):
                descriptor = models.model_character_defaults.select_descriptor(
                    default, character['texture_descriptors'], run.pixel.segment)
                if (descriptor is None or descriptor['flat_index'] not in payloads
                        or descriptor['flat_index'] in excluded or descriptor['flat_index'] in result):
                    continue
                resource = descriptor['flat_index']
                preview, status, evidence = models.rom_default_preview_texture(
                    run, default, character['texture_descriptors'], payloads, bank_contexts[bank])
                if preview is None or preview.flat_index != resource:
                    continue
                try:
                    contract = texture_model_storage.bound_contract(run, preview, payloads[resource])
                except ValueError:
                    continue
                if contract is not None:
                    result[resource] = dict(contract, family='model-selector-storage', consumer={
                        'model': [bank, entry, segment.index], 'material_run': index,
                        'selection': choice, 'status': status, 'binding_evidence': evidence,
                        'model_sha1': hashlib.sha1(segment.data).hexdigest(),
                        'initializer_sha1': default['sha1'],
                        'descriptor_indices': default['descriptor_indices'],
                        'expression_texture_selection': default.get('expression_texture_selection')})
    for bank, entry, segment, geometry, _ in source_models:
        if bank != 9:
            continue
        adjusted, state = models.model_special_attachment_materials.apply_preview_geometry(
            geometry, segment.data, contexts.get((bank, entry, segment.index)), payloads, {})
        if state is None:
            continue
        for index, run in enumerate(adjusted.material_runs):
            preview, status = models.choose_preview_texture(run, {}, payloads)
            if preview is None:
                preview, status, _ = models.rom_render_state_preview_texture(
                    run, {}, payloads, bank_contexts[bank])
            accept(preview, 'model-special-attachment', {
                'model': [bank, entry, segment.index], 'material_run': index,
                'status': status, 'model_sha1': hashlib.sha1(segment.data).hexdigest()})
    for bank, entry, segment, geometry, _ in source_models:
        for index, run in enumerate(geometry.material_runs):
            if (run.pixel is None or run.pixel.flat_index not in payloads
                    or run.pixel.flat_index in excluded or run.pixel.flat_index in result):
                continue
            preview, status = models.choose_preview_texture(run, {}, payloads)
            if preview is None:
                preview, status, _ = models.rom_render_state_preview_texture(
                    run, {}, payloads, bank_contexts[bank])
            try:
                contract = texture_model_storage.detail_contract(run, preview, payloads[run.pixel.flat_index])
            except ValueError:
                continue
            if contract is not None:
                result[run.pixel.flat_index] = dict(contract, family='model-detail-storage', consumer={
                    'model': [bank, entry, segment.index], 'material_run': index,
                    'status': status, 'model_sha1': hashlib.sha1(segment.data).hexdigest()})
    for bank, entry, segment, geometry, _ in source_models:
        for index, run in enumerate(geometry.material_runs):
            if (run.pixel is None or run.pixel.flat_index not in payloads
                    or run.pixel.flat_index in excluded or run.pixel.flat_index in result):
                continue
            try:
                authored = texture_model_storage.authored_contract(
                    segment.data, geometry, run, payloads[run.pixel.flat_index])
            except ValueError:
                continue
            if authored is not None:
                contract, evidence = authored
                result[run.pixel.flat_index] = dict(contract, family='model-authored-storage', consumer={
                    'model': [bank, entry, segment.index], 'material_run': index,
                    'status': 'complete-authored-source-storage', 'authored_storage': evidence,
                    'model_sha1': hashlib.sha1(segment.data).hexdigest()})
    # Constructor-only expression actions return before the same selector
    # writes. Keep this expansion last to preserve all earlier source contracts.
    for bank, entry, segment, geometry, character in source_models:
        if bank != 1 or entry != 0:
            continue
        for index, run in enumerate(geometry.material_runs):
            if run.pixel is None or run.pixel.segment not in (6, 7, 10, 11):
                continue
            for choice, default in texture_model_storage.action_selector_choices(defaults, entry):
                descriptor = models.model_character_defaults.select_descriptor(
                    default, character['texture_descriptors'], run.pixel.segment)
                if (descriptor is None or descriptor['flat_index'] not in payloads
                        or descriptor['flat_index'] in excluded or descriptor['flat_index'] in result):
                    continue
                preview, status, _ = models.rom_default_preview_texture(
                    run, default, character['texture_descriptors'], payloads, bank_contexts[bank])
                accept(preview, 'model-action-selector', {
                    'model': [bank, entry, segment.index], 'material_run': index,
                    'selection': choice, 'status': status,
                    'model_sha1': hashlib.sha1(segment.data).hexdigest(),
                    'initializer_sha1': default['sha1'],
                    'descriptor_indices': default['descriptor_indices'],
                    'expression_texture_selection': default['expression_texture_selection']})
    for bank, entry, segment, geometry, _ in source_models:
        if bank not in (3, 4, 9):
            continue
        context = contexts.get((bank, entry, segment.index))
        geometry, update = models.apply_rom_attachment_preview_update(segment.data, geometry, context)
        geometry, ui = models.model_ui_materials.apply_preview_geometry(
            geometry, segment.data, context, payloads, {})
        tables = bank_contexts[bank]
        for index, run in enumerate(geometry.material_runs):
            if run.pixel is None or run.pixel.flat_index is not None:
                continue
            resolvers = [(models.rom_object_binding_preview_texture, (run, {}, payloads, tables, context))]
            if update is not None:
                resolvers.append((models.rom_attachment_binding_preview_texture, (run, {}, payloads, update)))
            if ui is not None:
                resolvers.append((models.rom_direct_binding_preview_texture, (run, {}, payloads, ui)))
            for resolve, args in resolvers:
                first, _, proof = resolve(*args)
                if first is None:
                    continue
                for variant in proof['decoded_variants']:
                    resource = variant['flat_index']
                    if resource in excluded or resource in result:
                        continue
                    preview, status = binding_variant(run, first, variant, payloads, tables, context)
                    accept(preview, 'model-binding-variant', {
                        'model': [bank, entry, segment.index], 'material_run': index,
                        'status': status, 'model_sha1': hashlib.sha1(segment.data).hexdigest(),
                        'selected_variant': variant, 'complete_binding': proof})
    # Keep additional renderer states last: earlier manifests and PNGs retain
    # their original consumer even when the same storage has another view.
    for bank, entry, segment, geometry, character in source_models:
        if bank != 1 or entry != 123:
            continue
        for choice, default in texture_model_storage.renderer_selector_choices(defaults, entry):
            for index, run in enumerate(geometry.material_runs):
                if run.pixel is None or run.pixel.segment not in (10, 11):
                    continue
                descriptor = models.model_character_defaults.select_descriptor(
                    default, character['texture_descriptors'], run.pixel.segment)
                if (descriptor is None or descriptor['flat_index'] not in payloads
                        or descriptor['flat_index'] in excluded or descriptor['flat_index'] in result):
                    continue
                preview, status, _ = models.rom_default_preview_texture(
                    run, default, character['texture_descriptors'], payloads, bank_contexts[bank])
                accept(preview, 'model-renderer-variant', {
                    'model': [bank, entry, segment.index], 'material_run': index,
                    'selection': choice, 'status': status,
                    'model_sha1': hashlib.sha1(segment.data).hexdigest(),
                    'initializer_sha1': default['sha1'],
                    'descriptor_indices': default['descriptor_indices'],
                    'renderer_texture_selection': default['renderer_texture_selection']})
    return result
