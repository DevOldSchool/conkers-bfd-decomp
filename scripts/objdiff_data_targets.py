"""Independent data and rebuilt-asset targets for the published objdiff report."""
from __future__ import annotations

import hashlib
import json
import os
from pathlib import Path
import re
import subprocess

import compile_c
import data_boundaries
import diff
from elf_sections import sections
import font_assets
import font_splits
import normalize_asm
import objdiff
import objdiff_targets
import rom_span
import rzip_archive
from candidate_tables import Object32

ROOT = Path(__file__).resolve().parent.parent
OUTPUT = ROOT / 'build/us/objdiff-report/data'


def target_config(image: dict, directory: Path, binary: Path, code_start: int, code_end: int,
                  *, overlay: str = 'main', origin: int = 0x80000000,
                  code_vram: int | None = None) -> dict:
    relative = directory.relative_to(ROOT).as_posix()
    segments = []
    if code_start:
        segments.append([0, 'bin', 'prefix'])
    segments.append({'name': 'context', 'type': 'code', 'start': code_start,
                     'vram': origin + code_start if code_vram is None else code_vram,
                     'subsegments': [[code_start, 'asm', 'context']]})
    data_start = image['vram_start'] - origin
    if code_end < data_start:
        segments.append([code_end, 'bin', 'rsp-code'])
    elif code_end != data_start:
        raise ValueError('data target overlaps its original code context')
    segments += [{'name': overlay + '_data', 'type': 'code', 'start': data_start,
                  'vram': image['vram_start'],
                  'subsegments': [[s['start'] - origin, s.get('input', '.data').split('.')[1],
                                   f"{s['start']:08X}"] for s in image['ranges']]},
                 [binary.stat().st_size]]
    return {'name': 'US ' + overlay + ' initialized data',
            'sha1': hashlib.sha1(binary.read_bytes()).hexdigest(),
            'options': {'basename': overlay + '-data', 'base_path': os.path.relpath(ROOT, directory.parent),
                        'target_path': binary.relative_to(ROOT).as_posix(),
                        'platform': 'n64', 'compiler': 'IDO',
                        'asm_path': relative + '/asm', 'asset_path': relative + '/assets',
                        'src_path': relative + '/unused-src', 'build_path': relative + '/objects',
                        'ld_script_path': relative + '/splat.ld', 'cache_path': relative + '/splache',
                        'undefined_funcs_auto_path': relative + '/undefined_funcs.txt',
                        'undefined_syms_auto_path': relative + '/undefined_syms.txt',
                        'symbol_addrs_path': ['config/symbols/' + ('game-us' if overlay == 'game' else 'us') + '.txt'],
                        'create_c_files': False, 'asm_emit_size_directive': True,
                        'asm_data_macro': 'glabel', 'asm_jtbl_label_macro': 'glabel',
                        'data_string_guesser_level': 0, 'rodata_string_guesser_level': 0},
            'segments': segments}


def target_extent(path: Path, expected_section: str, expected_size: int) -> None:
    parsed = sections(path.read_bytes(), 1)
    for name, (header, _) in parsed.items():
        if name == expected_section:
            if header[1] != 1 or header[5] != expected_size or not header[2] & 2:
                raise ValueError(f'{path}: data extent/type/flags differ from the audited range')
        elif header[2] & 2 and header[5] and name not in ('.reginfo', '.MIPS.abiflags'):
            raise ValueError(f'{path}: unexpected allocated target section {name}')
    if expected_section not in parsed:
        raise ValueError(f'{path}: missing data target section')


def reference_definitions(assembly: str, rom: bytes, *, origin: int = 0x80000000) -> dict[str, int]:
    """Resolve symbolic pointer words from original rows, never candidate names.

    Splat may recognize a jump table through main's 0x10000000 execution alias
    without emitting an undefined-address assignment for its local label.
    Only a bare symbolic .word with independently checked ROM bytes qualifies.
    Expressions and unsupported directives remain linker errors.
    """
    result = {}
    pattern = (r'/\*\s+([0-9A-Fa-f]+)\s+([0-9A-Fa-f]{8})\s+'
               r'([0-9A-Fa-f]{8})\s*\*/\s*\.word\s+([A-Za-z_.$][\w.$]*)\s*$')
    for offset, address, word, symbol in re.findall(pattern, assembly, re.M):
        offset, address, value = int(offset, 16), int(address, 16), int(word, 16)
        if address != origin + offset or rom[offset:offset + 4] != bytes.fromhex(word):
            raise ValueError('symbolic data row differs from original ROM')
        if symbol in result and result[symbol] != value:
            raise ValueError('conflicting original pointer definitions')
        result[symbol] = value
    return result



def reference_assembly(assembly: str, section: str, *, output_section: str | None = None) -> str:
    """Keep original row offsets when a range begins inside an aligned section.

    A double at runtime address 0x...4950 is aligned even when its mapped range
    starts at 0x...494C. GNU as otherwise inserts padding relative to offset zero.
    Disable implicit directive alignment; explicit original rows and the full
    linked-image comparison remain authoritative. No symbols or sizes change.
    """
    text = normalize_asm.normalize(assembly)
    pattern = r'(^\.section\s+' + re.escape(section) + r'(?:,.*)?$)'
    def directive(match):
        return match[1].replace(section, output_section or section, 1) + '\n.align 0'
    text, count = re.subn(pattern, directive, text, flags=re.M)
    if count != 1:
        raise ValueError('expected one data reference section directive')
    return text


def prepare_targets(image: dict, rom: bytes, *, overlay: str = 'main',
                    output: Path | None = None) -> tuple[list[dict], dict]:
    output = OUTPUT if output is None else output
    directory = output / ('targets' if overlay == 'main' else overlay + '-targets')
    directory.mkdir(parents=True, exist_ok=True)
    if overlay == 'main':
        origin = 0x80000000
        payload = rom[:image['vram_end'] - origin]
        code, base, digest = rom_span.main_code(ROOT)
    elif overlay == 'debugger':
        code, data, base, data_base, digest = rom_span.debugger_image(ROOT)
        if data_base != image['vram_start'] or data_base != base + len(code):
            raise ValueError('debugger data disagrees with loader boundaries')
        origin, payload = base, code + data
    elif overlay == 'game':
        layout = json.loads((ROOT / 'config/rzip_layouts.json').read_text())['profiles']['us']
        game = rzip_archive.parse_game_archive(rom[int(layout['game_start'], 0):int(layout['game_end'], 0)])
        code, base, digest = rom_span.game_code(ROOT)
        data_base = int(layout['game_data_vram'], 0)
        if game.code != code or data_base != image['vram_start']:
            raise ValueError('game data disagrees with archive boundaries or code context')
        origin, payload = data_base - len(code), code + game.data
    else:
        raise ValueError('unsupported data target overlay')
    start, end = image['vram_start'] - origin, image['vram_end'] - origin
    expected = payload[start:end]
    if (start < 0 or end != len(payload) or len(expected) != image['loaded_bytes']
            or hashlib.sha256(expected).hexdigest() != image['sha256']):
        raise ValueError(overlay + ' data image changed after boundary audit')
    binary = directory / (overlay + '-input.bin')
    binary.write_bytes(payload)
    code_start = 0 if overlay == 'game' else base - origin
    code_end = code_start + len(code)
    if hashlib.sha1(rom).hexdigest() != digest or payload[code_start:code_end] != code:
        raise ValueError(overlay + ' reference context differs from checked ROM')
    config = output / (overlay + '-targets.yaml')
    objdiff.write_json(config, target_config(image, directory, binary, code_start, code_end,
                                            overlay=overlay, origin=origin, code_vram=base))
    with (directory / 'splat.log').open('w') as log:
        subprocess.run(['splat', 'split', str(config)], cwd=ROOT, stdout=log, stderr=log, check=True)
    units, objects, lines = [], [], ['SECTIONS {']
    definitions = {}
    for index, span in enumerate(image['ranges']):
        key = f"{span['start']:08X}"
        section = span.get('input', '.data')
        assembly_section = '.' + section.split('.')[1]
        source = directory / 'asm' / 'data' / f'{key}{assembly_section}.s'
        normalized, target = directory / f'{key}.s', directory / f'{key}.o'
        assembly = source.read_text()
        for symbol, value in reference_definitions(assembly, payload, origin=origin).items():
            if symbol in definitions and definitions[symbol] != value:
                raise ValueError('conflicting original data pointer definitions')
            definitions[symbol] = value
        normalized.write_text(reference_assembly(assembly, assembly_section, output_section=section))
        with (directory / f'{key}.log').open('w') as log:
            subprocess.run(['mips-linux-gnu-as', '-W', '-EB', '-march=vr4300', '-mabi=32', '-no-pad-sections',
                            '-I', 'include', '-o', str(target), str(normalized)],
                           cwd=ROOT, stdout=log, stderr=log, check=True)
        target_extent(target, section, span['size'])
        relative = target.relative_to(ROOT).as_posix()
        objects.append(relative)
        lines += [f'.unit{index} 0x{span["start"]:X} : SUBALIGN(1) {{ "{relative}"({section}) }}',
                  f'ASSERT(SIZEOF(.unit{index}) == {span["size"]}, "data target extent {key}")']
        units.append({**span, 'key': key, 'overlay': overlay, 'section': section,
                      'target_path': target.relative_to(output).as_posix(),
                      'target_sha256': objdiff_targets.sha256(target)})
    lines += ['/DISCARD/ : { *(.reginfo) *(.MIPS.abiflags) *(.pdr) *(.gnu.attributes) *(.comment) }', '}']
    for name in ('undefined_funcs.txt', 'undefined_syms.txt'):
        for symbol, address in re.findall(r'^\s*([A-Za-z_.$][\w.$]*)\s*=\s*(0x[0-9A-Fa-f]+);',
                                          (directory / name).read_text(), re.M):
            lines.append(f'PROVIDE({symbol} = {address});')
    for symbol, address in sorted(definitions.items()):
        lines.append(f'PROVIDE({symbol} = 0x{address:X});')
    objdiff.write_json(directory / 'rom-pointer-definitions.json', definitions)
    script, elf, linked = directory / 'targets.ld', directory / 'targets.elf', directory / 'targets.bin'
    script.write_text('\n'.join(lines) + '\n')
    with (directory / 'link.log').open('w') as log:
        subprocess.run(['mips-linux-gnu-ld', '-m', 'elf32btsmip', '-T', str(script), '-o', str(elf),
                        *objects], cwd=ROOT, stdout=log, stderr=log, check=True)
        subprocess.run(['mips-linux-gnu-objcopy', '-O', 'binary', str(elf), str(linked)],
                       cwd=ROOT, stdout=log, stderr=log, check=True)
    proof = objdiff_targets.verify_linked_bytes(linked.read_bytes(), expected, overlay + ' initialized data')
    return units, proof


def candidate_source(unit: dict) -> Path | None:
    if unit.get('owner') and 'sources' in unit['owner']:
        return ROOT / data_boundaries.active_source(ROOT, unit['owner']['sources'])
    if unit['kind'] == 'private_section':
        sources = [ROOT / path for path in unit['sources'] if (ROOT / path).is_file()]
    elif unit['kind'] == 'external_payload':
        match = re.fullmatch(r'\*(\w+)\.o\(\.[\w.]+\)', unit['input_selector'])
        if match is None:
            if candidate_archive(unit) is not None:
                return None
            raise ValueError('unsupported data candidate selector')
        overlay = unit.get('overlay', 'main')
        if overlay not in ('main', 'game', 'debugger'):
            raise ValueError('unsupported data candidate overlay')
        sources = [path for parent in (f'src/{overlay}', f'src/done/{overlay}')
                   for path in (ROOT / parent).rglob(match[1] + '.c')]
    else:
        return None
    if len(sources) != 1:
        raise ValueError(f"{unit['key']}: expected one active candidate source")
    return sources[0]


def candidate_archive(unit: dict) -> tuple[Path, str] | None:
    if unit['kind'] == 'sdk_placement':
        return ROOT / 'build/us/lib' / (unit['archive'] + '.a'), unit['member']
    if unit['kind'] == 'external_payload':
        match = re.fullmatch(r'(build/game-libs/us/[\w]+\.a):([\w]+\.o)\((\.[\w.]+)\)',
                             unit['input_selector'])
        if match and unit.get('overlay') == 'game' and match[3] == unit['section']:
            return ROOT / match[1], match[2]
    return None


def candidate_section(unit: dict, base: Path) -> tuple[bytes, int]:
    """Retain emitted sections while accounting only for the reviewed payload."""
    parsed = sections(base.read_bytes(), 1)
    if unit['section'] not in parsed:
        raise ValueError('missing candidate data section')
    header, payload = parsed[unit['section']]
    size, emitted = unit['size'], unit.get('emitted_size', unit['size'])
    if header[1] != 1 or not header[2] & 2 or header[5] != emitted:
        raise ValueError('candidate section differs from mapped extent/type/flags')
    obj = Object32(base.read_bytes())
    index = obj.sections.index(header)
    padding = emitted - size
    if padding:
        if (unit.get('compiler_padding_bytes') != padding or not 0 < padding < 16
                or size % 4 or emitted != ((size + 15) & ~15) or any(payload[size:])
                or any(section == index and offset >= size for section, offset in obj.relocations)
                or any(section == index and (value >= size or value + extent > size)
                       for _, value, extent, section in obj.non_section_symbols)):
            raise ValueError('candidate compiler padding violates the reviewed payload contract')
    unit['candidate_section_size'] = header[5]
    unit['candidate_compiler_padding_bytes'] = padding
    # Keep the full base object unchanged. Objdiff decides how its actual
    # symbols compare with the shorter independent target; no padding is credited.
    return payload[:size], sum(section == index for section, _ in obj.relocations)


def prepare_candidates(units: list[dict], *, output: Path | None = None) -> list[dict]:
    output = OUTPUT if output is None else output
    config = []
    for unit in units:
        directory = output / unit['key']
        directory.mkdir(parents=True, exist_ok=True)
        base = directory / 'base.o'
        base.unlink(missing_ok=True)
        source = candidate_source(unit)
        archive = candidate_archive(unit)
        # These physical tables use a build-time split tied to mixed text
        # offsets. A reduced C-only object's partition has not been proved.
        # Keep their independent targets without borrowing GLOBAL_ASM tables.
        if unit['section'].startswith('.rodata.'):
            unit['candidate_unavailable'] = 'split rodata requires a proved C-only table partition'
            source = None
        with (directory / 'build.log').open('w') as log:
            if source:
                focused = directory / 'base.c'
                focused.write_text(diff.GLOBAL_ASM_LINE.sub('', source.read_text()))
                result = subprocess.run(compile_c.compile_command('us', focused, base),
                                        cwd=ROOT, stdout=log, stderr=log)
                unit['source'] = source.relative_to(ROOT).as_posix()
                if result.returncode:
                    unit['compile_error'] = unit['key'] + '/build.log'
                    base.unlink(missing_ok=True)
            elif archive:
                archive_path, member = archive
                result = subprocess.run(['mips-linux-gnu-ar', 'p', str(archive_path), member],
                                        cwd=ROOT, stdout=subprocess.PIPE, stderr=log, check=True)
                if not result.stdout:
                    raise ValueError(f"missing SDK member {member}")
                base.write_bytes(result.stdout)
        overlay = unit.get('overlay', 'main')
        item = {'name': overlay + '/data/' + unit['key'], 'target_path': unit['target_path'],
                'metadata': {'complete': False, 'progress_categories': [overlay + '-data']}}
        if base.is_file():
            try:
                payload, relocations = candidate_section(unit, base)
            except ValueError as error:
                unit['candidate_error'] = str(error)
            else:
                unit['candidate_data_relocations'] = relocations
                if not relocations:
                    unit['literal_payload_matches_rom'] = hashlib.sha256(payload).hexdigest() == unit['sha256']
                unit['base_path'] = base.relative_to(output).as_posix()
                unit['base_sha256'] = objdiff_targets.sha256(base)
                item['base_path'] = unit['base_path']
                if (unit.get('owner') and unit['kind'] == 'sdk_placement' and overlay == 'main'
                        and unit.get('literal_payload_matches_rom') is True):
                    archive_path, _ = candidate_archive(unit)
                    unit.update(complete=True, data_completion_verified=True,
                                linked_inputs={archive_path.relative_to(ROOT).as_posix(): objdiff_targets.sha256(archive_path)})
                    item['metadata']['complete'] = True
        config.append(item)
    return config


def font_input_hashes(directory: Path) -> dict[str, str]:
    manifest = json.loads((directory / 'manifest.json').read_text())
    paths = [directory / 'manifest.json'] + [font_assets.safe_manifest_file(directory, item['file'])
                                            for item in manifest['glyphs']]
    return {path.relative_to(ROOT).as_posix(): objdiff_targets.sha256(path) for path in paths}


def prepare_font(rom: bytes, *, output: Path | None = None) -> tuple[dict, dict]:
    directory = (OUTPUT if output is None else output) / 'font'
    directory.mkdir(parents=True, exist_ok=True)
    layout = font_assets.load_layout('us')
    ranges = font_splits.verify_splits(ROOT / 'config/profiles/us.yaml', rom, layout)
    paths = [ROOT / ('build/us/assets/' + name + '.o') for _, _, name in ranges]
    with (directory / 'build.log').open('w') as log:
        subprocess.run(['make', '--silent', *[str(p.relative_to(ROOT)) for p in paths], 'PROFILE=us'],
                       cwd=ROOT, stdout=log, stderr=log, check=True)
    layout = font_assets.load_layout('us')
    start, end = layout['font_start'], layout['font_storage_end']
    original = rom[start:end]
    inputs = ROOT / 'build/fonts/us'
    hashes = font_input_hashes(inputs)
    packed = font_assets.packed_font_bytes(inputs)
    base, target = directory / 'base.o', directory / 'target.o'
    linked_inputs = {}
    chunks = []
    for (begin, stop, _), path in zip(ranges, paths, strict=True):
        target_extent(path, '.data', stop - begin)
        chunks.append(sections(path.read_bytes(), 1)['.data'][1])
        linked_inputs[path.relative_to(ROOT).as_posix()] = objdiff_targets.sha256(path)
    base_input = directory / 'base-input'
    base_input.mkdir(exist_ok=True)
    (base_input / 'font_rle.bin').write_bytes(b''.join(chunks))
    subprocess.run(['mips-linux-gnu-ld', '-r', '-b', 'binary', '-m', 'elf32btsmip',
                    '-o', '../base.o', 'font_rle.bin'], cwd=base_input, check=True)
    (directory / 'font_rle.bin').write_bytes(original)
    subprocess.run(['mips-linux-gnu-ld', '-r', '-b', 'binary', '-m', 'elf32btsmip',
                    '-o', 'target.o', 'font_rle.bin'], cwd=directory, check=True)
    for path in (base, target):
        target_extent(path, '.data', end - start)
    candidate = sections(base.read_bytes(), 1)['.data'][1]
    if candidate != packed or hashes != font_input_hashes(inputs):
        raise ValueError('font candidate differs from current editable inputs')
    proof = objdiff_targets.verify_linked_bytes(sections(target.read_bytes(), 1)['.data'][1],
                                              original, 'font storage')
    unit = {'key': 'font', 'kind': 'rebuilt_asset', 'section': '.data', 'size': end - start,
            'rom_start': start, 'rom_end': end, 'source_inputs': hashes,
            'linked_inputs': linked_inputs,
            'target_path': 'font/target.o', 'target_sha256': objdiff_targets.sha256(target),
            'base_path': 'font/base.o', 'base_sha256': objdiff_targets.sha256(base),
            'literal_payload_matches_rom': candidate == original, 'target_verification': proof}
    item = {'name': 'assets/font_rle', 'target_path': unit['target_path'], 'base_path': unit['base_path'],
            'metadata': {'complete': False, 'progress_categories': ['data']}}
    return unit, item
