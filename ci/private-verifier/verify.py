#!/usr/bin/env python3
"""Private-only coordinator. Never run this workflow from the public repository.

Only the pinned project snapshot supplies executable build tooling. Candidate
source/data are handled inside an offline disposable container. No container
output becomes a GitHub workflow command, public log, or public artifact.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import os
from pathlib import Path, PurePosixPath
import re
import subprocess
import tempfile
import urllib.request
import uuid

REPOSITORY = 'DevOldSchool/conkers-bfd-decomp'
ULTRALIB = 'https://github.com/DevOldSchool/ultralib.git'
SHA = re.compile(r'[0-9a-f]{40}')
SAFE_PATH = re.compile(r'[A-Za-z0-9_./+-]+')
DATA_FILES = {'progress/functions.json', 'progress/source_units.json', 'progress/summary.json',
              'progress/badge-us.json', 'progress/badge-eu.json', 'docs/progress.md'}
# Layout changes are build-control changes and require trusted-tooling promotion.
# Source-only matching/deferred work does not change these files.


def checked_sha(value):
    if not SHA.fullmatch(value):
        raise ValueError('Expected a full lowercase commit SHA')
    return value


def api(path):
    request = urllib.request.Request('https://api.github.com/' + path,
                                    headers={'Accept': 'application/vnd.github+json', 'User-Agent': 'conker-verifier'})
    with urllib.request.urlopen(request, timeout=30) as response:
        return json.load(response)


def resolve(pr, head, base):
    checked_sha(head); checked_sha(base)
    if not isinstance(pr, int) or pr < 1:
        raise ValueError('Invalid PR number')
    data = api(f'repos/{REPOSITORY}/pulls/{pr}')
    if (data['state'] != 'open' or data['base']['repo']['full_name'] != REPOSITORY
            or data['base']['ref'] != 'main' or data['head']['sha'] != head or data['base']['sha'] != base):
        raise ValueError('Approval no longer describes the open PR and current base')
    merge = checked_sha(api(f'repos/{REPOSITORY}/git/ref/pull/{pr}/merge')['object']['sha'])
    parents = api(f'repos/{REPOSITORY}/git/commits/{merge}')['parents']
    if [p['sha'] for p in parents] != [base, head]:
        raise ValueError('Merge revision does not have the approved parents')
    return {'pr': pr, 'head': head, 'base': base, 'merge': merge}


def run(command, **kwargs):
    return subprocess.run(command, check=True, **kwargs)


def git(repo, *args):
    return subprocess.check_output(['git', '-c', 'core.hooksPath=/dev/null', '-C', str(repo), *args])


def fetch(repo, url, refs):
    repo.mkdir(parents=True, exist_ok=True)
    run(['git', 'init', '-q', str(repo)])
    run(['git', '-C', str(repo), 'fetch', '--quiet', '--no-tags', '--depth=1', url, *refs])


def tree(repo, revision):
    result = {}
    for entry in git(repo, 'ls-tree', '-rz', revision).split(b'\0'):
        if not entry:
            continue
        header, raw_path = entry.split(b'\t', 1)
        mode, kind, oid = header.decode().split()
        path = raw_path.decode('utf-8')
        parts = PurePosixPath(path).parts
        if (not SAFE_PATH.fullmatch(path) or path.startswith('/') or '..' in parts
                or '.git' in parts or mode not in {'100644', '100755', '160000'}):
            raise ValueError('Unsupported repository path or file mode')
        result[path] = (mode, kind, oid)
    return result


def allowed_change(path):
    return ((path.startswith('src/') and path.endswith(('.c', '.h')))
            or (path.startswith('include/') and path.endswith('.h'))
            or path in DATA_FILES or path.endswith('.md') and (path.startswith('docs/') or '/' not in path)
            or path.startswith('tests/') and path.endswith('.py'))


def enforce_policy(trusted, candidate):
    blocked = [path for path in sorted(trusted.keys() | candidate.keys())
               if trusted.get(path) != candidate.get(path) and not allowed_change(path)]
    if blocked:
        raise ValueError('Trusted-tooling review required for: ' + ', '.join(blocked))


def registration_contract(document, *, units=False):
    """Progress may change; independently reviewed reference boundaries may not."""
    entries = document['source_units' if units else 'functions']
    result = {}
    for entry in entries:
        key = entry['source' if units else 'symbol']
        if key in result:
            raise ValueError('Duplicate reference registration')
        stable = {k: v for k, v in entry.items()
                  if k not in {'regions', 'deferred', 'original_asm'}}
        stable['regions'] = {
            profile: {k: v for k, v in region.items() if k not in {'state', 'evidence'}}
            for profile, region in entry['regions'].items()
        }
        result[key] = stable
    return result


def enforce_registrations(trusted, candidate, *, units=False):
    if registration_contract(trusted, units=units) != registration_contract(candidate, units=units):
        raise ValueError('Trusted-tooling review required for reference registrations or source-unit layout')


def export(repo, entries, destination):
    destination.mkdir(parents=True, exist_ok=True)
    for name, (mode, kind, oid) in entries.items():
        if kind == 'commit':
            if name != 'lib/ultralib':
                raise ValueError('Unexpected submodule')
            continue
        path = destination / name
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(git(repo, 'cat-file', 'blob', oid))
        path.chmod(0o755 if mode == '100755' else 0o644)


def selected_functions(base, candidate, changed):
    previous = {f['symbol']: f for f in base['functions']}
    shared = any(p.startswith('include/') or p.startswith('src/') and p.endswith('.h') for p in changed)
    selected = []
    for entry in candidate['functions']:
        state = entry.get('regions', {}).get('us', {}).get('state')
        if state not in {'matched', 'original_asm'}:
            continue
        if shared or entry['source'] in changed or previous.get(entry['symbol']) != entry:
            if not re.fullmatch(r'[A-Za-z_][A-Za-z_0-9]*', entry['symbol']):
                raise ValueError('Invalid function ID')
            selected.append({'symbol': entry['symbol'], 'state': state})
    return selected


def prepare(settings, plan, work):
    repo = work / 'git'
    fetch(repo, f'https://github.com/{REPOSITORY}.git',
          [plan['head'], plan['base'], plan['merge'], settings['trusted_revision']])
    # Revision traversal hides parents of shallow commits; the immutable object does not.
    header = git(repo, 'cat-file', 'commit', plan['merge']).split(b'\n\n', 1)[0]
    parents = [line.removeprefix(b'parent ').decode() for line in header.splitlines() if line.startswith(b'parent ')]
    if parents != [plan['base'], plan['head']]:
        raise ValueError('Fetched merge parents changed')
    trusted = tree(repo, settings['trusted_revision'])
    candidate = tree(repo, plan['merge'])
    base = tree(repo, plan['base'])
    enforce_policy(trusted, candidate)
    for path, units in [('progress/functions.json', False), ('progress/source_units.json', True)]:
        approved = json.loads(git(repo, 'cat-file', 'blob', trusted[path][2]))
        proposed = json.loads(git(repo, 'cat-file', 'blob', candidate[path][2]))
        enforce_registrations(approved, proposed, units=units)
    export(repo, candidate, work / 'candidate')
    # Build scripts, config, dependencies and tests are exactly the approved snapshot.
    # Tests from PRs run only in the public no-ROM workflow.
    for path, item in trusted.items():
        if path.startswith('tests/'):
            target = work / 'candidate' / path
            target.parent.mkdir(parents=True, exist_ok=True)
            target.write_bytes(git(repo, 'cat-file', 'blob', item[2]))
    submodule = checked_sha(trusted['lib/ultralib'][2])
    library = work / 'ultralib-git'
    fetch(library, ULTRALIB, [submodule])
    export(library, tree(library, submodule), work / 'candidate/lib/ultralib')
    changed = {p for p in base.keys() | candidate.keys() if base.get(p) != candidate.get(p)}
    old = json.loads(git(repo, 'show', plan['base'] + ':progress/functions.json'))
    current = json.loads((work / 'candidate/progress/functions.json').read_text())
    plan = {**plan, 'trusted_revision': settings['trusted_revision'],
            'functions': selected_functions(old, current, changed)}
    (work / 'plan.json').write_text(json.dumps(plan, indent=2))
    return plan


def docker_command(name, settings, candidate, rom, verifier, plan):
    return ['docker', 'run', '--detach', '--name', name, '--platform', 'linux/amd64',
            '--network', 'none', '--read-only', '--cap-drop', 'ALL',
            '--security-opt', 'no-new-privileges', '--pids-limit', '512',
            '--memory', '6g', '--cpus', '4', '--user', '1000:1000',
            '--tmpfs', '/tmp:rw,nosuid,nodev,size=512m,mode=1777',
            '--tmpfs', '/workspace:rw,exec,nosuid,nodev,size=4g,mode=1777',
            '--mount', f'type=bind,source={candidate},target=/candidate,readonly',
            '--mount', f'type=bind,source={rom},target=/input/baserom.us.z64,readonly',
            '--mount', f'type=bind,source={verifier / "sandbox.py"},target=/verifier/sandbox.py,readonly',
            '--mount', f'type=bind,source={plan},target=/plan.json,readonly',
            '--workdir', '/workspace', settings['image'],
            'sleep', 'infinity']


def read_container_file(name, path, maximum):
    # Docker's archive/copy API cannot reliably read tmpfs-backed paths. Use
    # the pinned image's read-only head binary; bound bytes and wall time before
    # hashing on the host. Capture stdout/stderr, never forward binary output or
    # container-controlled diagnostics to Actions' workflow-command parser.
    result = subprocess.run(['docker', 'exec', name, '/usr/bin/head', '-c', str(maximum + 1), '--', path],
                            capture_output=True, timeout=30, check=False)
    if result.returncode != 0 or len(result.stdout) > maximum:
        raise ValueError('Cannot read bounded verification output')
    return result.stdout


def build_image(settings, work):
    # Select the base by its registry digest, never a mutable tag.
    base = settings['image']
    present = subprocess.run(['docker', 'image', 'inspect', base],
                             stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    if present.returncode != 0:
        run(['docker', 'pull', '--platform', 'linux/amd64', settings['image']])
    actual = subprocess.check_output(['docker', 'image', 'inspect', '--format', '{{.Id}}', base], text=True).strip()
    if not re.fullmatch(r'sha256:[0-9a-f]{64}', actual):
        raise ValueError('Invalid local base image identity')
    # The existing conker wrapper adds this reviewed RSP assembler to the CPU
    # image. Build only its isolated Dockerfile context, before exposing a ROM.
    candidate = work / 'candidate'
    lock = json.loads((candidate / 'toolchain/tools.lock.json').read_text())
    armips = checked_sha(lock['tools']['armips']['revision'])
    dockerfile = (candidate / 'toolchain/rsp.Dockerfile').read_bytes()
    key = hashlib.sha256(dockerfile + actual.encode() + armips.encode()).hexdigest()[:24]
    base_tag = 'conker-private-base:' + actual.split(':')[1]
    tag = 'conker-private-rsp:' + key
    run(['docker', 'tag', base, base_tag])
    with tempfile.TemporaryDirectory() as directory:
        context = Path(directory)
        (context / 'Dockerfile').write_bytes(dockerfile)
        run(['docker', 'build', '--platform', 'linux/amd64', '--tag', tag,
             '--build-arg', 'BASE_IMAGE=' + base_tag, '--build-arg', 'ARMIPS_REV=' + armips, directory])
    image = subprocess.check_output(['docker', 'image', 'inspect', '--format', '{{.Id}}', tag], text=True).strip()
    if not re.fullmatch(r'sha256:[0-9a-f]{64}', image):
        raise ValueError('Invalid derived toolchain image ID')
    return image


def verify(settings, plan, work, rom, verifier):
    image = build_image(settings, work)
    if rom.stat().st_size != 67108864 or hashlib.sha1(rom.read_bytes()).hexdigest() != settings['rom_sha1']:
        raise ValueError('US ROM checksum mismatch')
    name = 'conker-private-' + uuid.uuid4().hex
    command = docker_command(name, {**settings, 'image': image}, (work / 'candidate').resolve(), rom.resolve(),
                             verifier.resolve(), (work / 'plan.json').resolve())
    try:
        # No raw build output reaches Actions' command parser, even in private logs.
        with (work / 'private-build.log').open('wb') as log:
            run(command, stdout=log, stderr=subprocess.STDOUT, timeout=60)
            # Keep tmpfs mounted until the host has read and hashed both outputs.
            run(['docker', 'exec', name, 'python3', '-I', '-u', '/verifier/sandbox.py'],
                stdout=log, stderr=subprocess.STDOUT, timeout=3600)
        # Recheck byte identity on the trusted host, using independently pinned digests.
        main = read_container_file(name, '/workspace/build/us/conker.us.z64', 67108864)
        game = read_container_file(name, '/workspace/build/game-integrated/us/conker.game.us.integrated.bin', 4 * 1024 * 1024)
        if hashlib.sha1(main).hexdigest() != settings['rom_sha1'] or hashlib.sha1(game).hexdigest() != settings['game_sha1']:
            raise ValueError('Host byte-identity check failed')
    finally:
        subprocess.run(['docker', 'rm', '-f', name], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    print('Private US focused checks and clean integration passed.')


def load_settings(path):
    data = json.loads(path.read_text())
    checked_sha(data['trusted_revision'])
    checked_sha(data['rom_sha1']); checked_sha(data['game_sha1'])
    if not re.fullmatch(r'ghcr\.io/devoldschool/conkers-bfd-decomp-toolchain@sha256:[0-9a-f]{64}', data['image']):
        raise ValueError('The verifier requires the approved digest-pinned toolchain image')
    return data


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('command', choices=['resolve', 'prepare', 'run'])
    parser.add_argument('--pr', type=int, required=True)
    parser.add_argument('--head', required=True)
    parser.add_argument('--base', required=True)
    parser.add_argument('--settings', type=Path, default=Path('settings.json'))
    parser.add_argument('--work', type=Path, default=Path('private-work'))
    parser.add_argument('--rom', type=Path)
    args = parser.parse_args()
    if args.command == 'run' and args.rom is None:
        parser.error('run requires --rom; prepare never accesses ROM inputs')
    plan = resolve(args.pr, args.head, args.base)
    if args.command == 'resolve':
        if os.environ.get('GITHUB_OUTPUT'):
            with open(os.environ['GITHUB_OUTPUT'], 'a') as output:
                for key in ('head', 'base', 'merge'):
                    print(f'{key}={plan[key]}', file=output)
        print('Approved PR revision and merge parents confirmed.')
        return
    settings = load_settings(args.settings)
    if args.work.exists():
        raise ValueError('Use a fresh private work directory')
    args.work.mkdir(parents=True, mode=0o700)
    plan = prepare(settings, plan, args.work)
    if args.command == 'prepare':
        print(f"Prepared {len(plan['functions'])} focused checks without accessing a ROM or starting Docker.")
        return
    print('Trusted-tooling policy passed; starting isolated verification.')
    verify(settings, plan, args.work, args.rom, Path(__file__).resolve().parent)
    if resolve(args.pr, args.head, args.base)['merge'] != plan['merge']:
        raise ValueError('PR changed during verification')


if __name__ == '__main__':
    main()
