#!/bin/bash

# Get the current working directory
CRRNT_DIR=$PWD
# Remove the last directory component
PRJ_PATH="${CRRNT_DIR%/*}"
echo "$PRJ_PATH"

echo "1: send build/  |  2: get *csv"
echo "Insert number here: "
read MY_OPTION

case $MY_OPTION in
  1)
    echo ::::----------------------------::::
    echo ::::Copy execution file to BBGW ::::
    echo ::::----------------------------::::
    echo -e "\n"
    cd ..
    scp -r $PRJ_PATH/build/ debian@192.168.7.2:~/l3g4_prj
    ;;
  2)
    echo ::::----------------------------::::
    echo ::::---Get csv file from BBGW---::::
    echo ::::----------------------------::::
    echo -e "\n"
    scp debian@192.168.7.2:~/l3g4_prj/data_output.csv $PRJ_PATH/tool
    ;;
  *)
    # Invalid option
    echo "Not a valid option. Please choose 1 or 2"
    ;;
esac

echo ::::----------------------------::::
echo ::::-----------Finish-----------::::
echo ::::----------------------------::::
