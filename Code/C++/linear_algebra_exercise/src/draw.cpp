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
#include <iostream>

void drawSphere(const glm::vec3& position, float radius)
{
    glColor3f(0.8f, 0.8f, 0.1f);
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

void drawTriangle(const Triangle& triangle, const bool frontfacing)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glBegin(GL_TRIANGLES);
    glColor3f(0.8f, 0.8f, 0.1f);
    glNormal3f(triangle.n.x, triangle.n.y, triangle.n.z);
    glVertex3f(triangle.v0.x, triangle.v0.y, triangle.v0.z);
    glVertex3f(triangle.v1.x, triangle.v1.y, triangle.v1.z);
    glVertex3f(triangle.v2.x, triangle.v2.y, triangle.v2.z);
    glEnd();

    glLineWidth(3.0);
    glBegin(GL_LINES);
    if (frontfacing)
        glColor3f(0.4f, 0.8f, 0.4f);
    else
        glColor3f(0.8f, 0.4f, 0.4f);
    glm::vec3 centre = (triangle.v0 + triangle.v1 + triangle.v2) / 3.0f;
    glVertex3f(centre.x, centre.y, centre.z);
    glVertex3f(centre.x + triangle.n.x, centre.y + triangle.n.y, centre.z + triangle.n.z);
    glEnd();
    glLineWidth(1.0);
}

void drawPlane(const Plane& plane, const bool front)
{

    // perpendicular vector to create quads corners
    glm::vec3 perp;
    if (std::abs(plane.n.z) < std::abs(plane.n.x))
        perp = glm::vec3(plane.n.y, -plane.n.x, 0.0);
    else
        perp = glm::vec3(0.0, -plane.n.z, plane.n.y);

    perp = glm::normalize(perp);
    glm::vec3 perp2 = glm::cross(perp, plane.n);
    glm::vec3 v;
    float scale = 10.0f;

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glBegin(GL_QUADS);

    if (front)
        glColor3f(0.4f, 0.8f, 0.4f);
    else
        glColor3f(0.8f, 0.4f, 0.4f);

    v = plane.p + perp * scale;
    glVertex3f(v.x, v.y, v.z);
    v = plane.p + perp2 * scale;
    glVertex3f(v.x, v.y, v.z);
    v = plane.p - perp * scale;
    glVertex3f(v.x, v.y, v.z);
    v = plane.p - perp2 * scale;
    glVertex3f(v.x, v.y, v.z);

    glEnd();

    glLineWidth(3.0);
    glBegin(GL_LINES);
    glColor3f(0.8f, 0.8f, 0.8f);

    glVertex3f(plane.p.x, plane.p.y, plane.p.z);
    glVertex3f(plane.p.x + plane.n.x, plane.p.y + plane.n.y, plane.p.z + plane.n.z);
    glEnd();
    glLineWidth(1.0);

    glPopMatrix();
}

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
