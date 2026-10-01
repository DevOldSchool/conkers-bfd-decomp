"""Shared path, authentication, and metadata helpers for evidence commands."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path


def require(condition, message):
    if not condition:
        raise ValueError(message)


def sha(data):
    return hashlib.sha256(data).hexdigest()


def encoded(value):
    return (json.dumps(value, sort_keys=True, indent=2) + "\n").encode()


def validate_paths(args, inputs, outputs):
    """Resolve once; validate all destinations before reading large inputs.

    Exclusive creation is still required at write time to close the ordinary
    validation/creation race. No output can alias another output or an input.
    """
    source_paths = set()
    for name in inputs:
        value = getattr(args, name, None)
        if value is None:
            continue
        path = Path(value).expanduser().resolve()
        require(path.is_file(), name + " input file is missing")
        source_paths.add(path)
        setattr(args, name, path)
    destinations = set()
    for name in outputs:
        value = getattr(args, name, None)
        if value is None:
            continue
        path = Path(value).expanduser()
        require(not path.is_symlink(), name + " must not be a symbolic link")
        path = path.resolve()
        require(path not in source_paths, name + " must be a new file, not an input")
        require(path not in destinations, "output paths must be distinct")
        require(not path.exists(), name + " must be a new file")
        require(path.parent.is_dir(), name + " parent directory is missing")
        destinations.add(path)
        setattr(args, name, path)


def write_new(path, data):
    """Write only a newly created file, never replacing evidence or reports."""
    with Path(path).open("xb") as output:
        output.write(data)


def read_checked(path, role, expected):
    """Authenticate one explicit input; expose only its semantic role on error."""
    data = Path(path).read_bytes()
    require(len(data) == expected["bytes"] and sha(data) == expected["sha256"],
            "evidence identity changed: " + role)
    return data


def source_reader(inputs, expected):
    """Return an authenticated reader and path-free provenance records."""
    provenance = {}

    def read(role):
        data = read_checked(inputs[role], role, expected[role])
        provenance[role] = {"bytes": len(data), "sha256": sha(data)}
        return data

    return read, provenance


def validate_event_hashes(events):
    """Recompute recorded render state hashes, rather than trusting the labels."""
    for event in events:
        canonical = json.dumps(event["state"], sort_keys=True, separators=(",", ":")).encode()
        require(sha(canonical) == event["render_state_hash"], "trace state hash changed")
