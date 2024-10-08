// Disable compiler warnings in third-party code (which we cannot change).
#include <framework/disable_all_warnings.h>
#include <framework/opengl_includes.h>

DISABLE_WARNINGS_PUSH()
// Include glad before glfw3
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
// #define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

DISABLE_WARNINGS_POP()

#include <algorithm>
#include <cassert>
#include <cstdlib> // EXIT_FAILURE
#include <framework/mesh.h>
#include <framework/shader.h>
#include <framework/trackball.h>
#include <framework/window.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl2.h>
#include <iostream>
#include <numeric>
#include <optional>
#include <span>
#include <toml/toml.hpp>
#include <vector>
#include <array>

// Configuration
const int WIDTH = 1200;
const int HEIGHT = 800;
toml::table config;


bool show_imgui = true;
bool debug = true;
bool diffuseLighting = false;
bool phongSpecularLighting = false;
bool blinnPhongSpecularLighting = false;
bool toonLightingDiffuse = false;
bool toonLightingSpecular = false;
bool toonxLighting = false;

bool distanceShaderEnabled = false;

struct {
    // Diffuse (Lambert)
    glm::vec3 kd{0.5f};
    // Specular (Phong/Blinn Phong)
    glm::vec3 ks{0.5f};
    float shininess = 3.0f;
    // Toon
    int toonDiscretize = 4;
    float toonSpecularThreshold = 0.49f;
} shadingData;


struct Texture {
    int width;
    int height;
    int channels;
    stbi_uc *texture_data;
    GLuint texture_id;
};

// Light Placement state
enum class LightPlacementValue {
    Sphere = 0, Shadow = 1, Specular = 2
};
LightPlacementValue interfaceLightPlacement{LightPlacementValue::Sphere};


// Lights
struct Light {
    glm::vec3 position;
    glm::vec3 color;
    bool is_spotlight;
    glm::vec3 direction;
    bool has_texture;
    Texture texture;
};

std::vector<Light> lights{};
size_t selectedLightIndex = 0;

static glm::vec3 userInteractionSphere(const glm::vec3 &selectedPos, const glm::vec3 &camPos) {
    // RETURN the new light position, defined as follows.
    // selectedPos is a location on the mesh. Use this location to place the light source to cover the location as seen from camPos.
    // Further, the light should be at a distance of 1.5 from the origin of the scene - in other words, located on a sphere of radius 1.5 around the origin.

    return {1, 1, 1};
}

static glm::vec3 userInteractionShadow(const glm::vec3 &selectedPos, const glm::vec3 &selectedNormal, const glm::vec3 &lightPos) {
    // RETURN the new light position such that the light towards the selectedPos is orthogonal to the normal at that location
    //--- in this way, the shading boundary will be exactly at this location.
    // there are several ways to do this, choose one you deem appropriate given the current light position
    // no panic, I will not judge what solution you chose, as long as the above condition is met.
    return glm::vec3(1, 0, 1);
}

static glm::vec3 userInteractionSpecular(const glm::vec3 &selectedPos, const glm::vec3 &selectedNormal, const glm::vec3 &lightPos, const glm::vec3 &cameraPos) {
    // RETURN the new light position such that a specularity (highlight) will be located at selectedPos, when viewed from cameraPos and lit from lightPos.
    // please ensure also that the light is at a distance of 1 from selectedPos! If the camera is on the wrong side of the surface (normal pointing the other way),
    // then just return the original light position.
    // There is only ONE way of doing this!
    return glm::vec3(0, 1, 1);
}

static size_t getClosestVertexIndex(const Mesh &mesh, const glm::vec3 &pos);

static std::optional<glm::vec3> getWorldPositionOfPixel(const Trackball &, const glm::vec2 &pixel);

static void userInteraction(const glm::vec3 &cameraPos, const glm::vec3 &selectedPos, const glm::vec3 &selectedNormal);

static void readLights();

static void printHelp();

void resetLights() {
    lights.clear();
    selectedLightIndex = 0;
    readLights();
}

void cleanLights() {
    for (Light &light: lights) {
        if (light.has_texture) {
            if (light.texture.texture_data) {
                stbi_image_free(light.texture.texture_data);
                light.texture.texture_data = nullptr;
            }
            if (light.texture.texture_id != 0) {
                glDeleteTextures(1, &light.texture.texture_id);
                light.texture.texture_id = 0;
            }
        }
    }
    lights.clear();
}

void selectNextLight() {
    selectedLightIndex = (selectedLightIndex + 1) % lights.size();
}

void selectPreviousLight() {
    if (selectedLightIndex == 0)
        selectedLightIndex = lights.size() - 1;
    else
        --selectedLightIndex;
}

void drawSquare(const glm::vec3 &center, const glm::vec3 &normal, const glm::vec3 &color, bool drawNormal = false) {
    // Calculate the right and up vectors for the square
    glm::vec3 right = glm::normalize(glm::cross(normal, glm::vec3(0.0f, 1.0f, 0.0f)));
    glm::vec3 up = glm::normalize(glm::cross(right, normal));

    // Calculate the vertices of the square
    std::array<glm::vec3, 4> vertices = {center + right * 0.5f + up * 0.5f, center - right * 0.5f + up * 0.5f, center - right * 0.5f - up * 0.5f, center + right * 0.5f - up * 0.5f};

    // Vertex data
    std::array<float, 24> vertexData = {vertices[0].x, vertices[0].y, vertices[0].z, color.r, color.g, color.b, vertices[1].x, vertices[1].y, vertices[1].z, color.r, color.g, color.b, vertices[2].x,
                                        vertices[2].y, vertices[2].z, color.r, color.g, color.b, vertices[3].x, vertices[3].y, vertices[3].z, color.r, color.g, color.b};

    // Indices for the square
    std::array<unsigned int, 6> indices = {0, 1, 2, 2, 3, 0};

    // Create and bind the VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create and bind the VBO
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

    // Create and bind the EBO
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Draw the square
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Draw the normal if requested
    if (drawNormal) {
        glm::vec3 normalEnd = center + normal;
        std::array<float, 12> normalData = {center.x, center.y, center.z, 1.0f, 0.0f, 0.0f, normalEnd.x, normalEnd.y, normalEnd.z, 1.0f, 0.0f, 0.0f};

        GLuint normalVbo;
        glGenBuffers(1, &normalVbo);
        glBindBuffer(GL_ARRAY_BUFFER, normalVbo);
        glBufferData(GL_ARRAY_BUFFER, normalData.size() * sizeof(float), normalData.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glDrawArrays(GL_LINES, 0, 2);

        glDeleteBuffers(1, &normalVbo);
    }

    // Unbind the VAO
    glBindVertexArray(0);

    // Clean up
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}

void imgui() {

    // Define UI here
    if (!show_imgui)
        return;

    ImGui::Begin("Final project part 1 : Modern Shading");
    ImGui::Text("Press \\ to show/hide this menu");

    ImGui::Separator();
    ImGui::Text("Material parameters");
    ImGui::SliderFloat("Shininess", &shadingData.shininess, 0.0f, 100.f);

    // Color pickers for Kd and Ks
    ImGui::ColorEdit3("Kd", &shadingData.kd[0]);
    ImGui::ColorEdit3("Ks", &shadingData.ks[0]);

    ImGui::SliderInt("Toon Discretization", &shadingData.toonDiscretize, 1, 10);
    ImGui::SliderFloat("Toon Specular Threshold", &shadingData.toonSpecularThreshold, 0.0f, 1.0f);

    ImGui::Separator();
    ImGui::Text("Shading modes");
    ImGui::Checkbox("0: Debug", &debug);
    ImGui::Checkbox("1: Diffuse Lighting", &diffuseLighting);
    ImGui::Checkbox("2: Phong Specular Lighting", &phongSpecularLighting);
    ImGui::Checkbox("3: Blinn-Phong Specular Lighting", &blinnPhongSpecularLighting);
    ImGui::Checkbox("4: Toon Lighting Diffuse", &toonLightingDiffuse);
    ImGui::Checkbox("5: Toon Lighting Specular", &toonLightingSpecular);
    ImGui::Checkbox("6: Toon X Lighting", &toonxLighting);
    ImGui::Checkbox("7: Distance Shader", &distanceShaderEnabled);

    ImGui::Separator();
    ImGui::Text("Lights");

    // Display lights in scene
    std::vector<std::string> itemStrings = {};
    for (size_t i = 0; i < lights.size(); i++) {
        auto string = "Light " + std::to_string(i);
        itemStrings.push_back(string);
    }

    std::vector<const char *> itemCStrings = {};
    for (const auto &string: itemStrings) {
        itemCStrings.push_back(string.c_str());
    }

    int tempSelectedItem = static_cast<int>(selectedLightIndex);
    if (ImGui::ListBox("Lights", &tempSelectedItem, itemCStrings.data(), (int) itemCStrings.size(), 4)) {
        selectedLightIndex = static_cast<size_t>(tempSelectedItem);
    }

    // Button for clearing lights
    if (ImGui::Button("Reset Lights")) {
        resetLights();
    }

    // Dropdown for interaction mode
    std::array interactionModeNames{"Shadow", "Sphere", "Specular"};
    int current_mode = static_cast<int>(interfaceLightPlacement);
    ImGui::Combo("User Interaction Mode", &current_mode, interactionModeNames.data(), (int) interactionModeNames.size());
    interfaceLightPlacement = static_cast<LightPlacementValue>(current_mode);

    ImGui::End();
    ImGui::Render();
}

std::optional<glm::vec3> tomlArrayToVec3(const toml::array *array) {
    glm::vec3 output{};

    if (array) {
        int i = 0;
        array->for_each([&](auto &&elem) {
            if (elem.is_number()) {
                if (i > 2)
                    return;
                output[i] = static_cast<float>(elem.as_floating_point()->get());
                i += 1;
            } else {
                std::cerr << "Error: Expected a number in array, got " << elem.type() << std::endl;
                return;
            }
        });
    }

    return output;
}


void readLights() {
    cleanLights();
    // read lights
    lights = std::vector<Light>{};
    size_t num_lights = config["lights"]["positions"].as_array()->size();
    std::cout << num_lights << std::endl;

    for (size_t i = 0; i < num_lights; ++i) {
        auto pos = tomlArrayToVec3(config["lights"]["positions"][i].as_array()).value();
        auto color = tomlArrayToVec3(config["lights"]["colors"][i].as_array()).value();
        bool is_spotlight = config["lights"]["is_spotlight"][i].value<bool>().value();
        auto direction = tomlArrayToVec3(config["lights"]["direction"][i].as_array()).value();
        bool has_texture = config["lights"]["has_texture"][i].value<bool>().value();
        auto tex_path = std::string(RESOURCE_ROOT) + config["lights"]["texture_path"].value_or("resources/smiley.png");
        int width = 0, height = 0, sourceNumChannels = 0;
        stbi_uc *pixels = nullptr;
        GLuint texture_id = 0;
        if (has_texture) {
            pixels = stbi_load(tex_path.c_str(), &width, &height, &sourceNumChannels, STBI_rgb);
            glGenTextures(1, &texture_id);
            glBindTexture(GL_TEXTURE_2D, texture_id);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
            glGenerateMipmap(GL_TEXTURE_2D);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
        lights.emplace_back(Light{pos, color, is_spotlight, direction, has_texture, {width, height, sourceNumChannels, pixels, texture_id}});
    }
}


// Program entry point. Everything starts here.
int main(int argc, char **argv) {

    // read toml file from argument line (otherwise use default file)
    std::string config_filename = argc == 2 ? std::string(argv[1]) : "resources/default_scene.toml";

    // parse initial scene config
    try {
        config = toml::parse_file(std::string(RESOURCE_ROOT) + config_filename);
    } catch (const toml::parse_error &) {
        std::cerr << "parsing failed" << std::endl;
    }

    // read material data
    shadingData.kd = tomlArrayToVec3(config["material"]["kd"].as_array()).value();
    shadingData.ks = tomlArrayToVec3(config["material"]["ks"].as_array()).value();
    shadingData.shininess = config["material"]["shininess"].value_or(0.0f);
    shadingData.toonDiscretize = (int) config["material"]["toonDiscretize"].value_or(0);
    shadingData.toonSpecularThreshold = config["material"]["toonSpecularThreshold"].value_or(0.0f);

    // Create window
    Window window{"Shading", glm::ivec2(WIDTH, HEIGHT), OpenGLVersion::GL41};

    readLights();


// read camera settings
    auto look_at = tomlArrayToVec3(config["camera"]["lookAt"].as_array()).value();
    auto rotations = tomlArrayToVec3(config["camera"]["rotations"].as_array()).value();
    float fovY = config["camera"]["fovy"].value_or(50.0f);
    float dist = config["camera"]["dist"].value_or(1.0f);

    auto diffuse_model = config["render_settings"]["diffuse_model"].value<std::string>();
    auto specular_model = config["render_settings"]["specular_model"].value<std::string>();
    bool do_pcf = config["render_settings"]["pcf"].value<bool>().value();
    bool do_shadows = config["render_settings"]["shadows"].value<bool>().value();

    Trackball trackball{&window, glm::radians(fovY)};
    trackball.setCamera(look_at, rotations, dist);

// read mesh
    bool animated = config["mesh"]["animated"].value_or(false);
    auto mesh_path = std::string(RESOURCE_ROOT) + config["mesh"]["path"].value_or("resources/dragon.obj");

    std::cout << mesh_path << std::endl;

    const Mesh mesh = loadMesh(mesh_path)[0];

    window.registerKeyCallback([&](int key, int /* scancode */, int action, int /* mods */) {
        if (key == '\\' && action == GLFW_PRESS) {
            show_imgui = !show_imgui;
        }

        if (action != GLFW_RELEASE)
            return;

        const bool shiftPressed = window.isKeyPressed(GLFW_KEY_LEFT_SHIFT) || window.isKeyPressed(GLFW_KEY_RIGHT_SHIFT);

        switch (key) {
            case GLFW_KEY_0: {
                debug = !debug;
                break;
            }
            case GLFW_KEY_1: {
                diffuseLighting = !diffuseLighting;
                break;
            }
            case GLFW_KEY_2: {
                phongSpecularLighting = !phongSpecularLighting;
                break;
            }
            case GLFW_KEY_3: {
                blinnPhongSpecularLighting = !blinnPhongSpecularLighting;
                break;
            }
            case GLFW_KEY_4: {
                toonLightingDiffuse = !toonLightingDiffuse;
                break;
            }
            case GLFW_KEY_5: {
                toonLightingSpecular = !toonLightingSpecular;
                if (toonLightingSpecular)
                    toonLightingDiffuse = true;
                break;
            }
            case GLFW_KEY_6: {
                toonxLighting = !toonxLighting;
                break;
            }
            case GLFW_KEY_7: {
                distanceShaderEnabled = !distanceShaderEnabled;
                break;
            }
            case GLFW_KEY_M: {
                interfaceLightPlacement = static_cast<LightPlacementValue>((static_cast<int>(interfaceLightPlacement) + 1) % 3);
                break;
            }
            case GLFW_KEY_L: {
                if (shiftPressed)
                    lights.push_back(Light{trackball.position(), glm::vec3(1)});
                else
                    lights[selectedLightIndex].position = trackball.position();
                return;
            }
            case GLFW_KEY_MINUS: {
                selectPreviousLight();

                return;
            }
            case GLFW_KEY_EQUAL: {
                if (shiftPressed) // '+' pressed (unless you use a weird keyboard layout).
                    selectNextLight();

                return;
            }
            case GLFW_KEY_N: {
                resetLights();

                return;
            }
            case GLFW_KEY_SPACE: {
                const auto optWorldPoint = getWorldPositionOfPixel(trackball, window.getCursorPixel());
                if (optWorldPoint) {
// std::cout << "World point: (" << optWorldPoint->x << ", " << optWorldPoint->y << ", " << optWorldPoint->z << ")" << std::endl;
// lights[selectedLightIndex].position = worldPoint;
                    const size_t selectedVertexIdx = getClosestVertexIndex(mesh, *optWorldPoint);
                    if (selectedVertexIdx != 0xFFFFFFFF) {
                        const Vertex &selectedVertex = mesh.vertices[selectedVertexIdx];
                        userInteraction(trackball.

                                position(), selectedVertex

                                                .position, selectedVertex.normal);
                    }
                }
                return;
            }

            case GLFW_KEY_T: {
                if (shiftPressed)
                    shadingData.toonSpecularThreshold += 0.001f;
                else
                    shadingData.toonSpecularThreshold -= 0.001f;
                std::cout << "ToonSpecular: " << shadingData.toonSpecularThreshold << std::endl;
                return;
            }
            case GLFW_KEY_D: {
                if (shiftPressed) {
                    ++shadingData.toonDiscretize;
                } else {
                    if (--shadingData.toonDiscretize < 1)
                        shadingData.toonDiscretize = 1;
                }
                std::cout << "Toon Discretization levels: " << shadingData.toonDiscretize << std::endl;
                return;
            }
            case GLFW_KEY_R: {
                if (shiftPressed) {
// Decrease diffuse Kd coefficient in the red channel by 0.1
                } else {
// Increase diffuse Kd coefficient in the red channel by 0.1
                }
                return;
            }
            case GLFW_KEY_G: {
// Same for green.
                return;
            }
            case GLFW_KEY_B: {
// Same for blue.
                return;
            }
            default:
                return;
        };

        if (!toonLightingDiffuse && !toonxLighting) {
            std::cout << "REALISTIC SHADING!" << std::endl;
            std::cout << "__________________" << std::endl;
            if (diffuseLighting) {
                std::cout << ("DiffuseLighting ON") << std::endl;
            } else {
                std::cout << ("DiffuseLighting OFF") << std::endl;
            }

            if (phongSpecularLighting) {
                std::cout << "PhongSpecularLighting ON" << std::endl;
                std::cout << "BlinnPhongSpecularLighting IGNORED" << std::endl;
            } else if (blinnPhongSpecularLighting) {
                std::cout << "PhongSpecularLighting OFF" << std::endl;
                std::cout << "BlinnPhongSpecularLighting ON" << std::endl;
            } else {
                std::cout << "PhongSpecularLighting OFF" << std::endl;
                std::cout << "BlinnPhongSpecularLighting OFF" << std::endl;
            }
        } else {
            std::cout << "TOON SHADING!" << std::endl;
            std::cout << "_____________" << std::endl;
            if (toonxLighting) {
                std::cout << "ToonLightingDiffuse IGNORED" << std::endl;
                std::cout << "ToonLightingSpecular IGNORED" << std::endl;
                std::cout << "ToonX ON" << std::endl;
            } else {
                if (toonLightingDiffuse) {
                    std::cout << "ToonLightingDiffuse ON" << std::endl;
                } else {
                    std::cout << "ToonLightingDiffuse OFF" << std::endl;
                }

                if (toonLightingSpecular) {
                    std::cout << "ToonLightingSpecular ON" << std::endl;
                } else {
                    std::cout << "ToonLightingSpecular OFF" << std::endl;
                }
                std::cout << "ToonX OFF" << std::endl;
            }
        }

        switch (interfaceLightPlacement) {
            case LightPlacementValue::Sphere: {
                std::cout << "Interaction: LightPlacementValue::Sphere" << std::endl;
                break;
            }
            case LightPlacementValue::Shadow: {
                std::cout << "Interaction: LightPlacementValue::Shadow" << std::endl;
                break;
            }
            case LightPlacementValue::Specular: {
                std::cout << "Interaction: LightPlacementValue::Specular" << std::endl;
                break;
            }
        };
    });

    const Shader debugShader = ShaderBuilder().addStage(GL_VERTEX_SHADER, RESOURCE_ROOT "shaders/vertex.glsl").addStage(GL_FRAGMENT_SHADER, RESOURCE_ROOT "shaders/debug_frag.glsl").build();
    const Shader lambertShader = ShaderBuilder().addStage(GL_VERTEX_SHADER, RESOURCE_ROOT "shaders/vertex.glsl").addStage(GL_FRAGMENT_SHADER, RESOURCE_ROOT "shaders/lambert_frag.glsl").build();
    const Shader phongShader = ShaderBuilder().addStage(GL_VERTEX_SHADER, RESOURCE_ROOT "shaders/vertex.glsl").addStage(GL_FRAGMENT_SHADER, RESOURCE_ROOT "shaders/phong_frag.glsl").build();
    const Shader blinnPhongShader = ShaderBuilder().addStage(GL_VERTEX_SHADER, RESOURCE_ROOT "shaders/vertex.glsl").addStage(GL_FRAGMENT_SHADER, RESOURCE_ROOT "shaders/blinn_phong_frag.glsl").build();

    const Shader toonDiffuseShader = ShaderBuilder().addStage(GL_VERTEX_SHADER, RESOURCE_ROOT "shaders/vertex.glsl").addStage(GL_FRAGMENT_SHADER,
                                                                                                                              RESOURCE_ROOT "shaders/toon_diffuse_frag.glsl").build();
    const Shader toonSpecularShader = ShaderBuilder().addStage(GL_VERTEX_SHADER, RESOURCE_ROOT "shaders/vertex.glsl").addStage(GL_FRAGMENT_SHADER,
                                                                                                                               RESOURCE_ROOT "shaders/toon_specular_frag.glsl").build();
    const Shader xToonShader = ShaderBuilder().addStage(GL_VERTEX_SHADER, RESOURCE_ROOT "shaders/vertex.glsl").addStage(GL_FRAGMENT_SHADER, RESOURCE_ROOT "shaders/x_toon_frag.glsl").build();

    const Shader lightShader = ShaderBuilder().addStage(GL_VERTEX_SHADER, RESOURCE_ROOT "shaders/light_vertex.glsl").addStage(GL_FRAGMENT_SHADER, RESOURCE_ROOT "shaders/light_frag.glsl").build();

    const Shader distanceShader = ShaderBuilder().addStage(GL_VERTEX_SHADER, RESOURCE_ROOT "shaders/vertex.glsl").addStage(GL_FRAGMENT_SHADER, RESOURCE_ROOT "shaders/distance_frag.glsl").build();

    // Create Vertex Buffer Object and Index Buffer Objects.
    GLuint vbo;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(mesh.vertices.size() * sizeof(Vertex)), mesh.vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint ibo;
    // Create index buffer object (IBO)
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(mesh.triangles.size() * sizeof(decltype(Mesh::triangles)::value_type)), mesh.triangles.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Bind vertex data to shader inputs using their index (location).
    // These bindings are stored in the Vertex Array Object.
    GLuint vao;
    // Create VAO and bind it so subsequent creations of VBO and IBO are bound to this VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    // The position and normal vectors should be retrieved from the specified Vertex Buffer Object.
    // The stride is the distance in bytes between vertices. We use the offset to point to the normals
    // instead of the positions.
    // Tell OpenGL that we will be using vertex attributes 0 and 1.
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // Load image from disk to CPU memory.
    int width, height, sourceNumChannels; // Number of channels in source image. pixels will always be the requested number of channels (3).
    stbi_uc *pixels = stbi_load(RESOURCE_ROOT "resources/toon_map.png", &width, &height, &sourceNumChannels, STBI_rgb);

    // Create a texture on the GPU with 3 channels with 8 bits each.
    GLuint texToon;
    glGenTextures(1, &texToon);
    glBindTexture(GL_TEXTURE_2D, texToon);

    // Set behavior for when texture coordinates are outside the [0, 1] range.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Set interpolation for texture sampling (GL_NEAREST for no interpolation).
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

    // Free the CPU memory after we copied the image to the GPU.
    stbi_image_free(pixels);


    glBindVertexArray(0);

    // Enable depth testing.
    glEnable(GL_DEPTH_TEST);

    // Main loop.
    while (!window.shouldClose()) {
        window.updateInput();
        imgui();

        // Clear the framebuffer to black and depth to maximum value (ranges from [-1.0 to +1.0]).
        glViewport(0, 0, window.getWindowSize().x, window.getWindowSize().y);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set model/view/projection matrix.
        const glm::vec3 cameraPos = trackball.position();
        const glm::mat4 model{1.0f};

        const glm::mat4 view = trackball.viewMatrix();
        const glm::mat4 projection = trackball.projectionMatrix();
        const glm::mat4 mvp = projection * view * model;

        auto render = [&](const Shader &shader) {
            // Set the model/view/projection matrix that is used to transform the vertices in the vertex shader.
            glUniformMatrix4fv(shader.getUniformLocation("mvp"), 1, GL_FALSE, glm::value_ptr(mvp));
            // Bind vertex data.
            glBindVertexArray(vao);
            // We tell OpenGL what each vertex looks like and how they are mapped to the shader using the names
            // NOTE: Usually this can be stored in the VAO, since the locations would be the same in all shaders by using the layout(location = ...) qualifier in the shaders, however this does not work on apple devices.
            glVertexAttribPointer(shader.getAttributeLocation("pos"), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, position));
            glVertexAttribPointer(shader.getAttributeLocation("normal"), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, normal));
            // Execute draw command.
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh.triangles.size()) * 3, GL_UNSIGNED_INT, nullptr);
            // Check for OpenGL errors
            auto error = glGetError();
            if (error != GL_NO_ERROR) {
                std::cerr << "OpenGL error after drawing: " << error << std::endl;
            }
            glBindVertexArray(0);
        };

        if (debug) {
            debugShader.bind();
            render(debugShader);
        }

        if (distanceShaderEnabled) {
            distanceShader.bind();
            glUniform3fv(distanceShader.getUniformLocation("viewPos"), 1, glm::value_ptr(cameraPos));
            render(distanceShader);
        }


        if (!debug) {
            // Draw mesh into depth buffer but disable color writes.
            glDepthMask(GL_TRUE);
            glDepthFunc(GL_LEQUAL);
            glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
            debugShader.bind();
            render(debugShader);

            // Draw the mesh again for each light / shading model.
            glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); // Enable color writes.
            glDepthMask(GL_FALSE); // Disable depth writes.
            glDepthFunc(GL_EQUAL); // Only draw a pixel if it's depth matches the value stored in the depth buffer.
            glEnable(GL_BLEND); // Enable blending.
            glBlendFunc(GL_SRC_ALPHA, GL_ONE); // Additive blending.



            for (const Light &light: lights) {

                if (toonxLighting) {
                    xToonShader.bind();
                    glUniform3fv(xToonShader.getUniformLocation("lightPos"), 1, glm::value_ptr(light.position));
                    glUniform3fv(xToonShader.getUniformLocation("lightColor"), 1, glm::value_ptr(light.color));
                    glUniform3fv(xToonShader.getUniformLocation("kd"), 1, glm::value_ptr(shadingData.kd));
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, texToon);
                    glUniform1i(xToonShader.getUniformLocation("texToon"), 0);
                    render(xToonShader);
                } else {
                    if (toonLightingDiffuse) {
                        toonDiffuseShader.bind();
                        glUniform3fv(toonDiffuseShader.getUniformLocation("lightPos"), 1, glm::value_ptr(light.position));
                        glUniform3fv(toonDiffuseShader.getUniformLocation("lightColor"), 1, glm::value_ptr(light.color));
                        glUniform3fv(toonDiffuseShader.getUniformLocation("kd"), 1, glm::value_ptr(shadingData.kd));
                        glUniform1i(toonDiffuseShader.getUniformLocation("toonDiscretize"), shadingData.toonDiscretize);
                        render(toonDiffuseShader);
                    }
                    if (toonLightingSpecular) {
                        toonSpecularShader.bind();
                        glUniform3fv(toonSpecularShader.getUniformLocation("lightPos"), 1, glm::value_ptr(light.position));
                        glUniform3fv(toonSpecularShader.getUniformLocation("lightColor"), 1, glm::value_ptr(light.color));
                        glUniform3fv(toonSpecularShader.getUniformLocation("ks"), 1, glm::value_ptr(shadingData.ks));
                        glUniform1f(toonSpecularShader.getUniformLocation("shininess"), shadingData.shininess);
                        glUniform3fv(toonSpecularShader.getUniformLocation("viewPos"), 1, glm::value_ptr(cameraPos));
                        glUniform1f(toonSpecularShader.getUniformLocation("toonSpecularThreshold"), shadingData.toonSpecularThreshold);
                        render(toonSpecularShader);
                    }
                }

                if (diffuseLighting) {
                    lambertShader.bind();
                    glUniform3fv(lambertShader.getUniformLocation("lightPos"), 1, glm::value_ptr(light.position));
                    glUniform3fv(lambertShader.getUniformLocation("lightColor"), 1, glm::value_ptr(light.color));
                    glUniform3fv(lambertShader.getUniformLocation("kd"), 1, glm::value_ptr(shadingData.kd));
                    render(lambertShader);
                }

                if (phongSpecularLighting || blinnPhongSpecularLighting) {
                    const Shader &shader = phongSpecularLighting ? phongShader : blinnPhongShader;
                    shader.bind();
                    glUniform3fv(shader.getUniformLocation("lightPos"), 1, glm::value_ptr(light.position));
                    glUniform3fv(shader.getUniformLocation("lightColor"), 1, glm::value_ptr(light.color));
                    glUniform3fv(shader.getUniformLocation("ks"), 1, glm::value_ptr(shadingData.ks));
                    glUniform1f(shader.getUniformLocation("shininess"), shadingData.shininess);
                    glUniform3fv(shader.getUniformLocation("viewPos"), 1, glm::value_ptr(cameraPos));
                    render(shader);
                }
            }
            // Restore default depth test settings and disable blending.
            glDepthFunc(GL_LEQUAL);
            glDepthMask(GL_TRUE);
            glDisable(GL_BLEND);
        }
        lightShader.bind();
        for (const Light &light: lights) {
            const glm::vec4 screenPos = mvp * glm::vec4(light.position, 1.0f);
            glPointSize(40.0f);
            glUniform4fv(lightShader.getUniformLocation("pos"), 1, glm::value_ptr(screenPos));
            glUniform3fv(lightShader.getUniformLocation("color"), 1, glm::value_ptr(light.color));
            glUniform1i(lightShader.getUniformLocation("useTexture"), light.has_texture);

            if (light.has_texture && light.texture.texture_data) {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, light.texture.texture_id);
                glUniform1i(lightShader.getUniformLocation("lightTexture"), 0);
            }

            glBindVertexArray(vao);
            glDrawArrays(GL_POINTS, 0, 1);
            glBindVertexArray(0);

            if (light.has_texture) {
                glBindTexture(GL_TEXTURE_2D, 0);
            }
        }
        // Present result to the screen.
        window.swapBuffers();
    }

    // Be a nice citizen and clean up after yourself.
    glDeleteTextures(1, &texToon);

    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
    glDeleteVertexArrays(1, &vao);
    cleanLights();
    return 0;
}

// User interaction - when the user chooses a vertex, you receive its position, normal, its index
// you can use it to NOW modify all global variables, such as the light position, or change material properties etc.
static void userInteraction(const glm::vec3 &cameraPos, const glm::vec3 &selectedPos, const glm::vec3 &selectedNormal) {
    switch (interfaceLightPlacement) {
        case LightPlacementValue::Sphere: {
            lights[selectedLightIndex].position = userInteractionSphere(selectedPos, cameraPos);
            break;
        }
        case LightPlacementValue::Shadow: {
            lights[selectedLightIndex].position = userInteractionShadow(selectedPos, selectedNormal, lights[selectedLightIndex].position);
            break;
        }
        case LightPlacementValue::Specular: {
            lights[selectedLightIndex].position = userInteractionSpecular(selectedPos, selectedNormal, lights[selectedLightIndex].position, cameraPos);
            break;
        }
    }
}

static size_t getClosestVertexIndex(const Mesh &mesh, const glm::vec3 &pos) {
    const auto iter = std::min_element(std::begin(mesh.vertices), std::end(mesh.vertices), [&](const Vertex &lhs, const Vertex &rhs) {
        return glm::length(lhs.position - pos) < glm::length(rhs.position - pos);
    });
    return (size_t) std::distance(std::begin(mesh.vertices), iter);
}

static std::optional<glm::vec3> getWorldPositionOfPixel(const Trackball &trackball, const glm::vec2 &pixel) {
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
    const glm::vec3 win{pixel, depth};

    // View matrix
    const glm::mat4 view = trackball.viewMatrix();
    const glm::mat4 projection = trackball.projectionMatrix();

    const glm::vec4 viewport{0, 0, WIDTH, HEIGHT};
    return glm::unProject(win, view, projection, viewport);
}
