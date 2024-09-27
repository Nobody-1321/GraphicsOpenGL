#define GLFW_INCLUDE_NONE
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Mesh.hpp"
#include "MeshFactory.hpp"
#include "MeshSimple.hpp"
#include <Utils.hpp>
#include "MeshTriangle.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

void init(GLFWwindow* window){

}

GLuint renderingProgram;

void init(){

    #ifdef __WIN32__
        //renderingProgram = Utils::createShaderProgram(
          //  "..\\..\\vertex.glsl",
            //"..\\..\\fragment.glsl");
        renderingProgram = Utils::createShaderProgram(
            "..\\..\\vertex2.glsl",
            "..\\..\\fragment2.glsl");
        
        std::cout << "Windows" << std::endl;
        //texture = Utils::loadTexture(".\\textures\\torus.jpg");
    #else
        renderingProgram = Utils::createShaderProgram(
            "./shaders/vertex_shader2.glsl",
            "./shaders/fragment_shader2.glsl");
        
        //texture = Utils::loadTexture("./textures/sand.png");        
        std::cout << "Linux" << std::endl;
    #endif
    
}

// Function to updae the display
void display(GLFWwindow* window){
    glClear(GL_COLOR_BUFFER_BIT);       
    glClearColor(1.0f, 0.3f, 0.3f, 1.0f);
    
    MeshFactory factory;
    factory.registerMeshType("simple", []() { return std::make_unique<SimpleMesh>(); });
    factory.registerMeshType("triangle", []() { return std::make_unique<TriangleMesh>(); });
    //auto mesh = factory.createMesh("simple");
    
    auto mesh = factory.createMesh("triangle");
  //  auto mesh2 = factory.createMesh("simple");
//    mesh2->setupMesh();
    mesh->setupMesh();

    glUseProgram(renderingProgram);

    mesh->render();
//    mesh2->render();

}


int main() {
    
   
    if (!glfwInit()) {exit(EXIT_FAILURE);}


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);                  
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                  
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            

    
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, " program_2_1 ", nullptr, nullptr);


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
