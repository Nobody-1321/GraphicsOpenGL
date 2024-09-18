#include "Singleton.hpp"
#include <iostream>

// Implementación del método estático para obtener la instancia
Singleton& Singleton::getInstance() {
    static Singleton instance; // Instancia única que se crea la primera vez
    return instance;
}

// Constructor privado
Singleton::Singleton() {
    std::cout << "Singleton creado." << std::endl;
}

// Destructor privado opcional
Singleton::~Singleton() {
    std::cout << "Singleton destruido." << std::endl;
}

// Ejemplo de un método de la clase Singleton
void Singleton::doSomething() {
    std::cout << "Haciendo algo en el Singleton." << std::endl;
}
