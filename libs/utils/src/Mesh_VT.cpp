#include "../include/Mesh_VT.hpp"
//mesh with vertex and color

Mesh_VT::Mesh_VT(std::vector<float> vertexPositions) : vertexPositions(vertexPositions) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
}

Mesh_VT::~Mesh_VT() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void Mesh_VT::setupMesh() {
    
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexPositions.size() * sizeof(float), &vertexPositions[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 2,GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Mesh_VT::render() {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertexPositions.size() / 5);
}
