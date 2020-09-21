// Include the header files we need.
// !!! YOU DO NOT NEED TO CHANGE THIS !!!
#pragma once
// Suppress warnings in third-party code.
#include "disable_all_warnings.h"
DISABLE_WARNINGS_PUSH()
#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <gsl-lite/gsl-lite.hpp>
DISABLE_WARNINGS_POP()
#include <string>
#include <vector>

// Celestrial body = planet / moon / star (including the sun)
struct CelestrialBody {
    // The radius of the sphere that represents the celestrial body.
    float radius { 1.0f };
    // A celestrial body may spin around it's own axis. The speed at which it rotates is
    //  expressed as the spin period. The spin period is the amount of time (in hours) it
    // takes for the body to complete one full rotation.
    float spinPeriod { 0.0f };

    // A celestrial body may orbit another celestrial body (e.g. a moon orbiting a planet).
    // pOrbitAround stores a pointer to the object that this celestrial body is orbiting.
    // The altitude describes the distance at which the object is orbitted (as measured
    // from the center of both objects). The orbit period describes how much time it takes
    // for the celestrial body to complete one rotation around the object being orbitted.

    // The spin of the object that is orbited SHOULD NOT be added to the orbital rotation
    // of the celestrial body. Assume that the celestrial body always orbits around the y
    // axis and that at t=0 the body is to the right (positive x) of the object being orbited.
    //
    // If pOrbitAround contains a null pointer (nullptr) then the position should be to the
    // origin (and orbitAltitude/orbitVelocity may be ignored).
    CelestrialBody* pOrbitAround { nullptr };
    float orbitAltitude { 0.0f };
    float orbitPeriod { 0.0f };

    // Only used for UI & drawing. YOU DO NOT NEED TO USE THIS VARIABLES!
    std::string name;
    GLuint texture;
};

std::vector<glm::mat4> computeCelestrialBodyTransformations(gsl::span<const CelestrialBody> celestrialBodies, float time);