#include "disable_all_warnings.h"
#include "draw.h"
#include "ray_tracing.h"
#include "trackball.h"
#include "window.h"
// Disable compiler warnings in third-party code (which we cannot change).
DISABLE_WARNINGS_PUSH()
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <imgui.h>
DISABLE_WARNINGS_POP()
#include <fstream>
#include <iostream>
#include <optional>

// This is the main application. The code in here does not need to be modified.
constexpr glm::ivec2 windowResolution { 800, 800 };


int main(int argc, char** argv)
{

    Trackball::printHelp();
    std::cout << "\n Usage: \"Practical4 [scene_id]\"" << std::endl;
    std::cout << "\n scene_id = 0 : Single triangle" << std::endl;
    std::cout << "\n scene_id = 1 : Cube (12 triangles)" << std::endl;
    std::cout << "\n scene_id = 2 : Dragon (87K triangles)" << std::endl;
    std::cout << "\n scene_id = 3 : 3 AABBs" << std::endl;
    std::cout << "\n scene_id = 4 : 3 spheres" << std::endl;
    std::cout << "\n scene_id = 5 : Mixed scene (AABBs, spheres and triangles)" << std::endl;
    std::cout << std::endl;
    std::cout << "\n Press the [R] key on your keyboard to create a ray towards the mouse cursor" << std::endl
              << std::endl;

    Window window { argv[0], windowResolution, OpenGLVersion::GL2 };
    Trackball camera { &window, glm::radians(50.0f), 3.0f };
    camera.setCamera (glm::vec3(0.0f, 0.0f, 0.0f), glm::radians(glm::vec3(20.0f, 20.0f, 0.0f)), 3.0f);

    std::optional<Ray> optRay;

    SceneType type = SingleTriangle;
    if (argc > 1)
        type = static_cast<SceneType>(atoi(argv[1]));

    optRay = camera.generateRay(window.getNormalizedCursorPos() * -2.0f + 1.0f);
    Scene scene = loadScene(type, DATA_DIR, *optRay);

    if (type == Custom)
        intersectRayWithScene(scene, *optRay);
    else
        optRay.reset();


    
    window.registerKeyCallback([&](int key, int /* scancode */, int action, int /* mods */) {
        if (action == GLFW_PRESS) {
            switch (key) {
            case GLFW_KEY_R: {
                // Shoot a ray. Produce a ray from camera to the far plane.
                optRay = camera.generateRay(window.getNormalizedCursorPos() * -2.0f + 1.0f);

                bool hit = false;
                if (intersectRayWithScene(scene, *optRay)) {
                    hit = true;
                }


            } break;
            case GLFW_KEY_ESCAPE: {
                window.close();
            } break;
            };
        }
    });

    while (!window.shouldClose()) {

        window.updateInput();

        ImGui::Begin("Final Project - Part 1");
        {
            std::array items { "SingleTriangle", "Cube", "Dragon", "AABBs", "Spheres", "Mixed", "Custom" };
            if ( ImGui::ListBox("Scenes\n", reinterpret_cast<int*>(&type), items.data(), int(items.size()), 7) )
            {
                
                scene = loadScene(type, DATA_DIR, *optRay);
                optRay->t = std::numeric_limits<float>::max();
                intersectRayWithScene(scene, *optRay);
                 
            }
        }

        // Clear screen.
        glClearDepth(1.0f);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Activate the light in the legacy OpenGL mode.
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_COLOR_MATERIAL);
        constexpr glm::vec4 lightPos { 0, 0, -2, 0 };
        glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(lightPos));

        // Normals will be normalized in the graphics pipeline.
        glEnable(GL_NORMALIZE);

        // Activate rendering modes.
        glEnable(GL_DEPTH_TEST);
        // Draw front and back facing triangles filled
        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_FILL);
        // Interpolate vertex colors over the triangles.
        glShadeModel(GL_SMOOTH);

        // Load view matrix.
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        const glm::mat4 viewMatrix = camera.viewMatrix();
        glMultMatrixf(glm::value_ptr(viewMatrix));

        // Load projection matrix.
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        const glm::mat4 projectionMatrix = camera.projectionMatrix();
        glMultMatrixf(glm::value_ptr(projectionMatrix));

        // Draw the scene and the ray (if any).
        drawScene(scene);

        if (optRay)
        {
            drawRay(*optRay);
        }


        // Draw a colored sphere at the location at which the trackball is looking/rotating around.
        glDisable(GL_LIGHTING);
        const Sphere trackballSphere { camera.lookAt(), 0.01f, glm::vec3(0.2f, 0.2f, 1.0f) };
        drawShape(trackballSphere);

        ImGui::End();

        window.swapBuffers();

    }

    return 0; // execution never reaches this point
}
