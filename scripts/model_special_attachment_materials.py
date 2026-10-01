"""New ROM-derived texture presets for specialized bank09 consumers 165/185.

Stored geometry, UVs and neutral joints are retained. This is an explicit source
consumer preset, not current gameplay phase, runtime deformation or raster parity.
"""
from dataclasses import asdict, replace
import hashlib
import struct

CONSUMERS = (
    (0x150FAE18, 880, 'f1d0b07180ae21e324293f911e9358d0039e3145'),
    (0x150FB1E8, 88, '4e94b65e23281c6ca6c87b9504ad5ea682fd7aa2'),
    (0x151D6BFC, 612, '34b5db66b4e644e1e8d204ee5ee137de0007d8c3'),
    (0x151D710C, 164, 'e15b7253fcc1d86f8fb47c8ebc10cfb35e7f7557'),
    (0x15157010, 436, '7513f331bff62bd4b58cec4ffd7cc5f4888ae40d'),
    (0x15157420, 1088, 'e2c01ccf96e364cf5c2c04cf7c82216b4536ed9a'),
    (0x151462C8, 496, '6dcfdd4d04697403fe2e944a1f79edaf5bea4bc4'),
    (0x15157F80, 104, '0dc643a3c9ae4d868402d41b64cf81bdfa78cc1e'),
    (0x15133EEC, 236, '022514849c4aa339cf0d13c9b00324f7681f7140'),
    (0x1509093C, 2232, '7f181f001e790262a58c7cc718fe9f4352ef2bd9'),
    (0x150911F4, 832, '80b64b061f9d7b4f36d648cbd47b73aa424000de'),
    (0x1503F62C, 396, 'b678946246dbc937322777d197d874c3dbd0839b'),
    (0x1502FE10, 456, '8637778facf0ce5e9a4cd03316b390e02fdf84e2'),
    (0x1510CE60, 652, '9a12376e197e0ae05d6d351d5d538865aa7dcc68'),
    (0x1510D0EC, 648, '47b67aab9ed8a4eb1706ced5424981ff21373aba'),
)
DATA = (
    (0x8008ADC0, '151d710c150fb1e8'),
    (0x80091484, '80090b300100001000100002'),
    (0x80090B30, '00000508'),
    (0x80090258, '00000791000007930000079a000007960000079700000e4100000e4900000cb2'),
    (0x8008BFA8, '15157420000000008008ad6000000000'),
    (0x80083A80, 'ef18acaf0c1841c8df00000000000000'),
    (0x80083C00, 'ef18acaf0c192048df00000000000000'),
    (0x80083780, 'ef18acaf0c1849d8df00000000000000'),
    (0x80083900, 'ef18acaf0c192078df00000000000000'),
    (0x80083490, 'ef18ac3f04d041c8df00000000000000'),
    (0x800834B0, 'ef18ac3f04d041c8df00000000000000'),
    (0x80083610, 'ef18ac3f04d13048df00000000000000'),
    (0x80083630, 'ef18ac3f04d12248df00000000000000'),
)
PAYLOADS = {1288: (2560, '5f4fbbce8a5e13ef37e05a1fb2421c05e08646c8'), 1937: (2560, 'a5d574cfd65023524334e7ee4e1f2870189ec3bc'), 1942: (2560, 'bbe59fd62a52367e51564610b6870377ff92b112'), 1946: (2560, '939d6a2117ffa9846e698c45cdf03cfc2b77be1b'), 3649: (1536, '07ed34cc49371c5e287ebe56b43746758383a2cd'), 3657: (1536, 'f59ba579859fed1a9025a7ff66840a1764cb8450')}
MODELS = {165: {'bytes': 3320, 'sha1': '8bcdaa72c1639c141d4717222b8703a3dc41ae5c', 'faces': 65, 'vertices': 89, 'joints': 9, 'runs': 8}, 185: {'bytes': 5768, 'sha1': '67baa7d6bb38261e4bce23dc28ec1cf73bf3d7fa', 'faces': 170, 'vertices': 232, 'joints': 0, 'runs': 9}}
RUNS = {165: ((5, 32, 15, 7, 2048, (64, 32, 2, 1)), (6, 47, 14, 6, 2048, (64, 32, 2, 1))), 185: ((5, 154, 4, 11, 1024, (32, 32, 2, 1)), (6, 158, 4, 10, 1024, (32, 32, 2, 1)), (7, 162, 4, 6, 2048, (32, 64, 2, 1)), (8, 166, 4, 7, 2048, (32, 64, 2, 1)))}
PHASES = {165: ({6: 1288, 7: 1288},),
          185: ({6: 1937, 7: 1937, 10: 3649, 11: 3649},
                {6: 1937, 7: 1937, 10: 3657, 11: 3657},
                {6: 1942, 7: 1942, 10: 3657, 11: 3657},
                {6: 1946, 7: 1946, 10: 3657, 11: 3657})}
SCOPE = ('Explicit first source-consumer texture phase, stored vertices, source UVs '
         'and neutral joints. Gameplay activation, current phase, later object '
         'updates, HUD deformation, visibility, colours, opacity and native raster '
         'appearance are unresolved. Entry185 external run0 remains unresolved.')


def checked(blob, base, address, size):
    offset = address - base
    if offset < 0 or size < 0 or offset + size > len(blob):
        raise ValueError('special attachment evidence span outside input')
    return blob[offset:offset + size]


def phase_for_counter(counter):
    """Controller1509093C branch selection; activation is a separate condition."""
    if type(counter) is not int or not 0 <= counter <= 65535:
        raise ValueError('special attachment counter must be an unsigned halfword')
    return 0 if counter < 480 else 1 if counter < 960 else 2 if counter < 1200 else 3


def model_context(entry):
    return {'bank': 9, 'entry': entry, 'segment': 0,
            'renderer': 'func_15157420' if entry == 165 else 'func_150911F4',
            'special_attachment_material_state': 'first-source-phase',
            'selected_phase': 0, 'scope': SCOPE}


def material_context(code, code_base, data, data_base):
    for address, size, expected in CONSUMERS:
        if hashlib.sha1(checked(code, code_base, address, size)).hexdigest() != expected:
            raise ValueError(f'special attachment consumer changed: {address:08X}')
    for address, text in DATA:
        expected = bytes.fromhex(text)
        if checked(data, data_base, address, len(expected)) != expected:
            raise ValueError(f'special attachment dispatch/descriptor/texture table changed: {address:08X}')
    return {'consumers': [{'function': f'func_{a:08X}', 'size': n, 'sha1': h}
                          for a, n, h in CONSUMERS],
            'models': [model_context(e) for e in sorted(MODELS)], 'capture_inputs': []}


def apply_preview_geometry(geometry, model_bytes, context, payloads, runtime_materials=None):
    """Resolve only the pinned six runs; no geometry or inherited-state edits."""
    if not context or 'special_attachment_material_state' not in context:
        return geometry, None
    # Captured materials carry their own image/state. Keep the model's source
    # binding references intact whenever such material evidence is supplied.
    if runtime_materials:
        return geometry, None
    entry = context.get('entry')
    if (type(entry) is not int or entry not in MODELS
            or any(type(context.get(k)) is not int for k in ("bank", "segment", "selected_phase"))
            or context != model_context(entry)):
        raise ValueError('special attachment context identity or phase changed')
    spec = MODELS[entry]
    if len(model_bytes) != spec['bytes'] or hashlib.sha1(model_bytes).hexdigest() != spec['sha1']:
        raise ValueError('special attachment source model changed')
    try:
        from scripts import model_assets as models
    except ModuleNotFoundError:
        import model_assets as models
    parsed, native = models.parse_attachment_model(model_bytes, models.parse_model_geometry)
    if (asdict(geometry) != asdict(parsed) or len(geometry.faces) != spec['faces']
            or len(geometry.vertices) != spec['vertices']
            or len(geometry.material_runs) != spec['runs'] or len(native['joints']) != spec['joints']):
        raise ValueError('special attachment parsed geometry changed')
    phases = PHASES[entry]
    for flat in {f for phase in phases for f in phase.values()}:
        size, expected = PAYLOADS[flat]
        raw = payloads.get(flat)
        if raw is None or len(raw) != size or hashlib.sha1(raw).hexdigest() != expected:
            raise ValueError(f'special attachment payload changed: {flat}')
    adjusted = list(geometry.material_runs)
    variants = [{'phase': index, 'bindings': dict(phase), 'runs': []}
                for index, phase in enumerate(phases)]
    for index, first, count, segment, palette_offset, layout in RUNS[entry]:
        run = geometry.material_runs[index]
        if (run.first_face != first or run.face_count != count
                or not run.texture_enabled or not run.texture_coordinates_proven
                or run.pixel is None or run.palette is None
                or run.pixel.external or run.palette.external
                or (run.pixel.flat_index, run.pixel.segment, run.pixel.offset) != (None, segment, 0)
                or (run.palette.flat_index, run.palette.segment, run.palette.offset) != (None, segment, palette_offset)):
            raise ValueError('special attachment run source binding changed')
        for phase_index, phase in enumerate(phases):
            flat = phase[segment]
            def mapped_binding(value):
                if value is None or value.segment not in phase:
                    return value
                binding_flat = phase[value.segment]
                binding_palette_offset = PAYLOADS[binding_flat][0] - 512
                if (value.external or value.flat_index is not None
                        or value.offset not in (0, binding_palette_offset)):
                    raise ValueError('special attachment texture load binding changed')
                return replace(value, flat_index=binding_flat, mode=0 if value.offset == 0 else 1,
                               segment=None, offset=None)
            mapped = replace(run, pixel=mapped_binding(run.pixel), palette=mapped_binding(run.palette),
                             texture_loads=tuple((mapped_binding(value), tile) for value, tile in run.texture_loads))
            texture, status = models.choose_preview_texture(mapped, {}, payloads)
            if (texture is None or (texture.width, texture.height, texture.format, texture.size) != layout
                    or texture.palette_byte_offset != palette_offset):
                raise ValueError('special attachment source texture cannot be decoded')
            variants[phase_index]['runs'].append({'run': index, 'faces': count, 'flat': flat,
                'png_sha1': texture.sha1, 'layout': list(layout), 'texture_status': status})
            if phase_index == 0:
                adjusted[index] = mapped
    proof = {'kind': 'rom-special-attachment-first-source-phase', 'entry': entry,
             'source_model_sha1': spec['sha1'], 'renderer': context['renderer'],
             'selected_phase': 0, 'source_faces': spec['faces'],
             'affected_faces': sum(r[2] for r in RUNS[entry]),
             'affected_runs': [r[0] for r in RUNS[entry]], 'correlated_variants': variants,
             'scope': SCOPE}
    proof["inherited_tlut"] = {"format": "rgba16",
        "checked_state_addresses": [f"0x{a:08X}" for a, _ in (DATA[5:9] if entry == 165 else DATA[9:])],
        "scope": "Both specialized renderer alpha arms agree on RGBA16 TLUT; blend/pass/opacity are not selected."}
    if entry == 165:
        proof['consumer'] = {'constructors': ['func_150FAE18', 'func_151D6BFC'],
            'descriptor_constructor': 'func_15157010', 'callback': 'func_151D710C',
            'selector': 195, 'descriptor_address': '0x80091484', 'flat_pointer': '0x80090B30',
            'helper': 'func_15133EEC', 'inline_palette_offset': 2048,
            'policy': 'Initial constructor states; auxiliary texture arrays are zero. Descriptor image dimensions do not replace the model tile dimensions.'}
    else:
        proof['consumer'] = {'controller': 'func_1509093C', 'state_address': '0x800D24C8',
            'selector_halfword': '0x800CC2D0+0xB2 (unsigned); gated by byte+0xAD',
            'phase_thresholds': [480, 960, 1200], 'state_texture_fields': {'6': 'B0', '7': 'B2', '10': 'B4', '11': 'B6'},
            'policy': 'First controller texture phase; later phases are correlated evidence only. Native controller also deforms vertices; this export retains stored geometry.'}
    return replace(geometry, material_runs=tuple(adjusted)), proof
