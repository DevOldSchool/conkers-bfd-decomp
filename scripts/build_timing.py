#!/usr/bin/env python3
"""Time one build stage and append its result to an ignored JSONL log."""
from __future__ import annotations

import argparse
from datetime import datetime, timezone
import json
from pathlib import Path
import subprocess
import time


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--profile', required=True, choices=('us', 'eu'))
    parser.add_argument('--mode', required=True, choices=('original', 'rebuilt'))
    parser.add_argument('--stage', required=True)
    parser.add_argument('command', nargs=argparse.REMAINDER)
    args = parser.parse_args()
    command = args.command
    if command[:1] == ['--']:
        command = command[1:]
    if not command:
        parser.error('a command is required after --')
    started_at = datetime.now(timezone.utc).isoformat()
    start = time.perf_counter()
    status = 1
    try:
        # Preserve inherited GNU Make jobserver descriptors for timed recursive makes.
        status = subprocess.run(command, close_fds=False).returncode
        return status
    finally:
        elapsed = time.perf_counter() - start
        result = dict(profile=args.profile, mode=args.mode, stage=args.stage,
                      started_at=started_at, elapsed_seconds=round(elapsed, 3),
                      exit_code=status, command=command)
        output = Path('build/timings') / f'{args.profile}-{args.mode}.jsonl'
        output.parent.mkdir(parents=True, exist_ok=True)
        with output.open('a') as stream:
            stream.write(json.dumps(result) + '\n')
        print(f'TIMING {args.profile}/{args.mode} {args.stage}: {elapsed:.3f}s (exit {status})', flush=True)


if __name__ == '__main__':
    raise SystemExit(main())
