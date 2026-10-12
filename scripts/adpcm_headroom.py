"""Lossless pre-saturation PCM for native ADPCM frames with clipped signals."""
import math
import struct

try:
    from scripts import adpcm_codec
except ModuleNotFoundError:
    import adpcm_codec


def source_float_wav(samples, sample_rate):
    if type(sample_rate) is not int or not 0 < sample_rate <= 0x3FFFFFFF:
        raise ValueError('invalid float PCM sample rate')
    if any(type(v) is not int or not -(1 << 23) <= v < (1 << 23) for v in samples):
        raise ValueError('float PCM source must contain exactly representable integer signal samples')
    pcm = struct.pack(f'<{len(samples)}f', *(value / 32768 for value in samples))
    fmt = struct.pack('<HHIIHHH', 3, 1, sample_rate, sample_rate * 4, 4, 32, 0)
    chunks = b'fmt ' + struct.pack('<I', len(fmt)) + fmt
    chunks += b'fact' + struct.pack('<II', 4, len(samples))
    chunks += b'data' + struct.pack('<I', len(pcm)) + pcm
    return b'RIFF' + struct.pack('<I', 4 + len(chunks)) + b'WAVE' + chunks


def read_float_wav(data, sample_rate, frames):
    if (len(data) < 12 or data[:4] != b'RIFF' or data[8:12] != b'WAVE'
            or struct.unpack_from('<I', data, 4)[0] != len(data) - 8):
        raise ValueError('invalid float PCM RIFF extent')
    chunks = {}
    cursor = 12
    while cursor < len(data):
        if cursor + 8 > len(data):
            raise ValueError('truncated float PCM chunk header')
        name = data[cursor:cursor + 4]
        size = struct.unpack_from('<I', data, cursor + 4)[0]
        end = cursor + 8 + size
        if end + (size & 1) > len(data) or name in chunks:
            raise ValueError('truncated or duplicate float PCM chunk')
        chunks[name] = data[cursor + 8:end]
        cursor = end + (size & 1)
    fmt = chunks.get(b'fmt ', b'')
    if (len(fmt) not in (16, 18)
            or struct.unpack('<HHIIHH', fmt[:16]) != (3, 1, sample_rate, sample_rate * 4, 4, 32)
            or len(fmt) == 18 and fmt[16:] != b'\0\0'):
        raise ValueError('float PCM WAV must be mono IEEE float32 at the native rate')
    if b'fact' in chunks and chunks[b'fact'] != struct.pack('<I', frames):
        raise ValueError('float PCM fact sample count changed')
    pcm = chunks.get(b'data', b'')
    if len(pcm) != frames * 4:
        raise ValueError('float PCM sample count changed')
    values = struct.unpack(f'<{frames}f', pcm)
    samples = []
    for value in values:
        scaled = value * 32768
        if not math.isfinite(scaled) or not -(1 << 23) <= scaled < (1 << 23) or scaled != int(scaled):
            raise ValueError('float PCM value is not an exact supported signal sample')
        samples.append(int(scaled))
    return samples


def decode_headroom(raw,coefficients,order,predictors):
    adpcm_codec.frame_plan(raw, coefficients, order, predictors)
    history=[0]*order;output=[]
    for start in range(0,len(raw),9):
        frame=raw[start:start+9];scale=1<<(frame[0]>>4);base=(frame[0]&15)*order*8
        residuals=[(n-16 if n&8 else n)*scale for byte in frame[1:] for n in (byte>>4,byte&15)]
        for vector_start in (0,8):
            vector=residuals[vector_start:vector_start+8];values=[]
            for i,r in enumerate(vector):
                accumulator=sum(coefficients[base+j*8+i]*history[j] for j in range(order))
                for j in range(i):
                    accumulator+=vector[j]*sum(coefficients[base+k*8+i-1-j] for k in range(1,order))
                values.append((r*2048+accumulator)>>11)
            output.extend(values);history=[max(-32768,min(32767,v)) for v in values[-order:]]
    return output

def encode_headroom(samples,plan):
    adpcm_codec.validate_plan(plan)
    if (not isinstance(samples,(list,tuple)) or len(samples)!=16*len(plan['frames'])
            or any(type(v) is not int or not -(1<<23)<=v<(1<<23) for v in samples)):
        raise ValueError('headroom PCM must contain complete exactly representable integer frames')
    coefficients=plan['coefficients'];order=plan['order'];history=[0]*order;output=bytearray()
    for number,(exponent,predictor) in enumerate(plan['frames']):
        scale=1<<exponent;base=predictor*order*8;residuals=[]
        for vector in range(2):
            values=samples[number*16+vector*8:number*16+vector*8+8];prior=[]
            for i,value in enumerate(values):
                accumulator=sum(coefficients[base+j*8+i]*history[j] for j in range(order))
                accumulator+=scale*sum(r*sum(coefficients[base+k*8+i-1-j] for k in range(1,order)) for j,r in enumerate(prior))
                delta=value-(accumulator>>11)
                if delta%scale or not -8<=delta//scale<=7:raise ValueError('no exact headroom residual')
                prior.append(delta//scale)
            residuals.extend(prior);history=[max(-32768,min(32767,v)) for v in values[-order:]]
        output.append((exponent<<4)|predictor)
        output.extend(((a&15)<<4)|(b&15) for a,b in zip(residuals[::2],residuals[1::2]))
    return bytes(output)
