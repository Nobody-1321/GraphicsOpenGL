#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <vector>
#include <GLFW/glfw3.h>
#include <iostream>
#include <MeshFactory.hpp>
#include "componentCreator.hpp"
#include <modelImporter.hpp>
#include <cmath>
#include "componentStruct.hpp"
#include <filesystem>

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
void setupMesh();

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

    
    init();

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

    std::unique_ptr<Shader> cubeShader_CPT = ComponentCreator::createShaderComponent(".\\shaders\\vertex_shader10.glsl", ".\\shaders\\fragment_shader10.glsl");

#else
    //cubeShader_CPT.vertexShaderPath = "./shaders/vertex_shader10.glsl";
    //cubeShader_CPT.fragmentShaderPath = "./shaders/fragment_shader10.glsl";
    
    std::unique_ptr<Shader> cubeShader_CPT = ComponentCreator::createShaderComponent("./shaders/vertex_shader1.glsl", "./shaders/fragment_shader1.glsl");
    
    std::cout << "Shader created" << std::endl;
    std::cout << "Vertex path: " << cubeShader_CPT->vertexShaderPath << std::endl;
    std::cout << "Fragment path: " << cubeShader_CPT->fragmentShaderPath << std::endl;
    std::cout << "Shader program: " << cubeShader_CPT->shaderProgram << std::endl;

#endif
    
    

    //setupMesh();
}

void setupMesh()
{
    std::vector<float> vertexPositions_floor = {
    // back face
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right    
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right              
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left                
    // front face
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right        
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left        
    // left face
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left       
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
    // right face
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right      
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right          
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
    // bottom face          
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left        
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
    // top face
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right                 
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // bottom-left  
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f  // top-left              
    };


  //  factory.registerMeshType("Mesh_floor", [vertexPositions_floor]() {
   //     return std::make_unique<Mesh_VT>(vertexPositions_floor);
    //}); 

}


void calculateDeltaTime() {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

