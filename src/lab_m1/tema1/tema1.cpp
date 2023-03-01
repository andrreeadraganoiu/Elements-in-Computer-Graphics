#include "lab_m1/tema1/tema1.h"

#include <vector>
#include <iostream>
#include "lab_m1/tema1/duck.h"
#include "lab_m1/tema1/transform2D.h"
#include "lab_m1/tema1/_object2D.h"
#include "components/text_renderer.h"
#include "lab_m1/tema1/constants.h"

using namespace std;
using namespace m1; 
using namespace gfxc;

Tema1::Tema1()
{
    duck = new Duck();

    right = true;
    up = true;
    flutter = true;

    wingAngle = 0;

    translateX = rand() % X_MAX + X_OFFSET;
    translateY = 5;

    score = 0;
    LIVES_NO = 3;
    GUNS_NO = 3;
    DUCKS_NO = 0;
    SPEED = 200;

    game_time = 0;
    
    angle = GenerateRandomAngle();
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
    glm::vec3 corner = glm::vec3(0, 0, 0);

    Mesh* body = _object2D::CreateRectangle("birdBody", corner, BODY_LENGTH, BODY_WIDTH, BROWN, true);
    AddMeshToList(body);

    Mesh* head = _object2D::CreateCircle("birdHead", corner + glm::vec3(BODY_LENGTH + HEAD_RADIUS, BODY_WIDTH / 2, 0),
                                          HEAD_RADIUS, GREEN, true);
    AddMeshToList(head);

    Mesh* leftWing = _object2D::CreateDownTriangle("birdWing1", corner + glm::vec3(BODY_LENGTH/2, BODY_WIDTH, 0),
                                                   WING_HALF_LENGTH, BROWN, true);
    AddMeshToList(leftWing);

    Mesh* rightWing = _object2D::CreateDownTriangle("birdWing2", corner + glm::vec3(BODY_LENGTH / 2, 0, 0), 
                                                   WING_HALF_LENGTH, BROWN, true);
    AddMeshToList(rightWing);

    Mesh* beak = _object2D::CreateTriangle("birdBeak", corner + glm::vec3(BODY_LENGTH + 2 * HEAD_RADIUS, HEAD_RADIUS, 0), 
                                          BEAK_HALF_LENGTH, ORANGE, true);
    AddMeshToList(beak);

    Mesh* grass = _object2D::CreateRectangle("grass", corner, resolution.x, 40, LIGHT_GREEN, true);
    AddMeshToList(grass);

    Mesh* wireframe = _object2D::CreateRectangle("wireframe", glm::vec3(10 ,650, 0), 100, 20, LIGHT_GREEN, false);
    AddMeshToList(wireframe);

    Mesh* scoreLevel = _object2D::CreateRectangle("scoreLevel", glm::vec3(10, 650, 0), 100, 20, LIGHT_GREEN, true);
    AddMeshToList(scoreLevel);
 
    
    Mesh* lives[3] = {_object2D::CreateCircle("live1", corner + glm::vec3(1000,700,0), HEAD_RADIUS, RED, true),
                      _object2D::CreateCircle("live2", corner + glm::vec3(1040,700,0), HEAD_RADIUS, RED, true),
                      _object2D::CreateCircle("live3", corner + glm::vec3(1080,700,0), HEAD_RADIUS, RED, true) };
    AddMeshToList(lives[0]);
    AddMeshToList(lives[1]);
    AddMeshToList(lives[2]);

    Mesh* guns[3] = {_object2D::CreateRectangle("gun1", corner + glm::vec3(1130,680,0), 20, 40, BLACK, true),
                     _object2D::CreateRectangle("gun2", corner + glm::vec3(1160,680,0), 20, 40, BLACK, true),
                     _object2D::CreateRectangle("gun3", corner + glm::vec3(1190,680,0), 20, 40, BLACK, true) };
    AddMeshToList(guns[0]);
    AddMeshToList(guns[1]);
    AddMeshToList(guns[2]);

    score_tr = new gfxc::TextRenderer(window->props.selfDir, window->GetResolution().x, window->GetResolution().y);
    score_tr->Load(window->props.selfDir + "\\assets\\fonts\\Hack-Bold.ttf", FONT_SIZE);

    display_tr = new gfxc::TextRenderer(window->props.selfDir, window->GetResolution().x, window->GetResolution().y);
    display_tr->Load(window->props.selfDir + "\\assets\\fonts\\Hack-Bold.ttf", FONT_SIZE);
}


void Tema1::FrameStart()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::RenderBird(glm::mat3 motionMatrix)
{
    modelMatrix = motionMatrix;

    RenderMesh2D(meshes["birdBody"], shaders["VertexColor"], modelMatrix);

    RenderMesh2D(meshes["birdHead"], shaders["VertexColor"], modelMatrix);

    modelMatrix = motionMatrix;
    modelMatrix *= transform2D::Translate(BODY_LENGTH / 2, BODY_WIDTH);
    modelMatrix *= transform2D::Rotate(wingAngle);
    modelMatrix *= transform2D::Translate(-BODY_LENGTH / 2, -BODY_WIDTH);
    RenderMesh2D(meshes["birdWing1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = motionMatrix;
    modelMatrix *= transform2D::Translate(BODY_LENGTH / 2, 0);
    modelMatrix *= transform2D::Rotate(-wingAngle);
    modelMatrix *= transform2D::Rotate(WING_ROTATION);
    modelMatrix *= transform2D::Translate(-BODY_LENGTH / 2, 0);
    RenderMesh2D(meshes["birdWing2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = motionMatrix;
    modelMatrix *= transform2D::Translate(BODY_LENGTH + 2 * HEAD_RADIUS, HEAD_RADIUS);
    modelMatrix *= transform2D::Rotate(BEAK_ROTATION);
    modelMatrix *= transform2D::Translate(-BODY_LENGTH - 2 * HEAD_RADIUS, -HEAD_RADIUS);
    RenderMesh2D(meshes["birdBeak"], shaders["VertexColor"], modelMatrix);

}

void Tema1::DrawScene()
{
    modelMatrix = glm::mat3(1);
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    RenderMesh2D(meshes["wireframe"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(10, 650);
    modelMatrix *= transform2D::Scale(score / 100, 1);
    modelMatrix *= transform2D::Translate(-10, -650);
    RenderMesh2D(meshes["scoreLevel"], shaders["VertexColor"], modelMatrix);


    modelMatrix = glm::mat3(1);
    for (i = 1; i <= LIVES_NO; i++)
    {
        RenderMesh2D(meshes["live" + to_string(i)], shaders["VertexColor"], modelMatrix);
    }

    modelMatrix = glm::mat3(1);
    for (i = 1; i <= GUNS_NO; i++)
    {
        RenderMesh2D(meshes["gun" + to_string(i)], shaders["VertexColor"], modelMatrix);
    }

    score_tr->RenderText("Score : " + std::to_string((int)score), 10, 10, 1);
}

void Tema1::MoveWings(float deltaTimeSeconds)
{
    if (wingAngle <= 0)
        flutter = true;

    if (wingAngle >= 1)
        flutter = false;

    if (flutter == true)
        wingAngle += deltaTimeSeconds * WING_SPEED;
    else
        wingAngle -= deltaTimeSeconds * WING_SPEED;
}

void Tema1::UpdatePos() 
{
    duck->p1 = motionMatrix * glm::vec3(0, 0, 1);
    duck->p2 = motionMatrix * glm::vec3(BODY_LENGTH + 2 * HEAD_RADIUS, 0, 1);
    duck->p3 = motionMatrix * glm::vec3(BODY_LENGTH + 2 * HEAD_RADIUS, BODY_WIDTH, 1);
    duck->p4 = motionMatrix * glm::vec3(0, BODY_WIDTH, 1);
}

void Tema1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->props.resolution;
    glClearColor(0, 0, 0.4, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, resolution.x, resolution.y);
    game_time += deltaTimeSeconds;

    DrawScene();

    motionMatrix = glm::mat3(1);

    motionMatrix *= transform2D::Translate(translateX, translateY);
    motionMatrix *= transform2D::Rotate(angle);

    RenderBird(motionMatrix);
    MoveWings(deltaTimeSeconds);
    UpdatePos();

    if (game_time > 10)
    {
        duck->escaped = true;
        game_time = 0;
    }

    if (duck->alive == false)
    {
        translateY -= deltaTimeSeconds * SPEED;
        angle = - M_PI / 2;

        if (translateY <= 0) 
        {
            game_time += deltaTimeSeconds;
            if (game_time > 3)
            {
                game_time = 0;
                GUNS_NO = 3;
                duck->alive = true;
                angle = GenerateRandomAngle();
                translateX = rand() % X_MAX + X_OFFSET;
                translateY = 5;
                first_launch = true;
            }
        }
        return;
    }

    if (duck->escaped == true)
    {
        if (LIVES_NO == 0)
        {
            if (score < SCORE_MAX)
            {
                display_tr->RenderText("GAME OVER", 550, 350, 2);
            }
            else
            {
                display_tr->RenderText("WIN", 630, 350, 2);
            }
            score_tr->RenderText("Score : " + std::to_string((int)score), 550, 400, 2);
            SPEED = 0;
            return;
        }
        translateY += deltaTimeSeconds * SPEED;
        angle = M_PI / 2;

        if (translateY >= resolution.y)
        {
            game_time += deltaTimeSeconds;
            if (game_time > 3 && LIVES_NO > 0)
            {
                game_time = 0;
                LIVES_NO--;
                GUNS_NO = 3;
                duck->escaped = false;
                angle = GenerateRandomAngle();
                translateX = rand() % X_MAX + X_OFFSET;
                translateY = 5;
                first_launch = true;
            }
        }
        return;
    }

    if (angle < RIGHT_ANGLE && first_launch)
    {
        right = true;
        up = true;
        first_launch = false;
    }
    if (angle >= RIGHT_ANGLE && first_launch) 
    {
        right = false;
        up = true;
        first_launch = false;
    }

    translateX += deltaTimeSeconds * SPEED * cos(angle);
    translateY += deltaTimeSeconds * SPEED * sin(angle);

    if (translateX <= 0 && !first_launch) // perete stanga
    {
        right = true;
        angle = M_PI - angle;

    }
    else if (translateX >= resolution.x - BODY_LENGTH  && !first_launch) // perete dreapta
    {
        right = false;
        angle = M_PI - angle;
    }
    else if (translateY <= 0 && !first_launch) // jos
    {
        up = true;
        angle = -angle;
    }
    else if (translateY >= resolution.y - BODY_WIDTH && !first_launch) // sus
    {
        up = false;
        angle = -angle;
    }
    
}

float Tema1::GenerateRandomAngle()
{
    return (float)(rand() % (int)ceil(M_PI * 100)) / 100.f;
}

void Tema1::FrameEnd()
{
}


void Tema1::OnInputUpdate(float deltaTime, int mods)
{

}


void Tema1::OnKeyPress(int key, int mods)
{

}


void Tema1::OnKeyRelease(int key, int mods)
{
  
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
   
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{

    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT))
    { 
        GUNS_NO--;
        
        if (duck->isKilled(mouseX, 720 - mouseY) == true && duck->escaped == false  
                                                         && duck->alive == true)
        {
            duck->alive = false;
            score += 5;
            DUCKS_NO++;
        }
        else
        {
            if (GUNS_NO == 0)
            {
                duck->escaped = true;
                DUCKS_NO++;
            }
        }
        (DUCKS_NO % 5 == 0) ? SPEED += SPEED / 5 : SPEED;
        
    }
    
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
