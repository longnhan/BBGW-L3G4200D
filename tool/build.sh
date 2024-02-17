echo ::::----------------------------::::
echo ::::Build project without symbol::::
echo ::::----------------------------::::

cd ~/BB_Green/bt_usr/l3g4_prj/build/
#clean existing files
rm -r *
#perform make
cmake -DCMAKE_BUILD_TYPE=Release ..
make

echo ::::----------------------------::::
echo ::::-----------Finish-----------::::
echo ::::----------------------------::::
