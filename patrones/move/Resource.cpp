#include <iostream>
#include <vector>
#include "Resource.hpp"  // Incluir el archivo de cabecera correspondiente

// Constructor por defecto
Resource::Resource() {
    std::cout << "Constructor por defecto llamado. Vector vacío asignado." << std::endl;
}

// Constructor con parámetro
Resource::Resource(const std::vector<int>& vec) : data(vec) {
    std::cout << "Constructor con parámetro llamado. Vector copiado." << std::endl;
}

// Constructor de copia
Resource::Resource(const Resource& other) : data(other.data) {
    std::cout << "Constructor de copia llamado. Vector copiado." << std::endl;
}

// Constructor de movimiento
Resource::Resource(Resource&& other) noexcept : data(std::move(other.data)) {
    std::cout << "Constructor de movimiento llamado. Vector movido." << std::endl;
}

// Operador de asignación por copia
Resource& Resource::operator=(const Resource& other) {
    if (this == &other) {
        return *this;  // Manejo de autoasignación
    }
    data = other.data;  // Copia el vector
    std::cout << "Operador de asignación por copia llamado." << std::endl;
    return *this;
}

// Operador de asignación por movimiento
Resource& Resource::operator=(Resource&& other) noexcept {
    if (this == &other) {
        return *this;  // Manejo de autoasignación
    }
    data = std::move(other.data);  // Transfiere la propiedad del vector
    std::cout << "Operador de asignación por movimiento llamado." << std::endl;
    return *this;
}

// Destructor
Resource::~Resource() {
    std::cout << "Destructor llamado. Liberando recurso (vector)." << std::endl;
}

// Método para imprimir los valores del vector
void Resource::print() const {
    std::cout << "Valores del vector: ";
    for (const auto& val : data) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

// Método para agregar un valor al vector
void Resource::addValue(int value) {
    data.push_back(value);
}

// Método para obtener el tamaño del vector
size_t Resource::size() const {
    return data.size();
}
