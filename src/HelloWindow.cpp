#define GLFW_INCLUDE_NONE
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


float r = 0.0f;
float g = 0.0f;
float b = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


// Initialization function (currently empty)
void init(GLFWwindow* window){
}


// Function to update the display
void display(GLFWwindow* window){
    glClear(GL_COLOR_BUFFER_BIT);       
//    glClearColor(1.0f, 0.3f, 0.3f, 1.0f);

    glClearColor(r, g, b, 1.0f);
    r += 0.01f;
    g += 0.02f;
    b += 0.05f;

    if (r > 1.0f) r = 0.0f;
    if (g > 1.0f) g = 0.0f;
    if (b > 1.0f) b = 0.0f;
    
}


int main() {
    
    // Initialize GLFW, terminate program if failed
    if (!glfwInit()) {exit(EXIT_FAILURE);}

    // Set window properties
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);                  
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                  
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            

    
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    
    //GLFWwindow* window = glfwCreateWindow(700, 700, " Hello Window ", glfwGetPrimaryMonitor(), nullptr);
    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, " program_2_1 ", nullptr, nullptr);
    
    //GLFWwindow* window = glfwCreateWindow(700, 700, " Hello Window ", nullptr, nullptr);
    glfwMaximizeWindow(window);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Set the OpenGL context for the window
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize GLAD to load OpenGL functions
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "failed to initialize GLAD " << std::endl;
        return -1;
    }
    

    // Main loop
    while (!glfwWindowShouldClose(window)) {

        display(window);
        processInput(window);          
        //glfwPollEvents();
        glfwWaitEvents();
        glfwSwapBuffers(window); 
    }

    // Terminate GLFW when program ends
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glfwGetFramebufferSize(window, &width, &height);
    //glViewport(0, 0, width, height);
    
}