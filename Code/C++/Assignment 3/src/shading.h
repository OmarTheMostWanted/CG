#pragma once
#include "disable_all_warnings.h"
#include "shading_data.h"
DISABLE_WARNINGS_PUSH()
#include <glm/vec3.hpp>
DISABLE_WARNINGS_POP()

// Functions that you can extend to help with debugging.
void yourKeyboardFunction(unsigned char key, ShadingData& shadingData);
glm::vec3 debugColor(const ShadingData& shadingData, const glm::vec3& vertexPos, const glm::vec3& normal, const glm::vec3& lightPos, const glm::vec3& cameraPos);

glm::vec3 diffuseOnly(const ShadingData& shadingData, const glm::vec3& vertexPos, const glm::vec3& normal, const glm::vec3& lightPos);
glm::vec3 phongSpecularOnly(const ShadingData& shadingData, const glm::vec3& vertexPos, const glm::vec3& normal, const glm::vec3& lightPos, const glm::vec3& cameraPos);
glm::vec3 blinnPhongSpecularOnly(const ShadingData& shadingData, const glm::vec3& vertexPos, const glm::vec3& normal, const glm::vec3& lightPos, const glm::vec3& cameraPos);
glm::vec3 toonShadingNoSpecular(const ShadingData& shadingData, const glm::vec3& vertexPos, const glm::vec3& normal, const glm::vec3& lightPos);
glm::vec3 toonShadingOnlySpecular(const ShadingData& shadingData, const glm::vec3& vertexPos, const glm::vec3& normal, const glm::vec3& lightPos, const glm::vec3& cameraPos);
