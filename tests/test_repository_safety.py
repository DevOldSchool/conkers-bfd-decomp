from __future__ import annotations

import json
import re
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent


def ignore_patterns(path: Path) -> list[str]:
    return [
        line
        for raw_line in path.read_text(encoding="utf-8").splitlines()
        if (line := raw_line.strip()) and not line.startswith("#")
    ]


class RepositorySafetyTests(unittest.TestCase):
    def test_default_container_image_is_digest_locked_and_sandboxed(self) -> None:
        lock = json.loads((ROOT / "toolchain" / "tools.lock.json").read_text(encoding="utf-8"))
        image = lock["container_image"]
        script = (ROOT / "scripts" / "conker.sh").read_text(encoding="utf-8")

        self.assertEqual("ghcr.io/devoldschool/conkers-bfd-decomp-toolchain", image["repository"])
        self.assertRegex(image["digest"], re.compile(r"^sha256:[0-9a-f]{64}$"))
        self.assertNotIn("conkers-bfd-decomp-toolchain:latest", script)
        self.assertNotIn('docker build --platform linux/amd64 --tag "$image_name"', script)
        self.assertIn('image_name="${CONKER_IMAGE:-$locked_image}"', script)
        for required_flag in (
            "--network none",
            "--read-only",
            "--cap-drop ALL",
            "--security-opt no-new-privileges",
            '--user "$(id -u):$(id -g)"',
        ):
            self.assertIn(required_flag, script)
        self.assertNotIn('source=$repo_root,target=/workspace"', script)
        self.assertNotIn("target=/workspace/.git", script)
        self.assertNotIn("target=/workspace/.conker", script)
        self.assertIn("--tmpfs /workspace:rw,nosuid,nodev,size=256m,mode=1777", script)
        self.assertIn('local access="${2:-readonly}"', script)
        self.assertIn('return 0', script)
        self.assertIn('mount="$mount,readonly"', script)
        for protected_path in ("roms", ".private-rom-assets"):
            self.assertIn(f"add_workspace_mount {protected_path}", script)
        for protected_path in ("config", "include", "scripts", "src", "toolchain"):
            self.assertIn(protected_path, script)

    def test_docker_build_context_is_a_minimal_allowlist(self) -> None:
        patterns = ignore_patterns(ROOT / ".dockerignore")

        self.assertEqual(
            [
                "**",
                "!Dockerfile",
                "!.dockerignore",
                "!toolchain/",
                "!toolchain/python-constraints.txt",
            ],
            patterns,
        )

    def test_publish_workflow_normalizes_the_ghcr_repository_owner(self) -> None:
        workflow = (
            ROOT / ".github" / "workflows" / "publish-toolchain.yml"
        ).read_text(encoding="utf-8")

        self.assertNotIn("ghcr.io/${{ github.repository_owner }}", workflow)
        self.assertIn("OWNER: ${{ github.repository_owner }}", workflow)
        self.assertIn(
            "tr '[:upper:]' '[:lower:]'", workflow
        )
        self.assertIn(
            "repository=ghcr.io/$owner_lc/conkers-bfd-decomp-toolchain", workflow
        )
        self.assertIn("${{ steps.image.outputs.repository }}:latest", workflow)

    def test_git_ignores_every_supported_rom_extension(self) -> None:
        patterns = ignore_patterns(ROOT / ".gitignore")

        self.assertIn("*.z64", patterns)
        self.assertTrue(any(pattern in patterns for pattern in ("*.n64", "*.n64*")))
        self.assertIn("*.v64", patterns)

    def test_game_build_has_incremental_and_explicit_refresh_paths(self) -> None:
        makefile = (ROOT / "Makefile").read_text(encoding="utf-8")
        script = (ROOT / "scripts" / "conker.sh").read_text(encoding="utf-8")

        self.assertIn("game-integrated-prepare: $(GAME_INTEGRATED_PREPARED)", makefile)
        self.assertIn("game-integrated-refresh:", makefile)
        self.assertIn('rm -f "$(GAME_INTEGRATED_PREPARED)"', makefile)
        self.assertIn("game-build [--profile us] [--refresh]", script)
        self.assertIn("game_build_target=game-integrated-refresh", script)


if __name__ == "__main__":
    unittest.main()
