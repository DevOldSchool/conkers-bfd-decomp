#!/usr/bin/env python3
"""Build an exhaustive US CPU-code project for native objdiff report generation.

References come from independently assembled splat full-disassembly units.
Their linked code bytes must reproduce the original US CPU-code ranges. Missing implementations stay
in the denominator. This is a code report, not a ROM/data completion claim.
"""
from __future__ import annotations

from concurrent.futures import ThreadPoolExecutor, as_completed
import hashlib
import json
from pathlib import Path
import struct
import subprocess
import sys
import time
import zipfile

import compile_c
import diff
import objdiff_targets
import objdiff
import project_state as state

ROOT = Path(__file__).resolve().parent.parent
OUTPUT = ROOT / 'build/us/objdiff-report'


def partition(start: int, end: int, owned: list[dict], boundaries: list[int]) -> list[dict]:
    """Cover a code range exactly once; never let raw gaps disappear."""
    result = []
    cursor = start
    for unit in sorted(owned, key=lambda u: u['start']) + [{'start': end, 'end': end}]:
        left, right = unit['start'], unit['end']
        if left < cursor or right > end or right < left:
            raise ValueError(f'overlapping/out-of-range report unit at {left:#x}:{right:#x}')
        cuts = [cursor] + sorted({x for x in boundaries if cursor < x < left}) + [left]
        for a, b in zip(cuts, cuts[1:]):
            if a != b:
                result.append({'start': a, 'end': b, 'kind': 'unassigned'})
        if left != right:
            result.append(unit)
        cursor = right
    if sum(u['end'] - u['start'] for u in result) != end - start:
        raise ValueError('report plan does not cover code range')
    return result


def plan() -> list[dict]:
    functions = state.load_json(state.FUNCTIONS_FILE)['functions']
    units = state.load_json(state.SOURCE_UNITS_FILE)['source_units']
    by_id = {f['symbol']: f for f in functions}
    ranges = state.validate_code_ranges(state.load_json(state.OVERLAYS_FILE))
    result = []
    for overlay in ('main', 'game'):
        start, end = ranges[overlay]['us']
        owned = []
        for unit in units:
            members = [by_id[name] for name in unit['functions']]
            if members[0].get('overlay', 'main') != overlay:
                continue
            region = unit['regions']['us']
            owned.append({'start': int(region['start'], 0), 'end': int(region['end'], 0),
                          'kind': 'source', 'source': unit['source'],
                          'complete': unit['integration'] == 'c'})
        entries = state.mapped_subsegments('us', overlay)
        for pos, (offset, kind, name) in enumerate(entries):
            if kind != 'lib' or not start <= offset < end:
                continue
            fields = [field.strip() for field in (name or '').split(',')]
            if len(fields) != 3 or fields[-1] != '.text' or fields[0] == 'librsp':
                continue
            following = next((s for s, _, _ in entries[pos + 1:] if s > offset), end)
            owned.append({'start': offset, 'end': min(end, following), 'kind': 'sdk',
                          'archive': fields[0], 'member': fields[1] + '.o', 'complete': True})
        for item in partition(start, end, owned, [s for s, _, _ in entries]):
            item['overlay'] = overlay
            item['key'] = f'{overlay}/{item["start"]:06X}'
            result.append(item)
    return result


def elf_text_symbols(path: Path) -> dict:
    data = path.read_bytes()
    if data[:6] != b'\x7fELF\x01\x02' or struct.unpack_from('>HH', data, 16) != (1, 8):
        raise ValueError(f'expected ELF32 MIPS object: {path}')
    shoff = struct.unpack_from('>I', data, 32)[0]
    size, count, names_index = struct.unpack_from('>HHH', data, 46)
    if size != 40:
        raise ValueError('unexpected ELF section header size')
    sections = [struct.unpack_from('>10I', data, shoff + i * size) for i in range(count)]
    strings = sections[names_index]
    names = data[strings[4]:strings[4]+strings[5]]
    text_sections = {i for i, s in enumerate(sections) if names[s[0]:].split(b'\0', 1)[0] == b'.text'}
    result = {}
    for section in sections:
        if section[1] != 2:
            continue
        strings = sections[section[6]]
        names = data[strings[4]:strings[4]+strings[5]]
        for offset in range(section[4], section[4] + section[5], 16):
            name, address, length, info, visibility, index = struct.unpack_from('>IIIBBH', data, offset)
            name = names[name:].split(b'\0', 1)[0].decode()
            if index in text_sections and name and info & 15 in (0, 2):
                result[name] = {'address': address, 'size': length, 'type': info & 15,
                                'hidden': visibility & 3 == 2}
    return result


def digest_files(paths: list[Path]) -> str:
    digest = hashlib.sha256()
    for path in sorted(paths):
        digest.update(str(path.relative_to(ROOT)).encode() + b'\0' + path.read_bytes())
    return digest.hexdigest()


def prepare() -> None:
    OUTPUT.mkdir(parents=True, exist_ok=True)
    for name in ('objdiff.json', 'coverage.json'):
        (OUTPUT / name).unlink(missing_ok=True)
    specs = plan()
    targets, target_verification = objdiff_targets.prepare(specs, OUTPUT)
    linked = {overlay: (OUTPUT / 'targets' / overlay / 'targets.bin').read_bytes()
              for overlay in ('main', 'game')}
    origins = {overlay: min(s['start'] for s in specs if s['overlay'] == overlay)
               for overlay in linked}
    common = digest_files([p for p in (ROOT / 'include').rglob('*') if p.is_file()] + [Path(__file__),
                          ROOT / 'Dockerfile', ROOT / 'scripts/normalize_asm.py', ROOT / 'scripts/objdiff_targets.py',
                          ROOT / 'scripts/compile_c.py', ROOT / 'scripts/diff.py',
                          ROOT / 'toolchain/tools.lock.json'])

    def build_unit(spec):
        directory = OUTPUT / spec['key']
        directory.mkdir(parents=True, exist_ok=True)
        target = targets[spec['key']]
        target_path = OUTPUT / target['path']
        target_symbols = elf_text_symbols(target_path)
        original = linked[spec['overlay']][spec['start'] - origins[spec['overlay']]:
                                          spec['end'] - origins[spec['overlay']]]
        symbol_coverage = objdiff_targets.symbol_coverage(original, target_symbols)
        base_source = ROOT / spec['source'] if spec['kind'] == 'source' else None
        archive = None
        if spec['kind'] == 'sdk':
            libdir = 'build/us/lib' if spec['overlay'] == 'main' else 'build/game-libs/us'
            archive = ROOT / libdir / (spec['archive'] + '.a')
        digest = hashlib.sha256((common + target['sha256'] + json.dumps(spec, sort_keys=True)).encode())
        if base_source:
            digest.update(base_source.read_bytes())
        if archive:
            digest.update(archive.read_bytes())
        key = digest.hexdigest()
        cache = directory / 'unit.json'
        if cache.exists():
            previous = json.loads(cache.read_text())
            outputs = [directory / 'base.o'] if previous.get('base_path') else []
            if not previous.get('compile_error') and previous.get('cache_key') == key and all(
                    p.is_file() and hashlib.sha256(p.read_bytes()).hexdigest() ==
                    previous.get('object_sha256', {}).get(p.name) for p in outputs):
                return previous
        with (directory / 'build.log').open('w') as log:
            unit = {**spec, 'cache_key': key, 'target_path': target['path'],
                    'target_source': target['source'], 'target_sha256': target['sha256'],
                    'symbol_count': len(target_symbols),
                    'code_bytes': target['text_bytes'], **symbol_coverage}
            if base_source:
                focused = diff.GLOBAL_ASM_LINE.sub('', base_source.read_text())
                focused_path = directory / 'base.c'
                focused_path.write_text(focused)
                # No activation of deferred #if 0 candidates in a public report.
                result = subprocess.run(compile_c.compile_command('us', focused_path, directory / 'base.o'),
                                        cwd=ROOT, stdout=log, stderr=log)
                if result.returncode:
                    unit['compile_error'] = f'{spec["key"]}/build.log'
                    unit['complete'] = False
                else:
                    unit['base_path'] = spec['key'] + '/base.o'
            elif archive:
                result = subprocess.run(['mips-linux-gnu-ar', 'p', str(archive), spec['member']],
                                        cwd=ROOT, capture_output=True, check=True)
                if not result.stdout:
                    raise ValueError(f'missing archive member: {archive}/{spec["member"]}')
                (directory / 'base.o').write_bytes(result.stdout)
                unit['base_path'] = spec['key'] + '/base.o'
                # Canonical archive placement supplies the symbol-address mapping.
                # Names are mapped only at the identical within-object address.
                candidates = elf_text_symbols(directory / 'base.o')
                mappings = {}
                for name, symbol in target_symbols.items():
                    if name in candidates or not symbol['size']:
                        continue
                    names = [n for n, s in candidates.items() if s['address'] == symbol['address']
                             and s['size'] > 0 and not s['hidden']]
                    if len(names) == 1:
                        mappings[name] = names[0]
                unit['symbol_mappings'] = mappings
            files = [directory/'base.o'] if unit.get('base_path') else []
            unit['object_sha256'] = {p.name: hashlib.sha256(p.read_bytes()).hexdigest() for p in files}
            objdiff.write_json(cache, unit)
            return unit

    built = []
    with ThreadPoolExecutor(max_workers=4) as pool:
        futures = {pool.submit(build_unit, spec): spec for spec in specs}
        for future in as_completed(futures):
            spec = futures[future]
            try:
                built.append(future.result())
            except Exception as error:
                raise ValueError(f'{spec["key"]}: {error}; see {OUTPUT/spec["key"]}/build.log') from error
            if len(built) % 100 == 0 or len(built) == len(specs):
                print(f'objdiff report objects: {len(built)}/{len(specs)}', flush=True)
    built.sort(key=lambda u: u['key'])
    units = []
    for item in built:
        category = 'sdk' if item['kind'] == 'sdk' else 'project'
        metadata = {'complete': item.get('complete', False),
                    'progress_categories': [item['overlay'], category]}
        if item.get('source'):
            metadata['source_path'] = item['source']
        name = item.get('source', '').removeprefix('src/') or (
            f'{item["overlay"]}/sdk/{item["archive"]}/{item["member"]}' if item['kind'] == 'sdk'
            else f'{item["overlay"]}/unassigned/{item["start"]:06X}')
        unit = {'name': name, 'target_path': item['target_path'], 'metadata': metadata}
        for field in ('base_path', 'symbol_mappings'):
            if field in item:
                unit[field] = item[field]
        units.append(unit)
    coverage = {'scope': 'All US main/game CPU code ranges; data and RSP excluded',
                'mapped_code_bytes': sum(u['code_bytes'] for u in built),
                'expected_code_bytes': sum(u['report_code_bytes'] for u in built),
                'excluded_zero_bytes': sum(u['excluded_zero_bytes'] for u in built),
                'target_method': 'splat make_full_disasm_for_code',
                'target_verification': target_verification,
                'compile_errors': [u['compile_error'] for u in built if 'compile_error' in u],
                'units': built}
    objdiff.write_json(OUTPUT / 'coverage.json', coverage)
    objdiff.write_json(OUTPUT / 'objdiff.json', {'build_target': False, 'build_base': False,
        'units': units, 'progress_categories': [{'id': k, 'name': n} for k,n in
            [('main','Main executable'),('game','Game overlay'),('project','Project code'),('sdk','SDK libraries')]]})


def validate_report(report: dict, coverage: dict, config: dict) -> None:
    """Check each unit, not just a total where opposite errors could cancel."""
    if report.get('version') != 2:
        raise ValueError('unexpected objdiff report format version')
    planned = {u['name']: s['report_code_bytes'] for u, s in zip(config['units'], coverage['units'])}
    reported = {u['name']: int(u['measures'].get('total_code', 0)) for u in report['units']}
    if len(planned) != len(config['units']) or len(reported) != len(report['units']):
        raise ValueError('duplicate report unit names')
    if len(config['units']) != len(coverage['units']) or reported != planned:
        raise ValueError('objdiff unit coverage differs from the complete code plan')
    if int(report['measures'].get('total_code', 0)) != coverage['expected_code_bytes']:
        raise ValueError('objdiff total differs from audited target symbol denominator')
    if coverage['expected_code_bytes'] + coverage['excluded_zero_bytes'] != coverage['mapped_code_bytes']:
        raise ValueError('target symbols and verified zero gaps do not cover all mapped code')


def input_fingerprint() -> str:
    paths = []
    for directory in ('src', 'include', 'config', 'progress'):
        paths.extend(p for p in (ROOT / directory).rglob('*') if p.is_file())
    paths.extend([ROOT / 'Makefile', ROOT / 'toolchain/tools.lock.json', Path(__file__), ROOT / 'scripts/objdiff.py', ROOT / 'scripts/objdiff_targets.py',
                  ROOT / 'scripts/extract_game_code.py', ROOT / 'scripts/compile_c.py',
                  ROOT / 'scripts/normalize_asm.py', ROOT / 'scripts/conker.sh'])
    return digest_files(paths)


def generate(binary: Path) -> int:
    OUTPUT.mkdir(parents=True, exist_ok=True)
    for name in ('report.json', 'us_report.zip', 'validation.json'):
        (OUTPUT / name).unlink(missing_ok=True)
    before = input_fingerprint()
    revision = subprocess.check_output(['git','rev-parse','HEAD'], cwd=ROOT, text=True).strip()
    started = time.perf_counter()
    subprocess.run([str(ROOT / 'conker'), 'objdiff-report-prepare'], cwd=ROOT, check=True)
    prepared = time.perf_counter()
    subprocess.run([str(binary), 'report', 'generate', '-p', str(OUTPUT), '-o', str(OUTPUT/'report.json')],
                   cwd=ROOT, check=True)
    coverage = json.loads((OUTPUT / 'coverage.json').read_text())
    report = json.loads((OUTPUT / 'report.json').read_text())
    measured = int(report['measures'].get('total_code', 0))
    expected = coverage['expected_code_bytes']
    validate_report(report, coverage, json.loads((OUTPUT/'objdiff.json').read_text()))
    for unit in coverage['units']:
        if objdiff_targets.sha256(OUTPUT / unit['target_path']) != unit['target_sha256']:
            raise ValueError(f'validated target changed during report generation: {unit["key"]}')
    if before != input_fingerprint():
        raise ValueError('source inputs changed during report generation')
    # Round-trip through the native parser as an independent format smoke test.
    subprocess.run([str(binary), 'report', 'changes', str(OUTPUT/'report.json'), str(OUTPUT/'report.json'),
                    '-o', str(OUTPUT/'self-changes.json')], check=True, cwd=ROOT)
    with zipfile.ZipFile(OUTPUT/'us_report.zip', 'w', zipfile.ZIP_DEFLATED) as archive:
        archive.write(OUTPUT/'report.json', 'report.json')
    validation = {'git_revision': revision, 'source_fingerprint': before,
                  'scope': coverage['scope'], 'format_version': report['version'],
                  'expected_code_bytes': expected, 'reported_code_bytes': measured,
                  'mapped_code_bytes': coverage['mapped_code_bytes'],
                  'excluded_zero_bytes': coverage['excluded_zero_bytes'],
                  'per_unit_coverage_verified': True,
                  'target_method': coverage['target_method'],
                  'target_verification': coverage['target_verification'],
                  'data_coverage': 'Not measured; native 100% data fields have a zero denominator',
                  'report_sha256': hashlib.sha256((OUTPUT/'report.json').read_bytes()).hexdigest(),
                  'preparation_seconds': prepared-started, 'report_and_validation_seconds': time.perf_counter()-prepared,
                  'compile_errors': coverage['compile_errors'],
                  'existing_progress': json.loads((ROOT/'progress/summary.json').read_text())['code_bytes']['regions']['us'],
                  'measures': report['measures']}
    objdiff.write_json(OUTPUT/'validation.json', validation)
    print(json.dumps(validation, indent=2))
    print('Saved build/us/objdiff-report/report.json and us_report.zip (local only).')
    return 2 if coverage['compile_errors'] else 0


if __name__ == '__main__':
    if sys.argv[1:] != ['prepare']:
        raise SystemExit('Use ./conker objdiff report')
    prepare()
