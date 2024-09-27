#pragma once
#include <glad/glad.h>
#include "../include/IMesh.hpp"
#include <vector>

class VertexMesh : public IMesh {
public:
    VertexMesh(std::vector<float> vertexPositions);
    ~VertexMesh();
    void setupMesh();
    void render();
private:
    unsigned int vao, vbo;
    std::vector<float> vertexPositions;
};
