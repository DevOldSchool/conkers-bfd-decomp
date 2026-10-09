"""Audit US loaded data placements without awarding objdiff matching credit."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path
import re

from profile_config import load_profile

import main_private_data
import rom_span
import rzip_archive

ROOT = Path(__file__).resolve().parent.parent


def partition(base: int, data: bytes, mappings: list[dict]) -> list[dict]:
    """Keep every byte, including zero gaps and unowned compiler-alignment tails."""
    end = base + len(data)
    cursor = base
    result = []
    for item in sorted(mappings, key=lambda item: item['start']):
        start, stop = item['start'], item['end']
        if start < cursor or stop <= start or stop > end:
            raise ValueError(f'overlapping or out-of-range data mapping at {start:#x}:{stop:#x}; '
                             f'previous end {cursor:#x}, image end {end:#x}')
        if cursor < start:
            result.append({'start': cursor, 'end': start, 'kind': 'unassigned'})
        result.append(dict(item))
        cursor = stop
    if cursor < end:
        result.append({'start': cursor, 'end': end, 'kind': 'unassigned'})
    for item in result:
        payload = data[item['start'] - base:item['end'] - base]
        item.update(size=len(payload), sha256=hashlib.sha256(payload).hexdigest(),
                    zero_filled=not any(payload))
    return result


def external_mappings(text: str, evidence: str) -> list[dict]:
    """Read the restricted placement syntax used by reviewed external-data scripts.

    INFO/NOLOAD is a packaging choice, not proof of BSS. Explicit payload sizes
    take precedence over emitted section sizes; compiler padding owns no ROM bytes.
    Reject unsupported named placements rather than silently losing a boundary.
    """
    text = re.sub(r'/\*.*?\*/', '', text, flags=re.S)
    headers = re.findall(r'^\s*(\.(?:main_rodata|game_rodata|debugger_rodata|sdk)_\w+)\b',
                         text, re.M)
    pattern = (r'(\.(?:main_rodata|game_rodata|debugger_rodata|sdk)_\w+)\s+'
               r'(0x[\dA-Fa-f]+)\s+\((INFO|NOLOAD)\)\s*:\s*'
               r'(?:SUBALIGN\(\d+\)\s*)?\{\s*([^{}]+?)\s*\}')
    result = []
    for name, address, mode, selector in re.findall(pattern, text):
        extents = {int(value, 0) for value in re.findall(
            r'SIZEOF\(' + re.escape(name) + r'\)\s*==\s*(0x[\dA-Fa-f]+|\d+)', text)} - {0}
        if len(extents) != 1:
            raise ValueError(f'{name}: expected one nonzero asserted section extent')
        emitted = extents.pop()
        payloads = re.findall(re.escape('__' + name[1:] + '_payload_size') +
                              r'\s*=\s*(0x[\dA-Fa-f]+|\d+)\s*;', text)
        if len(payloads) > 1:
            raise ValueError(f'{name}: duplicate payload extent')
        size = int(payloads[0], 0) if payloads else emitted
        if size <= 0 or size > emitted or (payloads and (size % 4 or ((size + 15) & ~15) != emitted)):
            raise ValueError(f'{name}: invalid payload extent')
        selection = re.fullmatch(r'(\*[\w]+\.o|build/game-libs/us/[\w]+\.a:[\w]+\.o)'
                                 r'\((\.[\w.]+)\);?', selector.strip())
        if selection is None:
            raise ValueError(f'{name}: unsupported input selector')
        start = int(address, 0)
        result.append({'start': start, 'end': start + size, 'kind': 'external_payload',
                       'output': name, 'input': selection[2], 'input_selector': selector.rstrip(';').strip(),
                       'linker_mode': mode, 'emitted_size': emitted,
                       'compiler_padding_bytes': emitted - size, 'evidence_reference': evidence})
    if sorted(headers) != sorted(item['output'] for item in result) or len(set(headers)) != len(headers):
        raise ValueError('unsupported or duplicate external-data placement')
    return result


def main_image(root: Path, rom: bytes) -> tuple[bytes, int, list[dict]]:
    """Bound main initialized data using the canonical map and checked RSP extents."""
    profile = load_profile(root / 'config/profiles/us.yaml')
    main = next(s for s in profile['segments'] if isinstance(s, dict) and s.get('name') == 'main')
    entries = []
    for s in main['subsegments']:
        if isinstance(s, list):
            entries.append({'start': s[0], 'type': s[1], **(
                {'name': s[2], 'object': s[3], 'section': s[4]} if s[1] == 'lib' else {})})
        elif 'start' in s:
            entries.append(s)
    rsp = json.loads((root / 'config/rsp/us.json').read_text())
    if hashlib.sha1(rom).hexdigest() != rsp['rom_sha1']:
        raise ValueError('RSP layout requires the checked US ROM')
    for p in rsp['payloads']:
        if hashlib.md5(rom[p['start']:p['end']]).hexdigest() != p['md5']:
            raise ValueError('RSP payload differs from its reviewed extent')
    start = max(p['end'] for p in rsp['payloads'] if p['kind'] == 'code')
    end = min(p['start'] for p in rsp['payloads'] if p['kind'] == 'data')
    if not 0 <= start < end <= len(rom) or not any(
            e['start'] == start and e['type'] == 'data' for e in entries) or not any(
            e['start'] == end and e.get('name') == 'librsp' for e in entries):
        raise ValueError('main data endpoints disagree with the canonical/RSP maps')
    owned = []
    for index, entry in enumerate(entries):
        offset = entry['start']
        if not start <= offset < end or entry['type'] != 'lib':
            continue
        if entry['name'] == 'librsp' or entry['section'] not in ('.data', '.rodata', '.sdata'):
            raise ValueError('unexpected library section inside main initialized data')
        stop = next(e['start'] for e in entries[index + 1:] if e['start'] > offset)
        owned.append({'start': 0x80000000 + offset, 'end': 0x80000000 + stop,
                      'kind': 'sdk_placement', 'archive': entry['name'],
                      'member': entry['object'] + '.o', 'input': entry['section'],
                      'evidence_reference': 'config/profiles/us.yaml'})
    for unit in main_private_data.mappings(root):
        for section in unit['sections']:
            main_private_data.expected_data(section, rom)
            address = int(section['vram'], 0)
            owned.append({'start': address, 'end': address + section['size'],
                          'kind': 'private_section', 'sources': unit['sources'],
                          'input': section['input'], 'evidence_reference': unit['evidence_reference']})
    return rom[start:end], 0x80000000 + start, owned


def active_source(root: Path, sources: list[str]) -> str:
    """Resolve raw/done alternatives consistently for auditing and reporting."""
    active = [source for source in sources if (root / source).is_file()]
    if len(active) != 1:
        raise ValueError('data owner needs exactly one active source from ' + ', '.join(sources))
    return active[0]


def checked_manifest(root: Path, images: dict, digest: str) -> dict:
    """Attach owners to build-derived ranges; the build files own all boundaries."""
    document = json.loads((root / 'config/data/us.json').read_text())
    if (document.get('schema_version') != 2 or document.get('rom_sha1') != digest
            or set(document['owners']) != set(images)):
        raise ValueError('data ownership manifest has an unsupported schema, ROM or images')
    for overlay, image in images.items():
        owners = {}
        for record in document['owners'][overlay]:
            if (set(record) != {'address', 'section', 'owner'}
                    or not re.fullmatch(r'0x[0-9A-Fa-f]{8}', str(record['address']))):
                raise ValueError('data owner requires a hexadecimal address and section')
            key = (int(record['address'], 16), record['section'])
            if key in owners:
                raise ValueError('duplicate data owner address and section')
            owners[key] = record['owner']
        mapped = {(span['start'], span['input']) for span in image['ranges']
                  if span['kind'] != 'unassigned'}
        if owners.keys() != mapped:
            missing = ', '.join(f'{address:#010x}:{section}'
                                for address, section in sorted(mapped - owners.keys()))
            extra = ', '.join(f'{address:#010x}:{section}'
                              for address, section in sorted(owners.keys() - mapped))
            raise ValueError(overlay + ' data owners disagree with canonical build placements; '
                             + f'update config/data/us.json (missing: {missing or "none"}; '
                             + f'extra: {extra or "none"})')
        for span in image['ranges']:
            if span['kind'] == 'unassigned':
                span['owner'] = None
                continue
            owner = owners[(span['start'], span['input'])]
            if not isinstance(owner, dict) or not owner:
                raise ValueError('mapped data requires an explicit owner')
            if 'sources' in owner:
                sources = owner['sources']
                if (set(owner) != {'sources'} or not isinstance(sources, list) or not sources
                        or any(not isinstance(p, str)
                               or not p.startswith(('src/' + overlay + '/', 'src/done/' + overlay + '/'))
                               or '..' in Path(p).parts for p in sources)):
                    raise ValueError('invalid data source owner')
                if span['kind'] == 'private_section':
                    if sources != span['sources']:
                        raise ValueError('data owner disagrees with private placement')
                elif span['kind'] != 'external_payload' or any(
                        '*' + Path(p).stem + '.o(' + span['input'] + ')' != span['input_selector']
                        for p in sources):
                    raise ValueError('data owner disagrees with linker selector')
                active_source(root, sources)
            else:
                if span['kind'] == 'sdk_placement':
                    expected_owner = {k: span[k] for k in ('archive', 'member')}
                elif span['kind'] == 'external_payload' and ':' in span['input_selector']:
                    selector = span['input_selector'].split('(', 1)[0]
                    archive, member = selector.split(':')
                    expected_owner = {'archive': Path(archive).stem, 'member': member}
                else:
                    raise ValueError('source placement requires a source owner')
                if owner != expected_owner:
                    raise ValueError('data owner disagrees with SDK placement')
            span['owner'] = owner
    return images


def audit(root: Path = ROOT) -> dict:
    rom = main_private_data.validated_rom(root)
    digest = hashlib.sha1(rom).hexdigest()
    main, main_base, main_owned = main_image(root, rom)
    layout = json.loads((root / 'config/rzip_layouts.json').read_text())['profiles']['us']
    if digest not in layout['normalized_sha1'] or layout['game_format'] != 'rzip':
        raise ValueError('game layout disagrees with the checked US ROM')
    game = rzip_archive.parse_game_archive(rom[int(layout['game_start'], 0):int(layout['game_end'], 0)])
    _, debugger, _, debugger_base, debugger_digest = rom_span.debugger_image(root)
    if digest != debugger_digest:
        raise ValueError('debugger ROM changed during audit')
    images = {'main': (main, main_base, main_owned),
              'game': (game.data, int(layout['game_data_vram'], 0), []),
              'debugger': (debugger, debugger_base, [])}
    excluded = []
    for overlay in images:
        paths = [f'config/{overlay}/us-rodata.ld']
        if overlay == 'game':
            paths.append('config/game/us-sdk.ld')
        for path in paths:
            for mapping in external_mappings((root / path).read_text(), path):
                if mapping['input'] in ('.bss', '.sbss'):
                    excluded.append({**mapping, 'consumer_overlay': overlay, 'reason': 'BSS excluded'})
                    continue
                if not (mapping['input'] in ('.data', '.sdata') or mapping['input'].startswith('.rodata')):
                    raise ValueError(f"{mapping['output']}: unsupported initialized input")
                destinations = [name for name, (data, base, _) in images.items()
                                if base <= mapping['start'] < mapping['end'] <= base + len(data)]
                if len(destinations) != 1:
                    raise ValueError(f"{mapping['output']}: no unique loaded data backing")
                destination = destinations[0]
                owned = images[destination][2]
                aliases = [item for item in owned if (item['start'], item['end']) ==
                           (mapping['start'], mapping['end'])]
                if destination != overlay and len(aliases) == 1:
                    # A game SDK object may bind to main's initialized storage.
                    # Keep the placement visible, but count the backing only once.
                    aliases[0].setdefault('shared_placements', []).append(
                        {**mapping, 'consumer_overlay': overlay})
                else:
                    owned.append({**mapping, 'consumer_overlay': overlay})
    output = {}
    for overlay, (data, base, owned) in images.items():
        spans = partition(base, data, owned)
        mapped = sum(s['size'] for s in spans if s['kind'] != 'unassigned')
        output[overlay] = {'vram_start': base, 'vram_end': base + len(data),
                           'loaded_bytes': len(data), 'mapped_bytes': mapped,
                           'unassigned_bytes': len(data) - mapped,
                           'sha256': hashlib.sha256(data).hexdigest(), 'ranges': spans}
    output = checked_manifest(root, output, digest)
    return {'schema_version': 1, 'rom_sha1': digest,
            'scope': 'US initialized CPU data images; excludes BSS, RSP and assets',
            'status': 'boundary_audit_only',
            'limits': 'Placements are not original object boundaries or matching credit. '
                      'No candidate sections or relocations were compared. Unassigned includes '
                      'zero bytes; compiler padding beyond explicit payloads remains unowned.',
            'images': output, 'excluded_bindings': excluded}


def generate(root: Path = ROOT) -> int:
    output = root / 'build/us/data-boundaries/audit.json'
    output.unlink(missing_ok=True)
    result = audit(root)
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(result, indent=2) + '\n')
    for overlay, item in result['images'].items():
        print(f"{overlay}: {item['loaded_bytes']} loaded bytes; {item['mapped_bytes']} mapped; "
              f"{item['unassigned_bytes']} unassigned")
    print('Saved build/us/data-boundaries/audit.json (boundary evidence, no matching credit).')
    return 0


if __name__ == "__main__":
    raise SystemExit(generate())
