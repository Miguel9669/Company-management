cmake_minimum_required(VERSION 3.22)
project(Company_management C)

set(CMAKE_C_STANDARD 99)

add_executable(Company_management main.c
        Libs/Geral.c
        Libs/Geral.h
        Libs/Admin.c
        Libs/Admin.h
        Libs/user.c
        Libs/user.h
        Libs/structs.h
        Libs/constVariables.h
        Libs/Menus.c
        Libs/Menus.h
)
