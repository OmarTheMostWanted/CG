#include "la.h"
// Suppress warnings in third-party code.
#include "disable_all_warnings.h"

DISABLE_WARNINGS_PUSH()

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <gsl/span>

DISABLE_WARNINGS_POP()

#include <iostream>

// return True if point is on positive side of plane (or on plane), false otherwise
bool isInFront(const glm::vec3 &pt, const Plane &plane) {

    glm::vec3 point = {plane.p.x - pt.x, plane.p.y - pt.y, plane.p.z - pt.z};

    float cos = (glm::dot(plane.n, point)) / (glm::length(point) * glm::length(pt));

//    return cos < 0;  ?????


    float res = std::acos(cos);

    return (res > (float) M_PI_2);

}

// compute triangle normal
// assume that triangle vertices winding order is couter-clockwise (v0-v1-v2)
// for example, the following triangle should have its normal pointing out of the screen (towards you)
// v0 ------ v2
// \         /
//  \       /
//   \     /
//    \   /
//      v1
glm::vec3 computeNormal(const Triangle &t) {
    glm::vec3 v01 = t.v1 - t.v0;
    glm::vec3 v12 = t.v2 - t.v1;

//    return glm::normalize(glm::cross(v12 , v01));
    return glm::normalize(glm::cross(v01 , v12));

}

// check if triangle is front or backfacing given a view vector. Return true if front facing, false otherwise
bool isFrontFacing(const Triangle &triangle, const glm::vec3 camera) {
    glm::vec3 normal = computeNormal(triangle);
    float cos = (glm::dot(normal, camera)) / (glm::length(camera) * glm::length(normal));
    float res = std::acos(cos);
    return (res < (float) M_PI_2);

}
