cmake_minimum_required(VERSION 3.20)
project(poo)

set(CMAKE_CXX_STANDARD 14)

add_executable(poo main.cpp classes/Carte.cpp classes/Carte.h classes/csvFile.cpp classes/csvFile.h classes/menu.cpp classes/menu.h classes/menuItem.cpp classes/menuItem.h classes/bibliotecaManager.cpp classes/bibliotecaManager.h)
