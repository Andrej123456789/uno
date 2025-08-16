cmake_minimum_required(VERSION 3.21)

set(CMAKE_BUILD_TYPE Release)

project(uno_pp)

IF (WIN32)
    set(CMAKE_C_FLAGS "")
ELSE()
    set(CMAKE_C_FLAGS "")
ENDIF()

file(GLOB SRC CONFIGURE_DEPENDS "*.c")

IF(WIN32)
    list(APPEND SRC "server/server_windows.c")
ELSE()
    list(APPEND SRC "server/server_posix.c")
ENDIF()

IF(WIN32)
    set(VCPKG_ROOT "" CACHE PATH "Root path to vcpkg")
    IF(VCPKG_ROOT)
        set(json-c_DIR "${VCPKG_ROOT}/installed/x64-windows-static/share/json-c")
    ENDIF()

    find_package(json-c CONFIG REQUIRED)

    add_executable(${PROJECT_NAME} ${SRC})
    target_link_libraries(${PROJECT_NAME} PRIVATE json-c::json-c)
ELSE()
    add_executable(${PROJECT_NAME} ${SRC})
    target_link_libraries(${PROJECT_NAME} PRIVATE json-c)
ENDIF()
