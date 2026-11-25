"""Native L-command fields; the two unconsumed header bytes stay opaque."""
FORMAT = 'conker-mp3-l-command-fields-v1'


def encode(record):
    if (type(record) is not dict or set(record) != {'format', 'action', 'duration_numerator'}
            or record['format'] != FORMAT or type(record['action']) is not int
            or not 0 <= record['action'] <= 254
            or type(record['duration_numerator']) is not int
            or not 0 <= record['duration_numerator'] < 1 << 28):
        raise ValueError('invalid native MP3 L-command fields')
    duration = record['duration_numerator']
    encoded = bytes(0x80 | ((duration >> shift) & 0x7F) for shift in (21, 14, 7, 0))
    return [(0, b'L'), (3, bytes([record['action'] + 1]) + encoded + b'\0')]


def decode(data):
    if (len(data) != 9 or data[0] != ord('L') or data[-1] != 0
            or not all(data[1:8]) or not all(byte & 0x80 for byte in data[4:8])):
        raise ValueError('unsupported native MP3 L-command encoding')
    duration = 0
    for byte in data[4:8]:
        duration = (duration << 7) | (byte & 0x7F)
    record = {'format': FORMAT, 'action': data[3] - 1, 'duration_numerator': duration}
    for offset, payload in encode(record):
        if data[offset:offset + len(payload)] != payload:
            raise ValueError('L-command does not reconstruct consumed fields')
    return record
