#include <array>
#include <iostream>
class Resource {
private:
    std::vector<int> data;
    std::array<int, 10> data2;

public:
    // Constructor por defecto
    Resource();

    // Constructor con parámetro
    Resource(const std::vector<int>& vec);

    // Constructor de copia
    Resource(const Resource& other)= delete;

    // Constructor de movimiento
    Resource(Resource&& other) noexcept = delete;

    // Operador de asignación por copia
    Resource& operator=(const Resource& other);

    // Operador de asignación por movimiento
    Resource& operator=(Resource&& other) noexcept;

    // Destructor
    ~Resource();

    // Método para imprimir los valores del vector
    void print() const;

    // Método para agregar un valor al vector
    void addValue(int value);

    // Método para obtener el tamaño del vector
    size_t size() const;
};
