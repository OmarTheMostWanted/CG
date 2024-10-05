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
#include <framework/mesh.h>
#include <framework/shader.h>
#include <framework/trackball.h>
#include <framework/window.h>
#include <imgui/imgui.h>
#include <optional>
#include <vector>

// Configuration
const int WIDTH = 800;
const int HEIGHT = 800;

bool show_imgui = true;

void imgui()
{

    // Define UI here
    if (!show_imgui)
        return;

    ImGui::Begin("Tutorial : GLSL");
    ImGui::Text("Press \\ to show/hide this menu");

    ImGui::End();
    ImGui::Render();
}

// Program entry point. Everything starts here.
int main(int argc, char** argv)
{

    // Initialize window
    Window window { "Basic OpenGL", glm::ivec2(WIDTH, HEIGHT), OpenGLVersion::GL41 };
    Trackball trackball { &window, glm::radians(50.0f) };

    // Read Mesh
    const Mesh mesh = loadMesh(argc == 2 ? argv[1] : RESOURCE_ROOT "resources/DavidHeadCleanMax.obj")[0];

    // Read Keyboard
    window.registerKeyCallback([&](int key, int /* scancode */, int action, int /* mods */) {
        if (key == '\\' && action == GLFW_PRESS) {
            show_imgui = !show_imgui;
        }

        if (action != GLFW_RELEASE)
            return;

    });

    // Construct Shader Pipeline
    const Shader debugShader = ShaderBuilder()
                                   .addStage(GL_VERTEX_SHADER, RESOURCE_ROOT "shaders/vertex.glsl")
                                   .addStage(GL_FRAGMENT_SHADER, RESOURCE_ROOT "shaders/debug_frag.glsl")
                                   .build();

    /*
     * A Vertex Buffer Object (VBO) is an OpenGL feature that provides a method for uploading vertex data
     * (such as positions, normals, colors, etc.) to the graphics card for non-immediate-mode rendering.
     * This allows for efficient rendering of complex 3D models by storing vertex data in the GPU's memory,
     * which can be accessed quickly during rendering.
     */

    /*
     * In the context of OpenGL, "binding" refers to the process of making a specific buffer
     * or object the current target for subsequent operations.
     * When you bind a buffer, any operations you perform (such as uploading data or configuring attributes)
     * will apply to that buffer until you bind a different buffer or unbind the current one.
     */

    // Create Vertex Buffer Object and Index Buffer Objects.
    GLuint vbo;

    glGenBuffers(1, &vbo);  // generates one buffer object and stores its id in vbo variable.

    /*
     *  GL_ARRAY_BUFFER is used to store vertex attributes (e.g., position, normal, color) and is used in the vertex shader.
     */

    glBindBuffer(GL_ARRAY_BUFFER, vbo); // binds the buffer object to the target GL_ARRAY_BUFFER. Any subsequent operations will be applied to vbo buffer.

    /*
     * glBufferData is used to allocate memory for the buffer object and to copy data into it.
     * GL_STATIC_DRAW is a hint to the driver that the data will not be changed once it is uploaded to the GPU.
     */
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(mesh.vertices.size() * sizeof(Vertex)), mesh.vertices.data(), GL_STATIC_DRAW); // copies the vertex data to the buffer object.
    glBindBuffer(GL_ARRAY_BUFFER, 0); // unbinds the buffer object, 0 is used since we don't want to bind any buffer object to the target GL_ARRAY_BUFFER.

    /*
     * An Index Buffer Object (IBO) is an OpenGL feature that provides a method for uploading index data
     * to the graphics card for use in indexed rendering.
     * It indicates the order in which the vertices should be rendered to form triangles or other shapes and allows for
     * the reuse of vertices in multiple triangles.
     */

    GLuint ibo; // Index Buffer Object
    // Create index buffer object (IBO)
    glGenBuffers(1, &ibo); // generates one buffer object and stores its id in ibo variable.

    /*
     * GL_ELEMENT_ARRAY_BUFFER is used to store the indices of the vertices that form the triangles.
     */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); // binds the buffer object to the target GL_ELEMENT_ARRAY_BUFFER.
    // the size in this case if the number of triangles times 3 since each triangle has 3 vertices.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(mesh.triangles.size() * sizeof(decltype(Mesh::triangles)::value_type)), mesh.triangles.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    /*
     * A Vertex Array Object (VAO) is an OpenGL feature that provides a method for storing the state of vertex attribute
     * configurations and buffer objects.
     * It  encapsulates all the state needed to specify vertex data. It stores the configuration of vertex attribute pointers and the associated buffer objects (VBOs and IBOs).
     * By storing the configuration in a VAO, you can quickly switch between different vertex data setups without re-specifying the state.
     */

    // Bind vertex data to shader inputs using their index (location).
    // These bindings are stored in the Vertex Array Object.
    GLuint vao; // the VAO stores the configuration of how this data is used. This includes the vertex attribute pointers and the associated buffer objects.
    // Create VAO and bind it so subsequent creations of VBO and IBO are bound to this VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);  // Used when you want to switch between different sets of vertex attribute configurations.
    /* Rebinding the VBO and IBO after unbinding them is necessary
     * because the VAO needs to store the state of these buffer bindings.
     * When you bind the VAO, it captures the current state of the vertex attribute pointers
     * and the associated buffer objects. Therefore, you need to rebind
     * the VBO and IBO to ensure that the VAO correctly captures their state.
     */
    glBindBuffer(GL_ARRAY_BUFFER, vbo); // bind the VBO to the target GL_ARRAY_BUFFER again to set the vertex attribute pointers.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); // bind the IBO to the target GL_ELEMENT_ARRAY_BUFFER again to set the indices.


    // The position and normal vectors should be retrieved from the specified Vertex Buffer Object.
    // The stride is the distance in bytes between vertices. We use the offset to point to the normals
    // instead of the positions.
    // Tell OpenGL that we will be using vertex attributes 0 and 1.
    glEnableVertexAttribArray(0); // 0 is the location of the position attribute in the vertex shader.
    glEnableVertexAttribArray(1); // 1 is the location of the normal attribute in the vertex shader.

    /*
     * VertexAttribArray holds the configuration of the vertex attribute pointers, unlike the buffer objects which hold the data.
     * glVertexAttribPointer tells OpenGL how to interpret the vertex data in the VBO.
     */

    // We tell OpenGL what each vertex looks like and how they are mapped to the shader by quering the driver for its location.

    /*
     * glVertexAttribPointer tells OpenGL how to interpret the vertex data in the VBO.
     * The first parameter is the location of the vertex attribute in the shader.
     * The second parameter is the number of components per vertex attribute (3 for position and normal).
     * The third parameter is the data type of each component (GL_FLOAT).
     * The fourth parameter specifies whether the data should be normalized.
     * The fifth parameter is the stride, which is the distance in bytes between vertices.
     * The last parameter is the offset, which is the distance in bytes from the start of the vertex to the attribute.
     */

    glVertexAttribPointer(debugShader.getAttributeLocation("pos"), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glVertexAttribPointer(debugShader.getAttributeLocation("normal"), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    glBindVertexArray(0); // unbind the VAO.

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
        const glm::mat4 model { 1.0f };
        const glm::mat4 view = trackball.viewMatrix();
        const glm::mat4 projection = trackball.projectionMatrix();
        const glm::mat4 mvp = projection * view * model;

        bool renderedSomething = false;
        auto render = [&]() {
            renderedSomething = true;

            // Set the model/view/projection matrix that is used to transform the vertices in the vertex shader.
            glUniformMatrix4fv(debugShader.getUniformLocation("mvp"), 1, GL_FALSE, glm::value_ptr(mvp));

            // Bind vertex data.
            glBindVertexArray(vao);

            // Execute draw command.
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh.triangles.size()) * 3, GL_UNSIGNED_INT, nullptr);

            // Unbind vertex data.
            glBindVertexArray(0);

        };

        if (!renderedSomething) {
            debugShader.bind();
            render();
        }

        // Present result to the screen.
        window.swapBuffers();
    }

    // Be a nice citizen and clean up after yourself.
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
    glDeleteVertexArrays(1, &vao);

    return 0;
}