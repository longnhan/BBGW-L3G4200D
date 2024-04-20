#!/bin/bash

echo "Time build: $(date '+%Y-%m-%d %H:%M')"
echo "User: $USER"

PRJ_PATH=~/projects/BBGW-L3G4200D #change base on path in your project

echo "Choose build option 1: Release  |  2: Debug"
read MY_OPTION
case $MY_OPTION in
1)
    echo "Release option"
    ;;
2)
    echo "Debug option"
    ;;
*)
    # Invalid option
    echo "Not a valid option. Please choose 1 or 2"
    exit 0
    ;;
esac

mkdir -p $PRJ_PATH/build/
cd $PRJ_PATH/build/
#clean existing files
rm -r *

export CC=$PRJ_PATH/toolchain/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc
export CXX=$PRJ_PATH/toolchain/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++

#perform make
if [ $MY_OPTION==1 ]
then
        cmake -DCMAKE_BUILD_TYPE=Release ..
else
        cmake -DCMAKE_BUILD_TYPE=Debug ..
fi
make

echo ::::----------------------------::::
echo ::::-----------Finish-----------::::
echo ::::----------------------------::::
