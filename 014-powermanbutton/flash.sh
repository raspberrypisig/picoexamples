#!/bin/bash
set -x

SERIAL_PORT=/dev/ttyACM0
FAKE_USB=/media/mohan/RPI-RP2

printf "\0" > $SERIAL_PORT
echo "waiting for $SERIAL_PORT"
while [ ! -d $FAKE_USB ]; do sleep 0.1; done
sleep 0.5
echo copying
cp $1 $FAKE_USB
echo done