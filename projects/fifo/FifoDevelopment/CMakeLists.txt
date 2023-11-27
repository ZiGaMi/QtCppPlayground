cmake_minimum_required(VERSION 3.5)

project(FifoDevelopment LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Settings optimizations
set(CMAKE_CXX_FLAGS_DEBUG "-Og")
set(CMAKE_CXX_FLAGS_RELEASE "-O0")

add_executable(FifoDevelopment
    main.cpp
    ring_buffer/ring_buffer.h
)

include(GNUInstallDirs)
install(TARGETS FifoDevelopment
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
