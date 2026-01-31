cmake_minimum_required(VERSION 3.5)

project(TestExternalAssaultCube LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(TestExternalAssaultCube main.cpp

    Offsets.h
    memory.h memory.cpp
    math.h math.cpp
    render.h render.cpp
    processmanager.h processmanager.cpp


)

include(GNUInstallDirs)
install(TARGETS TestExternalAssaultCube
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
