"""Local ROM audit; writes metadata only to an explicitly chosen JSON path."""
import argparse
import copy
import hashlib
import json
from pathlib import Path
from .common import encoded, validate_paths, write_new


EXPECTED_MODELS = {
    15: (392, 'b57c378311888c5cf0a0cfe591b3ee8efa42aec8', 7, 5, 0),
    16: (392, 'd31eaf71afa2508e1a8d44696fee1c0c0290af3d', 7, 5, 0),
    18: (1224, '9d7aa8eff2253fa892c90fbee943d15b9ee92dad', 44, 54, 0),
    132: (2840, '2b97317a8c9aa47b04656922ef0d15f0e3e280e6', 96, 108, 9),
}


def require(condition, message):
    if not condition:
        raise ValueError(message)


def audit(rom_path):
    from scripts import model_assets as models
    from scripts import model_expression_constructors as expressions
    path, layout = models.resolve_rom('us', rom_path)
    rom, _ = models.normalize_rom(path.read_bytes())
    digest = hashlib.sha1(rom).hexdigest()
    require(digest == '4cbadd3c4e0729dec46af64ad018050eada4f47a', 'US ROM identity changed')
    game = models.parse_game_archive(rom[layout['game_start']:layout['game_end']])
    before = (hashlib.sha256(game.code).hexdigest(), hashlib.sha256(game.data).hexdigest())
    report = expressions.parse_expression_constructor_programs(
        game.code, layout['game_vram'], game.data, layout['game_data_vram'])
    require(before == (hashlib.sha256(game.code).hexdigest(), hashlib.sha256(game.data).hexdigest()),
            'expression decoding mutated its source')
    mutation_count = 0
    for blob, base, spans, label in ((game.code, layout['game_vram'], expressions.CONSUMERS, 'consumer'),
                                    (game.data, layout['game_data_vram'], expressions.SOURCE_SPANS, 'source')):
        for address, size, _ in spans:
            # Last-byte mutation also guards complete declared function/table extent.
            for offset in sorted({0, size // 2, size - 1}):
                changed = bytearray(blob)
                changed[address - base + offset] ^= 1
                try:
                    if label == 'consumer':
                        expressions.parse_expression_constructor_programs(
                            changed, base, game.data, layout['game_data_vram'])
                    else:
                        expressions.parse_expression_constructor_programs(
                            game.code, layout['game_vram'], changed, base)
                except ValueError as error:
                    require(f'{label} changed' in str(error), 'mutation rejected for an unexpected reason')
                else:
                    raise ValueError(f'unguarded {label} mutation at {address+offset:08X}')
                mutation_count += 1
    _, _, model_digest, bundles, _ = models.load_model_bundles('us', rom_path, 9)
    require(model_digest == digest, 'model ROM changed')
    invariants = []
    for bundle in bundles:
        if bundle.index not in EXPECTED_MODELS:
            continue
        require(len(bundle.segments) == 1 and bundle.segments[0].index == 0,
                'expression attachment segment inventory changed')
        raw = bundle.segments[0].data
        geometry, native = models.parse_attachment_model(raw, models.parse_model_geometry)
        require((len(raw), hashlib.sha1(raw).hexdigest(), len(geometry.vertices),
                 len(geometry.faces), len(native['joints'])) == EXPECTED_MODELS[bundle.index],
                'expression attachment source geometry/UV/rig identity changed')
        source = copy.deepcopy((geometry, native))
        repeated = expressions.parse_expression_constructor_programs(
            game.code, layout['game_vram'], game.data, layout['game_data_vram'])
        require(repeated == report and (geometry, native) == source, 'metadata operation mutated state')
        regions = {s['name']: raw[s['offset']:s['offset']+s['size']] for s in native['sections']}
        require(models.encode_attachment_model(geometry, native, regions) == raw,
                'native geometry/UV/rig reconstruction changed')
        invariants.append({'entry': bundle.index, 'segment': 0, 'source_bytes': len(raw),
                           'source_sha1': hashlib.sha1(raw).hexdigest(),
                           'vertices': len(geometry.vertices), 'uvs': models.texture_coordinate_count(geometry),
                           'faces': len(geometry.faces), 'joints': len(native['joints']),
                           'native_round_trip': True, 'metadata_decode_preserves_source': True})
    require(len(invariants) == len(EXPECTED_MODELS), 'expression attachment source missing')
    stored = models.load_character_expression_manifest('us', rom_path, digest)
    refs = [{'character_entry': model['character_entry'], 'preset': preset['index'],
             'action_selector': preset['animation_selector'], 'native_action': preset['native_action'],
             'action_parameter_raw': preset['animation_duration_raw']}
            for model in stored['models'] for preset in model['presets'] if preset['animation_selector']]
    return {'normalized_sha1': digest, 'derivation': 'newly derived from ROM consumers and tables',
            'constructors': report, 'stored_expression_references': refs,
            'geometry_uv_rig_invariants': invariants, 'rom_mutations_rejected': mutation_count,
            'scope': expressions.SCOPE, 'capture_inputs': []}


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--rom', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args(argv)
    validate_paths(args, ('rom',), ('output',))
    result = audit(args.rom)
    write_new(args.output, encoded(result))
    print(json.dumps({'operations': result['constructors']['operation_count'],
                      'entries': result['constructors']['attachment_entries'],
                      'stored_expression_references': len(result['stored_expression_references']),
                      'rom_mutations_rejected': result['rom_mutations_rejected'],
                      'models': result['geometry_uv_rig_invariants']}, indent=2))


if __name__ == '__main__':
    main()
