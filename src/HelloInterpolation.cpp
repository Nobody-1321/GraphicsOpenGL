#define GLFW_INCLUDE_NONE
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Utils.hpp>
#include <cmath>
using namespace std;

#define numVAOs 2
#define numVBOs 2
GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

void setUpVertices(void);
GLuint createShaderProgram();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

void init(){

    #ifdef __WIN32__
        renderingProgram = Utils::createShaderProgram(
            ".\\shaders\\vertex_shader1.glsl",
            ".\\shaders\\fragment_shader1.glsl");
        std::cout << "Windows" << std::endl;
    #else
        renderingProgram = Utils::createShaderProgram(
            "./shaders/vertex_shader1.glsl",
            "./shaders/fragment_shader1.glsl");
        std::cout << "Linux" << std::endl;
    #endif

    setUpVertices();
}

// new program add
void display(GLFWwindow* window){
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.8470588235294118f, 0.8274509803921568f, 0.7647058823529411f, 1.0f);

    glUseProgram(renderingProgram);  
    
    glBindVertexArray(vao[0]);          // Bind to VAO containing the triangle
    glDrawArrays(GL_TRIANGLES, 0, 6);   // Draw the triangle     
    glBindVertexArray(0);               // Unbind from the VAO

}

int main() {
    
    
    if (!glfwInit()) {exit(EXIT_FAILURE);}

    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);                  
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                  
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            

    
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    GLFWwindow* window = glfwCreateWindow(700, 700, " Hello Glsl ", nullptr, nullptr);
    
    if (!window) {
        glfwTerminate();
        return -1;
    }

    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    
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

    
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}

void setUpVertices(void){
    //2 triangles with 3 vertices each and its color
    float vertexPositions[36] = { 
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };                                                                                                             

    glGenVertexArrays(1, vao);;
    glBindVertexArray(vao[0]);
    
    glGenBuffers(1, vbo); 
    
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
}

