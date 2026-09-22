#!/usr/bin/env bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

cd "$SCRIPT_DIR"

. ./config.sh

cd ..

BOARD_OPTIONS_ARG=""

if [ -n "$BOARD_OPTIONS" ]; then
    BOARD_OPTIONS_ARG="--board-options $BOARD_OPTIONS"
fi

arduino-cli upload -p $PORT --fqbn $BOARD $BOARD_OPTIONS_ARG .
