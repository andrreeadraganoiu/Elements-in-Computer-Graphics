#include "lab_m1/lab1/lab1.h"

#include <vector>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab1::Lab1()
{
    // TODO(student): Never forget to initialize class variables!
    clearColorR = 0;
    clearColorG = 0;
    clearColorB = 0;

    // default mesh is box
    meshID = 0;
    meshString = "box";

    // default pozition for sphere
    sphereX = 1;
    sphereY = 0.5f;
    sphereZ = 1;

    // default speed multiplier
    multiplier = 1.75f;
}


Lab1::~Lab1()
{
}


void Lab1::Init()
{
    // Load a mesh from file into GPU memory. We only need to do it once,
    // no matter how many times we want to draw this mesh.

    /* box mesh */
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // TODO(student): Load some more meshes. The value of RESOURCE_PATH::MODELS
    // is actually a path on disk, go there and you will find more meshes.

    /* teapot mesh */ 
    {
        Mesh* mesh = new Mesh("teapot");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "teapot.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    /* spehere mesh */
    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
}


void Lab1::FrameStart()
{
}


void Lab1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->props.resolution;

    // Sets the clear color for the color buffer

    // TODO(student): Generalize the arguments of `glClearColor`.
    // You can, for example, declare three variables in the class header,
    // that will store the color components (red, green, blue).
    glClearColor(clearColorR, clearColorG, clearColorB, 1); /*culoarea de background*/

    // Clears the color buffer (using the previously set color) and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); /*coloram cu acea culoare backgroundul*/

    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y); /*in functie de rezolutie stabilim cat de mare este efectiv zona din fereastra pe care afisam*/

    // Render the object
    RenderMesh(meshes["box"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));

    // Render the object again but with different properties
    RenderMesh(meshes[meshString], glm::vec3(-1, 0.5f, 0));

    // TODO(student): We need to render (a.k.a. draw) the mesh that
    // was previously loaded. We do this using `RenderMesh`. Check the
    // signature of this function to see the meaning of its parameters.
    // You can draw the same mesh any number of times.
    RenderMesh(meshes["teapot"], glm::vec3(-2, 0, 1));

    // The one that moves
    RenderMesh(meshes["sphere"], glm::vec3(sphereX, sphereY, sphereZ));

}


void Lab1::FrameEnd()
{
    DrawCoordinateSystem();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab1::OnInputUpdate(float deltaTime, int mods)
{
    // Treat continuous update based on input

    // TODO(student): Add some key hold events that will let you move
    // a mesh instance on all three axes. You will also need to
    // generalize the position used by `RenderMesh`.

    if (window->KeyHold(GLFW_KEY_W)) {
        sphereX += multiplier * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_S)) {
        sphereX -= multiplier * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_D)) {
        sphereZ += multiplier * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_A)) {
        sphereZ -= multiplier * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_E)) {
        sphereY += multiplier * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_Q)) {
        sphereY -= multiplier * deltaTime;
    }

}


void Lab1::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_F) {
        // TODO(student): Change the values of the color components.
        clearColorR = 0.75f;
        clearColorG = 0.75f;
        clearColorB = 0.75f;
    }

    // press R to reset clear color
    if (key == GLFW_KEY_R) {
        clearColorR = 0;
        clearColorG = 0;
        clearColorB = 0;
    }

    // TODO(student): Add a key press event that will let you cycle
    // through at least two meshes, rendered at the same position.
    // You will also need to generalize the mesh name used by `RenderMesh`.

    // press G to cycle through meshes
    if (key == GLFW_KEY_G) {
        switch (meshID) {
        case 0:
            meshString = "teapot";
            meshID = 1;
            break;
        case 1:
            meshString = "sphere";
            meshID = 2;
            break;
        case 2:
            meshString = "box";
            meshID = 0;
            break;
        }
    }
}


void Lab1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
    // Treat mouse scroll event
}


void Lab1::OnWindowResize(int width, int height)
{
    // Treat window resize event
}

//std::default_random_engine eng(rd());
//std::uniform_real_distribution<> sharp(SHARP_MIN, SHARP_MAX);
//
//std::uniform_real_distribution<> oblique(OBLIQUE_MIN, OBLIQUE_MAX);
//
//return pick % 2 ? sharp(eng) : oblique(eng);