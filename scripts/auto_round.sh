#!/usr/bin/env bash
# Unattended matching rounds driven by scheduled Claude Code routines.
#
# One round = one isolated worktree off origin/main, a bounded matching
# session, a clean verify-batch, a labelled PR. A later, independent round
# re-verifies and merges earlier PRs before it starts matching. See
# docs/automation-routines.md for the policy and the routine prompts.
#
# Subcommands (run from any checkout of the repository):
#   status                       Show lock state and busy toolchain containers.
#   start [--budget-minutes N]   Acquire the machine lock and create a round worktree.
#   remaining                    Print the minutes left in the current round.
#   commit -m <message>          Commit the current worktree with the agent identity.
#   open-pr --ids "<id>...> --title <t> --body-file <f>
#                                Push the round branch and open the auto-match PR.
#   review-pending               Re-verify and merge every open auto-match PR without a verdict.
#   review <pr-number>           Re-verify one PR, label it, and merge it when verified.
#   merge <pr-number>            Wait for public checks and merge a verified PR.
#   cleanup                      Stop the round container, remove the worktree and its branch,
#                                prune merged auto/match-* branches, release the lock.
# CONKER_AUTO_NO_MERGE=1 makes review/review-pending verify and label without merging.
set -euo pipefail

script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
repo_root="$(cd "$script_dir/.." && pwd)"
state_dir="${CONKER_AUTO_STATE:-$HOME/.conker-auto}"
lock_dir="$state_dir/lock"
rounds_root="${CONKER_AUTO_ROUNDS:-$(dirname "$repo_root")/conker-auto}"
remote_repo="${CONKER_AUTO_REPO:-DevOldSchool/conkers-bfd-decomp}"
# The ROM lives in the main checkout; this script may run from any linked worktree.
main_checkout="$(git -C "$repo_root" worktree list --porcelain | sed -n '1s/^worktree //p')"
rom_source="${CONKER_AUTO_ROM:-$main_checkout/roms/baserom.us.z64}"
busy_cpu_threshold="${CONKER_AUTO_BUSY_CPU:-25}"
default_budget_minutes="${CONKER_AUTO_BUDGET_MINUTES:-180}"
lock_grace_minutes=90
checks_timeout_minutes=60
label_match=auto-match
label_verified=auto-verified
label_human=needs-human
author_name=DevOldSchool-AI-Agent
author_email=focuses.fixer.3z@icloud.com
trailer=''
pr_footer=''

die() { printf 'auto-round: %s\n' "$*" >&2; exit 1; }
note() { printf 'auto-round: %s\n' "$*" >&2; }
now() { date +%s; }

git_agent() { git -c "user.name=$author_name" -c "user.email=$author_email" "$@"; }

lock_value() { [[ -f "$lock_dir/$1" ]] && cat "$lock_dir/$1" || true; }

busy_containers() {
    # Idle warm containers only run `sleep infinity`. A busy one has compiler or
    # differ processes, shows CPU, or has a host-side conker command driving it;
    # one `docker stats` sample alone reads 0% between build steps.
    local name count
    for name in $(docker ps --format '{{.Names}}' 2>/dev/null | grep '^conker-toolchain-' || true); do
        count="$(docker top "$name" -o pid 2>/dev/null | tail -n +2 | wc -l | tr -d ' ')"
        (( count > 1 )) && printf '%s: %s processes\n' "$name" "$count"
    done
    docker stats --no-stream --format '{{.Name}} {{.CPUPerc}}' 2>/dev/null \
        | awk -v limit="$busy_cpu_threshold" '$1 ~ /^conker-toolchain-/ { sub("%", "", $2); if ($2 + 0 >= limit) print $1 ": " $2 "% cpu" }'
    pgrep -fl 'scripts/conker\.sh (finish|verify-batch|build|game-build|prepare|probe|sweep|permute|automate|diff|objdiff|m2c|next)' 2>/dev/null \
        | sed 's/^/host: /' || true
}

lock_is_stale() {
    local deadline
    deadline="$(lock_value deadline)"
    [[ -n "$deadline" ]] || return 0
    (( $(now) > deadline + lock_grace_minutes * 60 ))
}

release_lock() {
    local pid
    pid="$(lock_value caffeinate_pid)"
    [[ -z "$pid" ]] || kill "$pid" 2>/dev/null || true
    rm -rf "$lock_dir"
}

remove_worktree() {
    local path="$1"
    [[ -d "$path" ]] || return 0
    if [[ -x "$path/conker" ]]; then
        (cd "$path" && ./conker stop >/dev/null 2>&1) || true
    fi
    git -C "$repo_root" worktree remove --force "$path" 2>/dev/null || rm -rf "$path"
    git -C "$repo_root" worktree prune
}

ensure_idle() {
    if [[ -d "$lock_dir" ]]; then
        if lock_is_stale; then
            note "reclaiming stale lock from $(lock_value started) (worktree $(lock_value worktree))"
            remove_worktree "$(lock_value worktree)"
            release_lock
        else
            printf 'AUTO_ROUND: BUSY lock held since %s for %s (deadline %s)\n' \
                "$(lock_value started)" "$(lock_value worktree)" "$(date -r "$(lock_value deadline)" '+%H:%M')"
            exit 3
        fi
    fi
    local busy
    busy="$(busy_containers)"
    if [[ -n "$busy" ]]; then
        printf 'AUTO_ROUND: BUSY toolchain containers in use:\n%s\n' "$busy"
        exit 3
    fi
}

prepare_checkout() {
    # Fresh worktrees need the submodules, a real ROM copy (not a symlink the
    # container cannot follow), the main checkout's pinned host Python (PyYAML)
    # and the US reference split before verify-batch.
    local path="$1"
    git -C "$path" submodule update --init --recursive --quiet
    if [[ -x "$main_checkout/build/host-python/bin/python3" && ! -e "$path/build/host-python" ]]; then
        mkdir -p "$path/build"
        ln -s "$main_checkout/build/host-python" "$path/build/host-python"
    fi
    [[ -f "$rom_source" ]] || die "US ROM not found at $rom_source"
    mkdir -p "$path/roms"
    rm -f "$path/roms/baserom.us.z64"
    cp "$rom_source" "$path/roms/baserom.us.z64"
    (cd "$path" && ./conker setup --us roms/baserom.us.z64 >/dev/null && ./conker _prepare-reference --profile us >/dev/null)
}

ensure_labels() {
    gh label create "$label_match" --repo "$remote_repo" --color 1d76db --force \
        --description 'Opened by an unattended matching round' >/dev/null
    gh label create "$label_verified" --repo "$remote_repo" --color 0e8a16 --force \
        --description 'Independently re-verified by a later round' >/dev/null
    gh label create "$label_human" --repo "$remote_repo" --color d93f0b --force \
        --description 'Automation stopped; a maintainer must look' >/dev/null
}

require_worktree_cwd() {
    local top
    top="$(git rev-parse --show-toplevel 2>/dev/null)" || die "run this inside the round worktree"
    [[ "$top" == "$(lock_value worktree)" ]] || die "current directory is not the locked round worktree ($(lock_value worktree))"
}

cmd_status() {
    if [[ -d "$lock_dir" ]]; then
        printf 'lock: held since %s, worktree %s, deadline %s%s\n' "$(lock_value started)" "$(lock_value worktree)" \
            "$(date -r "$(lock_value deadline)" '+%Y-%m-%d %H:%M')" "$(lock_is_stale && printf ' (stale)')"
    else
        printf 'lock: free\n'
    fi
    local busy
    busy="$(busy_containers)"
    printf 'busy containers: %s\n' "${busy:-none}"
}

cmd_start() {
    local budget="$default_budget_minutes"
    while [[ $# -gt 0 ]]; do
        case "$1" in
            --budget-minutes) budget="$2"; shift 2 ;;
            *) die "unknown start option $1" ;;
        esac
    done
    [[ "$budget" =~ ^[0-9]+$ ]] || die "--budget-minutes needs an integer"
    ensure_idle
    mkdir -p "$state_dir"
    mkdir "$lock_dir" 2>/dev/null || { printf 'AUTO_ROUND: BUSY lock raced\n'; exit 3; }
    local stamp branch path deadline
    stamp="$(date -u +%Y%m%d-%H%M)"
    branch="auto/match-$stamp"
    path="$rounds_root/$stamp"
    deadline=$(( $(now) + budget * 60 ))
    printf '%s\n' "$(date '+%Y-%m-%d %H:%M')" > "$lock_dir/started"
    printf '%s\n' "$deadline" > "$lock_dir/deadline"
    printf '%s\n' "$path" > "$lock_dir/worktree"
    printf '%s\n' "$branch" > "$lock_dir/branch"
    caffeinate -i -t $(( (budget + lock_grace_minutes) * 60 )) >/dev/null 2>&1 &
    printf '%s\n' "$!" > "$lock_dir/caffeinate_pid"
    # A failed start must not leave the lock held or a half-prepared worktree.
    started_ok=0
    trap '(( started_ok )) || { note "start failed; releasing the lock"; remove_worktree "$path"; release_lock; }' EXIT
    mkdir -p "$rounds_root"
    git -C "$repo_root" fetch --quiet origin
    git -C "$repo_root" worktree add --quiet -b "$branch" "$path" origin/main
    prepare_checkout "$path"
    ensure_labels
    started_ok=1
    printf 'AUTO_ROUND: STARTED\nWORKTREE=%s\nBRANCH=%s\nBASE=%s\nDEADLINE_EPOCH=%s\nDEADLINE_LOCAL=%s\n' \
        "$path" "$branch" "$(git -C "$path" rev-parse --short HEAD)" "$deadline" "$(date -r "$deadline" '+%Y-%m-%d %H:%M')"
}

cmd_remaining() {
    [[ -d "$lock_dir" ]] || die "no round is running"
    local left=$(( ($(lock_value deadline) - $(now)) / 60 ))
    printf '%s\n' "$left"
    (( left > 0 )) || printf 'AUTO_ROUND: DEADLINE_PASSED\n'
}

cmd_commit() {
    require_worktree_cwd
    [[ "${1:-}" == "-m" && -n "${2:-}" ]] || die "usage: commit -m <message>"
    git add -A
    git diff --cached --quiet && die "nothing to commit"
    git -c core.whitespace=cr-at-eol diff --cached --check
    if [[ -n "$trailer" ]]; then
        git_agent commit --quiet -m "$2" -m "$trailer"
    else
        git_agent commit --quiet -m "$2"
    fi
    git log --oneline -1
}

cmd_open_pr() {
    require_worktree_cwd
    local ids='' title='' body_file=''
    while [[ $# -gt 0 ]]; do
        case "$1" in
            --ids) ids="$2"; shift 2 ;;
            --title) title="$2"; shift 2 ;;
            --body-file) body_file="$2"; shift 2 ;;
            *) die "unknown open-pr option $1" ;;
        esac
    done
    [[ -n "$ids" && -n "$title" && -f "$body_file" ]] || die "usage: open-pr --ids \"<id>...\" --title <t> --body-file <f>"
    git diff --quiet && git diff --cached --quiet || die "commit the worktree before open-pr"
    local branch body
    branch="$(lock_value branch)"
    body="$(cat "$body_file")"$'\n\n'"Auto-match IDs: $ids"$'\n\n'"$pr_footer"
    git push --quiet -u origin "$branch"
    gh pr create --repo "$remote_repo" --base main --head "$branch" --title "$title" --body "$body" --label "$label_match"
}

pr_json() { gh pr view "$1" --repo "$remote_repo" --json "$2" --jq "$3"; }

pr_comment() { gh pr comment "$1" --repo "$remote_repo" --body "$2" >/dev/null; }

mark_human() {
    local pr="$1" reason="$2"
    note "PR #$pr needs a human: $reason"
    gh pr edit "$pr" --repo "$remote_repo" --add-label "$label_human" >/dev/null
    pr_comment "$pr" "**Automated review stopped**: $reason"$'\n\n'"$pr_footer"
    printf 'AUTO_ROUND: NEEDS_HUMAN %s\n' "$pr"
}

cmd_review_pending() {
    local numbers
    numbers="$(gh pr list --repo "$remote_repo" --state open --label "$label_match" --json number,labels \
        --jq "[.[] | select(all(.labels[].name; . != \"$label_verified\" and . != \"$label_human\")) | .number] | sort | .[]")"
    if [[ -z "$numbers" ]]; then
        printf 'AUTO_ROUND: NO_PENDING_REVIEWS\n'
        return
    fi
    local pr
    for pr in $numbers; do
        cmd_review "$pr" || true
    done
    # A PR verified earlier but not merged (checks were slow, or main moved) is merged now.
    for pr in $(gh pr list --repo "$remote_repo" --state open --label "$label_verified" --json number,labels \
            --jq "[.[] | select(all(.labels[].name; . != \"$label_human\")) | .number] | sort | .[]"); do
        cmd_merge "$pr" || true
    done
}

cmd_review() {
    local pr="$1"
    [[ "$pr" =~ ^[0-9]+$ ]] || die "usage: review <pr-number>"
    local state mergeable head_ref ids path
    state="$(pr_json "$pr" state .state)"
    [[ "$state" == "OPEN" ]] || die "PR #$pr is $state"
    ids="$(pr_json "$pr" body .body | sed -n 's/^Auto-match IDs: *//p' | tail -1)"
    if [[ -z "$ids" ]]; then
        mark_human "$pr" "the PR body has no \`Auto-match IDs:\` line"
        return 1
    fi
    mergeable="$(pr_json "$pr" mergeable .mergeable)"
    if [[ "$mergeable" == "CONFLICTING" ]]; then
        mark_human "$pr" "the branch conflicts with main"
        return 1
    fi
    # Review the branch as it will merge: bring it up to date with main first.
    if [[ "$(pr_json "$pr" mergeStateStatus .mergeStateStatus)" == "BEHIND" ]]; then
        gh pr update-branch "$pr" --repo "$remote_repo" >/dev/null || { mark_human "$pr" "update-branch failed"; return 1; }
        sleep 20
    fi
    head_ref="$(pr_json "$pr" headRefName .headRefName)"
    path="$rounds_root/review-$pr"
    remove_worktree "$path"
    mkdir -p "$rounds_root"
    git -C "$repo_root" fetch --quiet origin
    git -C "$repo_root" fetch --quiet origin "refs/heads/$head_ref"
    git -C "$repo_root" worktree add --quiet --detach "$path" FETCH_HEAD
    prepare_checkout "$path"

    local report verdict policy finish_out batch_out id ok=1
    report="## Automated review (independent re-verification)"$'\n\n'
    report+="Head: \`$(git -C "$path" rev-parse --short HEAD)\` on top of main \`$(git -C "$path" rev-parse --short origin/main)\`."$'\n\n'
    if policy="$(python3 "$script_dir/auto_policy.py" --repo "$path" --base origin/main --head HEAD --ids $ids 2>&1)"; then
        report+="Policy: pass"$'\n'
    else
        ok=0
        report+="Policy: **fail**"$'\n```\n'"$policy"$'\n```\n'
    fi
    if (( ok )); then
        for id in $ids; do
            finish_out="$(cd "$path" && ./conker finish "$id" 2>&1 | tail -40)" || true
            if grep -qx 'AGENT_ACTION: STOP_MATCHED' <<<"$finish_out"; then
                report+="- \`$id\`: STOP_MATCHED"$'\n'
            else
                ok=0
                report+="- \`$id\`: **not STOP_MATCHED**"$'\n```\n'"$(tail -15 <<<"$finish_out")"$'\n```\n'
            fi
        done
    fi
    if (( ok )); then
        batch_out="$(cd "$path" && ./conker verify-batch $ids 2>&1 | tail -60)" || true
        if grep -qx 'AGENT_ACTION: BATCH_COMPLETE' <<<"$batch_out"; then
            report+=$'\n'"verify-batch: BATCH_COMPLETE"$'\n'
        else
            ok=0
            report+=$'\n'"verify-batch: **failed**"$'\n```\n'"$(tail -25 <<<"$batch_out")"$'\n```\n'
        fi
    fi
    remove_worktree "$path"

    if (( ok )); then
        verdict="verified"
        gh pr edit "$pr" --repo "$remote_repo" --add-label "$label_verified" >/dev/null
    else
        verdict="needs-human"
        gh pr edit "$pr" --repo "$remote_repo" --add-label "$label_human" >/dev/null
    fi
    pr_comment "$pr" "$report"$'\n'"Verdict: **$verdict**"$'\n\n'"$pr_footer"
    if (( ok )); then
        printf 'AUTO_ROUND: VERIFIED %s\n' "$pr"
        if [[ -n "${CONKER_AUTO_NO_MERGE:-}" ]]; then
            printf 'AUTO_ROUND: MERGE_SKIPPED %s (CONKER_AUTO_NO_MERGE set)\n' "$pr"
        else
            cmd_merge "$pr"
        fi
    else
        printf 'AUTO_ROUND: NEEDS_HUMAN %s\n' "$pr"
        return 1
    fi
}

cmd_merge() {
    local pr="$1"
    [[ "$pr" =~ ^[0-9]+$ ]] || die "usage: merge <pr-number>"
    local labels
    labels="$(pr_json "$pr" labels '[.labels[].name] | join(" ")')"
    [[ " $labels " == *" $label_verified "* ]] || die "PR #$pr is not labelled $label_verified"
    [[ " $labels " != *" $label_human "* ]] || die "PR #$pr is labelled $label_human"
    local deadline=$(( $(now) + checks_timeout_minutes * 60 )) status buckets
    # Drive off GitHub's own merge state: the ruleset needs every public check
    # green and an up-to-date branch. `gh pr checks --required` reports nothing
    # until the aggregate job exists, so look at the check buckets instead.
    while :; do
        status="$(pr_json "$pr" mergeStateStatus .mergeStateStatus)"
        case "$status" in
            CLEAN|HAS_HOOKS) break ;;
            BEHIND)
                # Main moved; the next review-pending pass re-verifies the updated branch.
                gh pr update-branch "$pr" --repo "$remote_repo" >/dev/null || true
                gh pr edit "$pr" --repo "$remote_repo" --remove-label "$label_verified" >/dev/null
                pr_comment "$pr" "Main moved before merge; the branch was updated and will be re-verified by the next round."$'\n\n'"$pr_footer"
                printf 'AUTO_ROUND: REQUEUED %s\n' "$pr"
                return 1 ;;
            DIRTY) mark_human "$pr" "the branch conflicts with main"; return 1 ;;
            *)
                buckets="$(gh pr checks "$pr" --repo "$remote_repo" --json bucket --jq '[.[].bucket] | unique | join(" ")' 2>/dev/null || true)"
                if [[ " $buckets " == *" fail "* || " $buckets " == *" cancel "* ]]; then
                    mark_human "$pr" "a public check failed or was cancelled"
                    return 1
                fi ;;
        esac
        (( $(now) < deadline )) || { mark_human "$pr" "merge state stayed $status for $checks_timeout_minutes minutes"; return 1; }
        sleep 60
    done
    local head_ref
    head_ref="$(pr_json "$pr" headRefName .headRefName)"
    if gh pr merge "$pr" --repo "$remote_repo" --merge --delete-branch >/dev/null; then
        # --delete-branch can leave the remote ref when the local repo has no copy; make sure.
        git -C "$repo_root" fetch --quiet --prune origin || true
        if git -C "$repo_root" show-ref --verify --quiet "refs/remotes/origin/$head_ref"; then
            git -C "$repo_root" push --quiet origin --delete "$head_ref" || true
        fi
        printf 'AUTO_ROUND: MERGED %s\n' "$pr"
    else
        mark_human "$pr" "gh pr merge failed"
        return 1
    fi
}

prune_round_branches() {
    # Local auto/match-* branches outlive their worktrees: delete any that is not
    # checked out anywhere and is either merged into origin/main or gone upstream.
    local branch upstream
    git -C "$repo_root" fetch --quiet --prune origin || true
    while read -r branch; do
        [[ -n "$branch" ]] || continue
        git -C "$repo_root" worktree list --porcelain | grep -qx "branch refs/heads/$branch" && continue
        if git -C "$repo_root" merge-base --is-ancestor "$branch" origin/main 2>/dev/null; then
            git -C "$repo_root" branch -D "$branch" >/dev/null && note "deleted merged branch $branch"
            continue
        fi
        upstream="$(git -C "$repo_root" rev-parse --abbrev-ref "$branch@{upstream}" 2>/dev/null || true)"
        if [[ -n "$upstream" ]] && ! git -C "$repo_root" show-ref --verify --quiet "refs/remotes/$upstream"; then
            git -C "$repo_root" branch -D "$branch" >/dev/null && note "deleted branch $branch (upstream gone)"
        fi
    done < <(git -C "$repo_root" for-each-ref --format='%(refname:short)' 'refs/heads/auto/match-*')
}

cmd_cleanup() {
    if [[ ! -d "$lock_dir" ]]; then
        prune_round_branches
        printf 'AUTO_ROUND: NO_LOCK\n'
        return
    fi
    local path branch
    path="$(lock_value worktree)"
    branch="$(lock_value branch)"
    if [[ -d "$path" ]] && ! git -C "$path" diff --quiet HEAD 2>/dev/null; then
        note "worktree $path has uncommitted changes; they are discarded"
    fi
    remove_worktree "$path"
    # The round branch lives on in the PR (or was never pushed); the local copy is not needed.
    [[ -z "$branch" ]] || git -C "$repo_root" branch -D "$branch" >/dev/null 2>&1 || true
    prune_round_branches
    release_lock
    printf 'AUTO_ROUND: CLEANED\n'
}

main() {
    local command="${1:-}"
    shift || true
    case "$command" in
        status) cmd_status ;;
        start) cmd_start "$@" ;;
        remaining) cmd_remaining ;;
        commit) cmd_commit "$@" ;;
        open-pr) cmd_open_pr "$@" ;;
        review-pending) cmd_review_pending ;;
        review) cmd_review "$@" ;;
        merge) cmd_merge "$@" ;;
        cleanup) cmd_cleanup ;;
        *) sed -n '2,20p' "${BASH_SOURCE[0]}" | sed 's/^# \{0,1\}//'; exit 2 ;;
    esac
}

main "$@"
