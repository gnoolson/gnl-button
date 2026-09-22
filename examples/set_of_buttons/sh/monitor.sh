#!/usr/bin/env bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

cd "$SCRIPT_DIR"

. ./config.sh

arduino-cli monitor -p $PORT --config baudrate=9600
