cmake_minimum_required(VERSION 3.10)

# set the project name
project(sysLoad VERSION 1.0)


# add src to the executable
file(GLOB sysLoad_SRC
    "*.h"
    "*.cpp"
    "*.cc"
)

add_executable(sysLoad ${sysLoad_SRC})

#linking libraries
target_link_libraries(sysLoad ${sysLoad_SRC})