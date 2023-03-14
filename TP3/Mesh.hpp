#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <common/texture.hpp>

#include <GL/glew.h>

#include <GLFW/glfw3.h>


class Mesh {
    public :

    GLuint vertexbuffer;
    GLuint elementbuffer;
    GLuint textureBuffer;

    bool isGrassTextureAlreadyImported = false;
    bool isRockTextureAlreadyImported = false;
    bool isSnowrocksTextureAlreadyImported = false;
    bool isHeightMapTextureAlreadyImported = false;

    std::vector<glm::vec3> indexed_vertices;
    std::vector<std::vector<unsigned short> > triangles;
    std::vector<float> textureData;

    std::vector<unsigned short> indices;

    bool isATexturedMesh;

    Mesh(std::string filename, bool isATexturedMesh) {
        loadOFF(filename, indexed_vertices, indices, triangles );
        this->isATexturedMesh = isATexturedMesh;
    }

    Mesh(std::vector<glm::vec3> indexed_vertices, std::vector<float> textureData, std::vector<unsigned short> indices, bool isATexturedMesh) {
        this->isATexturedMesh = isATexturedMesh;
        this->indexed_vertices = indexed_vertices;
        this->textureData = textureData;
        this->indices = indices;
    }


    void sendDatas() {
        glGenBuffers(1, &vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &elementbuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0] , GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                    0,                  // attribute
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*)0            // array buffer offset
                    );

        if (isATexturedMesh) {
            glGenBuffers(1, &textureBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
            glBufferData(GL_ARRAY_BUFFER, textureData.size() * sizeof(float), &textureData[0], GL_STATIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
            glEnableVertexAttribArray(1);
        }

    }


    void drawMesh(GLuint programID) {
        if (isATexturedMesh) {
            if (!isGrassTextureAlreadyImported) {
                glActiveTexture(GL_TEXTURE0);
                loadBMP_custom("grass.bmp");
                glUniform1i(glGetUniformLocation(programID, "grassTexture"), 0);

                isGrassTextureAlreadyImported = true;
            }

            if (!isRockTextureAlreadyImported) {
                glActiveTexture(GL_TEXTURE1);
                loadBMP_custom("rock.bmp");
                glUniform1i(glGetUniformLocation(programID, "rockTexture"), 1);

                isRockTextureAlreadyImported = true;
            }

            if (!isSnowrocksTextureAlreadyImported) {
                glActiveTexture(GL_TEXTURE2);
                loadBMP_custom("snowrocks.bmp");
                glUniform1i(glGetUniformLocation(programID, "snowrocksTexture"), 2);

                isSnowrocksTextureAlreadyImported = true;
            }

            if (!isHeightMapTextureAlreadyImported) {
                glActiveTexture(GL_TEXTURE3);
                loadBMP_custom("Heightmap_Mountain.bmp");
                glUniform1i(glGetUniformLocation(programID, "textureCoords"), 3);

                isHeightMapTextureAlreadyImported = true;
            }
        }

        glDrawElements(
                    GL_TRIANGLES,      // mode
                    this->indices.size(),    // count
                    GL_UNSIGNED_SHORT,   // type
                    (void*)0           // element array buffer offset
                    );
        
    }

    void deleteMeshBuffers() {
        glDeleteBuffers(1, &vertexbuffer);
        glDeleteBuffers(1, &elementbuffer);
        glDeleteBuffers(1, &textureBuffer);
    }

    void updateMeshData(std::vector<glm::vec3> newIndexedVertices, std::vector<float> newTextureData, std::vector<unsigned short> newIndices) {
        this->indexed_vertices = newIndexedVertices;
        this->textureData = newTextureData;
        this->indices = newIndices;
    }
};