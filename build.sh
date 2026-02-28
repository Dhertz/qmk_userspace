#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
MAIN_FW="$HOME/Documents/qmk_firmware"
MONSGEEK_FW="$SCRIPT_DIR/qmk_firmware"

# Build all standard targets with main firmware
qmk config user.qmk_home="$MAIN_FW" >/dev/null
qmk userspace-compile

# Build monsgeek with wireless fork
qmk config user.qmk_home="$MONSGEEK_FW" >/dev/null
qmk compile -kb monsgeek/m1_v5/m1_v5_uk -km dhertz

# Restore default
qmk config user.qmk_home="$MAIN_FW" >/dev/null
