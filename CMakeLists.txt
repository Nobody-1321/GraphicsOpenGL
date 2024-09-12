cmake_minimum_required(VERSION 3.25)

include(${CMAKE_BINARY_DIR}/generators/conan_toolchain.cmake)

project(graphics VERSION 2.0.1 LANGUAGES CXX)

# Configurar compilador para salida de errores en color
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")
endif()

set(LIBRARIES_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/glad
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glad)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/utils)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/soild2)


find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)

#add_executable(${PROJECT_NAME} src/HelloWindow.cpp)
#add_executable(${PROJECT_NAME} src/HelloSquare.cpp)
#add_executable(${PROJECT_NAME} src/HelloTriangle.cpp)
#add_executable(${PROJECT_NAME} src/HelloGlsl.cpp)
add_executable(${PROJECT_NAME} src/HelloInterpolation.cpp)

set (RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/shaders)

file(MAKE_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY})

file(GLOB GLSL_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/*.glsl")

foreach(GLSL_FILE ${GLSL_FILES})
    file(COPY ${GLSL_FILE} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shaders)
endforeach()

target_link_libraries(${PROJECT_NAME} glfw glad OpenGL::GL glm::glm utilities soil3)