#pragma once

#include "components/simple_scene.h"
#include "lab_m1/tema1/duck.h"
#include "components/text_renderer.h"
#include <random>

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
         Tema1();
        ~Tema1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        void RenderBird(glm::mat3 modelMatrix);
        void MoveWings(float deltaTimeSeconds);
        void DrawScene();
        void UpdatePos();
        void IncreaseScoreLevel();
        float GenerateRandomAngle();

     protected:
        Duck* duck;
        float cx, cy;
        glm::mat3 modelMatrix;
        glm::mat3 motionMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;
        
        bool right; 
        bool up; 
        bool flutter; 

        float wingAngle;
        float angle;

        int LIVES_NO;
        int GUNS_NO;
        int DUCKS_NO;
        float score;
        int i;
        int SPEED;

        float game_time;

        bool first_launch = true;

        gfxc::TextRenderer* score_tr;
        gfxc::TextRenderer* display_tr;

        std::random_device rd;
    };
}   // namespace m1
