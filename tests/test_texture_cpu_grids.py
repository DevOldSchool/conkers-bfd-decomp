"""Native grid bounds and source load extents must explain every admitted byte."""
from contextlib import ExitStack
import hashlib
from pathlib import Path
import struct
from types import SimpleNamespace
import unittest
from unittest.mock import patch

from scripts import texture_cpu_grids as grids


def sha(raw):
    return hashlib.sha1(raw).hexdigest()


class CpuGridTests(unittest.TestCase):
    def fixture(self):
        base = 0x80000000
        data = bytearray(0x300)
        descriptors = {
            base + 0x100: struct.pack('>IBBHHBB', 42, 1, 0, 16, 16, 0, 3),
            base + 0x110: struct.pack('>IBBHHBB', 60, 1, 0, 16, 16, 3, 1),
            base + 0x120: struct.pack('>IBBHHBB', 0, 1, 0, 64, 22, 0, 2),
        }
        for address, raw in descriptors.items():
            data[address - base:address - base + 12] = raw
        data[0x200:0x210] = grids.cpu.SIZE_BYTES
        data[0x50:0x54] = b'type'
        code = b'complete registered consumer'
        bank = struct.pack('>4H', 80, 81, 80, 0)
        guards = dict(DESCRIPTORS={a: sha(r) for a, r in descriptors.items()},
                      CONSUMERS=((0x1000, len(code), sha(code)),),
                      DATA_GUARDS=((base + 0x50, 4, sha(b'type')),),
                      BANK_INDEX=0, BANK_SIZE=8, BANK_SHA1=sha(bank), BANK_DESCRIPTOR=base + 0x120,
                      UI_GRIDS=((base + 0x100, 2, 1, 0x1000),),
                      EFFECT_GRIDS=((base + 0x110, 32, 16, 0, 1, 0x1000, 'primary'),))
        return base, data, code, bank, guards

    def parse(self, base, data, code, bank, guards):
        with patch.multiple(grids, **guards), patch.object(grids.cpu, 'SIZE_TABLE', base + 0x200):
            return grids.verified_descriptors(code, 0x1000, data, base, bank)

    def test_native_descriptors_dispatch_and_bank_slots_are_preserved(self):
        base, data, code, bank, guards = self.fixture()
        records, ids = self.parse(base, data, code, bank, guards)
        self.assertEqual(ids, (80, 81, 80, 0))
        self.assertEqual(records[base + 0x100]['source'], 42)
        self.assertEqual(records[base + 0x120]['height'], 22)

    def test_changed_native_bytes_descriptor_dispatch_sizes_and_bank_fail(self):
        base, data, code, bank, guards = self.fixture()
        with self.assertRaisesRegex(ValueError, 'consumer'):
            self.parse(base, data, code[:-1] + b'!', bank, guards)
        with self.assertRaisesRegex(ValueError, 'bank image list'):
            self.parse(base, data, code, bank[:-1] + b'!', guards)
        for offset, message in ((0x50, 'dispatch data'), (0x106, 'descriptor'),
                                (0x126, 'descriptor'), (0x200, 'transfer-size')):
            altered = bytearray(data)
            altered[offset] ^= 1
            with self.subTest(offset=offset), self.assertRaisesRegex(ValueError, message):
                self.parse(base, altered, code, bank, guards)

    def test_frame_arrays_and_flagged_descriptors_are_not_grid_sources(self):
        base, data, code, bank, guards = self.fixture()
        for raw in (struct.pack('>IBBHHBB', base + 0x280, 1, 0, 16, 16, 0, 3),
                    struct.pack('>IBBHHBB', 42, 1, 1, 16, 16, 0, 3),
                    struct.pack('>IBBHHBB', 42, 2, 0, 16, 16, 0, 3)):
            altered = bytearray(data)
            altered[0x100:0x10C] = raw
            changed = {**guards, 'DESCRIPTORS': {**guards['DESCRIPTORS'], base + 0x100: sha(raw)}}
            with self.assertRaisesRegex(ValueError, 'direct resource'):
                self.parse(base, altered, code, bank, changed)

    def test_partial_edges_are_first_row_last_column_and_frames_do_not_overlap(self):
        record = dict(source=100, width=64, height=64)
        tiles = list(grids.effect_tiles(record, 88, 88, 0, 2))
        self.assertEqual([r for r, _, _ in tiles], list(range(100, 108)))
        self.assertEqual([(s['width'], s['height']) for _, s, _ in tiles],
                         [(64, 24), (64, 64), (24, 24), (24, 64)] * 2)
        self.assertEqual(tiles[4][2], dict(frame=1, column=0, row=0, columns=2, rows=2))

    def test_bordered_tiles_retain_full_storage_dimensions(self):
        record = dict(source=2530, width=32, height=64)
        tiles = list(grids.effect_tiles(record, 270, 124, 2, 1))
        self.assertEqual([r for r, _, _ in tiles], list(range(2530, 2548)))
        self.assertEqual({(s['width'], s['height']) for _, s, _ in tiles}, {(32, 64)})
        for w, h, border, frames in ((0, 88, 0, 1), (88, 0, 0, 1), (88, 88, 1, 1), (88, 88, 0, 0)):
            with self.assertRaises(ValueError):
                list(grids.effect_tiles(record, w, h, border, frames))

    def test_split_loads_cover_the_whole_payload_and_keep_row_swizzle_phase(self):
        record = dict(format=0, size=2, width=64, height=22, count=1, flags=0)
        self.assertEqual(grids.split_contract(record, bytes(5632)), {
            'format': 'rgba16', 'width': 64, 'height': 44,
            'row_layout': 'tmem-odd-row-32bit-swap', 'source_origin': 'top-left'})
        for shape, size in ((record, 5631), (record, 5633), (record, 8064),
                            (record, 2816), ({**record, 'height': 21}, 5376),
                            ({**record, 'width': 128}, 11264),
                            ({**record, 'flags': 1}, 5632), ({**record, 'format': 2}, 5632)):
            with self.subTest(shape=shape, size=size):
                self.assertIsNone(grids.split_contract(shape, bytes(size)))

    def load_fixture(self, entries, *, excluded=(), bank_flags=8):
        base, data, code, bank, guards = self.fixture()
        layout = dict(normalized_sha1=[sha(bank)], asset_table=0, game_start=0,
                      game_end=len(bank), game_vram=0x1000, game_data_vram=base)
        with ExitStack() as stack:
            stack.enter_context(patch.multiple(grids, **guards))
            stack.enter_context(patch.object(grids.cpu, 'SIZE_TABLE', base + 0x200))
            stack.enter_context(patch.object(grids.h, 'resolve_rom', return_value=(None, layout)))
            stack.enter_context(patch.object(grids.h, 'parse_game_archive', return_value=SimpleNamespace(code=code, data=data)))
            stack.enter_context(patch.object(grids.rzip_archive, 'parse_asset_banks', return_value=[
                SimpleNamespace(start=0, end=len(bank), flags=bank_flags)]))
            return grids.load(Path('/synthetic'), bank, entries, excluded)

    def entries(self):
        return [SimpleNamespace(index=i, data=bytes(n)) for i, n in
                ((42, 1024), (43, 1024), (60, 256), (61, 256), (80, 5632), (81, 8064))]

    def test_load_deduplicates_slots_preserves_exclusions_and_rejects_unconsumed_tail(self):
        result = self.load_fixture(self.entries(), excluded={42, 60})
        self.assertEqual(list(result), [43, 61, 80])
        self.assertEqual(result[80]['consumer']['slots'], [0, 2])
        self.assertEqual(result[80]['consumer']['pixel_offsets'], [0, 2816])
        self.assertEqual(result[61]['consumer']['column'], 1)
        with self.assertRaisesRegex(ValueError, 'extent or encoding'):
            self.load_fixture(self.entries(), bank_flags=1)

    def test_later_ui_ids_cannot_qualify_after_an_incomplete_preceding_source(self):
        entries = self.entries()
        entries[0].data = bytes(5120)
        result = self.load_fixture(entries, excluded={42})
        self.assertNotIn(43, result)
        self.assertIn(60, result)
