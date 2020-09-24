#include "disable_all_warnings.h"
#include "shading_data.h"
DISABLE_WARNINGS_PUSH()
#include <glm/geometric.hpp>
#include <glm/vec3.hpp>
DISABLE_WARNINGS_POP()
#include <iostream>

glm::vec3 userInteractionSphere(const glm::vec3& selectedPos, const glm::vec3& camPos)
{
    // RETURN the new light position, defined as follows:
    // selectedPos is a location on the mesh. Use this location to place the light source to cover the location as seen from camPos (cover the cursor).
    // Further, the light should be at a distance of 1.5 from the origin of the scene - in other words, located on a sphere of radius 1.5 around the origin.
    // The selectedPos is guaranteed to always be within the sphere.
    return glm::vec3(1, 1, 1);
}

glm::vec3 userInteractionShadow(const glm::vec3& selectedPos, const glm::vec3& selectedNormal, const glm::vec3& lightPos)
{
    // RETURN the new light position such that the light towards the selectedPos is orthgonal to the normal at that location
    // --- in this way, the shading boundary will be exactly at this location.
    // there are several ways to do this, choose one you deem appropriate given the current light position
    // no panic, I will not judge what solution you chose, as long as the above condition is met.
    return glm::vec3(1, 0, 1);
}

glm::vec3 userInteractionSpecular(const glm::vec3& selectedPos, const glm::vec3& selectedNormal, const glm::vec3& cameraPos)
{
    // RETURN the new light position such that a specularity (highlight) will be located at selectedPos, when viewed from cameraPos.
    // Please ensure also that the light is at a distance of 1 from selectedPos!
    // There is only ONE way of doing this!
    return glm::vec3(0, 1, 1);
}