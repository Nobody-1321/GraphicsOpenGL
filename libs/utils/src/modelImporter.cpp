#include "../include/modelImporter.hpp"

ModelImporter::ModelImporter() {}


void ModelImporter::parseObjFile(const char* path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v") {
            float x, y, z;
            ss >> x >> y >> z;
            vertVals.push_back(x);
            vertVals.push_back(y);
            vertVals.push_back(z);
        } else if (prefix == "vt") {
            float u, v;
            ss >> u >> v;
            texCoordVals.push_back(u);
            texCoordVals.push_back(v);
        } else if (prefix == "vn") {
            float nx, ny, nz;
            ss >> nx >> ny >> nz;
            normVals.push_back(nx);
            normVals.push_back(ny);
            normVals.push_back(nz);
        }
        else if (prefix == "f")
        {
            std::vector<unsigned int> vertIdx, texIdx, normIdx;
            char slash;
            std::string vertex;

            // Leer todos los vértices de la cara
            while (ss >> vertex)
            {
                std::stringstream vertexSS(vertex);
                unsigned int vIdx, tIdx, nIdx;
                vertexSS >> vIdx >> slash >> tIdx >> slash >> nIdx;

                vertIdx.push_back(vIdx);
                texIdx.push_back(tIdx);
                normIdx.push_back(nIdx);
            }

            // Comprobar si la cara tiene más de tres vértices (cuadrilátero)
            if (vertIdx.size() == 4)
            {
                unsigned int tri1[3] = {vertIdx[0], vertIdx[1], vertIdx[2]};
                unsigned int tri2[3] = {vertIdx[0], vertIdx[2], vertIdx[3]};

                // Primer triángulo
                for (int i = 0; i < 3; ++i)
                {
                    triangleVerts.push_back(vertVals[(tri1[i] - 1) * 3]);
                    triangleVerts.push_back(vertVals[(tri1[i] - 1) * 3 + 1]);
                    triangleVerts.push_back(vertVals[(tri1[i] - 1) * 3 + 2]);

                    textureCoords.push_back(texCoordVals[(texIdx[i] - 1) * 2]);
                    textureCoords.push_back(texCoordVals[(texIdx[i] - 1) * 2 + 1]);

                    normals.push_back(normVals[(normIdx[i] - 1) * 3]);
                    normals.push_back(normVals[(normIdx[i] - 1) * 3 + 1]);
                    normals.push_back(normVals[(normIdx[i] - 1) * 3 + 2]);
                }

                // Segundo triángulo
                for (int i = 0; i < 3; ++i)
                {
                    triangleVerts.push_back(vertVals[(tri2[i] - 1) * 3]);
                    triangleVerts.push_back(vertVals[(tri2[i] - 1) * 3 + 1]);
                    triangleVerts.push_back(vertVals[(tri2[i] - 1) * 3 + 2]);

                    textureCoords.push_back(texCoordVals[(texIdx[i] - 1) * 2]);
                    textureCoords.push_back(texCoordVals[(texIdx[i] - 1) * 2 + 1]);

                    normals.push_back(normVals[(normIdx[i] - 1) * 3]);
                    normals.push_back(normVals[(normIdx[i] - 1) * 3 + 1]);
                    normals.push_back(normVals[(normIdx[i] - 1) * 3 + 2]);
                }
            }
            else
            {
                // Cara triangular
                for (int i = 0; i < 3; ++i)
                {
                    triangleVerts.push_back(vertVals[(vertIdx[i] - 1) * 3]);
                    triangleVerts.push_back(vertVals[(vertIdx[i] - 1) * 3 + 1]);
                    triangleVerts.push_back(vertVals[(vertIdx[i] - 1) * 3 + 2]);

                    textureCoords.push_back(texCoordVals[(texIdx[i] - 1) * 2]);
                    textureCoords.push_back(texCoordVals[(texIdx[i] - 1) * 2 + 1]);

                    normals.push_back(normVals[(normIdx[i] - 1) * 3]);
                    normals.push_back(normVals[(normIdx[i] - 1) * 3 + 1]);
                    normals.push_back(normVals[(normIdx[i] - 1) * 3 + 2]);
                }
            }
        }
    }

    file.close();
}

void ModelImporter::parseObjFileVer(const char* path){
        std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string prefix;
        ss >> prefix;

        // Procesar los vértices (líneas que empiezan con "v")
        if (prefix == "v") {
            float x, y, z;
            ss >> x >> y >> z;
            vertVals.push_back(x);
            vertVals.push_back(y);
            vertVals.push_back(z);
        }
        // Procesar las caras (líneas que empiezan con "f")
        else if (prefix == "f") {
            unsigned int vertIdx[3];
            // Leer tres índices de vértices para formar un triángulo
            for (int i = 0; i < 3; ++i) {
                ss >> vertIdx[i];
            }

            // Convertir los índices a coordenadas de vértices
            for (int i = 0; i < 3; ++i) {
                unsigned int idx = vertIdx[i] - 1; // Los índices en OBJ empiezan desde 1
                triangleVerts.push_back(vertVals[idx * 3]);
                triangleVerts.push_back(vertVals[idx * 3 + 1]);
                triangleVerts.push_back(vertVals[idx * 3 + 2]);
            }
        }
    }

    file.close();
}

int ModelImporter::getNumVertices() {
    return triangleVerts.size() / 3;
}

std::vector<float> ModelImporter::getVertices() {
    return triangleVerts;
}

std::vector<float> ModelImporter::getTexCoords() {
    return textureCoords;
}

std::vector<float> ModelImporter::getNormals() {
    return normals;
}