cmake_minimum_required(VERSION 3.10)

project(magazyn)

include_directories("${PROJECT_SOURCE_DIR}/include")
add_executable(magazyn src/source.c src/print.c src/print_pdf.c)
configure_file(${CMAKE_SOURCE_DIR}/src/makepdf.sh ${CMAKE_BINARY_DIR}/makepdf.sh COPYONLY)

