#include "disable_all_warnings.h"
#include "shading_data.h"
DISABLE_WARNINGS_PUSH()
#include <glm/geometric.hpp>
#include <glm/vec3.hpp>
DISABLE_WARNINGS_POP()
#include <iostream>

glm::vec3 userInteractionSphere(const glm::vec3 &selectedPos, const glm::vec3 &camPos) {
    // RETURN the new light position, defined as follows:
    // selectedPos is a location on the mesh. Use this location to place the light source to cover the location as seen from camPos (cover the cursor).
    // Further, the light should be at a distance of 1.5 from the origin of the scene - in other words, located on a sphere of radius 1.5 around the origin.
    // The selectedPos is guaranteed to always be within the sphere.

    glm::vec3 ray = selectedPos - camPos;
    glm::vec3 rayDirection = glm::normalize(ray);

    glm::vec3 sphereCenter = glm::vec3(0, 0, 0);
    float radius = 1.5;

    glm::vec3 raySphereCenter = sphereCenter - camPos;

    //projecting the center of the sphere on the ray;
    float t = glm::dot(raySphereCenter, rayDirection);
    glm::vec3 projectedPoint = camPos + t * rayDirection;

    //distance from the center to the ray
    float length = glm::length(sphereCenter - projectedPoint);

    if (length > radius) { //make sure the point is inside the sphere
        return glm::vec3(0);
    }
    //distance from the projected point to the first intersection point;
//    float t1 =  glm::sqrt(pow(radius , 2) - pow(length , 2));
    float t1 = glm::sqrt((radius * radius) - (length * length));

    glm::vec3 firstIntersectionPoint = projectedPoint + (-1 * t1 * rayDirection);
    glm::vec3 SecondIntersectionPoint = projectedPoint + (+1 * t1 * rayDirection);


    return firstIntersectionPoint;
}

glm::vec3
userInteractionShadow(const glm::vec3 &selectedPos, const glm::vec3 &selectedNormal, const glm::vec3 &lightPos) {
    // RETURN the new light position such that the light towards the selectedPos is orthgonal to the normal at that location
    // --- in this way, the shading boundary will be exactly at this location.
    // there are several ways to do this, choose one you deem appropriate given the current light position
    // no panic, I will not judge what solution you chose, as long as the above condition is met.

    //auto randomRay = glm::vec3({selectedNormal.x, -1 * selectedNormal.y, selectedNormal.z});
    //return glm::normalize(glm::cross(selectedNormal, randomRay));


    auto randomRay1 = glm::vec3(0, 1, 0);
    auto randomRay2 = glm::vec3(0, 0, 1);

    //make sure the two rays are not almost pointing the same direction.
    auto choseRay = glm::dot(selectedNormal, randomRay1) > 0.95f ? randomRay1 : randomRay2;

    return glm::normalize(glm::cross(selectedNormal, choseRay));


}

glm::vec3
userInteractionSpecular(const glm::vec3 &selectedPos, const glm::vec3 &selectedNormal, const glm::vec3 &cameraPos) {
    // RETURN the new light position such that a specularity (highlight) will be located at selectedPos, when viewed from cameraPos.
    // Please ensure also that the light is at a distance of 1 from selectedPos!
    // There is only ONE way of doing this!

    glm::vec3 cameraRay = glm::normalize(selectedPos - cameraPos);
    glm::vec3  reflectedRay = cameraRay - (2 * (glm::dot(cameraRay, selectedNormal)) * selectedNormal);

    return selectedPos +  reflectedRay;
}