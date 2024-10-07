#pragma once

#include "componentStruct.hpp"
#include <memory>

class ComponentCreator
{
    public:
    //intelligent pointer Shader
    static std::unique_ptr<Shader> createShaderComponent(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);
    
    //static std::unique_ptr<Mesh> createMeshComponent(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, const std::vector<glm::vec2>& texCoords);
    //static Transform createTransform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scl);
    //static Mesh createMesh(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, const std::vector<glm::vec2>& texCoords);
    //static Camera createCamera(const glm::vec3& cameraPos, const glm::vec3& cameraFront, const glm::vec3& cameraUp);
    //static Entity createEntity(unsigned int entityID);
};

