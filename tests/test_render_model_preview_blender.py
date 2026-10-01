from __future__ import annotations

import unittest
from types import SimpleNamespace

from scripts.render_model_preview_blender import set_preview_render_engine


class PreviewRenderEngineTests(unittest.TestCase):
    def scene(self, engines):
        items = [SimpleNamespace(identifier=engine) for engine in engines]
        return SimpleNamespace(render=SimpleNamespace(
            engine="UNCHANGED",
            bl_rna=SimpleNamespace(properties={
                "engine": SimpleNamespace(enum_items=items),
            }),
        ))

    def test_material_render_uses_installed_eevee_identifier(self):
        for engine in ("BLENDER_EEVEE", "BLENDER_EEVEE_NEXT"):
            with self.subTest(engine=engine):
                scene = self.scene([engine, "BLENDER_WORKBENCH", "CYCLES"])
                set_preview_render_engine(scene, "material")
                self.assertEqual(engine, scene.render.engine)

    def test_material_render_prefers_eevee_next_when_both_exist(self):
        scene = self.scene(["BLENDER_EEVEE", "BLENDER_EEVEE_NEXT"])
        set_preview_render_engine(scene, "material")
        self.assertEqual("BLENDER_EEVEE_NEXT", scene.render.engine)

    def test_material_render_fails_clearly_without_eevee(self):
        scene = self.scene(["CYCLES", "BLENDER_WORKBENCH"])
        with self.assertRaisesRegex(RuntimeError, "require Eevee.*BLENDER_WORKBENCH, CYCLES"):
            set_preview_render_engine(scene, "material")
        self.assertEqual("UNCHANGED", scene.render.engine)

    def test_vertex_render_does_not_require_eevee_or_engine_enumeration(self):
        scene = SimpleNamespace(render=SimpleNamespace(engine="UNCHANGED"))
        set_preview_render_engine(scene, "vertex")
        self.assertEqual("BLENDER_WORKBENCH", scene.render.engine)


if __name__ == "__main__":
    unittest.main()
