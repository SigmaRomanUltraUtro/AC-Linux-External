cmake_minimum_required(VERSION 3.5)

project(TestExternalAssaultCube LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(TestExternalAssaultCube main.cpp

    Offsets.h
    memory/memory.h
    sdk/math.h
    sdk/math.cpp
    render/render.h
    render/render.cpp
    features//processmanager.h
    features/processmanager.cpp
    sdk/localPlayer.h
    memory/memory.cpp
    sdk/LocalPlayer.cpp
    sdk/weapon.h sdk/weapon.cpp
)

include(GNUInstallDirs)
install(TARGETS TestExternalAssaultCube
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
