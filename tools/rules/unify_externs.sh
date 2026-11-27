#!/usr/bin/env bash
# SPDX-License-Identifier: MIT
# unify_externs.sh -- give type-conflicting extern globals one declaration,
# proving every retype byte-neutral unit by unit (docs/code-rules.md, R2).
#
# For each global declared with different types, hoist_externs --unify
# proposes a declaration; this script applies it, compiles every retyped unit
# in the toolchain container and compares code (with relocations), data,
# rodata and section sizes against the unchanged unit. A global unifies only
# when all its retyped units are identical. Globals that share a changed unit
# are retried in batches with disjoint units, then with the next candidate.
#
# Usage (through ./conker unify-externs): unify_externs.sh [--apply] [--choices N]
# Without --apply only the report is written (build/unify-<time>/passed).
# With --apply the passing globals are written and every retyped unit is
# checked again; then run ./conker hoist-externs --apply and the byte gates.
#
# The result must not depend on the host. Only a compiler diagnostic counts as
# "this type does not work": an infrastructure failure (the container cannot
# read a source, as Docker Desktop bind mounts can briefly do after a file is
# replaced) is retried, and if it persists the run stops without deciding
# anything. Sources are restored by rewriting them in place, never by
# `git checkout`, and every compile waits until the container sees exactly the
# host's file contents.
set -euo pipefail

apply=0
max_choice=2
while [[ $# -gt 0 ]]; do
    case "$1" in
        --apply) apply=1 ;;
        --choices) max_choice="$2"; shift ;;
        *) echo "usage: unify_externs.sh [--apply] [--choices N]" >&2; exit 2 ;;
    esac
    shift
done
out="build/unify-$(date +%s)"
container="${CONKER_WARM_CONTAINER:?run through ./conker unify-externs}"
git diff --quiet -- src include || { echo "src/ and include/ must be clean" >&2; exit 1; }

mkdir -p "$out"
cc -std=c99 -D_POSIX_C_SOURCE=200809L -O2 -Wall -o "$out/rules_check" tools/rules/rules_check.c
cc -std=c99 -D_POSIX_C_SOURCE=200809L -O2 -Wall -o "$out/hoist_externs" tools/rules/hoist_externs.c
"$out/rules_check" --list-globals > "$out/listing.tsv"

# compile.sh DEST LIST: compile each unit and write a comparable listing of its
# code, data and section sizes (debug sections excluded). A unit whose C does
# not compile goes to DEST/failed; one the container could not read after
# three attempts goes to DEST/infra.
cat > "$out/compile.sh" <<'EOF'
#!/bin/sh
dest="$1"
xargs -P 12 -n 1 sh -c '
    unit="$1"; base="$0/$unit"
    mkdir -p "$(dirname "$base")"
    attempt=1
    while :; do
        if python3 scripts/compile_c.py --profile us --output "$base.o" "$unit" > "$base.log" 2>&1; then
            {
                mips-linux-gnu-objdump -drz "$base.o" | tail -n +4
                mips-linux-gnu-objdump -s -j .data -j .rodata -j .sdata -j .rdata -j .sbss -j .bss "$base.o" 2>/dev/null | tail -n +4
                mips-linux-gnu-objdump -h "$base.o" | awk "/^ *[0-9]+ /{print \$2, \$3}" | grep -v -E "mdebug|comment|gptab|reginfo|options|pdr|note"
            } > "$base.dis"
            break
        fi
        if ! grep -q -E "FileNotFoundError|No such file or directory|Stale file handle|Input/output error|Permission denied" "$base.log"; then
            echo "$unit" >> "$0/failed"         # a compiler diagnostic: this C does not compile
            break
        fi
        if [ "$attempt" -ge 3 ]; then
            echo "$unit" >> "$0/infra"          # the container could not read the unit
            break
        fi
        attempt=$((attempt + 1))
        sleep 1
    done
' "$dest"
EOF
chmod +x "$out/compile.sh"

# visible LISTFILE: wait until the container reads exactly the host's contents
visible() {
    local tries=0
    [[ -s "$1" ]] || return 0
    xargs cksum < "$1" > "$out/host.cksum"
    while :; do
        docker exec -i -w /workspace "$container" sh -c 'xargs cksum' < "$1" > "$out/container.cksum" 2>/dev/null || true
        cmp -s "$out/host.cksum" "$out/container.cksum" && return 0
        tries=$((tries + 1))
        if [[ "$tries" -ge 40 ]]; then
            echo "the container does not see the host's sources after 20 s; nothing decided" >&2
            diff "$out/host.cksum" "$out/container.cksum" >&2 || true
            restore
            exit 1
        fi
        sleep 0.5
    done
}

compile() {   # compile DEST LISTFILE
    mkdir -p "$1"
    : > "$1/failed"
    : > "$1/infra"
    visible "$2"
    docker exec -i -w /workspace "$container" sh "$out/compile.sh" "$1" < "$2"
    if [[ -s "$1/infra" ]]; then
        echo "the container could not read $(wc -l < "$1/infra") units (see $1/infra and their .log files); nothing decided" >&2
        restore
        exit 1
    fi
}

# restore: put src/ back as committed, rewriting files in place (no unlink)
restore() {
    local file

    git diff --name-only -- src | while read -r file; do
        git cat-file --filters "HEAD:$file" > "$file"
    done
    git diff --quiet -- src || { echo "could not restore src/" >&2; exit 1; }
}

identical() {  # identical DEST UNIT -> 0 when the unit compiled to the baseline listing
    ! grep -qxF "$2" "$1/failed" && cmp -s "$out/base/$2.dis" "$1/$2.dis"
}

# baseline: every unit any plan could touch
: > "$out/all-units"
for choice in $(seq 0 "$max_choice"); do
    "$out/hoist_externs" --unify --choice "$choice" "$out/listing.tsv" 2>/dev/null | awk -F'\t' '$1=="U"{print $2}' >> "$out/all-units"
done
sort -u "$out/all-units" -o "$out/all-units"
echo "baseline: $(wc -l < "$out/all-units") units"
compile "$out/base" "$out/all-units"
[[ ! -s "$out/base/failed" ]] || { echo "baseline compile failed:"; cat "$out/base/failed"; exit 1; }

# trial NAME-LIST CHOICE DEST: apply, compile changed units, revert; writes DEST/plan
trial() {
    mkdir -p "$(dirname "$3")"
    "$out/hoist_externs" --unify --apply --only "$1" --choice "$2" "$out/listing.tsv" 2>/dev/null \
        | awk -F'\t' '$1=="U"' > "$3.plan"
    cut -f2 "$3.plan" | sort -u > "$3.units"
    compile "$3" "$3.units"
    restore
}

# judge DEST: print "pass NAME" or "fail NAME" or "ambiguous NAME" per global in DEST.plan
judge() {
    local dest="$1"
    : > "$dest.bad-units"
    while read -r unit; do
        identical "$dest" "$unit" || echo "$unit" >> "$dest.bad-units"
    done < "$dest.units"
    awk -F'\t' -v bad="$dest.bad-units" '
        BEGIN { while ((getline u < bad) > 0) isbad[u] = 1 }
        { units[$3] = units[$3] " " $2; names[$2] = names[$2] " " $3 }
        END {
            for (g in units) {
                n = split(units[g], us, " "); status = "pass"
                for (i = 1; i <= n; i++) {
                    if (!(us[i] in isbad)) continue
                    m = split(names[us[i]], gs, " "); single = 1
                    for (j = 1; j <= m; j++) if (gs[j] != g) single = 0
                    status = single ? "fail" : (status == "fail" ? "fail" : "ambiguous")
                }
                print status, g
            }
        }' "$dest.plan" | sort -u
}

: > "$out/passed"
"$out/hoist_externs" --unify --choice 0 "$out/listing.tsv" 2>/dev/null | awk -F'\t' '$1=="U"{print $3}' | sort -u > "$out/remaining"
for choice in $(seq 0 "$max_choice"); do
    [[ -s "$out/remaining" ]] || break
    round="$out/round$choice"
    trial "$out/remaining" "$choice" "$round/all"
    judge "$round/all" > "$round/all.verdict"
    awk '$1=="pass"{print $2}' "$round/all.verdict" | sed "s/\$/\t$choice/" >> "$out/passed"
    awk '$1=="fail"{print $2}' "$round/all.verdict" > "$round/failed"
    awk '$1=="ambiguous"{print $2}' "$round/all.verdict" > "$round/ambiguous"
    echo "choice $choice: $(grep -c ^pass "$round/all.verdict" || true) pass, $(wc -l < "$round/failed") fail, $(wc -l < "$round/ambiguous") ambiguous"

    # isolate ambiguous globals in batches whose units do not overlap
    batch=0
    while [[ -s "$round/ambiguous" ]]; do
        batch=$((batch + 1))
        awk -F'\t' 'NR==FNR { amb[$1] = 1; next } ($3 in amb) { print $3 "\t" $2 }' \
            "$round/ambiguous" "$round/all.plan" | sort -u > "$round/amb-units"
        awk -F'\t' '
            { units[$1] = units[$1] " " $2 }
            END {
                for (g in units) {
                    n = split(units[g], us, " "); clash = 0
                    for (i = 1; i <= n; i++) if (us[i] in used) clash = 1
                    if (clash) continue
                    for (i = 1; i <= n; i++) used[us[i]] = 1
                    print g
                }
            }' "$round/amb-units" | sort > "$round/batch$batch.names"
        trial "$round/batch$batch.names" "$choice" "$round/batch$batch"
        judge "$round/batch$batch" > "$round/batch$batch.verdict"
        awk '$1=="pass"{print $2}' "$round/batch$batch.verdict" | sed "s/\$/\t$choice/" >> "$out/passed"
        awk '$1!="pass"{print $2}' "$round/batch$batch.verdict" >> "$round/failed"
        grep -vxF -f "$round/batch$batch.names" "$round/ambiguous" > "$round/ambiguous.next" || true
        mv "$round/ambiguous.next" "$round/ambiguous"
        echo "  batch $batch: $(wc -l < "$round/batch$batch.names") globals, $(grep -c ^pass "$round/batch$batch.verdict" || true) pass"
    done
    sort -u "$round/failed" > "$out/remaining"
done
sort -u "$out/passed" -o "$out/passed"
echo "unified: $(wc -l < "$out/passed") globals; still conflicting after trials: $(wc -l < "$out/remaining")"
echo "report: $out/passed (global, choice)"

if [[ "$apply" == 1 && -s "$out/passed" ]]; then
    # apply all passing globals at once, then prove the combination unit by unit
    "$out/hoist_externs" --unify --apply --only "$out/passed" "$out/listing.tsv" 2>/dev/null \
        | awk -F'\t' '$1=="U"' > "$out/final.plan"
    cut -f2 "$out/final.plan" | sort -u > "$out/final.units"
    compile "$out/final" "$out/final.units"
    differs=0
    while read -r unit; do
        identical "$out/final" "$unit" || { echo "differs: $unit" >&2; differs=1; }
    done < "$out/final.units"
    if [[ "$differs" == 1 ]]; then
        restore
        echo "the combined retypes changed object code; nothing applied" >&2
        exit 1
    fi
    echo "applied: $(wc -l < "$out/passed") globals retyped in $(wc -l < "$out/final.units") units, all identical"
    echo "next: ./conker hoist-externs --apply, then ./conker build and ./conker game-build"
fi
