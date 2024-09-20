cmake_minimum_required(VERSION 3.25)

include(${CMAKE_BINARY_DIR}/generators/conan_toolchain.cmake)

project(graphics VERSION 2.0.1 LANGUAGES CXX)


set(LIBRARIES_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/glad
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glad)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/utils)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/soild2)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/utils/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/soild2/SOIL2
)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)

#add_executable(${PROJECT_NAME} src/HelloWindow.cpp)
#add_executable(${PROJECT_NAME} src/HelloSquare.cpp)
#add_executable(${PROJECT_NAME} src/HelloTriangle.cpp)
#add_executable(${PROJECT_NAME} src/HelloGlsl.cpp)
#add_executable(${PROJECT_NAME} src/HelloInterpolation.cpp)
#add_executable(${PROJECT_NAME} src/HelloTexture.cpp)
#add_executable(${PROJECT_NAME} src/HelloMixTexture.cpp)
#add_executable(${PROJECT_NAME} src/HelloTrans.cpp)
#add_executable(${PROJECT_NAME} src/HelloCoordinates.cpp)
#add_executable(${PROJECT_NAME} src/HelloDeep.cpp)
#add_executable(${PROJECT_NAME} src/HelloCamera.cpp)
add_executable(${PROJECT_NAME} src/HelloCameraAround.cpp)


set (RUNTIME_OUTPUT_DIRECTORY_SHADERS ${CMAKE_CURRENT_BINARY_DIR}/shaders)
set (RUNTIME_OUTPUT_DIRECTORY_TEXTURES ${CMAKE_CURRENT_BINARY_DIR}/textures)


file(MAKE_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY_SHADERS})
file(MAKE_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY_TEXTURES})


file(GLOB GLSL_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/*.glsl")
file(GLOB TEXTURE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/textures/*.*")


foreach(GLSL_FILE ${GLSL_FILES})
    file(COPY ${GLSL_FILE} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shaders)
endforeach()

foreach(GLSL_TEX ${TEXTURE_FILES})
    file(COPY ${GLSL_TEX} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/textures)
endforeach()

target_link_libraries(${PROJECT_NAME} glfw glad OpenGL::GL glm::glm utilities soil3)