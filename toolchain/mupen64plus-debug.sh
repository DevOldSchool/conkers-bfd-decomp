#!/usr/bin/env bash
# SPDX-License-Identifier: MIT
set -euo pipefail

mupen_state_dir="/tmp/conker-mupen64plus-${UID:-0}"
mupen_config_dir="$mupen_state_dir/config"
export HOME="$mupen_state_dir"
export XDG_CONFIG_HOME="$mupen_config_dir"
export XDG_DATA_HOME="$mupen_state_dir/data"
mkdir -p "$mupen_config_dir" "$XDG_DATA_HOME"

exec /opt/mupen64plus/bin/mupen64plus \
    --corelib /opt/mupen64plus/lib/libmupen64plus.so.2 \
    --configdir "$mupen_config_dir" \
    --datadir /opt/mupen64plus/share/mupen64plus \
    --plugindir /opt/mupen64plus/lib/mupen64plus \
    "$@"
