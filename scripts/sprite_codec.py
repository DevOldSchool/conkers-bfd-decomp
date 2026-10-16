"""Lossless RGBA5551 and I4 sprite planes in native LoadBlock storage."""
from __future__ import annotations

try:
    from scripts import texture_build
except ModuleNotFoundError:
    import texture_build

FORMATS = ('rgba16', 'i4')


def dimensions(width, height):
    if (type(width) is not int or type(height) is not int or width not in (16, 32, 48, 64)
            or not 1 <= height <= 64 or width * height % 16 or width * height * 5 // 2 > 4096):
        raise ValueError('unsupported sprite dimensions or TMEM extent')
    return width * height * 5 // 2


def plane_layout(width, height, fmt):
    dimensions(width, height)
    if fmt == 'rgba16':
        return 0, width * height * 2, width * 2
    if fmt == 'i4':
        return width * height * 2, width * height // 2, width // 2
    raise ValueError('unsupported sprite plane')


def source_offsets(width, height, fmt):
    """Undo the native 16-bit LoadBlock and each render tile's odd-row swap.

    Both operations exchange the 32-bit halves of the same 64-bit word.
    I4 rows have a different stride from the combined RGBA16 upload.
    """
    offset, size, stride = plane_layout(width, height, fmt)
    dxt = (2048 + width // 4 - 1) // (width // 4)
    for byte in range(size):
        at = offset + byte
        upload_odd = ((at // 8 * dxt) >> 11) & 1
        sample_odd = (byte // stride) & 1
        source = at ^ (4 if upload_odd ^ sample_odd else 0)
        if not offset <= source < offset + size:
            raise ValueError('sprite sampling reaches outside its plane')
        yield source


def png_contract(width, height, fmt):
    plane_layout(width, height, fmt)
    return {'row_layout': 'linear', 'source_contract': {
        'format': fmt, 'width': width, 'height': height, 'source_origin': 'top-left'}}


def decode_frame(payload, width, height):
    """Produce editable PNGs whose rows follow increasing tile T coordinates."""
    if len(payload) != dimensions(width, height):
        raise ValueError('sprite frame has an unexpected byte extent')
    return {fmt: texture_build.source_png(bytes(payload[i] for i in source_offsets(width, height, fmt)),
                                         png_contract(width, height, fmt)) for fmt in FORMATS}


def encode_frame(images, width, height):
    if not isinstance(images, dict) or set(images) != set(FORMATS):
        raise ValueError('sprite frame requires exactly RGBA16 and I4 PNG planes')
    result = bytearray(dimensions(width, height))
    for fmt in FORMATS:
        plane = texture_build.source_png(images[fmt], png_contract(width, height, fmt), decode=True)
        for value, at in zip(plane, source_offsets(width, height, fmt), strict=True):
            result[at] = value
    return bytes(result)
