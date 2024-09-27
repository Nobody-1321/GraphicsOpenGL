cmake_minimum_required(VERSION 3.25)

include(${CMAKE_BINARY_DIR}/generators/conan_toolchain.cmake)

project(graphics VERSION 2.0.1 LANGUAGES CXX)


find_package(glfw3 REQUIRED)
#find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} src/Ventana.cpp)

set (RUNTIME_OUTPUT_DIRECTORY_SHADERS ${CMAKE_CURRENT_BINARY_DIR}/shaders)

file(MAKE_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY_SHADERS})


file(GLOB GLSL_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/*.hlsl")

foreach(GLSL_FILE ${GLSL_FILES})
    file(COPY ${GLSL_FILE} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shaders)
endforeach()

target_link_libraries(${PROJECT_NAME} glfw d3d11 dxgi d3dcompiler)
