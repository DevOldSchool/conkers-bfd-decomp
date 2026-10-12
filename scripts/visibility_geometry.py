"""Dimensions of scene visibility rows from the native mode-zero quadtree.

Only primary scene lists using segment-one, cache-start-zero vertices are
admitted. Integer X/Z triangle-box overlap is sufficient while every Y lies
inside the native [-16000, 16000] slab. This is a bounded reconstruction of
reviewed scenes, not a general replacement for the game's float helper.
"""
from __future__ import annotations
import hashlib
import struct
try:
    from scripts import model_assets
except ModuleNotFoundError:
    import model_assets

# Entire registered source units include embedded handwritten helper labels.
CODE_SPANS = (
    (0x1510F800, 32, 'e60ff68750b9704132b657981b121501e0de60fd'),
    (0x15000AC0, 9824, '3dbe9e48ed8af17da2d8a93df12637424371907f'),
    (0x15003120, 2240, '3429310d5307bde6707c50d8f0da3b21068f58ce'),
    (0x15049260, 480, 'ddde9dde51fc497075c87be01d5ac0588c2e77a2'),
    (0x150A3A70, 5712, '641320ba2d94f38db169d6fda3ffd81e5c4c4c08'),
    (0x150AA470, 96, 'ce75edb015630fc8fa967fc2732d8a80d236ae6f'),
    (0x150AA4D0, 3360, '91a485731964fd42fc1d855b7500ec17ce5d26a5'),
    (0x150A6210, 1616, '8d8279b398bc812d165d48d7c15b1e85f6987a2e'),
)


def cpu_faces(primary, vertex_count):
    """Replay 15001460's CPU vertex cache and triangle order independently."""
    if len(primary) < 8:
        raise ValueError('visibility primary model header is truncated')
    display, size = struct.unpack_from('>II', primary)
    if display % 8 or size % 8 or display + size > len(primary):
        raise ValueError('visibility display-list extent is invalid')
    cache, faces, loads = {}, [], 0
    for at in range(display, display + size, 8):
        a, b = struct.unpack_from('>II', primary, at)
        opcode = a >> 24
        if opcode == 0xDF:
            return tuple(faces), loads
        if opcode == 1:
            count = (a >> 12) & 255
            start = ((a >> 1) & 127) - count
            source = (b & 0xFFFFFF) // 16
            if (b >> 24 != 1 or b & 15 or start != 0 or not 1 <= count <= 32
                    or source + count > vertex_count):
                raise ValueError('visibility CPU vertex load is outside reviewed contract')
            # Native loop stops at count, not start + count; require start zero.
            for index in range(count):
                cache[index] = source + index
            loads += 1
            continue
        if opcode == 5:
            indices = [((a >> shift) & 255) >> 1 for shift in (16, 8, 0)]
        elif opcode == 6:
            indices = [(word >> shift) & 31 for word in (a, b) for shift in (17, 9, 1)]
        elif opcode >> 4 == 1:
            indices = ([(b >> shift) & 31 for shift in (25, 20, 15, 10, 5, 0)]
                       + [(a >> shift) & 31 for shift in (10, 5, 0, 23, 18)]
                       + [((b >> 30) & 3) | ((a >> 13) & 28)])
        else:
            continue
        if any(index not in cache for index in indices):
            raise ValueError('visibility CPU triangle references an unloaded vertex')
        faces.extend(tuple(cache[index] for index in indices[start:start + 3])
                     for start in range(0, len(indices), 3))
    raise ValueError('visibility CPU list has no end command')


def intersects(triangle, center_x, center_z, half):
    """Inclusive separating-axis test for a triangle and an X/Z square."""
    if (max(p[0] for p in triangle) < center_x - half
            or min(p[0] for p in triangle) > center_x + half
            or max(p[1] for p in triangle) < center_z - half
            or min(p[1] for p in triangle) > center_z + half):
        return False
    for a, b in zip(triangle, triangle[1:] + triangle[:1]):
        normal_x, normal_z = -(b[1] - a[1]), b[0] - a[0]
        projection = [normal_x * (p[0] - center_x) + normal_z * (p[1] - center_z) for p in triangle]
        radius = half * (abs(normal_x) + abs(normal_z))
        if min(projection) > radius or max(projection) < -radius:
            return False
    return True


def quadtree_dimensions(triangles, center_x=0, center_z=0, half=32768):
    selected = [t for t in triangles if intersects(t, center_x, center_z, half)]
    if len(selected) < 10 or half < 512:
        return 1, 1
    nodes, leaves, radius = 1, 0, half // 2
    for x, z in ((center_x - radius, center_z - radius), (center_x - radius, center_z + radius),
                 (center_x + radius, center_z - radius), (center_x + radius, center_z + radius)):
        child_nodes, child_leaves = quadtree_dimensions(selected, x, z, radius)
        nodes += child_nodes
        leaves += child_leaves
    return nodes, leaves


def scene_dimensions(scene):
    parts = model_assets.parse_model_bundle(scene)
    if not parts or parts[0].index != 0:
        raise ValueError('visibility scene has no primary model')
    primary = parts[0].data
    geometry = model_assets.parse_model_geometry(primary, allow_external_texture=True)
    if not geometry.vertices or any(abs(v.y) >= 16000 for v in geometry.vertices):
        raise ValueError('visibility geometry leaves the reviewed vertical slab')
    faces, loads = cpu_faces(primary, len(geometry.vertices))
    if faces != tuple(geometry.faces) or not faces or len(faces) > 65535:
        raise ValueError('visibility CPU geometry differs from primary triangles')
    triangles = [tuple((geometry.vertices[i].x, geometry.vertices[i].z) for i in face) for face in faces]
    nodes, leaves = quadtree_dimensions(triangles)
    if nodes > 21845 or leaves > 16384 or nodes * 3 + 1 != leaves * 4:
        raise ValueError('visibility quadtree exceeds native dimensions')
    return {'node_count': nodes, 'row_count': leaves, 'stride': ((nodes + 7) // 8 + 15) & ~15,
            'triangles': len(faces), 'vertex_loads': loads, 'primary_sha256': hashlib.sha256(primary).hexdigest()}
