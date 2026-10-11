"""Build the pinned native objdiff patch and exercise its exact-data contract."""
from __future__ import annotations

import hashlib
import json
import os
from pathlib import Path
import platform
import shutil
import struct
import subprocess
import tarfile
import tempfile


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def data_fixture(*, named: bool = True, addend: int = 0, destination: int = 4,
                 suffix: bytes = b'constant', relocation: bool = True, absolute: bool = False) -> bytes:
    """Synthetic ELF32/MIPS: one pointer, then unnamed initialized storage."""
    names = b'\0.text\0.rodata\0.rel.rodata\0.symtab\0.strtab\0.shstrtab\0'
    strings = b'\0function\0label\0prefix\0'
    symbols = bytes(16)
    symbols += struct.pack('>IIIBBH', 1, 0, 16, 0x12, 0, 1)
    symbols += struct.pack('>IIIBBH', 10, destination, 0, 0x10, 0, 0xFFF1 if absolute else 1)
    if named:
        symbols += struct.pack('>IIIBBH', 16, 0, 4, 0x11, 0, 2)
    payloads = [b'', struct.pack('>4I', 0x03E00008, 0, 0, 0),
                struct.pack('>I', addend) + suffix,
                struct.pack('>II', 0, (2 << 8) | 2) if relocation else b'', symbols, strings, names]
    types = [0, 1, 1, 9, 2, 3, 3]
    flags = [0, 6, 2, 0, 0, 0, 0]
    section_names = [b'', b'.text', b'.rodata', b'.rel.rodata', b'.symtab', b'.strtab', b'.shstrtab']
    data = bytearray(52)
    data[:16] = b'\x7fELF\x01\x02\x01' + bytes(9)
    struct.pack_into('>HHI', data, 16, 1, 8, 1)
    struct.pack_into('>I', data, 36, 0x10001000)
    headers = []
    for i, payload in enumerate(payloads):
        data.extend(bytes(-len(data) % 4))
        offset = len(data)
        data.extend(payload)
        headers.append(struct.pack('>10I', names.index(section_names[i] + b'\0') if i else 0,
                                   types[i], flags[i], 0, offset if i else 0, len(payload),
                                   {3: 4, 4: 5}.get(i, 0), {3: 2, 4: 1}.get(i, 0),
                                   4 if i else 0, {3: 8, 4: 16}.get(i, 0)))
    data.extend(bytes(-len(data) % 4))
    shoff = len(data)
    data.extend(b''.join(headers))
    struct.pack_into('>I', data, 32, shoff)
    struct.pack_into('>HHHHHH', data, 40, 52, 0, 0, 40, len(headers), 6)
    return bytes(data)


def verify_native(binary: Path) -> None:
    """Require positive and negative native report results, without game inputs."""
    cases = {
        'anonymous': (data_fixture(named=False), True),
        'equivalent-addend': (data_fixture(named=False, destination=0, addend=4), True),
        'changed-destination': (data_fixture(named=False, destination=8), False),
        'changed-anonymous-byte': (data_fixture(suffix=b'constanX'), False),
        'missing-anonymous-tail': (data_fixture(suffix=b'cons'), False),
        'extra-anonymous-tail': (data_fixture(suffix=b'constant\0'), False),
        'missing-relocation': (data_fixture(relocation=False), False),
    }
    with tempfile.TemporaryDirectory(prefix='objdiff-data-test-') as tmp:
        root = Path(tmp)
        (root / 'target.o').write_bytes(data_fixture())
        units = []
        for name, (payload, _) in cases.items():
            (root / (name + '.o')).write_bytes(payload)
            units.append({'name': name, 'target_path': 'target.o', 'base_path': name + '.o'})
        # Also reject an extra relocation when the original has none.
        (root / 'no-reloc.o').write_bytes(data_fixture(relocation=False))
        units.append({'name': 'extra-relocation', 'target_path': 'no-reloc.o', 'base_path': 'target.o'})
        cases['extra-relocation'] = (b'', False)
        units.append({'name': 'complete-without-candidate', 'target_path': 'target.o',
                      'metadata': {'complete': True}})
        cases['complete-without-candidate'] = (b'', False)
        (root / 'absolute-target.o').write_bytes(data_fixture(absolute=True))
        (root / 'absolute-changed.o').write_bytes(data_fixture(absolute=True, destination=8))
        units.append({'name': 'changed-absolute-destination', 'target_path': 'absolute-target.o',
                      'base_path': 'absolute-changed.o'})
        cases['changed-absolute-destination'] = (b'', False)
        (root / 'objdiff.json').write_text(json.dumps({'build_target': False, 'build_base': False,
            'options': {'data_diff_full_section': True}, 'units': units}))
        subprocess.run([str(binary), 'report', 'generate', '-p', str(root), '-o', str(root / 'report.json')], check=True)
        report = json.loads((root / 'report.json').read_text())
        for unit in report['units']:
            m = unit['measures']
            if unit['name'] == 'complete-without-candidate':
                if int(m.get('matched_code', 0)) or int(m.get('matched_functions', 0)) or int(m.get('complete_code', 0)) != int(m['total_code']):
                    raise ValueError('native linked completion must not invent C matching credit')
            actual = int(m.get('matched_data', 0)) == int(m['total_data'])
            if actual != cases[unit['name']][1]:
                raise ValueError('native full-data regression: ' + unit['name'])
        if {u['name'] for u in report['units']} != set(cases):
            raise ValueError('native full-data regression cases missing')


def install_patched(root: Path, lock: dict) -> Path:
    """Pin upstream source, Cargo.lock and patch; recheck cached binary hashes."""
    spec = lock['source_build']
    patch = root / spec['patch']
    if sha256(patch) != spec['patch_sha256']:
        raise ValueError('objdiff patch checksum mismatch')
    key = hashlib.sha256(json.dumps(spec, sort_keys=True).encode()).hexdigest()[:16]
    directory = root / 'build/host-tools' / ('objdiff-' + lock['version'] + '-' + key)
    binary = directory / ('objdiff-cli-' + platform.system().lower() + '-' + platform.machine())
    receipt = binary.with_suffix('.json')
    if binary.is_file() and receipt.is_file():
        proof = json.loads(receipt.read_text())
        if proof.get('source_build') == spec and proof.get('binary_sha256') == sha256(binary):
            return binary
    if not shutil.which('cargo'):
        raise ValueError('patched objdiff requires Rust/Cargo (see docs/objdiff.md)')
    directory.mkdir(parents=True, exist_ok=True)
    archive = directory / 'source.tar.gz'
    if not archive.is_file() or sha256(archive) != spec['archive_sha256']:
        with tempfile.NamedTemporaryFile(dir=directory, delete=False) as file:
            download = Path(file.name)
        try:
            url = lock['repository'].replace('https://github.com/', 'https://codeload.github.com/') + '/tar.gz/' + spec['revision']
            subprocess.run(['curl', '--fail', '--location', '--silent', '--show-error',
                            '--connect-timeout', '15', '--max-time', '180', url, '-o', str(download)], check=True)
            if sha256(download) != spec['archive_sha256']:
                raise ValueError('objdiff source checksum mismatch')
            os.replace(download, archive)
        finally:
            download.unlink(missing_ok=True)
    print('Building pinned objdiff with full initialized-data comparison...', flush=True)
    with tempfile.TemporaryDirectory(prefix='source-', dir=directory) as tmp:
        with tarfile.open(archive) as tar:
            tar.extractall(tmp, filter='data')
        source = Path(tmp) / ('objdiff-' + spec['revision'])
        patch_env = {**os.environ, 'GIT_CEILING_DIRECTORIES': str(source.parent)}
        subprocess.run(['git', 'apply', '--check', str(patch)], cwd=source, env=patch_env, check=True)
        subprocess.run(['git', 'apply', str(patch)], cwd=source, env=patch_env, check=True)
        env = {**os.environ, 'CARGO_TARGET_DIR': str(source / 'target')}
        with (directory / 'build.log').open('w') as log:
            subprocess.run(['cargo', 'build', '--locked', '--release', '-p', 'objdiff-cli'],
                           cwd=source, env=env, stdout=log, stderr=log, check=True)
        built = source / 'target/release/objdiff-cli'
        verify_native(built)
        shutil.copy2(built, binary)
    receipt.write_text(json.dumps({'source_build': spec, 'binary_sha256': sha256(binary),
        'rustc': subprocess.check_output(['rustc', '--version'], text=True).strip(),
        'native_regressions': 'passed'}, indent=2) + '\n')
    return binary
