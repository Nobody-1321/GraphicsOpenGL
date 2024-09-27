#define GLFW_EXPOSE_NATIVE_WIN32  // Exponer funciones de Windows
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>  // Para glfwGetWin32Window
#include <d3d11.h>
#include <d3dcompiler.h> 
#pragma comment (lib, "d3d11.lib")

IDXGISwapChain* swapChain;
ID3D11Device* dev;
ID3D11DeviceContext* devcon;
ID3D11RenderTargetView* backbuffer;


ID3D11VertexShader* vertexShader;
ID3D11PixelShader* pixelShader;
ID3D11InputLayout* inputLayout;

void InitShadersAndInputLayout() {
    // Cargar y compilar el Vertex Shader
    ID3DBlob* vsBlob;
    D3DCompileFromFile(L"vertex.hlsl", nullptr, nullptr, "main", "vs_5_0", 0, 0, &vsBlob, nullptr);
    dev->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &vertexShader);
    
    // Cargar y compilar el Pixel Shader
    ID3DBlob* psBlob;
    D3DCompileFromFile(L"pixel.hlsl", nullptr, nullptr, "main", "ps_5_0", 0, 0, &psBlob, nullptr);
    dev->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &pixelShader);
    
    // Definir el layout de entrada (Input Layout)
    D3D11_INPUT_ELEMENT_DESC layout[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    dev->CreateInputLayout(layout, 2, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &inputLayout);
    devcon->IASetInputLayout(inputLayout);
    
    vsBlob->Release();
    psBlob->Release();
}

// Vértices del triángulo
struct Vertex {
    float x, y, z;  // Posición
    float r, g, b;  // Color
};



ID3D11Buffer* vertexBuffer;

void InitD3D(HWND hwnd);
void Render();
void CleanD3D();
void InitGraphics();

int main() {
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);  // Deshabilitar API de gráficos de OpenGL/Vulkan
    GLFWwindow* window = glfwCreateWindow(800, 600, "DirectX con GLFW", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    HWND hwnd = glfwGetWin32Window(window);  // Obtener el HWND de la ventana de GLFW
    InitD3D(hwnd);  // Inicializar DirectX con la ventana
    InitGraphics(); // Inicializar los gráficos (triángulo)

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();  // Manejar eventos de GLFW
        Render();  // Renderizar la escena con DirectX
    }

    CleanD3D();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void InitD3D(HWND hwnd) {
    // Configuración del Swap Chain
    DXGI_SWAP_CHAIN_DESC scd = {0};
    scd.BufferCount = 1;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = hwnd;
    scd.SampleDesc.Count = 4; // Multisample count
    scd.Windowed = TRUE; // No pantalla completa

    // Crear el dispositivo y Swap Chain
    D3D11CreateDeviceAndSwapChain(0, D3D_DRIVER_TYPE_HARDWARE, 0, 0, 0, 0,
                                  D3D11_SDK_VERSION, &scd, &swapChain, &dev, 0, &devcon);

    // Crear Render Target (back buffer)
    ID3D11Texture2D* pBackBuffer;
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
    dev->CreateRenderTargetView(pBackBuffer, 0, &backbuffer);
    pBackBuffer->Release();

    // Configurar el viewport (800x600)
    D3D11_VIEWPORT viewport = {0};
    viewport.Width = 800;
    viewport.Height = 600;
    devcon->RSSetViewports(1, &viewport);
}

void InitGraphics() {
    Vertex vertices[] = {
        { 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f },  // Rojo
        { 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f },  // Verde
        {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f }   // Azul
    };

    // Crear y mapear el Vertex Buffer
    D3D11_BUFFER_DESC bd = {0};
    bd.Usage = D3D11_USAGE_DYNAMIC;
    bd.ByteWidth = sizeof(vertices);
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    dev->CreateBuffer(&bd, 0, &vertexBuffer);
    D3D11_MAPPED_SUBRESOURCE ms;
    devcon->Map(vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
    memcpy(ms.pData, vertices, sizeof(vertices));
    devcon->Unmap(vertexBuffer, 0);
}


void Render() {
    float color[4] = {0.55f, 0.2f, 0.4f, 1.0f}; // Fondo
    devcon->ClearRenderTargetView(backbuffer, color);

    // Configurar el Vertex Buffer y shaders
    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    devcon->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
    devcon->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    devcon->VSSetShader(vertexShader, 0, 0);
    devcon->PSSetShader(pixelShader, 0, 0);

    // Dibujar el triángulo
    devcon->Draw(3, 0);
    swapChain->Present(0, 0); // Intercambiar buffers
}

void CleanD3D() {
    // Liberar los recursos
    swapChain->Release();
    backbuffer->Release();
    dev->Release();
    devcon->Release();
    vertexBuffer->Release();
}
