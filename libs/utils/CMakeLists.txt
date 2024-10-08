cmake_minimum_required(VERSION 3.25)

include(${CMAKE_BINARY_DIR}/generators/conan_toolchain.cmake)

project(mi_proyecto)  

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)

set(MAIN_SOURCE_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Sphere.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Torus.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/modelImporter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/VertexMesh.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Mesh_VV.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Mesh_VT.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MeshFactory.cpp
)

add_library(utilities STATIC ${MAIN_SOURCE_FILES})

# Directorios de inclusión públicos
target_include_directories(utilities PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_precompile_headers(utilities PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/stlHeaders.hpp )

target_link_libraries(utilities PRIVATE
    glad
    glfw
    glm::glm
    OpenGL::GL
    soil3
)