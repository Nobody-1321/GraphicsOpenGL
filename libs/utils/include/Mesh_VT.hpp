#pragma once
#include <glad/glad.h>
#include "../include/IMesh.hpp"
#include <vector>

class Mesh_VT : public IMesh {
public:
    Mesh_VT(std::vector<float> vertexPositions);
    ~Mesh_VT();
    void setupMesh();
    void render() override;
private:
    unsigned int vao, vbo;
    std::vector<float> vertexPositions;
};
