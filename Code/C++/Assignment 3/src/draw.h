#pragma once
#include "disable_all_warnings.h"
#include "mesh.h"
DISABLE_WARNINGS_PUSH()
#include <glm/vec3.hpp>
#include <gsl-lite/gsl-lite.hpp>
DISABLE_WARNINGS_POP()

void drawMeshWithColors(const Mesh& mesh, gsl::span<const glm::vec3> colors);