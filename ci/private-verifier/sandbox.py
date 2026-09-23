#!/usr/bin/env python3
"""Runs only inside the offline verifier container; stdout stays private."""
import json
from pathlib import Path
import shutil
import subprocess
import sys


def run(*command):
    subprocess.run(command, cwd='/workspace', check=True)


def verify_match(root, symbol, objects):
    """Compare actual source-unit bytes, including emitted boundary alignment.

    The interactive compiler omits unrelated GLOBAL_ASM members for fast
    iteration. That changes terminal alignment in mixed units. Compile the
    complete unit once here; never synthesize padding or shorten a raw span.
    Ordinary function-sized spans keep the project's focused relocation/alias
    proof. Cache that compilation by source too, rather than by function.
    """
    import diff
    import compile_c
    import layout_check
    import linked_aliases
    import candidate_tables

    source, regional_symbol, game = diff.find_work_item_by_id(symbol, 'us')
    diff.require_c_implementation(source, symbol)
    if source not in objects:
        candidate = root / 'build/private-check' / source.relative_to(root).with_suffix('.o')
        candidate.parent.mkdir(parents=True, exist_ok=True)
        run(*compile_c.compile_command('us', source, candidate))
        function, unit = layout_check.load_work_item(symbol, 'us')
        if unit is not None:
            layout_check.validate_layout(function, unit, layout_check.object_symbols(candidate),
                                         *layout_check.text_extent(candidate), 'us')
        focused_source = diff.focused_candidate_source('us', source)
        focused = candidate
        if focused_source != source:
            focused = root / 'build/private-focused' / source.relative_to(root).with_suffix('.o')
            focused.parent.mkdir(parents=True, exist_ok=True)
            run(*compile_c.compile_command('us', focused_source, focused))
        objects[source] = candidate, focused
    complete, focused = objects[source]
    assembly = diff.ensure_reference_function('us', regional_symbol, game_reference=game)
    size = diff.expected_function_size('us', regional_symbol)
    focused_object = candidate_tables.Object32(focused.read_bytes())
    symbols = [row for rows in focused_object.symbols.values() for row in rows if row[0] == regional_symbol]
    if len(symbols) != 1:
        raise ValueError('Expected one compiled C function symbol: ' + regional_symbol)
    # A short symbol needs real source-context bytes, not fabricated zeroes.
    candidate = complete if symbols[0][2] < size else focused
    reference = diff.reference_object('us', regional_symbol, game_reference=game, assembly=assembly)
    options = {}
    if game:
        original = candidate
        options['table_check'] = lambda: candidate_tables.verify_candidate(original, regional_symbol, assembly, size)
        function, _ = layout_check.load_work_item(symbol, 'us')
        pair = linked_aliases.prepare(root, candidate, reference, assembly, regional_symbol,
                                      int(function['regions']['us']['vram'], 16), size)
        if pair is not None:
            candidate, reference = pair
    result = diff.run_required_asm_diff(candidate, reference, regional_symbol,
                                        diff.write_settings('us', source), size,
                                        compact_mismatch=True, **options)
    if result:
        raise ValueError('Full registered-span comparison failed: ' + symbol)


def main():
    root = Path('/workspace')
    sys.path.insert(0, str(root / 'scripts'))
    # /workspace is a root-owned tmpfs mount; copy children without chmod on it.
    for source in Path('/candidate').iterdir():
        target = root / source.name
        if source.is_dir():
            shutil.copytree(source, target)
        else:
            shutil.copy2(source, target)
    plan = json.loads(Path('/plan.json').read_text())
    run('python3', 'scripts/project_state.py', 'setup', '--us', '/input/baserom.us.z64')
    run('python3', 'scripts/project_state.py', 'validate')
    run('python3', 'scripts/project_state.py', 'progress', '--check')
    run('make', '--silent', 'prepare-reference', 'PROFILE=us')
    run('make', '--silent', '--jobs', '4', 'profile-libs', 'PROFILE=us')
    run('make', '--silent', '--jobs', '4', 'build', 'PROFILE=us')
    run('make', '--silent', '--jobs', '4', 'game-libs')
    run('make', '--silent', '--jobs', '4', 'game-integrated-refresh', 'GAME_PROFILE=us')
    objects = {}
    failed = []
    for entry in plan['functions']:
        if entry['state'] == 'matched':
            try:
                verify_match(root, entry['symbol'], objects)
            except (ValueError, OSError, subprocess.CalledProcessError) as error:
                # Collect all failed IDs in private diagnostics, then fail closed.
                print(f"Private comparison failed for {entry['symbol']}: {error}", flush=True)
                failed.append(entry['symbol'])
        else:
            # Verify original-assembly proof without mutating inventory.
            import original_asm
            functions = json.loads((root / 'progress/functions.json').read_text())['functions']
            target = next(f for f in functions if f['symbol'] == entry['symbol'])
            proof = original_asm.verify(root, target)
            evidence = target['regions']['us']['evidence']
            for key in ('rom_sha1', 'span_sha256', 'assembly_sha256'):
                if proof[key] != evidence[key]:
                    raise ValueError('Original assembly proof changed')
    if failed:
        raise ValueError('Failed registered-span comparisons: ' + ', '.join(failed))
    run('python3', 'scripts/project_state.py', 'progress', '--check')


if __name__ == '__main__':
    main()
