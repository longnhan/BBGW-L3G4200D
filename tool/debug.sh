#!/bin/bash
echo ::::----------------------------::::
echo :::: Build project with symbol  ::::
echo ::::----------------------------::::

echo "Time build: $(date '+%Y-%m-%d %H:%M')"
echo "User: $USER"

mkdir -p ~/projects/BBGW-L3G4200D/build/ #change base on path in your project
cd ~/projects/BBGW-L3G4200D/build/ #change base on path in your project
#clean existing files
rm -r *

#set env
export CC=~/projects/BBGW-L3G4200D/toolchain/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc
export CXX=~/projects/BBGW-L3G4200D/toolchain/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++

#set build type
cmake -DCMAKE_BUILD_TYPE=Debug ..
make

echo ::::----------------------------::::
echo ::::           Finish           ::::
echo ::::----------------------------::::