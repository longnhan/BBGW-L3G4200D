echo ::::----------------------------::::
echo ::::Build project without symbol::::
echo ::::----------------------------::::

cd ~/BB_Green/bt_usr/l3g4_prj/build/
#clean existing files
rm -r *
#create nesscesary files
cmake ..
#perform make
cmake --build .

echo ::::----------------------------::::
echo ::::           Finish           ::::
echo ::::----------------------------::::
