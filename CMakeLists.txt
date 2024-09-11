cmake_minimum_required(VERSION 3.25)

include(${CMAKE_BINARY_DIR}/generators/conan_toolchain.cmake)

project(graphics VERSION 2.0.1 LANGUAGES CXX)

set(LIBRARIES_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/glad
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glad)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)

#add_executable(${PROJECT_NAME} src/HelloWindow.cpp)
add_executable(${PROJECT_NAME} src/HelloTriangle.cpp)

target_link_libraries(${PROJECT_NAME} glfw glad OpenGL::GL glm::glm)