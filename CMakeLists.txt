cmake_minimum_required(VERSION 3.30)
project(Praktikum5 C)

set(CMAKE_C_STANDARD 90)
set(-ansi -std=c90 -pedantic -pedantic-errors -Wall -Wextra -Werror -Wconversion)


add_executable(Praktikum5 praktikum5Test.c matrix.c vector.c matrix.h vector.h)
