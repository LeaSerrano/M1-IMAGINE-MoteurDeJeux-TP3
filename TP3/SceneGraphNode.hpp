#include "Mesh.hpp"
#include "Transform.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <list>
#include <memory>

class SceneGraphNode : public Mesh {

    public : 
    Transform transform;

    SceneGraphNode(std::string filename, bool isATexturedMesh) : Mesh(filename, isATexturedMesh) {}

    SceneGraphNode(std::vector<glm::vec3> indexed_vertices, std::vector<float> textureData, std::vector<unsigned short> indices, bool isATexturedMesh) : Mesh(indexed_vertices, textureData, indices, isATexturedMesh) {}

    std::vector<SceneGraphNode*> children;
    SceneGraphNode* parent = nullptr;

    void addChild(SceneGraphNode* child) {
        children.push_back(child);
        child->parent = this;
    }

    void update() {
        if (parent) {
            transform.modelMatrix = parent->transform.modelMatrix * this->transform.changeModelMatrix();
        }
        else {
            transform.modelMatrix = this->transform.changeModelMatrix();
        }

        for (SceneGraphNode* child : this->children) {
            child->update();
        }
    }

    void drawScene(GLuint programID) {
        for (SceneGraphNode* childNode : this->children) {
            childNode->sendDatas();
            childNode->drawMesh(programID);
        }
    }

    void updateScene(std::vector<glm::vec3> indexed_vertices, std::vector<float> textureData, std::vector<unsigned short> indices) {
        for (SceneGraphNode* childNode : this->children) {
            childNode->updateMeshData(indexed_vertices, textureData, indices);
        }
    }

    void deleteBuffer() {
        for (SceneGraphNode* childNode : this->children) {
            childNode->deleteBuffer();
        }
    }
};