#!/bin/bash
set -x

program="$1"
echo $program

SERIAL_PORT=/dev/ttyACM0
FAKE_USB=/media/mohan/RPI-RP2

printf "\0" > $SERIAL_PORT
echo "waiting for $SERIAL_PORT"
while true
do
  sleep 2
  # sudo visudo
  # %sudo	ALL=(ALL:ALL) NOPASSWD: ALL 
  sudo blkid|grep RPI-RP2
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

echo minicom time...
sleep 1
#ctrl a z x to exit
# crtl a k to exit
screen /dev/ttyACM0 115200