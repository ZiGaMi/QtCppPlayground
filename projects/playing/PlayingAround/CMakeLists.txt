cmake_minimum_required(VERSION 3.5)

project(PlayingAround LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(PlayingAround main.cpp)

include(GNUInstallDirs)
install(TARGETS PlayingAround
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
