#include "camera.h"
// Suppress warnings in third-party code.
#include <framework/disable_all_warnings.h>
DISABLE_WARNINGS_PUSH()
// Include GLEW before GLFW
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>
// Library for loading an image
#include <stb/stb_image.h>
DISABLE_WARNINGS_POP()
#include <array>
#include <framework/mesh.h>
#include <framework/shader.h>
#include <framework/window.h>
#include <iostream>
#include <span>
#include <vector>
#include "imgui/imgui.h"

// Configuration
constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;


bool show_imgui = true;

// Assignment settings
std::array samplingModes{"Single Sample", "PCF"};
std::array peelingModes{"Lighting", "Peeling"};
std::array lightTypeModes{"Normal", "Spot light"};
std::array lightColorModes{"White", "Textured"};

// Assignment config variables, index into the above arrays
int samplingMode = 0;
int peelingMode = 0;
int lightMode = 0;
int lightColorMode = 0;

void imgui()
{
    // Define UI here
    if (!show_imgui)
        return;

    ImGui::Begin("Practical 4: Shadow Mapping");
    ImGui::Text("Press \\ to show/hide this menu");
    ImGui::Separator();
    ImGui::Combo("Sampling Mode", &samplingMode, samplingModes.data(), (int)samplingModes.size());
    ImGui::Combo("Depth Peeling", &peelingMode, peelingModes.data(), (int)peelingModes.size());
    ImGui::Combo("Spotlight", &lightMode, lightTypeModes.data(), (int)lightTypeModes.size());
    ImGui::Combo("Light Color", &lightColorMode, lightColorModes.data(), (int)lightColorModes.size());

    ImGui::End();
    ImGui::Render();
}

int main()
{
    Window window{"Shadow Mapping", glm::ivec2(WIDTH, HEIGHT), OpenGLVersion::GL41};

    Camera mainCamera{&window, glm::vec3(1.2f, 1.1f, 0.9f), -glm::vec3(1.2f, 1.1f, 0.9f), "Main Camera"};
    Camera lightCamera{&window, glm::vec3(-1.2f, 1.1f, -0.9f), -glm::vec3(-1.2f, 1.1f, -0.9f), "Light Camera"};

    Camera* activeCamera = &mainCamera;
    mainCamera.setUserInteraction(true);
    lightCamera.setUserInteraction(false);

    constexpr float fov = glm::pi<float>() / 4.0f;
    constexpr float aspect = static_cast<float>(WIDTH) / static_cast<float>(HEIGHT);
    const glm::mat4 mainProjectionMatrix = glm::perspective(fov, aspect, 0.1f, 30.0f);

    // === Modify for exercise 1 ===
    // Key handle function
    window.registerKeyCallback([&](int key, int /* scancode */, int action, int /* mods */)
    {
        if (key == '\\' && action == GLFW_PRESS)
        {
            show_imgui = !show_imgui;
        }
        if (action == GLFW_PRESS)
        {
            switch (key)
            {
            case GLFW_KEY_1:
                activeCamera = &mainCamera;
                mainCamera.setUserInteraction(true);
                lightCamera.setUserInteraction(false);
                break;
            case GLFW_KEY_2:
                activeCamera = &lightCamera;
                lightCamera.setUserInteraction(true);
                mainCamera.setUserInteraction(false);
                break;
            default:
                break;
            }
        }
    });

    const Shader lightShader = ShaderBuilder().addStage(GL_VERTEX_SHADER, RESOURCE_ROOT "shaders/light_vertex.glsl").addStage(GL_FRAGMENT_SHADER, RESOURCE_ROOT "shaders/light_frag.glsl").build();
    const Shader mainShader = ShaderBuilder().addStage(GL_VERTEX_SHADER, RESOURCE_ROOT "shaders/shader_vert.glsl").addStage(GL_FRAGMENT_SHADER, RESOURCE_ROOT "shaders/shader_frag.glsl").build();
    const Shader shadowShader = ShaderBuilder().addStage(GL_VERTEX_SHADER, RESOURCE_ROOT "shaders/shadow_vert.glsl").addStage(GL_FRAGMENT_SHADER, RESOURCE_ROOT "shaders/shadow_frag.glsl").build();

    // === Load a texture for exercise 5 ==>
    // Create Texture
    int texWidth, texHeight, texChannels;
    stbi_uc* pixels = stbi_load(RESOURCE_ROOT "resources/smiley.png", &texWidth, &texHeight, &texChannels, 3);
    GLuint texLight;
    glGenTextures(1, &texLight);
    glBindTexture(GL_TEXTURE_2D, texLight);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    // Set behaviour for when texture coordinates are outside the [0, 1] range.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // Set interpolation for texture sampling (GL_NEAREST for no interpolation).
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    // === Load a texture for exercise 5 ===?<

    // Load mesh from disk. =>
    const Mesh mesh = mergeMeshes(loadMesh(RESOURCE_ROOT "resources/scene.obj"));
    // Create Element(Index) Buffer Object and Vertex Buffer Objects.
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
    glBindVertexArray(0);
    // Load mesh from disk. =<

    // === Create Shadow Texture ===>
    GLuint texShadow;
    const int SHADOWTEX_RES = 1000;
    glGenTextures(1, &texShadow); // Generate a texture object.
    glBindTexture(GL_TEXTURE_2D, texShadow); // Bind the texture object.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, SHADOWTEX_RES, SHADOWTEX_RES, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL); // Create the texture.
    // Set behaviour for when texture coordinates are outside the [0, 1] range.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // Set interpolation for texture sampling (GL_NEAREST for no interpolation).
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
    // === Create Shadow Texture ===<

    // === Create framebuffer for extra texture ===>
    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texShadow, 0); // Attach the texture to the framebuffer.
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // Unbind the framebuffer.
    // === Create framebuffer for extra texture ===<


    // Main loop
    while (!window.shouldClose())
    {
        window.updateInput();
        imgui();

        activeCamera->updateInput();
        const glm::mat4 lightMvp = mainProjectionMatrix * lightCamera.viewMatrix(); // Assume model matrix is identity.


        // === Stub code for you to fill in order to render the shadow map ===
        {
            // Bind the off-screen framebuffer for rendering the shadow map
            glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

            // Clear the shadow map and set needed options for rendering
            glClearDepth(1.0);
            glClear(GL_DEPTH_BUFFER_BIT);
            glEnable(GL_DEPTH_TEST);

            // Bind the shader
            shadowShader.bind();

            // Set viewport size
            glViewport(0, 0, SHADOWTEX_RES, SHADOWTEX_RES);

            // .... HERE YOU MUST ADD THE CORRECT UNIFORMS FOR RENDERING THE SHADOW MAP
            // pass samplingmode as uniform

            // Set the light camera's view matrix
            glUniformMatrix4fv(shadowShader.getUniformLocation("mvp"), 1, GL_FALSE, glm::value_ptr(lightMvp));

            // Bind vertex data
            glBindVertexArray(vao);
            glVertexAttribPointer(shadowShader.getAttributeLocation("pos"), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
            // Execute draw command
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh.triangles.size() * 3), GL_UNSIGNED_INT, nullptr);
            // Unbind the off-screen framebuffer
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        // Bind the shader
        mainShader.bind();
        const glm::mat4 mvp = mainProjectionMatrix * activeCamera->viewMatrix(); // Assume model matrix is identity.
        glUniformMatrix4fv(mainShader.getUniformLocation("mvp"), 1, GL_FALSE, glm::value_ptr(mvp));
        glUniformMatrix4fv(mainShader.getUniformLocation("lightMVP"), 1, GL_FALSE, glm::value_ptr(lightMvp));
        glUniform3fv(mainShader.getUniformLocation("lightPos"), 1, glm::value_ptr(lightCamera.cameraPos()));

        // Set view position
        const glm::vec3 cameraPos = mainCamera.cameraPos();
        // glUniform3fv(mainShader.getUniformLocation("viewPos"), 1, glm::value_ptr(cameraPos));

        // .... HERE YOU MUST ADD THE CORRECT UNIFORMS FOR RENDERING THE MAIN IMAGE
        glUniform1i(mainShader.getUniformLocation("samplingMode"), samplingMode);
        glUniform1i(mainShader.getUniformLocation("peelingMode"), peelingMode);
        glUniform1i(mainShader.getUniformLocation("lightMode"), lightMode);
        glUniform1i(mainShader.getUniformLocation("lightColorMode"), lightColorMode);
        glUniform1f(mainShader.getUniformLocation("shadowMapResolution"), static_cast<float>(SHADOWTEX_RES));

        // Bind vertex data
        glBindVertexArray(vao);
        glVertexAttribPointer(mainShader.getAttributeLocation("pos"), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        glVertexAttribPointer(mainShader.getAttributeLocation("normal"), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

        // Bind the shadow map to texture slot 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texShadow);
        glUniform1i(mainShader.getUniformLocation("texShadow"), 0);

        // Set viewport size
        glViewport(0, 0, WIDTH, HEIGHT);

        // Clear the framebuffer to black and depth to maximum value
        glClearDepth(1.0);
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDisable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);

        // Execute draw command
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh.triangles.size() * 3), GL_UNSIGNED_INT, nullptr);

        // Draw lights as (square) points.
        //glDepthMask(GL_FALSE);
        lightShader.bind();
        {
            const glm::vec4 screenPos = mvp * glm::vec4(lightCamera.cameraPos(), 1.0f);
            const glm::vec3 color { 1, 1, 0 };

            glPointSize(40.0f);
            glUniform4fv(lightShader.getUniformLocation("pos"), 1, glm::value_ptr(screenPos));
            glUniform3fv(lightShader.getUniformLocation("color"), 1, glm::value_ptr(color));
            glBindVertexArray(vao);
            glDrawArrays(GL_POINTS, 0, 1);
            glBindVertexArray(0);
        }

        // Present result to the screen.
        window.swapBuffers();
    }

    // Be a nice citizen and clean up after yourself.
    glDeleteFramebuffers(1, &framebuffer);
    glDeleteTextures(1, &texShadow);
    glDeleteTextures(1, &texLight);
    glDeleteBuffers(1, &ibo);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    return 0;
}

