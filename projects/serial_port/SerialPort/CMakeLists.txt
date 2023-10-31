cmake_minimum_required(VERSION 3.14)

project(SerialPort LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS SerialPort)

add_executable(SerialPort
  main.cpp
  drivers/serial.cpp
  drivers/serial.h
)

target_link_libraries(SerialPort Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(SerialPort Qt6::SerialPort)

include(GNUInstallDirs)
install(TARGETS SerialPort
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

