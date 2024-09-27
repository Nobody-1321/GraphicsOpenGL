#include "../include/Mesh_VV.hpp"
//mesh with vertex and color

Mesh_VV::Mesh_VV(std::vector<float> vertexPositions) : vertexPositions(vertexPositions) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
}

Mesh_VV::~Mesh_VV() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void Mesh_VV::setupMesh() {
    
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexPositions.size() * sizeof(float), &vertexPositions[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3,GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Mesh_VV::render() {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertexPositions.size() / 6);
}