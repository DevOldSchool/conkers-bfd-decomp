"""Resumable model exports and compact, evidence-scoped review queues."""
from __future__ import annotations

import argparse
from collections import Counter
from contextlib import contextmanager
import fcntl
import hashlib
import json
import os
from pathlib import Path
import signal
import subprocess
import sys
import time

try:
    from scripts.model_preview_evidence import preview_fingerprint
    from scripts.model_evidence_cache import source_identity
except ModuleNotFoundError:
    from model_preview_evidence import preview_fingerprint
    from model_evidence_cache import source_identity

ROOT = Path(__file__).resolve().parents[1]
BANKS = (1, 3, 4, 9)


def read(path):
    return json.loads(Path(path).read_text())


def identity(value):
    return hashlib.sha256(json.dumps(value, sort_keys=True, separators=(',', ':')).encode()).hexdigest()


def digest(path):
    with Path(path).open('rb') as stream:
        return hashlib.file_digest(stream, 'sha256').hexdigest()


def write(path, value):
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_name(path.name + '.tmp')
    temporary.write_text(json.dumps(value, indent=2, sort_keys=True) + '\n')
    os.replace(temporary, path)


def build_path(root, value):
    path = (root / value).resolve()
    if not path.is_relative_to((root / 'build/assets/models').resolve()) or path == (root / 'build/assets/models').resolve():
        raise ValueError('batch outputs must be below build/assets/models')
    return path


def tree_identity(path):
    path = Path(path)
    if not path.exists():
        return None
    if path.is_file():
        return digest(path)
    return identity({str(p.relative_to(path)): digest(p) for p in sorted(path.rglob('*'))
                     if p.is_file() and '__pycache__' not in p.parts})


def code_identity(root):
    return identity(source_identity(root, ['scripts/model_assets.py'], digest))


def test_inputs(root):
    # The full suite includes repository assertions as well as Python imports.
    # Reuse only when all of those source trees and the interpreter are stable.
    return {**{name: tree_identity(root / name) for name in
        ('scripts', 'tests', 'config', 'docs', 'src', 'include', 'progress', 'conker', 'CONTRIBUTING.md', 'AGENTS.md')},
        'python': digest(Path(sys.executable).resolve())}


def constructor_stage(root, config, output, state, banks, *, runner=None):
    summaries = {}
    for bank in banks:
        artifact = output / f'constructors-bank{bank:02}.json'
        stage(root, output, state, f'constructors-{bank:02}',
            ['./conker', 'model-assets', 'constructors', '--bank', f'{bank:02}',
             '--rom', config['rom'], '--output', str(artifact)],
            {'code': code_identity(root), 'rom': digest(root / config['rom']),
             'layout': tree_identity(root / 'config/rzip_layouts.json'),
             'launcher': tree_identity(root / 'conker')}, artifact, runner=runner or execute)
        result = read(artifact)
        summaries[str(bank)] = {'report': str(artifact.relative_to(root)), 'counts': result['counts'],
            'argument_counts': result['argument_analysis']['counts'], 'targets': result['target_queue']}
    return summaries


def model_key(bank, entry, segment):
    return f'{bank:02}:{entry:04}:{segment:02}'


def model_fingerprint(record, source):
    return identity({'record': record, 'source': preview_fingerprint(source)})


def missing_material(run):
    if not run['face_count'] or run.get('texture') or run['status'] == 'untextured':
        return False
    formula = run.get('combine_formula')
    # Missing combine state is uncertainty, not proof that a draw is untextured.
    return formula is None or bool(set(formula['inputs']) & {'TEXEL0', 'TEXEL1'})


def scan(root, config, reviews, investigations):
    root = Path(root).resolve()
    validation = read(root / config['validation_config'])
    inspection = read(root / config['inspection_config'])
    cases = {r['id']: r for r in validation['render_cases']}
    canonical = build_path(root, config['rom_root'])
    rows, rom_hashes = [], set()
    for bank in BANKS:
        directory = canonical / f'us-bank-{bank:02}-preview'
        manifest = read(directory / 'manifest.json')
        if manifest['bank_index'] != bank or manifest.get('runtime_material_manifest') is not None:
            raise ValueError(f'not a ROM-only bank-{bank:02} corpus')
        rom_hashes.add(manifest['normalized_sha1'])
        for record in manifest['models']:
            key = model_key(bank, record['bank_entry'], record['segment'])
            if any(r.get('runtime_material') for r in record['material_runs']):
                raise ValueError(f'captured material in ROM-only corpus: {key}')
            source = (directory / record['gltf_file']).resolve()
            if not source.is_relative_to(directory.resolve()):
                raise ValueError(f'preview source escapes corpus: {key}')
            missing = [r for r in record['material_runs'] if missing_material(r)]
            fingerprint = model_fingerprint(record, source)
            decision = reviews.get(key)
            current = decision and decision['fingerprint'] == fingerprint
            state = ('no-drawable-geometry' if not record['face_count'] else
                     'material-blocked' if missing else
                     decision['decision'] if current else 'review-needed')
            rows.append({'key': key, 'bank': bank, 'entry': record['bank_entry'],
                         'segment': record['segment'], 'source': str(source.relative_to(root)),
                         'faces': record['face_count'], 'fingerprint': fingerprint, 'status': state,
                         'review_stale': bool(decision and not current),
                         'review_reason': decision['reason'] if decision else None,
                         'missing_faces': sum(r['face_count'] for r in missing),
                         'blockers': dict(Counter(r['status'] for r in missing)),
                         'blocker_faces': {status: sum(r['face_count'] for r in missing if r['status'] == status)
                                           for status in {r['status'] for r in missing}}})
    if len(rom_hashes) != 1 or len({r['key'] for r in rows}) != len(rows):
        raise ValueError('duplicate model identities or mixed ROMs')
    published, manifests, assemblies = set(), {}, []
    # A set contains every scene's components: recompose it once per read phase,
    # not once for every gallery card. Never retain evidence across scans.
    assembly_cache, assembly_sources = {}, []
    keys = {r["key"] for r in rows}
    for case in inspection['models']:
        path = Path(cases[case['render_case']]['source'])
        # Match the actual source manifest identity, including legacy bind sources.
        manifest_path = root / path.parent.parent / 'manifest.json'
        if manifest_path not in manifests:
            manifests[manifest_path] = read(manifest_path)
        manifest = manifests[manifest_path]
        if manifest.get('family') == 'rom-static-scene-assemblies':
            try:
                from scripts.model_scene_assemblies import inspection_evidence
            except ModuleNotFoundError:
                from model_scene_assemblies import inspection_evidence
            source = (root / path).resolve()
            evidence = inspection_evidence(source, verification_cache=assembly_cache)
            if manifest['normalized_sha1'] not in rom_hashes:
                raise ValueError(f'assembly belongs to another ROM: {path}')
            assemblies.append({'name': case['name'], 'scene_index': evidence['scene_index']})
            assembly_sources.append((source, evidence))
            continue
        record = next((r for r in manifest['models'] if path.name in
                       (Path(r['gltf_file']).name, Path(r.get('bind_gltf_file') or '').name)), None)
        if record is None or manifest['normalized_sha1'] not in rom_hashes:
            raise ValueError(f'unknown gallery source: {path}')
        key = model_key(manifest['bank_index'], record['bank_entry'], record['segment'])
        if key in published or key not in keys:
            raise ValueError(f'duplicate or unknown gallery model: {key}')
        published.add(key)
    grouped = {}
    for row in rows:
        if row['key'] in published:
            row['status'] = 'published'
            continue
        for blocker in row['blockers']:
            grouped.setdefault(blocker, []).append(row)
    code = code_identity(root)
    groups = []
    for blocker, members in grouped.items():
        members.sort(key=lambda r: (-r['blocker_faces'][blocker], r['key']))
        fingerprint = identity({'code': code, 'members': [(r['key'], r['fingerprint']) for r in members]})
        previous = investigations.get(blocker)
        held = bool(previous and previous['fingerprint'] == fingerprint)
        groups.append({'blocker': blocker, 'model_count': len(members),
                       'affected_faces': sum(r['blocker_faces'][blocker] for r in members),
                       'representative': members[0]['key'], 'models': [r['key'] for r in members],
                       'fingerprint': fingerprint, 'status': 'deferred' if held else 'investigate',
                       'reason': previous['reason'] if previous else None})
    groups.sort(key=lambda r: (r['status'] == 'deferred', -r['model_count'], -r['affected_faces'], r['blocker']))
    # Independent final phase catches component, selection and output changes
    # after the first card was checked, including changes without a new manifest.
    assembly_cache = {}
    for source, evidence in assembly_sources:
        if inspection_evidence(source, verification_cache=assembly_cache) != evidence:
            raise ValueError('scene assembly changed during batch scan')
    return {'schema_version': 1, 'normalized_sha1': next(iter(rom_hashes)),
            'published_scene_assemblies': assemblies,
            'counts': dict(Counter(r['status'] for r in rows)), 'models': rows, 'groups': groups,
            'scope': 'Manifest/source triage, not a fresh ROM extraction or native appearance proof. '
                     'Groups may overlap and do not establish a shared runtime consumer.'}


@contextmanager
def lock(output):
    output.mkdir(parents=True, exist_ok=True)
    with (output / '.model-batch.lock').open('a') as stream:
        try:
            fcntl.flock(stream, fcntl.LOCK_EX | fcntl.LOCK_NB)
        except BlockingIOError as error:
            raise ValueError('another model batch is using this checkout') from error
        yield


def execute(command, root, log):
    with log.open('w') as stream:
        child = subprocess.Popen(command, cwd=root, stdout=stream, stderr=subprocess.STDOUT,
                                 start_new_session=True)
        try:
            return child.wait()
        except KeyboardInterrupt:
            os.killpg(child.pid, signal.SIGTERM)
            try:
                child.wait(timeout=5)
            except subprocess.TimeoutExpired:
                os.killpg(child.pid, signal.SIGKILL)
                child.wait()
            raise


def stage(root, output, state, name, command, inputs, artifact=None, *, reusable=True, runner=execute):
    key = identity({'command': command, 'inputs': inputs})
    old = state.setdefault('stages', {}).get(name, {})
    if (reusable and old.get('status') == 'passed' and old.get('input') == key
            and (artifact is None or (artifact.exists() and old.get('output') == tree_identity(artifact)))):
        print(f'{name}: unchanged', flush=True)
        return
    log = output / 'logs' / (name + '.log')
    log.parent.mkdir(parents=True, exist_ok=True)
    record = {'status': 'running', 'input': key, 'command': command,
              'log': str(log.relative_to(root)), 'started_at': time.time()}
    state['stages'][name] = record
    write(output / 'state.json', state)
    print(f'{name}: running; log {record["log"]}', flush=True)
    try:
        result = runner(command, root, log)
        if result:
            raise ValueError(f'{name} failed ({result}); see {record["log"]}')
        if artifact is not None and not artifact.exists():
            raise ValueError(f'{name} did not produce {artifact}')
        record.update(status='passed', output=tree_identity(artifact) if artifact is not None else None)
    except BaseException as error:
        record.update(status='interrupted' if isinstance(error, KeyboardInterrupt) else 'failed', error=str(error))
        raise
    finally:
        record['finished_at'] = time.time()
        write(output / 'state.json', state)


def render_exceptions(report):
    return {r['id']: r['check'].get('current_sha256') for r in report.get('renders', [])
            if r.get('check', {}).get('status') != 'passed'}


def run(root, config, output, state, banks, blender=None, *, runner=execute):
    command = ['./conker', 'model-assets']
    common = {'code': code_identity(root), 'rom': digest(root / config['rom']),
              'layout': tree_identity(root / 'config/rzip_layouts.json'),
              'launcher': tree_identity(root / 'conker'),
              'textures': tree_identity(root / config['textures'])}
    report_path = root / read(root / config['inspection_config'])['validation_report']
    if report_path.name != 'report.json':
        raise ValueError('inspection validation_report must name report.json')
    if 'baseline_render_exceptions' not in state:
        previous = read(report_path) if report_path.is_file() else {}
        if previous and not previous.get('summary', {}).get('completed'):
            raise ValueError('previous validation is unfinished; complete it before establishing the batch baseline')
        state['baseline_render_exceptions'] = render_exceptions(previous)
        write(output / 'state.json', state)
    stage(root, output, state, 'tests', [sys.executable, '-m', 'unittest', 'discover', '-s', 'tests'],
          test_inputs(root), runner=runner)
    for bank in banks:
        stage(root, output, state, f'verify-{bank:02}', command + ['verify', '--bank', f'{bank:02}', '--rom', config['rom']], common, runner=runner)
        for corpus in config['corpora']:
            destination = build_path(root, str(Path(corpus['root']) / f'us-bank-{bank:02}-preview'))
            args = command + ['preview', '--bank', f'{bank:02}', '--rom', config['rom'],
                              '--textures', config['textures'], '--output', str(destination), '--force']
            dependencies = dict(common)
            if corpus.get('runtime_materials'):
                args += ['--runtime-materials', corpus['runtime_materials']]
                dependencies['materials'] = tree_identity((root / corpus['runtime_materials']).parent)
            elif bank == 1 and corpus.get('rom_defaults'):
                args += ['--rom-defaults']
            stage(root, output, state, f'preview-{corpus["name"]}-{bank:02}', args, dependencies,
                  destination, runner=runner)
    # Assembly provenance includes component manifest hashes. Refresh it after
    # bank exports, even when unchanged geometry can reuse its render cache.
    for directory in read(root / config['validation_config']).get('scene_assemblies', []):
        destination = build_path(root, directory)
        stage(root, output, state, 'scene-assemblies-' + destination.name,
              command + ['scene-assemblies', '--rom', config['rom'],
                         '--model-root', config['rom_root'], '--output', str(destination)],
              {}, destination, reusable=False, runner=runner)
    # The authoritative validator owns dependency/tool caches. Always call it:
    # an outer cache cannot safely infer all capture, composition or Blender inputs.
    args = command + ['validate', '--validation-config', config['validation_config'],
                      '--output', str(report_path.parent)]
    if blender:
        args += ['--blender', str(blender)]
    stage(root, output, state, 'validate', args, {}, reusable=False, runner=runner)
    report = read(report_path)
    if not report.get('summary', {}).get('completed') or report.get('status') == 'failed':
        raise ValueError('validation did not complete successfully; gallery not refreshed')
    exceptions = render_exceptions(report)
    changed = {k: v for k, v in exceptions.items() if k not in state['baseline_render_exceptions']
               or state['baseline_render_exceptions'][k] != v}
    if changed:
        write(output / 'render-review.json', {'status': 'review-needed', 'renders': changed})
        raise ValueError('changed render exceptions need review; gallery not refreshed (render-review.json)')
    stage(root, output, state, 'inspect', command + ['inspect', '--inspection-config', config['inspection_config']],
          {}, reusable=False, runner=runner)
    write(output / 'render-review.json', {'status': 'unchanged-exceptions', 'renders': exceptions})
    # A resolved exception must not become a permanent allowance for regression.
    state['baseline_render_exceptions'] = exceptions
    write(output / 'state.json', state)


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--batch-config', type=Path, default=ROOT / 'config/model-batch.json')
    parser.add_argument('--output', type=Path, default=ROOT / 'build/assets/models/batch')
    parser.add_argument('--run', action='store_true', help='verify and refresh selected banks, validate, then refresh approved gallery entries')
    parser.add_argument('--constructors', action='store_true', help='resume ROM constructor argument analysis in the batch journal')
    parser.add_argument('--bank', choices=['01', '03', '04', '09'], action='append', help='bank to refresh (repeatable; default all four)')
    parser.add_argument('--blender', type=Path)
    decision = parser.add_mutually_exclusive_group()
    decision.add_argument('--defer-model', metavar='BANK:ENTRY:SEGMENT')
    decision.add_argument('--defer-group', metavar='BLOCKER')
    decision.add_argument('--reopen-group', metavar='BLOCKER')
    parser.add_argument('--reason')
    args = parser.parse_args(argv)
    if args.bank and not (args.run or args.constructors):
        parser.error('--bank applies only to --run or --constructors')
    if args.run and (args.defer_model or args.defer_group or args.reopen_group):
        parser.error('record review decisions separately from --run')
    if (args.defer_model or args.defer_group) and not (args.reason and args.reason.strip()):
        parser.error('deferrals require --reason')
    try:
        config = read(args.batch_config)
        if config.get('schema_version') != 1:
            raise ValueError('unsupported model batch configuration')
        names = [c['name'] for c in config['corpora']]
        if len(set(names)) != len(names) or any(not n or not all(c.isalnum() or c == '-' for c in n) for n in names):
            raise ValueError('invalid or duplicate corpus names')
        if len({c['root'] for c in config['corpora']}) != len(names):
            raise ValueError('duplicate corpus output roots')
        if not any(c['root'] == config['rom_root'] and c.get('rom_defaults')
                   and not c.get('runtime_materials') for c in config['corpora']):
            raise ValueError('batch requires a ROM-only corpus with character defaults')
        output = build_path(ROOT, args.output)
        with lock(ROOT / "build/assets/models"):
            state = read(output / 'state.json') if (output / 'state.json').exists() else {'schema_version': 1}
            reviews_path = ROOT / config['reviews']
            reviews = read(reviews_path)['models']
            investigations = state.setdefault('investigations', {})
            if args.reopen_group:
                investigations.pop(args.reopen_group, None)
            if args.run:
                run(ROOT, config, output, state, sorted({int(b) for b in args.bank}) if args.bank else BANKS, args.blender)
            if args.constructors:
                state['constructors'] = constructor_stage(ROOT, config, output, state,
                    sorted({int(b) for b in args.bank}) if args.bank else (9,))
            report = scan(ROOT, config, reviews, investigations)
            if args.defer_model:
                row = next((r for r in report['models'] if r['key'] == args.defer_model), None)
                if row is None or row['status'] != 'review-needed':
                    raise ValueError('defer-model requires an unpublished model currently needing visual review')
                reviews[row['key']] = {'fingerprint': row['fingerprint'], 'decision': 'review-deferred', 'reason': args.reason}
                write(reviews_path, {'schema_version': 1, 'models': reviews})
            if args.defer_group:
                group = next((r for r in report['groups'] if r['blocker'] == args.defer_group), None)
                if group is None:
                    raise ValueError('unknown blocker group')
                investigations[group['blocker']] = {'fingerprint': group['fingerprint'], 'reason': args.reason}
            report = scan(ROOT, config, reviews, investigations) if args.defer_group or args.defer_model else report
            report['constructors'] = state.get('constructors', {})
            write(output / 'state.json', state)
            write(output / 'report.json', report)
            write(output / 'review-needed.json', [r for r in report['models'] if r['status'] == 'review-needed'])
            print('Models: ' + ', '.join(f'{k}={v}' for k, v in sorted(report['counts'].items())))
            for group in report['groups'][:8]:
                print(f"{group['blocker']}: {group['model_count']} models; example {group['representative']}; {group['status']}")
            print(f'Report: {output.relative_to(ROOT)}/report.json')
        return 0
    except KeyboardInterrupt:
        print('Model batch interrupted; completed export steps are resumable.', file=sys.stderr)
        return 130
    except (OSError, ValueError, KeyError, TypeError) as error:
        print(f'Model batch: {error}', file=sys.stderr)
        return 1


if __name__ == '__main__':
    raise SystemExit(main())
