#include "lab_m1/tema2/tema2.h"
#include "lab_m1/tema2/define.h"
#include <vector>
#include <string>
#include <iostream>
#include <math.h> 
#include <glm/gtc/random.hpp>

using namespace std;
using namespace m1;


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}

void Tema2::DrawGrass()
{
    vector<VertexFormat> grass_vertices;
    for (int i = -30; i <= 30; i++) {
        for (int j = -30; j <= 30; j++) {
            VertexFormat x = VertexFormat(glm::vec3(i, -0.1f, j), glm::vec3(1.f, 0.0f, 1.f), glm::vec3(0.0f, 0.8f, 0.4f));
            grass_vertices.push_back(x);
        }
    }
    vector<unsigned int> grass_indices;
    for (int i = 0; i < 3600; i++) {
        grass_indices.push_back((i + 1) % 3600);
        grass_indices.push_back(i % 3600);
        grass_indices.push_back((i + 31) % 3600);

        grass_indices.push_back((i + 1) % 3600);
        grass_indices.push_back((i + 31) % 3600);
        grass_indices.push_back((i + 32) % 3600);

    }
    meshes["grass"] = new Mesh("grass");
    meshes["grass"]->InitFromData(grass_vertices, grass_indices);
}

void Tema2::DrawTree()
{
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0, 0.3), glm::vec3(0, 1, 1), glm::vec3(0.21f, 0.31f, 0.f)),
            VertexFormat(glm::vec3(0.3, 0, 0.3), glm::vec3(0, 1, 1), glm::vec3(0.f, 0.39f, 0.f)),
            VertexFormat(glm::vec3(0, 0.3, 0.3), glm::vec3(0, 1, 1), glm::vec3(0.f, 0.39f, 0.f)),
            VertexFormat(glm::vec3(0.3, 0.3, 0.3), glm::vec3(0, 1, 1), glm::vec3(0.f, 0.39f, 0.f)),
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 1, 1), glm::vec3(0.f, 0.39f, 0.f)),
            VertexFormat(glm::vec3(0.3, 0, 0), glm::vec3(0, 1, 1), glm::vec3(0.f, 0.39f, 0.f)),
            VertexFormat(glm::vec3(0, 0.3, 0), glm::vec3(0, 1, 1), glm::vec3(0.f, 0.39f, 0.f)),
            VertexFormat(glm::vec3(0.3, 0.3, 0), glm::vec3(0, 1, 1), glm::vec3(0.f, 0.39f, 0.f))

        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4

        };

        meshes["tree_crown"] = new Mesh("tree_crown");
        meshes["tree_crown"]->InitFromData(vertices, indices);
    }

    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0, 0.1), glm::vec3(0, 1, 1), glm::vec3(0.42f, 0.31f, 0.f)),
            VertexFormat(glm::vec3(0.1, 0, 0.1), glm::vec3(0, 1, 1), glm::vec3(0.42f, 0.31f, 0.f)),
            VertexFormat(glm::vec3(0, 0.3, 0.1), glm::vec3(0, 1, 1), glm::vec3(0.42f, 0.31f, 0.f)),
            VertexFormat(glm::vec3(0.1, 0.3, 0.1), glm::vec3(0, 1, 1), glm::vec3(0.42f, 0.31f, 0.f)),
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 1, 1), glm::vec3(0.42f, 0.31f, 0.f)),
            VertexFormat(glm::vec3(0.1, 0, 0), glm::vec3(0, 1, 1), glm::vec3(0.42f, 0.31f, 0.f)),
            VertexFormat(glm::vec3(0, 0.3, 0), glm::vec3(0, 1, 1), glm::vec3(0.42f, 0.31f, 0.f)),
            VertexFormat(glm::vec3(0.1, 0.3, 0), glm::vec3(0, 1, 1), glm::vec3(0.42f, 0.31f, 0.f))


        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4

        };

        meshes["tree_trunk"] = new Mesh("tree_trunk");
        meshes["tree_trunk"]->InitFromData(vertices, indices);
    }
}

void Tema2::DrawCar(glm::vec3 color)
{
    vector<VertexFormat> verticess
    {
        VertexFormat(glm::vec3(0, 0, 0.1), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(0.2, 0, 0.1), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(0, 0.1, 0.1), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(0.2, 0.1, 0.1), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(0.2, 0, 0), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(0, 0.1, 0), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(0.2, 0.1, 0), glm::vec3(0, 1, 1), color)


    };

    vector<unsigned int> indicess =
    {
        0, 1, 2,
        1, 3, 2,
        2, 3, 7,
        2, 7, 6,
        1, 7, 3,
        1, 5, 7,
        6, 7, 4,
        7, 5, 4,
        0, 4, 1,
        1, 4, 5,
        2, 6, 4,
        0, 2, 4

    };

    string str;
    if (color == RED)
    {
        str = "_red";
    }
    else if (color == BLUE)
    {
        str = "_blue";
    }
    else
    {
        str = "_pink";
    }

    meshes["car" + str] = new Mesh("car" + str);
    meshes["car" + str]->InitFromData(verticess, indicess);
}

void Tema2::DrawScene()
{
    DrawGrass();
    DrawTree();
    DrawCar(RED);
    DrawCar(BLUE);
    DrawCar(PINK);

    for (int i = 0; i < road_points.size(); i++) 
    {
        glm::vec3 p1 = road_points[i];
        glm::vec3 p2 = road_points[(i + 1) % road_points.size()];

        glm::vec3 d = p2 - p1;
        glm::vec3 p = glm::cross(d, UP);
        p = glm::normalize(p);

        glm::vec3 road_int_p = p1 - road_internal_dist * p;
        glm::vec3 road_ext_p = p1 + road_external_dist * p;

        road_int_vertices.push_back(VertexFormat(road_int_p, glm::vec3(1.f, 0.1f, 1.0f), glm::vec3(0.82f, 0.82f, 0.82f)));
        road_ext_vertices.push_back(VertexFormat(road_ext_p, glm::vec3(1.f, 0.1f, 1.f), glm::vec3(0.82f, 0.82f, 0.82f)));

        glm::vec3 tree_int_p = p1 - tree_internal_dist * p;
        glm::vec3 tree_ext_p = p1 + tree_external_dist * p;

        trees_int_vertices.push_back(VertexFormat(tree_int_p, glm::vec3(1.f, 0.1f, 1.0f), glm::vec3(0.82f, 0.82f, 0.82f)));
        trees_ext_vertices.push_back(VertexFormat(tree_ext_p, glm::vec3(1.f, 0.1f, 1.f), glm::vec3(0.82f, 0.82f, 0.82f)));
    }

    
    for (int i = 0; i < road_points.size(); i++)
    {
        road_vertices.push_back(road_ext_vertices[i]);
        road_vertices.push_back(road_int_vertices[i]);
    }

 
    for (int i = 0; i < road_points.size() * 2 - 2; i++)
    {
        road_indices.push_back(i);
        road_indices.push_back((i + 1) % (road_points.size() * 2 - 2));
        road_indices.push_back((i + 3) % (road_points.size() * 2 - 2));

        road_indices.push_back(i);
        road_indices.push_back((i + 3) % (road_points.size() * 2 - 2));
        road_indices.push_back((i + 2) % (road_points.size() * 2 - 2));
    }

    meshes["road"] = new Mesh("road");
    meshes["road"]->InitFromData(road_vertices, road_indices);
}

void Tema2::Init()
{
    renderCameraTarget = false;
    int capacity = 10;

    vector<glm::vec3> fillingPoints = {};
    for (int i = 0; i < road_points.size(); i++)
    {
        glm::vec3 p1 = road_points[i];
        glm::vec3 p2 = road_points[(i + 1) % road_points.size()];
        glm::vec3 p = p2 - p1;
        for (int j = 0; j < capacity - 1; j++)
        {
            float factor = (j * 1.0f) / (capacity - 1);
            fillingPoints.push_back(p1 + (factor * p));
        }
    }

    road_points.clear();
    road_points = fillingPoints;

    for (int i = 0; i < 2; i++)
    {
        startPos[i] = rand() % road_points.size();
    }
  
    camera = new implemented::_Camera();
    camera->Set(glm::vec3(-3.0f, 0.9, 1.59054f), glm::vec3(CAR_X, 0.0f, CAR_Z), glm::vec3(0, 1, 0));
    projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, 0.01f, 200.0f);
    alpha = 0;
    DrawScene();
}


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::RenderScene()
{
    glm::mat4 modelMatrix = glm::mat4(1);
    RenderMesh(meshes["road"], shaders["VertexNormal"], modelMatrix);

    modelMatrix = glm::mat4(1);
    RenderMesh(meshes["grass"], shaders["VertexNormal"], modelMatrix);

    for (int i = 0; i < trees_ext_vertices.size(); i += 20) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= glm::translate(modelMatrix, glm::vec3(trees_ext_vertices[i].position));
        RenderMesh(meshes["tree_trunk"], shaders["VertexNormal"], modelMatrix);

        modelMatrix = glm::mat4(1);
        float x2 = -0.1f;
        float y2 = 0.3;
        float z2 = -0.1f;
        glm::vec3 v = glm::vec3(x2, y2, z2);
        modelMatrix *= glm::translate(modelMatrix, glm::vec3(trees_ext_vertices[i].position + v));
        RenderMesh(meshes["tree_crown"], shaders["VertexNormal"], modelMatrix);

    }

    for (int i = 0; i < trees_int_vertices.size(); i += 10) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= glm::translate(modelMatrix, glm::vec3(trees_int_vertices[i].position));
        RenderMesh(meshes["tree_trunk"], shaders["VertexNormal"], modelMatrix);

        modelMatrix = glm::mat4(1);
        float x2 = -0.1f;
        float y2 = 0.3;
        float z2 = -0.1f;
        glm::vec3 v = glm::vec3(x2, y2, z2);
        modelMatrix *= glm::translate(modelMatrix, glm::vec3(trees_int_vertices[i].position + v));
        RenderMesh(meshes["tree_crown"], shaders["VertexNormal"], modelMatrix);

    }
}

void Tema2::RenderCar()
{
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.78756f + x, 0.0f, 1.59054f + z));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.1, 0, 0.05));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(alpha), glm::vec3(0, 1, 0));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.1, 0, -0.05));
    RenderMesh(meshes["car_red"], shaders["VertexNormal"], modelMatrix);
}

void Tema2::DrawViewport(float deltaTimeSeconds)
{
    glClear(GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0.75f * resolution.x, 0, 0.25f * resolution.x, 0.25f * resolution.y);
    projectionMatrix = glm::ortho(-2.f, 2.f, -1.f, 1.f, 0.01f, 200.f);

    glm::vec3 camera_position = camera->position;
    glm::vec3 pos = camera->GetTargetPosition();
    camera->Set(pos + glm::vec3(0, 2, 0), pos, glm::vec3(0.f, 0.0f, 1.f));
    RenderScene();
    RenderCar();
    RenderOtherCar("blue", startPos[0], t0, deltaTimeSeconds);
    RenderOtherCar("pink", startPos[1], t1, deltaTimeSeconds);

    projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, 0.01f, 200.0f);
    camera->Set(camera_position, pos, glm::vec3(0, 1, 0));
}

void Tema2::RenderOtherCar(string color, int &startIdx, float &t,float deltaTimeSeconds)
{    
    glm::vec3 curPoint = road_points[(startIdx) % road_points.size()];
    glm::vec3 nextPoint = road_points[(startIdx + 1) % road_points.size()];

    glm::vec3 position = glm::vec3((1 - t) * curPoint.x + t * nextPoint.x,
                                   0.f,
                                   (1 - t) * curPoint.z + t * nextPoint.z);
    t = t + 1.5 * deltaTimeSeconds;
    if (curPoint.x + t >= nextPoint.x) {
        t = 0;
        startIdx++;
    }

    glm::vec3 dir = glm::normalize(nextPoint - curPoint);

    float angleR = atan2(dir.x, dir.z);
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, position)
        * glm::rotate(modelMatrix, angleR + RADIANS(90), glm::vec3(0.0f, 1.f, 0.0f));
    RenderMesh(meshes["car_" + color], shaders["VertexNormal"], modelMatrix);

}

void Tema2::Update(float deltaTimeSeconds)
{
    RenderOtherCar("blue", startPos[0], t0, deltaTimeSeconds);
    RenderOtherCar("pink", startPos[1], t1, deltaTimeSeconds);
    
    RenderScene();
    RenderCar();
    DrawViewport(deltaTimeSeconds);
}


void Tema2::FrameEnd()
{
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Tema2::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}

float Tema2::CalculateArea(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
    return 0.5f * abs((p1.x * (p2.z - p3.z) + p2.x * (p3.z - p1.z) + p3.x * (p1.z - p2.z)));
}

bool Tema2::isOnRoad(glm::vec3 position)
{
    for (int i = 0; i < road_points.size(); i++)
    {
        glm::vec3 p1 = road_ext_vertices[i].position;
        glm::vec3 p2 = road_int_vertices[i].position;
        glm::vec3 p3 = road_ext_vertices[(i + 1) % road_points.size()].position;
        glm::vec3 p4 = road_int_vertices[(i + 1) % road_points.size()].position;

        float area1 = CalculateArea(p2, p3, p4) + CalculateArea(p1, p3, p4);
        float area2 = CalculateArea(position, p1, p2) + CalculateArea(position, p1, p3) +
            CalculateArea(position, p3, p4) + CalculateArea(position, p4, p2);
      

        if (fabs(area1 - area2) < 0.04f)
        {
            return true;
        }
    }
    return false;
}

bool Tema2::isCarHit()
{
    glm::vec3 position = glm::vec3(CAR_X - 0.1f + x,
                                   0.0f,
                                   CAR_Z - 0.05f + z);
    for (int i = 0; i < 2; i++)
    {
        if (glm::distance(position, road_points[startPos[i] % road_points.size()]) < 0.3f)
        {
            return true;
        }
    }
    
    return false;
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{

    float cameraSpeed = 2.0f;
    v = 2 * deltaTime;

    if (isCarHit())
    {
        return;
    }


    if (window->KeyHold(GLFW_KEY_W)) {
        glm::vec3 position = glm::vec3(CAR_X - 0.1f + x + v * cos(RADIANS(alpha)),
            0.0f,
            CAR_Z - 0.05f + z - v * sin(RADIANS(alpha)));

        if (isOnRoad(position) == true)
        {
            camera->MoveForward(cameraSpeed * deltaTime);
            x += v * cos(RADIANS(alpha));
            z -= v * sin(RADIANS(alpha));
        }

    }

    if (window->KeyHold(GLFW_KEY_A)) {

        camera->RotateThirdPerson_OY(RADIANS(deltaTime * ROT_SPEED));
        alpha += deltaTime * ROT_SPEED;
    }

    if (window->KeyHold(GLFW_KEY_S)) {
        glm::vec3 position = glm::vec3(CAR_X - 0.1 + x - v * cos(RADIANS(alpha)),
            0.0f,
            CAR_Z - 0.05 + z + v * sin(RADIANS(alpha)));

        if (isOnRoad(position) == true)
        {
            camera->MoveForward(-cameraSpeed * deltaTime);
            x -= v * cos(RADIANS(alpha));
            z += v * sin(RADIANS(alpha));
        }

    }

    if (window->KeyHold(GLFW_KEY_D)) {

        camera->RotateThirdPerson_OY(RADIANS(-deltaTime * ROT_SPEED));
        alpha -= deltaTime * ROT_SPEED;

    }

    if (window->KeyHold(GLFW_KEY_Q)) {

        camera->TranslateUpward(-cameraSpeed * deltaTime);
    }

    if (window->KeyHold(GLFW_KEY_E)) {

        camera->TranslateUpward(cameraSpeed * deltaTime);
    }

}
    

void Tema2::OnKeyPress(int key, int mods)
{
    
    if (key == GLFW_KEY_T)
    {
        renderCameraTarget = !renderCameraTarget;
    }

}


void Tema2::OnKeyRelease(int key, int mods)
{
    
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
   
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
   
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
