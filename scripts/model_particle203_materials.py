"""New ROM-derived initial particle-203 texture proof; no capture dependency.

This restores one missing material resolution, not a historical source file.
The emitter copies descriptor +0x5C/+0x5D=1 to object +0xEC/+0xED.
The type-16 renderer then establishes OtherMode and combiner before calling
bank-09 entry 203. Dynamic particle colour, alpha, transforms and timing are
outside this static texture proof.
"""
from __future__ import annotations

import hashlib
import json
import struct
from dataclasses import asdict, replace

CONSUMERS = (
    (0x15169C70, 1924, 'e3c9ee727af24871ee3f7817af01fab3ff743df9'),
    (0x15171200, 1024, '253afecfdc609e2919f21b35fd1e613ea48b5376'),
    (0x15168BE4, 104, 'be31373b6a9c7307ea80718753a2b53890ce905c'),
    (0x15167A68, 112, '0825b0b974ca67a92c0a6e7d8665230b02e2b181'),
    (0x15168A4C, 80, '41a70fd6b122eeb005b9c01d21f215c154765b9d'),
    (0x151674F8, 1392, '1a4cc2434666765a39feb16096d26a83d4b8fcc3'),
    (0x15168C4C, 488, 'cb5b00eb61cb935bbf619a63a48aace0943f5af6'),
    (0x1518C900, 260, '38d05a33437a0f688bda1b2cf2ac6299b9aede8e'),
    (0x1510CE60, 652, '9a12376e197e0ae05d6d351d5d538865aa7dcc68'),
    (0x15142FBC, 136, 'e271c17f3ef050f70c77607be39588cf00d0c810'),
)
# These semantic landmarks are checked separately from the full function pins.
GUARDS = (
    (0x1516A070, 0x24010003),
    (0x1516A074, 0x1441003B),
    (0x1516A0DC, 0x240500CB),
    (0x1516A0E8, 0x0D45C480),
    (0x1517122C, 0x00A08825),
    (0x151712A8, 0x24080001),
    (0x151712AC, 0x24090001),
    (0x151712DC, 0xA3B100D6),
    (0x151712E0, 0xA3A800D8),
    (0x151712E4, 0xA3A900D9),
    (0x15171314, 0x27B5007C),
    (0x15171374, 0x02202025),
    (0x15171384, 0x0D463240),
    (0x15171390, 0xAFA200BC),
    (0x151714D0, 0x02A02025),
    (0x151715B0, 0x0D45A2F9),
    (0x15168BFC, 0x24040010),
    (0x15168C20, 0x0D459E9A),
    (0x15168C30, 0x24450090),
    (0x15168C34, 0x0C008E84),
    (0x15168C38, 0x24060060),
    (0x15167AB0, 0x0D45A293),
    (0x15167AB4, 0x8FA50028),
    (0x15168A88, 0xA0850000),
    (0x15168D58, 0x922600EC),
    (0x15168D5C, 0x24010001),
    (0x15168D64, 0x10C10006),
    (0x15168D68, 0x3C050008),
    (0x15168D80, 0x3C0A0055),
    (0x15168D84, 0x354A2230),
    (0x15168D88, 0x10000003),
    (0x15168D8C, 0xAFAA0060),
    (0x15168D9C, 0x34A5ACA0),
    (0x15168DA0, 0x8FA60060),
    (0x15168DA4, 0x0D450BEF),
    (0x15168DAC, 0x922C00ED),
    (0x15168DB0, 0x24010001),
    (0x15168DB8, 0x15810008),
    (0x15168DC0, 0x3C0DFC12),
    (0x15168DC4, 0x3C0EFF73),
    (0x15168DC8, 0x35CEFFFF),
    (0x15168DCC, 0x35AD3824),
    (0x15168DD0, 0xAC4D0000),
    (0x15168DD4, 0xAC4E0004),
    (0x15168E08, 0x3C0BDE00),
    (0x15168E0C, 0xAC8B0000),
    (0x15168E10, 0x8E2C00D0),
    (0x15168E1C, 0xAC8C0004),
    (0x1518C934, 0x24180009),
    (0x1518C938, 0xAFB80010),
    (0x1518C94C, 0xAFAE0014),
    (0x1518C950, 0x0D40ADAF),
    (0x1518C978, 0x8E040000),
    (0x1518C99C, 0x0D443398),
    (0x1518C9A4, 0x8E040000),
    (0x1518C9A8, 0x0D45A395),
    (0x15142FCC, 0x34A8000F),
    (0x15143010, 0x01014824),
    (0x15143018, 0x3C01EF00),
    (0x1514301C, 0x01215025),
    (0x15143020, 0xAC4A0000),
    (0x15143024, 0xAC460004),
)
DISPATCH_ADDRESS = 0x8008B7E8
DISPATCH_WORDS = (0x15168BAC, 0, 0x15168C4C, 0, 0, 0, 0, 0, 0, 0x8008B498, 0, 0, 0)
MODEL_SHA256 = 'a54ec90e727542926329a9e15b43153d714d0902f9e79b081603e54bbf9f3b2d'
RUN_SHA256 = '9c1a7792abf7ef5fbe319808a69e8fa0694143969bc011e65b809745cda9f766'
PAYLOAD_SHA256 = 'c31c40010a97998f387019fd5b47a50d2daec1aeadbf8f9a6d29e3df2bb4b3f8'
COMBINE_MODE = (0xFC123824, 0xFF73FFFF)
OTHER_MODE = (0xEF08ACAF, 0x00552230)
SCOPE = ('Initial particle constructor path through func_15169C70 and func_15171200. '
         'ROM texture RGB only; texture alpha is one because the combiner uses '
         'PRIMITIVE times SHADE alpha. Dynamic colour, draw alpha, later state, '
         'transforms, timing and native raster parity remain unresolved.')


def _slice(data, base, address, size):
    offset = address - base
    if offset < 0 or size < 0 or offset + size > len(data):
        raise ValueError('particle203 ROM consumer span is missing')
    return data[offset:offset + size]


def run_digest(run):
    return hashlib.sha256(json.dumps(asdict(run), sort_keys=True,
                                    separators=(',', ':')).encode()).hexdigest()


def _state():
    return {
        'kind': 'particle203-initial-ci4',
        'model_sha256': MODEL_SHA256,
        'material_run_sha256': RUN_SHA256,
        'flat_index': 332, 'payload_bytes': 2080,
        'payload_sha256': PAYLOAD_SHA256,
        'other_mode': list(OTHER_MODE), 'combine_mode': list(COMBINE_MODE),
        'object_mode_offset': 0xEC, 'object_mode': 1,
        'object_combiner_offset': 0xED, 'object_combiner': 1,
    }


def material_context(code: bytes, code_base: int, data: bytes, data_base: int) -> dict:
    consumers = []
    for address, size, expected in CONSUMERS:
        actual = hashlib.sha1(_slice(code, code_base, address, size)).hexdigest()
        if actual != expected:
            raise ValueError(f'particle203 ROM consumer changed: 0x{address:08X}')
        consumers.append({'function': f'func_{address:08X}', 'size': size, 'sha1': actual})
    for address, expected in GUARDS:
        if struct.unpack('>I', _slice(code, code_base, address, 4))[0] != expected:
            raise ValueError(f'particle203 ROM instruction changed: 0x{address:08X}')
    dispatch = _slice(data, data_base, DISPATCH_ADDRESS, 52)
    if dispatch != struct.pack('>13I', *DISPATCH_WORDS):
        raise ValueError('particle203 type-16 render dispatch changed')
    return {
        'consumers': consumers,
        'models': [{
            'bank': 9, 'entry': 203, 'segment': 0,
            'renderer': 'func_15168C4C',
            'particle_texture_state': _state(),
            'constructors': [{
                'function': 'func_15169C70', 'entry_literal_pc': '0x1516A0DC',
                'call_pc': '0x1516A0E8', 'emitter': 'func_15171200',
                'load_call_pc': '0x15171384', 'loader': 'func_1518C900',
                'descriptor_stack_offset': 0x7C,
                'constructor': 'func_15168BE4', 'descriptor_copy_bytes': 0x60,
                'object_destination_offset': 0x90, 'object_type': 16,
                'dispatch_address': f'0x{DISPATCH_ADDRESS:08X}',
                'dispatch_sha256': hashlib.sha256(dispatch).hexdigest(),
                'mode_store_pc': '0x151712E0', 'combiner_store_pc': '0x151712E4',
                'other_mode_call_pc': '0x15168DA4',
                'combine_store_pc': '0x15168DD0', 'model_call_pc': '0x15168E0C',
            }],
            'scope': SCOPE,
        }],
        'capture_inputs': [],
    }


def preview_texture(run, payloads, context, model_data, bank, entry, segment):
    """Resolve exactly one authenticated run without changing source geometry."""
    if context is None or 'particle_texture_state' not in context:
        return None, 'rom-particle203-context-unresolved', None
    if (any(type(value) is not int for value in (bank, entry, segment))
            or (bank, entry, segment) != (9, 203, 0)
            or any(type(context.get(key)) is not int for key in ('bank', 'entry', 'segment'))
            or tuple(context.get(key) for key in ('bank', 'entry', 'segment')) != (9, 203, 0)):
        raise ValueError('particle203 preview identity changed')
    state = context['particle_texture_state']
    # JSON type-sensitive comparison also rejects True in place of selector 1.
    if (json.dumps(state, sort_keys=True) != json.dumps(_state(), sort_keys=True)
            or context.get('renderer') != 'func_15168C4C'):
        raise ValueError('particle203 preview context changed')
    if len(model_data) != 392 or hashlib.sha256(model_data).hexdigest() != MODEL_SHA256:
        raise ValueError('particle203 source model changed')
    if run_digest(run) != RUN_SHA256:
        raise ValueError('particle203 source material run changed')
    payload = payloads.get(332)
    if (not isinstance(payload, bytes) or len(payload) != 2080
            or hashlib.sha256(payload).hexdigest() != PAYLOAD_SHA256):
        raise ValueError('particle203 flat332 source payload changed')
    try:
        from scripts import model_assets as models
    except ModuleNotFoundError:
        import model_assets as models
    mapped = replace(run, combine_mode=COMBINE_MODE, other_mode=OTHER_MODE)
    original, status = models.direct_runtime_indexed_preview_texture(mapped, payload)
    if (original is None or status != 'runtime-composed-direct-ci4-texture'
            or (original.width, original.height, original.format, original.size,
                original.pixel_byte_offset, original.palette_byte_offset) != (64, 64, 2, 0, 0, 2048)):
        raise ValueError('particle203 CI4 source decode changed')
    # Only TLUT RGB participates in this combiner. Make a derived opaque
    # texture; retain the actual payload hash and unmodified decode hash below.
    opaque = bytearray(payload)
    for offset in range(2049, 2080, 2):
        opaque[offset] |= 1
    texture, status = models.direct_runtime_indexed_preview_texture(mapped, bytes(opaque))
    if texture is None or status != 'runtime-composed-direct-ci4-texture':
        raise ValueError('particle203 opaque texture decode failed')
    evidence = {
        'context': context,
        'source_model_sha256': MODEL_SHA256,
        'source_material_run_sha256': RUN_SHA256,
        'flat_index': 332, 'source_payload_bytes': len(payload),
        'source_payload_sha256': PAYLOAD_SHA256,
        'source_ci4_png_sha1': original.sha1,
        'texture_png_sha1': texture.sha1,
        'decoded_texel_count': texture.width * texture.height,
        'texture_alpha': 'one; source TLUT alpha is not sampled by this combiner',
        'scope': SCOPE,
    }
    return replace(texture, family='us-rom-particle203'), 'rom-particle203-ci4-rgb-texture', evidence
