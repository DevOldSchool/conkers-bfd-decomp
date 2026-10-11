"""Fresh N64 ADPCM residual encoding from PCM16 and native frame parameters."""
from __future__ import annotations

import io
import struct
import wave


def validate_plan(plan):
    if (not isinstance(plan, dict) or set(plan) != {'format', 'order', 'predictor_count', 'coefficients', 'frames'}
            or plan['format'] != 'conker-adpcm-pcm16-plan-v1'
            or type(plan['order']) is not int or plan['order'] != 2
            or type(plan['predictor_count']) is not int or plan['predictor_count'] not in (1, 4)
            or not isinstance(plan['coefficients'], list)
            or len(plan['coefficients']) != 8 * plan['order'] * plan['predictor_count']
            or any(type(value) is not int or not -32768 <= value <= 32767 for value in plan['coefficients'])
            or not isinstance(plan['frames'], list) or not plan['frames']):
        raise ValueError('invalid ADPCM encoding plan')
    for frame in plan['frames']:
        if (not isinstance(frame, list) or len(frame) != 2
                or any(type(value) is not int for value in frame)
                or not 0 <= frame[0] <= 15 or not 0 <= frame[1] < plan['predictor_count']):
            raise ValueError('invalid ADPCM scale or predictor')


def frame_plan(data, coefficients, order, predictor_count):
    if not data or len(data) % 9:
        raise ValueError('ADPCM payload must contain complete nine-byte frames')
    plan = {'format': 'conker-adpcm-pcm16-plan-v1', 'order': order,
            'predictor_count': predictor_count, 'coefficients': list(coefficients),
            'frames': [[header >> 4, header & 15] for header in data[::9]]}
    validate_plan(plan)
    return plan


def encode_vector(target, history, coefficients, base, order, scale):
    """Select the lexicographically first residual solution, without original residuals."""
    prediction = [sum(coefficients[base + j * 8 + i] * history[j] for j in range(order))
                  for i in range(8)]
    taps = [[sum(coefficients[base + k * 8 + i - 1 - j] for k in range(1, order))
             for j in range(i)] for i in range(8)]
    visited = 0

    def solve(previous):
        nonlocal visited
        visited += 1
        if visited > 1000000:
            raise ValueError('ADPCM residual search exceeded its supported bound')
        i = len(previous)
        if i == 8:
            return previous
        accumulator = prediction[i] + scale * sum(r * c for r, c in zip(previous, taps[i]))
        sample = target[i]
        if sample not in (-32768, 32767):
            difference = sample - (accumulator >> 11)
            candidates = (difference // scale,) if difference % scale == 0 else ()
        else:
            candidates = range(-8, 8)
        for residual in candidates:
            if (-8 <= residual <= 7
                    and max(-32768, min(32767, (residual * scale * 2048 + accumulator) >> 11)) == sample):
                result = solve(previous + [residual])
                if result is not None:
                    return result
        return None

    result = solve([])
    if result is None:
        raise ValueError('PCM has no residual solution for the selected ADPCM frame parameters')
    return result


def encode_pcm(samples, plan):
    validate_plan(plan)
    if (not isinstance(samples, (list, tuple)) or len(samples) != 16 * len(plan['frames'])
            or any(type(value) is not int or not -32768 <= value <= 32767 for value in samples)):
        raise ValueError('ADPCM source must be complete signed PCM16 frames')
    order = plan['order']
    history = [0] * order
    output = bytearray()
    for frame_index, (exponent, predictor) in enumerate(plan['frames']):
        scale = 1 << exponent
        base = predictor * order * 8
        residuals = []
        for vector in range(2):
            start = frame_index * 16 + vector * 8
            target = samples[start:start + 8]
            residuals.extend(encode_vector(target, history, plan['coefficients'], base, order, scale))
            history = list(target[-order:])
        output.append((exponent << 4) | predictor)
        output.extend(((a & 15) << 4) | (b & 15) for a, b in zip(residuals[::2], residuals[1::2]))
    return bytes(output)


def source_wav(samples, sample_rate):
    if type(sample_rate) is not int or sample_rate <= 0:
        raise ValueError('invalid ADPCM source sample rate')
    if any(type(value) is not int or not -32768 <= value <= 32767 for value in samples):
        raise ValueError('invalid signed PCM16 source')
    stream = io.BytesIO()
    with wave.open(stream, 'wb') as file:
        file.setnchannels(1)
        file.setsampwidth(2)
        file.setframerate(sample_rate)
        file.writeframes(struct.pack(f'<{len(samples)}h', *samples))
    return stream.getvalue()


def read_wav(data, sample_rate, frames):
    try:
        with wave.open(io.BytesIO(data), 'rb') as file:
            if (file.getnchannels() != 1 or file.getsampwidth() != 2
                    or file.getframerate() != sample_rate or file.getcomptype() != 'NONE'
                    or file.getnframes() != frames):
                raise ValueError('ADPCM source WAV format or frame count differs from its contract')
            pcm = file.readframes(frames)
        if len(pcm) != frames * 2:
            raise ValueError('ADPCM source WAV has a truncated PCM payload')
        return list(struct.unpack(f'<{frames}h', pcm))
    except (wave.Error, EOFError, struct.error) as error:
        raise ValueError('invalid ADPCM source WAV') from error
