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
    glm::vec3(1.0f, 2.5f, -7.5f),   // Reduciendo la distancia
    glm::vec3(-0.75f, -1.1f, -1.25f), // Acercando este cubo
    glm::vec3(-1.9f, -1.0f, -6.15f), // Acercando este cubo
    glm::vec3(1.2f, -0.2f, -1.75f), // Reduciendo la separación
    glm::vec3(-0.85f, 1.5f, -3.75f), // Acercando la posición
    glm::vec3(0.65f, -1.0f, -1.25f), // Juntando más
    glm::vec3(0.75f, 1.0f, -1.25f), // Reduciendo la distancia
    glm::vec3(0.75f, 0.1f, -0.75f), // Acercando este cubo
    glm::vec3(0.0f, 0.0f, -10.00f) //light cube
};

void rotateLight() { 
    float radius = 5.0f;  // El radio de la circunferencia

    // Calcula el tiempo actual
    float time = glfwGetTime();
    
    // Ajusta las posiciones en el eje X y Z para moverse en una circunferencia
//    cubePositions[9].y = cos(time) * radius;
    cubePositions[9].z = sin(time) * radius;

    // Si no deseas movimiento vertical, mantiene el valor constante en Y
//    cubePositions[9].x = 1.0f;  // Altura fija de la luz
}


void init()
{

#ifdef __WIN32__
    renderingProgram = Utils::createShaderProgram(
        ".\\shaders\\vertex_shader10_AttL.glsl",
        ".\\shaders\\fragment_shader10_AttL.glsl");
    
//    renderingProgram = Utils::createShaderProgram(
//        ".\\shaders\\vertex_shader9_DML.glsl",
//        ".\\shaders\\fragment_shader9_DML.glsl");


    texture1 = Utils::loadTexture(".\\textures\\container2.png");
    texture2 = Utils::loadTexture(".\\textures\\container2_specular.png");
    std::cout << "Windows" << std::endl;
#else
    renderingProgram = Utils::createShaderProgram(
        "./shaders/vertex_shader10_DirL.glsl",
        "./shaders/fragment_shader10_DirL.glsl");

    texture1 = Utils::loadTexture("./textures/container2.png");
    texture2 = Utils::loadTexture("./textures/container2_specular.png");
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


    float r=0, g=0, b=0;

// new program add
void display(GLFWwindow *window)
{
    glClear(GL_COLOR_BUFFER_BIT);
    //glClearColor(0.8470588235294118f, 0.8274509803921568f, 0.7647058823529411f, 1.0f);
    rotateLight();
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        r = 1.0f;
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        g = 1.0f;
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
        b = 1.0f;
    
    glClearColor(r, g, b, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(renderingProgram);

    for (int i = 0; i < 10; i++)
    {
        model = glm::mat4(1.0f);
        view = glm::mat4(1.0f);
        projection = glm::mat4(1.0f);

        model = glm::translate(model, cubePositions[i]);

        float angle = glm::radians(20.0f * (float)glfwGetTime()); // Cambiar con el tiempo

//        model = glm::rotate(model, angle, glm::vec3(0.5f, 1.0f, 0.0f));

        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

        
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
                
        projection = glm::perspective(glm::radians(Zoom), aspectRatio, 0.1f, 1000.0f);

        unsigned int modelLoc = glGetUniformLocation(renderingProgram, "model");
        unsigned int viewLoc = glGetUniformLocation(renderingProgram, "view");
        unsigned int projectionLoc = glGetUniformLocation(renderingProgram, "projection");

        unsigned int viewPosLoc = glGetUniformLocation(renderingProgram, "viewPos");

        unsigned int lightPosLoc = glGetUniformLocation(renderingProgram, "light.direction");
        unsigned int lightAmbLoc = glGetUniformLocation(renderingProgram, "light.ambient");
        unsigned int lightDiffLoc = glGetUniformLocation(renderingProgram, "light.diffuse");
        unsigned int lightSpecLoc = glGetUniformLocation(renderingProgram, "light.specular");

        unsigned int lightConstantLoc = glGetUniformLocation(renderingProgram, "light.constant");
        unsigned int lightLinearLoc = glGetUniformLocation(renderingProgram, "light.linear");
        unsigned int lightQuadraticLoc = glGetUniformLocation(renderingProgram, "light.quadratic");

        glUniform1f(lightConstantLoc, 1.0f);
        glUniform1f(lightLinearLoc, 0.09f);
        glUniform1f(lightQuadraticLoc, 0.032f);

        glUniform3fv(viewPosLoc, 1, glm::value_ptr(cameraPos));

        glm::vec3 lightPosition = cubePositions[9];

        glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPosition));
        glUniform3f(lightAmbLoc, 0.8f, 0.8f, 0.8f);
        glUniform3f(lightDiffLoc, 0.5f, 0.5f, 0.5f);
        glUniform3f(lightSpecLoc, 1.0f, 1.0f, 1.0f);


        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(vao[0]); // Bind to VAO containing the triangle

        glActiveTexture(GL_TEXTURE0);           // Activate the texture unit
        glBindTexture(GL_TEXTURE_2D, texture1); // Bind the texture to the unit

        glActiveTexture(GL_TEXTURE1);           // Activate the texture unit
        glBindTexture(GL_TEXTURE_2D, texture2); // Bind the texture to the unit

        GLint textureLoc1 = glGetUniformLocation(renderingProgram, "material.diffuse");
        GLint textureLoc2 = glGetUniformLocation(renderingProgram, "material.specular");

        glUniform1i(textureLoc1, 0); // Set the sampler texture unit to 0
                                     //    glUniform1i(textureLoc2, 1);         // Set the sampler texture unit to 1
        glUniform1i(textureLoc2, 1); // Set the sampler texture unit to 1

        glDrawArrays(GL_TRIANGLES, 0, 36); // Draw the triangle
    }
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
    GLFWwindow *window = glfwCreateWindow(mode->width, mode->height, " Hello Mix Texture ", nullptr, nullptr);

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
    // Posiciones (x, y, z) y normales (nx, ny, nz)
    float vertexPositions[] = {
        // Cara trasera (normales hacia -Z)
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        // Cara delantera (normales hacia +Z)
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        // Cara izquierda (normales hacia -X)
        -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 
        -0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        // Cara derecha (normales hacia +X)
         0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 
         0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        // Cara inferior (normales hacia -Y)
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 
         0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

        // Cara superior (normales hacia +Y)
        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 
         0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f   
    };

    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);

    glGenBuffers(1, vbo); // Solo un VBO es necesario

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

    // Atributo para las posiciones (vec3)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    // Atributo para las normales (vec3)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Atributo para las coordenadas de textura (vec2)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
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