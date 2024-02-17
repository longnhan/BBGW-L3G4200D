cmake_minimum_required(VERSION 3.5)
project(l3g4_prj VERSION 1.0)

# Set compiler flags
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -g -Wall -Werror")

# Add preprocessor definitions
add_definitions(-DDEBUG)

# Set toolchain
set(CMAKE_C_COMPILER ${CMAKE_SOURCE_DIR}/toolchain/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc)

# Add your source files
set(SOURCES
    src/main.c
    src/main.h
    user_driver/l3g4.c
    user_driver/l3g4.h
    user_driver/i2c_driver.c
    user_driver/i2c_driver.h
)

# Include directories
include_directories(
    src
    user_driver
    user_driver/linux
    user_driver/linux/mmc
    user_driver/linux/genwqe
    user_driver/linux/android
    user_driver/linux/hdlc
    user_driver/linux/hsi
    user_driver/linux/spi
    user_driver/linux/netfilter
    user_driver/linux/netfilter_arp
    user_driver/linux/sunrpc
    user_driver/linux/surface_aggregator
    user_driver/linux/netfilter_bridge
    user_driver/linux/netfilter_ipv4
    user_driver/linux/netfilter_ipv6
    user_driver/linux/tc_act
    user_driver/linux/tc_ematch
    user_driver/linux/nfsd
    user_driver/linux/byteorder
    user_driver/linux/caif
    user_driver/linux/iio
    user_driver/linux/can
    user_driver/linux/usb
    user_driver/linux/cifs
    user_driver/linux/isdn
    user_driver/linux/raid
    user_driver/linux/dvb
    user_driver/linux/sched
    # user_driver/linux/wimax
    # toolchain/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf/lib/gcc/arm-linux-gnueabihf/6.5.0/include
)

# Include header in user_driver/linux/
file(GLOB LINUX_HEADERS
    "user_driver/linux/*.h"
    "user_driver/linux/mmc/*.h"
    "user_driver/linux/genwqe/*.h"
    "user_driver/linux/android/*.h"
    "user_driver/linux/hdlc/*.h"
    "user_driver/linux/hsi/*.h"
    "user_driver/linux/spi/*.h"
    "user_driver/linux/netfilter/*.h"
    "user_driver/linux/netfilter_arp/*.h"
    "user_driver/linux/sunrpc/*.h"
    "user_driver/linux/surface_aggregator/*.h"
    "user_driver/linux/netfilter_bridge/*.h"
    "user_driver/linux/netfilter_ipv4/*.h"
    "user_driver/linux/netfilter_ipv6/*.h"
    "user_driver/linux/tc_act/*.h"
    "user_driver/linux/tc_ematch/*.h"
    "user_driver/linux/nfsd/*.h"
    "user_driver/linux/byteorder/*.h"
    "user_driver/linux/caif/*.h"
    "user_driver/linux/iio/*.h"
    "user_driver/linux/can/*.h"
    "user_driver/linux/usb/*.h"
    "user_driver/linux/cifs/*.h"
    "user_driver/linux/isdn/*.h"
    "user_driver/linux/raid/*.h"
    "user_driver/linux/dvb/*.h"
    "user_driver/linux/sched/*.h"
    "user_driver/linux/wimax/*.h"
)

# Create the executable
add_executable(l3g4_prj ${SOURCES} ${LINUX_HEADERS})

# Generate .map file
set_target_properties(l3g4_prj PROPERTIES LINK_FLAGS "-Wl,-Map=l3g4_prj.map")