"""Full-payload texture contracts from existing ROM-backed model consumers."""
from __future__ import annotations

import hashlib
from pathlib import Path
from types import SimpleNamespace

try:
    from scripts import (model_assets as models, model_texture_sequences as sequences,
                         texture_assets as t, texture_rgba16, texture_native)
except ModuleNotFoundError:
    import model_assets as models
    import model_texture_sequences as sequences
    import texture_assets as t
    import texture_rgba16
    import texture_native

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
    return result
