#ifndef SINGLETON_HPP
#define SINGLETON_HPP

class Singleton {
public:
    // Proporciona acceso global a la única instancia
    static Singleton& getInstance();

    // Ejemplo de método de la clase Singleton
    void doSomething();

    // Eliminar los métodos de copia y asignación para evitar duplicación
    Singleton(const Singleton&) = delete; // Prohíbe la copia
    Singleton& operator=(const Singleton&) = delete; // Prohíbe la asignación

private:
    // Constructor privado para evitar creación directa de objetos
    Singleton();

    // Destructor privado opcional
    ~Singleton();
};

#endif // SINGLETON_HPP
