#!/usr/bin/env python3
"""Set up and check an isolated, pinned host Python environment."""
from __future__ import annotations

import argparse
import importlib
import importlib.metadata
from pathlib import Path
import subprocess
import sys
import venv

ROOT = Path(__file__).resolve().parent.parent
MODULES = {"PyYAML": "yaml", "numpy": "numpy", "scipy": "scipy",
           "soundfile": "soundfile", "cffi": "cffi", "pycparser": "pycparser",
           "typing-extensions": "typing_extensions"}
# Host helpers such as project_state.py import PyYAML; the rest are needed only
# to run the test suite on the host instead of in the toolchain container.
CORE = ("PyYAML",)


def requirements(root: Path = ROOT) -> dict[str, str]:
    result = {}
    for line in (root / "toolchain/python-requirements.txt").read_text().splitlines():
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        name, separator, version = line.partition("==")
        if not separator or name not in MODULES or not version or name in result:
            raise ValueError("host requirements must contain unique exact package pins")
        result[name] = version
    if set(result) != set(MODULES):
        raise ValueError("host requirements omit a required package")
    return result


def check(root: Path = ROOT, *, core: bool = False) -> list[str]:
    errors = []
    if sys.version_info < (3, 12):
        errors.append("host Python >= 3.12 is required")
    for name, version in requirements(root).items():
        if core and name not in CORE:
            continue
        try:
            actual = importlib.metadata.version(name)
            if actual != version:
                errors.append(f"{name}: expected {version}, found {actual}")
            else:
                importlib.import_module(MODULES[name])
        except (ImportError, OSError) as error:
            errors.append(f"{name}: unavailable ({error})")
    if errors:
        errors.append("run ./conker host-setup to create/update build/host-python; then rerun ./conker")
    return errors


def setup(root: Path = ROOT) -> None:
    if sys.version_info < (3, 12):
        raise ValueError("run host-setup with Python >= 3.12 on PATH")
    requirements(root)  # Validate before creating or installing anything.
    environment = root / "build/host-python"
    venv.EnvBuilder(with_pip=True).create(environment)
    python = environment / "bin/python3"
    subprocess.run([str(python), "-m", "pip", "install", "--requirement",
                    str(root / "toolchain/python-requirements.txt")], check=True)
    subprocess.run([str(python), str(root / "scripts/host_environment.py"), "check"], check=True)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("action", choices=("setup", "check"))
    scope = parser.add_mutually_exclusive_group()
    scope.add_argument("--core", action="store_true",
                       help="check only the packages host helpers import")
    scope.add_argument("--all", action="store_true",
                       help="also check host-mode test packages (default)")
    args = parser.parse_args()
    try:
        if args.action == "setup":
            setup()
        else:
            errors = check(core=args.core)
            if errors:
                for error in errors:
                    print(f"error: {error}", file=sys.stderr)
                return 2
            scope = "core host" if args.core else "Host"
            print(f"{scope[0].upper()}{scope[1:]} Python dependencies: exact pins and imports verified")
    except (ValueError, OSError, subprocess.CalledProcessError) as error:
        print(f"error: {error}", file=sys.stderr)
        return 2
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
