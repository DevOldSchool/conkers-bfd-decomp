"""Independent data and rebuilt-asset targets for the published objdiff report."""
from __future__ import annotations

from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor
from functools import partial
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess

import binary_object
from build_jobs import job_count
import compile_c
import data_boundaries
import diff
from elf_sections import sections
import font_assets
import font_splits
import texture_build
import model_build
import model_morph_build
import event_build
import script_build
import sprite_build
import visibility_build
import route_build
import animation_control_build
import animation_bank_build
import scene_volume_build
import scene_field_build
import animation_clips_build
import sequence_build
import mp3_table_build
import mp3_spectral_build
import objdiff_storage
import sound_bank_build
import adpcm_build
import adpcm_layout
import asset_receipts
import normalize_asm
import objdiff
import objdiff_targets
import rom_span
import rzip_archive
from candidate_tables import Object32

ROOT = Path(__file__).resolve().parent.parent
OUTPUT = ROOT / 'build/us/objdiff-report/data'
# The MP3 encoders read literal decoder tables from a C source outside scripts/.
MP3_DECODER_SOURCE = mp3_table_build.ENCODER_EXTRA_SOURCES
assert MP3_DECODER_SOURCE == mp3_spectral_build.ENCODER_EXTRA_SOURCES
# ``./conker objdiff report --fresh`` sets this: every rebuilt asset is encoded
# again from its editable sources and build receipts are ignored.
FRESH_ENCODE = False


def family_receipts(family: str, module: str, *, extra: tuple[str, ...] = ()):
    """Load one asset family's build receipts; the fresh audit mode ignores them."""
    if FRESH_ENCODE:
        return asset_receipts.empty(family)
    return asset_receipts.load(ROOT, family, module, extra=extra)


def asset_candidate(receipts, name, *, hashes, extent, encode, ranged=False):
    return asset_receipts.candidate(ROOT, receipts, name, hashes=hashes, extent=extent,
                                    encode=encode, fresh=FRESH_ENCODE, ranged=ranged)


def candidate_provenance(provenance, candidate: bytes) -> dict:
    """Record whether a candidate was encoded now or reused from a build receipt."""
    provenance = provenance or asset_receipts.fresh_provenance()
    if provenance.get('candidate_source') not in asset_receipts.CANDIDATE_SOURCES:
        raise ValueError('rebuilt asset candidate has an unknown origin')
    record = {'candidate_source': provenance['candidate_source'],
              'payload_sha256': hashlib.sha256(candidate).hexdigest()}
    if 'receipt' in provenance:
        record['receipt'] = provenance['receipt']
    return record


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



def declared_data_symbols(path: Path) -> dict[str, tuple[int, int]]:
    """Read explicit payload extents from the canonical splat symbol file."""
    pattern = (r'^([A-Za-z_.$][\w.$]*)\s*=\s*(0x[0-9A-Fa-f]+);'
               r'[^\n]*?\bsize:(0x[0-9A-Fa-f]+)')
    return {name: (int(address, 16), int(size, 16))
            for name, address, size in re.findall(pattern, path.read_text(), re.M)}


def anonymous_declared_padding(text: str, declared: dict[str, tuple[int, int]]) -> str:
    """Keep verified zero padding as bytes, without inventing a data variable.

    Only an unreferenced pad emitted immediately after a canonical, explicitly
    sized payload qualifies. Unknown gaps, referenced labels and nonzero bytes
    retain their symbols. The complete assembled section still must match ROM.
    """
    block = re.compile(r'^\.globl (?P<name>[\w.$]+)\n(?P=name):\n'
                       r'(?P<body>.*?)^\.size (?P=name), \. - (?P=name)\n', re.M | re.S)
    rows = re.compile(r'/\*\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s+'
                      r'(?:([0-9A-Fa-f]+)\s+)?\*/\s+\.(word|short|byte|float|double)\s+(?:0x0+|0(?:\.0)?)')
    previous = None
    edits = []
    for match in block.finditer(text):
        body = match['body']
        if previous is not None and previous['name'] in declared:
            between = text[previous.end():match.start()].strip()
            marker = re.fullmatch(
                r'/\* Automatically generated and unreferenced pad'
                r'(?: \(generated by the size of [\w.$]+\))? \*/', between)
            address, size = declared[previous['name']]
            original_rows = re.findall(
                r'/\*\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s+', previous['body'])
            padding_rows = rows.findall(body)
            cursor = address + size
            valid = bool(marker and original_rows and padding_rows
                         and int(original_rows[0], 16) == address)
            valid = valid and not rows.sub('', body).strip()
            for row_address, raw, directive in padding_rows:
                width = {'word': 4, 'short': 2, 'byte': 1, 'float': 4, 'double': 8}[directive]
                valid = (valid and int(row_address, 16) == cursor
                         and (not raw or (len(raw) == width * 2 and int(raw, 16) == 0)))
                cursor += width
            valid = valid and cursor <= ((address + size + 15) & ~15)
            if valid:
                edits.append((match.start(), match.end(), body))
        previous = match
    for start, end, body in reversed(edits):
        text = text[:start] + body + text[end:]
    return text


def reference_assembly(assembly: str, section: str, *, output_section: str | None = None,
                       declared_symbols: dict[str, tuple[int, int]] | None = None) -> str:
    """Keep original row offsets when a range begins inside an aligned section.

    A double at runtime address 0x...4950 is aligned even when its mapped range
    starts at 0x...494C. GNU as otherwise inserts padding relative to offset zero.
    Disable implicit directive alignment; explicit original rows and the full
    linked-image comparison remain authoritative. Canonically sized payloads
    may leave verified padding anonymous; their symbols and sizes stay intact.
    """
    text = anonymous_declared_padding(normalize_asm.normalize(assembly), declared_symbols or {})
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
        # Spimdisasm defaults to applying explicit sizes only in .data.
        # Honor the same canonical payload extents in .rodata references.
        subprocess.run(['splat', 'split', str(config)], cwd=ROOT, stdout=log, stderr=log,
                       env={**os.environ, 'SPIMDISASM_CREATE_RODATA_PADS': 'True'}, check=True)
    symbol_file = ROOT / "config/symbols" / ("game-us.txt" if overlay == "game" else "us.txt")
    declared = declared_data_symbols(symbol_file)
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
        normalized.write_text(reference_assembly(assembly, assembly_section, output_section=section,
                                                   declared_symbols=declared))
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


def allocated_debugger_inputs(units: list[dict], output: Path) -> dict[str, str]:
    """Refresh the actual runtime link before considering source-data completion."""
    mapped = [u for u in units if u['kind'] == 'source_placement']
    if not mapped:
        return {}
    if any(u.get('overlay') != 'debugger' for u in mapped):
        raise ValueError('unsupported allocated source-data overlay')
    with (output / 'debugger-runtime-build.log').open('w') as log:
        subprocess.run(['make', '--silent', '--jobs', str(job_count()), 'build',
                        'PROFILE=us', 'ASSETS=0'], cwd=ROOT, stdout=log, stderr=log, check=True)
    import verify_debugger_rodata
    elf = ROOT / 'build/us/original-assets/conker.us.elf'
    verify_debugger_rodata.verify(elf)
    return {elf.relative_to(ROOT).as_posix(): objdiff_targets.sha256(elf)}


def same_source_object(candidate: Path, linked: Path) -> bool:
    """Compare actual storage and relocations, ignoring only debug/file metadata."""
    left, right = Object32(candidate.read_bytes()), Object32(linked.read_bytes())
    def storage(obj):
        parsed = sections(obj.data, 1)
        return {name: (header[1:4], header[5], header[8], payload)
                for name, (header, payload) in parsed.items()
                if header[2] & 2 and name not in ('.reginfo', '.MIPS.abiflags')}
    return (storage(left) == storage(right)
            and left.relocations == right.relocations
            and sorted(left.non_section_symbols) == sorted(right.non_section_symbols))


def prepare_candidates(units: list[dict], *, output: Path | None = None) -> list[dict]:
    output = OUTPUT if output is None else output
    config = []
    runtime_inputs = allocated_debugger_inputs(units, output)
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
                result = compile_c.run_compile('us', focused, base,
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
                elif unit['kind'] == 'source_placement':
                    linked = ROOT / ('build/us/' + unit['source'].removesuffix('.c') + '.o')
                    if not same_source_object(base, linked):
                        raise ValueError('debugger data candidate differs from actual linker input')
                    if unit['source'] == 'src/done/debugger/debugger_0000.c':
                        import debugger_assets
                        unit['source_inputs'] = {
                            (debugger_assets.DIRECTORY / name).as_posix():
                            objdiff_targets.sha256(ROOT / debugger_assets.DIRECTORY / name)
                            for name in ('glyphs.pgm', 'strings.json')}
                    unit.update(complete=True, data_completion_verified=True,
                                linked_inputs={**runtime_inputs,
                                    linked.relative_to(ROOT).as_posix(): objdiff_targets.sha256(linked)})
                    item['metadata']['complete'] = True
        config.append(item)
    return config


def font_input_hashes(directory: Path) -> dict[str, str]:
    manifest = json.loads((directory / 'manifest.json').read_text())
    paths = [directory / 'manifest.json'] + [font_assets.safe_manifest_file(directory, item['file'])
                                            for item in manifest['glyphs']]
    return {path.relative_to(ROOT).as_posix(): objdiff_targets.sha256(path) for path in paths}


def prepare_texture(rom: bytes, expected: dict, *, output: Path, receipts=None) -> tuple[dict, dict]:
    """Compare an actual PNG-built ROM link object with independent stored bytes."""
    index = expected['flat_index']
    name = texture_build.part_name(index)
    source = texture_build.input_directory(index, expected)
    inputs = ROOT / source
    if receipts is None:
        receipts = family_receipts('textures', 'scripts/texture_build.py')
    packed, hashes, provenance = asset_candidate(
        receipts, name, hashes=texture_build.input_hashes(inputs, expected), extent=expected,
        encode=lambda: texture_build.packed_texture(inputs, expected))
    return prepare_rebuilt_asset(
        rom, key=f'texture-{index:04d}', name=name, extent=expected, packed=packed, hashes=hashes,
        source_directory=source, read_hashes=partial(texture_build.input_hashes, inputs, expected),
        label=f'texture {index} RZIP storage', output=output, provenance=provenance)


def prepare_textures(rom: bytes, *, output: Path) -> tuple[list[dict], list[dict]]:
    """Validate selection once and rebuild all selected linker inputs in one Make call."""
    checked_rom, selected = texture_build.reviewed_textures(ROOT)
    if checked_rom != rom:
        raise ValueError('texture reference ROM differs from the validated report ROM')
    paths = ['build/us/assets/' + texture_build.part_name(e['flat_index']) + '.o' for e, _ in selected]
    build_rebuilt_objects(paths, 'texture', output)
    receipts = family_receipts('textures', 'scripts/texture_build.py')
    # Each reference has its own directory. Preserve catalog order and retain
    # all per-object checks; the report also rechecks every source hash at end.
    with ThreadPoolExecutor(max_workers=job_count()) as workers:
        pairs = list(workers.map(partial(prepare_texture, rom, output=output, receipts=receipts),
                                 (expected for expected, _ in selected)))
    return [unit for unit, _ in pairs], [item for _, item in pairs]


def prepare_rebuilt_asset(rom, *, key, name, extent, packed, hashes,
                          source_directory, read_hashes, label, output, provenance=None):
    """Compare one actual linker object with source-derived bytes and an independent target.

    ``packed`` comes from a fresh encode or from a build receipt whose inputs,
    encoder and output hashes re-derive from the checkout; ``provenance`` says
    which. Either way the candidate is compared against the ROM bytes here.
    """
    directory = output / key
    directory.mkdir(parents=True, exist_ok=True)
    linked = ROOT / ('build/us/assets/' + name + '.o')
    start, end = extent['rom_start'], extent['rom_end']
    original = rom[start:end]
    base, target = directory / 'base.o', directory / 'target.o'
    linked_bytes = linked.read_bytes()
    base.write_bytes(linked_bytes)
    relative = name + '.bin'
    reference = directory / relative
    reference.parent.mkdir(parents=True, exist_ok=True)
    reference.write_bytes(original)
    # Byte-identical to `ld -r -b binary` from this directory, without a process per asset.
    target.write_bytes(binary_object.binary_object(original, relative))
    for path in (base, target):
        target_extent(path, '.data', end - start)
    candidate = sections(base.read_bytes(), 1)['.data'][1]
    if (candidate != packed or hashes != read_hashes()
            or linked.read_bytes() != linked_bytes):
        raise ValueError(f'{label} candidate differs from current editable inputs')
    proof = objdiff_targets.verify_linked_bytes(sections(target.read_bytes(), 1)['.data'][1],
                                              original, label)
    unit = {'key': key, 'kind': 'rebuilt_asset', 'section': '.data',
            'size': end - start, 'rom_start': start, 'rom_end': end,
            'source_inputs': {(source_directory / p).as_posix(): h for p, h in hashes.items()},
            'linked_inputs': {linked.relative_to(ROOT).as_posix(): hashlib.sha256(linked_bytes).hexdigest()},
            'target_path': key + '/target.o', 'target_sha256': objdiff_targets.sha256(target),
            'base_path': key + '/base.o', 'base_sha256': objdiff_targets.sha256(base),
            'literal_payload_matches_rom': candidate == original, 'target_verification': proof,
            'report_code_bytes': 0, 'report_data_bytes': end - start, 'complete': candidate == original,
            **candidate_provenance(provenance, candidate)}
    item = {'name': 'assets/' + name, 'target_path': unit['target_path'],
            'base_path': unit['base_path'],
            'metadata': {'complete': unit['complete'], 'progress_categories': ['data']}}
    return unit, item


def model_receipts(banks) -> list:
    """Whole-catalog and per-bank model builds write separate receipt files."""
    return [family_receipts('models', 'scripts/model_build.py'),
            *(family_receipts(f'models/bank{bank:02d}', 'scripts/model_build.py') for bank in sorted(banks))]


def prepare_model(rom: bytes, expected: dict, *, output: Path, receipts=None) -> tuple[dict, dict]:
    index, bank = expected['entry'], expected['bank']
    source = model_build.input_directory(index, bank)
    name = model_build.part_name(index, bank)
    if receipts is None:
        receipts = model_receipts({bank})
    packed, hashes, provenance = asset_candidate(
        receipts, name, hashes=model_build.input_hashes(ROOT / source, expected), extent=expected,
        encode=lambda: model_build.packed_model(ROOT / source, expected))
    return prepare_rebuilt_asset(
        rom, key=f'model-{bank:02d}-{index:04d}', name=name,
        extent=expected, packed=packed, hashes=hashes, source_directory=source,
        read_hashes=partial(model_build.input_hashes, ROOT / source, expected),
        label=f'model {bank:02d}:{index:04d}', output=output, provenance=provenance)


# Set once the report refreshed every asset link object in one Make call.
_PREBUILT_ASSET_OBJECTS = False


def prebuild_asset_objects(output: Path) -> None:
    """Refresh all rebuilt asset link objects in one Make evaluation.

    Each later per-family request only checks that its objects exist. Make still
    decides what is stale; this removes one Makefile evaluation per family.
    """
    global _PREBUILT_ASSET_OBJECTS
    _PREBUILT_ASSET_OBJECTS = False
    output.mkdir(parents=True, exist_ok=True)
    log_path = output / 'asset-objects-build.log'
    with log_path.open('w') as log:
        try:
            subprocess.run(['make', '--silent', '--jobs', str(job_count()), 'asset-objects', 'PROFILE=us', 'ASSETS=1'],
                           cwd=ROOT, stdout=log, stderr=log, check=True)
        except subprocess.CalledProcessError as error:
            raise ValueError(f'asset link-object build failed (exit {error.returncode}); see {log_path}') from error
    _PREBUILT_ASSET_OBJECTS = True


def build_rebuilt_objects(paths, label, output):
    if _PREBUILT_ASSET_OBJECTS:
        missing = [path for path in paths if not (ROOT / path).is_file()]
        if missing:
            raise ValueError(f'{label}: {len(missing)} linker inputs missing after the asset-objects build, '
                             f'for example {missing[0]}')
        return
    log_path = output / (label + '-build.log')
    with log_path.open('w') as log:
        try:
            subprocess.run(['make', '--silent', '--jobs', str(job_count()), *paths, 'PROFILE=us', 'ASSETS=1'],
                           cwd=ROOT, stdout=log, stderr=log, check=True)
        except subprocess.CalledProcessError as error:
            raise ValueError(f'{label} linker-input build failed (exit {error.returncode}); see {log_path}') from error


def prepare_models(rom: bytes, *, output: Path) -> tuple[list[dict], list[dict]]:
    """Validate selection once and rebuild all selected linker inputs in one Make call."""
    checked_rom, selected = model_build.reviewed_models(ROOT)
    if checked_rom != rom:
        raise ValueError('model reference ROM differs from the validated report ROM')
    paths = ['build/us/assets/' + model_build.part_name(e['entry'], e['bank']) + '.o' for e, _ in selected]
    build_rebuilt_objects(paths, 'model', output)
    receipts = model_receipts({e['bank'] for e, _ in selected})
    # Each reference has its own directory. Preserve catalog order and retain
    # all per-object checks; the report also rechecks every source hash at end.
    with ThreadPoolExecutor(max_workers=job_count()) as workers:
        pairs = list(workers.map(partial(prepare_model, rom, output=output, receipts=receipts),
                                 (expected for expected, _ in selected)))
    return [unit for unit, _ in pairs], [item for _, item in pairs]


def prepare_sequence(rom: bytes, expected: dict, *, output: Path, receipts=None) -> tuple[dict, dict]:
    index = expected['entry']
    source = sequence_build.input_directory(index)
    name = sequence_build.part_name(index)
    if receipts is None:
        receipts = family_receipts('sequences', 'scripts/sequence_build.py')
    packed, hashes, provenance = asset_candidate(
        receipts, name, hashes=sequence_build.input_hashes(ROOT / source, expected), extent=expected,
        encode=lambda: sequence_build.packed_sequence(ROOT / source, expected))
    return prepare_rebuilt_asset(
        rom, key=f'sequence-{index:04d}', name=name,
        extent=expected, packed=packed, hashes=hashes, source_directory=source,
        read_hashes=partial(sequence_build.input_hashes, ROOT / source, expected),
        label=f'sequence {index:04d} compact-sequence storage', output=output, provenance=provenance)


def prepare_sequences(rom: bytes, *, output: Path) -> tuple[list[dict], list[dict]]:
    """Validate selection once and rebuild all selected linker inputs in one Make call."""
    checked_rom, selected = sequence_build.reviewed_sequences(ROOT)
    if checked_rom != rom:
        raise ValueError('sequence reference ROM differs from the validated report ROM')
    paths = ['build/us/assets/' + sequence_build.part_name(e['entry']) + '.o' for e, _ in selected]
    build_rebuilt_objects(paths, 'sequence', output)
    receipts = family_receipts('sequences', 'scripts/sequence_build.py')
    # Each reference has its own directory. Preserve catalog order and retain
    # all per-object checks; the report also rechecks every source hash at end.
    with ThreadPoolExecutor(max_workers=job_count()) as workers:
        pairs = list(workers.map(partial(prepare_sequence, rom, output=output, receipts=receipts),
                                 (expected for expected, _ in selected)))
    return [unit for unit, _ in pairs], [item for _, item in pairs]


def prepare_sound_part(rom: bytes, expected: dict, *, output: Path, receipts=None) -> tuple[dict, dict]:
    index = expected['part']
    source = sound_bank_build.input_directory(index)
    name = sound_bank_build.part_name(index)
    if receipts is None:
        receipts = family_receipts('sound-bank', 'scripts/sound_bank_build.py')
    packed, hashes, provenance = asset_candidate(
        receipts, name, hashes=sound_bank_build.input_hashes(ROOT / source, expected), extent=expected,
        encode=lambda: sound_bank_build.packed_part(ROOT / source, expected))
    return prepare_rebuilt_asset(
        rom, key=f'sound-bank-{index}', name=name,
        extent=expected, packed=packed, hashes=hashes, source_directory=source,
        read_hashes=partial(sound_bank_build.input_hashes, ROOT / source, expected),
        label=f'sound-bank part {index} sound-bank storage', output=output, provenance=provenance)


def prepare_sound_bank(rom: bytes, *, output: Path) -> tuple[list[dict], list[dict]]:
    """Validate selection once and rebuild all selected linker inputs in one Make call."""
    checked_rom, selected = sound_bank_build.reviewed_parts(ROOT)
    if checked_rom != rom:
        raise ValueError('sound-bank reference ROM differs from the validated report ROM')
    paths = ['build/us/assets/' + sound_bank_build.part_name(e['part']) + '.o' for e, _ in selected]
    build_rebuilt_objects(paths, 'sound-bank', output)
    receipts = family_receipts('sound-bank', 'scripts/sound_bank_build.py')
    # Each reference has its own directory. Preserve catalog order and retain
    # all per-object checks; the report also rechecks every source hash at end.
    with ThreadPoolExecutor(max_workers=job_count()) as workers:
        pairs = list(workers.map(partial(prepare_sound_part, rom, output=output, receipts=receipts),
                                 (expected for expected, _ in selected)))
    return [unit for unit, _ in pairs], [item for _, item in pairs]


def prepare_adpcm_sample(rom: bytes, expected: dict, *, output: Path, receipts=None) -> list[tuple[dict, dict]]:
    """Encode the complete sample unless every part's build receipt re-derives from the checkout.

    Reuse needs the receipt's input hashes, encoder hash and output hash to match the
    current inputs, encoder and built part; otherwise the whole sample is encoded
    again. Either way each part is compared against the ROM bytes here.
    """
    sample = expected['sample']
    source = adpcm_build.input_directory(sample)
    if receipts is None:
        receipts = family_receipts('adpcm', 'scripts/adpcm_build.py')
    hashes = adpcm_build.input_hashes(ROOT / source, expected)
    reused = [asset_receipts.reusable(ROOT, receipts, adpcm_layout.part_name(sample, part['first_frame']),
                                      hashes=hashes, extent=part, fresh=FRESH_ENCODE)
              for part in expected['parts']]
    if reused and all(item is not None for item in reused):
        parts = [((part, item.packed), item.provenance) for part, item in zip(expected['parts'], reused)]
    else:
        encoded, hashes = adpcm_build.packed_sample(ROOT / source, expected)
        parts = [(pair, asset_receipts.fresh_provenance()) for pair in encoded]
    return [prepare_rebuilt_asset(
        rom, key=f'adpcm-{sample:04d}-{part["first_frame"]:08X}',
        name=adpcm_layout.part_name(sample, part['first_frame']), extent=part,
        packed=packed, hashes=hashes, source_directory=source,
        read_hashes=partial(adpcm_build.input_hashes, ROOT / source, expected),
        label=f'ADPCM sample {sample}', output=output, provenance=provenance)
        for (part, packed), provenance in parts]


def initialize_adpcm_report_worker(root, rom, output, receipts=None, fresh=False):
    # Pass the ROM and receipts once per process, not once per sample. Explicit
    # initialization works with spawn as well as fork, including a caller's isolated checkout.
    global ROOT, FRESH_ENCODE, _ADPCM_REPORT_ROM, _ADPCM_REPORT_OUTPUT, _ADPCM_REPORT_RECEIPTS
    ROOT, FRESH_ENCODE, _ADPCM_REPORT_ROM, _ADPCM_REPORT_OUTPUT = root, fresh, rom, output
    _ADPCM_REPORT_RECEIPTS = receipts


def prepare_adpcm_report_worker(expected):
    return prepare_adpcm_sample(_ADPCM_REPORT_ROM, expected, output=_ADPCM_REPORT_OUTPUT,
                                receipts=_ADPCM_REPORT_RECEIPTS)


def prepare_adpcm(rom: bytes, *, output: Path) -> tuple[list[dict], list[dict]]:
    checked_rom, selected = adpcm_build.reviewed_samples(ROOT)
    if checked_rom != rom:
        raise ValueError('ADPCM reference ROM differs from the validated report ROM')
    paths = ['build/us/assets/' + adpcm_layout.part_name(e['sample'], p['first_frame']) + '.o'
             for e, _, _ in selected for p in e['parts']]
    build_rebuilt_objects(paths, 'adpcm', output)
    receipts = family_receipts('adpcm', 'scripts/adpcm_build.py')
    with ProcessPoolExecutor(max_workers=job_count(),
                             initializer=initialize_adpcm_report_worker,
                             initargs=(ROOT, rom, output, receipts, FRESH_ENCODE)) as workers:
        groups = list(workers.map(prepare_adpcm_report_worker,
                                  (expected for expected, _, _ in selected), chunksize=8))
    pairs = [pair for group in groups for pair in group]
    return [unit for unit, _ in pairs], [item for _, item in pairs]


def prepare_font(rom: bytes, *, output: Path | None = None) -> tuple[dict, dict]:
    directory = (OUTPUT if output is None else output) / 'font'
    directory.mkdir(parents=True, exist_ok=True)
    layout = font_assets.load_layout('us')
    ranges = font_splits.verify_splits(ROOT / 'config/profiles/us.yaml', rom, layout)
    paths = [ROOT / ('build/us/assets/' + name + '.o') for _, _, name in ranges]
    if _PREBUILT_ASSET_OBJECTS:
        build_rebuilt_objects([str(p.relative_to(ROOT)) for p in paths], 'font', directory)
    else:
        with (directory / 'build.log').open('w') as log:
            subprocess.run(['make', '--silent', '--jobs', str(job_count()), *[str(p.relative_to(ROOT)) for p in paths], 'PROFILE=us', 'ASSETS=1'],
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
            'literal_payload_matches_rom': candidate == original, 'target_verification': proof,
            **candidate_provenance(None, candidate)}
    item = {'name': 'assets/font_rle', 'target_path': unit['target_path'], 'base_path': unit['base_path'],
            'metadata': {'complete': False, 'progress_categories': ['data']}}
    return unit, item


def prepare_mp3_table(rom: bytes, expected: dict, part: dict, *, output: Path, receipts=None) -> tuple[dict, dict]:
    source = mp3_table_build.INPUT_DIRECTORY
    name = mp3_table_build.part_name(part['name'])
    if receipts is None:
        receipts = family_receipts('mp3-tables', 'scripts/mp3_table_build.py', extra=MP3_DECODER_SOURCE)
    packed, hashes, provenance = asset_candidate(
        receipts, name, hashes=mp3_table_build.input_hashes(ROOT / source, expected), extent=part,
        encode=lambda: _packed_mp3_table(part['name'], expected, source))
    return prepare_rebuilt_asset(
        rom, key=part['name'], name=name,
        extent=part, packed=packed, hashes=hashes, source_directory=source,
        read_hashes=partial(mp3_table_build.input_hashes, ROOT / source, expected),
        label=f"MP3 decoder {part['name']} storage", output=output, provenance=provenance)


def _packed_mp3_table(name, expected, source):
    packed, hashes = mp3_table_build.packed_tables(ROOT / source, expected)
    return packed[name], hashes


def prepare_mp3_tables(rom: bytes, *, output: Path) -> tuple[list[dict], list[dict]]:
    checked_rom, expected, _ = mp3_table_build.reviewed_tables(ROOT)
    if checked_rom != rom:
        raise ValueError('MP3 table reference ROM differs from the validated report ROM')
    paths = ['build/us/assets/' + mp3_table_build.part_name(p['name']) + '.o' for p in expected['parts']]
    build_rebuilt_objects(paths, 'mp3-tables', output)
    receipts = family_receipts('mp3-tables', 'scripts/mp3_table_build.py', extra=MP3_DECODER_SOURCE)
    pairs = [prepare_mp3_table(rom, expected, part, output=output, receipts=receipts) for part in expected['parts']]
    return [unit for unit, _ in pairs], [item for _, item in pairs]


def prepare_morph_bank(rom: bytes, expected: dict, *, output: Path, receipts=None) -> tuple[dict, dict]:
    source = model_morph_build.INPUT_DIRECTORY
    if receipts is None:
        receipts = family_receipts('morphs', 'scripts/model_morph_build.py')
    packed, hashes, provenance = asset_candidate(
        receipts, model_morph_build.PART_NAME, hashes=model_morph_build.input_hashes(ROOT / source, expected),
        extent=expected, encode=lambda: model_morph_build.packed_bank(ROOT / source, expected))
    return prepare_rebuilt_asset(
        rom, key='morph-bank', name=model_morph_build.PART_NAME,
        extent=expected, packed=packed, hashes=hashes, source_directory=source,
        read_hashes=partial(model_morph_build.input_hashes, ROOT / source, expected),
        label='character morph bank storage', output=output, provenance=provenance)


def prepare_morphs(rom: bytes, *, output: Path) -> tuple[list[dict], list[dict]]:
    checked_rom, expected, _ = model_morph_build.reviewed_bank(ROOT)
    if checked_rom != rom:
        raise ValueError('morph reference ROM differs from validated report ROM')
    build_rebuilt_objects(['build/us/assets/' + model_morph_build.PART_NAME + '.o'], 'morph', output)
    unit, item = prepare_morph_bank(rom, expected, output=output)
    return [unit], [item]

def prepare_rebuilt_ranges(original_bank, expected, *, source, packed, fresh_spans, hashes,
                           key, name, linked, ranges, read_hashes, output, provenance=None):
    """Credit only disjoint regenerated slices of an independently checked linked object.

    ``packed`` and ``fresh_spans`` come from a fresh encode or from a build receipt
    that re-derives from the checkout; ``provenance`` records which. The slices are
    compared against the original ROM bytes here in both cases.
    """
    if len(original_bank) != expected['rom_end'] - expected['rom_start']:
        raise ValueError('asset reference extent differs from reviewed object')
    directory = output / key
    directory.mkdir(parents=True, exist_ok=True)
    linked_bytes = linked.read_bytes()
    target_extent(linked, '.data', expected['rom_end'] - expected['rom_start'])
    actual = sections(linked_bytes, 1)['.data'][1]
    if actual != packed:
        raise ValueError('asset linked candidate differs from current semantic and backing inputs')
    fresh_ranges = [[expected['rom_start'] + start, expected['rom_start'] + start + len(payload)]
                    for start, payload in fresh_spans]
    size = sum(end - start for start, end in ranges)
    objdiff_storage.rebuilt_ranges({'rom_ranges': ranges, 'size': size})
    if (ranges != fresh_ranges
            or any(not expected['rom_start'] <= start < end <= expected['rom_end'] for start, end in ranges)):
        raise ValueError('asset report ranges differ from the generated bank')
    candidate = b''.join(actual[start - expected['rom_start']:end - expected['rom_start']]
                         for start, end in ranges)
    fresh = b''.join(payload for _, payload in fresh_spans)
    original = b''.join(original_bank[start - expected['rom_start']:end - expected['rom_start']] for start, end in ranges)
    if candidate != fresh or candidate != original:
        raise ValueError('asset ranges differ from fresh semantic sources or original ROM')
    # Native objects contain only the proved slices, in physical ROM order.
    # Index, padding and nonmatching entries remain in the raw-storage target.
    relative = name + '.bin'
    base, target = directory / 'base.o', directory / 'target.o'
    base.write_bytes(binary_object.binary_object(candidate, relative))
    target.write_bytes(binary_object.binary_object(original, relative))
    for path in (base, target):
        target_extent(path, '.data', size)
    proof = objdiff_targets.verify_linked_bytes(sections(target.read_bytes(), 1)['.data'][1],
                                              original, 'asset semantic ranges')
    if (hashes != read_hashes()
            or linked.read_bytes() != linked_bytes):
        raise ValueError('asset source or ROM linker object changed during report preparation')
    sources = {(ROOT / source / path).resolve().relative_to(ROOT.resolve()).as_posix(): digest
               for path, digest in hashes.items()}
    unit = {'key': key, 'kind': 'rebuilt_asset', 'section': '.data', 'size': size,
            'rom_ranges': ranges, 'linked_rom_start': expected['rom_start'], 'linked_rom_end': expected['rom_end'],
            'source_inputs': sources, 'linked_inputs': {linked.relative_to(ROOT).as_posix(): hashlib.sha256(linked_bytes).hexdigest()},
            'target_path': key + '/target.o', 'target_sha256': objdiff_targets.sha256(target),
            'base_path': key + '/base.o', 'base_sha256': objdiff_targets.sha256(base),
            'literal_payload_matches_rom': True, 'target_verification': proof,
            'report_code_bytes': 0, 'report_data_bytes': size, 'complete': True,
            **candidate_provenance(provenance, actual)}
    item = {'name': 'assets/' + name, 'target_path': unit['target_path'], 'base_path': unit['base_path'],
            'metadata': {'complete': True, 'progress_categories': ['data']}}
    return unit, item



def prepare_visibility_bank(rom: bytes, expected: dict, *, output: Path, receipts=None) -> tuple[dict, dict]:
    """Report only regenerated physical ranges of the actual linked object."""
    source = visibility_build.INPUT_DIRECTORY
    if receipts is None:
        receipts = family_receipts('visibility', 'scripts/visibility_build.py')
    packed, fresh_spans, hashes, provenance = asset_candidate(
        receipts, visibility_build.PART_NAME, hashes=visibility_build.input_hashes(ROOT / source, expected),
        extent=expected, encode=lambda: visibility_build.packed_bank(ROOT / source, expected), ranged=True)
    key = 'visibility-bank'
    name = 'visibility/bank05'
    return prepare_rebuilt_ranges(
        rom[expected['rom_start']:expected['rom_end']], expected, source=source,
        packed=packed, fresh_spans=fresh_spans, hashes=hashes, key=key, name=name,
        linked=ROOT / ('build/us/assets/' + visibility_build.PART_NAME + '.o'), ranges=expected['rom_ranges'],
        read_hashes=lambda: visibility_build.input_hashes(ROOT / source, expected), output=output,
        provenance=provenance)



def prepare_visibility(rom: bytes, *, output: Path) -> tuple[list[dict], list[dict]]:
    checked_rom, expected, _ = visibility_build.reviewed_bank(ROOT)
    if checked_rom != rom:
        raise ValueError('visibility reference ROM differs from validated report ROM')
    build_rebuilt_objects(['build/us/assets/' + visibility_build.PART_NAME + '.o'], 'visibility', output)
    unit, item = prepare_visibility_bank(rom, expected, output=output)
    return [unit], [item]


def prepare_sprite_bank(rom: bytes, expected: dict, *, output: Path, receipts=None) -> tuple[dict, dict]:
    """Report only regenerated physical ranges of the actual linked object."""
    source = sprite_build.INPUT_DIRECTORY
    if receipts is None:
        receipts = family_receipts('sprites', 'scripts/sprite_build.py')
    packed, fresh_spans, hashes, provenance = asset_candidate(
        receipts, sprite_build.PART_NAME, hashes=sprite_build.input_hashes(ROOT / source, expected),
        extent=expected, encode=lambda: sprite_build.packed_bank(ROOT / source, expected), ranged=True)
    key = 'sprite-bank'
    name = 'sprites/bank00'
    return prepare_rebuilt_ranges(
        rom[expected['rom_start']:expected['rom_end']], expected, source=source,
        packed=packed, fresh_spans=fresh_spans, hashes=hashes, key=key, name=name,
        linked=ROOT / ('build/us/assets/' + sprite_build.PART_NAME + '.o'), ranges=expected['rom_ranges'],
        read_hashes=lambda: sprite_build.input_hashes(ROOT / source, expected), output=output,
        provenance=provenance)



def prepare_sprites(rom: bytes, *, output: Path) -> tuple[list[dict], list[dict]]:
    checked_rom, expected, _ = sprite_build.reviewed_bank(ROOT)
    if checked_rom != rom:
        raise ValueError('sprite reference ROM differs from validated report ROM')
    build_rebuilt_objects(['build/us/assets/' + sprite_build.PART_NAME + '.o'], 'sprites', output)
    unit, item = prepare_sprite_bank(rom, expected, output=output)
    return [unit], [item]


def prepare_mp3_spectral_stream(original: bytes, expected: dict, *, output: Path, receipts=None) -> tuple[dict, dict]:
    index = expected['entry']
    source = mp3_spectral_build.input_directory(index)
    if receipts is None:
        receipts = family_receipts('mp3-spectral', 'scripts/mp3_spectral_build.py', extra=MP3_DECODER_SOURCE)
    packed, fresh_spans, hashes, provenance = asset_candidate(
        receipts, mp3_spectral_build.part_name(index),
        hashes=mp3_spectral_build.input_hashes(ROOT / source, expected),
        extent={'rom_start': expected['rom_start'], 'rom_end': expected['rom_end']},
        encode=lambda: mp3_spectral_build.packed_stream(
            ROOT / source, expected, include_partial=True,
            # The audit mode re-encodes from coefficients; the span cache is
            # another receipt-like shortcut it must not take.
            cache_directory=None if FRESH_ENCODE else ROOT / 'build/us/mp3-spectral/cache'), ranged=True)
    ranges, _, _ = mp3_spectral_build.codec.reviewed_ranges(original, include_partial=True)
    return prepare_rebuilt_ranges(
        original, expected, source=source, packed=packed, fresh_spans=fresh_spans, hashes=hashes,
        key=f'mp3-spectral-{index:04d}', name=f'audio/mp3/spectral/{index:04d}',
        linked=ROOT / ('build/us/assets/' + mp3_spectral_build.part_name(index) + '.o'),
        ranges=[[expected['rom_start'] + a, expected['rom_start'] + z] for a, z in ranges],
        read_hashes=lambda: mp3_spectral_build.input_hashes(ROOT / source, expected), output=output,
        provenance=provenance)


def initialize_mp3_spectral_report_worker(root, output, receipts=None, fresh=False):
    global ROOT, FRESH_ENCODE, _SPECTRAL_OUTPUT, _SPECTRAL_RECEIPTS
    ROOT, FRESH_ENCODE, _SPECTRAL_OUTPUT, _SPECTRAL_RECEIPTS = root, fresh, output, receipts


def prepare_mp3_spectral_report_worker(task):
    expected, original = task
    return prepare_mp3_spectral_stream(original, expected, output=_SPECTRAL_OUTPUT,
                                       receipts=_SPECTRAL_RECEIPTS)


def prepare_mp3_spectral(rom: bytes, *, output: Path) -> tuple[list[dict], list[dict]]:
    mp3_spectral_build.prune_legacy_cache(ROOT / 'build/us/mp3-spectral/cache')
    checked_rom, selected = mp3_spectral_build.reviewed_streams(ROOT)
    if checked_rom != rom:
        raise ValueError('spectral reference ROM differs from validated report ROM')
    paths = ['build/us/assets/' + mp3_spectral_build.part_name(e['entry']) + '.o' for e, _ in selected]
    build_rebuilt_objects(paths, 'mp3-spectral', output)
    receipts = family_receipts('mp3-spectral', 'scripts/mp3_spectral_build.py', extra=MP3_DECODER_SOURCE)
    with ProcessPoolExecutor(max_workers=job_count(), initializer=initialize_mp3_spectral_report_worker,
                             initargs=(ROOT, output, receipts, FRESH_ENCODE)) as workers:
        pairs = list(workers.map(prepare_mp3_spectral_report_worker, selected, chunksize=4))
    return [unit for unit, _ in pairs], [item for _, item in pairs]



def prepare_script_bank(rom: bytes, expected: dict, *, output: Path, receipts=None) -> tuple[dict, dict]:
    source = script_build.INPUT_DIRECTORY
    if receipts is None:
        receipts = family_receipts('scripts', 'scripts/script_build.py')
    packed, hashes, provenance = asset_candidate(
        receipts, script_build.PART_NAME, hashes=script_build.input_hashes(ROOT / source, expected),
        extent=expected, encode=lambda: script_build.packed_bank(ROOT / source, expected))
    return prepare_rebuilt_asset(
        rom, key='script-bank', name=script_build.PART_NAME,
        extent=expected, packed=packed, hashes=hashes, source_directory=source,
        read_hashes=partial(script_build.input_hashes, ROOT / source, expected),
        label='script program bank storage', output=output, provenance=provenance)


def prepare_scripts(rom: bytes, *, output: Path) -> tuple[list[dict], list[dict]]:
    checked_rom, expected, _ = script_build.reviewed_bank(ROOT)
    if checked_rom != rom:
        raise ValueError('script reference ROM differs from validated report ROM')
    build_rebuilt_objects(['build/us/assets/' + script_build.PART_NAME + '.o'], 'scripts', output)
    unit, item = prepare_script_bank(rom, expected, output=output)
    return [unit], [item]

def prepare_event_bank(rom: bytes, expected: dict, *, output: Path, receipts=None) -> tuple[dict, dict]:
    source = event_build.INPUT_DIRECTORY
    if receipts is None:
        receipts = family_receipts('events', 'scripts/event_build.py')
    packed, hashes, provenance = asset_candidate(
        receipts, event_build.PART_NAME, hashes=event_build.input_hashes(ROOT / source, expected),
        extent=expected, encode=lambda: event_build.packed_bank(ROOT / source, expected))
    return prepare_rebuilt_asset(
        rom, key='event-bank', name=event_build.PART_NAME,
        extent=expected, packed=packed, hashes=hashes, source_directory=source,
        read_hashes=partial(event_build.input_hashes, ROOT / source, expected),
        label='event program bank storage', output=output, provenance=provenance)


def prepare_events(rom: bytes, *, output: Path) -> tuple[list[dict], list[dict]]:
    checked_rom, expected, _ = event_build.reviewed_bank(ROOT)
    if checked_rom != rom:
        raise ValueError('event reference ROM differs from validated report ROM')
    build_rebuilt_objects(['build/us/assets/' + event_build.PART_NAME + '.o'], 'events', output)
    unit, item = prepare_event_bank(rom, expected, output=output)
    return [unit], [item]

def prepare_scene_volume_bank(rom: bytes, expected: dict, *, output: Path, receipts=None) -> tuple[dict, dict]:
    """Report only regenerated physical ranges of the actual linked object."""
    source = scene_volume_build.INPUT_DIRECTORY
    if receipts is None:
        receipts = family_receipts('scene-volumes', 'scripts/scene_volume_build.py')
    packed, fresh_spans, hashes, provenance = asset_candidate(
        receipts, scene_volume_build.PART, hashes=scene_volume_build.input_hashes(ROOT / source, expected),
        extent=expected, encode=lambda: scene_volume_build.packed_bank(ROOT / source, expected), ranged=True)
    key = 'scene-volumes'
    name = 'scenes/volumes'
    return prepare_rebuilt_ranges(
        rom[expected['rom_start']:expected['rom_end']], expected, source=source,
        packed=packed, fresh_spans=fresh_spans, hashes=hashes, key=key, name=name,
        linked=ROOT / ('build/us/assets/' + scene_volume_build.PART + '.o'), ranges=expected['rom_ranges'],
        read_hashes=lambda: scene_volume_build.input_hashes(ROOT / source, expected), output=output,
        provenance=provenance)


def prepare_scene_volumes(rom: bytes, *, output: Path) -> tuple[list[dict], list[dict]]:
    checked_rom, expected, _ = scene_volume_build.reviewed_bank(ROOT)
    if checked_rom != rom:
        raise ValueError('scene reference ROM differs from validated report ROM')
    build_rebuilt_objects(['build/us/assets/' + scene_volume_build.PART + '.o'], 'scene volumes', output)
    unit, item = prepare_scene_volume_bank(rom, expected, output=output)
    return [unit], [item]

def prepare_scene_field_bank(rom: bytes, expected: dict, *, output: Path, receipts=None) -> tuple[dict, dict]:
    """Report only regenerated physical ranges of the actual linked object."""
    source = scene_field_build.INPUT_DIRECTORY
    if receipts is None:
        receipts = family_receipts('scene-fields', 'scripts/scene_field_build.py')
    packed, fresh_spans, hashes, provenance = asset_candidate(
        receipts, scene_field_build.PART, hashes=scene_field_build.input_hashes(ROOT / source, expected),
        extent=expected, encode=lambda: scene_field_build.packed_bank(ROOT / source, expected), ranged=True)
    key = 'scene-fields'
    name = 'scenes/fields'
    return prepare_rebuilt_ranges(
        rom[expected['rom_start']:expected['rom_end']], expected, source=source,
        packed=packed, fresh_spans=fresh_spans, hashes=hashes, key=key, name=name,
        linked=ROOT / ('build/us/assets/' + scene_field_build.PART + '.o'), ranges=expected['rom_ranges'],
        read_hashes=lambda: scene_field_build.input_hashes(ROOT / source, expected), output=output,
        provenance=provenance)


def prepare_scene_fields(rom: bytes, *, output: Path) -> tuple[list[dict], list[dict]]:
    checked_rom, expected, _ = scene_field_build.reviewed_bank(ROOT)
    if checked_rom != rom:
        raise ValueError('scene reference ROM differs from validated report ROM')
    build_rebuilt_objects(['build/us/assets/' + scene_field_build.PART + '.o'], 'scene fields', output)
    unit, item = prepare_scene_field_bank(rom, expected, output=output)
    return [unit], [item]


def prepare_animation_bank_object(rom: bytes, expected: dict, *, output: Path, receipts=None) -> tuple[dict, dict]:
    """Report only regenerated physical ranges of the actual linked object."""
    source = animation_bank_build.input_directory(expected['bank'])
    if receipts is None:
        receipts = family_receipts('animation-bank', 'scripts/animation_bank_build.py')
    packed, fresh_spans, hashes, provenance = asset_candidate(
        receipts, animation_bank_build.part_name(expected['bank']), hashes=animation_bank_build.input_hashes(ROOT / source, expected),
        extent=expected, encode=lambda: animation_bank_build.packed_bank(ROOT / source, expected), ranged=True)
    key = f'animation-bank{expected["bank"]:02X}'
    name = f'animations/bank{expected["bank"]:02X}'
    return prepare_rebuilt_ranges(
        rom[expected['rom_start']:expected['rom_end']], expected, source=source,
        packed=packed, fresh_spans=fresh_spans, hashes=hashes, key=key, name=name,
        linked=ROOT / ('build/us/assets/' + animation_bank_build.part_name(expected['bank']) + '.o'), ranges=expected['rom_ranges'],
        read_hashes=lambda: animation_bank_build.input_hashes(ROOT / source, expected), output=output,
        provenance=provenance)



def prepare_animation_bank(rom: bytes, *, output: Path) -> tuple[list[dict], list[dict]]:
    units, configs = [], []
    for bank in animation_bank_build.BANKS:
        checked_rom, expected, _ = animation_bank_build.reviewed_bank(bank, ROOT)
        if checked_rom != rom:
            raise ValueError('animation reference ROM differs from validated report ROM')
        build_rebuilt_objects(['build/us/assets/' + animation_bank_build.part_name(bank) + '.o'], 'animation bank', output)
        unit, item = prepare_animation_bank_object(rom, expected, output=output)
        units.append(unit); configs.append(item)
    return units, configs


def prepare_animation_control_bank(rom: bytes, expected: dict, *, output: Path, receipts=None) -> tuple[dict, dict]:
    """Report only regenerated physical ranges of the actual linked object."""
    source = animation_control_build.input_directory(expected['bank'])
    if receipts is None:
        receipts = family_receipts('animation-control', 'scripts/animation_control_build.py')
    packed, fresh_spans, hashes, provenance = asset_candidate(
        receipts, animation_control_build.part_name(expected['bank']), hashes=animation_control_build.input_hashes(ROOT / source, expected),
        extent=expected, encode=lambda: animation_control_build.packed_bank(ROOT / source, expected), ranged=True)
    key = f'animation-control-bank{expected["bank"]:02X}'
    name = f'animation-controls/bank{expected["bank"]:02X}'
    return prepare_rebuilt_ranges(
        rom[expected['rom_start']:expected['rom_end']], expected, source=source,
        packed=packed, fresh_spans=fresh_spans, hashes=hashes, key=key, name=name,
        linked=ROOT / ('build/us/assets/' + animation_control_build.part_name(expected['bank']) + '.o'), ranges=expected['rom_ranges'],
        read_hashes=lambda: animation_control_build.input_hashes(ROOT / source, expected), output=output,
        provenance=provenance)



def prepare_animation_controls(rom: bytes, *, output: Path) -> tuple[list[dict], list[dict]]:
    units, configs = [], []
    for bank in animation_control_build.BANKS:
        checked_rom, expected, _ = animation_control_build.reviewed_bank(bank, ROOT)
        if checked_rom != rom:
            raise ValueError('animation control reference ROM differs from validated report ROM')
        build_rebuilt_objects(['build/us/assets/' + animation_control_build.part_name(bank) + '.o'], 'animation controls', output)
        unit, item = prepare_animation_control_bank(rom, expected, output=output)
        units.append(unit); configs.append(item)
    return units, configs


def prepare_route_bank(rom: bytes, expected: dict, *, output: Path, receipts=None) -> tuple[dict, dict]:
    """Report only regenerated physical ranges of the actual linked object."""
    source = route_build.input_directory(expected['bank'])
    if receipts is None:
        receipts = family_receipts('routes', 'scripts/route_build.py')
    packed, fresh_spans, hashes, provenance = asset_candidate(
        receipts, route_build.part_name(expected['bank']), hashes=route_build.input_hashes(ROOT / source, expected),
        extent=expected, encode=lambda: route_build.packed_bank(ROOT / source, expected), ranged=True)
    key = f'route-bank{expected["bank"]:02X}'
    name = f'routes/bank{expected["bank"]:02X}'
    return prepare_rebuilt_ranges(
        rom[expected['rom_start']:expected['rom_end']], expected, source=source,
        packed=packed, fresh_spans=fresh_spans, hashes=hashes, key=key, name=name,
        linked=ROOT / ('build/us/assets/' + route_build.part_name(expected['bank']) + '.o'), ranges=expected['rom_ranges'],
        read_hashes=lambda: route_build.input_hashes(ROOT / source, expected), output=output,
        provenance=provenance)



def prepare_routes(rom: bytes, *, output: Path) -> tuple[list[dict], list[dict]]:
    units, configs = [], []
    for bank in route_build.BANKS:
        checked_rom, expected, _ = route_build.reviewed_bank(bank, ROOT)
        if checked_rom != rom:
            raise ValueError('route reference ROM differs from validated report ROM')
        build_rebuilt_objects(['build/us/assets/' + route_build.part_name(bank) + '.o'], 'routes', output)
        unit, item = prepare_route_bank(rom, expected, output=output)
        units.append(unit); configs.append(item)
    return units, configs


def prepare_animation_clips_object(rom: bytes, expected: dict, *, output: Path, receipts=None) -> tuple[dict, dict]:
    """Report only regenerated physical ranges of the actual linked object."""
    source = animation_clips_build.input_directory(expected['part'])
    if receipts is None:
        receipts = family_receipts('animation-clips', 'scripts/animation_clips_build.py')
    packed, fresh_spans, hashes, provenance = asset_candidate(
        receipts, animation_clips_build.part_name(expected['part']), hashes=animation_clips_build.input_hashes(ROOT / source, expected),
        extent=expected, encode=lambda: animation_clips_build.packed_object(ROOT / source, expected), ranged=True)
    key = f'animation-clips-{expected["part"]}'
    name = f'animations/partial/{expected["part"]}'
    return prepare_rebuilt_ranges(
        rom[expected['rom_start']:expected['rom_end']], expected, source=source,
        packed=packed, fresh_spans=fresh_spans, hashes=hashes, key=key, name=name,
        linked=ROOT / ('build/us/assets/' + animation_clips_build.part_name(expected['part']) + '.o'), ranges=expected['rom_ranges'],
        read_hashes=lambda: animation_clips_build.input_hashes(ROOT / source, expected), output=output,
        provenance=provenance)


def prepare_animation_clips(rom: bytes, *, output: Path) -> tuple[list[dict], list[dict]]:
    checked_rom, selected = animation_clips_build.reviewed_objects(ROOT)
    if checked_rom != rom:
        raise ValueError('partial animation reference ROM differs from validated report ROM')
    paths = ['build/us/assets/' + animation_clips_build.part_name(e['part']) + '.o' for e, _ in selected]
    build_rebuilt_objects(paths, 'animation clips', output)
    pairs = [prepare_animation_clips_object(rom, expected, output=output) for expected, _ in selected]
    return [unit for unit, _ in pairs], [item for _, item in pairs]
