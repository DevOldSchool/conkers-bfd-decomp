"""Publish named, self-contained inspection copies of validated model exports."""

from __future__ import annotations

import base64
import copy
import hashlib
import html
import json
import math
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
CATEGORIES = {
    'characters': ('Characters', 'Characters, creatures and living objects.'),
    'collectables': ('Collectables', 'Cash, keys, food and multiplayer objectives.'),
    'weapons': ('Weapons', 'Guns, crossbows, melee weapons, explosives and projectiles.'),
    'scene-items': ('Scene items', 'Scenery, props, vehicles and equipment.'),
    'parts-effects': ('Parts & effects', 'Detached parts, attachments, debris and effects.'),
    'extracted-review': ('Extracted review', 'Remaining ROM exports for review. Includes unfinished materials, fragments, variants and records with no drawable faces. Assembled components and identical exported presentations are shown on their corresponding gallery cards.'),
}


def validate_gallery_metadata(models: list[dict]) -> None:
    """Require deliberate categorization without treating labels as ROM evidence."""
    for model in models:
        if any(key in model for key in ('download_file', 'download_sha256', 'download_format',
                                       'texgen_inspection', 'scene55_inspection', 'embedded_type13_inspection', 'embedded_type06_inspection', 'haybot_inspection')):
            raise ValueError('inspection downloads must be derived from verified artifacts')
        if 'gallery_represented_by' in model or 'gallery_equivalent_to' in model:
            raise ValueError('review representation must be derived from verified source evidence')
        if model.get('category') not in CATEGORIES:
            raise ValueError(f'invalid or missing inspection category: {model["name"]}')
        aliases = model.get('aliases', [])
        if not isinstance(aliases, list) or any(not isinstance(alias, str) for alias in aliases):
            raise ValueError(f'invalid inspection aliases: {model["name"]}')
        rotation = model.get('preview_rotation')
        if rotation is not None and (not isinstance(rotation, list) or len(rotation) != 3
                or any(isinstance(v, bool) or not isinstance(v, (int, float))
                       or not math.isfinite(v) or abs(v) > 360 for v in rotation)):
            raise ValueError(f'invalid inspection camera rotation: {model["name"]}')
        identification = model.get('identification')
        if identification is not None:
            reference = urlsplit(identification.get('reference_url', ''))
            if (identification.get('basis') != 'visual-reference'
                    or reference.scheme != 'https' or not reference.hostname
                    or not identification.get('reference_label')):
                raise ValueError(f'invalid visual identification reference: {model["name"]}')

    by_name = {model.get('name'): model for model in models}
    for model in models:
        replacement = model.get('gallery_replaced_by')
        if replacement is None:
            continue
        target = by_name.get(replacement) if isinstance(replacement, str) else None
        if (target is None or target.get('gallery_replaced_by') is not None
                or target['category'] != model['category']):
            raise ValueError(f'invalid gallery replacement: {model["name"]}')


def gallery_records(records: list[dict]) -> list[dict]:
    """Keep replaced source exports in evidence, but offer only their replacement."""
    return [record for record in records
            if record.get('gallery_replaced_by') is None and not record.get('gallery_represented_by')
            and not record.get('gallery_equivalent_to')]


def gallery_page(records: list[dict], output: Path) -> str:
    """Render a standalone, offline gallery with category and alias filtering."""
    records = gallery_records(records)
    cards = []
    for record in records:
        if record.get('preview'):
            image_link = os.path.relpath(ROOT / record['preview'], output)
            image_link += '?v=' + record['preview_sha256']
            preview = (f'<img loading="lazy" width="512" height="512" src="{html.escape(image_link, quote=True)}" '
                       f'alt="{html.escape(record["label"], quote=True)}">')
        else:
            preview = '<div class="preview-placeholder">No drawable faces</div>'
        download = record.get('download_file', record['file'])
        model_link = download + '?v=' + record.get('download_sha256', record['glb_sha256'])
        search_text = ' '.join([record['label'], record['file'], download,
                                record.get('review_label', ''), *record.get('aliases', [])])
        identification = record.get('identification')
        reference = ''
        if identification:
            reference = (f'<p>Visual identification: <a href="{html.escape(identification["reference_url"], quote=True)}">'
                         f'{html.escape(identification["reference_label"])}</a>. '
                         'The name is inferred from appearance; the bank and entry identify the ROM asset.</p>')
        title = record['label'].split(' — ROM', 1)[0]
        badge = (f'<p class="review-badge" data-status="{html.escape(record["review_status"], quote=True)}">'
                 f'{html.escape(record["review_label"])}</p>' if record.get('review_status') else '')
        bank = f'{record["bank"]:02x}' if 'bank' in record else ''
        cards.append(
            f'<article data-category="{record["category"]}" data-bank="{bank}" '
            f'data-review-status="{html.escape(record.get("review_status", ""), quote=True)}" '
            f'data-search="{html.escape(search_text, quote=True)}">'
            f'<a href="{html.escape(model_link, quote=True)}">'
            f'{preview}<h2>{html.escape(title)}</h2></a>{badge}<code>{html.escape(download)}</code>'
            f'<details><summary>Export details</summary><p>{html.escape(record["note"])}</p>{reference}</details></article>')
    categories = {**CATEGORIES, 'all': ('All models', 'Standalone models, scene assemblies and remaining records for review.')}
    tabs = []
    for category, (label, description) in categories.items():
        count = sum(category == 'all' or row['category'] == category for row in records)
        tabs.append(f'<button type="button" role="tab" id="tab-{category}" data-category="{category}" '
                    f'data-description="{html.escape(description, quote=True)}" data-label="{label}" '
                    f'aria-controls="model-panel" aria-selected="false" tabindex="-1">'
                    f'{html.escape(label)} <span class="tab-count">{count}</span></button>')
    template = Path(__file__).with_name('model_inspection.html').read_text()
    # Substitute only template tokens, never tokens inside user-facing metadata.
    values = {'TABS': ''.join(tabs), 'CARDS': ''.join(cards), 'COUNT': str(len(records)),
              'PREVIEW_STYLES': Path(__file__).with_name('preview-common.css').read_text()}
    return re.sub(r'\{\{(TABS|CARDS|COUNT|PREVIEW_STYLES)\}\}', lambda match: values[match[1]], template)


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


def rom_source_evidence(source: Path, *, assembly_cache=None) -> dict:
    """Require a selected ROM model, even in a corpus with other captured rows."""
    source = source.resolve()
    root = source.parent.parent
    manifest_path = root / 'manifest.json'
    manifest_bytes = manifest_path.read_bytes()
    manifest = json.loads(manifest_bytes)
    if manifest.get('family') == 'rom-static-scene-assemblies':
        try:
            from scripts.model_scene_assemblies import inspection_evidence
        except ModuleNotFoundError:
            from model_scene_assemblies import inspection_evidence
        return inspection_evidence(source, verification_cache=assembly_cache)
    bank = manifest.get('bank_index')
    if (bank not in (1, 3, 4, 9) or manifest.get('profile') != 'us'
            or manifest.get('family') != f'indexed-bank-{bank:02x}-model-preview'):
        raise ValueError('inspection requires a ROM model preview, not a captured composition')
    if bank == 1 and not manifest.get('rom_character_defaults'):
        raise ValueError('character inspection requires the ROM-default corpus')
    relative = str(source.relative_to(root))
    records = [record for record in manifest['models']
               if relative in (record.get('gltf_file'), record.get('bind_gltf_file'))]
    if len(records) != 1 or not isinstance(records[0].get('material_runs'), list):
        raise ValueError('inspection source lacks a unique ROM model record')
    record = records[0]
    if any(run.get('runtime_material') is not None for run in record['material_runs']):
        raise ValueError('inspection model uses captured runtime materials')
    document = json.loads(source.read_bytes())
    if any('runtimeMaterial' in material.get('extras', {})
           for material in document.get('materials', [])):
        raise ValueError('inspection glTF contains captured runtime material evidence')
    return {'manifest_sha256': digest(manifest_bytes), 'bank': bank,
            'entry': record['bank_entry'], 'segment': record['segment'],
            'source': 'ROM', 'capture_inputs': []}


def prepare_texgen_inspection(options: dict, review_records: list[dict], output: Path,
                              pending: list[tuple[Path, bytes]]) -> tuple:
    """Replace one visible download after verification; retain its raw GLB evidence.

    Only prepares in-memory publication records and bytes. The returned artifact
    proof must be rechecked immediately before the publisher writes any files.
    """
    try:
        from scripts.model_inspection_options import texgen_options
    except ModuleNotFoundError:
        from model_inspection_options import texgen_options
    mode, artifact_output = texgen_options(options, ROOT)
    name = 'review-bank01-0066-00-rom'
    candidates = [record for record in review_records if record.get('name') == name
                  or (record.get('bank'), record.get('entry'), record.get('segment')) == (1, 66, 0)]
    if len(candidates) != 1:
        raise ValueError('texgen inspection requires one current character66 review record')
    record = candidates[0]
    if (record.get('name') != name or (record.get('bank'), record.get('entry'), record.get('segment')) != (1, 66, 0)
            or record.get('category') != 'extracted-review'
            or record.get('review_status') != 'appearance-blocked'
            or record.get('status') != 'extracted-for-review'
            or record.get('native_visual_parity') != 'incomplete'
            or record.get('file') != 'review/' + name + '.glb'
            or any(record.get(key) for key in ('gallery_replaced_by', 'gallery_represented_by', 'gallery_equivalent_to'))):
        raise ValueError('texgen inspection review identity or scope changed')
    rom_source = record.get('rom_source', {})
    if ((rom_source.get('bank'), rom_source.get('entry'), rom_source.get('segment')) != (1, 66, 0)
            or rom_source.get('source') != 'ROM' or rom_source.get('capture_inputs') != []):
        raise ValueError('texgen inspection requires the matching ROM source evidence')
    raw_exports = [data for path, data in pending if path == output / record['file']]
    if len(raw_exports) != 1 or digest(raw_exports[0]) != record.get('glb_sha256'):
        raise ValueError('texgen inspection raw GLB evidence changed')
    if mode == 'animated':
        try:
            from scripts import model_character_animated_texgen as backend
        except ModuleNotFoundError:
            import model_character_animated_texgen as backend
    else:
        try:
            from scripts import model_character_texgen as backend
        except ModuleNotFoundError:
            import model_character_texgen as backend
    artifact = backend.inspection_artifact(artifact_output)
    proof, blend, image, scope = (artifact[key] for key in ('proof', 'blend', 'preview', 'scope'))
    if (not isinstance(proof, dict) or proof.get('kind') != f'character66-{mode}-texgen'
            or proof.get('model') != [1, 66, 0]
            or proof.get('output') != str(artifact_output.relative_to(ROOT))
            or proof.get('source') != record['source']
            or proof.get('source_fingerprint') != record['source_fingerprint']
            or proof.get('source_gltf_sha256') != record['source_fingerprint']['gltf_sha256']
            or preview_fingerprint(ROOT / record['source']) != record['source_fingerprint']):
        raise ValueError('texgen inspection artifact does not match the current review source')
    if (not isinstance(blend, bytes) or not blend or not isinstance(image, bytes)
            or not image.startswith(b'\x89PNG\r\n\x1a\n') or not isinstance(scope, str) or not scope
            or digest(blend) != proof.get('blend_sha256')
            or digest(image) != proof.get('preview_sha256')):
        raise ValueError('texgen inspection artifact bytes or scope changed')
    if not record.get('preview'):
        raise ValueError('texgen inspection requires the current review preview')
    preview_target = ROOT / record['preview']
    # Remove the prepared raw thumbnail so publication never writes it and then
    # overwrites it with a different inspection state in the same transaction.
    if sum(path == preview_target for path, _ in pending) != 1:
        raise ValueError('texgen inspection review preview publication is ambiguous')
    download = 'review/' + name + f'-{mode}-texgen.blend'
    pending[:] = [(path, data) for path, data in pending if path != preview_target]
    pending.extend(((output / download, blend), (preview_target, image)))
    record.update(download_file=download, download_sha256=digest(blend), download_format='blend',
                  preview_sha256=digest(image), texgen_inspection=copy.deepcopy(proof),
                  label=('Bank 01 / 0066 / 00 — ' + ('animated' if mode == 'animated' else 'neutral-pose')
                         + ' Blender inspection'),
                  note=scope + ' Original review: ' + record['note'])
    return backend.inspection_artifact_current, artifact_output, proof


def prepare_scene55_inspection(options: dict, records: list[dict], output: Path,
                               pending: list[tuple[Path, bytes]]) -> tuple:
    """Admit one independently sampled scene material without another scene card."""
    try:
        from scripts.model_inspection_options import scene55_output
        from scripts import model_scene55_inspection as backend
    except ModuleNotFoundError:
        from model_inspection_options import scene55_output
        import model_scene55_inspection as backend
    artifact_output = scene55_output(options, ROOT)
    name = 'scene-55-assembly-rom'
    candidates = [r for r in records if r.get('name') == name]
    if len(candidates) != 1:
        raise ValueError('scene55 inspection requires one current assembly record')
    record = candidates[0]
    source = record.get('rom_source', {})
    if (record.get('category') != 'scene-items' or record.get('status') != 'ready-for-inspection'
            or record.get('native_visual_parity') != 'incomplete'
            or record.get('file') != name + '.glb'
            or source.get('source') != 'ROM' or source.get('kind') != 'static-scene-assembly'
            or source.get('scene_index') != 55 or source.get('capture_inputs') != []
            or any(record.get(k) for k in ('gallery_replaced_by', 'gallery_represented_by', 'gallery_equivalent_to'))):
        raise ValueError('scene55 inspection assembly identity or scope changed')
    raw = [data for path, data in pending if path == output / record['file']]
    if len(raw) != 1 or digest(raw[0]) != record.get('glb_sha256'):
        raise ValueError('scene55 inspection raw GLB evidence changed')
    artifact = backend.inspection_artifact(artifact_output)
    proof, blend, image, scope = (artifact[k] for k in ('proof', 'blend', 'preview', 'scope'))
    if (not isinstance(proof, dict) or proof.get('kind') != 'scene55-dual-texture'
            or proof.get('scene_index') != 55
            or proof.get('output') != str(artifact_output.relative_to(ROOT))
            or proof.get('source') != record['source']
            or proof.get('source_fingerprint') != record['source_fingerprint']
            or proof.get('source_gltf_sha256') != record['source_fingerprint']['gltf_sha256']
            or preview_fingerprint(ROOT / record['source']) != record['source_fingerprint']):
        raise ValueError('scene55 inspection artifact does not match the current assembly source')
    if (not isinstance(blend, bytes) or not blend or not isinstance(image, bytes)
            or not image.startswith(b'\x89PNG\r\n\x1a\n') or not isinstance(scope, str) or not scope
            or digest(blend) != proof.get('blend_sha256') or digest(image) != proof.get('preview_sha256')):
        raise ValueError('scene55 inspection artifact bytes or scope changed')
    if not record.get('preview'):
        raise ValueError('scene55 inspection requires the current assembly preview')
    target = ROOT / record['preview']
    if sum(path == target for path, _ in pending) != 1:
        raise ValueError('scene55 inspection preview publication is ambiguous')
    download = name + '-dual-texture.blend'
    pending[:] = [(p, b) for p, b in pending if p != target]
    pending.extend(((output / download, blend), (target, image)))
    record.update(download_file=download, download_sha256=digest(blend), download_format='blend',
                  preview_sha256=digest(image), scene55_inspection=copy.deepcopy(proof),
                  label=record['label'] + ' — Blender inspection',
                  note=scope + ' Original assembly: ' + record['note'])
    return backend.inspection_artifact_current, artifact_output, proof


def publish_inspection(config_path: Path, output: Path) -> dict:
    config = json.loads(config_path.read_text())
    validate_gallery_metadata(config['models'])
    report_path = ROOT / config['validation_report']
    report = json.loads(report_path.read_text())
    if not report.get('summary', {}).get('completed') or report.get('status') == 'failed':
        raise ValueError('run model-assets validate successfully before publishing inspection files')
    output = output.resolve()
    previews = ROOT / config['previews']
    files = {row['path']: row for row in report['files']}
    renders = {row['id']: row for row in report['renders']}
    records, pending, names = [], [], set()
    assembly_cache = {}
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
        presentation = None
        if case.get('preview_rotation') is not None:
            try:
                from scripts.model_inspection_preview import oriented_preview
            except ModuleNotFoundError:
                from model_inspection_preview import oriented_preview
            image, presentation = oriented_preview(
                source, current, case['preview_rotation'], render.get('settings', {}),
                ROOT / 'build/assets/models/inspection-preview-cache')
        rom_evidence = rom_source_evidence(source, assembly_cache=assembly_cache) if config.get('rom_only') else None
        if rom_evidence and rom_evidence.get('kind') == 'static-scene-assembly':
            check = report.get('checks', {}).get('scene-assemblies:' + str(source.parent.parent.relative_to(ROOT)), {})
            if check.get('status') != 'passed' or check.get('manifest_sha256') != rom_evidence['manifest_sha256']:
                raise ValueError('scene assembly lacks current ROM placement validation')
        glb, evidence = pack_glb(source)
        if evidence['source_fingerprint'] != current:
            raise ValueError(f'source changed since validation: {source}')
        record = {**case, 'source': str(source.relative_to(ROOT)), **evidence,
                  **({'preview_presentation': presentation} if presentation is not None else {}),
                  **({'rom_source': rom_evidence} if rom_evidence is not None else {}),
                  'file': name + '.glb', 'preview': str((previews / (name + '.png')).relative_to(ROOT)),
                  'preview_sha256': digest(image.read_bytes()), 'status': 'ready-for-inspection',
                  'native_visual_parity': 'incomplete'}
        records.append(record)
        pending.extend(((output / record['file'], glb), (previews / (name + '.png'), image.read_bytes())))
    review_records = []
    if config.get('extracted_review'):
        try:
            from scripts.model_inspection_review import prepare_review
        except ModuleNotFoundError:
            from model_inspection_review import prepare_review
        review_records, review_files = prepare_review(config['extracted_review'], records, report, output, previews)
        pending.extend(review_files)
    artifact_preflights = []
    if 'texgen_inspection' in config:
        if not config.get('rom_only'):
            raise ValueError('texgen inspection requires ROM-only publication')
        artifact_preflights.append(prepare_texgen_inspection(config['texgen_inspection'], review_records, output, pending))
    if 'scene55_inspection' in config:
        if not config.get('rom_only'):
            raise ValueError('scene55 inspection requires ROM-only publication')
        artifact_preflights.append(prepare_scene55_inspection(config['scene55_inspection'], records, output, pending))
    if 'haybot_inspection' in config:
        if not config.get('rom_only'):
            raise ValueError('Haybot inspection requires ROM-only publication')
        try:
            from scripts.model_inspection_haybot import prepare_haybot
        except ModuleNotFoundError:
            from model_inspection_haybot import prepare_haybot
        artifact_preflights.append(prepare_haybot(
            config['haybot_inspection'], records, ROOT, output, pending))
    # Validate the complete set before updating any published file.
    # Never reuse preparation evidence here: component/placement changes during
    # packaging must trigger fresh whole-set recomposition before publication.
    assembly_cache = {}
    for record in records + review_records:
        if preview_fingerprint(ROOT / record['source']) != record['source_fingerprint']:
            raise ValueError('an inspection input changed before publication')
        if config.get('rom_only') and rom_source_evidence(
                ROOT / record['source'], assembly_cache=assembly_cache) != record['rom_source']:
            raise ValueError('ROM inspection provenance changed before publication')
    if review_records and config.get('rom_only'):
        try:
            from scripts.model_review_representation import apply_representation
        except ModuleNotFoundError:
            from model_review_representation import apply_representation
        apply_representation(records, review_records)
        try:
            from scripts.model_review_equivalence import apply_equivalence, bind_equivalence_decisions
        except ModuleNotFoundError:
            from model_review_equivalence import apply_equivalence, bind_equivalence_decisions
        bind_equivalence_decisions(review_records, ROOT, ROOT / config['extracted_review']['reviews'])
        apply_equivalence(records, review_records, ROOT)
    # Embedded primitives have no indexed bank identity. Their independent
    # source reconstruction, Khronos check and fresh Blender verification happen
    # before admission; do not feed them through indexed review/equivalence.
    if 'embedded_type13_inspection' in config:
        if not config.get('rom_only'):
            raise ValueError('embedded inspection requires ROM-only publication')
        try:
            from scripts.model_inspection_embedded import prepare_type13
        except ModuleNotFoundError:
            from model_inspection_embedded import prepare_type13
        record, additions, preflight = prepare_type13(
            config['embedded_type13_inspection'], ROOT, output, previews)
        if any(row['name'] == record['name'] or row['source'] == record['source']
               for row in records + review_records):
            raise ValueError('duplicate embedded inspection source or name')
        records.append(record)
        pending.extend(additions)
        artifact_preflights.append(preflight)
    if 'embedded_type06_inspection' in config:
        if not config.get('rom_only'):
            raise ValueError('embedded inspection requires ROM-only publication')
        try:
            from scripts.model_inspection_embedded_type06 import prepare_type06
        except ModuleNotFoundError:
            from model_inspection_embedded_type06 import prepare_type06
        record, additions, preflight = prepare_type06(
            config['embedded_type06_inspection'], ROOT, output, previews)
        if any(row['name'] == record['name'] or row['source'] == record['source']
               for row in records + review_records):
            raise ValueError('duplicate embedded inspection source or name')
        records.append(record)
        pending.extend(additions)
        artifact_preflights.append(preflight)
    visible = gallery_records(records + review_records)
    manifest = {'schema_version': 1, 'family': 'model-inspection-set', 'models': records,
                'review_models': review_records,
                'curated_count': len(records), 'review_count': len(review_records),
                'gallery_count': len(visible),
                'gallery_curated_count': len(gallery_records(records)),
                'gallery_review_count': len(gallery_records(review_records)),
                'represented_review_count': sum(bool(row.get('gallery_represented_by')) for row in review_records),
                'equivalent_review_count': sum(bool(row.get('gallery_equivalent_to')) for row in review_records),
                'rom_only': bool(config.get('rom_only')),
                'categories': [{'id': key, 'label': value[0], 'description': value[1]}
                               for key, value in CATEGORIES.items()],
                'validation_report': str(report_path.relative_to(ROOT)),
                'scope': 'Self-contained GLBs preserve source geometry, rigs, animations and image bytes. Optional Blender inspections document their selected-state limits and retain the source exports; native visual parity remains incomplete.'}
    start_file = visible[0].get('download_file', visible[0]['file']) if visible else ''
    lines = ['# Models to inspect', '', 'Import a named `.glb` into Blender and use Material Preview, or open a `.blend` file directly. Each download embeds its textures.',
             f'Start with **{start_file}**.', '',
             'Previews show the neutral pose for animated rigs. Native appearance is still under investigation.', '',
             '| Model | Category | Blender file | Preview | Notes |', '| --- | --- | --- | --- | --- |']
    for record in visible:
        image_link = (f"[Preview]({os.path.relpath(ROOT / record['preview'], output)})"
                      if record.get('preview') else 'No drawable faces')
        download = record.get('download_file', record['file'])
        lines.append(f"| {record['label']} | {CATEGORIES[record['category']][0]} | [{download}]({download}) | {image_link} | {record['note']} |")
    lines += ['', 'Refresh after validation: `./conker model-assets inspect`.',
              'The manifest records the original paths and content hashes. Packaging does not modify those sources.', '']
    page = gallery_page(records + review_records, output)
    pending += [(output / 'README.md', '\n'.join(lines).encode()), (output / 'index.html', page.encode())]
    for recheck, artifact_output, proof in artifact_preflights:
        if recheck(artifact_output, proof) is False:
            raise ValueError('inspection artifact changed before publication')
    for path, data in pending:
        write_if_changed(path, data)
    write_if_changed(output / 'manifest.json', (json.dumps(manifest, indent=2) + '\n').encode())
    return manifest
