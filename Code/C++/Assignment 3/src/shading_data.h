#pragma once
#include "disable_all_warnings.h"
DISABLE_WARNINGS_PUSH()
#include <glm/vec3.hpp>
DISABLE_WARNINGS_POP()

struct ShadingData {
    glm::vec3 Kd { 0.5f, 0.5f, 0.5f }; // Diffuse coefficient per vertex.
    glm::vec3 Ks { 0.5f, 0.5f, 0.5f }; // Specularity coefficient per vertex.
    float shininess = 20.0f; // Exponent for phong and blinn-phong specularities per vertex.
    int toonDiscretize = 4; // Number of levels in toon shading.
    float toonSpecularThreshold = 0.49f; // Threshold for specularity.
};