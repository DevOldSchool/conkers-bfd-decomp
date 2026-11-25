"""Bounded ID3v1 text fields; bytes after a NUL terminator are not authored text.

Field layout: https://id3.org/ID3v1. Conker stores these source tags at the
runtime MPEG boundary, before additional uninterpreted stream storage.
"""
FORMAT = 'id3v1-text-prefixes-v1'
FIELDS = (('title', 3, 30), ('artist', 33, 30), ('album', 63, 30),
          ('year', 93, 4), ('comment', 97, 30))


def encode(record):
    if (type(record) is not dict or set(record) != {'format', 'fields', 'genre'}
            or record['format'] != FORMAT or type(record['fields']) is not dict
            or set(record['fields']) != {name for name, _, _ in FIELDS}
            or type(record['genre']) is not int or not 0 <= record['genre'] <= 255):
        raise ValueError('invalid ID3v1 text source')
    spans = [(0, b'TAG')]
    for name, offset, width in FIELDS:
        field = record['fields'][name]
        if (type(field) is not dict or set(field) != {'text', 'terminated'}
                or type(field['text']) is not str or type(field['terminated']) is not bool
                or any(not 32 <= ord(c) < 127 for c in field['text'])):
            raise ValueError('ID3v1 field must be printable text with an explicit terminator flag')
        data = field['text'].encode('ascii')
        if field['terminated']:
            if len(data) >= width:
                raise ValueError('ID3v1 terminator exceeds its field')
            data += b'\0'
        elif len(data) != width:
            raise ValueError('unterminated ID3v1 text must fill its field')
        spans.append((offset, data))
    spans.append((127, bytes([record['genre']])))
    return merge(spans)


def merge(spans):
    result = []
    for start, data in sorted(spans):
        if not data:
            raise ValueError('empty reconstructed metadata range')
        if result and start < result[-1][0] + len(result[-1][1]):
            raise ValueError('overlapping reconstructed metadata ranges')
        if result and start == result[-1][0] + len(result[-1][1]):
            at, previous = result[-1]; result[-1] = (at, previous + data)
        else:
            result.append((start, data))
    return result


def decode(data):
    if len(data) != 128 or data[:3] != b'TAG':
        raise ValueError('ID3v1 record must have its marker and 128-byte extent')
    record = {'format': FORMAT, 'fields': {}, 'genre': data[127]}
    for name, offset, width in FIELDS:
        field = data[offset:offset + width]
        at = field.find(b'\0')
        prefix = field if at < 0 else field[:at]
        try:
            text = prefix.decode('ascii')
        except UnicodeDecodeError as error:
            raise ValueError('unsupported ID3v1 text encoding') from error
        record['fields'][name] = {'text': text, 'terminated': at >= 0}
    for start, fresh in encode(record):
        if data[start:start + len(fresh)] != fresh:
            raise ValueError('ID3v1 text does not reproduce original fields')
    return record
