"""Selected material routing must never fall through to geometry output writes."""
import contextlib
import io
import unittest
from unittest import mock

from scripts import model_embedded_geometry as embedded


class EmbeddedInspectionRouting(unittest.TestCase):
    def test_explicit_material_mode_forwards_only_supplied_options(self):
        with mock.patch.object(embedded, 'material_inspection', return_value=7) as backend, \
                mock.patch.object(embedded, 'export') as geometry:
            result = embedded.main(['--primitive', 'type13', '--material-inspection', 'counter5',
                                    '--rom', '/tmp/conker-input.z64', '--output', '/tmp/inspection',
                                    '--blender', '/tmp/blender', '--verify'])
        self.assertEqual(result, 7)
        backend.assert_called_once_with(['--rom', '/tmp/conker-input.z64', '--output', '/tmp/inspection',
                                         '--blender', '/tmp/blender', '--verify'])
        geometry.assert_not_called()

    def test_material_default_output_is_owned_by_separate_backend(self):
        with mock.patch.object(embedded, 'material_inspection', return_value=0) as backend, \
                mock.patch.object(embedded, 'export') as geometry:
            self.assertEqual(embedded.main(['--primitive', 'type13', '--material-inspection', 'counter5']), 0)
        backend.assert_called_once_with([])
        geometry.assert_not_called()

    def test_type06_selected_state_forwards_without_geometry_writes(self):
        with mock.patch.object(embedded, 'material_inspection_type06', return_value=9) as backend, \
                mock.patch.object(embedded, 'material_inspection') as other, \
                mock.patch.object(embedded, 'export') as geometry:
            self.assertEqual(9, embedded.main(['--primitive', 'type06', '--material-inspection', 'elapsed0',
                                              '--rom', '/tmp/rom', '--verify']))
        backend.assert_called_once_with(['--rom', '/tmp/rom', '--verify'])
        other.assert_not_called(); geometry.assert_not_called()
        for primitive in ('type08', 'type13'):
            with self.subTest(primitive=primitive), mock.patch.object(embedded, 'material_inspection_type06') as backend, \
                    contextlib.redirect_stderr(io.StringIO()), self.assertRaises(SystemExit):
                embedded.main(['--primitive', primitive, '--material-inspection', 'elapsed0'])
            backend.assert_not_called()

    def test_invalid_mode_combinations_do_not_invoke_either_writer(self):
        cases = [ ['--material-inspection', 'counter5'],
                  ['--primitive', 'type08', '--material-inspection', 'counter5'],
                  ['--primitive', 'type13', '--blender', '/tmp/blender'],
                  ['--primitive', 'type13', '--material-inspection', 'counter10'] ]
        for argv in cases:
            with self.subTest(argv=argv), mock.patch.object(embedded, 'material_inspection') as backend, \
                    mock.patch.object(embedded, 'export') as geometry, contextlib.redirect_stderr(io.StringIO()):
                with self.assertRaises(SystemExit) as error:
                    embedded.main(argv)
                self.assertEqual(error.exception.code, 2)
                backend.assert_not_called()
                geometry.assert_not_called()


if __name__ == '__main__':
    unittest.main()
