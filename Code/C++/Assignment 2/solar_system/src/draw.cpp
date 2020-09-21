#include "draw.h"
#include "disable_all_warnings.h"
// Suppress warnings in third-party code.
DISABLE_WARNINGS_PUSH()
#include <glad/glad.h> // Include glad before glu
#ifdef __APPLE__
#include <OpenGL/GLU.h>
#else

#ifdef _WIN32
// Windows.h includes a ton of stuff we don't need, this macro tells it to include less junk.
#define WIN32_LEAN_AND_MEAN
// Disable legacy macro of min/max which breaks completely valid C++ code (std::min/std::max won't work).
#define NOMINMAX
// GLU requires Windows.h on Windows :-(.
#include <Windows.h>
#endif
#include <GL/glu.h>

#endif
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
DISABLE_WARNINGS_POP()
#include <exception>
#include <iostream>

void drawCoordSystem(const float length)
{
    // Remember all states of the GPU.
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    // Deactivate the lighting state.
    glDisable(GL_LIGHTING);

    // Draw axes.
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(length, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, length, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, length);
    glEnd();

    // Restore previous GPU state.
    glPopAttrib();
}

void drawCube(const glm::mat4& transform)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(glm::value_ptr(transform));

    glBegin(GL_QUADS);
    // Left face.
    glNormal3f(-1, 0, 0);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, 1, 1);
    glVertex3f(-1, 1, -1);
    glVertex3f(-1, -1, -1);
    // Right face.
    glNormal3f(1, 0, 0);
    glVertex3f(1, 1, -1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, -1, -1);
    // Back face.
    glNormal3f(0, 0, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(-1, 1, 1);
    glVertex3f(-1, -1, 1);
    // Front face.
    glNormal3f(0, 0, -1);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, 1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(1, -1, -1);
    // Top face.
    glNormal3f(0, 1, 0);
    glVertex3f(-1, 1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, -1);
    glVertex3f(-1, 1, -1);
    // Bot face.
    glNormal3f(0, -1, 0);
    glVertex3f(1, -1, -1);
    glVertex3f(1, -1, 1);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, -1, -1);
    glEnd();

    glPopMatrix();
}

void drawSphere(const glm::mat4& transform, GLuint texture)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(glm::value_ptr(transform));

    auto sphere = gluNewQuadric();
    gluQuadricNormals(sphere, GLU_SMOOTH);
    gluQuadricTexture(sphere, GL_TRUE);
    gluSphere(sphere, 1.0f, 20, 10);
    gluDeleteQuadric(sphere);

    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void drawSphere(const glm::vec3& position, float radius)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    const auto translate = glm::translate(glm::identity<glm::mat4>(), position);
    glMultMatrixf(glm::value_ptr(translate));

    auto sphere = gluNewQuadric();
    gluQuadricNormals(sphere, GLU_SMOOTH);
    gluSphere(sphere, radius, 20, 10);
    gluDeleteQuadric(sphere);

    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint loadTexture(const std::filesystem::path& fileName)
{
    if (!std::filesystem::exists(fileName)) {
        std::cerr << "Texture file does not exists: " << fileName << std::endl;
        throw std::exception();
    }

    int width, height, numChannels;
    const auto fileNameStr = fileName.string(); // Create l-value so c_str() is safe.
    stbi_uc* pixels = stbi_load(fileNameStr.c_str(), &width, &height, &numChannels, STBI_rgb);

    if (!pixels) {
        std::cerr << "Failed to read texture " << fileName << " using stb_image.h" << std::endl;
        throw std::exception();
    }

    glEnable(GL_TEXTURE_2D);
    GLuint texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    stbi_image_free(pixels); // Free CPU data when the texture has been copied to the GPU.
    return texID;
}
