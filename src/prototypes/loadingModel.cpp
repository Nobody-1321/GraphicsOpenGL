#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Utils.hpp>
#include <modelImporter.hpp>


using namespace std;

#define numVAOs 1
#define numVBOs 2  //changed from 2 to 3

float cameraX, cameraY, cameraZ;

GLuint renderingProgram;
GLuint worldTexture;

GLuint vao[numVAOs];
GLuint vbo[numVBOs];

GLuint projLoc, mvLoc;
int width, height;
float aspect;

glm::mat4 modelMat;
glm::mat4 viewMat;
glm::mat4 projectionMat;
glm::mat4 perspectiveMat;

int numVertices;

void setupVertices() {
    
    ModelImporter model;

    
    #ifdef __WIN32__
        model.parseObjFile(".\\model\\stanford-bunny.obj");
    #else
        //model.parseObjFileVer("./model/stanford-bunny.obj");
        //model.parseObjFile("./model/cat.obj");
        model.parseObjFileVer("./model/xyzrgb_dragon.obj");
    #endif


    numVertices = model.getNumVertices();
    std::vector<float> catVertices = model.getVertices();

    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);

    glGenBuffers(1, vbo);

    // Configurar VBO para los vértices
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, catVertices.size() * sizeof(float), &catVertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
    glEnableVertexAttribArray(0);
    
}

void init(GLFWwindow *window) {


    #ifdef __WIN32__
        renderingProgram = Utils::createShaderProgram(
            ".\\shaders\\vertex_shader_P6.glsl",
            ".\\shaders\\fragment_shader_P6.glsl");
        
        std::cout << "Windows" << std::endl;
    #else
        renderingProgram = Utils::createShaderProgram(
            "./shaders/vertex_shader_P6.glsl",
            "./shaders/fragment_shader_P6.glsl");
        
        std::cout << "Linux" << std::endl;
    #endif

    
    glfwGetFramebufferSize(window, &width, &height);

    aspect = static_cast<float>(width) / static_cast<float>(height);

    perspectiveMat = glm::perspective(glm::radians(60.0f), aspect, 0.1f, 100.0f);

    cameraX = 0.0f; cameraY = 10.0f; cameraZ = 70.0f;
    
    setupVertices();
}


void display(GLFWwindow *window, double currentTime) {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glClearColor(0.0, 0.0, 0.0, 1.0);

    glUseProgram(renderingProgram);

    glBindVertexArray(vao[0]);

    GLuint projectionUni = glGetUniformLocation(renderingProgram, "projection");
    GLuint modelViewUni = glGetUniformLocation(renderingProgram, "modelView");
    
    viewMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));

    float angle = glm::radians(90.0f);
    modelMat = glm::rotate(glm::mat4(1.0f), -(float)angle, glm::vec3(1.0f, 0.0f, 0.0f));
    modelMat = glm::rotate(modelMat, -(float)currentTime, glm::vec3(0.0f, 0.0f, 1.0f));
    modelMat = glm::scale(modelMat, glm::vec3(0.5f, 0.5f, 0.5f));

    glm::mat4 mvMat = viewMat * modelMat;


    glUniformMatrix4fv(projectionUni, 1, GL_FALSE, glm::value_ptr(perspectiveMat));
    glUniformMatrix4fv(modelViewUni, 1, GL_FALSE, glm::value_ptr(mvMat));

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glDrawArrays(GL_TRIANGLES, 0, numVertices);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main() {
    
    // Initialize GLFW, terminate program if failed
    if (!glfwInit()) {exit(EXIT_FAILURE);}

    // Set window properties
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

    // Initialize GLAD to load OpenGL functions
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "failed to initialize GLAD " << std::endl;
        return -1;
    }
    
    // Set the viewport size
    glViewport(0, 0, mode->width, mode->height);

    init(window);

    // Main loop
    while (!glfwWindowShouldClose(window)) {

        display(window, glfwGetTime());
        processInput(window);          
        glfwPollEvents();
        //glfwWaitEvents();
        glfwSwapBuffers(window); 
    }

    // Terminate GLFW when program ends
    glfwTerminate();
   
    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
