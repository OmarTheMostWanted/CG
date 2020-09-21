#pragma once
#include "disable_all_warnings.h"
#include "opengl_includes.h"
// Suppress warnings in third-party code.
DISABLE_WARNINGS_PUSH()
#include <glm/mat4x4.hpp>
DISABLE_WARNINGS_POP()
#include <filesystem>

void drawCoordSystem(const float length = 1);
void drawCube(const glm::mat4& transform);
void drawSphere(const glm::mat4& transform, GLuint texture);
void drawSphere(const glm::vec3& position, float radius);

GLuint loadTexture(const std::filesystem::path& file);