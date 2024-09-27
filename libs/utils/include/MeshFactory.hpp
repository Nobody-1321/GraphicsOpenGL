#pragma once
#include "IMesh.hpp"
#include <memory>
#include <map>
#include <functional>
#include <iostream>

class MeshFactory {
public:
    // Función para registrar nuevos tipos de mallas
    void registerMeshType(const std::string& typeName, std::function<std::unique_ptr<IMesh>()> creator);

    // Función para crear una malla basada en el nombre del tipo
    std::unique_ptr<IMesh> createMesh(const std::string& typeName);

private:
    // Mapa que asocia nombres de tipo con funciones de creación
    std::map<std::string, std::function<std::unique_ptr<IMesh>()>> meshFactoryMap;
};
