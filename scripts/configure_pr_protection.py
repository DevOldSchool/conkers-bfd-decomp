#!/usr/bin/env python3
"""Preview/apply main's PR rules after the new checks and verifier App are live.

Requires the repository owner's gh session. No secrets are read or printed.
"""
import argparse
import json
import subprocess

REPO = 'DevOldSchool/conkers-bfd-decomp'
PUBLIC_CHECK = 'All public PR checks passed'
ROM_CHECK = 'US ROM verification (maintainer approved)'


def api(path, method='GET', data=None):
    args = ['gh', 'api', path, '--method', method]
    if data is not None:
        args += ['--input', '-']
    result = subprocess.check_output(args, input=None if data is None else json.dumps(data).encode())
    return json.loads(result)


def updated_ruleset(existing, app_id, require_reviews=False):
    result = {k: existing[k] for k in ('name', 'target', 'enforcement', 'conditions')}
    if existing.get('bypass_actors'):
        result['bypass_actors'] = existing['bypass_actors']
    result['rules'] = [r for r in existing['rules'] if r['type'] not in {'pull_request', 'required_status_checks'}]
    old_review = next((r['parameters'] for r in existing['rules'] if r['type'] == 'pull_request'), None)
    if require_reviews:
        review = old_review or {}
        result['rules'].append({'type': 'pull_request', 'parameters': {
            **review, 'required_approving_review_count': max(1, review.get('required_approving_review_count', 0)),
            'dismiss_stale_reviews_on_push': True, 'require_code_owner_review': True,
            'require_last_push_approval': True, 'required_review_thread_resolution': True}})
    elif old_review is not None:
        # Keep the single-maintainer workflow usable until another code owner joins.
        result['rules'].append({'type': 'pull_request', 'parameters': dict(old_review)})
    old_checks = next((r['parameters'] for r in existing['rules'] if r['type'] == 'required_status_checks'), {})
    checks = [r for r in old_checks.get('required_status_checks', [])
              if r['context'] not in {'metadata-and-tooling', PUBLIC_CHECK, ROM_CHECK}]
    checks += [{'context': PUBLIC_CHECK, 'integration_id': 15368},
               {'context': ROM_CHECK, 'integration_id': app_id}]
    result['rules'].append({'type': 'required_status_checks', 'parameters': {
        **old_checks, 'strict_required_status_checks_policy': True,
        'do_not_enforce_on_create': False, 'required_status_checks': checks}})
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--app-id', required=True, type=int)
    parser.add_argument('--pr', required=True, type=int, help='PR demonstrating both new passing checks')
    parser.add_argument('--ruleset', type=int, default=21853096)
    parser.add_argument('--require-reviews', action='store_true',
                        help='Also require fresh second-person/code-owner reviews after another maintainer joins')
    parser.add_argument('--apply', action='store_true')
    args = parser.parse_args()
    if args.app_id <= 0:
        parser.error('App ID must be positive')
    existing = api(f'repos/{REPO}/rulesets/{args.ruleset}')
    update = updated_ruleset(existing, args.app_id, args.require_reviews)
    if not args.apply:
        print(json.dumps(update, indent=2))
        return
    if not api(f'repos/{REPO}')['permissions'].get('admin'):
        raise SystemExit('Run --apply from the owner/admin gh session.')
    pr = api(f'repos/{REPO}/pulls/{args.pr}')
    if pr['state'] != 'open' or pr['base']['ref'] != 'main' or pr['base']['repo']['full_name'] != REPO:
        raise SystemExit('Select an open PR targeting this repository main branch.')
    merge = pr['merge_commit_sha']
    if not merge:
        raise SystemExit('The current PR merge revision is not available yet.')
    checks = api(f'repos/{REPO}/commits/{merge}/check-runs?per_page=100')['check_runs']
    statuses = api(f'repos/{REPO}/commits/{merge}/statuses?per_page=100')
    public = next((c for c in checks if c['name'] == PUBLIC_CHECK), None)
    rom = next((s for s in statuses if s['context'] == ROM_CHECK), None)
    if not public or public['conclusion'] != 'success' or public['app']['id'] != 15368 or not rom or rom['state'] != 'success':
        raise SystemExit('Both new checks must first pass on the same current PR merge revision.')
    # Status API does not expose installation identity: confirm the App slug via API.
    app_slug = rom['creator']['login'].removesuffix('[bot]')
    if api(f'apps/{app_slug}')['id'] != args.app_id:
        raise SystemExit('ROM status was not posted by the expected verifier App.')
    fresh = api(f'repos/{REPO}/pulls/{args.pr}')
    if (fresh['state'] != 'open' or fresh['merge_commit_sha'] != merge
            or fresh['head']['sha'] != pr['head']['sha'] or fresh['base']['sha'] != pr['base']['sha']):
        raise SystemExit('PR changed while checking readiness; refresh and retry.')
    api(f'repos/{REPO}/rulesets/{args.ruleset}', 'PUT', update)
    print('Enabled named PR checks and verifier App binding.' +
          (' Fresh second-person/code-owner reviews are required.' if args.require_reviews else ' Existing review policy preserved.'))


if __name__ == '__main__':
    main()
