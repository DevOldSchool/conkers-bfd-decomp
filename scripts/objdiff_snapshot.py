"""Read local native objdiff progress without compiling or fetching anything."""
from __future__ import annotations

import hashlib
import json
import math
from pathlib import Path
import re
import subprocess


REPORT_DIRECTORY = Path('build/us/objdiff-report')
INPUTS = ('src', 'include', 'config', 'progress', 'lib', 'scripts',
          'Makefile', 'Dockerfile', 'conker', 'toolchain/tools.lock.json')
GENERATE = 'Run ./conker objdiff report with your configured US ROM, pinned SDK and toolchain; then ./conker progress.'


def git(root: Path, *args: str) -> str:
    return subprocess.check_output(['git', *args], cwd=root, text=True,
                                   stderr=subprocess.PIPE)


def input_fingerprint(root: Path) -> str:
    """Hash report inputs, including working-tree edits and SDK submodules.

    Git's ignore rules exclude generated outputs. Deleted inputs and uninitialized
    submodules cannot silently reuse a report. No build products or ROMs are read.
    """
    def files(directory: Path, paths: tuple[str, ...]):
        names = git(directory, 'ls-files', '-z', '--cached', '--others',
                    '--exclude-standard', '--', *paths)
        for name in sorted(set(names.split('\0')) - {''}):
            path = directory / name
            if path.is_dir():
                if not (path / '.git').exists():
                    raise ValueError(f'uninitialized submodule: {path.relative_to(root)}')
                yield from files(path, ())
            else:
                yield path

    digest = hashlib.sha256()
    for path in files(root, INPUTS):
        digest.update(str(path.relative_to(root)).encode() + b'\0')
        digest.update(hashlib.sha256(path.read_bytes()).digest() if path.is_file() else b'missing')
    return digest.hexdigest()


def inventory_only() -> dict:
    return {'status': 'not_requested', 'reason': 'Inventory-only mode; objdiff snapshot was not read.'}


def read_status(root: Path) -> dict:
    """Return a display status, never substitute inventory credit for objdiff."""
    directory = root / REPORT_DIRECTORY
    result = {'status': 'missing', 'reason': 'Native report.json and validation.json are required.'}
    if not all((directory / name).is_file() for name in ('report.json', 'validation.json')):
        return result
    try:
        raw = (directory / 'report.json').read_bytes()
        report = json.loads(raw)
        proof = json.loads((directory / 'validation.json').read_bytes())
        if (proof.get('profile') != 'us' or proof.get('snapshot_schema') != 1
                or not isinstance(proof.get('source_dirty'), bool)
                or not re.fullmatch(r'[0-9a-f]{40}', proof.get('git_revision', ''))
                or not re.fullmatch(r'[0-9a-f]{64}', proof.get('source_fingerprint', ''))):
            return {'status': 'unverified', 'reason': 'Missing or unsupported US snapshot provenance; regenerate the report.'}
        if (report['version'] != 2 or proof['format_version'] != 2
                or proof['report_sha256'] != hashlib.sha256(raw).hexdigest()
                or proof.get('per_unit_coverage_verified') is not True
                or proof.get('compile_errors') != []
                or proof['measures'] != report['measures']):
            raise ValueError('report integrity or generation validation failed')
        measures = report['measures']
        total = int(measures.get('total_code', 0))
        matched = int(measures.get('matched_code', 0))
        percent = float(measures.get('matched_code_percent', 0))
        if (total <= 0 or not 0 <= matched <= total or not math.isfinite(percent)
                or not 0 <= percent <= 100 or abs(percent - 100 * matched / total) > 0.001
                or int(proof['reported_code_bytes']) != total
                or int(proof['expected_code_bytes']) != total):
            raise ValueError('invalid native code measures or denominator')
        result = {'status': 'unverified', 'reason': 'Cannot check current source inputs.',
                  'profile': 'us', 'git_revision': proof['git_revision'],
                  'source_dirty': proof['source_dirty'], 'source_fingerprint': proof['source_fingerprint'],
                  'report_sha256': proof['report_sha256'], 'matched_code': matched,
                  'total_code': total, 'matched_code_percent': percent}
        revision = git(root, 'rev-parse', 'HEAD').strip()
        fingerprint = input_fingerprint(root)
        reasons = []
        if revision != proof['git_revision']:
            reasons.append('HEAD differs from the report source revision')
        if fingerprint != proof['source_fingerprint']:
            reasons.append('report inputs have changed')
        result.update(status='stale' if reasons else 'current', current_revision=revision,
                      reason='; '.join(reasons) if reasons else 'Source revision and input fingerprint match.')
    except (OSError, subprocess.CalledProcessError) as error:
        result.update(status='unverified', reason=f'Cannot read/check snapshot inputs ({type(error).__name__}).')
    except (ValueError, KeyError, TypeError, AttributeError, OverflowError) as error:
        result.update(status='invalid', reason=f'Invalid objdiff snapshot ({type(error).__name__}); regenerate it.')
    return result


def render_status(status: dict) -> list[str]:
    current = status['status'] == 'current'
    value = f"{status['matched_code_percent']:.4f}%" if current else f"unavailable ({status['status']})"
    lines = [f'## US objdiff code match: {value}', '', status['reason']]
    if 'git_revision' in status:
        lines.extend(['', f"- Profile: **{status['profile']}**; native metric: `matched_code_percent` (all categories).",
                      f"- Report source revision: `{status['git_revision']}`.",
                      f"- Modified report inputs at generation: **{'yes' if status['source_dirty'] else 'no'}**.",
                      f"- Input fingerprint: `{status['source_fingerprint']}`.",
                      f"- Report SHA-256: `{status['report_sha256']}`.",
                      f"- {'Matched' if current else 'Last snapshot (not current)'} code: **{status['matched_code']:,} / {status['total_code']:,} bytes ({status['matched_code_percent']:.4f}%)**."])
    lines.extend(['', 'Snapshot: `build/us/objdiff-report/report.json` with local `validation.json`.',
                  GENERATE, 'Reading progress never builds, installs tools or accesses the network.',
                  'Compare with decomp.dev only for the same source inputs, revision, US version and all-category metric.',
                  'Tracked US CPU code only; no data/assets, other boot code, RSP or EU coverage.', ''])
    return lines
