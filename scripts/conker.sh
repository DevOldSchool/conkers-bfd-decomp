#!/usr/bin/env bash
# SPDX-License-Identifier: MIT
set -euo pipefail

repo_root="$(CDPATH= cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
state_tool="$repo_root/scripts/project_state.py"
toolchain_lock="$repo_root/toolchain/tools.lock.json"
locked_image="$(python3 -c 'import json, sys; lock = json.load(open(sys.argv[1], encoding="utf-8")); image = lock["container_image"]; print(f"{image['"'"'repository'"'"']}@{image['"'"'digest'"'"']}")' "$toolchain_lock")"
image_name="${CONKER_IMAGE:-$locked_image}"
local_image_name="conkers-bfd-decomp-toolchain:local-amd64"
workspace_id="$(python3 -c 'import hashlib, sys; print(hashlib.sha256(sys.argv[1].encode()).hexdigest()[:12])' "$repo_root")"
warm_container_name="conker-toolchain-$workspace_id"
warm_container_schema="1"
mips_to_c_revision="$(python3 -c 'import json, sys; print(json.load(open(sys.argv[1], encoding="utf-8"))["tools"]["mips_to_c"]["revision"])' "$toolchain_lock")"
host_mips_to_c="$repo_root/build/host-tools/mips_to_c-$mips_to_c_revision"

container_run_args=(
    --platform linux/amd64
    --network none
    --read-only
    --cap-drop ALL
    --security-opt no-new-privileges
    --pids-limit 512
    --user "$(id -u):$(id -g)"
    --tmpfs /tmp:rw,nosuid,nodev,size=1g
)

die() {
    printf 'error: %s\n' "$*" >&2
    exit 1
}

[[ "$mips_to_c_revision" =~ ^[0-9a-f]{40}$ ]] || die "invalid pinned mips_to_c revision"

usage() {
    cat <<'EOF'
Usage: ./conker <command> [options]

Getting started
  doctor                         Check Docker and local prerequisites.
  rom-info <path>                Print a ROM's SHA-1 and file size.
  setup --us <path> [--eu <path>]
                                 Validate the active US ROM; EU/PAL is optional future setup.
  progress [render|check]        Show, regenerate, or verify project progress.
  progress match <work-item-id>
                                 Verify and record a zero-difference function match.
  progress integrate <work-item-id>
                                 Verify and record a byte-identical source-unit integration.
  progress integrate --all-reviewed
                                 Integrate all incomplete reviewed game units in one build.
  normalize-source-headers       Move reviewed source-unit comments below includes.
  next [--one [--details]]       List functions ready to claim; optionally show one with local context.
  next --ready                   Select one function, prewarm Docker, and include its m2c starter.
  automate-simple [--limit N] [--max-attempts N]
                                 Keep unchanged, placeholder-free m2c bodies only when CURRENT (0).
  defer <work-item-id> --reason <text>
                                 Measure and record its score, preserve its C candidate,
                                 restore GLOBAL_ASM, and skip selection.
  resume <work-item-id>          Restore its C candidate and return it to automatic selection.
  finish [--profile us] <work-item-id>
                                 Record CURRENT (0), then check progress and whitespace.
  verify-batch [--incremental] <work-item-id> [<work-item-id>...]
                                 Run end-of-batch gates; incremental is for local iteration only.
  stop                           Stop and remove this checkout's warm toolchain container.

After the raw base split map is available
  prepare [--profile us]         Extract generated sources (defaults to US).
  build [--profile us|--all]     Build US by default (`--all` means all active profiles).
  diff [--profile us] <work-item-id>
  diff --record [--profile us] <work-item-id>
                                 Show a focused diff and record it immediately when CURRENT (0).
  diff --watch [--profile us] <work-item-id>
                                 Keep an auto-rebuilding focused diff open while editing.
  first-diff [--profile us]      Report the first difference in a rebuilt ROM.
  mupen [mupen64plus-options]    Run the pinned headless Mupen64Plus debugger on the US ROM.
  m2c [--profile us] <work-item-id>
                                 Generate a C starter; auto-detects main versus game overlay.
  game-asm [--profile us]        Export decompressed game-code reference assembly.
  game-index                     List reviewable US game-function proposals.
  register-game --id <id> --us <symbol> --source <path>
                                 Register one US game-overlay function for matching work.
  register-main --id <id> --us <symbol> --source <path>
                                 Register one US main-executable function for matching work.
  register-source-unit [--overlay main|game] --source <path> (--function <id>...|--register-members) --us-start <offset>
      --us-end <offset> --evidence-kind <kind> --evidence-reference <reference>
                                 Register a separately reviewed source/object boundary.
  withdraw-source-unit --source <path>
                                 Withdraw a raw game boundary while retaining function work.
  retire-library-units --evidence-reference <path> [--source <path>...]
                                 Remove untouched raw-ASM units after exact archive mapping.
      --source <path> --preserved-source <library-path>
                                 Retire matched Rare work only after verifying an identical library source copy.
  game-m2c [--profile us] <work-item-id>
                                 Compatibility alias for the auto-detecting m2c command.
  game-diff [--profile us] <work-item-id>
                                 Compatibility alias for the auto-detecting diff command.
  game-build [--profile us] [--refresh]
                                 Incrementally build and byte-verify game units; --refresh rebuilds the cache.
  rzip-extract [--profile us|debug|ects] [--rom <path>] [--output <dir>]
                                 Separate game code/data and indexed asset files.
  rzip-pack --profile us --input <packed-assets> [--output <rom>] [--force]
                                 Rebuild the fixed US flat RZIP region into a ROM.
  font-assets <extract|pack|verify> [options]
                                 Extract, rebuild, or byte-verify the RLE font table.
  mp3-assets <extract|pack|verify|cue-extract|cue-verify> [options]
                                 Extract or verify US MP3 streams, tables, and embedded cues.
  audio-assets <survey|extract|preview|sample-preview|verify> [options]
                                 Survey, extract, preview, or byte-verify US non-MP3 audio assets.
  texture-assets <extract|pack|verify|survey> [options]
                                 Survey, extract, rebuild, or verify proven US textures.
  model-assets <survey|extract|preview|verify> [options]
                                 Survey, export, preview, or verify proven US model banks.
  hud-assets <survey|extract|preview|verify> [options]
                                 Extract, preview, or verify US HUD/menu metadata and sprites.
  asset-correlate [--base us] [--compare debug|ects] [--output <path>] [--force]
                                 Correlate manifest-only asset fingerprints across profiles.
  beta-index [--refresh]         Correlate beta functions/source paths with retail US.
  library-audit [--json]        Scan raw US main ranges for complete I-L libultra sections.
  rareunzip <input> <output>     Decompress one RZIP chunk (paths inside this repository).
  libultra [--version I|J|K|L]  Build a pinned 2.0 libultra ROM archive (default: L).
  rsp                          Assemble and byte-verify the configured US RSP payloads.
  libultrare                    Build and verify the pinned Rare-modified archive.

All build commands run inside the pinned linux/amd64 Docker environment.
US is the default profile; pass --profile explicitly only to override it.
EOF
}

require_docker() {
    if ! command -v docker >/dev/null 2>&1; then
        printf '%s\n' 'error: Docker is required. Install Docker Desktop or Docker Engine, then rerun ./conker doctor.' >&2
        return 1
    fi
}

require_docker_access() {
    require_docker || return 1
    if ! docker info --format '{{.ServerVersion}}' >/dev/null 2>&1; then
        printf '%s\n' 'error: Docker is installed, but this process cannot access the Docker daemon. Start Docker or grant Docker socket permission, then rerun the command.' >&2
        return 1
    fi
}

image_is_healthy() {
    docker run --rm "${container_run_args[@]}" \
        --mount "type=bind,source=$repo_root/tests/fixtures/ido_smoke.c,target=/tmp/ido-smoke.c,readonly" \
        "$image_name" sh -c \
        'test -x /opt/ido/cc && test -f /opt/tools/asm-processor/build.py && test -x /usr/local/bin/conker-mupen64plus && test -f /opt/mupen64plus/lib/libmupen64plus.so.2 && test -f /opt/mupen64plus/lib/mupen64plus/mupen64plus-rsp-hle.so && command -v wget >/dev/null && command -v less >/dev/null && /usr/local/bin/conker-mupen64plus --help 2>&1 | grep -q "Console User-Interface Version 2.6.0" && /opt/ido/cc -c -32 -G 0 -non_shared -O2 -mips2 -o /tmp/ido-smoke.o /tmp/ido-smoke.c && test -s /tmp/ido-smoke.o' \
        >/dev/null 2>&1
}

watch_image_is_compatible() {
    [[ "$(docker image inspect --format '{{ index .Config.Labels "org.devoldschool.conker.diff-watch" }}' "$image_name" 2>/dev/null)" == "1" ]]
}

ensure_cpu_image() {
    require_docker || return 1
    if docker image inspect "$image_name" >/dev/null 2>&1; then
        return
    fi
    require_docker_access || return 1
    printf 'Fetching the published toolchain image (%s)...\n' "$image_name"
    if ! docker pull --platform linux/amd64 "$image_name"; then
        printf 'Published image unavailable; building it locally...\n'
        docker build --platform linux/amd64 --tag "$local_image_name" "$repo_root"
        image_name="$local_image_name"
    fi
    if ! image_is_healthy; then
        printf 'Toolchain image is missing a required pinned dependency; rebuilding it locally...\n'
        docker build --platform linux/amd64 --tag "$local_image_name" "$repo_root"
        image_name="$local_image_name"
        image_is_healthy || die "toolchain image failed the IDO compilation smoke test"
    fi
}

ensure_image() {
    if [[ "${rsp_image_ready:-0}" == 1 ]]; then return; fi
    ensure_cpu_image || return 1
    local armips_revision
    local rsp_image
    local rsp_key
    armips_revision="$(python3 -c 'import json, sys; print(json.load(open(sys.argv[1]))["tools"]["armips"]["revision"])' "$toolchain_lock")"
    [[ "$armips_revision" =~ ^[0-9a-f]{40}$ ]] || die "invalid pinned armips revision"
    rsp_key="$(python3 -c 'import hashlib, pathlib, sys; print(hashlib.sha256(pathlib.Path(sys.argv[1]).read_bytes() + sys.argv[2].encode() + sys.argv[3].encode()).hexdigest()[:16])' "$repo_root/toolchain/rsp.Dockerfile" "$(docker image inspect --format '{{.Id}}' "$image_name")" "$armips_revision")"
    rsp_image="conkers-bfd-rsp:$rsp_key"
    if ! docker image inspect "$rsp_image" >/dev/null 2>&1; then
        docker build --platform linux/amd64 --tag "$rsp_image" \
            --build-arg "BASE_IMAGE=$image_name" --build-arg "ARMIPS_REV=$armips_revision" \
            -f "$repo_root/toolchain/rsp.Dockerfile" "$repo_root/toolchain"
    fi
    image_name="$rsp_image"
    rsp_image_ready=1
}

add_workspace_mount() {
    local relative_path="$1"
    local access="${2:-readonly}"
    local mount="type=bind,source=$repo_root/$relative_path,target=/workspace/$relative_path"
    if [[ ! -e "$repo_root/$relative_path" ]]; then
        return 0
    fi
    if [[ "$access" == "readonly" ]]; then
        mount="$mount,readonly"
    fi
    workspace_mounts+=(--mount "$mount")
}

workspace_mount_args() {
    local mode="${1:-build}"
    local path
    local access

    mkdir -p "$repo_root/asm" "$repo_root/assets" "$repo_root/build" "$repo_root/reference"
    workspace_mounts=(--tmpfs /workspace:rw,nosuid,nodev,size=256m,mode=1777)

    add_workspace_mount Makefile
    add_workspace_mount Dockerfile
    for path in config docs include lib progress scripts src tests toolchain tools; do
        access=readonly
        if [[ "$mode" == "integrate" ]]; then
            case "$path" in
                config|docs|progress|src) access=readwrite ;;
            esac
        elif [[ "$mode" == "libultra" && "$path" == "lib" ]]; then
            access=readwrite
        fi
        add_workspace_mount "$path" "$access"
    done
    for path in asm assets build reference; do
        add_workspace_mount "$path" readwrite
    done
    add_workspace_mount roms
    add_workspace_mount .private-rom-assets
}

remove_warm_container() {
    if docker container inspect "$warm_container_name" >/dev/null 2>&1; then
        docker rm --force "$warm_container_name" >/dev/null
    fi
}

ensure_warm_container() {
    local desired_image_id
    local current_image_id
    local current_schema
    local running

    ensure_image
    desired_image_id="$(docker image inspect --format '{{.Id}}' "$image_name")"
    if docker container inspect "$warm_container_name" >/dev/null 2>&1; then
        current_image_id="$(docker container inspect --format '{{.Image}}' "$warm_container_name")"
        current_schema="$(docker container inspect --format '{{index .Config.Labels "org.devoldschool.conker.warm-schema"}}' "$warm_container_name")"
        if [[ "$current_image_id" != "$desired_image_id" || "$current_schema" != "$warm_container_schema" ]]; then
            remove_warm_container
        fi
    fi

    if ! docker container inspect "$warm_container_name" >/dev/null 2>&1; then
        workspace_mount_args
        docker run --detach \
            --name "$warm_container_name" \
            --label "org.devoldschool.conker.warm-schema=$warm_container_schema" \
            "${container_run_args[@]}" \
            "${workspace_mounts[@]}" \
            --workdir /workspace \
            "$image_name" sleep infinity >/dev/null
        return
    fi

    running="$(docker container inspect --format '{{.State.Running}}' "$warm_container_name")"
    if [[ "$running" != "true" ]]; then
        docker start "$warm_container_name" >/dev/null
    fi
}

ensure_host_mips_to_c() {
    local cache_parent="$repo_root/build/host-tools"
    local temporary_cache="$cache_parent/.mips_to_c-$mips_to_c_revision.tmp.$$"

    if [[ -f "$host_mips_to_c/m2c.py" && -d "$host_mips_to_c/m2c" ]]; then
        return
    fi
    ensure_warm_container
    mkdir -p "$cache_parent"
    [[ "$temporary_cache" == "$cache_parent/"* ]] || die "refusing unsafe host-tool cache path"
    [[ "$host_mips_to_c" == "$cache_parent/mips_to_c-"* ]] || die "refusing unsafe host-tool cache path"
    rm -rf "$temporary_cache"
    mkdir -p "$temporary_cache"
    docker cp "$warm_container_name:/opt/tools/mips_to_c/." "$temporary_cache"
    [[ -f "$temporary_cache/m2c.py" && -d "$temporary_cache/m2c" ]] || die "pinned mips_to_c cache is incomplete"
    rm -rf "$host_mips_to_c"
    mv "$temporary_cache" "$host_mips_to_c"
}

run_host_mips_to_c() {
    ensure_host_mips_to_c
    CONKER_HOST_M2C=1 \
        CONKER_MIPS_TO_C="$host_mips_to_c/m2c.py" \
        PYTHONPATH="$host_mips_to_c${PYTHONPATH:+:$PYTHONPATH}" \
        python3 scripts/m2c.py "$@"
}

run_in_container() {
    ensure_warm_container
    run_in_warm_container "$@"
}

run_in_warm_container() {
    docker exec --workdir /workspace "$warm_container_name" "$@"
}

run_in_container_integrating() {
    ensure_image
    workspace_mount_args integrate
    docker run --rm "${container_run_args[@]}" \
        "${workspace_mounts[@]}" \
        --workdir /workspace \
        "$image_name" "$@"
}

run_in_container_libultra() {
    ensure_image
    workspace_mount_args libultra
    docker run --rm "${container_run_args[@]}" \
        "${workspace_mounts[@]}" \
        --workdir /workspace \
        "$image_name" "$@"
}

run_in_container_interactive() {
    ensure_image
    if ! watch_image_is_compatible; then
        printf 'Toolchain image predates diff-watch support; rebuilding it locally...\n'
        docker build --platform linux/amd64 --tag "$local_image_name" "$repo_root"
        image_name="$local_image_name"
        image_is_healthy || die "toolchain image failed the diff-watch smoke test"
    fi
    ensure_warm_container
    exec docker exec --interactive --tty --workdir /workspace "$warm_container_name" "$@"
}

require_profile() {
    case "$1" in
        us) ;;
        eu) die "profile 'eu' is preserved as a future goal; the active target is 'us'" ;;
        *) die "profile must be 'us'" ;;
    esac
}

parse_profile_and_value() {
    local usage_text="$1"
    shift
    selected_profile=us
    selected_value=""
    if [[ $# -eq 1 ]]; then
        selected_value="$1"
    elif [[ $# -eq 3 && "$1" == "--profile" ]]; then
        selected_profile="$2"
        selected_value="$3"
    else
        die "$usage_text"
    fi
    require_profile "$selected_profile"
}

parse_profile_only() {
    local usage_text="$1"
    shift
    selected_profile=us
    if [[ $# -eq 0 ]]; then
        :
    elif [[ $# -eq 2 && "$1" == "--profile" ]]; then
        selected_profile="$2"
    else
        die "$usage_text"
    fi
    require_profile "$selected_profile"
}

parse_game_build_options() {
    local usage_text="$1"
    shift
    selected_profile=us
    refresh_game_build=false
    while [[ $# -gt 0 ]]; do
        case "$1" in
            --profile)
                [[ $# -ge 2 ]] || die "$usage_text"
                selected_profile="$2"
                shift 2
                ;;
            --refresh)
                refresh_game_build=true
                shift
                ;;
            *) die "$usage_text" ;;
        esac
    done
    require_profile "$selected_profile"
}

verify_and_record_match() {
    if ! python3 "$state_tool" setup-check --profile "$selected_profile"; then
        return 3
    fi
    if ! ensure_warm_container; then
        return 3
    fi
    diff_status=0
    run_in_warm_container python3 scripts/diff.py "$selected_profile" "$selected_value" --auto-overlay --require-match || diff_status=$?
    if [[ "$diff_status" -ne 0 ]]; then
        return "$diff_status"
    fi
    if ! python3 "$state_tool" mark-matched --profile "$selected_profile" "$selected_value"; then
        return 3
    fi
}

prepare_next_work() {
    local details
    local first_line
    local identifier
    details="$(python3 "$state_tool" next --one --details)"
    first_line="${details%%$'\n'*}"
    [[ "$first_line" == "work-item: "* ]] || die "next --one --details did not emit a work-item"
    identifier="${first_line#work-item: }"
    printf '%s\n' "$details"
    python3 "$state_tool" setup-check --profile us
    ensure_warm_container
    printf 'toolchain: warm (%s)\n' "$warm_container_name"
    run_host_mips_to_c us "$identifier" --auto-overlay --ready-output
}

command="${1:-help}"
shift || true

case "$command" in
    help|-h|--help)
        usage
        ;;
    doctor)
        ensure_image
        if ! image_is_healthy; then
            printf 'Toolchain image failed its smoke tests; rebuilding it locally...\n'
            docker build --platform linux/amd64 --tag "$local_image_name" "$repo_root"
            image_name="$local_image_name"
            image_is_healthy || die "toolchain image failed its smoke tests"
        fi
        docker version --format 'Docker client: {{.Client.Version}}'
        printf 'Required container platform: linux/amd64\n'
        printf 'IDO compilation smoke test: OK\n'
        printf 'Mupen64Plus debugger smoke test: OK\n'
        python3 "$state_tool" validate
        ;;
    rom-info)
        [[ $# -eq 1 ]] || die "usage: ./conker rom-info <path>"
        python3 "$state_tool" rom-info "$1"
        ;;
    setup)
        python3 "$state_tool" setup "$@"
        ;;
    progress)
        action="${1:-show}"
        case "$action" in
            show) python3 "$state_tool" progress --show ;;
            render) python3 "$state_tool" progress --render ;;
            check) python3 "$state_tool" progress --check ;;
            match)
                shift
                parse_profile_and_value "usage: ./conker progress match [--profile us] <work-item-id>" "$@"
                verify_and_record_match
                ;;
            integrate)
                shift
                parse_profile_and_value "usage: ./conker progress integrate [--profile us] <work-item-id>|--all-reviewed" "$@"
                python3 "$state_tool" setup-check --profile "$selected_profile"
                run_in_container_libultra make --silent game-libs
                if [[ "$selected_value" == "--all-reviewed" ]]; then
                    run_in_container_integrating python3 scripts/integrate.py --profile "$selected_profile" --all-reviewed
                else
                    run_in_container_integrating python3 scripts/integrate.py --profile "$selected_profile" "$selected_value"
                fi
                ;;
            *) die "usage: ./conker progress [render|check] | ./conker progress match [--profile us] <work-item-id> | ./conker progress integrate [--profile us] <work-item-id>|--all-reviewed" ;;
        esac
        ;;
    normalize-source-headers)
        [[ $# -eq 0 ]] || die "usage: ./conker normalize-source-headers"
        python3 "$state_tool" normalize-source-headers
        ;;
    next)
        if [[ "${1:-}" == "--ready" ]]; then
            [[ $# -eq 1 ]] || die "usage: ./conker next --ready"
            prepare_next_work
        else
            python3 "$state_tool" next "$@"
        fi
        ;;
    automate-simple)
        python3 scripts/automate_simple_m2c.py "$@"
        ;;
    defer)
        [[ $# -ge 3 ]] || die "usage: ./conker defer <work-item-id> --reason <text>"
        deferred_symbol="$1"
        python3 "$state_tool" setup-check --profile us
        ensure_warm_container
        deferred_score="$(run_in_warm_container python3 scripts/diff.py us "$deferred_symbol" --auto-overlay --score-only)"
        [[ "$deferred_score" =~ ^[0-9]+$ ]] || die "focused diff did not return a numeric score"
        [[ "$deferred_score" -gt 0 ]] || die "cannot defer an exact CURRENT (0) candidate; run finish instead"
        python3 "$state_tool" defer "$@" --score "$deferred_score"
        ;;
    resume)
        [[ $# -eq 1 ]] || die "usage: ./conker resume <work-item-id>"
        python3 "$state_tool" resume "$1"
        ;;
    finish)
        parse_profile_and_value "usage: ./conker finish [--profile us] <work-item-id>" "$@"
        match_status=0
        verify_and_record_match || match_status=$?
        if [[ "$match_status" -eq 1 ]]; then
            printf 'AGENT_ACTION: CONTINUE_MISMATCH\n'
            exit 1
        elif [[ "$match_status" -eq 2 ]]; then
            printf 'AGENT_ACTION: FIX_COMPILE\n'
            exit 2
        elif [[ "$match_status" -ne 0 ]]; then
            printf 'AGENT_ACTION: BLOCKED_TOOLING\n'
            exit "$match_status"
        fi
        if ! python3 "$state_tool" progress --check; then
            printf 'AGENT_ACTION: BLOCKED_TOOLING\n'
            exit 1
        fi
        if ! git -C "$repo_root" -c core.whitespace=cr-at-eol diff --check; then
            printf 'AGENT_ACTION: BLOCKED_TOOLING\n'
            exit 1
        fi
        printf '%s: per-function gate passed (match, progress, whitespace).\n' "$selected_value"
        printf 'AGENT_ACTION: STOP_MATCHED\n'
        ;;
    verify-batch)
        batch_mode="clean"
        if [[ "${1:-}" == "--incremental" ]]; then
            batch_mode="incremental"
            shift
        fi
        [[ $# -gt 0 ]] || die "usage: ./conker verify-batch [--incremental] <work-item-id> [<work-item-id>...]"
        batch_failure_stamp="$repo_root/build/verify-batch/clean-integration-failure.sha256"
        batch_fingerprint="$(python3 "$state_tool" batch-fingerprint)"
        if [[ "$batch_mode" == "clean" && -f "$batch_failure_stamp" ]]; then
            previous_batch_fingerprint=""
            IFS= read -r previous_batch_fingerprint < "$batch_failure_stamp" || true
            if [[ "$previous_batch_fingerprint" == "$batch_fingerprint" ]]; then
                printf '%s\n' 'error: this exact worktree already failed clean integration; change the source before rerunning verify-batch.' >&2
                printf 'AGENT_ACTION: FIX_INTEGRATION\n'
                exit 1
            fi
        fi
        batch_overlays=""
        if ! batch_overlays="$(python3 "$state_tool" batch-plan "$@")"; then
            printf 'AGENT_ACTION: BLOCKED_TOOLING\n'
            exit 1
        fi
        if ! python3 "$state_tool" setup-check --profile us; then
            printf 'AGENT_ACTION: BLOCKED_TOOLING\n'
            exit 1
        fi
        if [[ " $batch_overlays " == *" main "* ]]; then
            if ! run_in_container make --silent --jobs 4 build PROFILE=us; then
                printf 'AGENT_ACTION: BLOCKED_TOOLING\n'
                exit 1
            fi
        fi
        if [[ " $batch_overlays " == *" game "* ]]; then
            if ! run_in_container_libultra make --silent game-libs; then
                printf 'AGENT_ACTION: BLOCKED_TOOLING\n'
                exit 1
            fi
            game_batch_target="game-integrated-refresh"
            if [[ "$batch_mode" == "incremental" ]]; then
                game_batch_target="game-integrated"
            fi
            if ! run_in_container make --silent --jobs 4 "$game_batch_target" GAME_PROFILE=us; then
                integrated_binary="$repo_root/build/game-integrated/us/conker.game.us.integrated.bin"
                integrated_reference="$repo_root/build/game-integrated/us/game.code.bin"
                if [[ -f "$integrated_binary" && -f "$integrated_reference" ]] && ! cmp -s "$integrated_binary" "$integrated_reference"; then
                    if [[ "$batch_mode" == "clean" ]]; then
                        mkdir -p "$(dirname "$batch_failure_stamp")"
                        printf '%s\n' "$batch_fingerprint" > "$batch_failure_stamp"
                    fi
                    printf 'AGENT_ACTION: FIX_INTEGRATION\n'
                else
                    printf 'AGENT_ACTION: BLOCKED_TOOLING\n'
                fi
                exit 1
            fi
        fi
        if ! python3 -m unittest discover -s tests -q -b; then
            printf 'AGENT_ACTION: BLOCKED_TOOLING\n'
            exit 1
        fi
        if ! python3 "$state_tool" validate; then
            printf 'AGENT_ACTION: BLOCKED_TOOLING\n'
            exit 1
        fi
        if ! python3 "$state_tool" progress --check; then
            printf 'AGENT_ACTION: BLOCKED_TOOLING\n'
            exit 1
        fi
        if ! git -C "$repo_root" -c core.whitespace=cr-at-eol diff --check; then
            printf 'AGENT_ACTION: BLOCKED_TOOLING\n'
            exit 1
        fi
        rm -f "$batch_failure_stamp"
        printf 'Verified batch (%s): %s\n' "$batch_mode" "$*"
        printf 'AGENT_ACTION: BATCH_COMPLETE\n'
        ;;
    stop)
        require_docker_access
        if docker container inspect "$warm_container_name" >/dev/null 2>&1; then
            remove_warm_container
            printf 'Removed warm toolchain container %s.\n' "$warm_container_name"
        else
            printf 'No warm toolchain container is running for this checkout.\n'
        fi
        ;;
    prepare|build)
        if [[ $# -eq 1 && "$1" == "--all" ]]; then
            python3 "$state_tool" setup-check --all
            if [[ "$command" == "build" ]]; then
                run_in_container_libultra make profile-libs PROFILE=us
            fi
            run_in_container make "$command" PROFILE=us
        else
            parse_profile_only "usage: ./conker $command [--profile us|--all]" "$@"
            python3 "$state_tool" setup-check --profile "$selected_profile"
            if [[ "$command" == "build" && "$selected_profile" == "us" ]]; then
                run_in_container_libultra make profile-libs PROFILE=us
            fi
            run_in_container make "$command" PROFILE="$selected_profile"
        fi
        ;;
    m2c)
        parse_profile_and_value "usage: ./conker m2c [--profile us] <work-item-id>" "$@"
        python3 "$state_tool" setup-check --profile "$selected_profile"
        run_host_mips_to_c "$selected_profile" "$selected_value" --auto-overlay
        ;;
    diff)
        if [[ "${1:-}" == "--watch" ]]; then
            shift
            parse_profile_and_value "usage: ./conker diff --watch [--profile us] <work-item-id>" "$@"
            if [[ ! -t 0 || ! -t 1 ]]; then
                printf '%s\n' 'error: diff --watch requires an interactive terminal; use finish for a noninteractive edit loop.' >&2
                printf 'AGENT_ACTION: USE_FINISH_LOOP\n'
                exit 2
            fi
            python3 "$state_tool" setup-check --profile "$selected_profile"
            run_in_container_interactive python3 scripts/diff.py "$selected_profile" "$selected_value" --auto-overlay --watch
        elif [[ "${1:-}" == "--record" ]]; then
            shift
            parse_profile_and_value "usage: ./conker diff --record [--profile us] <work-item-id>" "$@"
            verify_and_record_match
        else
            parse_profile_and_value "usage: ./conker diff [--profile us] <work-item-id>" "$@"
            python3 "$state_tool" setup-check --profile "$selected_profile"
            run_in_container python3 scripts/diff.py "$selected_profile" "$selected_value" --auto-overlay
        fi
        ;;
    first-diff)
        parse_profile_only "usage: ./conker first-diff [--profile us]" "$@"
        python3 "$state_tool" setup-check --profile "$selected_profile"
        run_in_container python3 scripts/first_diff.py "$selected_profile"
        ;;
    mupen)
        if [[ $# -eq 1 && "$1" == "--help" ]]; then
            run_in_container /usr/local/bin/conker-mupen64plus --help || {
                status=$?
                # Mupen64Plus 2.6.0 reports help with status 1.
                [[ $status -eq 1 ]] || exit "$status"
            }
            exit 0
        fi
        [[ -t 0 && -t 1 ]] || die "mupen requires an interactive terminal"
        python3 "$state_tool" setup-check --profile us
        run_in_container_interactive /usr/local/bin/conker-mupen64plus \
            --noosd --nospeedlimit --debug --emumode 1 \
            --gfx dummy --audio dummy --input dummy --rsp mupen64plus-rsp-hle \
            "$@" roms/baserom.us.z64
        ;;
    game-asm)
        parse_profile_only "usage: ./conker game-asm [--profile us]" "$@"
        python3 "$state_tool" setup-check --profile "$selected_profile"
        run_in_container make game-asm GAME_REFERENCE_PROFILE="$selected_profile"
        ;;
    game-index)
        [[ $# -eq 0 ]] || die "usage: ./conker game-index"
        python3 "$state_tool" setup-check --all
        run_in_container make game-asm GAME_REFERENCE_PROFILE=us >&2
        python3 "$state_tool" game-index
        ;;
    register-game)
        [[ $# -eq 6 ]] || die "usage: ./conker register-game --id <id> --us <symbol> --source <path>"
        python3 "$state_tool" setup-check --all
        run_in_container make game-asm GAME_REFERENCE_PROFILE=us >&2
        python3 "$state_tool" register-game "$@"
        ;;
    register-main)
        [[ $# -eq 6 ]] || die "usage: ./conker register-main --id <id> --us <symbol> --source <path>"
        python3 "$state_tool" setup-check --profile us
        if [[ ! -d "$repo_root/reference/us/asm" ]]; then
            run_in_container make prepare-reference PROFILE=us >&2
        fi
        python3 "$state_tool" register-main "$@"
        ;;
    register-source-unit)
        [[ $# -gt 0 ]] || die "usage: ./conker register-source-unit [--overlay main|game] --source <path> (--function <id>...|--register-members) --us-start <offset> --us-end <offset> --evidence-kind <kind> --evidence-reference <reference>"
        python3 "$state_tool" setup-check --profile us
        registration_overlay=game
        previous_argument=""
        for argument in "$@"; do
            if [[ "$previous_argument" == "--overlay" ]]; then
                registration_overlay="$argument"
                break
            fi
            previous_argument="$argument"
        done
        if [[ "$registration_overlay" == "main" && ! -d "$repo_root/reference/us/asm" ]]; then
            run_in_container make prepare-reference PROFILE=us >&2
        elif [[ "$registration_overlay" == "game" && ! -d "$repo_root/reference/game/us/asm" ]]; then
            run_in_container make game-asm GAME_REFERENCE_PROFILE=us >&2
        fi
        python3 "$state_tool" register-source-unit "$@"
        ;;
    withdraw-source-unit)
        [[ $# -eq 2 ]] || die "usage: ./conker withdraw-source-unit --source <path>"
        python3 "$state_tool" withdraw-source-unit "$@"
        ;;
    retire-library-units)
        [[ $# -gt 0 ]] || die "usage: ./conker retire-library-units --evidence-reference <path> [--source <path>...]"
        # The guarded migration validates metadata against the new archive map;
        # ordinary setup-check still expects the old mixed units to map as C.
        python3 "$state_tool" retire-library-units "$@"
        ;;
    game-m2c)
        parse_profile_and_value "usage: ./conker game-m2c [--profile us] <work-item-id>" "$@"
        python3 "$state_tool" setup-check --profile "$selected_profile"
        run_host_mips_to_c "$selected_profile" "$selected_value" --auto-overlay
        ;;
    _prepare-reference)
        parse_profile_only "internal usage: ./conker _prepare-reference [--profile us]" "$@"
        python3 "$state_tool" setup-check --profile "$selected_profile"
        run_in_container make prepare-reference PROFILE="$selected_profile"
        ;;
    game-diff)
        parse_profile_and_value "usage: ./conker game-diff [--profile us] <work-item-id>" "$@"
        python3 "$state_tool" setup-check --profile "$selected_profile"
        run_in_container python3 scripts/diff.py "$selected_profile" "$selected_value" --auto-overlay
        ;;
    game-build)
        parse_game_build_options "usage: ./conker game-build [--profile us] [--refresh]" "$@"
        python3 "$state_tool" setup-check --profile "$selected_profile"
        run_in_container_libultra make --silent game-libs
        game_build_target=game-integrated
        if [[ "$refresh_game_build" == "true" ]]; then
            game_build_target=game-integrated-refresh
        fi
        run_in_container make --silent --jobs 4 "$game_build_target" GAME_PROFILE="$selected_profile"
        ;;
    rzip-extract)
        profile_supplied=false
        for argument in "$@"; do
            if [[ "$argument" == "--profile" || "$argument" == --profile=* ]]; then
                profile_supplied=true
                break
            fi
        done
        if [[ "$profile_supplied" == "false" ]]; then
            set -- --profile us "$@"
        fi
        python3 scripts/rzip_extract.py "$@"
        ;;
    rzip-pack)
        python3 scripts/rzip_pack.py "$@"
        ;;
    font-assets)
        [[ $# -ge 1 ]] || die "usage: ./conker font-assets <extract|pack|verify> [options]"
        python3 scripts/font_assets.py "$@"
        ;;
    mp3-assets)
        [[ $# -ge 1 ]] || die "usage: ./conker mp3-assets <extract|pack|verify|cue-extract|cue-verify> [options]"
        python3 scripts/mp3_assets.py "$@"
        ;;
    audio-assets)
        [[ $# -ge 1 ]] || die "usage: ./conker audio-assets <survey|extract|preview|sample-preview|verify> [options]"
        python3 scripts/audio_assets.py "$@"
        ;;
    texture-assets)
        [[ $# -ge 1 ]] || die "usage: ./conker texture-assets <extract|pack|verify|survey> [options]"
        python3 scripts/texture_assets.py "$@"
        ;;
    model-assets)
        [[ $# -ge 1 ]] || die "usage: ./conker model-assets <survey|extract|preview|verify> [options]"
        python3 scripts/model_assets.py "$@"
        ;;
    hud-assets)
        [[ $# -ge 1 ]] || die "usage: ./conker hud-assets <survey|extract|preview|verify> [options]"
        python3 scripts/hud_assets.py "$@"
        ;;
    asset-correlate)
        python3 scripts/asset_correlate.py "$@"
        ;;
    beta-index)
        [[ $# -eq 0 || ( $# -eq 1 && "$1" == "--refresh" ) ]] || die "usage: ./conker beta-index [--refresh]"
        run_in_container python3 scripts/beta_index.py "$@"
        ;;
    library-audit)
        [[ $# -eq 0 || ( $# -eq 1 && "$1" == "--json" ) ]] || die "usage: ./conker library-audit [--json]"
        python3 scripts/audit_library_boundaries.py "$@"
        ;;
    rareunzip)
        [[ $# -eq 2 ]] || die "usage: ./conker rareunzip <input> <output>"
        run_in_container python3 tools/third_party/rareunzip.py "$@"
        ;;
    libultra)
        libultra_version=L
        if [[ $# -eq 2 && "$1" == "--version" ]]; then
            libultra_version="$2"
        elif [[ $# -ne 0 ]]; then
            die "usage: ./conker libultra [--version I|J|K|L]"
        fi
        case "$libultra_version" in
            I|J|K|L) ;;
            *) die "libultra version must be I, J, K, or L" ;;
        esac
        run_in_container_libultra make libultra ULTRALIB_VERSION="$libultra_version"
        ;;
    rsp)
        [[ $# -eq 0 ]] || die "usage: ./conker rsp"
        python3 "$state_tool" setup-check --profile us
        run_in_container make rsp
        ;;
    libultrare)
        [[ $# -eq 0 ]] || die "usage: ./conker libultrare"
        run_in_container_libultra make libultrare
        ;;
    *)
        die "unknown command '$command'. Run ./conker help."
        ;;
esac
