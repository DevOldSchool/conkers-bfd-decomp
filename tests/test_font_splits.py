from dataclasses import replace
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch
import yaml
sys.path.insert(0, str(Path(__file__).resolve().parent.parent / 'scripts'))
import font_assets
import font_splits


class FontSplitTests(unittest.TestCase):
    def fixture(self, root):
        glyphs = [font_assets.FontGlyph(48, 2, 1, b'\0\0', b'\x10\x10', b''),
                  font_assets.FontGlyph(49, 2, 1, b'\0\0', b'\x10\x20', b'')]
        packed = font_assets.encode_font_table(glyphs, 3)
        layout = {'font_start': 16, 'font_count': 2, 'font_storage_end': 16 + len(packed)}
        profile = root / 'config/profiles/us.yaml'
        profile.parent.mkdir(parents=True)
        doc = {'segments': [{'name': 'font_rle', 'type': 'group', 'start': 16, 'align': 1, 'subalign': 1,
            'subsegments': [[16, 'bin', 'font/glyphs/0000'], [25, 'bin', 'font/glyphs/0001'],
                            [35, 'bin', 'font/padding']]}, [38]]}
        profile.write_text(yaml.safe_dump(doc))
        return profile, bytes(16) + packed, layout, glyphs, doc

    def test_yaml_must_agree_with_each_original_record_and_padding(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            profile, rom, layout, _, doc = self.fixture(root)
            spans = font_splits.verify_splits(profile, rom, layout)
            self.assertEqual([b-a for a,b,_ in spans], [9,10,3])
            doc['segments'][0]['subsegments'][1][0] += 1
            profile.write_text(yaml.safe_dump(doc))
            with self.assertRaisesRegex(ValueError, 'original record'):
                font_splits.verify_splits(profile, rom, layout)

    def test_same_total_size_cannot_hide_shifted_glyph_boundaries(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            _, rom, layout, glyphs, _ = self.fixture(root)
            original = rom[16:]
            with patch.object(font_assets, 'load_profile_fonts', return_value=(None,rom,None,layout,glyphs,3)), \
                    patch.object(font_assets, 'build_fonts', return_value=original):
                spans = font_splits.build_parts(root)
                self.assertEqual(b''.join((root/'build/us/fonts/parts'/f'{name}.bin').read_bytes()
                                         for _,_,name in spans), original)
                glyphs = [replace(glyphs[0], pixels=glyphs[1].pixels), replace(glyphs[1], pixels=glyphs[0].pixels)]
                changed = font_assets.encode_font_table(glyphs, 3)
                self.assertEqual(len(changed), len(original))
                with patch.object(font_assets, 'build_fonts', return_value=changed), \
                        self.assertRaisesRegex(ValueError, 'record extent'):
                    font_splits.build_parts(root)
