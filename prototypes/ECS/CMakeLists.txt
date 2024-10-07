cmake_minimum_required(VERSION 3.25)

include(${CMAKE_BINARY_DIR}/generators/conan_toolchain.cmake)

project(graphics VERSION 2.0.1 LANGUAGES CXX)
# c++ standard 20
set(CMAKE_CXX_STANDARD 20)


add_subdirectory(../../libs/glad ${CMAKE_BINARY_DIR}/glad)
add_subdirectory(../../libs/utils ${CMAKE_BINARY_DIR}/utils)
add_subdirectory(../../libs/soild2 ${CMAKE_BINARY_DIR}/soild2)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)
#glfw status

message(STATUS "glfw3 found: ${glfw3_FOUND}")

add_executable(${PROJECT_NAME} main.cpp componentCreator.cpp )

target_compile_options(${PROJECT_NAME} PRIVATE -g)  # Opción para símbolos de depuración (-g en GCC/Clang)

set (RUNTIME_OUTPUT_DIRECTORY_SHADERS ${CMAKE_CURRENT_BINARY_DIR}/shaders)

file(MAKE_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY_SHADERS})

file(GLOB GLSL_FILES "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.glsl")

foreach(GLSL_FILE ${GLSL_FILES})
    file(COPY ${GLSL_FILE} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shaders)
endforeach()

target_link_libraries(${PROJECT_NAME} glfw glad OpenGL::GL glm::glm utilities soil3 )

