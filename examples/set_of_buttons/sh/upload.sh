#!/bin/bash

. ./config.sh

cd ..

arduino-cli upload -p $PORT --fqbn $BOARD .
