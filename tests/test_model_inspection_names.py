"""Keep reviewed character identities in the canonical gallery metadata."""
import html
import json
import unittest

from scripts import model_inspection as inspection


class ModelInspectionNameTests(unittest.TestCase):
    def test_reviewed_names_and_references_reach_generated_gallery(self):
        config = json.loads((inspection.ROOT / 'config/model-inspection.json').read_text())
        inspection.validate_gallery_metadata(config['models'])
        models = {model['name']: model for model in config['models']}
        expected = {
            5: 'Wasp', 10: 'Mrs. Catfish', 14: 'Corn Bag — unused',
            15: 'Lady Cog — red', 24: 'Jack — metal box',
            26: 'Catfish — skeletal remains', 52: 'TNT Imp', 68: 'Dung Beetle',
            70: 'Lady Cog — blue', 76: 'Lady Cog — green', 107: 'Electric Eel',
            125: 'Franky the Pitchfork — broken upper part',
            165: 'Red Dinosaur', 173: 'Wayne — cigar',
            174: 'Wanka — fat wasp', 175: 'Wanka — skinny wasp',
        }
        records = []
        for entry, title in expected.items():
            name = f'character-bank01-{entry:04d}-rom'
            with self.subTest(entry=entry):
                model = models[name]
                self.assertEqual(title, model['label'].split(' — ROM', 1)[0])
                self.assertEqual(name, model['render_case'])
                self.assertEqual('visual-reference', model['identification']['basis'])
                self.assertTrue(model['identification']['reference_url'].startswith(
                    'https://conker.fandom.com/wiki/'))
                if entry != 165:
                    self.assertTrue(any(alias.startswith('Former label: ')
                                        for alias in model['aliases']))
                records.append({**model, 'file': name + '.glb', 'glb_sha256': 'test'})
        page = inspection.gallery_page(records, inspection.ROOT / 'inspect')
        for title in expected.values():
            self.assertIn('<h2>' + html.escape(title) + '</h2>', page)
        for record in records:
            self.assertIn(html.escape(record['identification']['reference_url'], quote=True), page)
            self.assertIn(record['name'] + '.glb', page)

    def test_tnt_imp_does_not_keep_false_dinosaur_identity(self):
        config = json.loads((inspection.ROOT / 'config/model-inspection.json').read_text())
        models = {model['name']: model for model in config['models']}
        imp = models['character-bank01-0052-rom']
        self.assertEqual('https://conker.fandom.com/wiki/TNT_Imp',
                         imp['identification']['reference_url'])
        self.assertNotIn('baby dinosaur', imp['aliases'])
        self.assertTrue(models['character-bank01-0054-rom']['label'].startswith('Dino Baby — ROM'))
        self.assertTrue(models['character-bank01-0058-rom']['label'].startswith('Fire Imp — ROM'))
        self.assertTrue(models['character-bank01-0083-rom']['label'].startswith('Fangy the Raptor — ROM'))


if __name__ == '__main__':
    unittest.main()
