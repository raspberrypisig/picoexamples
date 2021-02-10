#!/bin/bash
set -x


SERIAL_PORT=/dev/ttyACM0
FAKE_USB=/media/mohan/RPI-RP2

printf "\0" > $SERIAL_PORT
echo "waiting for $SERIAL_PORT"
while true
do
  sleep 5
  blkid|grep RPI-RP2|cut -f1 -d':'
  if [ $? -eq 0 ];
    then
    break
  fi
done
pico=$(blkid|grep RPI-RP2|cut -f1 -d':')
echo $pico
#sleep 0.5
udisksctl mount --no-user-interaction -b $pico
echo copying
cp $1 $FAKE_USB
echo done
