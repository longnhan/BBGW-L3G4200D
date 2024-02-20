echo ::::----------------------------::::
echo :::: Build project with symbol  ::::
echo ::::----------------------------::::

echo "Time build: $(date '+%Y-%m-%d %H:%M')"
echo "User: $USER"

cd ~/BB_Green/bt_usr/l3g4_prj/build/
#clean existing files
rm -r *
#set build type
cmake -DCMAKE_BUILD_TYPE=Debug ..
make

echo ::::----------------------------::::
echo ::::           Finish           ::::
echo ::::----------------------------::::