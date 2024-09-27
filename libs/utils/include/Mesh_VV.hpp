#pragma once
#include <glad/glad.h>
#include "../include/IMesh.hpp"
#include <vector>

class Mesh_VV : public IMesh {
public:
    Mesh_VV(std::vector<float> vertexPositions);
    ~Mesh_VV();
    void setupMesh();
    void render() override;
private:
    unsigned int vao, vbo;
    std::vector<float> vertexPositions;
};
