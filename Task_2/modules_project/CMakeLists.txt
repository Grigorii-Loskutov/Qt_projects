cmake_minimum_required(VERSION 3.14)

project(modules_project LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Network Sql)

add_executable(modules_project
  main.cpp
)
target_link_libraries(modules_project PRIVATE Qt6::Core Qt6::Network Qt6::Sql)

install(TARGETS modules_project
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
