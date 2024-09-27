#define GLFW_INCLUDE_NONE
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <MeshFactory.hpp>
#include <VertexMesh.hpp>
#include <Mesh_VV.hpp>
#include <Utils.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

MeshFactory factory;
GLuint renderingProgram;

void init(){

    #ifdef __WIN32__
        renderingProgram = Utils::createShaderProgram(
            ".\\shaders\\vertex_shader1.glsl",
            ".\\shaders\\fragment_shader1.glsl");
        
        std::cout << "Windows" << std::endl;
        //texture = Utils::loadTexture(".\\textures\\torus.jpg");
    #else
        renderingProgram = Utils::createShaderProgram(
            "./shaders/vertex_shader2.glsl",
            "./shaders/fragment_shader2.glsl");
        
        //texture = Utils::loadTexture("./textures/sand.png");        
        std::cout << "Linux" << std::endl;
    #endif
 
    std::vector<float> vertexPositions = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    
    factory.registerMeshType("simple", [vertexPositions]() { 
        //return std::make_unique<VertexMesh>(vertexPositions); 
        return std::make_unique<Mesh_VV>(vertexPositions); 
    });
    
 
}

// Function to updae the display
void display(GLFWwindow* window){

    glClear(GL_COLOR_BUFFER_BIT);       
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    
    auto mesh = factory.createMesh("simple");
    mesh->setupMesh();

    glUseProgram(renderingProgram);

    mesh->render();
}


int main() {
    
   
    if (!glfwInit()) {exit(EXIT_FAILURE);}


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);                  
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                  
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            

    
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, " Mesh ", nullptr, nullptr);


    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwMaximizeWindow(window);


    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "failed to initialize GLAD " << std::endl;
        return -1;
    }
    
    init();

    while (!glfwWindowShouldClose(window)) {

        display(window);
        processInput(window);          
        glfwPollEvents();
        glfwSwapBuffers(window); 
    }

    glfwTerminate();
   
    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
