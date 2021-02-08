#!/usr/bin/env bash
set -x

PROJECT=$1

cp $PROJECT/build/${PROJECT}.uf2  /media/$(whoami)/RPI-RP2
