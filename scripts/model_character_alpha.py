"""ROM-only, state-conditional evidence for the remaining character materials.

This diagnostic does not select an inspection preset or modify any export.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from scripts import model_assets as models, model_character_parts as parts
from scripts.rzip_archive import AssetBank


CALLER_SPANS = (
    (0x150169A0, 1908, '774d2e2e6e020e45f99980cef4342f92be94e5bb'),
    (0x1501D1D4, 132, 'a956c60b89ac78dc93a1b0879259c2749cf59fec'),
    (0x1501D348, 1892, '438ba4bb6e8349c0e0e649dadfad11df5e4c9d25'),
    (0x15022398, 400, '57111be545a15f9f9d05f2ef0a339b9d8fd19a5a'),
    (0x15022848, 156, 'c78174d428cb5484a962906086110df33fd36757'),
    (0x1502AC88, 636, '24f02469c9605e212ed65a4c75b216d50ef8577e'),
    (0x1502B350, 344, 'd789fbbc29db59a4ea107ebe753587f3774b8d51'),
    (0x1502B4A8, 288, 'd1a82190ae64677a9404302b5a61653a5770a7dc'),
    (0x1502B6BC, 308, '91ed9cccb2168331f871d0b5b3597f9cfc8f558f'),
    (0x1502B8E0, 212, '2aea02ea13f93c5c25772d23323e71f576b8e0de'),
    (0x1502C974, 704, '166b05f7f97b828a9ebad3c9a7e51e8a6b748eea'),
    (0x150615DC, 48, '8a4fe980ec54296c23b0180b9aeb2aa694d9fdd4'),
    (0x1506196C, 60, 'd8ea7ef06bfdcfef9cdbf35db05257f62ea68fbb'),
    (0x150825C0, 924, 'e626c88906c1344002292db83074802975dc059a'),
    (0x15082A44, 2152, 'df94e52b3063e063c091fac537096563d3e47620'),
    (0x150837D4, 280, '7bd9c8414be99e3bc26944fe08eb04064933a30d'),
    (0x150839B8, 272, '83514e60fb88c39b8e225ba6b68a54a5094c2dff'),
    (0x15083E0C, 132, 'fd044c1bd7448bc462a2a5a8eda7d7876153c772'),
    (0x150849CC, 76, 'f406a1972f5f0f73bdcce7b9fb373af650daf567'),
    (0x150859AC, 272, '052c8a8b5e3be9c51932ac759fcd5a9ae38e3d56'),
)
CALLER_TABLES = (
    (0x80096760, 152, 'd2805f5884afa263d5d6a6a8bfacfda5360e16cd'),
    (0x80096808, 164, '2684755d381a5e959bd1ff6bca799a010cdd6199'),
    (0x8009D9A0, 28, 'c09305583996294ea9ba0d81591d463512ce58e4'),
)


def checked_spans(data: bytes, base: int, spans: tuple) -> list[dict]:
    result = []
    for address, size, expected in spans:
        offset = address - base
        if offset < 0 or offset + size > len(data) or hashlib.sha1(
                data[offset:offset + size]).hexdigest() != expected:
            raise ValueError(f'ROM character caller evidence changed at 0x{address:08X}')
        result.append({'address': f'0x{address:08X}', 'bytes': size, 'sha1': expected})
    return result


def wrapper_opacity(actor_alpha: int, view_alpha: int, *, force_full: bool = False,
                    mode_4_alpha: int | None = None) -> int:
    """Conditional 1502C974 result after visibility gates, not observed state."""
    values = [actor_alpha, view_alpha] + ([] if mode_4_alpha is None else [mode_4_alpha])
    if any(not 0 <= value <= 255 for value in values):
        raise ValueError('expected byte opacity inputs')
    product = actor_alpha * view_alpha
    opacity = 255 if product == 255 * 255 else product >> 8
    if force_full:
        opacity = 255
    return opacity if mode_4_alpha is None else opacity * mode_4_alpha >> 8


def spawn_records(data: bytes, entries: set[int]) -> list[dict]:
    """Bank-0E records consumed by 150169A0 and 15082A44; zero-based indices."""
    if len(data) % 0x30:
        raise ValueError('character spawn payload is not a whole number of 0x30-byte records')
    result = []
    for offset in range(0, len(data), 0x30):
        raw = data[offset:offset + 0x30]
        if raw[4] in entries:
            result.append({'record_index': offset // 0x30, 'decoded_offset': offset,
                           'model': [1, raw[4], 0], 'actor_type_byte': raw[3],
                           'spawn_gate_byte': raw[2],
                           'ordinary_spawn_skipped': raw[2] == 1,
                           'script_selector': raw[0x28],
                           'initial_position_xyz': list(struct.unpack_from('>hhh', raw, 6)),
                           'record_hex': raw.hex()})
    return result


def script_tracks(data: bytes) -> list[dict]:
    """Decode only the bounded layout consumed by 1501D348/15022398."""
    if len(data) < 8:
        raise ValueError('script directory is truncated')
    table_size = struct.unpack_from('>I', data)[0]
    if not table_size or table_size % 8 or table_size > len(data):
        raise ValueError('script directory has an invalid span')
    blocks = []
    previous_end = table_size
    count = table_size // 8
    for index in range(count):
        start, flags = struct.unpack_from('>II', data, index * 8)
        size = flags & 0x0FFFFFFF
        if flags >> 28 != (8 if index == count - 1 else 0):
            raise ValueError('script child has unsupported flags or terminator')
        if size and (start < previous_end or start + size > len(data)):
            raise ValueError('script child has an invalid range')
        blocks.append((start, data[start:start + size] if size else b''))
        if size:
            previous_end = start + size
    header = blocks[0][1]
    if len(header) != 8:
        raise ValueError('script header must contain four halfwords')
    tracks = struct.unpack_from('>H', header)[0]
    if tracks > 255:
        raise ValueError('script track count exceeds the consumer byte counter')
    if count < 1 + 2 * tracks:
        raise ValueError('script is missing track descriptors')
    result = []
    descriptor_base = blocks[1 + tracks][0] if tracks else 0
    for index in range(tracks):
        track_offset, track = blocks[1 + index]
        offset, descriptor = blocks[1 + tracks + index]
        if len(descriptor) != 8 or offset != descriptor_base + index * 8:
            raise ValueError('script actor descriptors are not contiguous eight-byte records')
        if len(track) % 8:
            raise ValueError('script track has a partial eight-byte record')
        if len(track) // 8 > 65535:
            raise ValueError('script track exceeds the consumer halfword counter')
        result.append({'track_index': index, 'track_offset': track_offset,
                       'initial_counter': len(track) // 8,
                       'track_sha256': hashlib.sha256(track).hexdigest(),
                       'descriptor_offset': offset, 'descriptor_hex': descriptor.hex(),
                       'descriptor_type': struct.unpack_from('>H', descriptor)[0],
                       'script_selector': descriptor[2]})
    return result


def script_spawn_matches(tracks: list[dict], combined: bytes, entries: set[int]) -> list[dict]:
    # The runtime returns the first matching selector, including prefix records.
    first = {}
    for row in spawn_records(combined, set(range(256))):
        first.setdefault(row['script_selector'], row)
    matches = []
    for track in tracks:
        selector = track['script_selector']
        if track['descriptor_type'] != 2 or not track['initial_counter'] or not selector:
            continue
        row = first.get(selector)
        if row and row['model'][1] in entries:
            matches.append({**track, 'model': row['model'],
                            'combined_record_index': row['record_index']})
    return matches


def scene_scripts(normalized: bytes, layout: dict, scene: int, combined: bytes,
                  entries: set[int]) -> dict:
    bank = next(b for b in models.parse_asset_banks(normalized, layout['asset_table']) if b.index == 6)
    if bank.flags:
        raise ValueError('bank 06 has unsupported flags')
    source = next((e for e in models.parse_asset_entries(normalized, bank) if e.index == scene), None)
    if source is None:
        return {'scene': scene, 'scripts': [], 'source': 'no populated bank-06 scene entry'}
    if source.type_flags:
        raise ValueError('bank-06 scene directory has unsupported flags')
    children = models.parse_asset_entries(normalized, AssetBank(scene, source.start, source.end, 0))
    scripts = []
    for child in children:
        if child.type_flags & ~0x90:
            raise ValueError('bank-06 script has unsupported flags')
        raw = normalized[child.start:child.end]
        data = models.decode_rzip_chunk(raw).data if child.compressed else raw
        tracks = script_tracks(data)
        scripts.append({'asset_path': [6, scene, child.index],
                        'rom_span': [f'0x{x:X}' for x in (child.start, child.end)],
                        'decoded_bytes': len(data), 'sha256': hashlib.sha256(data).hexdigest(),
                        'tracks': tracks, 'matches': script_spawn_matches(tracks, combined, entries)})
    return {'scene': scene, 'scripts': scripts,
            'activation_entry': '0x1501D348',
            'activation_arguments': {'a0': scene, 'a1': 'script asset-path index', 'a2': 'script slot'},
            'gates': ['Selected slot byte at 800C35EA + slot must differ from 1.',
                      'Pending script byte at 800C35C4 must be zero.',
                      'Scene must equal 800BE9F0 for immediate loading; otherwise a transition is requested.',
                      'Type-2 track counter must be nonzero and its first matching spawn record must not already have an actor.'],
            'scope': 'Initial type-2 actor descriptors only; script activation and submitted draws remain unobserved.'}


def caller_evidence(normalized: bytes, layout: dict, game, entries: list[int]) -> dict:
    guards = checked_spans(game.code, layout['game_vram'], CALLER_SPANS)
    tables = checked_spans(game.data, layout['game_data_vram'], CALLER_TABLES)
    scene_switch = struct.unpack_from('>38I', game.data, 0x80096760 - layout['game_data_vram'])
    selection_switch = struct.unpack_from('>41I', game.data, 0x80096808 - layout['game_data_vram'])
    bank = next(b for b in models.parse_asset_banks(normalized, layout['asset_table']) if b.index == 14)
    if bank.flags:
        raise ValueError('bank 0E has unsupported flags')
    sources, contexts, scripts = [], [], []
    for source in models.parse_asset_entries(normalized, bank):
        raw = normalized[source.start:source.end]
        data = models.decode_rzip_chunk(raw).data if source.compressed else raw
        records = spawn_records(data, set(entries))
        sources.append({'entry': source.index, 'decoded_bytes': len(data),
                        'records': len(data) // 0x30, 'sha256': hashlib.sha256(data).hexdigest()})
        if not records:
            continue
        branch = scene_switch[source.index - 26] if 26 <= source.index < 64 else 0x150169F8
        prefix = {0x150169E0: (0x1A34E0, 0x1A37E0),
                  0x150169F8: (0x1A33F0, 0x1A34E0)}[branch]
        prefix_count = (prefix[1] - prefix[0]) // 0x30
        for record in records:
            record['combined_record_index'] = prefix_count + record['record_index']
        scripts.append(scene_scripts(normalized, layout, source.index,
                                     normalized[prefix[0]:prefix[1]] + data, set(entries)))
        contexts.append({'bank': 14, 'entry': source.index,
                         'rom_span': [f'0x{x:X}' for x in (source.start, source.end)],
                         'payload_sha256': hashlib.sha256(data).hexdigest(),
                         'prefix_record_count': prefix_count,
                         'prefix_rom_span': [f'0x{x:X}' for x in prefix],
                         'prefix_sha256': hashlib.sha256(normalized[prefix[0]:prefix[1]]).hexdigest(),
                         'records': records})
    choices = []
    for branch, entry in ((0x15016D68, 155), (0x15016D88, 154)):
        if entry in entries:
            choices.extend({'selection': index, 'branch': f'0x{branch:08X}',
                            'model': [1, entry, 0], 'actor_type_byte': 21}
                           for index, address in enumerate(selection_switch) if address == branch)
    return {'consumer_spans': guards, 'jump_table_spans': tables,
            'spawn_sources': sources, 'spawn_contexts': contexts,
            'scene_script_routes': scripts,
            'player_selection_cases': choices,
            'opacity_inputs': {'actor_alpha_offset': '0x07', 'view_alpha_offset': '0x0B + view_index',
                               'full_opacity_condition': 'Both input bytes are 255, before wrapper overrides.',
                               'force_full_condition': 'Non-null actor+0x318 pointer, word at pointer+0x2C equals 0x100, and view index differs from actor byte 0x127.',
                               'mode_4_global_alpha_address': '0x800DF7C4',
                               'mode_4_max_output': wrapper_opacity(255, 255, mode_4_alpha=255)},
            'limits': ['Spawn records and selectable cases are not positive runtime draws.',
                       'Combined record indices are not live actor slots.',
                       'Modes 3/4/5 can select an alternate model through 150849CC.',
                       'Masks, colour state, visibility gates and later actor mutations remain unresolved.']}


def render_table_for_call(mode: int, opacity: int) -> dict:
    """Conditional branches at 1502CF04–1502CFB8; not observed actor state."""
    if mode not in range(6) or not 0 <= opacity <= 255:
        raise ValueError('expected a reviewed draw mode 0–5 and byte opacity')
    table = 0x800832C0 if mode in (3, 5) else (0x80082FC0 if opacity < 255 else 0x80083140)
    return {'draw_mode': mode, 'caller_opacity': opacity,
            'segment_8_base': f'0x{table:08X}',
            'display_list_table': 'secondary' if mode == 3 else 'primary'}


def alpha_state(pair: tuple[int, int]) -> dict:
    other = models.decode_other_mode(pair)
    low = pair[1]
    return {'other_mode': [f'0x{x:08X}' for x in pair],
            'cycle_type': other['cycle_type'], 'texture_lut': other['texture_lut'],
            'alpha_compare': other['alpha_compare'],
            'alpha_coverage_select': bool(low & 0x2000),
            'coverage_times_alpha': bool(low & 0x1000),
            'force_blend': bool(low & 0x4000), 'depth_write': bool(low & 0x20),
            'blender_cycle_2_mux': [(low >> shift) & 3 for shift in (28, 24, 20, 16)],
            'zero_combiner_alpha_replaced_by_coverage': bool(low & 0x2000 and not low & 0x1000)}


def palette_evidence(run, payloads: dict[int, bytes]) -> dict | None:
    binding = run.palette
    if binding is None or binding.flat_index is None or binding.mode not in (1, 2):
        return None
    payload = payloads[binding.flat_index]
    size = 512 if binding.mode == 1 else 32
    if len(payload) < size:
        raise ValueError('ROM payload is shorter than its trailing palette')
    palette = payload[-size:]
    return {'flat_id': binding.flat_index, 'mode': binding.mode,
            'payload_bytes': len(payload), 'palette_offset': len(payload) - size,
            'palette_bytes': size, 'palette_sha256': hashlib.sha256(palette).hexdigest(),
            'payload_sha256': hashlib.sha256(payload).hexdigest(),
            'zero_alpha_entries': sum(not (x & 1) for (x,) in struct.iter_unpack('>H', palette)),
            'entries': size // 2,
            'scope': 'Trailing RGBA5551 palette bytes; not effective draw alpha or load-span approval.'}


def build_report(rom: Path | None, entries: list[int]) -> dict:
    path, layout = models.resolve_rom('us', rom)
    normalized, _ = models.normalize_rom(path.read_bytes())
    sha1 = hashlib.sha1(normalized).hexdigest()
    if sha1 not in layout['normalized_sha1']:
        raise ValueError('US normalized ROM SHA-1 mismatch')
    game = models.parse_game_archive(normalized[layout['game_start']:layout['game_end']])
    consumers = parts.verify_consumers(game.code, layout['game_vram'])
    tables = models.parse_runtime_render_state_tables(game.data, layout['game_data_vram'])
    payloads = models.load_flat_asset_payloads('us', rom, sha1)
    bank = next(b for b in models.parse_asset_banks(normalized, layout['asset_table']) if b.index == 1)
    if bank.flags:
        raise ValueError('bank 01 has unsupported flags')
    sources = {e.index: e for e in models.parse_asset_entries(normalized, bank)}
    records = []
    for entry in sorted(set(entries)):
        source = sources[entry]
        raw = normalized[source.start:source.end]
        data = models.decode_rzip_chunk(raw).data if source.compressed else raw
        geometry, character_layout = models.parse_character_model_geometry(data)
        geometry, _ = parts.primary_preview(data, geometry, character_layout)
        geometry, _, _ = models.omit_zero_area_preview_faces(geometry)
        runs = []
        for index, run in enumerate(geometry.material_runs):
            if not run.face_count:
                continue
            palette = palette_evidence(run, payloads)
            combine = models.decode_combine_mode(run.combine_mode)
            inputs = set(combine['inputs']) if combine else None
            no_texture = inputs is not None and not inputs & {'TEXEL0', 'TEXEL1'}
            zero = palette is not None and palette['zero_alpha_entries'] == palette['entries']
            if not (zero or no_texture):
                continue
            variants = []
            if run.other_mode_partial is None and run.other_mode is not None:
                variants.append({'source': 'explicit-model-command', **alpha_state(run.other_mode)})
            elif run.other_mode_partial is None and run.runtime_render_state_offset is not None:
                for table in tables:
                    row, = [r for r in table['entries'] if int(r['offset'], 0) == run.runtime_render_state_offset]
                    variants.append({'segment_8_base': table['base_address'],
                                     **alpha_state(tuple(int(x, 0) for x in row['other_mode']))})
            runs.append({'material_run': index, 'faces': run.face_count,
                         'combine_mode': [f'0x{x:08X}' for x in run.combine_mode] if combine else None,
                         'combine_formula': combine, 'palette': palette,
                         'all_palette_alpha_zero': zero,
                         'no_texture_input_in_either_combiner_cycle': no_texture,
                         'all_known_variants_two_cycle': bool(variants) and all(v['cycle_type'] == 'two-cycle' for v in variants),
                         'segment_8_offset': run.runtime_render_state_offset,
                         'conditional_states': variants})
        records.append({'model': [1, entry, 0], 'model_sha1': hashlib.sha1(data).hexdigest(),
                        'primary_faces': len(geometry.faces), 'runs': runs,
                        'effective_call_state': 'unresolved', 'export_eligibility': 'unchanged'})
    return {'schema_version': 3, 'normalized_sha1': sha1, 'consumers': consumers,
            'caller_evidence': caller_evidence(normalized, layout, game, entries),
            'conditional_call_selection': [render_table_for_call(mode, opacity)
                                           for mode in range(6) for opacity in (0, 254, 255)],
            'models': records,
            'limits': ['No actual caller opacity, draw mode, part masks or colour state is established.',
                       'Coverage replacement does not establish native visibility or glTF parity.',
                       'Non-textured combiners still need primitive/environment colour and K5 evidence.',
                       'No geometry, palette alpha, material binding or gallery eligibility is changed.']}


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--rom', type=Path)
    parser.add_argument('--entry', type=int, action='append', help='decimal bank-01 entry (repeatable)')
    parser.add_argument('--output', type=Path, default=ROOT / 'build/assets/models/character-alpha-frontier.json')
    args = parser.parse_args()
    try:
        report = build_report(args.rom, args.entry or [154, 155, 162])
    except (ValueError, KeyError, OSError) as error:
        parser.error(str(error))
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + '\n')
    for row in report['models']:
        zero = sum(r['faces'] for r in row['runs'] if r['all_palette_alpha_zero']
                   and not r['no_texture_input_in_either_combiner_cycle'])
        untextured = sum(r['faces'] for r in row['runs'] if r['no_texture_input_in_either_combiner_cycle'])
        print(f"01:{row['model'][1]:04d}:00: {zero} textured faces with zero-alpha palettes; "
              f"{untextured} faces with texture-independent combiners; call state unresolved")
    for context in report['caller_evidence']['spawn_contexts']:
        print(f"ROM spawn bank 0E / scene {context['entry']:02d}: "
              f"{len(context['records'])} matching records; not observed draws")
    for scene in report['caller_evidence']['scene_script_routes']:
        for script in scene['scripts']:
            if script['matches']:
                ids = ', '.join(f"01:{row['model'][1]:04d}:00" for row in script['matches'])
                print(f"ROM script {script['asset_path']}: {ids}; conditional activation only")
    print(f'Report: {args.output}')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
