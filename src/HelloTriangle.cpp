// Definimos esta macro para evitar que GLFW incluya automáticamente los headers de OpenGL
#define GLFW_INCLUDE_NONE

#include <iostream>       // Librería estándar para entrada/salida
#include <glad/glad.h>    // Librería para cargar funciones de OpenGL
#include <GLFW/glfw3.h>   // Librería para crear ventanas y manejar eventos de OpenGL
using namespace std;      // Uso del espacio de nombres estándar para simplificar sintaxis

// Definimos las constantes para la cantidad de VAOs (Vertex Array Objects) y VBOs (Vertex Buffer Objects)
#define numVAOs 1
#define numVBOs 1

// Variables globales para almacenar el programa de renderizado y los objetos VAO y VBO
GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

// Código fuente del shader de vértices en GLSL
const char *vertexShaderSource = "#version 410 core\n"
    "layout (location = 0) in vec3 aPos;\n"    // El atributo de posición se pasará a través del layout 0
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"     // Convertimos el vec3 en vec4 y lo asignamos a gl_Position
    "}\0";

// Código fuente del shader de fragmentos en GLSL
const char *fragmentShaderSource = "#version 410 core\n"
    "out vec4 FragColor;\n"                   // Declaramos una variable de salida para el color del fragmento
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.0251f, 1.0f, 1.0f, 1.0f);\n"  // Color púrpura RGBA (R=1.0, G=0.0, B=1.0, A=1.0)
    "}\n\0";

// Prototipos de las funciones
void setUpVertices(void);
GLuint createShaderProgram();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// Función para inicializar el programa de renderizado y los vértices
void init(){
    renderingProgram = createShaderProgram();  // Creamos el programa de shaders
    setUpVertices();                           // Configuramos los vértices para el triángulo
}

// Función que maneja el ciclo de renderizado
void display(GLFWwindow* window){
    glClear(GL_COLOR_BUFFER_BIT);              // Limpiamos el buffer de color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);      // Establecemos el color de fondo a negro

    glUseProgram(renderingProgram);            // Activamos el programa de shaders

    // Asociamos el VAO para usar los vértices que configuramos
    glBindVertexArray(vao[0]);

    // Dibujamos el triángulo usando los vértices
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Desasociamos el VAO para evitar efectos secundarios
    glBindVertexArray(0);
}

int main() {
    // Inicializamos GLFW, si falla terminamos el programa
    if (!glfwInit()) {exit(EXIT_FAILURE);}

    // Establecemos la versión de OpenGL (4.3) y el perfil que vamos a usar
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Habilitamos compatibilidad para futuras versiones de OpenGL

    // Creamos la ventana de 700x700 pixeles
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    GLFWwindow* window = glfwCreateWindow(700, 700, " Hello Triangle ", nullptr, nullptr);

    // Si la creación de la ventana falla, terminamos el programa
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Establecemos el contexto de OpenGL para la ventana creada
    glfwMakeContextCurrent(window);
    // Registramos la función de callback para manejar el redimensionado de la ventana
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Inicializamos GLAD para poder acceder a las funciones de OpenGL
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "failed to initialize GLAD " << std::endl;
        return -1;
    }

    init();  // Llamamos a la función de inicialización

    // Bucle principal de renderizado
    while (!glfwWindowShouldClose(window)) {
        display(window);        // Actualizamos la pantalla
        processInput(window);   // Procesamos la entrada del usuario (teclado)
        glfwPollEvents();       // Manejamos los eventos de la ventana
        glfwSwapBuffers(window);// Intercambiamos el buffer de la ventana
    }

    // Cuando el programa termina, destruimos la ventana y finalizamos GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

// Función para configurar los vértices de un triángulo
void setUpVertices(void){
    // Array que contiene las coordenadas de los vértices del triángulo (x, y, z)
    float vertexPositions[9] = {
        -0.5f, -0.5f, 0.0f,    // Vértice 1: esquina inferior izquierda
         0.5f, -0.5f, 0.0f,    // Vértice 2: esquina inferior derecha
         0.0f,  0.5f, 0.0f     // Vértice 3: parte superior
    };

    // Generamos un VAO (Vertex Array Object) y lo asociamos
    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);

    // Generamos un VBO (Vertex Buffer Object) y lo asociamos al VAO
    glGenBuffers(1, vbo);    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

    // Enviamos los datos de los vértices al buffer de la GPU
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

    // Especificamos cómo se deben interpretar los datos del buffer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);  // Habilitamos el atributo de vértice en el layout 0
}

// Función para manejar la entrada del usuario
void processInput(GLFWwindow *window){
    // Si el usuario presiona la tecla Escape, cerramos la ventana
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// Función de callback para ajustar el viewport cuando se redimensiona la ventana
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);  // Ajustamos el viewport para que ocupe toda la ventana
}

// Función para crear el programa de shaders (vértice + fragmento)
GLuint createShaderProgram(){
    GLint vertCompiled;  // Variable para almacenar el estado de compilación del shader de vértices
    GLint fragCompiled;  // Variable para almacenar el estado de compilación del shader de fragmentos
    GLint linked;        // Variable para verificar si el linking fue exitoso

    // Creamos el shader de vértices y el de fragmentos
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Cargamos el código fuente en los shaders
    glShaderSource(vShader, 1, &vertexShaderSource, nullptr);
    glShaderSource(fShader, 1, &fragmentShaderSource, nullptr);

    // Compilamos el shader de vértices
    glCompileShader(vShader);
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
    if (vertCompiled != 1) {
        cout << "vertex compilation failed" << endl;
    }

    // Compilamos el shader de fragmentos
    glCompileShader(fShader);
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
    if (fragCompiled != 1) {
        cout << "fragment compilation failed" << endl;
    }

    // Creamos un programa y vinculamos los shaders compilados
    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);

    // Linkeamos el programa (combinamos los shaders en un programa ejecutable)
    glLinkProgram(vfProgram);
    glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
    if (linked != 1) {
        cout << "linking failed" << endl;
    }

    // Eliminamos los shaders una vez que ya fueron vinculados al programa
    glDeleteShader(vShader);
    glDeleteShader(fShader);

    return vfProgram;  // Devolvemos el programa de shaders creado
}