#!/usr/bin/env bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

cd "$SCRIPT_DIR"

. ./config.sh

cd ..

CLANGD_DIR="./clangd"

if [[ "$BOARD" == avr* ]]; then
    cp "$CLANGD_DIR/avr" "./.clangd"
elif [[ "$BOARD" == esp32* ]]; then
    cp "$CLANGD_DIR/esp32" "./.clangd"
else
    echo "Unknown board ($BOARD)"
    exit
fi


arduino-cli compile --fqbn $BOARD --build-path ./build --only-compilation-database --libraries $LIBRARIES .

ln build/compile_commands.json compile_commands.json
