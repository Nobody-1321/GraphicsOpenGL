#define GLFW_INCLUDE_NONE  // Evita la inclusión de cabeceras de OpenGL
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Utils.hpp>
#include <cmath>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
using namespace std;

int main()
{
    // Inicializa GLFW
    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    // Configura las opciones de la ventana GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Crea la ventana GLFW
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    GLFWwindow *window = glfwCreateWindow(700, 700, "Hello Mix Texture", nullptr, nullptr);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Inicializa GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Configura el tamaño del viewport
    glViewport(0, 0, 700, 700);

    // Inicializa ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Habilitar controles de teclado
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Habilitar controles de Gamepad


    //ImGui::StyleColorsDark(); // Configura el estilo de ImGui
    //ImGui::StyleColorsClassic(); // Configura el estilo de ImGui
    ImGui::StyleColorsLight(); // Configura el estilo de ImGui

    // Configura el backend de ImGui para OpenGL y GLFW
    ImGui_ImplGlfw_InitForOpenGL(window, true); // El segundo parámetro install_callback = true instalará callbacks de GLFW
    ImGui_ImplOpenGL3_Init("#version 430");     // Asegúrate de pasar la versión de GLSL correcta

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        

    // Bucle principal
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Inicio del frame de ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Muestra una ventana simple que creamos nosotros mismos. Usamos un par Begin/End para crear una ventana con nombre.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!"); // Crea una ventana llamada "Hello, world!" y la agrega.

            ImGui::Text("This is some useful text.");          // Muestra algún texto (también se pueden usar strings formateados)
            ImGui::Checkbox("Demo Window", &show_demo_window); // Edita los booleanos guardando el estado abrierto/cerrado
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);             // Edita 1 números flotante usando un control deslizante de 0.0f a 1.0f
            ImGui::ColorEdit3("clear color", (float *)&clear_color); // Edita 3 números flotantes representando un color

            if (ImGui::Button("Button")) // Los botones devuelven verdadero cuando se hace clic en ellos (la mayoría de los widgets devuelven verdadero cuando se editan/activan)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        // 3. Muestra otra ventana de ejemplo.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window); // Pasa un puntero a nuestra variable booleana (la ventana tendrá un botón de cierre que borrará el booleano cuando se haga clic)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        } // Ejemplo de interfaz simple en ImGui

        // Renderiza la UI de ImGui
        ImGui::Render();
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Intercambia buffers
        glfwSwapBuffers(window);
    }

    // Limpiar recursos al finalizar
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
