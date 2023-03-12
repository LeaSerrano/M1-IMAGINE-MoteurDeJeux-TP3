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

class SceneGraph : public Mesh {

    public : 
    Transform transform;

    /*SceneGraph(std::vector<unsigned short> indices, std::vector<glm::vec3> indexed_vertices, std::vector<float> textureData) : Model(indices, indexed_vertices, textureData)
    {}*/

    SceneGraph(std::string filename) : Mesh(filename) {}

    std::list<std::unique_ptr<SceneGraph>> children;
    SceneGraph* parent = nullptr;

    template<typename... Targs>
    void addChild(const Targs&... args) {
        children.emplace_back(std::make_unique<SceneGraph>(args...));
        children.back()->parent = this;
    }

    void update() {
        if (parent) {
            transform.modelMatrix = parent->transform.modelMatrix * transform.changeModelMatrix();
        }
        else {
            transform.modelMatrix = transform.changeModelMatrix();
        }

        for(auto&& child : children) {
            child->update();
        }
    }
};