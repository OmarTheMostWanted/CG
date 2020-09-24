#include "disable_all_warnings.h"
#include "draw.h"
#include "mesh.h"
#include "shading.h"
#include "trackball.h"
#include "user_interaction.h"
#include "window.h"
DISABLE_WARNINGS_PUSH()
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>
#include <glm/vector_relational.hpp>
#include <imgui.h>
DISABLE_WARNINGS_POP()
#include <array>
#include <iostream>
#include <string>

enum class DiffuseMode {
    None,
    Lambert,
    ToonDiffuse
};

enum class SpecularMode {
    None,
    Phong,
    BlinnPhong,
    ToonSpecular
};

// Different display modes.
struct DisplayModes {
    bool debug = false;
    DiffuseMode diffuse = DiffuseMode::Lambert;
    SpecularMode specular = SpecularMode::None;
};

enum class LightPlacement {
    Sphere,
    Shadow,
    Specular
};

struct Light {
    glm::vec3 pos;
    glm::vec3 color;
};

struct ProgramState {
    DisplayModes displayModes;
    glm::vec3 backgroundColor { 0.2f, 0.2f, 0.0f };

    std::vector<Light> lights;
    int selectedLight = 0;
    LightPlacement lightPlacement = LightPlacement::Sphere;

    Mesh myMesh;
    unsigned selectedVertex = 0xFFFFFFFF;
    bool showSelectedVertex = true;
    ShadingData shadingData;
};

glm::vec3 computeLighting(const ProgramState& programState, unsigned vertexIndex, const glm::vec3& cameraPos, const Light& light)
{
    const auto& vertex = programState.myMesh.vertices[vertexIndex];

    //do not change any global variables here! This function will be called for EACH vertex
    //of the mesh, so your change would happen several times
    if (programState.displayModes.debug) {
        return debugColor(programState.shadingData, vertex.pos, vertex.normal, light.pos, cameraPos);
    }

    glm::vec3 result { 0.0f };
    switch (programState.displayModes.diffuse) {
    case DiffuseMode::Lambert: {
        result += diffuseOnly(programState.shadingData, vertex.pos, vertex.normal, light.pos);
    } break;
    case DiffuseMode::ToonDiffuse: {
        result = toonShadingNoSpecular(programState.shadingData, vertex.pos, vertex.normal, light.pos);
    } break;
    case DiffuseMode::None:
        break;
    };

    switch (programState.displayModes.specular) {
    case SpecularMode::Phong: {
        result += phongSpecularOnly(programState.shadingData, vertex.pos, vertex.normal, light.pos, cameraPos);
    } break;
    case SpecularMode::BlinnPhong: {
        result += blinnPhongSpecularOnly(programState.shadingData, vertex.pos, vertex.normal, light.pos, cameraPos);
    } break;
    case SpecularMode::ToonSpecular: {
        result += toonShadingOnlySpecular(programState.shadingData, vertex.pos, vertex.normal, light.pos, cameraPos);
    } break;
    case SpecularMode::None:
        break;
    };

    const glm::vec3 diff = light.pos - vertex.pos;
    const float dist2 = glm::dot(diff, diff);
    const glm::vec3 Li = light.color / dist2;
    return Li * result;
}

void userInteraction(ProgramState& programState, const glm::vec3& cameraPos)
{
    const auto& vertex = programState.myMesh.vertices[programState.selectedVertex];
    auto& light = programState.lights[static_cast<size_t>(programState.selectedLight)];

    switch (programState.lightPlacement) {
    case LightPlacement::Sphere: {
        light.pos = userInteractionSphere(vertex.pos, cameraPos);
    } break;
    case LightPlacement::Shadow: {
        light.pos = userInteractionShadow(vertex.pos, vertex.normal, light.pos);
    } break;
    case LightPlacement::Specular: {
        light.pos = userInteractionSpecular(vertex.pos, vertex.normal, cameraPos);
    } break;
    };
}

static std::optional<glm::vec3> getWorldPositionOfPixel(const Window& window, const Trackball& trackball, const glm::vec2& pixel);

void keyboard(unsigned char key, ProgramState& state, const Window& window, const Trackball& camera)
{
    switch (key) {
    case ' ': {
        const auto worldPoint = getWorldPositionOfPixel(window, camera, window.getCursorPixel());
        if (worldPoint) {
            state.selectedVertex = unsigned(getClosestVertexIndex(state.myMesh, *worldPoint));
            userInteraction(state, camera.position());
        }
    } break;
    default:
        yourKeyboardFunction(key, state.shadingData);
    }
}

// Get the 3D world position of the mouse cursor (assuming the depth buffer has been filled).
static std::optional<glm::vec3> getWorldPositionOfPixel(const Window& window, const Trackball& trackball, const glm::vec2& pixel)
{
    float depth;
    glReadPixels(static_cast<int>(pixel.x), static_cast<int>(pixel.y), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

    if (depth == 1.0f) {
        // This is a work around for a bug in GCC:
        // https://gcc.gnu.org/bugzilla/show_bug.cgi?id=80635
        //
        // This bug will emit a warning about a maybe uninitialized value when writing:
        // return {};
        constexpr std::optional<glm::vec3> tmp;
        return tmp;
    }

    // Coordinates convert from pixel space to OpenGL screen space (range from -1 to +1)
    const glm::vec3 win { pixel, depth };

    // View matrix
    const glm::mat4 view = trackball.viewMatrix();
    const glm::mat4 projection = trackball.projectionMatrix();

    const glm::vec4 viewport { glm::vec2(0), window.windowSize() };
    return glm::unProject(win, view, projection, viewport);
}

void draw(const ProgramState& state, const Trackball& camera, gsl::span<const glm::vec3> vertexColors)
{
    glClearColor(state.backgroundColor.r, state.backgroundColor.g, state.backgroundColor.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Initialize projection and view matrices.
    glMatrixMode(GL_PROJECTION);
    const auto projectionMatrix = camera.projectionMatrix();
    glLoadMatrixf(glm::value_ptr(projectionMatrix));
    glMatrixMode(GL_MODELVIEW);
    const auto viewMatrix = camera.viewMatrix();
    glLoadMatrixf(glm::value_ptr(viewMatrix));

    // Drawing mode options.
    glEnable(GL_DEPTH_TEST); // Enable depth test.
    glDepthMask(GL_TRUE); // Enable depth write.
    glDisable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    drawMeshWithColors(state.myMesh, vertexColors);

    // Disable depth write because we don't want the points in our depth buffer (messes with user interaction).
    glDepthMask(GL_FALSE); // Disable depth write.

    // Draw a big yellow point (square) around the selected light.
    glPointSize(40);
    glColor3f(1, 1, 0);
    glBegin(GL_POINTS);
    glVertex3fv(glm::value_ptr(state.lights[static_cast<size_t>(state.selectedLight)].pos));
    glEnd();

    // Draw lights as points (squares) in the lights color.
    glPointSize(10);
    glBegin(GL_POINTS);
    for (const auto& light : state.lights) {
        glColor3fv(glm::value_ptr(light.color));
        glVertex3fv(glm::value_ptr(light.pos));
    }
    glEnd();

    // Draw a small red point (square) at the selected vertex.
    if (state.showSelectedVertex && state.selectedVertex != 0xFFFFFFFF) {
        glBegin(GL_POINTS);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3fv(glm::value_ptr(state.myMesh.vertices[state.selectedVertex].pos));
        glEnd();
    }

    glDepthMask(GL_TRUE); // Disable depth write.
}

void computeLighting(const ProgramState& state, const glm::vec3& cameraPos, gsl::span<glm::vec3> outVertexColors)
{
    for (unsigned v = 0; v < state.myMesh.vertices.size(); v++) {
        outVertexColors[v] = glm::vec3(0.0f);
        for (const auto& light : state.lights)
            outVertexColors[v] += computeLighting(state, v, cameraPos, light);
    }
}

void printHelp()
{
    std::cout << "Program Usage:" << std::endl;
    std::cout << "SPACE - replaces mouse click for selection, will then call your light placement function" << std::endl;
}

bool specularModeCompatible(DiffuseMode diffuse, SpecularMode specular)
{
    switch (diffuse) {
    case DiffuseMode::None:
        return true;
    case DiffuseMode::Lambert: {
        switch (specular) {
        case SpecularMode::None:
        case SpecularMode::Phong:
        case SpecularMode::BlinnPhong:
            return true;
        default:
            break;
        };
    } break;
    case DiffuseMode::ToonDiffuse: {
        switch (specular) {
        case SpecularMode::None:
        case SpecularMode::ToonSpecular:
            return true;
        default:
            break;
        };
    } break;
    default:
        return false;
    };
    return false;
}

void drawUI(ProgramState& state, const Trackball& camera)
{
    constexpr std::array diffuseLabels {
        "None",
        "Lambert",
        "Toon Diffuse"
    };
    constexpr std::array specularLabels {
        "None",
        "Phong",
        "Blinn-Phong",
        "Toon Specular"
    };
    constexpr std::array lightPlacementLabels {
        "Sphere",
        "Shadow",
        "Specular"
    };

    ImGui::Begin("Options");

    ImGui::Text("Shading");
    ImGui::Spacing();
    ImGui::Checkbox("Debug shading", &state.displayModes.debug);
    if (!state.displayModes.debug) {
        // https://github.com/ocornut/imgui/issues/1658
        if (ImGui::BeginCombo("Diffuse shading", diffuseLabels[size_t(state.displayModes.diffuse)])) {
            for (size_t i = 0; i < diffuseLabels.size(); i++) {
                bool isSelected = (i == size_t(state.displayModes.diffuse));
                if (ImGui::Selectable(diffuseLabels[i], isSelected)) {
                    state.displayModes.diffuse = DiffuseMode(i);
                    if (!specularModeCompatible(state.displayModes.diffuse, state.displayModes.specular))
                        state.displayModes.specular = SpecularMode::None;
                }
                if (isSelected)
                    ImGui::SetItemDefaultFocus(); // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
            }
            ImGui::EndCombo();
        }
        if (ImGui::BeginCombo("Specular shading", specularLabels[size_t(state.displayModes.specular)])) {
            for (size_t i = 0; i < specularLabels.size(); i++) {
                if (!specularModeCompatible(state.displayModes.diffuse, SpecularMode(i)))
                    continue;

                const bool isSelected = (i == size_t(state.displayModes.specular));
                if (ImGui::Selectable(specularLabels[i], isSelected)) {
                    state.displayModes.specular = SpecularMode(i);
                }
                if (isSelected)
                    ImGui::SetItemDefaultFocus(); // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
            }
            ImGui::EndCombo();
        }
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::Text("Material");
    ImGui::Spacing();
    ImGui::ColorEdit3("Diffuse color (Kd)", glm::value_ptr(state.shadingData.Kd));
    ImGui::ColorEdit3("Specular color (Ks)", glm::value_ptr(state.shadingData.Ks));
    ImGui::SliderFloat("Shininess", &state.shadingData.shininess, 1.0f, 30.0f, "%.1f", 2.0f);
    ImGui::SliderInt("Toon discrete steps", &state.shadingData.toonDiscretize, 1, 20);
    ImGui::SliderFloat("Toon threshold", &state.shadingData.toonSpecularThreshold, 0.0f, 1.0f);

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::Text("Lights");
    ImGui::Spacing();

    if (ImGui::Button("Add lightsource")) {
        state.lights.push_back(Light { camera.position(), glm::vec3(1.0f) });
        state.selectedLight = int(state.lights.size() - 1);
    }
    if (ImGui::Button("Reset lights")) {
        state.lights.clear();
        state.lights.push_back(Light { glm::vec3(0, 0, 3), glm::vec3(1.0f) });
        state.selectedLight = 0;
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    {
        using namespace std::string_literals;
        std::string tmp = "Light "s + std::to_string(state.selectedLight);
        if (ImGui::BeginCombo("Selected light", tmp.c_str())) {
            for (size_t i = 0; i < state.lights.size(); i++) {
                tmp = "Light "s + std::to_string(i);
                bool isSelected = (int(i) == state.selectedLight);
                if (ImGui::Selectable(tmp.c_str(), isSelected)) {
                    state.selectedLight = int(i);
                }
                if (isSelected)
                    ImGui::SetItemDefaultFocus(); // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
            }
            ImGui::EndCombo();
        }
    }

    ImGui::ColorEdit3("Light color", glm::value_ptr(state.lights[size_t(state.selectedLight)].color));
    ImGui::Spacing();

    if (ImGui::BeginCombo("Light placement", lightPlacementLabels[size_t(state.lightPlacement)])) {
        for (size_t i = 0; i < lightPlacementLabels.size(); i++) {
            const bool isSelected = (i == size_t(state.lightPlacement));
            if (ImGui::Selectable(lightPlacementLabels[i], isSelected)) {
                state.lightPlacement = LightPlacement(i);
            }
            if (isSelected)
                ImGui::SetItemDefaultFocus(); // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }
    ImGui::Checkbox("Show selected vertex", &state.showSelectedVertex);
    if (ImGui::Button("Place light at current camera position")) {
        state.lights[static_cast<size_t>(state.selectedLight)].pos = camera.position();
    }

    ImGui::End();
}

int main(int argc, char** argv)
{
    Window window { "Practical 3", glm::ivec2(800), OpenGLVersion::GL2 };
    Trackball trackball { &window, glm::radians(80.0f), 2.0f, 0.387463093f, -0.293215364f };
    trackball.disableTranslation();

    printHelp();

    //this function loads a mesh
    ProgramState state {};
    state.myMesh = loadMesh(argv[1] ? argv[1] : std::filesystem::path(DATA_DIR) / "DavidHeadCleanMax.obj", true);
    state.lights.push_back(Light { glm::vec3(-0.1f, 0.2f, -1.4f), glm::vec3(1.0f) });

    window.registerCharCallback([&](unsigned unicodeCodePoint) {
        keyboard(static_cast<unsigned char>(unicodeCodePoint), state, window, trackball);
    });

    while (!window.shouldClose()) {
        window.updateInput();

        std::vector<glm::vec3> vertexColors(state.myMesh.vertices.size());
        computeLighting(state, trackball.position(), vertexColors);

        draw(state, trackball, vertexColors);
        drawUI(state, trackball);

        window.swapBuffers();
    }
}
