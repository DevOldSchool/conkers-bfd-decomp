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
  next [--one [--details]]       List functions ready to claim; optionally show one with local context.
  next --ready                   Select one function, prewarm Docker, and include its m2c starter.
  finish [--profile us] <work-item-id>
                                 Record CURRENT (0), then check progress and whitespace.
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
  m2c [--profile us] <work-item-id>
                                 Generate a C starter; auto-detects main versus game overlay.
  game-asm [--profile us]        Export decompressed game-code reference assembly.
  game-index                     List reviewable US game-function proposals.
  register-game --id <id> --us <symbol> --source <path>
                                 Register one US game-overlay function for matching work.
  register-source-unit --source <path> (--function <id>...|--register-members) --us-start <offset>
      --us-end <offset> --evidence-kind <kind> --evidence-reference <reference>
                                 Register a separately reviewed game source/object boundary.
  game-m2c [--profile us] <work-item-id>
                                 Compatibility alias for the auto-detecting m2c command.
  game-diff [--profile us] <work-item-id>
                                 Compatibility alias for the auto-detecting diff command.
  game-build [--profile us] [--refresh]
                                 Incrementally build and byte-verify game units; --refresh rebuilds the cache.
  rzip-extract [--profile us|debug|ects] [--rom <path>] [--output <dir>]
                                 Separate game code/data and indexed asset files.
  beta-index [--refresh]         Correlate beta functions/source paths with retail US.
  rareunzip <input> <output>     Decompress one RZIP chunk (paths inside this repository).
  libultra                       Build the pinned 2.0L libultra ROM archive.

All build commands run inside the pinned linux/amd64 Docker environment.
US is the default profile; pass --profile explicitly only to override it.
EOF
}

require_docker() {
    command -v docker >/dev/null 2>&1 || die "Docker is required. Install Docker Desktop or Docker Engine, then rerun ./conker doctor."
}

image_is_healthy() {
    docker run --rm "${container_run_args[@]}" \
        --mount "type=bind,source=$repo_root/tests/fixtures/ido_smoke.c,target=/tmp/ido-smoke.c,readonly" \
        "$image_name" sh -c \
        'test -x /opt/ido/cc && test -f /opt/tools/asm-processor/build.py && command -v wget >/dev/null && command -v less >/dev/null && /opt/ido/cc -c -32 -G 0 -non_shared -O2 -mips2 -o /tmp/ido-smoke.o /tmp/ido-smoke.c && test -s /tmp/ido-smoke.o' \
        >/dev/null 2>&1
}

watch_image_is_compatible() {
    [[ "$(docker image inspect --format '{{ index .Config.Labels "org.devoldschool.conker.diff-watch" }}' "$image_name" 2>/dev/null)" == "1" ]]
}

ensure_image() {
    require_docker
    if docker image inspect "$image_name" >/dev/null 2>&1; then
        return
    fi
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
    python3 "$state_tool" setup-check --profile "$selected_profile"
    run_in_container python3 scripts/diff.py "$selected_profile" "$selected_value" --auto-overlay --require-match
    python3 "$state_tool" mark-matched --profile "$selected_profile" "$selected_value"
}

prepare_next_work() {
    local identifier
    identifier="$(python3 "$state_tool" next --one --id-only)"
    python3 "$state_tool" next --one --details
    python3 "$state_tool" setup-check --profile us
    ensure_warm_container
    printf 'toolchain: warm (%s)\n' "$warm_container_name"
    printf 'c-starter:\n'
    run_host_mips_to_c us "$identifier" --auto-overlay
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
            printf 'Toolchain image failed its IDO smoke test; rebuilding it locally...\n'
            docker build --platform linux/amd64 --tag "$local_image_name" "$repo_root"
            image_name="$local_image_name"
            image_is_healthy || die "toolchain image failed the IDO compilation smoke test"
        fi
        docker version --format 'Docker client: {{.Client.Version}}'
        printf 'Required container platform: linux/amd64\n'
        printf 'IDO compilation smoke test: OK\n'
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
                if [[ "$selected_value" == "--all-reviewed" ]]; then
                    run_in_container_integrating python3 scripts/integrate.py --profile "$selected_profile" --all-reviewed
                else
                    run_in_container_integrating python3 scripts/integrate.py --profile "$selected_profile" "$selected_value"
                fi
                ;;
            *) die "usage: ./conker progress [render|check] | ./conker progress match [--profile us] <work-item-id> | ./conker progress integrate [--profile us] <work-item-id>|--all-reviewed" ;;
        esac
        ;;
    next)
        if [[ "${1:-}" == "--ready" ]]; then
            [[ $# -eq 1 ]] || die "usage: ./conker next --ready"
            prepare_next_work
        else
            python3 "$state_tool" next "$@"
        fi
        ;;
    finish)
        parse_profile_and_value "usage: ./conker finish [--profile us] <work-item-id>" "$@"
        verify_and_record_match
        python3 "$state_tool" progress --check
        git -C "$repo_root" -c core.whitespace=cr-at-eol diff --check
        printf '%s: per-function gate passed (match, progress, whitespace).\n' "$selected_value"
        ;;
    stop)
        require_docker
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
            run_in_container make "$command" PROFILE=us
        else
            parse_profile_only "usage: ./conker $command [--profile us|--all]" "$@"
            python3 "$state_tool" setup-check --profile "$selected_profile"
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
    register-source-unit)
        [[ $# -gt 0 ]] || die "usage: ./conker register-source-unit --source <path> (--function <id>...|--register-members) --us-start <offset> --us-end <offset> --evidence-kind <kind> --evidence-reference <reference>"
        python3 "$state_tool" setup-check --profile us
        if [[ ! -d "$repo_root/reference/game/us/asm" ]]; then
            run_in_container make game-asm GAME_REFERENCE_PROFILE=us >&2
        fi
        python3 "$state_tool" register-source-unit "$@"
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
    beta-index)
        [[ $# -eq 0 || ( $# -eq 1 && "$1" == "--refresh" ) ]] || die "usage: ./conker beta-index [--refresh]"
        run_in_container python3 scripts/beta_index.py "$@"
        ;;
    rareunzip)
        [[ $# -eq 2 ]] || die "usage: ./conker rareunzip <input> <output>"
        run_in_container python3 tools/third_party/rareunzip.py "$@"
        ;;
    libultra)
        [[ $# -eq 0 ]] || die "usage: ./conker libultra"
        run_in_container_libultra make libultra
        ;;
    *)
        die "unknown command '$command'. Run ./conker help."
        ;;
esac
