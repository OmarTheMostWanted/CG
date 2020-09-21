// Include the header files we need.
// !!! YOU DO NOT NEED TO CHANGE THIS !!!
#pragma once
// Suppress warnings in third-party code.
#include "disable_all_warnings.h"
DISABLE_WARNINGS_PUSH()
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <gsl-lite/gsl-lite.hpp>
DISABLE_WARNINGS_POP()
#include <vector>

struct ArmSegment {
    // Rotation around the positive x axis (glm::vec3(1,0,0)) in radians.
    float rotationX { 0.0f };
    glm::vec3 boxSize;
};

std::vector<glm::mat4> computeRobotArmTransforms(gsl::span<const ArmSegment> armSegments);
