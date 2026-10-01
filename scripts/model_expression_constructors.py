"""Reviewed US expression action records decoded as attachment constructors.

This is newly derived metadata, not execution of a constructor or proof of
runtime activation, an attachment pose, material state, or gameplay lifetime.
"""
from __future__ import annotations

import hashlib
import struct

# These whole ROM functions cover expression lookup/application, the runtime
# representation gate, action dispatch, descriptor construction and both loaders.
CONSUMERS = (
    (0x1507E908, 96, 'c602e20a2b335d94feb349539cbdb76d69957d50'),
    (0x1507E5C8, 240, '77b08fc8d2ec99c73d27527f43df6c9952d0c5fa'),
    (0x1507EA44, 120, 'c4818df6a7fca422de2d463163d68866d05b090f'),
    (0x1507E9F8, 76, '31fcadb16432eb6925dc6fcf17d561857102493d'),
    (0x150849A0, 44, '62d89a7ec36b39096dfd2c98896619b96b71866a'),
    (0x15083568, 356, '419012702249e321c26fc2badb49949b0aafa0fc'),
    (0x15030AF4, 608, 'f506f08cf457bc3d9bb7a751c0c1381e2ddd39a9'),
    (0x1502FFD8, 384, 'd03a13f16beb1aacae4a2c964a393164e8a477c4'),
    (0x1502FE10, 456, '8637778facf0ce5e9a4cd03316b390e02fdf84e2'),
    (0x1503F62C, 396, 'b678946246dbc937322777d197d874c3dbd0839b'),
    (0x15031A50, 452, '433d396431907cf2bdef8fc872dbcd46dd31d274'),
)
SELECTOR_TABLE = 0x8009D910
SOURCE_SPANS = (
    (SELECTOR_TABLE, 5, '09a64860b417d420abef7af1563888482654f4c3'),
    (0x8009B8A0, 4, 'a804515bf84a32bcf9938e570378d2de94fbf17c'),
    # Model 132's initializer switch selects the no-op return; 15/16/18
    # reach that return through direct comparisons in the pinned function.
    (0x80096F48, 4, '40bbd076b4d2be044326eff75c0fcc2d4d19c60b'),
    (0x80086CE4, 8, 'b09fcedd7cdfe2648cb263c9db44f14233d633e4'),
    (0x80086CEC, 8, '8340f79aa134b37ad368fa21cbced3f5248bfb9f'),
    (0x80086CF4, 8, '33e099df03c62d0309211c388a2e08b826fe9496'),
    (0x80086D0C, 8, 'e4cd53d6006c2a83f3c388c6525458859348e319'),
    (0x80086D14, 8, '023ff62b93121253ffbb0acf447c9caa9447c3b1'),
    (0x8009CE50, 16, 'a511252a95c755f9ed1b729841b757bcc7c89a43'),
    (0x8009CE60, 16, '45f44d1459a55a5d1d87b7a9faacc3b12b8808d4'),
    (0x8009CE70, 16, 'b6f93bb76d9f8e700eb4bb4a160b288b02a2d1c9'),
    (0x8009CEB0, 16, '9bb7d883854e1effa8d8ac8337ce7b6228f3400e'),
    (0x8009CED0, 32, '011da636f684783488bb76ed7a7ce9b819538cd7'),
)
SCOPE = ('ROM expression attachment-constructor metadata. No constructor is executed; '
         'source geometry, UVs, rig and animations are not edited. Runtime activation, '
         'allocation success, animation playback, attachment placement, material state '
         'and visibility remain unresolved.')


def _span(blob, base, address, size):
    offset = address - base
    if offset < 0 or size < 0 or offset + size > len(blob):
        raise ValueError('expression constructor evidence exceeds its source buffer')
    return blob[offset:offset + size]


def _verify(blob, base, spans, label):
    for address, size, digest in spans:
        if hashlib.sha1(_span(blob, base, address, size)).hexdigest() != digest:
            raise ValueError(f'expression constructor {label} changed at 0x{address:08X}')


def _decode_record(raw, action, index, address):
    """Decode the reviewed dispatch ABI; admission is the pinned caller's job."""
    if len(raw) != 16 or raw[3] not in (1, 2):
        raise ValueError('expression action is not a reviewed attachment constructor')
    kind = raw[3]
    animation_selector = raw[6] if kind == 2 else -1
    # +0x17 is a signed byte at its loader consumer (1502FFF8). A future
    # high-bit record would require reviewing the signed selection separately.
    if kind == 2 and animation_selector > 127:
        raise ValueError('expression attachment animation selector is outside the reviewed range')
    return {
        'index': index, 'record_address': f'0x{address:08X}',
        'record_sha1': hashlib.sha1(raw).hexdigest(),
        'dispatch_kind': kind, 'operation': 'attachment-constructor',
        'constructor': 'func_15030AF4', 'bank': 9, 'entry': raw[0],
        'model_source': 'record byte +0x00 via constructor a1 and descriptor +0x01',
        'updater_selector': raw[2],
        'attachment_animation_selector': animation_selector,
        'loader': 'func_1503F62C' if kind == 2 else 'func_1502FE10',
        'descriptor_initial_fields': {
            # Record-to-descriptor writes in 15030AF4, before loaders/initializer.
            'u8_0x01': raw[0], 'u8_0x02': raw[1], 'u8_0x04': raw[7],
            'u8_0x06': action, 'u8_0x07': raw[2],
            'u16_0x0A': struct.unpack_from('>H', raw, 8)[0],
            'u16_0x0C': struct.unpack_from('>H', raw, 10)[0],
            'u16_0x0E': struct.unpack_from('>H', raw, 12)[0],
            'u8_0x15': raw[4], 'u8_0x16': raw[5],
            's8_0x17': animation_selector, 'u16_0x18': 0, 'u16_0x1A': 0,
            # Expression caller supplies a3=0; constructor converts it to FFFF.
            'u16_0x1C': 0xFFFF, 'u16_0x1E': raw[14], 'u16_0x20': raw[15],
        },
        'expression_action_parameter_usage': 'ignored-by-attachment-constructor-branch',
        'record_offsets_ignored_by_dispatch': [6] if kind == 1 else [],
        'initializer': 'func_15031A50 no-op for this model',
        'creation_conditions': {
            'parent_u8_0x3B': 'nonzero owner ID',
            'duplicate_policy': 'skip if same owner ID, action ID and model already exist',
            'duplicate_bypass_flag': bool(raw[7] & 8),
            'allocation_and_model_loading': 'must succeed',
        },
    }


def parse_expression_constructor_programs(code, code_base, data, data_base):
    """Read only the exact US expression selector/header/record source identities.

    Parent modification (dispatch kind zero) uses a different ABI and is never
    admitted here as a bank-09 model. Every byte of each header and record,
    including reserved fields and ignored bytes, participates in source guards.
    """
    _verify(code, code_base, CONSUMERS, 'consumer')
    _verify(data, data_base, SOURCE_SPANS, 'source')
    actions = _span(data, data_base, SELECTOR_TABLE, 5)
    programs = []
    for selector, action in enumerate(actions, 1):
        header_address = 0x80086CC4 + (action - 1) * 8
        header = _span(data, data_base, header_address, 8)
        pointer, count = struct.unpack('>IB3x', header)
        raw = _span(data, data_base, pointer, count * 16)
        operations = [_decode_record(raw[i * 16:(i + 1) * 16], action, i, pointer + i * 16)
                      for i in range(count)]
        programs.append({
            'selector': selector, 'native_action': action,
            'table_address': f'0x{header_address:08X}',
            'table_sha1': hashlib.sha1(header).hexdigest(),
            'program_address': f'0x{pointer:08X}', 'record_count': count,
            'decoded_size': len(raw), 'sha1': hashlib.sha1(raw).hexdigest(),
            'operations': operations,
            'execution_policy': 'attempt every record in order; no rollback on a skipped or failed request',
            'return_value_policy': 'result of the last record, not a summary of created attachments',
        })
    return {
        'family': 'ROM-expression-attachment-constructors', 'schema_version': 1,
        'programs': programs,
        'operation_count': sum(len(p['operations']) for p in programs),
        'attachment_entries': sorted({r['entry'] for p in programs for r in p['operations']}),
        'consumer_sha1': {f'0x{a:08X}': d for a, _, d in CONSUMERS},
        'source_sha1': {f'0x{a:08X}': d for a, _, d in SOURCE_SPANS},
        'action_parameter': {
            'expression_offset': 6, 'source_type': 'u16-big-endian',
            'scale_address': '0x8009B8A0',
            'scale_f32': struct.unpack('>f', _span(data, data_base, 0x8009B8A0, 4))[0],
            'dispatcher_usage': 'kind zero parent-modification branch only',
            'attachment_constructor_usage': 'ignored',
        },
        'runtime_gate': ('func_1507E9F8 exposes the table only when func_150849A0 '
                         'returns zero for the current actor representation'),
        'scope': SCOPE, 'capture_inputs': [],
    }
