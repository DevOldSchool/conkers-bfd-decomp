"""Publish named, self-contained inspection copies of validated model exports."""

from __future__ import annotations

import base64
import copy
import hashlib
import html
import json
import os
import re
import struct
import tempfile
from pathlib import Path
from urllib.parse import unquote, urlsplit

try:
    from scripts.model_preview_evidence import preview_fingerprint
except ModuleNotFoundError:
    from model_preview_evidence import preview_fingerprint

ROOT = Path(__file__).resolve().parents[1]


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def resource(source: Path, uri: str) -> bytes:
    if uri.startswith('data:'):
        header, encoded = uri.split(',', 1)
        if not header.endswith(';base64'):
            raise ValueError('only base64 data URIs are supported')
        return base64.b64decode(encoded, validate=True)
    parsed = urlsplit(uri)
    relative = Path(unquote(parsed.path))
    target = (source.parent / relative).resolve()
    if (parsed.scheme or parsed.netloc or parsed.query or parsed.fragment
            or relative.is_absolute() or not target.is_relative_to(source.parent.parent)):
        raise ValueError(f'nonlocal inspection resource: {uri}')
    return target.read_bytes()


def read_glb(data: bytes) -> tuple[dict, bytes]:
    magic, version, length = struct.unpack_from('<4sII', data)
    if magic != b'glTF' or version != 2 or length != len(data):
        raise ValueError('invalid GLB header')
    json_size, json_kind = struct.unpack_from('<I4s', data, 12)
    binary_header = 20 + json_size
    bin_size, bin_kind = struct.unpack_from('<I4s', data, binary_header)
    if (json_kind != b'JSON' or bin_kind != b'BIN\0' or json_size % 4 or bin_size % 4
            or binary_header + 8 + bin_size != length):
        raise ValueError('invalid GLB chunks')
    return json.loads(data[20:binary_header]), data[binary_header + 8:]


def pack_glb(source: Path) -> tuple[bytes, dict]:
    """Wrap the original buffer and image bytes; never re-export mesh data."""
    source = source.resolve()
    before = preview_fingerprint(source)
    original = json.loads(source.read_text())
    if original.get('asset', {}).get('version') != '2.0' or len(original.get('buffers', [])) != 1:
        raise ValueError('inspection packaging requires a single-buffer glTF 2.0 export')
    if set(original.get('extensionsUsed', [])) - {'KHR_materials_unlit'}:
        raise ValueError('unsupported inspection extension')
    document = copy.deepcopy(original)
    buffer = document['buffers'][0]
    raw = resource(source, buffer.pop('uri'))
    if len(raw) != buffer['byteLength']:
        raise ValueError('source buffer length mismatch')
    binary = bytearray(raw)
    views = document.setdefault('bufferViews', [])
    original_view_count = len(views)
    for view in views:
        offset = view.get('byteOffset', 0)
        if view['buffer'] != 0 or offset < 0 or offset + view['byteLength'] > len(raw):
            raise ValueError('source buffer view exceeds original buffer')
    images = []
    for image in document.get('images', []):
        if 'uri' not in image:
            # Already-embedded images keep their original view and bytes.
            continue
        data = resource(source, image.pop('uri'))
        if data.startswith(b'\x89PNG\r\n\x1a\n'):
            mime = 'image/png'
        elif data.startswith(b'\xff\xd8\xff'):
            mime = 'image/jpeg'
        else:
            raise ValueError('unsupported inspection image format')
        binary.extend(b'\0' * (-len(binary) % 4))
        image['bufferView'] = len(views)
        image['mimeType'] = mime
        views.append({'buffer': 0, 'byteOffset': len(binary), 'byteLength': len(data)})
        binary.extend(data)
        images.append((image['bufferView'], data))
    buffer['byteLength'] = len(binary)
    binary.extend(b'\0' * (-len(binary) % 4))
    encoded = json.dumps(document, separators=(',', ':')).encode()
    encoded += b' ' * (-len(encoded) % 4)
    result = (struct.pack('<4sII', b'glTF', 2, 28 + len(encoded) + len(binary))
              + struct.pack('<I4s', len(encoded), b'JSON') + encoded
              + struct.pack('<I4s', len(binary), b'BIN\0') + binary)
    packed, packed_binary = read_glb(result)
    if packed_binary[:len(raw)] != raw or packed['bufferViews'][:original_view_count] != original.get('bufferViews', []):
        raise ValueError('packaging changed source mesh buffer data')
    for key in set(original) - {'buffers', 'bufferViews', 'images'}:
        if packed[key] != original[key]:
            raise ValueError(f'packaging changed source {key}')
    for index, data in images:
        view = packed['bufferViews'][index]
        start = view['byteOffset']
        if packed_binary[start:start + view['byteLength']] != data:
            raise ValueError('packaging changed image bytes')
    if preview_fingerprint(source) != before:
        raise ValueError('source changed during inspection packaging')
    return result, {'source_fingerprint': before, 'glb_sha256': digest(result),
                    'geometry_buffer_sha256': digest(raw),
                    'image_count': len(document.get('images', [])),
                    'animation_count': len(document.get('animations', []))}


def write_if_changed(path: Path, data: bytes) -> None:
    if path.is_file() and path.read_bytes() == data:
        return
    path.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.NamedTemporaryFile(dir=path.parent, delete=False) as temporary:
        temporary.write(data)
        name = Path(temporary.name)
    name.replace(path)


def publish_inspection(config_path: Path, output: Path) -> dict:
    config = json.loads(config_path.read_text())
    report_path = ROOT / config['validation_report']
    report = json.loads(report_path.read_text())
    if not report.get('summary', {}).get('completed') or report.get('status') == 'failed':
        raise ValueError('run model-assets validate successfully before publishing inspection files')
    output = output.resolve()
    previews = ROOT / config['previews']
    files = {row['path']: row for row in report['files']}
    renders = {row['id']: row for row in report['renders']}
    records, pending, names = [], [], set()
    for case in config['models']:
        name = case['name']
        if not re.fullmatch(r'[a-z0-9]+(?:-[a-z0-9]+)*', name) or name in names:
            raise ValueError(f'invalid or duplicate inspection name: {name}')
        names.add(name)
        render = renders[case['render_case']]
        source = Path(render['source'])
        file = files[str(source)]
        current = preview_fingerprint(source)
        if current != file['input_fingerprint'] or any(
                file['checks'][kind]['status'] != 'passed' for kind in ('gltf', 'blender')):
            raise ValueError(f'stale or unvalidated inspection source: {source}')
        image = Path(render['image'])
        if digest(image.read_bytes()) != render['check']['current_sha256']:
            raise ValueError(f'stale inspection image: {image}')
        glb, evidence = pack_glb(source)
        if evidence['source_fingerprint'] != current:
            raise ValueError(f'source changed since validation: {source}')
        record = {**case, 'source': str(source.relative_to(ROOT)), **evidence,
                  'file': name + '.glb', 'preview': str((previews / (name + '.png')).relative_to(ROOT)),
                  'preview_sha256': digest(image.read_bytes()), 'status': 'ready-for-inspection',
                  'native_visual_parity': 'incomplete'}
        records.append(record)
        pending.extend(((output / record['file'], glb), (previews / (name + '.png'), image.read_bytes())))
    # Validate the complete set before updating any published file.
    for record in records:
        if preview_fingerprint(ROOT / record['source']) != record['source_fingerprint']:
            raise ValueError('an inspection input changed before publication')
    manifest = {'schema_version': 1, 'family': 'model-inspection-set', 'models': records,
                'validation_report': str(report_path.relative_to(ROOT)),
                'scope': 'Self-contained copies preserve source geometry, rigs, animations and image bytes; native visual parity remains incomplete.'}
    lines = ['# Models to inspect', '', 'Import a named `.glb` into Blender and use Material Preview. Each file embeds its textures.',
             'Start with **conker-captured-neutral.glb** for Conker with eyes.', '',
             'Previews show the neutral pose for animated rigs. Native appearance is still under investigation.', '',
             '| Model | Blender file | Preview | Notes |', '| --- | --- | --- | --- |']
    cards = []
    for record in records:
        image_path = ROOT / record['preview']
        image_link = os.path.relpath(image_path, output)
        lines.append(f"| {record['label']} | [{record['file']}]({record['file']}) | [Preview]({image_link}) | {record['note']} |")
        cards.append(f'<article><a href="{html.escape(record["file"], quote=True)}"><img src="{html.escape(image_link, quote=True)}" alt="{html.escape(record["label"], quote=True)}"><h2>{html.escape(record["label"])}</h2></a><p>{html.escape(record["note"])}</p><code>{html.escape(record["file"])}</code></article>')
    lines += ['', 'Refresh after validation: `./conker model-assets inspect`.',
              'The manifest records the original paths and content hashes. Packaging does not modify those sources.', '']
    page = ('<!doctype html><html lang="en"><meta charset="utf-8"><meta name="viewport" content="width=device-width, initial-scale=1">'
            '<title>Conker models to inspect</title><style>body{font:16px system-ui;margin:32px;background:#171b20;color:#eee}a{color:#a7d9ff}main{display:grid;grid-template-columns:repeat(auto-fit,minmax(260px,1fr));gap:24px}article{padding:16px;background:#252b33;border-radius:8px}img{width:100%}h2{font-size:20px}code{overflow-wrap:anywhere}</style>'
            '<h1>Models to inspect</h1><p>Import these self-contained GLB files into Blender using Material Preview. Start with Conker captured neutral.</p>'
            '<p>Native appearance remains under investigation. Animated model previews show the neutral pose.</p><main>'
            + ''.join(cards) + '</main><p>Refresh: <code>./conker model-assets inspect</code></p></html>\n')
    pending += [(output / 'README.md', '\n'.join(lines).encode()), (output / 'index.html', page.encode())]
    for path, data in pending:
        write_if_changed(path, data)
    write_if_changed(output / 'manifest.json', (json.dumps(manifest, indent=2) + '\n').encode())
    return manifest
