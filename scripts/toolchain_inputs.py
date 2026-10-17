#!/usr/bin/env python3
"""Hash the public toolchain image's build inputs and compare them with the lock.

The post-merge verification workflow pulls the pinned image from the registry
only when the checkout's toolchain inputs are the ones that image was built
from; otherwise it rebuilds the image locally. ``Publish toolchain`` records
the hash of the inputs it built, next to the registry digest, as
``container_image.inputs_sha256`` in ``toolchain/tools.lock.json``.

The hash covers the files that trigger ``Publish toolchain`` (the Docker build
context allowlist plus the pinned tool revisions), sorted by path, each as
``path`` + NUL + contents, like ``objdiff_report.digest_files``. The lock file
itself is hashed as canonical JSON without its ``container_image`` block: that
block records the published image and is not an input of the image, so
recording a new digest and hash never changes the hash it records.

Subcommands:

``hash``
    Print the checkout's inputs hash.
``check [--quiet]``
    Compare the checkout with the lock. Exit 0 when the lock's
    ``inputs_sha256`` matches, 1 when the inputs changed since the published
    image (or the lock lacks the field, or an input is missing).
``image``
    Print the locked ``repository@digest`` reference.
``record --digest DIGEST [--repository REPOSITORY] [--inputs-sha256 HASH]``
    Write the published digest and the checkout's inputs hash into the lock.
    With ``--inputs-sha256`` (copied from the publish job summary), refuse to
    record a hash that differs from the checkout, which would pin an image to
    inputs it was not built from.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
LOCK = Path("toolchain/tools.lock.json")
# Keep in step with the ``Publish toolchain`` push paths (minus the workflow
# itself, which does not enter the image); tests/test_toolchain_inputs.py
# checks that they agree.
INPUTS = (
    Path("Dockerfile"),
    Path(".dockerignore"),
    Path("toolchain/mupen64plus-debug.sh"),
    Path("toolchain/python-constraints.txt"),
    Path("toolchain/python-requirements.txt"),
    LOCK,
)
IMAGE_KEY = "container_image"
HASH_KEY = "inputs_sha256"
DIGEST = re.compile(r"^sha256:[0-9a-f]{64}$")
SHA256 = re.compile(r"^[0-9a-f]{64}$")


def load_lock(root: Path = ROOT) -> dict:
    return json.loads((root / LOCK).read_text(encoding="utf-8"))


def lock_without_image(lock: dict) -> bytes:
    pins = {key: value for key, value in lock.items() if key != IMAGE_KEY}
    return (json.dumps(pins, sort_keys=True, separators=(",", ":")) + "\n").encode()


def input_bytes(root: Path, path: Path) -> bytes:
    if path == LOCK:
        return lock_without_image(load_lock(root))
    return (root / path).read_bytes()


def inputs_hash(root: Path = ROOT) -> str:
    digest = hashlib.sha256()
    for path in sorted(INPUTS, key=str):
        digest.update(path.as_posix().encode() + b"\0" + input_bytes(root, path))
    return digest.hexdigest()


def locked_image(lock: dict) -> str:
    image = lock[IMAGE_KEY]
    return f"{image['repository']}@{image['digest']}"


def check(root: Path = ROOT) -> tuple[bool, str]:
    """Return (match, message) comparing the checkout with the lock."""
    lock = load_lock(root)
    image = locked_image(lock)
    recorded = lock[IMAGE_KEY].get(HASH_KEY)
    try:
        current = inputs_hash(root)
    except FileNotFoundError as error:
        return False, f"toolchain inputs changed: missing input {error.filename} ({image})"
    if recorded is None:
        return False, f"toolchain inputs changed: the lock records no {HASH_KEY} for {image}"
    if recorded != current:
        return False, f"toolchain inputs changed: lock {recorded} != checkout {current} ({image})"
    return True, f"toolchain inputs match the published image: {current} ({image})"


def record(root: Path, digest: str, repository: str | None, expected: str | None) -> dict:
    if not DIGEST.match(digest):
        raise SystemExit(f"error: digest must look like sha256:<64 hex digits>, not {digest!r}")
    current = inputs_hash(root)
    if expected is not None and expected != current:
        raise SystemExit(
            f"error: published inputs hash {expected} differs from this checkout's {current}; "
            "the image was built from other toolchain inputs")
    lock = load_lock(root)
    image = lock[IMAGE_KEY]
    if repository is not None:
        image["repository"] = repository
    image["digest"] = digest
    image[HASH_KEY] = current
    (root / LOCK).write_text(json.dumps(lock, indent=2) + "\n", encoding="utf-8")
    return image


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--root", type=Path, default=ROOT, help=argparse.SUPPRESS)
    commands = parser.add_subparsers(dest="command", required=True)
    commands.add_parser("hash", help="print the checkout's toolchain inputs hash")
    check_parser = commands.add_parser("check", help="compare the checkout with the lock (exit 1 on change)")
    check_parser.add_argument("--quiet", action="store_true", help="print nothing; use the exit status")
    commands.add_parser("image", help="print the locked repository@digest")
    record_parser = commands.add_parser("record", help="record a published digest and the inputs hash in the lock")
    record_parser.add_argument("--digest", required=True, help="registry manifest digest (sha256:...)")
    record_parser.add_argument("--repository", help="registry repository; defaults to the locked one")
    record_parser.add_argument("--inputs-sha256", dest="expected", help="hash from the publish job summary")
    args = parser.parse_args(argv)
    root = args.root.resolve()
    if args.command == "hash":
        print(inputs_hash(root))
    elif args.command == "image":
        print(locked_image(load_lock(root)))
    elif args.command == "check":
        match, message = check(root)
        if not args.quiet:
            print(message)
        return 0 if match else 1
    elif args.command == "record":
        if args.expected is not None and not SHA256.match(args.expected):
            parser.error("--inputs-sha256 must be 64 hex digits")
        image = record(root, args.digest, args.repository, args.expected)
        print(f"recorded {image['repository']}@{image['digest']} {HASH_KEY}={image[HASH_KEY]}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
