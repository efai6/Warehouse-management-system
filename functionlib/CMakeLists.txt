cmake_minimum_required(VERSION 3.10)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(libpower update.c Object_code_check.c)
