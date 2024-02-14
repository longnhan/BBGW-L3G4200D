echo ::::----------------------------::::
echo :::: Build project with symbol  ::::
echo ::::----------------------------::::

cd ~/BB_Green/bt_usr/l3g4_prj/build/
#clean existing files
cmake --build . --target clean
#create nesscesary files
cmake ..
#set build type
BUILD_TYPE="debug"
#perform make
cmake --build .

echo ::::----------------------------::::
echo ::::           Finish           ::::
echo ::::----------------------------::::