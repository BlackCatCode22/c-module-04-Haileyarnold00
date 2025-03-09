cmake_minimum_required(VERSION 3.10)
project(ZooManagement)

set(CMAKE_CXX_STANDARD 14)

add_executable(ZooManagement 
    main.cpp
    Animal.cpp
    Hyena.cpp
    Lion.cpp
    Tiger.cpp
    Bear.cpp
)
