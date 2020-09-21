// Include the header files we need.
// !!! YOU DO NOT NEED TO CHANGE THIS !!!
#pragma once
// Suppress warnings in third-party code.
#include "disable_all_warnings.h"
DISABLE_WARNINGS_PUSH()
#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <gsl/span>
DISABLE_WARNINGS_POP()
#include <string>
#include <vector>

// plane is defined by a normal and point on the plane
struct Plane {
    glm::vec3 p;
    glm::vec3 n;
};

struct Triangle {
    glm::vec3 v0;
    glm::vec3 v1;
    glm::vec3 v2;
    glm::vec3 n;
};

glm::vec3 computeNormal(const Triangle& t);

bool isInFront(const glm::vec3& pt, const Plane& plane);

bool isFrontFacing(const Triangle& t, const glm::vec3 camera);