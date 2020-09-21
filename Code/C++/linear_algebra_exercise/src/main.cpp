#include "disable_all_warnings.h"
#include "draw.h"
#include "la.h"
#include "trackball.h"
#include "window.h"
// Suppress warnings in third-party code.
DISABLE_WARNINGS_PUSH()
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <gsl/span>
#include <imgui.h>
DISABLE_WARNINGS_POP()
#include <array>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>

enum class Exercise {
    POINTPLANE,
    NORMAL,
    FRONTFACING
};

// Random engine generate random bit patterns.
std::default_random_engine e {};

float randFloat(float scale)
{
    std::uniform_real_distribution<float> uniformDist(-scale, scale);
    return uniformDist(e);
}

glm::vec3 randomPoint(float scale)
{
    return glm::vec3(randFloat(scale), randFloat(scale), randFloat(scale));
}

size_t randSize_t(size_t max)
{
    std::uniform_int_distribution<size_t> uniformDist(0, max);
    return uniformDist(e);
}

struct exercise1Test {
    glm::vec3 pt;
    Plane plane;
    bool solution;
};

struct exercises23Test {
    Triangle triangle;
    glm::vec3 cam_rotation;
    float cam_dist;
    bool solution;
};

int main(int /* argc */, char** argv)
{

    constexpr float pt_scale = 5.0f; // scale for generating random vertices

    // Point/Plane exercise
    glm::vec3 pt(0.0f, 0.0f, 0.0f);
    Plane plane;
    plane.p = glm::vec3(0.0f, 3.0f, 0.0f);
    plane.n = glm::vec3(0.0f, 1.0f, 0.0f);

    // Triangle for triangle normal and frontfacing exercise
    Triangle triangle;
    triangle.v0 = glm::vec3(0.0f, 0.0f, 0.0f);
    triangle.v1 = glm::vec3(0.0f, 1.0f, 0.0f);
    triangle.v2 = glm::vec3(1.0f, 1.0f, 0.0f);
    triangle.n = glm::vec3(0.0f, 0.0f, 0.0f);

    Exercise exercise = Exercise::POINTPLANE;

    bool sameside = false; // exercise 1 answer
    bool frontfacing = false; // exercise 3 answer
    size_t solution_id = 0xFFFFFFFF; // flag to use pre-generated cases with answer
    std::string solution = "NA";

    Trackball::printHelp();

    Window window { argv[0], glm::ivec2(800), OpenGLVersion::GL2 };
    window.registerKeyCallback(
        [&](int key, int /* scancode */, int action, int /* mods */) {
            if (action == GLFW_PRESS) {
                switch (key) {
                case GLFW_KEY_ESCAPE: {
                    window.close();
                    break;
                }
                };
            }
        });
    Trackball trackball { &window, glm::radians(50.0f), 13.0f, 0.785398602f, 3.75943637f };


    // read pre-computed solutions from file to vector
    /*******************************************************************/
    std::ifstream ifs(std::filesystem::path(DATA_DIR) / "pointplane");
    assert(ifs.is_open());
    std::vector<exercise1Test> pointPlaneTests;
    exercise1Test ex1;
    while (!ifs.eof()) {
        ifs >> ex1.pt.x >> ex1.pt.y >> ex1.pt.z >> ex1.plane.p.x >> ex1.plane.p.y >> ex1.plane.p.z >> ex1.plane.n.x >> ex1.plane.n.y >> ex1.plane.n.z >> ex1.solution;
        pointPlaneTests.push_back(ex1);
    }
    ifs.close();

    ifs = std::ifstream(std::filesystem::path(DATA_DIR) / "triangle");
    assert(ifs.is_open());
    std::vector<exercises23Test> triangleTests;
    exercises23Test exs23;
    while (!ifs.eof()) {
        ifs >> exs23.triangle.v0.x >> exs23.triangle.v0.y >> exs23.triangle.v0.z >> exs23.triangle.v1.x >> exs23.triangle.v1.y >> exs23.triangle.v1.z >> exs23.triangle.v2.x >> exs23.triangle.v2.y >> exs23.triangle.v2.z >> exs23.triangle.n.x >> exs23.triangle.n.y >> exs23.triangle.n.z >> exs23.cam_rotation.x >> exs23.cam_rotation.y >> exs23.cam_rotation.z >> exs23.cam_dist >> exs23.solution;
        triangleTests.push_back(exs23);
    }
    ifs.close();

    /*******************************************************************/

    while (!window.shouldClose()) {
        window.updateInput();

        // Initialize viewpoint.
        glViewport(0, 0, window.windowSize().x, window.windowSize().y);
        // Clear screen.
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

        ImGui::Begin("Linear Algebra Exercises");

        {
            std::array items { "PointPlane", "TriangleNormal", "FrontFacing" };
            ImGui::ListBox("Exercises\n", reinterpret_cast<int*>(&exercise), items.data(), int(items.size()), 4);
        }

        bool update = false;
        if (exercise == Exercise::POINTPLANE) {

            if (ImGui::Button("Generate random Point")) {
                pt = randomPoint(pt_scale);
                solution_id = 0xFFFFFFFF;
                update = true;
            }
            if (ImGui::Button("Generate random Plane")) {
                plane.p = randomPoint(pt_scale);
                plane.n = randomPoint(1.0f);
                plane.n = glm::normalize(plane.n);
                solution_id = 0xFFFFFFFF;
                update = true;
            }
            if (ImGui::Button("Check Solution")) {
                solution_id = randSize_t(pointPlaneTests.size()-1);
                pt = pointPlaneTests[solution_id].pt;
                plane = pointPlaneTests[solution_id].plane;
                update = true;
            }

            // YOUR SOLUTION
            if (update) {
                sameside = isInFront(pt, plane);

                if (solution_id != 0xFFFFFFFF) {
                    if (sameside == pointPlaneTests[solution_id].solution)
                        solution = "Correct";
                    else
                        solution = "Wrong";
                } else
                    solution = "NA";
            }
            drawSphere(pt, 0.3f);
            drawPlane(plane, sameside);
        } else if (exercise == Exercise::NORMAL || exercise == Exercise::FRONTFACING) {
            if (ImGui::Button("Generate random Triangle")) {
                triangle.v0 = randomPoint(pt_scale);
                triangle.v1 = randomPoint(pt_scale);
                triangle.v2 = randomPoint(pt_scale);
                triangle.n = glm::vec3(0.0f, 0.0f, 0.0f);
                solution_id = 0xFFFFFFFF;
                update = true;
            }
            if (ImGui::Button("Check Solution")) {
                solution_id = randSize_t(pointPlaneTests.size()-1);
                triangle = triangleTests[solution_id].triangle;
                if (exercise == Exercise::FRONTFACING) {
                    trackball.setCamera(glm::vec3(0.0f), triangleTests[solution_id].cam_rotation, triangleTests[solution_id].cam_dist);
                    glMatrixMode(GL_MODELVIEW);
                    const glm::mat4 view = trackball.viewMatrix();
                    glLoadMatrixf(glm::value_ptr(view));
                }
                update = true;
            }

            // YOUR SOLUTION
            glm::vec3 normal = computeNormal(triangle);
            if (exercise == Exercise::FRONTFACING)
                frontfacing = isFrontFacing(triangle, trackball.position());

            if (update) // clicked some button
            {
                solution = "NA";
                if (solution_id != 0xFFFFFFFF) {
                    solution = "Wrong";
                    if (exercise == Exercise::NORMAL) {
                        if (glm::all(glm::epsilonEqual(triangle.n, normal, glm::vec3(0.0001f))))
                            solution = "Correct";
                    } else {
                        if (frontfacing == triangleTests[solution_id].solution)
                            solution = "Correct";
                    }
                }

                // update triangle with your solution
                triangle.n = normal;
            }
            drawTriangle(triangle, frontfacing);
        }

        ImGui::LabelText(solution.c_str(), "solution");

        ImGui::End();

        window.swapBuffers();
    }
}
