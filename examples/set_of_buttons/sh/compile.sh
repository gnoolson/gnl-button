#!/bin/bash

. ./config.sh

cd ..

arduino-cli compile --fqbn $BOARD  --libraries $LIBRARIES .
