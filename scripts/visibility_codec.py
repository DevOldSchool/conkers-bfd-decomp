"""Native 256-symbol visibility Huffman codebooks from explicit bitstrings."""
from __future__ import annotations
import struct

FORMAT = 'conker-visibility-codebook-v1'


def encode_codebook(record):
    if not isinstance(record, dict) or set(record) != {'format', 'codes'} or record['format'] != FORMAT:
        raise ValueError('unsupported visibility codebook schema')
    codes = record['codes']
    if not isinstance(codes, list) or len(codes) != 256:
        raise ValueError('visibility codebook requires 256 byte-symbol slots')
    prefixes, leaves, pairs = {''}, set(), []
    for bits in codes:
        if bits is None:
            pairs.append((0, 0))
            continue
        if not isinstance(bits, str) or not 1 <= len(bits) <= 32 or set(bits) - {'0', '1'}:
            raise ValueError('visibility code must be a bounded binary string')
        if bits in leaves:
            raise ValueError('duplicate visibility code')
        leaves.add(bits)
        prefixes.update(bits[:end] for end in range(1, len(bits) + 1))
        pairs.append((int(bits, 2), len(bits)))
    if not leaves or any(bits[:end] in leaves for bits in leaves for end in range(1, len(bits))):
        raise ValueError('visibility codes are empty or not prefix-free')
    # Native nodes hold a signed symbol and two signed byte offsets.
    allocation = len(prefixes) * 6
    if allocation > 32767:
        raise ValueError('visibility tree exceeds native signed offsets')
    return struct.pack('>I', allocation) + b''.join(struct.pack('>II', *pair) for pair in pairs) + bytes(4)


def decode_codebook(data):
    if len(data) != 2056:
        raise ValueError('visibility codebook has an unsupported extent')
    codes = []
    for code, length in struct.iter_unpack('>II', data[4:2052]):
        if not length:
            if code:
                raise ValueError('absent visibility symbol has a nonzero code')
            codes.append(None)
        else:
            if length > 32 or code >= 1 << length:
                raise ValueError('visibility code exceeds its declared bit length')
            codes.append(f'{code:0{length}b}')
    record = {'format': FORMAT, 'codes': codes}
    if encode_codebook(record) != data:
        raise ValueError('visibility tree allocation or alignment is unexplained')
    return record


BITMAP_FORMAT = 'conker-visibility-node-sets-v1'


def bitmap_dimensions(node_count):
    if type(node_count) is not int or not 1 <= node_count <= 21845 or node_count % 4 != 1:
        raise ValueError('visibility node count is outside a native full quadtree')
    return (node_count * 3 + 1) // 4, ((node_count + 7) // 8 + 15) & ~15


def encode_bitmap(record, codebook):
    """Generate LSB node flags, then MSB Huffman codes and zero 64-bit alignment."""
    if (not isinstance(record, dict) or set(record) != {'format', 'node_count', 'visible_nodes'}
            or record['format'] != BITMAP_FORMAT):
        raise ValueError('unsupported visibility bitmap schema')
    row_count, stride = bitmap_dimensions(record['node_count'])
    rows = record['visible_nodes']
    if not isinstance(rows, list) or len(rows) != row_count:
        raise ValueError('visibility rows differ from quadtree leaves')
    encode_codebook(codebook)
    codes = codebook['codes']
    output, pending, width = bytearray(), 0, 0
    for visible in rows:
        if (not isinstance(visible, list)
                or any(type(n) is not int or not 0 <= n < record['node_count'] for n in visible)
                or visible != sorted(set(visible))):
            raise ValueError('visibility nodes must be sorted unique in-range indices')
        flags = bytearray(stride)
        for node in visible:
            flags[node // 8] |= 1 << (node % 8)
        for symbol in flags:
            bits = codes[symbol]
            if bits is None:
                raise ValueError('visibility byte has no Huffman symbol')
            pending = (pending << len(bits)) | int(bits, 2)
            width += len(bits)
            while width >= 8:
                width -= 8
                output.append((pending >> width) & 255)
            pending &= (1 << width) - 1
    if width:
        output.append(pending << (8 - width))
    output.extend(bytes((-len(output)) % 8))
    return bytes(output)


def decode_bitmap(data, node_count, codebook):
    row_count, stride = bitmap_dimensions(node_count)
    encode_codebook(codebook)
    symbols = {bits: symbol for symbol, bits in enumerate(codebook['codes']) if bits is not None}
    prefixes = {bits[:end] for bits in symbols for end in range(1, len(bits))}
    rows, bit = [], 0
    for _ in range(row_count):
        visible = []
        for byte in range(stride):
            prefix = ''
            while prefix not in symbols:
                if bit >= len(data) * 8:
                    raise ValueError('visibility Huffman stream is truncated')
                prefix += str((data[bit // 8] >> (7 - bit % 8)) & 1)
                bit += 1
                if prefix not in symbols and prefix not in prefixes:
                    raise ValueError('visibility Huffman stream has an absent branch')
            value = symbols[prefix]
            for shift in range(8):
                if value & (1 << shift):
                    node = byte * 8 + shift
                    if node >= node_count:
                        raise ValueError('visibility bitmap has unexplained unused node bits')
                    visible.append(node)
        rows.append(visible)
    record = {'format': BITMAP_FORMAT, 'node_count': node_count, 'visible_nodes': rows}
    if encode_bitmap(record, codebook) != data:
        raise ValueError('visibility Huffman stream has unexplained alignment or trailing bytes')
    return record
