"""Matching and linked completion for maintained original assembly source."""
from pathlib import Path
import subprocess
import re

from candidate_tables import Object32
import linked_aliases
import rom_span

import objdiff_targets
import original_asm
import prepare_nonmatching_asm
import project_state as state


def prepare_candidate(spec: dict, root: Path, output: Path) -> dict:
    """Freshly assemble maintained source and prove its full allocated ROM span."""
    source = Path(spec['source']).with_suffix('.s')
    if source.is_absolute() or '..' in source.parts or not source.parts or source.parts[0] != 'src':
        raise ValueError('maintained assembly must be a repository source')
    path = root / source
    if not path.is_file() or path.is_symlink():
        raise ValueError('maintained assembly source is missing or indirect')
    directory = output / spec['key']
    directory.mkdir(parents=True, exist_ok=True)
    candidate = directory / 'base.o'
    with (directory / 'maintained-assembly.log').open('w') as log:
        subprocess.run(['mips-linux-gnu-as', '-W', '-EB', '-march=vr4300', '-mabi=32',
                        '-I', 'include', '-o', str(candidate), str(source)],
                       cwd=root, stdout=log, stderr=log, check=True)
    size = spec['end'] - spec['start']
    if objdiff_targets.text_extent(candidate.read_bytes()) != size:
        raise ValueError('maintained assembly does not cover the full reviewed extent')
    linked = 'build/us/asm/us/' + str(source.relative_to('src').with_suffix('.o'))
    if candidate.read_bytes() != (root / linked).read_bytes():
        raise ValueError('maintained assembly differs from the actual runtime linker input')
    obj = Object32(candidate.read_bytes())
    code, base, rom_hash = rom_span.debugger_code(root)
    start = spec['start'] + objdiff_targets.ORIGINS['debugger']
    declared = original_asm.declared_symbols(root, False)
    undefined = {name for symbols in obj.symbols.values()
                 for name, _, _, section in symbols if name and section == 0}
    definitions = {}
    for name in undefined:
        if name in declared:
            definitions[name] = declared[name]
        elif re.fullmatch(r'D_[0-9A-Fa-f]{8}', name):
            # The canonical debugger C data uses address labels. Resolve the
            # literal address exactly; the complete linked ROM bytes must match.
            definitions[name] = int(name[2:], 16)
        else:
            raise ValueError('maintained assembly has an unreviewed external symbol: ' + name)
    payload = linked_aliases.linked_span(candidate, obj, spec['original_asm_members'][0],
        start, size, definitions, directory / 'maintained-linked', reference=False, padding=True)
    expected = code[start - base:start - base + size]
    proof = objdiff_targets.verify_linked_bytes(payload, expected, 'maintained debugger assembly')
    return {'assembly_source': source.as_posix(),
            'base_path': candidate.relative_to(output).as_posix(),
            'base_sha256': objdiff_targets.sha256(candidate),
            'candidate_origin': 'maintained_original_assembly',
            'maintained_assembly_proof': {**proof, 'rom_sha1': rom_hash},
            'maintained_source_inputs': {source.as_posix(): objdiff_targets.sha256(path)},
            'maintained_linked_inputs': {linked: objdiff_targets.sha256(root / linked)}}


def qualify(spec: dict, runtime_inputs: dict, root: Path, *, output: Path | None = None) -> dict:
    if spec.get('kind') != 'original_asm' or spec.get('overlay') != 'debugger' or not runtime_inputs:
        raise ValueError('original assembly completion needs a verified debugger runtime image')
    functions = state.load_json(state.FUNCTIONS_FILE)['functions']
    by_id = {f['symbol']: f for f in functions}
    members = [by_id[name] for name in spec['original_asm_members']]
    start, end = spec['start'], spec['end']
    cursor = start + objdiff_targets.ORIGINS['debugger']
    for member in members:
        original_asm.validate_metadata(member)
        region = member['regions']['us']
        if (member.get('overlay') != 'debugger' or member['source'] != spec['source']
                or region['state'] != 'original_asm' or int(region['vram'], 0) != cursor):
            raise ValueError('original assembly members do not cover the complete unit')
        cursor += region['size_bytes']
    if cursor != end + objdiff_targets.ORIGINS['debugger']:
        raise ValueError('original assembly members do not cover the complete unit')
    entries = state.mapped_subsegments('us', 'debugger')
    position = next((i for i, (offset, _, _) in enumerate(entries) if offset == start), None)
    name = spec['source'].removeprefix('src/').removesuffix('.c')
    following = (entries[position + 1][0] if position is not None and position + 1 < len(entries)
                 else state.validate_code_ranges(state.load_json(state.OVERLAYS_FILE))['debugger']['us'][1])
    if (position is None or tuple(entries[position][1:]) != ('asm', name) or following != end):
        raise ValueError('original assembly completion needs its exact canonical ASM placement')
    prepare_nonmatching_asm.materialize('us', spec['source'])
    proofs = {}
    source_inputs = {spec['source']: objdiff_targets.sha256(root / spec['source'])}
    for member in members:
        proof = original_asm.verify(root, member)
        original_asm.require_unchanged_span(member, proof)
        proofs[member['symbol']] = proof
        path = state.nonmatching_asm_path(member['source'], member['regions']['us']['symbol'])
        source_inputs[Path(path).as_posix()] = objdiff_targets.sha256(root / path)
    candidate = prepare_candidate(spec, root, output or root / 'build/us/objdiff-report')
    source_inputs.update(candidate.pop('maintained_source_inputs'))
    linked_inputs = candidate.pop('maintained_linked_inputs')
    return {**candidate, 'complete': True, 'original_asm_completion_verified': True,
            'original_asm_proofs': proofs,
            'completion_reason': 'Maintained original assembly matches the full ROM span and actual runtime input',
            'source_inputs': source_inputs,
            'linked_inputs': {**runtime_inputs, **linked_inputs}}
