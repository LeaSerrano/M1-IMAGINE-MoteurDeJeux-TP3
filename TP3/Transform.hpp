#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

class Transform {

    public :

    glm::vec3 rotation = {0.0f, 0.0f, 0.0f};
    glm::vec3 scale = {1.0f, 1.0f, 1.0f};
    glm::vec3 position = {0.0f, 0.0f, 0.0f};

    glm::mat4 modelMatrix = glm::mat4(1.0f);

    //bool needUpdate = true;

    glm::mat4 changeModelMatrix() {
        glm::mat4 transformX = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 transformY = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

        glm::mat4 rotationMatrix = transformX * transformY * transformZ;

        return glm::translate(glm::mat4(1.0f), position) * rotationMatrix * glm::scale(glm::mat4(1.0f), scale);
    }
    
    /*void apply(glm::vec4 p) {

    }

    glm::vec3 applyToPoint(glm::vec3 p) {

    }

    glm::vec3 applyToVector(glm::vec3 p) {

    }

    glm::vec3 applyToVector(glm::vec3 p) {

    }*/

    /*void getModelMatrixWithoutUpdating() {
        modelMatrix = changeModelMatrix();
        needUpdate = false;
    } 

    void combineWith(glm::mat4 &mat) {
        modelMatrix = changeModelMatrix() * mat;
        needUpdate = false;
    }

    void setPosition(const glm::vec3& p) {
        position = p;
        needUpdate = true;
    }

    void setScale(const glm::vec3& s) {
        scale = s;
        needUpdate = true;
    }

    void setRotation(const glm::vec3& r) {
        rotation = r;
        needUpdate = true;
    }

    glm::vec3& getPosition() {
        return position;
    }

    glm::vec3& getScale() {
        return scale;
    }

    glm::vec3& getRotation() {
        return rotation;
    }

    glm::mat4& getModelMatrix() {
        return modelMatrix;
    }

    bool transformNeedUpdate() {
        return needUpdate;
    }*/

    /*Transform inverse() {
        
    }

    Transform interpolateWith(Transform &t, float k) {

    }*/

};