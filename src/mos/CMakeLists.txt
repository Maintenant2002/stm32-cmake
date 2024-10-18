cmake_minimum_required(VERSION 3.22)

project(mos)
add_library(mos INTERFACE)

target_include_directories(mos INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/arch
    ${CMAKE_CURRENT_SOURCE_DIR}/kernel
    ${CMAKE_CURRENT_SOURCE_DIR}/kernel/data_type
)