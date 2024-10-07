#pragma once
#include <glad/glad.h>
#include <vector>
#include <filesystem>
#include <glm/glm.hpp>
#include <bitset>
#include <IMesh.hpp>

constexpr int MAX_COMPONENTS = 32;

using EntityID = unsigned int;
using ComponentType = unsigned int;

// Componente Transform para manejar la posición, rotación y escala de la entidad
struct Transform {
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    Transform() = default;
    Transform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scl)
        : position{pos}, rotation{rot}, scale{scl} {}
};

// Componente Mesh para almacenar los datos de los vértices, normales y coordenadas de textura
struct Mesh {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords;
};

// Componente Shader para gestionar los shaders del objeto
struct Shader {
    const unsigned int shaderProgram{0};
    const std::filesystem::path vertexShaderPath;
    const std::filesystem::path fragmentShaderPath;

    Shader() = default;

    // Constructor con el programa shader
    Shader(unsigned int shaderProgram, const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
        : shaderProgram{shaderProgram}, vertexShaderPath(vertexPath), fragmentShaderPath(fragmentPath) {}

    // Liberar recursos de OpenGL en el destructor
    ~Shader() {
        if (shaderProgram != 0) {
            glDeleteProgram(shaderProgram);
        }
    }
};

// Componente para manejar la cámara en la escena
struct Camera {
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
};

// Componente para la entidad, utilizando un identificador seguro
struct Entity {
    EntityID id;

    Entity(unsigned int entityID) : id{EntityID{entityID}} {}
};

// Máscara de componentes que tiene una entidad
struct EntityComponentMask {
    std::bitset<MAX_COMPONENTS> components;
};

// Sistema de componentes
/*class ECSManager {
private:
    std::unordered_map<EntityID, EntityComponentMask> entityComponentMasks;
    std::unordered_map<EntityID, Transform> transforms;
    std::unordered_map<EntityID, Mesh> meshes;

public:
    // Registrar un componente para una entidad
    void addComponent(EntityID entity, ComponentType type) {
        entityComponentMasks[entity].components.set(type);
    }

    // Agregar un Transform a una entidad
    void addTransform(EntityID entity, const Transform& transform) {
        transforms[entity] = transform;
        addComponent(entity, 0); // El componente 0 representa Transform
    }

    // Agregar un Mesh a una entidad
    void addMesh(EntityID entity, const Mesh& mesh) {
        meshes[entity] = mesh;
        addComponent(entity, 1); // El componente 1 representa Mesh
    }

    // Verificar si una entidad tiene un componente específico
    bool hasComponent(EntityID entity, ComponentType type) {
        return entityComponentMasks[entity].components.test(type);
    }

    // Obtener Transform de una entidad si existe
    Transform* getTransform(EntityID entity) {
        if (hasComponent(entity, 0)) {
            return &transforms[entity];
        }
        return nullptr;
    }

    // Obtener Mesh de una entidad si existe
    Mesh* getMesh(EntityID entity) {
        if (hasComponent(entity, 1)) {
            return &meshes[entity];
        }
        return nullptr;
    }
};
*/