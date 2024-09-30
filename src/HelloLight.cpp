#define GLFW_INCLUDE_NONE
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Utils.hpp>
#include <cmath>
using namespace std;

#define numVAOs 1
#define numVBOs 2

GLuint texture1;
GLuint texture2;

GLuint vao[numVAOs];
GLuint vbo[numVBOs];

glm::mat4 model;
glm::mat4 view;
glm::mat4 projection;

float aspectRatio;

glm::vec3 cameraPos;
glm::vec3 cameraFront;
glm::vec3 cameraUp;

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

float Zoom = 45.0f;
float yaw; // Iniciar con -90 grados para mirar hacia adelante
float pitch;   // El ángulo en el eje Y (pitch)
float lastX, lastY; // Iniciar el mouse en el centro de la pantalla
bool firstMouse;
float sensitivity; // Sensibilidad del mouse

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void setUpVertices();
GLuint createShaderProgram();
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);



void calculateDeltaTime() {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

glm::vec3 cubePositions[] = {
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(2.0f, 0.0f, 0.0f),
    glm::vec3(-1.0f, 0.0f, 0.0f),
    glm::vec3(2.0f, 0.0f, 2.0f),
};

glm::vec4 colorValue[] ={
    glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
    glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
    glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
    glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
    glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), // Light
};

GLuint renderingPrograms[5];

void init() {
#ifdef __WIN32__
    renderingPrograms[4] = Utils::createShaderProgram(
        ".\\shaders\\vertex_shader7.glsl",
        ".\\shaders\\fragment_shader7.glsl");

    renderingPrograms[3] = Utils::createShaderProgram(
        ".\\shaders\\vertex_shader7.glsl",
        ".\\shaders\\fragment_shader7.glsl");

    renderingPrograms[2] = Utils::createShaderProgram(
        ".\\shaders\\vertex_shader7_SL.glsl",
        ".\\shaders\\fragment_shader7_SL.glsl");

    renderingPrograms[1] = Utils::createShaderProgram(
        ".\\shaders\\vertex_shader7_DL.glsl",
        ".\\shaders\\fragment_shader7_DL.glsl");

    renderingPrograms[0] = Utils::createShaderProgram(
        ".\\shaders\\vertex_shader7_AL.glsl",
        ".\\shaders\\fragment_shader7_AL.glsl");
    
    std::cout << "Windows" << std::endl;
#else
    renderingPrograms[4] = Utils::createShaderProgram(
        "./shaders/vertex_shader7.glsl",
        "./shaders/fragment_shader7.glsl");

    renderingPrograms[3] = Utils::createShaderProgram(
        "./shaders/vertex_shader7.glsl",
        "./shaders/fragment_shader7.glsl");

    renderingPrograms[2] = Utils::createShaderProgram(
        "./shaders/vertex_shader7_SL.glsl",
        "./shaders/fragment_shader7_SL.glsl");

    renderingPrograms[1] = Utils::createShaderProgram(
        "./shaders/vertex_shader7_DL.glsl",
        "./shaders/fragment_shader7_DL.glsl");

    renderingPrograms[0] = Utils::createShaderProgram(
        "./shaders/vertex_shader7_AL.glsl",
        "./shaders/fragment_shader7_AL.glsl");
 
    std::cout << "Linux" << std::endl;
#endif

    cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f); 
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    yaw = -90.0f;             // Iniciar con -90 grados para mirar hacia adelante
    pitch = 0.0f;             // El ángulo en el eje Y (pitch)
    firstMouse = true;
    sensitivity = 0.1f; // Sensibilidad del mouse

    setUpVertices();
}


// new program add
void display(GLFWwindow *window)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    for (int i = 0; i < 5; i++)
    {

        glUseProgram(renderingPrograms[i]);

        model = glm::mat4(1.0f);
        view = glm::mat4(1.0f);
        projection = glm::mat4(1.0f);

        model = glm::translate(model, cubePositions[i]);

        float angle = glm::radians(20.0f * (float)glfwGetTime()); // Cambiar con el tiempo

        model = glm::rotate(model, angle, glm::vec3(0.5f, 1.0f, 0.0f));

        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

        
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        

        projection = glm::perspective(glm::radians(Zoom), aspectRatio, 0.1f, 100.0f);

        unsigned int modelLoc = glGetUniformLocation(renderingPrograms[i], "model");
        unsigned int alightColor = glGetUniformLocation(renderingPrograms[i], "lightColor");
        unsigned int objectColorVec = glGetUniformLocation(renderingPrograms[i], "objectColor");
        unsigned int viewLoc = glGetUniformLocation(renderingPrograms[i], "view");
        unsigned int projectionLoc = glGetUniformLocation(renderingPrograms[i], "projection");
        unsigned int lightPosLoc = glGetUniformLocation(renderingPrograms[i], "lightPos");
        unsigned int viewPosLoc = glGetUniformLocation(renderingPrograms[i], "viewPos");
        
        glUniform3fv(viewPosLoc, 1, glm::value_ptr(cameraPos));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform4fv(alightColor, 1, glm::value_ptr(colorValue[4]));
        glUniform4fv(objectColorVec, 1, glm::value_ptr(colorValue[i]));
        glUniform3fv(lightPosLoc, 1, glm::value_ptr(cubePositions[4]));

        glBindVertexArray(vao[0]); // Bind to VAO containing the triangle
        glDrawArrays(GL_TRIANGLES, 0, 36); // Draw the triangle
    }
}

int main()
{
    calculateDeltaTime();
    //center


    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    GLFWwindow *window = glfwCreateWindow(mode->width, mode->height, "Hello Window", nullptr, nullptr);
    
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMaximizeWindow(window);

    aspectRatio = 700.0f / 700.0f;
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    glfwSetCursorPosCallback(window, mouse_callback); 
    glfwSetScrollCallback(window, scroll_callback); 

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "failed to initialize GLAD " << std::endl;
        return -1;
    }

    init();

    while (!glfwWindowShouldClose(window))
    {
        calculateDeltaTime();
        display(window);
        processInput(window);
        glfwPollEvents();

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO);
    glfwTerminate();

    return 0;
}

void setUpVertices(void)
{
    // Vértices con normales
    float vertexPositions[] = {
        // Cara trasera (normales hacia -Z)
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

        // Cara delantera (normales hacia +Z)
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,

        // Cara izquierda (normales hacia -X)
        -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,

        // Cara derecha (normales hacia +X)
         0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,

        // Cara inferior (normales hacia -Y)
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

        // Cara superior (normales hacia +Y)
        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);

    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

    // Posiciones del vértice
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Normales del vértice
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void processInput(GLFWwindow *window)
{
    float cameraSpeed = 2.1f * deltaTime; // Ajustar la velocidad según deltaTime

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // Asegúrate de que el viewport cubra toda la ventana
    glViewport(0, 0, width, height);
    aspectRatio = (float)width / (float)height;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
        
    
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    // Calcular el desplazamiento del ratón desde la última posición registrada
    float xOffset = xpos - lastX;
    float yOffset = lastY - ypos; // Invertir el valor Y ya que los ejes Y de la pantalla y OpenGL están invertidos
    lastX = xpos;
    lastY = ypos;

    // Aplicar la sensibilidad al desplazamiento del ratón
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    // Ajustar yaw (eje horizontal) y pitch (eje vertical)
    yaw += xOffset;
    pitch += yOffset;

    // Limitar el ángulo del pitch para que no voltee más allá de los 90 grados
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    // Calcular la nueva dirección del frente de la cámara
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front); // Normalizar el vector para asegurar que tenga una magnitud de 1
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}