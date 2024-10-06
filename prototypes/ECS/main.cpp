#define GLFW_INCLUDE_NONE
#include <vector>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <MeshFactory.hpp>
#include "componentCreator.hpp"
#include <modelImporter.hpp>
#include <cmath>
#include "componentStruct.hpp"

using namespace std;

#define numVAOs 1
#define numVBOs 2


GLuint vao[numVAOs];
GLuint vbo[numVBOs];


float aspectRatio;


MeshFactory factory;

//componentStruct component;


float lastFrame;
float deltaTime;

void calculateDeltaTime();
void init();


int main()
{

    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    GLFWwindow *window = glfwCreateWindow(mode->width, mode->height, "ECS", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    aspectRatio = mode->width / mode->height;
    glfwMaximizeWindow(window);

    glfwMakeContextCurrent(window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "failed to initialize GLAD " << std::endl;
        return -1;
    }


    glViewport(0, 0, mode->width, mode->height);

    while (!glfwWindowShouldClose(window))
    {
        calculateDeltaTime();
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void init()
{

    
#ifdef __WIN32__
    //cubeShader_CPT.vertexShaderPath = ".\\shaders\\vertex_shader10.glsl";
    //cubeShader_CPT.fragmentShaderPath = ".\\shaders\\fragment_shader10.glsl";
    Shader cube_cpt =  ComponentCreator::createShaderComponent( ".\\shaders\\vertex_shader10.glsl", ".\\shaders\\fragment_shader10.glsl");    

#else
    //cubeShader_CPT.vertexShaderPath = "./shaders/vertex_shader10.glsl";
    //cubeShader_CPT.fragmentShaderPath = "./shaders/fragment_shader10.glsl";
#endif

    //setupMesh();
}

void calculateDeltaTime() {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

