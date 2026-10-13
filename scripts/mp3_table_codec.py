"""Generate Conker's MP3 Huffman nodes and fast lookup tables from C seed codes."""
from __future__ import annotations

import hashlib
import re
import struct

FORMAT = 'conker-mp3-huffman-seeds-v1'
CONSUMERS = (
    (0x1F2960, 5248, '4ca3738ba6dcfaf74dd5cab929a36f3f87c67f1d', 'playback'),
    (0x1F3DE0, 16768, '0f8348f8d83fe1d945cd01ed1a7dee90709cc608', 'decoder'),
    (0x1F7F60, 2320, '5c73afefeda51d0af7c8796ee6617fe71f51f706', 'frame reader'),
    (0x1F8870, 1152, '58a30e95a62dac87c8260191c4ebcbbe75ba340b', 'Huffman traversal'),
)


def verify_consumers(game_code):
    for start, size, digest, name in CONSUMERS:
        if hashlib.sha1(game_code[start:start + size]).hexdigest() != digest:
            raise ValueError(f'MP3 {name} consumer differs from reviewed US instructions')


def seed_records(source):
    """Read only literal seed definitions, including their explicit terminators."""
    books = {}
    pattern = r'const struct mp3decthing (\w+)\[\] = \{(.*?)\};'
    row = r'\{\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*\}\s*,?'
    for name, body in re.findall(pattern, source, re.S):
        rows = [list(map(int, values)) for values in re.findall(row, body)]
        if (name in books or re.sub(row, '', body).strip() or not rows
                or rows[-1] != [100, 100, 100, 0, 0] or any(r[3] for r in rows)):
            raise ValueError('unsupported MP3 C seed definition')
        books[name] = [[x, y, width, code] for x, y, width, _, code in rows[:-1]]
    maps = re.findall(r'struct mp3decthing \*var8005f670\[\] = \{(.*?)\};', source, re.S)
    if len(maps) != 1:
        raise ValueError('missing or duplicated MP3 C table map')
    pointers = []
    for item in maps[0].split(','):
        item = item.strip()
        if not item:
            continue
        match = re.fullmatch(r'\(struct mp3decthing \*\)(\w+)', item)
        if item == 'NULL':
            pointers.append(None)
        elif match:
            pointers.append(match[1])
        else:
            raise ValueError('unsupported MP3 C table pointer')
    records = {'format': FORMAT, 'codebooks': books, 'table_codebooks': pointers}
    encode_tables(records)
    return records


def encode_tree(rows):
    if not isinstance(rows, list) or not 2 <= len(rows) <= 256:
        raise ValueError('invalid Huffman seed count')
    codes = {}
    symbols = set()
    for row in rows:
        if (not isinstance(row, list) or len(row) != 4 or any(type(v) is not int for v in row)):
            raise ValueError('invalid Huffman seed record')
        x, y, width, code = row
        if not (0 <= x <= 15 and 0 <= y <= 15 and 1 <= width <= 32 and 0 <= code < 1 << width):
            raise ValueError('Huffman seed outside field bounds')
        bits = ''.join(str((code >> i) & 1) for i in range(width))
        if bits in codes or (x, y) in symbols:
            raise ValueError('duplicate Huffman code or symbol')
        codes[bits] = (x, y)
        symbols.add((x, y))
    if any(bits[:i] in codes for bits in codes for i in range(1, len(bits))):
        raise ValueError('Huffman code is a prefix of another code')
    nodes = [[0, 0, 255, 255]]
    prefixes = {'': 0}
    # Original allocation visits each depth, then the C seed rows in order.
    # Nodes therefore have breadth-first storage, with relative u8 child edges.
    for depth in range(1, max(map(len, codes)) + 1):
        for bits in codes:
            if len(bits) < depth:
                continue
            prefix = bits[:depth]
            if prefix not in prefixes:
                parent = prefixes[prefix[:-1]]
                index = len(nodes)
                delta = index - parent
                if delta > 255:
                    raise ValueError('Huffman relative child edge exceeds u8')
                prefixes[prefix] = index
                nodes[parent][int(prefix[-1])] = delta
                nodes.append([0, 0, *codes[prefix]] if prefix in codes else [0, 0, 255, 255])
    if any(node[2:] == [255, 255] and (not node[0] or not node[1]) for node in nodes):
        raise ValueError('incomplete Huffman branch')
    return b''.join(bytes(node) for node in nodes)


def encode_tables(records):
    if (not isinstance(records, dict) or set(records) != {'format', 'codebooks', 'table_codebooks'}
            or records['format'] != FORMAT):
        raise ValueError('invalid MP3 seed format')
    books, mapping = records['codebooks'], records['table_codebooks']
    if (not isinstance(books, dict) or len(books) != 17
            or any(not isinstance(name, str) or not re.fullmatch(r'var\w+', name) for name in books)
            or not isinstance(mapping, list) or len(mapping) != 34 or mapping[0] is not None
            or any(not isinstance(name, str) for name in mapping[1:])
            or set(mapping[1:]) != set(books)):
        raise ValueError('invalid MP3 codebook mapping')
    trees = {name: encode_tree(rows) for name, rows in books.items()}
    offsets = [0]
    nodes = bytearray()
    values, lengths = bytearray(34 * 256), bytearray(34 * 256)
    for table, name in enumerate(mapping[1:], 1):
        offsets.append(len(nodes))
        nodes.extend(trees[name])
        for x, y, width, code in books[name]:
            if width > 8:
                continue
            prefix = int(''.join(str((code >> i) & 1) for i in range(width)), 2)
            for suffix in range(1 << (8 - width)):
                index = table * 256 + (prefix << (8 - width)) + suffix
                values[index], lengths[index] = (y << 4) | x, width
    # The stored allocation contains one final initialized, unlinked empty node.
    # Preserve its typed fields; its runtime purpose is not established.
    nodes.extend(bytes((0, 0, 255, 255)))
    return {'mp3_huffman_offsets': struct.pack('>36I', *offsets, 0, 0),
            'mp3_lookup': bytes(values + lengths), 'mp3_huffman': bytes(nodes)}
