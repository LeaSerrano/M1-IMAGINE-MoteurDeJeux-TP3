#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

struct Transform {


    glm::vec3 pos = {0.0f, 0.0f, 0.0f};
    glm::vec3 eulerRot = {0.0f, 0.0f, 0.0f};
    glm::vec3 scale = {1.0f, 1.0f, 1.0f};

    glm::mat4 modelMatrix = glm::mat4(1.0f);

    glm::mat4 getLocalModelMatrix() {
        const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f), glm::radians(eulerRot.x), glm::vec3(1.0f, 0.0f, 0.0f));
        const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f), glm::radians(eulerRot.y), glm::vec3(0.0f, 1.0f, 0.0f));
        const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f), glm::radians(eulerRot.z), glm::vec3(0.0f, 0.0f, 1.0f));

        const glm::mat4 rotationMatrix = transformX * transformY * transformZ;

        return glm::translate(glm::mat4(1.0f), pos) * rotationMatrix * glm::scale(glm::mat4(1.0f), scale);
    }

};