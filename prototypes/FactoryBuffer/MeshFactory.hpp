#pragma once
#include "Mesh.hpp"
#include <memory>
#include <map>
#include <functional>
#include <iostream>

class MeshFactory {
public:
    // Función para registrar nuevos tipos de mallas
    void registerMeshType(const std::string& typeName, std::function<std::unique_ptr<Mesh>()> creator) {
        meshFactoryMap[typeName] = creator;
    }

    // Función para crear una malla basada en el nombre del tipo
    std::unique_ptr<Mesh> createMesh(const std::string& typeName) {
        auto it = meshFactoryMap.find(typeName);
        if (it != meshFactoryMap.end()) {
            return it->second();  // Ejecuta el callback de creación
        }
        throw std::runtime_error("Mesh type not registered.");
    }

private:
    // Mapa que asocia nombres de tipo con funciones de creación
    std::map<std::string, std::function<std::unique_ptr<Mesh>()>> meshFactoryMap;
};
