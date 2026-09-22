#!/usr/bin/env bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

cd "$SCRIPT_DIR"

. ./config.sh

cd ..

CLEAN_FLAG=""
if [ "$1" = "-c" ]; then
    CLEAN_FLAG="--clean"
fi

VERBOSE_FLAG=""
if [ "$1" = "-v" ]; then
    VERBOSE_FLAG="--verbose"
fi

arduino-cli compile --fqbn "$BOARD" --libraries "$LIBRARIES" --output-dir ./build $VERBOSE_FLAG --warnings all $CLEAN_FLAG .
