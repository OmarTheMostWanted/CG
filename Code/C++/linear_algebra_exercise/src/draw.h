#pragma once
#include "disable_all_warnings.h"
#include "opengl_includes.h"
// Suppress warnings in third-party code.
DISABLE_WARNINGS_PUSH()
#include <glm/mat4x4.hpp>
DISABLE_WARNINGS_POP()
#include "la.h"
#include <filesystem>

void drawCoordSystem(const float length = 1);

void drawTriangle(const Triangle& triangle, const bool frontfacing);

void drawPlane(const Plane& plane, const bool front);

void drawSphere(const glm::vec3& position, float radius);
