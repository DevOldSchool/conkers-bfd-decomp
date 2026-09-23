from __future__ import annotations

import json
import re
import unittest
from pathlib import Path

import yaml


ROOT = Path(__file__).resolve().parent.parent


def ignore_patterns(path: Path) -> list[str]:
    return [
        line
        for raw_line in path.read_text(encoding="utf-8").splitlines()
        if (line := raw_line.strip()) and not line.startswith("#")
    ]


class RepositorySafetyTests(unittest.TestCase):
    def test_rom_workflow_keeps_private_inputs_behind_main_environment(self) -> None:
        workflow = yaml.safe_load((ROOT / ".github/workflows/rom-verify-main.yml").read_text())
        events = workflow.get("on", workflow.get(True))
        self.assertEqual(set(events), {"push", "workflow_dispatch"})
        self.assertEqual(events["push"]["branches"], ["main"])
        self.assertEqual(workflow["permissions"], {"contents": "read"})
        self.assertEqual(set(workflow["jobs"]), {"verify-main"})
        job = workflow["jobs"]["verify-main"]
        self.assertEqual(job["if"], "github.ref == 'refs/heads/main'")
        self.assertEqual(job["environment"], "rom-verification")
        steps = job["steps"]
        checkouts = [step for step in steps if step.get("uses", "").startswith("actions/checkout@")]
        self.assertEqual(len(checkouts), 2)
        self.assertEqual(checkouts[0]["with"]["ref"], "${{ github.sha }}")
        for checkout in checkouts:
            self.assertIs(checkout["with"]["persist-credentials"], False)
        private = checkouts[1]
        self.assertEqual(private["with"]["repository"], "${{ secrets.ROM_ASSETS_REPOSITORY }}")
        self.assertEqual(private["with"]["token"], "${{ secrets.ROM_ASSETS_READ_TOKEN }}")
        self.assertEqual(private["with"]["sparse-checkout"], "baserom.us.z64")
        builds = [step for step in steps if "docker build " in step.get("run", "")]
        self.assertEqual(len(builds), 1)
        self.assertLess(steps.index(builds[0]), steps.index(private))
        token_steps = [step for step in steps if "ROM_ASSETS_READ_TOKEN" in str(step)]
        self.assertEqual(token_steps, [private])
        uploads = [step for step in steps if step.get("uses", "").startswith("actions/upload-artifact@")]
        self.assertEqual(len(uploads), 1)
        self.assertEqual(uploads[0]["with"]["path"], "build/us/objdiff-report/report.json")
        self.assertEqual(uploads[0]["with"]["if-no-files-found"], "error")
        self.assertEqual(steps[-1]["if"], "always()")
        self.assertIn("./conker stop", steps[-1]["run"])
        self.assertIn("rm -rf -- .private-rom-assets roms/baserom.us.z64", steps[-1]["run"])

    def test_public_pr_workflow_has_no_private_credentials_or_privileged_trigger(self) -> None:
        raw = (ROOT / ".github/workflows/ci.yml").read_text()
        workflow = yaml.safe_load(raw)
        events = workflow.get("on", workflow.get(True))
        self.assertEqual(set(events), {"pull_request", "push"})
        self.assertEqual(workflow["permissions"], {"contents": "read"})
        self.assertNotIn("secrets.", raw)
        self.assertNotIn("ROM_ASSETS", raw)
        for job in workflow["jobs"].values():
            self.assertNotIn("environment", job)
            self.assertNotIn("permissions", job)
        required = workflow["jobs"]["required"]
        self.assertEqual(required["if"], "always()")
        self.assertEqual(set(required["needs"]), set(workflow["jobs"]) - {"required"})
        self.assertIn("job['result'] == 'success'", required["steps"][0]["run"])

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
        for tool in (
            "mupen64plus-core",
            "mupen64plus-ui-console",
            "mupen64plus-rsp-hle",
            "mupen64plus-rsp-cxd4",
            "angrylion-rdp-plus",
        ):
            self.assertRegex(lock["tools"][tool]["revision"], re.compile(r"^[0-9a-f]{40}$"))
        dockerfile = (ROOT / "Dockerfile").read_text(encoding="utf-8") + (ROOT / "toolchain/Dockerfile.mupen-software").read_text(encoding="utf-8")
        for tool in (
            "mupen64plus-core",
            "mupen64plus-ui-console",
            "mupen64plus-rsp-hle",
            "mupen64plus-rsp-cxd4",
            "angrylion-rdp-plus",
        ):
            self.assertIn(lock["tools"][tool]["revision"], dockerfile)
        self.assertIn("DEBUGGER=1", dockerfile)
        self.assertIn("Mupen64Plus debugger smoke test: OK", script)
        self.assertNotIn("$HOME/Development/mupen64plus-debug", script)

    def test_docker_build_context_is_a_minimal_allowlist(self) -> None:
        patterns = ignore_patterns(ROOT / ".dockerignore")

        self.assertEqual(
            [
                "**",
                "!Dockerfile",
                "!.dockerignore",
                "!toolchain/",
                "!toolchain/mupen64plus-debug.sh",
                "!toolchain/python-constraints.txt",
                "!toolchain/Dockerfile.mupen-software",
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
        self.assertIn("toolchain/mupen64plus-debug.sh", workflow)
        self.assertIn("toolchain/tools.lock.json", workflow)

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

    def test_us_build_prepares_libultra_through_the_writable_mount(self) -> None:
        makefile = (ROOT / "Makefile").read_text(encoding="utf-8")
        script = (ROOT / "scripts" / "conker.sh").read_text(encoding="utf-8")

        self.assertIn("MODERN_LD=1", makefile)
        self.assertIn("run_in_container_libultra make profile-libs PROFILE=us", script)
        self.assertIn("PROFILE_LIB_G_us", makefile)
        self.assertIn("PROFILE_LIB_GD_us", makefile)
        self.assertIn("PROFILE_LIB_RARE_us", makefile)
        self.assertIn("--whole-archive", makefile)
        self.assertIn("$(MAKE) --no-print-directory libultrare", makefile)
        self.assertIn("TARGET=libultra_d", makefile)
        self.assertIn("build/G/libultra_d/src/audio/", makefile)
        for forced_symbol in (
            "_bzero",
            "osInvalICache",
            "osInvalDCache",
            "_Litob",
            "__osPiCreateAccessQueue",
            "_bcopy",
            "osWritebackDCache",
            "osSetIntMask",
            "osWritebackDCacheAll",
            "__osSiCreateAccessQueue",
            "osMapTLB",
            "__sinf",
            "__ll_div",
            "__osProbeTLB",
            "osViModeMpalLan1",
            "osViModeNtscLan1",
            "__libm_qnan_f",
        ):
            self.assertIn(f"-u {forced_symbol}", makefile)
        self.assertNotIn("--defsym=__osProbeTLB", makefile)
        for archive_defined_symbol in (
            "__osThreadTail",
            "__osRunQueue",
            "__osRunningThread",
            "__libm_qnan_f",
        ):
            self.assertNotIn(f"--defsym={archive_defined_symbol}", makefile)

    def test_libultra_research_command_limits_supported_versions(self) -> None:
        script = (ROOT / "scripts" / "conker.sh").read_text(encoding="utf-8")
        libultra_case = script.split("    libultra)", 1)[1].split("\n    *)", 1)[0]

        self.assertIn('libultra_version=L', libultra_case)
        self.assertIn('"--version"', libultra_case)
        self.assertIn('G|I|J|K|L)', libultra_case)
        self.assertIn('ULTRALIB_VERSION="$libultra_version"', libultra_case)

    def test_library_audit_has_a_bounded_supported_command(self) -> None:
        script = (ROOT / "scripts" / "conker.sh").read_text(encoding="utf-8")
        audit_case = script.split("    library-audit)", 1)[1].split("        ;;", 1)[0]

        self.assertIn("library-audit [--json]", script)
        self.assertIn('[[ $# -eq 0 || ( $# -eq 1 && "$1" == "--json" ) ]]', audit_case)
        self.assertIn("python3 scripts/audit_library_boundaries.py", audit_case)

    def test_library_owned_sources_do_not_remain_as_generic_source_units(self) -> None:
        libultra_sources = sorted(
            path.relative_to(ROOT).as_posix()
            for path in (ROOT / "src" / "libultra").rglob("*")
            if path.is_file()
        )
        libultrare_sources = sorted(
            path.relative_to(ROOT).as_posix()
            for path in (ROOT / "src" / "libultrare").rglob("*")
            if path.is_file()
        )

        self.assertEqual([], libultra_sources)
        self.assertEqual(
            [
                "src/libultrare/gu/powf.c",
            ],
            libultrare_sources,
        )
        # A non-exact Rare reconstruction must remain outside the archive.
        candidate = (ROOT / "src/libultrare/gu/powf.c").read_text(encoding="utf-8")
        self.assertIn("#if 0\n", candidate)
        self.assertNotIn(
            "src/libultrare/gu/powf.c",
            (ROOT / "lib/libultrare/Makefile").read_text(encoding="utf-8"),
        )

    def test_agent_workflow_prewarms_and_composes_the_per_function_gate(self) -> None:
        script = (ROOT / "scripts" / "conker.sh").read_text(encoding="utf-8")
        prepare_body = script.split("prepare_next_work() {", 1)[1].split("\n}", 1)[0]
        finish_case = script.split("    finish)", 1)[1].split("        ;;", 1)[0]
        watch_case = script.split('if [[ "${1:-}" == "--watch" ]]', 1)[1].split(
            "        elif", 1
        )[0]
        batch_case = script.split("    verify-batch)", 1)[1].split("        ;;", 1)[0]

        self.assertIn('next --one --details', prepare_body)
        self.assertNotIn('next --one --id-only', prepare_body)
        self.assertIn("ensure_warm_container", prepare_body)
        self.assertIn(
            'run_host_mips_to_c us "$identifier" --auto-overlay --ready-output',
            prepare_body,
        )
        self.assertNotIn("remove_warm_container", prepare_body)

        self.assertIn("verify_and_record_match", finish_case)
        self.assertIn("verify_and_record_match --compact-mismatch", finish_case)
        self.assertIn("scripts/layout_check.py", script)
        self.assertIn('progress --check', finish_case)
        self.assertIn("core.whitespace=cr-at-eol diff --check", finish_case)
        self.assertIn("AGENT_ACTION: FIX_COMPILE", finish_case)
        self.assertIn("AGENT_ACTION: CONTINUE_MISMATCH", finish_case)
        self.assertIn("AGENT_ACTION: BLOCKED_TOOLING", finish_case)
        self.assertIn("AGENT_ACTION: STOP_MATCHED", finish_case)

        self.assertIn("! -t 0 || ! -t 1", watch_case)
        self.assertIn("AGENT_ACTION: USE_FINISH_LOOP", watch_case)

        self.assertIn('batch-plan "$@"', batch_case)
        self.assertIn("game-integrated-refresh", batch_case)
        self.assertIn("game-integrated", batch_case)
        self.assertIn("python3 -m unittest discover -s tests -q -b", batch_case)
        self.assertIn("batch-fingerprint", batch_case)
        self.assertIn("clean-integration-failure.sha256", batch_case)
        self.assertIn("AGENT_ACTION: FIX_INTEGRATION", batch_case)
        self.assertIn("AGENT_ACTION: BATCH_COMPLETE", batch_case)
        self.assertLess(
            batch_case.index("already failed clean integration"),
            batch_case.index('batch-plan "$@"'),
        )

        self.assertIn("diagnose-diff <work-item-id>", script)
        self.assertIn("permute <work-item-id> [--budget N]", script)
        self.assertIn("automate [--limit N | --all | --function ID]", script)
        self.assertIn("reopen-match <work-item-id> --reason <text>", script)

        permute_case = script.split("    permute)", 1)[1].split("        ;;", 1)[0]
        self.assertIn('apply-permutation "$permute_symbol"', permute_case)
        self.assertIn('"$repo_root/conker" finish "$permute_symbol"', permute_case)
        self.assertIn('rollback-permutation "$permute_symbol"', permute_case)
        self.assertIn('clear-permutation "$permute_symbol"', permute_case)
        self.assertLess(
            permute_case.index("apply-permutation"), permute_case.index("finish")
        )
        self.assertLess(
            permute_case.index("finish"), permute_case.index("rollback-permutation")
        )

    def test_unified_automation_uses_public_authoritative_gates(self) -> None:
        dispatch = (ROOT / "scripts" / "conker.sh").read_text(encoding="utf-8")
        automation_case = dispatch.split("    automate)", 1)[1].split(
            "        ;;", 1
        )[0]
        automation = (ROOT / "scripts" / "automate.py").read_text(
            encoding="utf-8"
        )
        contribution_guide = (ROOT / "CONTRIBUTING.md").read_text(encoding="utf-8")

        self.assertIn("automate [--limit N | --all | --function ID]", dispatch)
        self.assertIn('python3 scripts/automate.py "$@"', automation_case)
        self.assertIn("generate_starter(candidate.identifier)", automation)
        self.assertIn('"finish", candidate.identifier', automation)
        self.assertIn('"verify-batch", *matched', automation)
        self.assertNotIn('"diff", candidate.identifier', automation)
        self.assertIn('"diagnose-diff", candidate.identifier', automation)
        self.assertIn('"permute",', automation)
        self.assertIn("source.write_bytes(original)", automation)
        self.assertIn("write_report(", automation)
        self.assertIn("reconcile_pending_batch(", automation)
        self.assertIn("candidate_fingerprint(", automation)
        self.assertIn("save_failure_artifacts(", automation)
        self.assertIn("--analyze", automation)
        self.assertIn("--verbose", automation)
        self.assertIn("command_log", automation)
        self.assertIn("repair_compile_diagnostics", automation)
        self.assertIn("stage_fingerprint", automation)
        self.assertIn("./conker automate --all --defer-best", contribution_guide)

    def test_docker_access_is_checked_before_image_download(self) -> None:
        script = (ROOT / "scripts" / "conker.sh").read_text(encoding="utf-8")
        ensure_image = script.split("ensure_cpu_image() {", 1)[1].split("\n}", 1)[0]

        self.assertIn("require_docker || return 1", ensure_image)
        self.assertIn("require_docker_access || return 1", ensure_image)
        self.assertLess(
            ensure_image.index("require_docker_access"),
            ensure_image.index("docker pull"),
        )
        ensure_rsp = script.split("ensure_image() {", 1)[1].split("\n}", 1)[0]
        self.assertLess(ensure_rsp.index("ensure_cpu_image || return 1"),
                        ensure_rsp.index("docker build"))

    def test_canonical_scalar_aliases_cover_m2c_integer_types(self) -> None:
        types = (ROOT / "include" / "types.h").read_text(encoding="utf-8")

        for alias in ("s8", "u8", "s16", "u16", "s32", "u32", "s64", "u64"):
            self.assertRegex(types, rf"typedef [^;]+ {alias};")


if __name__ == "__main__":
    unittest.main()
