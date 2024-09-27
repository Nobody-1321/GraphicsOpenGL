#pragma once
#include <glad/glad.h>
#include "../include/IMesh.hpp"
#include <vector>

class Mesh_VVT : public IMesh {
public:
    Mesh_VVT(std::vector<float> vertexPositions);
    ~Mesh_VVT();
    void setupMesh();
    void render() override;
private:
    unsigned int vao, vbo;
    std::vector<float> vertexPositions;
};
