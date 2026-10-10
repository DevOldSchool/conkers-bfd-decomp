"""Group independently verified code/data references by their declared owner."""
import json
from pathlib import Path
import re
import subprocess

import data_boundaries
from elf_sections import sections
import objdiff
import objdiff_targets


def owner_key(unit: dict, root: Path) -> tuple | None:
    owner = unit.get('owner')
    if owner and 'sources' in owner:
        return ('source', data_boundaries.active_source(root, owner['sources']))
    if owner:
        return ('sdk', unit['overlay'], owner['archive'], owner['member'])
    if unit.get('kind') == 'source':
        return ('source', unit['source'])
    if unit.get('kind') == 'sdk':
        return ('sdk', unit['overlay'], unit['archive'], unit['member'])
    return None


def combine_targets(parts: list[dict], output: Path, destination: Path) -> dict:
    """Combine whole reference sections without adding padding or changing symbols."""
    expected = {}
    inputs = []
    for part in parts:
        path = output / part['target_path']
        inputs.append(path)
        for name, (header, _) in sections(path.read_bytes(), 1).items():
            if header[1] == 1 and header[2] & 2 and header[5] and name not in ('.reginfo', '.MIPS.abiflags'):
                expected[name] = expected.get(name, 0) + header[5]
    destination.parent.mkdir(parents=True, exist_ok=True)
    script = destination.with_suffix('.ld')
    lines = ['SECTIONS {']
    for name, size in expected.items():
        lines += [f'{name} 0 : SUBALIGN(1) {{ *({name}) }}',
                  f'ASSERT(SIZEOF({name}) == {size}, "owned reference extent")']
    lines += ['}']
    script.write_text('\n'.join(lines) + '\n')
    with destination.with_suffix('.log').open('w') as log:
        subprocess.run(['mips-linux-gnu-ld', '-r', '-m', 'elf32btsmip', '-T', str(script),
                        '-o', str(destination), *map(str, inputs)], check=True, stdout=log, stderr=log)
    actual = {name: header[5] for name, (header, _) in sections(destination.read_bytes(), 1).items()
              if header[1] == 1 and header[2] & 2 and header[5] and name not in ('.reginfo', '.MIPS.abiflags')}
    if actual != expected:
        raise ValueError('grouping changed an owned reference extent')
    return {'target_path': destination.relative_to(output).as_posix(),
            'target_sha256': objdiff_targets.sha256(destination)}


def group_units(specs: list[dict], configs: list[dict], root: Path, output: Path, *,
                verify: bool = True) -> tuple[list[dict], list[dict]]:
    groups = {}
    for index, (spec, config) in enumerate(zip(specs, configs, strict=True)):
        identity = owner_key(spec, root) or ('unowned', index)
        groups.setdefault(identity, []).append((spec, config))
    results, settings = [], []
    for identity, pairs in groups.items():
        parts, items = zip(*pairs)
        unit, config = dict(parts[0]), {**items[0], 'metadata': dict(items[0]['metadata'])}
        data_parts = [p for p in parts if p.get('report_data_bytes')]
        if identity[0] == 'source':
            unit['source'] = identity[1]
            config['name'] = identity[1].removeprefix('src/')
            config['metadata']['source_path'] = identity[1]
        elif identity[0] == 'sdk':
            config['name'] = f'{identity[1]}/sdk/{identity[2]}/{identity[3]}'
        if len(parts) > 1:
            unit.update(combine_targets(list(parts), output, output / 'owned' / unit['key'] / 'target.o'))
            config['target_path'] = unit['target_path']
            unit['report_data_bytes'] = sum(p.get('report_data_bytes', 0) for p in parts)
            unit['report_code_bytes'] = sum(p['report_code_bytes'] for p in parts)
            # The code candidate already contains its C data sections. Do not
            # concatenate multiple compilations of the same source object.
            if not unit.get('base_path'):
                base = next((p for p in parts if p.get('base_path')), None)
                if base:
                    unit.update({k: base[k] for k in ('base_path', 'base_sha256') if k in base})
                    config['base_path'] = base['base_path']
        if data_parts and identity[0] in ('source', 'sdk'):
            unit['data_ranges'] = [dict(p) for p in data_parts]
            unit['complete'] = all(p.get('complete', False) for p in parts)
            unit['completion_reason'] = ('All owned sections rebuilt and linked' if unit['complete'] else
                                         'Owned data includes preserved ROM backing or incomplete source')
            config['metadata']['complete'] = unit['complete']
            if unit['complete']:
                unit['data_completion_verified'] = all(p.get('data_completion_verified') for p in data_parts)
                unit['linked_inputs'] = {
                    path: digest for part in data_parts
                    for path, digest in part.get('linked_inputs', {}).items()}

            config['metadata']['progress_categories'] = list(dict.fromkeys(
                c for item in items for c in item['metadata']['progress_categories']))
        results.append(unit)
        settings.append(config)
    if verify:
        verify_grouped_images(results, output)
    return results, settings


def verify_grouped_images(units: list[dict], output: Path) -> dict:
    """Relink the exact objects objdiff sees, including cross-section relocations."""
    result = {}
    for overlay in ('main', 'game', 'debugger'):
        code = sorted([u for u in units if u.get('overlay') == overlay and 'code_bytes' in u],
                      key=lambda u: u['start'])
        data = []
        for unit in units:
            if unit.get('overlay') != overlay:
                continue
            for span in unit.get('data_ranges', [unit] if unit.get('report_data_bytes') else []):
                data.append((span, unit['target_path']))
        data.sort(key=lambda pair: pair[0]['start'])
        if not code or not data:
            raise ValueError('grouped references must cover every loaded image')
        directory = output / 'owned' / overlay
        directory.mkdir(parents=True, exist_ok=True)
        data_directory = output / 'data' / ('targets' if overlay == 'main' else overlay + '-targets')
        definitions = {}
        for original in (output / 'targets' / overlay / 'targets.elf', data_directory / 'targets.elf'):
            symbols = subprocess.check_output(
                ['mips-linux-gnu-nm', '--defined-only', str(original)], text=True)
            pattern = r'^([0-9a-fA-F]+)\s+\w\s+([A-Za-z_.$][\w.$]*)$'
            for address, name in re.findall(pattern, symbols, re.M):
                value = int(address, 16)
                if name in definitions and definitions[name] != value:
                    raise ValueError('original code/data symbol addresses conflict: ' + name)
                definitions[name] = value
        pointers = json.loads((data_directory / 'rom-pointer-definitions.json').read_text())
        for name, value in pointers.items():
            if name in definitions and definitions[name] != value:
                raise ValueError('original pointer definition conflicts: ' + name)
            definitions[name] = value
        paths = list(dict.fromkeys([u['target_path'] for u in code] + [p for _, p in data]))
        code_start = objdiff_targets.ORIGINS[overlay] + code[0]['start']
        lines = ['SECTIONS {', f'.codeimage 0x{code_start:X} : SUBALIGN(1) {{']
        lines += [f'"{output / u["target_path"]}"(.text)' for u in code]
        lines += ['}', f'.dataimage 0x{data[0][0]["start"]:X} (INFO) : SUBALIGN(1) {{']
        selections = set()
        for span, path in data:
            selector = (path, span['section'])
            if selector in selections:
                raise ValueError('discontiguous data ranges share an input section')
            selections.add(selector)
            lines.append(f'"{output / path}"({span["section"]})')
        lines += ['}', '/DISCARD/ : { *(.reginfo) *(.MIPS.abiflags) *(.pdr) '
                  '*(.gnu.attributes) *(.comment) }', '}']
        lines += [f'PROVIDE({name} = 0x{value:X});' for name, value in sorted(definitions.items())]
        script = directory / 'verify.ld'
        script.write_text('\n'.join(lines) + '\n')
        elf = directory / 'verify.elf'
        with (directory / 'verify.log').open('w') as log:
            subprocess.run(['mips-linux-gnu-ld', '-m', 'elf32btsmip', '-T', str(script), '-o', str(elf),
                            *[str(output / p) for p in paths]], check=True, stdout=log, stderr=log)
        linked = sections(elf.read_bytes(), 2)
        result[overlay] = {
            'code': objdiff_targets.verify_linked_bytes(
                linked['.codeimage'][1], (output / 'targets' / overlay / 'targets.bin').read_bytes(),
                overlay + ' grouped code'),
            'data': objdiff_targets.verify_linked_bytes(
                linked['.dataimage'][1], (data_directory / 'targets.bin').read_bytes(),
                overlay + ' grouped data')}
    objdiff.write_json(output / 'owned/verification.json', result)
    return result
