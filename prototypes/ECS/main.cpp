#define GLFW_INCLUDE_NONE
#include <vector>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Utils.hpp>
#include <MeshFactory.hpp>
#include <modelImporter.hpp>
#include <cmath>
using namespace std;

#define numVAOs 1
#define numVBOs 2


GLuint windowTexture;
GLuint floorTexture;

GLuint vao[numVAOs];
GLuint vbo[numVBOs];

struct transformData {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
};


struct meshData {
    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> texCoords;
};

float aspectRatio;

struct cameraData {
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
};


struct shaderData {
    GLuint skullShader;
};

struct entityData {
    unsigned int id;
    entityData(unsigned int id) : id(id) {}
};

MeshFactory factory;

float lastFrame;
float deltaTime;

void calculateDeltaTime() {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
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
    GLFWwindow *window = glfwCreateWindow(mode->width, mode->height, "ECS", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    aspectRatio = mode->width / mode->height;
    glfwMaximizeWindow(window);

    glfwMakeContextCurrent(window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "failed to initialize GLAD " << std::endl;
        return -1;
    }


    glViewport(0, 0, mode->width, mode->height);

    while (!glfwWindowShouldClose(window))
    {
        calculateDeltaTime();
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}


