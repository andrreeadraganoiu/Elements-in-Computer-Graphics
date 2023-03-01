#pragma once

#include "components/simple_scene.h"
#include "lab_m1/tema2/lab_camera.h"

using namespace std;

namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
     public:
         Tema2();
        ~Tema2();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;
        void RenderMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix) override;
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        void DrawScene();
        void DrawGrass();
        void DrawTree();
        void DrawCar(glm::vec3 color);
        void DrawViewport(float deltaTimeSeconds);
        void RenderScene();
        void RenderCar();
        void RenderOtherCar(string color, int &startIdx, float &t, float deltaTimeSeconds);
        bool isOnRoad(glm::vec3 position);
        bool isCarHit();
        float CalculateArea(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);

     protected:
        implemented::_Camera *camera;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;

        vector<VertexFormat> road_int_vertices;
        vector<VertexFormat> road_ext_vertices;
        vector<VertexFormat> trees_int_vertices;
        vector<VertexFormat> trees_ext_vertices;
        vector<VertexFormat> road_vertices;
        vector<unsigned int> road_indices;

        float road_internal_dist = 0.5;
        float road_external_dist = 0.5;

        float tree_internal_dist = 0.6;
        float tree_external_dist = 0.6;

        float x = 0.0;
        float z = 0.0;
        float alpha = 0;
        float v = 0;
        int startPos[2];

        float t0 = 0;
        float t1 = 0;
        float fov = 60;
        float left = -5;
        float right = 5;
    };
}   // namespace m1
