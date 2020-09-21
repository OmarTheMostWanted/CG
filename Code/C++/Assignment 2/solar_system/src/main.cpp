#include "disable_all_warnings.h"
#include "draw.h"
#include "reference.h"
#include "solar_system.h"
#include "trackball.h"
#include "window.h"
// Suppress warnings in third-party code.
DISABLE_WARNINGS_PUSH()

#include <glm/gtc/type_ptr.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <gsl-lite/gsl-lite.hpp>
#include <imgui.h>

DISABLE_WARNINGS_POP()

#include <array>
#include <fstream>
#include <iostream>

static const std::filesystem::path dataDirPath{DATA_DIR};

int main(int /* argc */, char **argv) {
    Trackball::printHelp();

    Window window{argv[0], glm::ivec2(800), OpenGLVersion::GL2};
    window.registerKeyCallback(
            [&](int key, int /* scancode */, int /* action */, int /* mods */) {
                switch (key) {
                    case GLFW_KEY_ESCAPE: {
                        window.close();
                        break;
                    }
                    case GLFW_KEY_L: {
                        // Turn lighting on.
                        if (window.isKeyPressed(GLFW_KEY_LEFT_SHIFT) || window.isKeyPressed(GLFW_KEY_RIGHT_SHIFT))
                            glEnable(GL_LIGHTING);
                        else
                            glDisable(GL_LIGHTING);

                        break;
                    }
                };
            });
    Trackball trackball{&window, glm::radians(50.0f), 13.0f, 0.785398602f, 3.75943637f};

    std::array<CelestrialBody, 4> bodies;
    // Sun at the center of our solar system.
    bodies[0].radius = 0.8f;
    bodies[0].spinPeriod = 627.0f;
    bodies[0].name = "Sun";
    bodies[0].texture = loadTexture(dataDirPath / "2k_sun.jpg");

    // Moon orbiting around the earth.
    bodies[1].radius = 0.1f;
    bodies[1].spinPeriod = 660.0f;
    bodies[1].pOrbitAround = &bodies[2];
    bodies[1].orbitAltitude = 0.8f;
    // The moon rotates at the same speed as that it orbits the earth, hence we always see the same side of the moon.
    bodies[1].orbitPeriod = bodies[1].spinPeriod;
    bodies[1].name = "Moon";
    bodies[1].texture = loadTexture(dataDirPath / "2k_moon.jpg");

    // Earth orbiting around the sun.
    bodies[2].radius = 0.3f;
    bodies[2].spinPeriod = 24.0f;
    bodies[2].pOrbitAround = &bodies[0];
    bodies[2].orbitAltitude = 3.0f;
    bodies[2].orbitPeriod = 8770.0f;
    bodies[2].name = "Earth";
    bodies[2].texture = loadTexture(dataDirPath / "2k_earth_daymap.jpg");

    // Mars orbiting around the sun.
    bodies[3].radius = 0.25f;
    bodies[3].spinPeriod = 24.6f;
    bodies[3].pOrbitAround = &bodies[0];
    bodies[3].orbitAltitude = 5.0f;
    bodies[3].orbitPeriod = 16500.0f;
    bodies[3].name = "Mars";
    bodies[3].texture = loadTexture(dataDirPath / "2k_mars.jpg");

    const ReferenceSolutionLoader referenceSolutions{dataDirPath / "reference.bin"};
    int solutionID = -1;
    std::vector<std::string> solutionLabels(referenceSolutions.getNumReferenceSolutions() + 1);
    solutionLabels[0] = "Your solution";
    for (int i = 0; i < referenceSolutions.getNumReferenceSolutions(); i++)
        solutionLabels[i + 1] = "Reference " + std::to_string(i + 1);
    //std::fstream file { "reference.bin", std::ios::binary | std::ios::out };

    float time = 0.0f, timeIncrement = 0.25f;
    while (!window.shouldClose()) {
        window.updateInput();

        // Initialize viewpoint.
        glViewport(0, 0, window.windowSize().x, window.windowSize().y);
        // Clear screen.
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui::Begin("Celestrial Bodies");

        // NOTE(Mathijs): solution labels shifted by one such that solutionID == -1 maps to the first label.
        if (ImGui::BeginCombo("Solution", solutionLabels[solutionID + 1].c_str())) {
            for (int i = 0; i < int(solutionLabels.size()); i++) {
                bool isSelected = ((i - 1) == solutionID);
                if (ImGui::Selectable(solutionLabels[i].c_str(), isSelected)) {
                    solutionID = i - 1;
                    if (solutionID != -1)
                        timeIncrement = 0.0f;
                }
                if (isSelected)
                    ImGui::SetItemDefaultFocus(); // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
            }
            ImGui::EndCombo();
        }

        ImGui::Spacing();

        if (solutionID == -1) {
            ImGui::Text("Current time: %.1f days", double(time / 24.0f));
            ImGui::SliderFloat("Speed (hours per frame)", &timeIncrement, -10.0f, 10.0f);
            ImGui::Spacing();

            for (int i = 0; i < bodies.size(); i++) {
                auto &body = bodies[i];

                if (ImGui::CollapsingHeader(body.name.c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
                    // Without this line it will think all bodies are shared because they use
                    // the same labels. When you change the setting for 1 body it will try to
                    // change the same value for the other bodies as well. By using IDs we can
                    // work around this issue.
                    ImGui::PushID(int(i));
                    ImGui::SliderFloat("Spin period", &body.spinPeriod, 0.0f, 1000.0f);
                    if (body.pOrbitAround) {
                        ImGui::SliderFloat("Orbit altitude", &body.orbitAltitude, 1.0f, 20.0f);
                        ImGui::SliderFloat("Orbit period", &body.orbitPeriod, 0.0f, 10000.0f);
                    }
                    ImGui::Spacing();
                    ImGui::PopID();
                }
            }
        }
        ImGui::End();

        // Enable depth test.
        glEnable(GL_DEPTH_TEST);
        // Load model/view matrix.
        glMatrixMode(GL_MODELVIEW);
        const glm::mat4 viewTransform = trackball.viewMatrix();
        glLoadMatrixf(glm::value_ptr(viewTransform));
        // Load projection matrix.
        glMatrixMode(GL_PROJECTION);
        const glm::mat4 perspectiveMatrix = trackball.projectionMatrix();
        glLoadMatrixf(glm::value_ptr(perspectiveMatrix));

        drawCoordSystem();
        {
            glPushAttrib(GL_ALL_ATTRIB_BITS);
            // Draw a sphere at the point that the camera is looking at / rotating around to help the user orientate.
            glDisable(GL_LIGHTING);
            glColor3f(0.0f, 0.0f, 1.0f);
            drawSphere(trackball.lookAt(), 0.1f);
            glPopAttrib();
        }

        // Enable lighting.
        glShadeModel(GL_SMOOTH);
        glEnable(GL_LIGHTING);
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_NORMALIZE);
        // Set the light at the first body (which we assume is the sun).
        constexpr glm::vec4 sunColor{0.9f, 0.8f, 0.2f, 1};
        constexpr glm::vec4 sunIntensity = 3.0f * sunColor;
        glEnable(GL_LIGHT0);
        {
            // Create a l-value because passing a pointer to an r-value ( glm::value_ptr(glm::vec4(...)) ) is illegal!
            const glm::vec4 sunPosition{glm::vec3(0), 1};
            glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(sunPosition));
        }
        glLightfv(GL_LIGHT0, GL_DIFFUSE, glm::value_ptr(sunIntensity));

        //auto transforms = computeCelestrialBodyTransformations(bodies, time);
        const auto transforms = (solutionID == -1) ? computeCelestrialBodyTransformations(bodies, time)
                                                   : referenceSolutions.getReferenceSolution(solutionID, time, bodies);

        /*// NOTE(Mathijs): code to write your current situation to disk such that it can be used as a comparison.
        static bool wasDownPrevFrame = false;
        if (window.isKeyPressed(GLFW_KEY_0) && !wasDownPrevFrame) {
            std::cout << "Writing solution" << std::endl;
            file.write(reinterpret_cast<const char*>(&time), sizeof(time));
            const size_t numBodies = bodies.size();
            file.write(reinterpret_cast<const char*>(&numBodies), sizeof(numBodies));
            for (const auto body : bodies) {
                file.write(reinterpret_cast<const char*>(&body.radius), sizeof(float));
                file.write(reinterpret_cast<const char*>(&body.spinPeriod), sizeof(float));
                file.write(reinterpret_cast<const char*>(&body.orbitAltitude), sizeof(float));
                file.write(reinterpret_cast<const char*>(&body.orbitPeriod), sizeof(float));
            }
            file.write(reinterpret_cast<const char*>(transforms.data()), transforms.size() * sizeof(transforms[0]));
        }
        wasDownPrevFrame = window.isKeyPressed(GLFW_KEY_0);*/

        for (size_t i = 0; i < transforms.size(); i++) {
            if (i == 0) {
                // First body is the sun (should appear to emit light).
                glMaterialfv(GL_FRONT, GL_EMISSION, glm::value_ptr(sunColor));
            } else {
                // Other bodies don't emit light.
                constexpr glm::vec4 black{0, 0, 0, 1};
                glMaterialfv(GL_FRONT, GL_EMISSION, glm::value_ptr(black));
            }

            drawSphere(transforms[i], bodies[i].texture);
        }

        time += timeIncrement;
        window.swapBuffers();
    }
}