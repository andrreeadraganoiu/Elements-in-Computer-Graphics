#pragma once
#include "components/simple_scene.h"

    class Duck
    {
    public:
        bool alive;
        bool escaped;
        glm::vec3 p1, p2, p3, p4;
   
        Duck();
        ~Duck();
        bool isKilled(float x, float y);
        float calculateArea(glm::vec3& p1, glm::vec3& p2, glm::vec3& p3);
    };
