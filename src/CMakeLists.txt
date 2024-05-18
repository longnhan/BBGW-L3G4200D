# Add the source files in this directory
set(SRC_FILES
    ps_main.c	# first process
    ps_logfile.c  # second process
    main.h
)

# Create a library from these files
add_library(src_lib ${SRC_FILES})

# Specify include directories for this target
target_include_directories(src_lib PUBLIC ${CMAKE_SOURCE_DIR}/src)