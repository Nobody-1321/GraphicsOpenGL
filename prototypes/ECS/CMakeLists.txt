cmake_minimum_required(VERSION 3.25)

include(${CMAKE_BINARY_DIR}/generators/conan_toolchain.cmake)

project(graphics VERSION 2.0.1 LANGUAGES CXX)


add_subdirectory(../../libs/glad ${CMAKE_BINARY_DIR}/glad)
add_subdirectory(../../libs/utils ${CMAKE_BINARY_DIR}/utils)
add_subdirectory(../../libs/soild2 ${CMAKE_BINARY_DIR}/soild2)

#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/utils)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/soild2)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui)

#include_directories(
#    ${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/include
#    ${CMAKE_CURRENT_SOURCE_DIR}/libs/utils/include
#    ${CMAKE_CURRENT_SOURCE_DIR}/libs/soild2/SOIL2
#)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)


add_executable(${PROJECT_NAME} main.cpp componentCreator.cpp)

#set (RUNTIME_OUTPUT_DIRECTORY_SHADERS ${CMAKE_CURRENT_BINARY_DIR}/shaders)
#set (RUNTIME_OUTPUT_DIRECTORY_TEXTURES ${CMAKE_CURRENT_BINARY_DIR}/textures)
#set (RUNTIME_OUTPUT_DIRECTORY_MODEL ${CMAKE_CURRENT_BINARY_DIR}/model)


#file(MAKE_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY_SHADERS})
#file(MAKE_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY_TEXTURES})
#file(MAKE_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY_MODEL})


#file(GLOB GLSL_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/*.glsl")
#file(GLOB TEXTURE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/textures/*.*")
#file(GLOB MODEL_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/model/*.*")

#foreach(GLSL_FILE ${GLSL_FILES})
#    file(COPY ${GLSL_FILE} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shaders)
#endforeach()

#foreach(GLSL_TEX ${TEXTURE_FILES})
#    file(COPY ${GLSL_TEX} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/textures)
#endforeach()

#foreach(GLSL_MODEL ${MODEL_FILES})
#    file(COPY ${GLSL_MODEL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/model)
#endforeach()

target_link_libraries(${PROJECT_NAME} glfw glad OpenGL::GL glm::glm utilities soil3 )
#target_link_libraries(${PROJECT_NAME} glfw glad OpenGL::GL glm::glm utilities)
