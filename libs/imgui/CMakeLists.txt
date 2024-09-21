cmake_minimum_required(VERSION 3.25)

include(${CMAKE_BINARY_DIR}/generators/conan_toolchain.cmake)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

set(MAIN_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(MAIN_SOURCE_FILES 
    ${MAIN_SOURCE_DIR}/imgui_demo.cpp
    ${MAIN_SOURCE_DIR}/imgui_draw.cpp
    ${MAIN_SOURCE_DIR}/imgui_impl_glfw.cpp
    ${MAIN_SOURCE_DIR}/imgui_impl_opengl3.cpp
    ${MAIN_SOURCE_DIR}/imgui_tables.cpp
    ${MAIN_SOURCE_DIR}/imgui_widgets.cpp
    ${MAIN_SOURCE_DIR}/imgui.cpp
)

set(HEADER_FILES_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(imgui STATIC ${MAIN_SOURCE_FILES})
target_include_directories(imgui PUBLIC ${HEADER_FILES_DIR})

target_link_libraries(imgui glfw OpenGL::GL)
