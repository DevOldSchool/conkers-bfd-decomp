"""ROM-proven copied display-list state for bank-09 UI entries 162 and 164.

The preview retains stored geometry and neutral joints. It does not replay native
UI animation, position, visibility, environment opacity or rasterization.
"""
from dataclasses import asdict, replace
import hashlib
import struct

CONSUMERS = (
    (0x151EB06C, 2244, '321cdb6b0234419d3d38a4acc4151786d502aeea'),
    (0x151ED90C, 588, '4477ab2487888005b9b981d746d3e4827632f631'),
    (0x151EDBDC, 880, '2a0fcb728902c350ede39802852cee5080623817'),
    (0x1503F62C, 396, 'b678946246dbc937322777d197d874c3dbd0839b'),
    (0x1502FE10, 456, '8637778facf0ce5e9a4cd03316b390e02fdf84e2'),
    (0x1510CE60, 652, '9a12376e197e0ae05d6d351d5d538865aa7dcc68'),
    (0x1510D0EC, 648, '47b67aab9ed8a4eb1706ced5424981ff21373aba'),
)

# Explicit instruction checks complement complete consumer pins; literals alone
# do not establish the intervening register, allocation and copied-list flow.
GUARDS = (
    (0x151EB5AC, 0x240400A4), (0x151EB5B4, 0x24050017),
    (0x151EB5BC, 0x0D47B643), (0x151EB5C8, 0xAC220058),
    (0x151EB5CC, 0x240400A2), (0x151EB5D0, 0x24050008),
    (0x151EB5D8, 0x0D47B643), (0x151EB5E4, 0xAC22005C),
    (0x151EB694, 0x8CA50058), (0x151EB714, 0x0D47B6F7),
    (0x151EB724, 0x8CA5005C), (0x151EB754, 0x0D47B6F7),
    (0x151ED960, 0x240E0001), (0x151ED964, 0xA2AE0015),
    (0x151ED98C, 0x0D40FD8B),
    (0x151EDAA4, 0x3C080050), (0x151EDAA8, 0x3C07FFFE),
    (0x151EDAAC, 0x34E7FFFF), (0x151EDAB0, 0x350841C8),
    (0x151EDABC, 0x240900FC), (0x151EDAC0, 0x240600EF),
    (0x151EDAF0, 0x15860004), (0x151EDAF8, 0x01476824),
    (0x151EDAFC, 0xAC4D0000), (0x151EDB00, 0xAC480004),
    (0x151EDB04, 0x14890002), (0x151EDB0C, 0xAC400000),
    (0x151EDD48, 0x3C0CFC12), (0x151EDD4C, 0x358CFE25),
    (0x151EDD50, 0x240DFBFD), (0x151EDD54, 0xACCD0004),
    (0x151EDD58, 0xACCC0000),
    (0x151EDE38, 0x8DEF0058), (0x151EDE3C, 0x562F0029),
    (0x151EDE44, 0x92380015), (0x151EDE48, 0x2709FFFF),
    (0x151EDE4C, 0x312300FF), (0x151EDE50, 0x14600007),
    (0x151EDE54, 0xA2290015), (0x151EDE60, 0x3059007F),
    (0x151EDE64, 0x272A000F), (0x151EDE68, 0xA22A0015),
    (0x151EDE6C, 0x314300FF), (0x151EDE70, 0x28610007),
    (0x151EDE74, 0x10200004), (0x151EDE78, 0x00002825),
    (0x151EDE84, 0x24840507), (0x151EDE8C, 0x24840508),
    (0x151EDE94, 0x0D44343B), (0x151EDEB4, 0x3C0BDB06),
    (0x151EDEB8, 0x356B0018), (0x151EDEBC, 0xAC6B0000),
    (0x151EDEC0, 0xAC620004), (0x151EDECC, 0x3C0CDB06),
    (0x151EDED0, 0x358C001C), (0x151EDED4, 0xAC8C0000),
    (0x151EDED8, 0xAC820004), (0x151EDEFC, 0xAC480000),
    (0x151EDF00, 0x8C8E0004), (0x151EDF08, 0xAC4E0004),
)

DATA = ((0x80090058, '0000000000000000'),
        (0x80090110, 'e700000000000000d700000280008000df00000000000000'))
MODELS = {162: (2728, '495cde88325beee15d1dfd5cf299bb07a3629f1e', 108, 6),
          164: (3256, 'becd009254e612e93cba4f3dd9483096cb9613cc', 65, 8)}
PAYLOADS = {1287: (2560, '60437bba6f1e6c20f7c4888e212f5d7ce85aa42b'),
            1288: (2560, '5f4fbbce8a5e13ef37e05a1fb2421c05e08646c8')}
COMBINE = (0xFC12FE25, 0xFFFFFBFD)
SCOPE = ('ROM constructor first-draw texture state with stored geometry and neutral '
         'joints. UI animation, position, visibility, dynamic environment opacity '
         'and native raster appearance remain unresolved. The texture PNG retains '
         'source texel alpha; native combiner alpha instead uses ENVIRONMENT.')


def checked(blob, base, address, size):
    offset = address - base
    if offset < 0 or size < 0 or offset + size > len(blob):
        raise ValueError('UI evidence span outside input')
    return blob[offset:offset + size]


def first_draw_flat(counter=1, random_value=0):
    """Pinned renderer selector after decrement; expose RNG only for proof tests."""
    if type(counter) is not int or not 0 <= counter <= 255 or type(random_value) is not int:
        raise ValueError('UI blink selector inputs must be integers and a byte counter')
    next_counter = (counter - 1) & 255
    if next_counter == 0:
        next_counter = (random_value & 127) + 15
    return 1287 if next_counter < 7 else 1288


def model_context(entry):
    if type(entry) is not int or entry not in MODELS:
        raise ValueError('UI context entry is unsupported')
    return {'bank': 9, 'entry': entry, 'segment': 0,
            'renderer': 'func_151EDBDC',
            'ui_material_state': 'constructor-first-draw',
            'constructor': 'func_151ED90C',
            'model_pointer': f'0x{0x80090058 if entry == 164 else 0x8009005C:08X}',
            'animation_selector': 23 if entry == 164 else 8,
            'scope': SCOPE}


def material_context(code, code_base, data, data_base):
    for address, size, expected in CONSUMERS:
        if hashlib.sha1(checked(code, code_base, address, size)).hexdigest() != expected:
            raise ValueError(f'UI consumer changed: 0x{address:08X}')
    for address, expected in GUARDS:
        if checked(code, code_base, address, 4) != struct.pack('>I', expected):
            raise ValueError(f'UI instruction changed: 0x{address:08X}')
    for address, expected in DATA:
        raw = bytes.fromhex(expected)
        if checked(data, data_base, address, len(raw)) != raw:
            raise ValueError(f'UI constructor or setup data changed: 0x{address:08X}')
    return {'consumers': [{'function': f'func_{a:08X}', 'size': n, 'sha1': h}
                          for a, n, h in CONSUMERS],
            'models': [model_context(entry) for entry in sorted(MODELS)],
            'capture_inputs': []}


def _source_geometry(model_bytes):
    try:
        from scripts import model_assets as models
    except ModuleNotFoundError:
        import model_assets as models
    return models.parse_attachment_model(model_bytes, models.parse_model_geometry)[0]


def apply_preview_geometry(geometry, model_bytes, context, payloads, runtime_materials=None):
    """Apply the pinned UI copy operations; preserve source vertices and faces.

    Invoke before face omission and ordinary texture choice. Return the original
    object unchanged for every context outside this separately proven UI path.
    The caller must keep its source_geometry for source/run accounting.
    """
    if not context or 'ui_material_state' not in context:
        return geometry, None
    if runtime_materials:
        return geometry, None
    entry = context.get('entry')
    if (type(entry) is not int or entry not in MODELS
            or any(type(context.get(key)) is not int
                   for key in ('bank', 'segment', 'animation_selector'))
            or context != model_context(entry)):
        raise ValueError('UI context identity changed')
    size, expected, faces, runs = MODELS[entry]
    if len(model_bytes) != size or hashlib.sha1(model_bytes).hexdigest() != expected:
        raise ValueError('UI source model changed')
    if len(geometry.faces) != faces or len(geometry.material_runs) != runs:
        raise ValueError('UI source geometry accounting changed')
    # The direct CLI and package imports have separate dataclass identities.
    # Compare every decoded field, including nested runs/vertices, across them.
    if asdict(geometry) != asdict(_source_geometry(model_bytes)):
        raise ValueError('UI source geometry differs from the pinned model')
    if entry == 164:
        for flat, (size, expected) in PAYLOADS.items():
            raw = payloads.get(flat)
            if raw is None or len(raw) != size or hashlib.sha1(raw).hexdigest() != expected:
                raise ValueError('UI blink payload changed')

    def binding(value):
        if value is None or value.segment is None:
            return value
        if (entry != 164 or value.external or value.flat_index is not None
                or value.segment not in (6, 7) or value.offset not in (0, 2048)):
            raise ValueError('UI runtime texture binding changed')
        return replace(value, flat_index=first_draw_flat(),
                       mode=0 if value.offset == 0 else 1, segment=None, offset=None)

    mapped = []
    for run in geometry.material_runs:
        if run.other_mode is None or run.other_mode_partial is not None:
            raise ValueError('UI full EF state is required')
        if run.other_mode[0] >> 24 != 0xEF or run.runtime_render_state_offset is not None:
            raise ValueError('UI inherited render-state call is unsupported')
        if run.pixel and run.pixel.segment is not None:
            if (run.pixel.offset != 0 or run.palette is None
                    or run.palette.segment != run.pixel.segment or run.palette.offset != 2048):
                raise ValueError('UI inline palette pairing changed')
        mapped.append(replace(run, other_mode=(run.other_mode[0] & 0xFFFEFFFF, 0x005041C8),
            combine_mode=COMBINE, pixel=binding(run.pixel), palette=binding(run.palette),
            texture_loads=tuple((binding(value), tile) for value, tile in run.texture_loads)))
    proof = {'kind': 'rom-ui-constructor-first-draw', 'constructor': 'func_151ED90C',
             'renderer': 'func_151EDBDC', 'model_sha1': MODELS[entry][1],
             'other_mode_word0_and': '0xFFFEFFFF', 'other_mode_word1': '0x005041C8',
             'removed_model_command': 'FC',
             'renderer_combine_mode': [f'0x{word:08X}' for word in COMBINE],
             'source_faces': faces, 'source_runs': runs, 'scope': SCOPE}
    if entry == 164:
        proof['texture_binding'] = {'pixel_segments': [6, 7], 'palette_offset': 2048,
            'selected_flat': first_draw_flat(), 'constructor_counter': 1,
            'first_draw_reload_range': [15, 142],
            'later_blink_flat': 1287, 'selector': '(counter-1)&255; zero reloads (rng&127)+15; <7 selects1287, otherwise1288',
            'payloads': [{'flat': flat, 'bytes': n, 'sha1': h} for flat, (n, h) in PAYLOADS.items()]}
    return replace(geometry, material_runs=tuple(mapped)), proof
