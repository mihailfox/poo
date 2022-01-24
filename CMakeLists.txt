cmake_minimum_required(VERSION 3.20)
project(poo)

set(CMAKE_CXX_STANDARD 14)

add_executable(poo main.cpp classes/book.cpp classes/book.h classes/csvFile.cpp classes/csvFile.h classes/menu.cpp classes/menu.h classes/menuItem.cpp classes/menuItem.h classes/booksManager.cpp classes/booksManager.h classes/domain.cpp classes/domain.h classes/domainsManager.cpp classes/domainsManager.h classes/helper.cpp classes/helper.h)

#file(COPY carti.in DESTINATION ${CMAKE_BINARY_DIR})
#file(COPY domenii.in DESTINATION ${CMAKE_BINARY_DIR})