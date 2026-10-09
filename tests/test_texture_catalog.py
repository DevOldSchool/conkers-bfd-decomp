"""Runtime resource identity, full-payload proof, and duplicate storage guards."""
import hashlib
from contextlib import ExitStack
from pathlib import Path
from types import SimpleNamespace
import unittest
from unittest.mock import patch

from scripts import texture_assets as t, texture_catalog as catalog
from scripts.rzip_archive import FlatRzipEntry


class TextureCatalogTests(unittest.TestCase):
    def resolve(self, *, conflicting=False, wrong_rom=False, hud=False):
        rom = b'synthetic ROM'
        # Empty slots 1 and 2: runtime ID 3 is physical stream 1.
        entries = (FlatRzipEntry(0, 0, 4, b'header'),
                   FlatRzipEntry(3, 4, 8, b'p' * 1056))
        record = {'flat_index': 3, 'rom_start': '0x4', 'rom_end': '0x8',
                  'width': 16, 'height': 34, 'preview_width': 32, 'preview_height': 17,
                  'row_layout': 'linear'}
        digest = hashlib.sha1(rom).hexdigest()
        manifest = {'normalized_sha1': digest, 'textures': [record]}
        empty = dict(manifest, textures=[])
        rectangular = {'normalized_sha1': 'wrong' if wrong_rom else digest,
                       'proven_textures': [],
                       'runtime_tiled_ci4_contract': {'groups': [
                           {'views': [{'first_flat_index': 3, 'last_flat_index': 3}]}]}}
        with ExitStack() as stack:
            def mock(obj, name, **kwargs):
                return stack.enter_context(patch.object(obj, name, **kwargs))
            mock(catalog, 'runtime_context', return_value=(
                {'flat_assets_start': 0}, entries, SimpleNamespace(sprites=())))
            ci8 = mock(catalog.texture_ci8, 'survey', return_value=(
                manifest, {3: b'q' * 1056 if conflicting else entries[1].data}))
            mock(catalog.texture_rgba16, 'survey', return_value=(empty, {}))
            mock(catalog.texture_native, 'survey', return_value=(empty, {}))
            mock(t, 'survey_rectangular_textures', return_value=rectangular)
            mock(t, 'TILED_OVERRIDE_FIRST_INDEX', new=3)
            mock(t, 'TILED_OVERRIDE_ENTRY_COUNT', new=1)
            mock(catalog.h, 'resource_preview_dimensions', return_value={3: (16, 16)})
            mock(catalog.h, 'reachable_flat_indices', return_value=(3,) if hud else ())
            mock(catalog.h, 'resource_preview_image', return_value=SimpleNamespace(
                bytes_used=1024, texture_format='rgba32'))
            mock(catalog.artwork, 'ARTWORK', new=())
            mock(catalog.texture_model_catalog, 'load', return_value={})
            cpu = mock(catalog.texture_cpu_descriptors, 'load', return_value={})
            effects = mock(catalog.texture_cpu_effects, 'load', return_value={})
            grids = mock(catalog.texture_cpu_grids, 'load', return_value={})
            particles = mock(catalog.texture_cpu_particles, 'load', return_value={})
            literals = mock(catalog.texture_cpu_literals, 'load', return_value={})
            tables = mock(catalog.texture_cpu_tables, 'load', return_value={})
            result = catalog.load_extended(Path('/synthetic'), rom)
            self.assertEqual(ci8.call_args.kwargs['flat_entries'], entries)
            self.assertIn(3, cpu.call_args.args[3])
            self.assertIn(3, effects.call_args.args[3])
            self.assertIn(3, grids.call_args.args[3])
            self.assertIn(3, particles.call_args.args[3])
            self.assertIn(3, literals.call_args.args[3])
            self.assertIn(3, tables.call_args.args[3])
            return result

    def test_runtime_gap_and_duplicate_consumers_use_one_physical_range(self):
        result = self.resolve()
        self.assertEqual(list(result), [1])
        texture, contract = result[1]
        self.assertEqual((texture.rom_start, texture.rom_end), (4, 8))
        self.assertEqual(contract, {
            'identity': 'runtime-resource', 'runtime_resource_id': 3,
            'family': 'ci8-proven', 'format': 'ci8', 'width': 16, 'height': 34,
            'row_layout': 'linear', 'source_origin': 'bottom-left'})

    def test_conflicting_payload_and_changed_rom_fail(self):
        with self.assertRaisesRegex(ValueError, 'conflicting texture payload'):
            self.resolve(conflicting=True)
        with self.assertRaisesRegex(ValueError, 'reference ROM changed'):
            self.resolve(wrong_rom=True)

    def test_hud_partial_preview_is_not_a_full_texture_contract(self):
        with self.assertRaisesRegex(ValueError, 'full native texture contract'):
            self.resolve(hud=True)
