#!/usr/bin/env python3
"""Check cheap local inputs needed after a focused match reaches its clean batch."""

from __future__ import annotations

from pathlib import Path
import subprocess
import sys

ROOT = Path(__file__).resolve().parent.parent


def git_output(root: Path, *arguments: str) -> str:
    result = subprocess.run(
        ["git", "-c", "core.fsmonitor=false", "-C", str(root), *arguments],
        text=True, capture_output=True, check=False,
    )
    if result.returncode:
        raise ValueError(result.stderr.strip() or "git could not inspect the checkout")
    return result.stdout.strip()


def check(root: Path = ROOT) -> list[str]:
    errors = []
    reference = root / "reference/us/asm"
    # game-integrated-prepare also materializes reviewed main/debugger units.
    # Its game reference is generated on demand; this separate input is not.
    if not reference.is_dir() or next((path for path in reference.rglob("*.s") if path.is_file()), None) is None:
        errors.append("missing or empty reference/us/asm; run "
                      "./conker _prepare-reference --profile us before matching")

    sdk = root / "lib/ultralib"
    if not (sdk / ".git").exists() or not (sdk / "Makefile").is_file():
        errors.append("lib/ultralib is not initialized; run "
                      "git submodule update --init --recursive lib/ultralib")
    else:
        try:
            # The index also honors an intentional staged pin update. Do not
            # fetch, switch revisions, or overwrite existing submodule work.
            entries = git_output(root, "ls-files", "--stage", "--", "lib/ultralib").splitlines()
            fields = entries[0].split() if len(entries) == 1 else []
            if len(fields) != 4 or fields[0] != "160000" or fields[2] != "0":
                raise ValueError("lib/ultralib has no single resolved gitlink in the index")
            expected = fields[1]
            actual = git_output(sdk, "rev-parse", "HEAD")
            if actual != expected:
                errors.append(f"lib/ultralib is at {actual}; the index pins {expected}. "
                              "Restore the pinned checkout after preserving any submodule work")
        except (OSError, ValueError) as error:
            errors.append(f"cannot verify lib/ultralib: {error}")
    return errors


def main() -> int:
    errors = check()
    if errors:
        for error in errors:
            print(f"error: {error}", file=sys.stderr)
        print("AGENT_ACTION: BLOCKED_TOOLING")
        return 2
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
