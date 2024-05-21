#!/bin/sh

echo "How do you want to access BBGW?"
echo "1: minicom  |  2: via wifi  |  3:SSH  |  4: BBGW serial"
echo "Insert number here: "

read MY_OPTION

USER_NAME="debian"
BBGW_SSH="debian@192.168.7.2"
BBGW_WIFI="debian@192.168.1.104"

case $MY_OPTION in
  1)
    # Minicom
    echo "Minicom"
    sudo minicom -D /dev/ttyACM0 
    sleep 2
    echo -e "\n"
    echo -e "$USER_NAME" ; sleep 5
    echo -e "\n"
    ;;
  2)
    # WiFi
    echo "WiFi"
    ssh $BBGW_WIFI; sleep 5
    echo -e "\n"
    sleep 1
    echo -e "\n"
    ;;
  3)
    # SSH
    echo "SSH"
    ssh $BBGW_SSH; sleep 3
    echo -e "\n"
    sleep 1
    echo -e "\n"
    ;;
  4)
    # ttyUSB0
    echo "ttyUSB0"
    sudo minicom -D /dev/ttyUSB0
    ;;
  *)
    # Invalid option
    echo "Not a valid option. Please choose 1, 2, or 3."
    ;;
esac
