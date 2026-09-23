#!/usr/bin/env python3
"""Fresh-job status publisher: fixed public messages, never build artifacts."""
import argparse
import base64
import json
import os
from pathlib import Path
import subprocess
import tempfile
import time
import urllib.request

from verify import REPOSITORY, checked_sha, resolve

CONTEXT = 'US ROM verification (maintainer approved)'


def request(path, token, payload=None, method=None):
    body = None if payload is None else json.dumps(payload).encode()
    req = urllib.request.Request('https://api.github.com/' + path, data=body, method=method,
        headers={'Accept': 'application/vnd.github+json', 'Authorization': 'Bearer ' + token,
                 'User-Agent': 'conker-verifier'})
    with urllib.request.urlopen(req, timeout=30) as response:
        return json.load(response)


def encode(value):
    return base64.urlsafe_b64encode(json.dumps(value, separators=(',', ':')).encode()).rstrip(b'=')


def installation_token():
    # Private key only exists on the fresh publisher runner, never on the builder.
    app_id = os.environ['VERIFIER_APP_ID']
    if not app_id.isdecimal():
        raise ValueError('Invalid GitHub App ID')
    now = int(time.time())
    message = encode({'alg': 'RS256', 'typ': 'JWT'}) + b'.' + encode({'iat': now - 60, 'exp': now + 300, 'iss': app_id})
    with tempfile.TemporaryDirectory() as temporary:
        key = Path(temporary) / 'app.pem'
        key.write_text(os.environ['VERIFIER_APP_PRIVATE_KEY'])
        key.chmod(0o600)
        signature = subprocess.check_output(['openssl', 'dgst', '-sha256', '-sign', str(key)], input=message)
    jwt = (message + b'.' + base64.urlsafe_b64encode(signature).rstrip(b'=')).decode()
    installation = request(f'repos/{REPOSITORY}/installation', jwt)
    result = request(f'app/installations/{installation["id"]}/access_tokens', jwt,
                     {'repositories': [REPOSITORY.split('/')[1]], 'permissions': {'statuses': 'write'}})
    return result['token']


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--pr', type=int, required=True)
    parser.add_argument('--head', required=True)
    parser.add_argument('--base', required=True)
    parser.add_argument('--merge', required=True)
    parser.add_argument('--state', choices=['pending', 'success', 'failure'], required=True)
    args = parser.parse_args()
    checked_sha(args.head); checked_sha(args.base); checked_sha(args.merge)
    state = args.state
    # Never convert a failure/stale run into a passing result.
    try:
        current = resolve(args.pr, args.head, args.base)
        if current['merge'] != args.merge:
            state = 'failure'
    except Exception:
        state = 'failure'
    descriptions = {'pending': 'Awaiting maintainer-approved private US verification.',
                    'success': 'Approved revision passed private US verification.',
                    'failure': 'Private verification failed, was cancelled, or became stale.'}
    token = installation_token()
    try:
        # The synthetic merge SHA includes the exact base, preventing a previous
        # head-only success from validating a changed base.
        request(f'repos/{REPOSITORY}/statuses/{args.merge}', token,
                {'state': state, 'context': CONTEXT, 'description': descriptions[state]})
    finally:
        req = urllib.request.Request('https://api.github.com/installation/token', method='DELETE',
                                     headers={'Authorization': 'Bearer ' + token, 'User-Agent': 'conker-verifier'})
        with urllib.request.urlopen(req, timeout=30):
            pass
    print('Published fixed verification status for the approved merge revision.')


if __name__ == '__main__':
    main()
