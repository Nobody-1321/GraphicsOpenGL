#pragma once

class Mesh {
public:
    unsigned int vao, vbo;

    Mesh() {
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
    }

    virtual ~Mesh() {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
    }

    virtual void setupMesh() = 0;

    virtual void render() {
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 36); 
    }
};
