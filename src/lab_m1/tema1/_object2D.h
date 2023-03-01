#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace _object2D
{
    Mesh* CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner, float length, float width, glm::vec3 color, bool fill);
    Mesh* CreateCircle(std::string name, glm::vec3 center, float radius, glm::vec3 color, bool fill);
    Mesh* CreateTriangle(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
    Mesh* CreateDownTriangle(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
}
