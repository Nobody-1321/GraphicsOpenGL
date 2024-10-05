#define GLFW_INCLUDE_NONE
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
using namespace std;

#define numVAOs 2
#define numVBOs 2
GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

const char *vertexShaderSource = "#version 410 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    
    "out vec4 vertexColor;\n"
    "uniform vec4 ourColor;\n"
    
    "void main()\n"
    "{\n"
        " gl_Position = vec4(aPos, 1.0);\n"
        " vertexColor = ourColor;\n"
    "}\0";

const char *fragmentShaderSource = "#version 410 core\n"
    "out vec4 FragColor;\n"
    "in vec4 vertexColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vertexColor;\n"    
    "}\n\0";


void setUpVertices(void);
GLuint createShaderProgram();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

void init(){
    renderingProgram = createShaderProgram();
    setUpVertices();
}


void display(GLFWwindow* window){
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f); // Color gris claro

    glUseProgram(renderingProgram);  
    
    float timeValue = glfwGetTime();  // Get the current time
    
    float blueValue = (sin(timeValue) / 2.5f) + 0.3f;  // Calculate the blue value
    float redValue = (cos(timeValue) / 2.5f) + 0.3f;   // Calculate the red value
    float greenValue = (sin(timeValue) / 2.5f) + 0.3f; // Calculate the green value

    int vertexColorLocation = glGetUniformLocation(renderingProgram, "ourColor"); // Get the location of the uniform variable 'ourColor'
    glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f); // Set the value of the uniform variable 'ourColor'
    
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

    float vertexPositions[] = { 
        -0.5f, -0.5f, 0.0f,        
        -0.5f, 0.5f, 0.0f,         
         0.5f,  0.5f, 0.0f,        
        -0.5f, -0.5f, 0.0f,        
        0.5f, -0.5f, 0.0f,         
        0.5f, 0.5f, 0.0f           
    };                             
                                   
                                                               
    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);

    glGenBuffers(1, vbo); 
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
    glEnableVertexAttribArray(0);

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

GLuint createShaderProgram() {
    // Variables to store the compilation status of shaders and the linking status of the program
    GLint vertCompiled;  // Indicates if vertex shader compiled successfully
    GLint fragCompiled;  // Indicates if fragment shader compiled successfully
    GLint linked;        // Indicates if the program linked successfully
    
    // Create the vertex and fragment shader objects
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);   // Create a vertex shader object
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER); // Create a fragment shader object
    
    // Attach the shader source code to the shader objects
    // 'vertexShaderSource' and 'fragmentShaderSource' are strings containing the GLSL shader code
    glShaderSource(vShader, 1, &vertexShaderSource, nullptr);  // Set vertex shader source code
    glShaderSource(fShader, 1, &fragmentShaderSource, nullptr); // Set fragment shader source code
    
    // Compile the vertex shader
    glCompileShader(vShader);
    
    // Check if the vertex shader compiled successfully
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled); // Retrieve compile status
    if (vertCompiled != 1) {  // If compilation failed
        cout << "vertex compilation failed" << endl;  // Output an error message
    }
    
    // Compile the fragment shader
    glCompileShader(fShader);
    
    // Check if the fragment shader compiled successfully
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled); // Retrieve compile status
    if (fragCompiled != 1) {  // If compilation failed
        cout << "fragment compilation failed" << endl;  // Output an error message
    }
    
    // Create a shader program and attach both shaders to it
    GLuint vfProgram = glCreateProgram();  // Create a shader program object
    glAttachShader(vfProgram, vShader);    // Attach the compiled vertex shader
    glAttachShader(vfProgram, fShader);    // Attach the compiled fragment shader
    
    // Link the shader program (this combines the vertex and fragment shaders into a single program)
    glLinkProgram(vfProgram);
    
    // Check if the program linked successfully
    glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked); // Retrieve link status
    if (linked != 1) {  // If linking failed
        cout << "linking failed" << endl;  // Output an error message
    }
    
    // Once the shaders are linked into the program, they are no longer needed, so we can delete them
    glDeleteShader(vShader);  // Delete the vertex shader object
    glDeleteShader(fShader);  // Delete the fragment shader object
    
    // Return the linked shader program, which can now be used to render objects
    return vfProgram;
}
