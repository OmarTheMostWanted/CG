#include "draw.h"
#include "window.h"
#include <glm/gtc/type_ptr.hpp>

void drawMeshWithColors(const Mesh& mesh, gsl::span<const glm::vec3> colors)
{
    glBegin(GL_TRIANGLES);
    for (const auto& triangle : mesh.indices) {
        for (int v = 0; v < 3; v++) {
            const auto& color = colors[triangle[v]];
            const auto& vertex = mesh.vertices[triangle[v]];

            glColor3fv(glm::value_ptr(color));
            glNormal3fv(glm::value_ptr(vertex.normal));
            glVertex3fv(glm::value_ptr(vertex.pos));
        }
    }
    glEnd();
}
