#include "draw.h"
#include "disable_all_warnings.h"
// Suppress warnings in third-party code.
DISABLE_WARNINGS_PUSH()
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
DISABLE_WARNINGS_POP()

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
    glVertex3f(0, 0, 1);
    glVertex3f(0, 1, 1);
    glVertex3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    // Right face.
    glNormal3f(1, 0, 0);
    glVertex3f(1, 1, 0);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 0, 1);
    glVertex3f(1, 0, 0);
    // Back face.
    glNormal3f(0, 0, 1);
    glVertex3f(1, 0, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(0, 1, 1);
    glVertex3f(0, 0, 1);
    // Front face.
    glNormal3f(0, 0, -1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);
    glVertex3f(1, 1, 0);
    glVertex3f(1, 0, 0);
    // Top face.
    glNormal3f(0, 1, 0);
    glVertex3f(0, 1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, 0);
    glVertex3f(0, 1, 0);
    // Bot face.
    glNormal3f(0, -1, 0);
    glVertex3f(1, 0, 0);
    glVertex3f(1, 0, 1);
    glVertex3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glEnd();

    glPopMatrix();
}