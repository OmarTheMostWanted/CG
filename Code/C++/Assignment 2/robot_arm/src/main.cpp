#include "disable_all_warnings.h"
#include "draw.h"
#include "reference.h"
#include "robot_arm.h"
#include "trackball.h"
#include "window.h"
// Suppress warnings in third-party code.
DISABLE_WARNINGS_PUSH()
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec4.hpp>
#include <gsl-lite/gsl-lite.hpp>
#include <imgui.h>
DISABLE_WARNINGS_POP()
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

static const std::filesystem::path dataDirPath { DATA_DIR };

int main(int /* argc */, char** argv)
{
    Trackball::printHelp();

    Window window { argv[0], glm::ivec2(1280, 720), OpenGLVersion::GL2 };
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
    //pWindow->registerWindowResizeCallback(reshape);
    Trackball trackball { &window, glm::radians(50.0f), glm::vec3(0, 1.5f, 2), 6.0f, 0.0f, glm::radians(90.0f) };

    //std::fstream file { "reference.bin", std::ios::binary | std::ios::out };
    const ReferenceSolutionLoader referenceSolutions { dataDirPath / "reference.bin" };
    int solutionID = -1;
    std::vector<std::string> solutionLabels(referenceSolutions.getNumReferenceSolutions() + 1);
    solutionLabels[0] = "Your solution";
    for (int i = 0; i < referenceSolutions.getNumReferenceSolutions(); i++)
        solutionLabels[i + 1] = "Reference " + std::to_string(i + 1);

    std::vector armSegments {
        ArmSegment { glm::radians(-50.0f), glm::vec3(1, 1, 3) },
        ArmSegment { glm::radians(30.0f), glm::vec3(1.0f, 0.6f, 2) },
        ArmSegment { glm::radians(40.0f), glm::vec3(0.3f, 0.3f, 1) }
    };

    while (!window.shouldClose()) {
        window.updateInput();

        // Initialize viewpoint.
        glViewport(0, 0, window.windowSize().x, window.windowSize().y);

        // Clear screen.
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Load model/view matrix.
        glMatrixMode(GL_MODELVIEW);
        const glm::mat4 viewTransform = trackball.viewMatrix();
        glLoadMatrixf(glm::value_ptr(viewTransform));
        // Load projection matrix.
        glMatrixMode(GL_PROJECTION);
        const glm::mat4 perspectiveMatrix = trackball.projectionMatrix();
        glLoadMatrixf(glm::value_ptr(perspectiveMatrix));

        // Enable lighting.
        glShadeModel(GL_SMOOTH);
        glEnable(GL_LIGHTING);
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_NORMALIZE);
        // Set the lights to some arbitrary positions and colors.
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(glm::vec4(-0.8f, -1.3f, -0.9f, 1)));
        glLightfv(GL_LIGHT0, GL_DIFFUSE, glm::value_ptr(glm::vec4(0.8f, 0.3f, 0.4f, 1)));
        glEnable(GL_LIGHT1);
        glLightfv(GL_LIGHT1, GL_POSITION, glm::value_ptr(glm::vec4(1.9f, 1.8f, 2.3f, 1)));
        glLightfv(GL_LIGHT1, GL_DIFFUSE, glm::value_ptr(glm::vec4(0.3f, 0.9f, 0.6f, 1)));

        // Enable depth test.
        glEnable(GL_DEPTH_TEST);

        drawCoordSystem();

        ImGui::Begin("Arm Segments");

                // NOTE(Mathijs): solution labels shifted by one such that solutionID == -1 maps to the first label.
        if (ImGui::BeginCombo("Solution", solutionLabels[solutionID + 1].c_str())) {
            for (int i = 0; i < int(solutionLabels.size()); i++) {
                bool isSelected = ((i - 1) == solutionID);
                if (ImGui::Selectable(solutionLabels[i].c_str(), isSelected)) {
                    solutionID = i - 1;
                }
                if (isSelected)
                    ImGui::SetItemDefaultFocus(); // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
            }
            ImGui::EndCombo();
        }

        ImGui::Spacing();

        if (solutionID == -1) {
            for (size_t i = 0; i < armSegments.size(); i++) {
                auto& armSegment = armSegments[i];

                using namespace std::string_literals;
                const auto name = "Arm segment "s + std::to_string(i);
                if (ImGui::CollapsingHeader(name.c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
                    // Without this line it will think all segments are shared because they use
                    // the same labels. When you change the setting for 1 segment it will try to
                    // change the same value for the other segments as well. By using IDs we can
                    // work around this issue.
                    ImGui::PushID(int(i));
                    ImGui::SliderAngle("Rotation X", &armSegment.rotationX, -180.0f, +180.0f);
                    ImGui::SliderFloat3("Size", glm::value_ptr(armSegment.boxSize), 0.1f, 3.0f);
                    ImGui::Spacing();
                    ImGui::PopID();
                }
            }
        }
        ImGui::End();

        const auto transforms = (solutionID == -1) ? computeRobotArmTransforms(armSegments) : referenceSolutions.getReferenceSolution(solutionID, armSegments);
        for (const auto& transform : transforms)
            drawCube(transform);

        /*// NOTE(Mathijs): code to write your current situation to disk such that it can be used as a comparison.
        static bool wasDownPrevFrame = false;
        if (window.isKeyPressed(GLFW_KEY_0) && !wasDownPrevFrame) {
            std::cout << "Writing solution" << std::endl;
            const size_t numSegments = armSegments.size();
            file.write(reinterpret_cast<const char*>(&numSegments), sizeof(numSegments));
            file.write(reinterpret_cast<const char*>(armSegments.data()), armSegments.size() * sizeof(armSegments[0]));
            file.write(reinterpret_cast<const char*>(transforms.data()), transforms.size() * sizeof(transforms[0]));
        }
        wasDownPrevFrame = window.isKeyPressed(GLFW_KEY_0);*/

        window.swapBuffers();
    }
}