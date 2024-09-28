#define GLFW_INCLUDE_NONE
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Utils.hpp>
#include <cmath>
using namespace std;

#define numVAOs 1
#define numVBOs 2

GLuint renderingProgram;
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

float deltaTime = 1.0f;	// Time between current frame and last frame
float lastFrame = 1.0f; // Time of last frame

float Zoom = 45.0f;
float yaw; // Iniciar con -90 grados para mirar hacia adelante
float pitch;   // El ángulo en el eje Y (pitch)
float lastX, lastY; // Iniciar el mouse en el centro de la pantalla
bool firstMouse;
float sensitivity; // Sensibilidad del mouse


void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void setUpVertices(void);
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
    glm::vec3(2.0f, 5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f, 3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f, 2.0f, -2.5f),
    glm::vec3(1.5f, 0.2f, -1.5f),
    glm::vec3(-1.3f, 1.0f, -1.5f)};

void init()
{

#ifdef __WIN32__
    renderingProgram = Utils::createShaderProgram(
        ".\\shaders\\vertex_shader6.glsl",
        ".\\shaders\\fragment_shader6.glsl");//deep example 61 normal 6

    texture1 = Utils::loadTexture(".\\textures\\torus.jpg");
    texture2 = Utils::loadTexture(".\\textures\\angry.png");
    std::cout << "Windows" << std::endl;
#else
    renderingProgram = Utils::createShaderProgram(
        "./shaders/vertex_shader61.glsl",
        "./shaders/fragment_shader61.glsl");

    texture1 = Utils::loadTexture("./textures/torus.jpg");
    texture2 = Utils::loadTexture("./textures/angry.png");
    std::cout << "Linux" << std::endl;
#endif
    
    cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

    yaw = -90.0f;             // Iniciar con -90 grados para mirar hacia adelante
    pitch = 0.0f;             // El ángulo en el eje Y (pitch)
    lastX = 400, lastY = 300; // Iniciar el mouse en el centro de la pantalla
    firstMouse = true;
    sensitivity = 0.1f; // Sensibilidad del mouse

    setUpVertices();
}

// new program add
void display(GLFWwindow *window)
{
    glClearColor(0.8470588235294118f, 0.8274509803921568f, 0.7647058823529411f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // Habilitar stencil y depth tests
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_DEPTH_TEST);

    // Fase 1: Configurar stencil para dibujar los cubos normales
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);  // Reemplaza con 1 cuando el test pasa
    glStencilFunc(GL_ALWAYS, 1, 0xFF);          // Siempre pasa, stencil = 1
    glStencilMask(0xFF);                        // Habilitar la escritura en el buffer de stencil

    glUseProgram(renderingProgram);

    // Dibujar cubos normales
    for (int i = 0; i < 10; i++)
    {
        // Configuración de matrices model, view, projection
        model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = glm::radians(20.0f * (float)glfwGetTime());
        model = glm::rotate(model, angle, glm::vec3(0.5f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        projection = glm::perspective(glm::radians(Zoom), aspectRatio, 0.1f, 100.0f);

        // Pasar matrices a shaders
        glUniformMatrix4fv(glGetUniformLocation(renderingProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(renderingProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(renderingProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        //vector color
        glUniform4f(glGetUniformLocation(renderingProgram, "ourColor"), 0.0f, 0.0f, 1.0f, 1.0f);

        // Vincular y usar texturas
        glBindVertexArray(vao[0]);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glUniform1i(glGetUniformLocation(renderingProgram, "texture1"), 0);
        glUniform1i(glGetUniformLocation(renderingProgram, "texture2"), 1);

        // Dibujar el cubo
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // Fase 2: Dibujar contornos (u otro efecto)
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);   // Solo pasa donde el stencil no es 1
    glStencilMask(0x00);                   // Deshabilitar escritura en stencil
    glDisable(GL_DEPTH_TEST);              // Deshabilitar test de profundidad

    for (int i = 0; i < 10; i++)
    {
        // Ajustar el tamaño del modelo para el contorno
        model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = glm::radians(20.0f * (float)glfwGetTime());
        model = glm::rotate(model, angle, glm::vec3(0.5f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.55f, 0.55f, 0.55f));  // Agrandar el modelo ligeramente para el contorno

        // Pasar matrices a shaders
        glUniformMatrix4fv(glGetUniformLocation(renderingProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(renderingProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(renderingProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniform4f(glGetUniformLocation(renderingProgram, "ourColor"), 0.0f, 0.0f, 0.0f, 0.0f);
        
        // Dibujar el contorno
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // Restaurar estado
    glStencilMask(0xFF);  // Habilitar la escritura en el stencil nuevamente
    glEnable(GL_DEPTH_TEST);  // Habilitar el test de profundidad
}

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
    GLFWwindow *window = glfwCreateWindow(700, 700, " Hello Mix Texture ", nullptr, nullptr);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

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
    // 3 vertices each and its texture coordinates
    float vertexPositions[] = {
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,     1.0f, 0.0f,
        0.5f, 0.5f, -0.5f,      1.0f, 1.0f,
        0.5f, 0.5f, -0.5f,      1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f,     0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f,     0.0f, 0.0f,
        0.5f, -0.5f, 0.5f,      1.0f, 0.0f,
        0.5f, 0.5f, 0.5f,       1.0f, 1.0f,
        0.5f, 0.5f, 0.5f,       1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f,      0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,     0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f,   1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f,   1.0f, 0.0f,

        0.5f, 0.5f, 0.5f,   1.0f, 0.0f,
        0.5f, 0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f,  0.0f, 0.0f,
        0.5f, 0.5f, 0.5f,   1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, 0.5f,   1.0f, 0.0f,
        0.5f, -0.5f, 0.5f,   1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, 0.5f, -0.5f,   1.0f, 1.0f,
        0.5f, 0.5f, 0.5f,    1.0f, 0.0f,
        0.5f, 0.5f, 0.5f,    1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f,   0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f,  0.0f, 1.0f  };

    glGenVertexArrays(1, vao);
    ;
    glBindVertexArray(vao[0]);

    glGenBuffers(1, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
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