"""Independent GNU linker trial; writes only ignored experimental output."""
from pathlib import Path
import hashlib
import re
import subprocess

from elf_sections import sections
import objdiff_candidate


def verify_linked_copies(raw: Path, canonical: Path, runtime: bytes,
                         bases: dict[str, int], directory: Path) -> dict:
    runtime_obj = objdiff_candidate.Elf(runtime, 2)
    addresses = {}
    for name, value, _, _, _, section in runtime_obj.symbols:
        if name and (0 < section < len(runtime_obj.headers) or section == 0xFFF1):
            addresses.setdefault(name, set()).add(value)
    original = objdiff_candidate.Elf(raw.read_bytes())
    definitions = []
    for name, value, _, _, _, section in original.symbols:
        if name and section == 0:
            if not re.fullmatch(r'[A-Za-z_.$][\w.$]*', name) or len(addresses.get(name, [])) != 1 or value:
                raise ValueError('unresolved comparison-copy external: ' + name)
            definitions.append(f'{name} = 0x{next(iter(addresses[name])):X};')
    expected = {}
    for name, base in bases.items():
        size = original.headers[original.names.index(name)][5]
        containing = [(h, runtime_obj.payload(i)) for i, h in enumerate(runtime_obj.headers)
                      if h[1] == 1 and h[2] & 2 and h[3] <= base and base + size <= h[3] + h[5]]
        if len(containing) != 1:
            raise ValueError('candidate placement is not in one allocated runtime section')
        header, payload = containing[0]
        expected[name] = payload[base - header[3]:base - header[3] + size]
    directory.mkdir(parents=True, exist_ok=True)
    for label, path in (('raw', raw), ('canonical', canonical)):
        script = directory / (label + '.ld')
        lines = ['SECTIONS {'] + [f'{name} 0x{base:X} : {{ *({name}) }}' for name, base in bases.items()]
        lines += ['/DISCARD/ : { *(.reginfo) *(.MIPS.abiflags) *(.pdr) *(.mdebug) '
                  '*(.gnu.attributes) *(.comment) }', '}', *definitions]
        script.write_text('\n'.join(lines) + '\n')
        output = directory / (label + '.elf')
        with (directory / (label + '.log')).open('w') as log:
            subprocess.run(['mips-linux-gnu-ld', '-m', 'elf32btsmip', '-T', str(script),
                            '-o', str(output), str(path)], check=True, stdout=log, stderr=log)
        linked = sections(output.read_bytes(), 2)
        for name, payload in expected.items():
            if linked.get(name, (None, None))[1] != payload:
                raise ValueError('comparison copy differs from runtime bytes: ' + label + ' ' + name)
    return {name: {'bytes': len(payload), 'sha256': hashlib.sha256(payload).hexdigest(),
                   'raw_and_canonical_match_runtime': True} for name, payload in expected.items()}
