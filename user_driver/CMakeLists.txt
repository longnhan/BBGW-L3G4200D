# user_driver/CMakeLists.txt

# Add the source files in this directory
set(USER_DRIVER_FILES
    l3g4.c
    l3g4.h
    i2c_driver.c
    i2c_driver.h
)

# Create a library from these files
add_library(user_driver_lib ${USER_DRIVER_FILES})

# Specify include directories for this target
target_include_directories(user_driver_lib PUBLIC ${CMAKE_SOURCE_DIR}/user_driver)
