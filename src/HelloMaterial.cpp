#define GLFW_INCLUDE_NONE
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Utils.hpp>
#include <cmath>
#include <Sphere.hpp>
using namespace std;

#define numVAOs 1
#define numVBOs 2

//Sphere mySphere(1.0f, 4608, 2304);
Sphere mySphere(1.0f, 144, 72);
//Sphere mySphere(1.0f, 16, 8);
//Sphere mySphere(1.0f, 4, 2);

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
    glm::vec3(-2.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(2.0f, 0.0f, 0.0f),
    glm::vec3(4.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 0.0f, -4.0f),
};

glm::vec4 colorValue[] = {
    glm::vec4(0.135f, 0.2225f, 0.1575f, 1.0f), // esmeralda
    glm::vec4(0.0215f, 0.1745f, 0.0215f, 1.0f), // jade
    glm::vec4(0.05375f, 0.05f, 0.06625f, 1.0f), // obsidiana
    glm::vec4(0.698f, 0.096f, 0.203f, 1.0f),   // rubí (ajustado)
    glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),         // Light
};

struct materialAttributes
{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};

//array of materials

materialAttributes materials[] = {
    {{0.135f, 0.2225f, 0.1575f}, {0.54f, 0.89f, 0.63f}, {0.316228f, 0.316228f, 0.316228f}, 32.0f},  // esmeralda
    {{0.0215f, 0.1745f, 0.0215f}, {0.07568f, 0.61424f, 0.07568f}, {0.633f, 0.727811f, 0.633f}, 32.0f}, // jade
    {{0.05375f, 0.05f, 0.06625f}, {0.18275f, 0.17f, 0.22525f}, {0.332741f, 0.328634f, 0.346435f}, 32.0f}, // obsidiana
    {{0.698f, 0.096f, 0.203f}, {1.0f, 0.0f, 0.0f}, {0.633f, 0.727811f, 0.633f}, 32.0f} // rubí (ajustado)
};


GLuint renderingPrograms[5];

void init() {
#ifdef __WIN32__
    renderingPrograms[4] = Utils::createShaderProgram(
        ".\\shaders\\vertex_shader7.glsl",
        ".\\shaders\\fragment_shader7.glsl");

    renderingPrograms[3] = Utils::createShaderProgram(
        ".\\shaders\\vertex_shader8_ML.glsl",
        ".\\shaders\\fragment_shader9_ML.glsl");

    renderingPrograms[2] = Utils::createShaderProgram(
        ".\\shaders\\vertex_shader8_ML.glsl",
        ".\\shaders\\fragment_shader9_ML.glsl");

    renderingPrograms[1] = Utils::createShaderProgram(
        ".\\shaders\\vertex_shader8_ML.glsl",
        ".\\shaders\\fragment_shader9_ML.glsl");

    renderingPrograms[0] = Utils::createShaderProgram(
        ".\\shaders\\vertex_shader8_ML.glsl",
        ".\\shaders\\fragment_shader9_ML.glsl");
`
 
#else
    renderingPrograms[4] = Utils::createShaderProgram(
        "./shaders/vertex_shader7.glsl",
        "./shaders/fragment_shader7.glsl");

    renderingPrograms[3] = Utils::createShaderProgram(
        "./shaders/vertex_shader8_ML.glsl",
        "./shaders/fragment_shader9_ML.glsl");

    renderingPrograms[2] = Utils::createShaderProgram(
        "./shaders/vertex_shader8_ML.glsl",
        "./shaders/fragment_shader9_ML.glsl");

    renderingPrograms[1] = Utils::createShaderProgram(
        "./shaders/vertex_shader8_ML.glsl",
        "./shaders/fragment_shader9_ML.glsl");

    renderingPrograms[0] = Utils::createShaderProgram(
        "./shaders/vertex_shader8_ML.glsl",
        "./shaders/fragment_shader9_ML.glsl");
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

void rotateLight() { 
    float radius = 5.0f;  // El radio de la circunferencia

    // Calcula el tiempo actual
    float time = glfwGetTime();
    
    // Ajusta las posiciones en el eje X y Z para moverse en una circunferencia
    cubePositions[4].y = cos(time) * radius;
    cubePositions[4].z = sin(time) * radius;

    // Si no deseas movimiento vertical, mantiene el valor constante en Y
    cubePositions[4].x = 1.0f;  // Altura fija de la luz
}

// new program add
void display(GLFWwindow *window)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    rotateLight();

    for (int i = 0; i < 5; i++)
    {

        glUseProgram(renderingPrograms[i]);

        model = glm::mat4(1.0f);
        view = glm::mat4(1.0f);
        projection = glm::mat4(1.0f);

        model = glm::translate(model, cubePositions[i]);

        float angle = glm::radians(20.0f * (float)glfwGetTime()); // Cambiar con el tiempo

        //model = glm::rotate(model, angle, glm::vec3(0.5f, 1.0f, 0.0f));

        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

        
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        

        projection = glm::perspective(glm::radians(Zoom), aspectRatio, 0.1f, 1000.0f);

        unsigned int modelLoc = glGetUniformLocation(renderingPrograms[i], "model");
        unsigned int viewLoc = glGetUniformLocation(renderingPrograms[i], "view");
        unsigned int projectionLoc = glGetUniformLocation(renderingPrograms[i], "projection");

        unsigned int alightColor = glGetUniformLocation(renderingPrograms[i], "lightColor");
        unsigned int objectColorVec = glGetUniformLocation(renderingPrograms[i], "objectColor");
        unsigned int lightPosLoc = glGetUniformLocation(renderingPrograms[i], "lightPos");
        unsigned int viewPosLoc = glGetUniformLocation(renderingPrograms[i], "viewPos");
       //material

    if (i != 4){

        unsigned int matAmbLoc = glGetUniformLocation(renderingPrograms[i], "material.ambient");
        unsigned int matDiffLoc = glGetUniformLocation(renderingPrograms[i], "material.diffuse");
        unsigned int matSpecLoc = glGetUniformLocation(renderingPrograms[i], "material.specular");
        unsigned int matShineLoc = glGetUniformLocation(renderingPrograms[i], "material.shininess");

        unsigned int lightPosLoc = glGetUniformLocation(renderingPrograms[i], "light.position");
        unsigned int lightAmbLoc = glGetUniformLocation(renderingPrograms[i], "light.ambient");
        unsigned int lightDiffLoc = glGetUniformLocation(renderingPrograms[i], "light.diffuse");
        unsigned int lightSpecLoc = glGetUniformLocation(renderingPrograms[i], "light.specular");

        glm::vec3 lightPosition = cubePositions[4]; // Posición fija de la luz

        glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPosition));
        glUniform3fv(lightAmbLoc, 1, glm::value_ptr(glm::vec3(0.2f, 0.2f, 0.2f)));
        glUniform3fv(lightDiffLoc, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
        glUniform3fv(lightSpecLoc, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));

        glUniform3fv(matAmbLoc, 1, glm::value_ptr(materials[i].ambient));                
        glUniform3fv(matDiffLoc, 1, glm::value_ptr(materials[i].diffuse));
        glUniform3fv(matSpecLoc, 1, glm::value_ptr(materials[i].specular));
        glUniform1f(matShineLoc, materials[i].shininess);
    }

        glUniform3fv(viewPosLoc, 1, glm::value_ptr(cameraPos));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform4fv(alightColor, 1, glm::value_ptr(colorValue[4]));
        glUniform4fv(objectColorVec, 1, glm::value_ptr(colorValue[i]));
        glUniform3fv(lightPosLoc, 1, glm::value_ptr(cubePositions[4]));


        //glBindVertexArray(vao[0]);
        glDrawElements(GL_TRIANGLES, mySphere.getNumIndices(), GL_UNSIGNED_INT, 0);
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
    glfwTerminate();

    return 0;
}

void setUpVertices(void)
{
    std::vector<unsigned int> indices = mySphere.getIndices();
    std::vector<glm::vec3> vertices = mySphere.getVertices();
    std::vector<glm::vec3> normals = mySphere.getNormals();

    std::vector<float> vertexPositions;

    for (int i = 0; i < vertices.size(); i++)
    {
        vertexPositions.push_back(vertices[i].x);
        vertexPositions.push_back(vertices[i].y);
        vertexPositions.push_back(vertices[i].z);
        vertexPositions.push_back(normals[i].x);
        vertexPositions.push_back(normals[i].y);
        vertexPositions.push_back(normals[i].z);
    }

    std::cout << "Vertices: " << vertices.size() << std::endl;

    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);

    glGenBuffers(2, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, vertexPositions.size() * sizeof(float), &vertexPositions[0], GL_STATIC_DRAW);

    // Posiciones del vértice
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Normales del vértice
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    ///configuración de los indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);


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