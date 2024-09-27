#pragma once
#include <glad/glad.h>
#include "../include/IMesh.hpp"
#include <vector>

class Mesh : public IMesh {
public:
    Mesh(std::vector<float> vertexPositions);
    ~Mesh();
    void setupMesh();
    void render() override;
private:
    unsigned int vao, vbo;
    std::vector<float> vertexPositions;
};
