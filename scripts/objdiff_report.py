#!/usr/bin/env python3
"""Build a US CPU-code and initialized-data project for native objdiff report generation.

References come from independently assembled splat full-disassembly units.
Their linked code bytes must reproduce the original US CPU-code ranges. Missing implementations stay
in the denominator. The rebuilt font is included; other stored assets, BSS and RSP are excluded.
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

from profile_config import load_profile

import compile_c
import data_boundaries
import diff
import main_private_data
import objdiff
import objdiff_data_targets
import objdiff_snapshot
import objdiff_ownership
import objdiff_targets
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
    for overlay in state.OVERLAYS:
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


def prepare_data() -> tuple[list[dict], list[dict], dict]:
    """Prepare initialized CPU data directly for the artifact CI publishes.

    Independently linked references cover all loaded initialized data.
    Separate data units preserve the existing code denominator.
    Native perfect matches are measured; placement alone grants no completion.
    """
    directory = OUTPUT / 'data'
    directory.mkdir(parents=True, exist_ok=True)
    audit = data_boundaries.audit(ROOT)
    rom = main_private_data.validated_rom(ROOT)
    built, proofs = [], {}
    for overlay in state.OVERLAYS:
        current, proofs[overlay] = objdiff_data_targets.prepare_targets(
            audit['images'][overlay], rom, overlay=overlay, output=directory)
        built.extend(current)
    config = objdiff_data_targets.prepare_candidates(built, output=directory)
    for item, unit in zip(config, built, strict=True):
        unit.update(key='data/' + unit['key'], report_code_bytes=0,
                    report_data_bytes=unit['size'])
        for field in ('target_path', 'base_path'):
            if field in unit:
                unit[field] = 'data/' + unit[field]
                item[field] = unit[field]
        if unit.get('compile_error'):
            unit['compile_error'] = 'data/' + unit['compile_error']
        item['metadata']['progress_categories'] = [unit['overlay'], 'data']
        if unit.get('source'):
            item['metadata']['source_path'] = unit['source']
    return built, config, {
        'expected_data_bytes': sum(i['loaded_bytes'] for i in audit['images'].values()),
        'mapped_data_bytes': sum(i['mapped_bytes'] for i in audit['images'].values()),
        'unassigned_data_bytes': sum(i['unassigned_bytes'] for i in audit['images'].values()),
        'data_target_verification': proofs,
        'data_rom_sha1': audit['rom_sha1'],
    }


def prepare_font() -> tuple[dict, dict]:
    """Credit the editable font only when the actual ROM build input matches."""
    rom = main_private_data.validated_rom(ROOT)
    unit, item = objdiff_data_targets.prepare_font(rom, output=OUTPUT)
    profile = load_profile(ROOT / 'config/profiles/us.yaml')
    segments = profile['segments']
    index = next(i for i, s in enumerate(segments) if isinstance(s, dict) and s.get('name') == 'font_rle')
    following = segments[index + 1]
    end = following['start'] if isinstance(following, dict) else following[0]
    if (segments[index]['type'] != 'group' or segments[index]['start'] != unit['rom_start']
            or end != unit['rom_end']):
        raise ValueError('font report range differs from canonical YAML build placement')
    unit.update(report_code_bytes=0, report_data_bytes=unit['size'],
                complete=unit['literal_payload_matches_rom'])
    item['metadata']['complete'] = unit['complete']
    item['metadata']['progress_categories'] = ['data']
    return unit, item


def prepare() -> None:
    OUTPUT.mkdir(parents=True, exist_ok=True)
    for name in ('objdiff.json', 'coverage.json'):
        (OUTPUT / name).unlink(missing_ok=True)
    specs = plan()
    targets, target_verification = objdiff_targets.prepare(specs, OUTPUT)
    linked = {overlay: (OUTPUT / 'targets' / overlay / 'targets.bin').read_bytes()
              for overlay in state.OVERLAYS}
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
            libdir = 'build/game-libs/us' if spec['overlay'] == 'game' else 'build/us/lib'
            archive = ROOT / libdir / (spec['archive'] + '.a')
        digest = hashlib.sha256((common + target['sha256'] + json.dumps(spec, sort_keys=True)).encode())
        if base_source:
            digest.update(base_source.read_bytes())
        if archive:
            digest.update(archive.read_bytes())
        linked_object = None
        if base_source and spec.get('complete') and not compile_c.GLOBAL_ASM_PRAGMA.search(base_source.read_text()):
            prefix = 'build/game-integrated/us/' if spec['overlay'] == 'game' else 'build/us/'
            linked_object = ROOT / (prefix + spec['source'].removesuffix('.c') + '.o')
            with (directory / 'linked-build.log').open('w') as log:
                subprocess.run(['make', '--silent', str(linked_object.relative_to(ROOT)), 'PROFILE=us'],
                               cwd=ROOT, stdout=log, stderr=log, check=True)
            digest.update(linked_object.read_bytes())
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
            if linked_object:
                (directory / 'base.o').write_bytes(linked_object.read_bytes())
                unit['base_path'] = spec['key'] + '/base.o'
                unit['linked_inputs'] = {linked_object.relative_to(ROOT).as_posix(): objdiff_targets.sha256(linked_object)}
                unit['candidate_origin'] = 'actual_build_object'
            elif base_source:
                unit['candidate_origin'] = 'C_only_assembly_excluded'
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
    data_built, data_config, data_coverage = prepare_data()
    font, font_config = prepare_font()
    data_built.append(font)
    data_config.append(font_config)
    data_coverage['loaded_data_bytes'] = data_coverage.get('expected_data_bytes', 0)
    data_coverage['expected_data_bytes'] = data_coverage.get('expected_data_bytes', 0) + font['size']
    data_coverage['mapped_data_bytes'] = data_coverage.get('mapped_data_bytes', 0) + font['size']
    data_coverage['stored_asset_bytes'] = font['size']
    grouped, grouped_config = objdiff_ownership.group_units(built + data_built, units + data_config, ROOT, OUTPUT)
    coverage = {'scope': 'US main/game/debugger CPU code, initialized data and rebuilt font; other assets, BSS and RSP excluded',
                'mapped_code_bytes': sum(u['code_bytes'] for u in built),
                'expected_code_bytes': sum(u['report_code_bytes'] for u in built),
                'excluded_zero_bytes': sum(u['excluded_zero_bytes'] for u in built),
                'target_method': 'splat make_full_disasm_for_code',
                'target_verification': target_verification,
                'compile_errors': [u['compile_error'] for u in built + data_built if 'compile_error' in u]
                    + [u['key'] + ': ' + u['candidate_error'] for u in data_built if u.get('candidate_error')],
                'units': grouped, **data_coverage}
    objdiff.write_json(OUTPUT / 'coverage.json', coverage)
    objdiff.write_json(OUTPUT / 'objdiff.json', {'build_target': False, 'build_base': False,
        'units': grouped_config, 'progress_categories': [{'id': k, 'name': n} for k,n in
            [('main','Main executable'),('game','Game overlay'),('debugger','Debugger overlay'),
             ('project','Project code'),('sdk','SDK libraries'),('data','Data')]]})


def validate_report(report: dict, coverage: dict, config: dict, *,
                    require_matched_completion: bool = True) -> None:
    """Check each unit, not just a total where opposite errors could cancel."""
    if report.get('version') != 2:
        raise ValueError('unexpected objdiff report format version')
    planned = {u['name']: (s['report_code_bytes'], s.get('report_data_bytes', 0))
               for u, s in zip(config['units'], coverage['units'])}
    reported = {u['name']: (int(u['measures'].get('total_code', 0)),
                             int(u['measures'].get('total_data', 0))) for u in report['units']}
    if len(planned) != len(config['units']) or len(reported) != len(report['units']):
        raise ValueError('duplicate report unit names')
    if len(config['units']) != len(coverage['units']) or reported != planned:
        raise ValueError('objdiff unit coverage differs from the complete code/data plan')
    if int(report['measures'].get('total_code', 0)) != coverage['expected_code_bytes']:
        raise ValueError('objdiff total differs from audited target symbol denominator')
    if coverage['expected_code_bytes'] + coverage['excluded_zero_bytes'] != coverage['mapped_code_bytes']:
        raise ValueError('target symbols and verified zero gaps do not cover all mapped code')

    data_total = coverage.get('expected_data_bytes', 0)
    if (int(report['measures'].get('total_data', 0)) != data_total
            or sum(size[1] for size in planned.values()) != data_total
            or coverage.get('mapped_data_bytes', 0) + coverage.get('unassigned_data_bytes', 0) != data_total):
        raise ValueError('native data total differs from audited initialized images')
    by_name = {u['name']: u['measures'] for u in report['units']}
    for item, spec in zip(config['units'], coverage['units']):
        measures = by_name[item['name']]
        total = spec.get('report_data_bytes', 0)
        matched = int(measures.get('matched_data', 0))
        if not 0 <= matched <= total or (not item.get('base_path') and matched):
            raise ValueError('data without a matching candidate earned native credit')
        complete = bool(item.get('metadata', {}).get('complete'))
        expected_complete = total if spec.get('complete') else 0
        if total and complete:
            if require_matched_completion and matched != total:
                raise ValueError('fully linked data must be natively matched in every unit')
            if not ((spec.get('data_completion_verified') and spec.get('linked_inputs')) or
                    (spec.get('kind') == 'rebuilt_asset' and spec.get('complete')
                    and spec.get('literal_payload_matches_rom') is True
                    and spec.get('source_inputs') and spec.get('linked_inputs')
                    and spec.get('target_verification', {}).get('matches_original') is True)):
                raise ValueError('data placement cannot award fully linked completion')
        if total and (complete != bool(expected_complete)
                      or int(measures.get('complete_data', 0)) != expected_complete):
            raise ValueError('data placement cannot award fully linked completion')
    for field in ('matched_data', 'complete_data'):
        if int(report['measures'].get(field, 0)) != sum(int(m.get(field, 0)) for m in by_name.values()):
            raise ValueError('native data measures do not reconcile')


def qualify_data_completion(report: dict, coverage: dict, config: dict) -> list[dict]:
    """Remove build-eligible completion when native data symbols do not all match.

    Change only generation inputs. A subsequent native pass calculates all final
    completion measures, including code completion for the affected whole units.
    """
    validate_report(report, coverage, config, require_matched_completion=False)
    measures = {unit['name']: unit['measures'] for unit in report['units']}
    downgraded = []
    for item, spec in zip(config['units'], coverage['units'], strict=True):
        total = spec.get('report_data_bytes', 0)
        matched = int(measures[item['name']].get('matched_data', 0))
        if total and spec.get('complete') and matched != total:
            spec['complete'] = False
            spec['completion_reason'] = 'Linked data is not fully matched by native objdiff'
            item['metadata']['complete'] = False
            downgraded.append({'name': item['name'], 'data_bytes': total,
                               'matched_data_bytes': matched,
                               'code_bytes': spec['report_code_bytes']})
    return downgraded


def input_fingerprint() -> str:
    return objdiff_snapshot.input_fingerprint(ROOT)


def generate(binary: Path) -> int:
    OUTPUT.mkdir(parents=True, exist_ok=True)
    for name in ('report.json', 'us_report.zip', 'validation.json'):
        (OUTPUT / name).unlink(missing_ok=True)
    before = input_fingerprint()
    revision = subprocess.check_output(['git','rev-parse','HEAD'], cwd=ROOT, text=True).strip()
    source_dirty = bool(objdiff_snapshot.git(ROOT, 'status', '--porcelain', '--untracked-files=normal',
                                             '--', *objdiff_snapshot.INPUTS))
    started = time.perf_counter()
    subprocess.run([str(ROOT / 'conker'), 'objdiff-report-prepare'], cwd=ROOT, check=True)
    prepared = time.perf_counter()
    subprocess.run([str(binary), 'report', 'generate', '-p', str(OUTPUT), '-o', str(OUTPUT/'report.json')],
                   cwd=ROOT, check=True)
    coverage = json.loads((OUTPUT / 'coverage.json').read_text())
    report = json.loads((OUTPUT / 'report.json').read_text())
    config = json.loads((OUTPUT / 'objdiff.json').read_text())
    completion_downgrades = qualify_data_completion(report, coverage, config)
    if completion_downgrades:
        objdiff.write_json(OUTPUT / 'coverage.json', coverage)
        objdiff.write_json(OUTPUT / 'objdiff.json', config)
        subprocess.run([str(binary), 'report', 'generate', '-p', str(OUTPUT),
                        '-o', str(OUTPUT / 'report.json')], cwd=ROOT, check=True)
        final_report = json.loads((OUTPUT / 'report.json').read_text())
        fields = ('total_code', 'matched_code', 'total_data', 'matched_data')
        def matches(document):
            return {unit['name']: tuple(int(unit['measures'].get(k, 0)) for k in fields)
                    for unit in document['units']}
        if matches(report) != matches(final_report):
            raise ValueError('native matching changed while qualifying completion')
        report = final_report
    measured = int(report['measures'].get('total_code', 0))
    expected = coverage['expected_code_bytes']
    validate_report(report, coverage, config)
    for unit in coverage['units']:
        for path, digest in (unit.get('source_inputs', {}) | unit.get('linked_inputs', {})).items():
            if objdiff_targets.sha256(ROOT / path) != digest:
                raise ValueError('source or ROM build input changed during report generation: ' + path)
        if objdiff_targets.sha256(OUTPUT / unit['target_path']) != unit['target_sha256']:
            raise ValueError(f'validated target changed during report generation: {unit["key"]}')
        if unit.get('base_path'):
            digest = unit.get('base_sha256') or unit['object_sha256']['base.o']
            if objdiff_targets.sha256(OUTPUT / unit['base_path']) != digest:
                raise ValueError(f'validated base changed during report generation: {unit["key"]}')
    if (before != input_fingerprint()
            or revision != subprocess.check_output(['git', 'rev-parse', 'HEAD'], cwd=ROOT, text=True).strip()):
        raise ValueError('source inputs changed during report generation')
    # Round-trip through the native parser as an independent format smoke test.
    subprocess.run([str(binary), 'report', 'changes', str(OUTPUT/'report.json'), str(OUTPUT/'report.json'),
                    '-o', str(OUTPUT/'self-changes.json')], check=True, cwd=ROOT)
    with zipfile.ZipFile(OUTPUT/'us_report.zip', 'w', zipfile.ZIP_DEFLATED) as archive:
        archive.write(OUTPUT/'report.json', 'report.json')
    validation = {'snapshot_schema': 1, 'profile': 'us', 'source_dirty': source_dirty,
                  'git_revision': revision, 'source_fingerprint': before,
                  'scope': coverage['scope'], 'format_version': report['version'],
                  'expected_code_bytes': expected, 'reported_code_bytes': measured,
                  'mapped_code_bytes': coverage['mapped_code_bytes'],
                  'excluded_zero_bytes': coverage['excluded_zero_bytes'],
                  'per_unit_coverage_verified': True,
                  'target_method': coverage['target_method'],
                  'target_verification': coverage['target_verification'],
                  'expected_data_bytes': coverage.get('expected_data_bytes', 0),
                  'reported_data_bytes': int(report['measures'].get('total_data', 0)),
                  'data_target_verification': coverage.get('data_target_verification', {}),
                  'loaded_data_bytes': coverage.get('loaded_data_bytes', 0),
                  'stored_asset_bytes': coverage.get('stored_asset_bytes', 0),
                  'data_coverage': 'Initialized CPU data plus rebuilt font; font completion requires exact current ROM build input',
                  'asset_verification': {u['key']: {k: u[k] for k in (
                      'literal_payload_matches_rom', 'source_inputs', 'linked_inputs', 'target_verification')}
                      for u in coverage['units'] if u.get('kind') == 'rebuilt_asset'},
                  'report_sha256': hashlib.sha256((OUTPUT/'report.json').read_bytes()).hexdigest(),
                  'preparation_seconds': prepared-started, 'report_and_validation_seconds': time.perf_counter()-prepared,
                  'completion_downgrades': completion_downgrades,
                  'compile_errors': coverage['compile_errors'],
                  'existing_progress': state.summary(state.validate_project()[1])['code_bytes']['regions']['us'],
                  'measures': report['measures']}
    objdiff.write_json(OUTPUT/'validation.json', validation)
    print(json.dumps(validation, indent=2))
    print('Saved build/us/objdiff-report/report.json and us_report.zip (local only).')
    return 2 if coverage['compile_errors'] else 0


if __name__ == '__main__':
    if sys.argv[1:] != ['prepare']:
        raise SystemExit('Use ./conker objdiff report')
    prepare()
