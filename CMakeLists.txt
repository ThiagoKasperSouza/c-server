cmake_minimum_required(VERSION 3.10)
project(C_Http C)

# define versao padrao do C
set(CMAKE_C_STANDARD 11)

# Informa cmake onde achar headers
include_directories(src/lib)

# Busca arquivos no src
file(GLOB SOURCES "src/*.c")

# define o nome do exec
add_executable(program ${SOURCES})