cmake_minimum_required(VERSION 3.10)

project(magazyn)

include_directories("${PROJECT_SOURCE_DIR}/include")
add_executable(magazyn src/source.c src/print.c src/print_pdf.c)
