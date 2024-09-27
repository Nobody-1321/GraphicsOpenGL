#include "../include/VertexMesh.hpp"

VertexMesh::VertexMesh(std::vector<float> vertexPositions) : vertexPositions(vertexPositions) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
}

VertexMesh::~VertexMesh() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void VertexMesh::setupMesh() {
    
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexPositions.size() * sizeof(float), &vertexPositions[0], GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}
//desactivar el vao
void VertexMesh::render() {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertexPositions.size() / 3);
    glBindVertexArray(0);
}

