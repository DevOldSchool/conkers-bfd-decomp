"""Shared concurrency setting for build commands and objdiff workers."""
from __future__ import annotations

import argparse
import os
import re


def job_count(value: str | None = None) -> int:
    if value is None:
        value = os.environ.get('CONKER_JOBS') or '4'
    if not re.fullmatch(r'[1-9][0-9]*', value):
        raise ValueError('--jobs/CONKER_JOBS must be a positive integer')
    return int(value)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('jobs', nargs='?')
    args = parser.parse_args()
    try:
        print(job_count(args.jobs))
    except ValueError as error:
        parser.error(str(error))


if __name__ == '__main__':
    main()
