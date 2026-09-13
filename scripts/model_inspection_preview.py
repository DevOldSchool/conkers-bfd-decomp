"""Cached camera-only thumbnails of validated inspection models."""
from __future__ import annotations

import hashlib
import json
import math
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from scripts.model_preview_evidence import preview_fingerprint


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def oriented_preview(source, fingerprint, rotation, settings, cache):
    """Keep presentation renders separate from native/regression evidence."""
    blender = Path(shutil.which('blender') or '/Applications/Blender.app/Contents/MacOS/Blender')
    settings = {key: settings.get(key, default) for key, default in
                (('view', 'three-quarter'), ('shading', 'material'), ('size', 512))}
    renderer_paths = [Path(__file__), ROOT / 'scripts/render_model_preview_blender.py',
                      ROOT / 'scripts/model_preview_evidence.py']
    inputs = {'source': str(source), 'fingerprint': fingerprint,
              'camera_rotation_degrees': rotation, 'settings': settings,
              'renderers': {str(p): digest(p) for p in renderer_paths},
              'blender': digest(blender)}
    key = hashlib.sha256(json.dumps(inputs, sort_keys=True).encode()).hexdigest()
    cache.mkdir(parents=True, exist_ok=True)
    image, record = cache / (key + '.png'), cache / (key + '.json')
    if preview_fingerprint(source) != fingerprint:
        raise ValueError('inspection source changed before thumbnail rendering')
    result = json.loads(record.read_text()) if record.is_file() else None
    if not (result and result.get('inputs') == inputs and image.is_file()
            and result.get('image_sha256') == digest(image)):
        request = cache / (key + '-request.json')
        request.write_text(json.dumps({**inputs, 'output': str(image)}))
        with (cache / (key + '.log')).open('w') as log:
            subprocess.run([str(blender), '--background', '--factory-startup',
                            '--python-exit-code', '1', '--python', str(Path(__file__)),
                            '--', str(request)], cwd=ROOT, stdout=log,
                           stderr=subprocess.STDOUT, check=True)
        if (preview_fingerprint(source) != fingerprint
                or any(digest(p) != inputs['renderers'][str(p)] for p in renderer_paths)
                or digest(blender) != inputs['blender']):
            raise ValueError('inspection thumbnail inputs changed during rendering')
        result = {'inputs': inputs, 'image_sha256': digest(image),
                  'scope': 'Camera and lights rotated for inspection; model data unchanged. Not native appearance evidence.'}
        record.write_text(json.dumps(result, indent=2) + '\n')
    return image, result


def render(request):
    import bpy
    from mathutils import Euler, Matrix, Vector
    from scripts.render_model_preview_blender import main as render_model

    source = Path(request['source'])
    if preview_fingerprint(source) != request['fingerprint']:
        raise ValueError('inspection source changed before Blender import')
    settings = request['settings']
    # Reuse the normal importer, framing and lighting. Its intermediate view
    # is temporary; only the camera/light transform changes for the final PNG.
    with tempfile.TemporaryDirectory() as tmp:
        render_model(['--input', str(source), '--output', str(Path(tmp) / 'base.png'),
                      '--size', str(settings['size']), '--view', settings['view'],
                      '--shading', settings['shading']])
    corners = [obj.matrix_world @ Vector(corner) for obj in bpy.context.scene.objects
               if obj.type == 'MESH' for corner in obj.bound_box]
    center = Vector(tuple((min(v[a] for v in corners) + max(v[a] for v in corners)) / 2
                          for a in range(3)))
    rotation = Euler(tuple(math.radians(v) for v in request['camera_rotation_degrees']), 'XYZ')
    transform = Matrix.Translation(center) @ rotation.to_matrix().to_4x4() @ Matrix.Translation(-center)
    for obj in bpy.context.scene.objects:
        if obj.type in ('CAMERA', 'LIGHT'):
            obj.matrix_world = transform @ obj.matrix_world
    bpy.context.scene.render.filepath = request['output']
    bpy.ops.render.render(write_still=True)
    if preview_fingerprint(source) != request['fingerprint']:
        raise ValueError('inspection source changed during Blender rendering')


if __name__ == '__main__':
    render(json.loads(Path(sys.argv[sys.argv.index('--') + 1]).read_text()))
