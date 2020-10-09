#include "draw.h"
#include "disable_all_warnings.h"
#include "opengl_includes.h"
// Suppress warnings in third-party code.
DISABLE_WARNINGS_PUSH()
#ifdef __APPLE__
#include <OpenGL/GLU.h>
#else
#ifdef WIN32
// Windows.h includes a ton of stuff we don't need, this macro tells it to include less junk.
#define WIN32_LEAN_AND_MEAN
// Disable legacy macro of min/max which breaks completely valid C++ code (std::min/std::max won't work).
#define NOMINMAX
// GLU requires Windows.h on Windows :-(.
#include <Windows.h>
#endif
#include <GL/glu.h>
#endif
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
DISABLE_WARNINGS_POP()
#include <algorithm>

static void setMaterial(const Material& material)
{
    // Set the material color of the shape.
    glColor3fv(glm::value_ptr(material.kd));
}

void drawShape(const Mesh& mesh)
{
    setMaterial(mesh.material);

    glBegin(GL_TRIANGLES);
    for (const auto& triangleIndex : mesh.triangles) {
        for (int i = 0; i < 3; i++) {
            const auto& vertex = mesh.vertices[triangleIndex[i]];
            glNormal3fv(glm::value_ptr(vertex.n)); // Normal.
            glVertex3fv(glm::value_ptr(vertex.p)); // Position.
        }
    }
    glEnd();
}

void drawShape(const Sphere& sphere)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    const glm::mat4 transform = glm::translate(glm::identity<glm::mat4>(), sphere.center);
    glMultMatrixf(glm::value_ptr(transform));

    setMaterial(sphere.material);
    auto quadric = gluNewQuadric();
    gluSphere(quadric, sphere.radius, 50, 20);
    gluDeleteQuadric(quadric);

    glPopMatrix();
}

void drawShape(const AxisAlignedBox& box)
{
    setMaterial(box.material);

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushMatrix();

    // front      back
    // 3 ----- 2  7 ----- 6
    // |       |  |       |
    // |       |  |       |
    // 0 ------1  4 ------5

    glBegin(GL_QUADS);
    glNormal3f(0, 0, -1);
    glVertex3f(box.lower.x, box.upper.y, box.lower.z); //3
    glVertex3f(box.upper.x, box.upper.y, box.lower.z); //2
    glVertex3f(box.upper.x, box.lower.y, box.lower.z); //1
    glVertex3f(box.lower.x, box.lower.y, box.lower.z); //0

    glNormal3f(0, 0, 1);
    glVertex3f(box.upper.x, box.lower.y, box.upper.z); //5
    glVertex3f(box.upper.x, box.upper.y, box.upper.z); //6
    glVertex3f(box.lower.x, box.upper.y, box.upper.z); //7
    glVertex3f(box.lower.x, box.lower.y, box.upper.z); //4

    glNormal3f(1, 0, 0);
    glVertex3f(box.upper.x, box.upper.y, box.lower.z); //2
    glVertex3f(box.upper.x, box.upper.y, box.upper.z); //6
    glVertex3f(box.upper.x, box.lower.y, box.upper.z); //5
    glVertex3f(box.upper.x, box.lower.y, box.lower.z); //1

    glNormal3f(-1, 0, 0);
    glVertex3f(box.lower.x, box.lower.y, box.upper.z); //4
    glVertex3f(box.lower.x, box.upper.y, box.upper.z); //7
    glVertex3f(box.lower.x, box.upper.y, box.lower.z); //3
    glVertex3f(box.lower.x, box.lower.y, box.lower.z); //0

    glNormal3f(0, 1, 0);
    glVertex3f(box.lower.x, box.upper.y, box.upper.z); //7
    glVertex3f(box.upper.x, box.upper.y, box.upper.z); //6
    glVertex3f(box.upper.x, box.upper.y, box.lower.z); //2
    glVertex3f(box.lower.x, box.upper.y, box.lower.z); //3

    glNormal3f(0, -1, 0);
    glVertex3f(box.upper.x, box.lower.y, box.lower.z); //1
    glVertex3f(box.upper.x, box.lower.y, box.upper.z); //5
    glVertex3f(box.lower.x, box.lower.y, box.upper.z); //4
    glVertex3f(box.lower.x, box.lower.y, box.lower.z); //0
    glEnd();

    glPopMatrix();
    glPopAttrib();
}

void drawScene(const Scene& scene)
{
    for (const auto& mesh : scene.meshes)
        drawShape(mesh);
    for (const auto& sphere : scene.spheres)
        drawShape(sphere);
    for (const auto& box : scene.boxes)
        drawShape(box);
}

void drawRay(const Ray& ray)
{
    const glm::vec3 hitPoint = ray.origin + std::clamp(ray.t, 0.0f, 100.0f) * ray.direction;

    bool hit = false;
    if (ray.t < std::numeric_limits<float>::max())
        hit = true;

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);

    if (hit)
        glColor3f(0, 1, 1);
    else
        glColor3f(1, 0, 0);
    glVertex3fv(glm::value_ptr(ray.origin));
    if (hit)
        glColor3f(0, 0, 1);
    else
        glColor3f(1, 1, 0);
    glVertex3fv(glm::value_ptr(hitPoint));
    glEnd();

    if (hit) {
        drawShape(Sphere { hitPoint, 0.005f, Material { glm::vec3(0, 1, 0) } });
    }

    glPopAttrib();
}
