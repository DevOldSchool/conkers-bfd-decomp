#!/usr/bin/env python3
"""Publish public inventory reports after the approved exact-SHA main build.

The workflow dependency is the verification authority. This script does not
verify ROMs and must never be run as a substitute for that job.
"""
from __future__ import annotations

import base64
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess
import tempfile

import project_state as state

REPOSITORY = "DevOldSchool/conkers-bfd-decomp"
REPORT_REF = "refs/heads/progress-reports"
REPORT_FILES = {"summary.json", "badge-us.json", "badge-eu.json", "progress.md"}
PUBLIC_FILES = REPORT_FILES | {"checkpoint.json"}
ZERO_SHA = "0" * 40


def git(root: Path, *args: str, input: str | None = None, env: dict | None = None) -> str:
    return subprocess.check_output(
        ["git", *args], cwd=root, input=input, text=True, env=env,
    ).strip()


def require_sha(value: str) -> str:
    if not isinstance(value, str) or not re.fullmatch(r"[0-9a-f]{40}", value):
        raise ValueError("expected a full source commit SHA")
    return value


def ancestor(root: Path, before: str, after: str) -> bool:
    result = subprocess.run(["git", "merge-base", "--is-ancestor", before, after], cwd=root)
    if result.returncode not in (0, 1):
        raise ValueError("cannot establish checkpoint ancestry")
    return result.returncode == 0


def should_publish(root: Path, source: str, previous: str | None) -> bool:
    if previous is None:
        return True
    require_sha(previous)
    if ancestor(root, source, previous):
        return False  # Same checkpoint or an older rerun; never move backwards.
    if not ancestor(root, previous, source):
        raise ValueError("published and proposed source histories diverge")
    return True


def public_files(output: Path, expected: dict[str, str], source: str,
                 run_id: str, attempt: str) -> dict[str, str]:
    require_sha(source)
    if not all(re.fullmatch(r"[1-9][0-9]*", value) for value in (run_id, attempt)):
        raise ValueError("expected positive workflow run and attempt IDs")
    if set(expected) != REPORT_FILES or output.is_symlink() or not output.is_dir():
        raise ValueError("invalid public report output directory or allowlist")
    if {path.name for path in output.iterdir()} != REPORT_FILES:
        raise ValueError("unexpected or missing files in public report directory")
    for name, content in expected.items():
        path = output / name
        if path.is_symlink() or not path.is_file() or path.stat().st_size > 2_000_000:
            raise ValueError(f"not a regular bounded public report: {name}")
        if path.read_bytes() != content.encode("utf-8"):
            raise ValueError(f"report differs from validated canonical rendering: {name}")
    files = dict(expected)
    run_url = f"https://github.com/{REPOSITORY}/actions/runs/{run_id}/attempts/{attempt}"
    files["progress.md"] = (
        f"Verified source: [`{source}`](https://github.com/{REPOSITORY}/commit/{source}) · "
        f"[Approved main verification]({run_url})\n\n"
        "This inventory checkpoint may lag main while verification or publication is pending.\n"
        "US build verification does not establish EU/PAL, gameplay or asset completion.\n\n"
        + files["progress.md"]
    )
    files["checkpoint.json"] = json.dumps({
        "schema_version": 1, "source_sha": source, "workflow_run_id": run_id,
        "workflow_run_attempt": attempt, "workflow_run_url": run_url,
        "files_sha256": {name: hashlib.sha256(content.encode()).hexdigest()
                         for name, content in sorted(files.items())},
    }, indent=2, sort_keys=True) + "\n"
    return files


def remote_head(root: Path, ref: str) -> str | None:
    result = git(root, "ls-remote", "--refs", "origin", ref)
    if not result:
        return None
    sha, name = result.split()
    if name != ref:
        raise ValueError("unexpected remote ref")
    return require_sha(sha)


def create_commit(root: Path, files: dict[str, str], parent: str | None, source: str) -> str:
    if set(files) != PUBLIC_FILES:
        raise ValueError("publication must contain only the five public outputs")
    with tempfile.TemporaryDirectory(prefix="conker-progress-index-") as temporary:
        env = {**os.environ, "GIT_INDEX_FILE": str(Path(temporary) / "index"),
               "GIT_AUTHOR_NAME": "DevOldSchool-AI-Agent",
               "GIT_AUTHOR_EMAIL": "267263626+DevOldSchool-AI-Agent@users.noreply.github.com",
               "GIT_COMMITTER_NAME": "DevOldSchool-AI-Agent",
               "GIT_COMMITTER_EMAIL": "267263626+DevOldSchool-AI-Agent@users.noreply.github.com"}
        git(root, "read-tree", "--empty", env=env)
        for name, content in sorted(files.items()):
            blob = git(root, "hash-object", "-w", "--stdin", input=content, env=env)
            git(root, "update-index", "--add", "--cacheinfo", f"100644,{blob},{name}", env=env)
        tree = git(root, "write-tree", env=env)
        parents = ["-p", parent] if parent else []
        return git(root, "commit-tree", tree, *parents, "-m", f"Progress for verified main {source}", env=env)


def push_checkpoint(root: Path, commit: str, expected: str | None) -> None:
    # A normal fast-forward push plus a pre-push comparison against the remote's
    # advertised head. Git's server-side ref lock then rejects a later race.
    # This also rejects deletion/rewind races that a plain FF push could accept.
    with tempfile.TemporaryDirectory(prefix="conker-progress-hooks-") as temporary:
        hook = Path(temporary) / "pre-push"
        hook.write_text('''#!/bin/sh
set -eu
while read -r local_ref local_sha remote_ref remote_sha; do
    if [ "$remote_ref" != "refs/heads/progress-reports" ] ||
       [ "$remote_sha" != "$CONKER_EXPECTED_REPORT_HEAD" ]; then
        echo "Report branch changed; rerun the publisher without forcing." >&2
        exit 1
    fi
done
''')
        hook.chmod(0o700)
        git(root, "-c", f"core.hooksPath={temporary}", "push", "--atomic", "origin",
            f"{commit}:{REPORT_REF}",
            env={**os.environ, "CONKER_EXPECTED_REPORT_HEAD": expected or ZERO_SHA})
    if remote_head(root, REPORT_REF) != commit:
        raise ValueError("remote report head changed after publication; inspect before retrying")


def publish(root: Path, files: dict[str, str], source: str) -> str | None:
    require_sha(source)
    if git(root, "rev-parse", "HEAD") != source or git(root, "status", "--porcelain", "--untracked-files=no"):
        raise ValueError("publisher requires a clean checkout of the verified source SHA")
    git(root, "fetch", "--no-tags", "origin", "refs/heads/main")
    main = git(root, "rev-parse", "FETCH_HEAD")
    if not ancestor(root, source, main):
        raise ValueError("verified source is not in current main history")
    expected = remote_head(root, REPORT_REF)
    previous = None
    if expected:
        git(root, "fetch", "--no-tags", "origin", REPORT_REF)
        if git(root, "rev-parse", "FETCH_HEAD") != expected:
            raise ValueError("report branch changed while fetching; rerun")
        entries = git(root, "ls-tree", "-r", expected).splitlines()
        if {line.split("\t")[1] for line in entries} != PUBLIC_FILES or any(
            not line.startswith("100644 blob ") for line in entries
        ):
            raise ValueError("existing report branch has unexpected files or modes")
        checkpoint = json.loads(git(root, "show", f"{expected}:checkpoint.json"))
        if checkpoint.get("schema_version") != 1:
            raise ValueError("unsupported checkpoint schema")
        previous = require_sha(checkpoint.get("source_sha"))
    if not should_publish(root, source, previous):
        print("Skipped: the published checkpoint is already this source or newer.")
        return None
    commit = create_commit(root, files, expected, source)
    push_checkpoint(root, commit, expected)
    print(f"Published verified source {source} as {commit} on progress-reports.")
    return commit


def main() -> None:
    if (os.environ.get("GITHUB_ACTIONS") != "true"
            or os.environ.get("GITHUB_REPOSITORY") != REPOSITORY
            or os.environ.get("GITHUB_REF") != "refs/heads/main"
            or os.environ.get("GITHUB_EVENT_NAME") not in {"push", "workflow_dispatch"}):
        raise ValueError("publication is restricted to the approved main workflow")
    source = require_sha(os.environ["VERIFIED_SHA"])
    if source != os.environ["GITHUB_SHA"]:
        raise ValueError("verified and checked-out workflow SHAs differ")
    _, functions = state.validate_project()
    expected = {path.name: content for path, content in state.progress_contents(functions).items()}
    files = public_files(state.SUMMARY_FILE.parent, expected, source,
                         os.environ["GITHUB_RUN_ID"], os.environ["GITHUB_RUN_ATTEMPT"])
    # Keep the short-lived job credential out of disk config and command lines.
    authorization = base64.b64encode(("x-access-token:" + os.environ["GH_TOKEN"]).encode()).decode()
    os.environ.update(GIT_CONFIG_COUNT="1", GIT_CONFIG_KEY_0="http.https://github.com/.extraheader",
                      GIT_CONFIG_VALUE_0="AUTHORIZATION: basic " + authorization)
    publish(state.ROOT, files, source)


if __name__ == "__main__":
    main()
