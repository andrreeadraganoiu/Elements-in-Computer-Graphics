#include "lab_m1/tema1/_object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* _object2D::CreateRectangle(const std::string& name, glm::vec3 corner, float length, 
                               float width, glm::vec3 color, bool fill)
{

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, width, 0), color),
        VertexFormat(corner + glm::vec3(0, width, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* _object2D::CreateCircle(std::string name, glm::vec3 center, float radius, glm::vec3 color, bool fill) {

    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;
    int triangleCount = 100;

    for (int i = 0; i < triangleCount; i++) {
        vertices.push_back(VertexFormat(glm::vec3(center[0] + radius * cos(2 * M_PI / triangleCount * i), 
                           center[1] + radius * sin(2 * M_PI / triangleCount * i), 0), color));
        indices.push_back(i);
    }

    indices.push_back(0);

    Mesh* circle = new Mesh(name);

    circle->SetDrawMode(GL_TRIANGLE_FAN);

    circle->InitFromData(vertices, indices);
    return circle;
}

Mesh* _object2D::CreateDownTriangle(const std::string& name, glm::vec3 corner, 
                                  float length, glm::vec3 color,bool fill)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 3 * length, 0), color),
        VertexFormat(corner + glm::vec3(-length, 3 * length, 0), color),
    };

    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2 };

    triangle->InitFromData(vertices, indices);
    return triangle;
}

Mesh* _object2D::CreateTriangle(const std::string& name, glm::vec3 corner, 
                              float length, glm::vec3 color, bool fill)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(0, 3 * length, 0), color),
        VertexFormat(corner + glm::vec3(-length, 0, 0), color),
    };

    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2 };

    triangle->InitFromData(vertices, indices);
    return triangle;
}