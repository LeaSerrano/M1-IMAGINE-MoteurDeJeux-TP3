#include "Model.hpp"
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

class Entity : public Model {

    public : 
    Transform transform;

    Entity(std::vector<unsigned short> indices, std::vector<glm::vec3> indexed_vertices, std::vector<float> textureData) : Model(indices, indexed_vertices, textureData)
    {}

    std::list<std::unique_ptr<Entity>> children;
    Entity* parent = nullptr;

    template<typename... Targs>
    void addChild(const Targs&... args) {
        children.emplace_back(std::make_unique<Entity>(args...));
        children.back()->parent = this;
    }

    void updateSelfAndChild() {
        if (parent) {
            transform.modelMatrix = parent->transform.modelMatrix * transform.getLocalModelMatrix();
        }
        else {
            transform.modelMatrix = transform.getLocalModelMatrix();
        }

        for(auto&& child : children) {
            child->updateSelfAndChild();
        }
    }
};