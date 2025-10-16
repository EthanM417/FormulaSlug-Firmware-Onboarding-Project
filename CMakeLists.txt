cmake_minimum_required(VERSION 4.1.1)
cmake_policy(VERSION 4.1.1)

set(MBED_APP_JSON_PATH mbed_app.json5)

include(mbed-os/tools/cmake/mbed_toolchain_setup.cmake)
project(firmwareOnboard
    LANGUAGES C CXX ASM) 
include(mbed_project_setup)

add_subdirectory(mbed-os)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} mbed-os) # Can also link to mbed-baremetal here
mbed_set_post_build(${PROJECT_NAME})
