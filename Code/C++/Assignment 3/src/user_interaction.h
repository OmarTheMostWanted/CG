#pragma once
#include "disable_all_warnings.h"
// Disable warnings in third-party code.
DISABLE_WARNINGS_PUSH()
#include <glm/vec3.hpp>
DISABLE_WARNINGS_POP()

glm::vec3 userInteractionSphere(const glm::vec3& selectedPos, const glm::vec3& camPos);
glm::vec3 userInteractionShadow(const glm::vec3& selectedPos, const glm::vec3& selectedNormal, const glm::vec3& lightPos);
glm::vec3 userInteractionSpecular(const glm::vec3& selectedPos, const glm::vec3& selectedNormal, const glm::vec3& cameraPos);