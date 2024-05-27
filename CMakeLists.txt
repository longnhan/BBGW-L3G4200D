cmake_minimum_required(VERSION 3.5)
project(l3g4_prj VERSION 1.0)

# Add preprocessor definitions
add_definitions(-DDEBUG)

# Set toolchain
set(CMAKE_C_COMPILER ${CMAKE_SOURCE_DIR}/toolchain/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/user_driver
)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(user_driver)

# Create the executable for 2 processes
add_executable(l3g4_prj_main src/ps_main.c)
add_executable(l3g4_prj_logfile src/ps_logfile.c)


# Link libraries for 2 processes
target_link_libraries(l3g4_prj_main pthread rt)
target_link_libraries(l3g4_prj_main src_lib user_driver_lib)

target_link_libraries(l3g4_prj_logfile pthread rt)
target_link_libraries(l3g4_prj_logfile src_lib user_driver_lib)

# Generate .map file for 2 processes
set_target_properties(l3g4_prj_main PROPERTIES LINK_FLAGS "-Wl,-Map=l3g4_prj_main.map")
set_target_properties(l3g4_prj_logfile PROPERTIES LINK_FLAGS "-Wl,-Map=l3g4_prj_logfile.map")