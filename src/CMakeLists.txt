cmake_minimum_required(VERSION 3.10)

# set the project name
project(MarsGame VERSION 0.1)

target_include_directories(MarsGame PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

# add the executable
add_executable(MarsGame graphics1.c)