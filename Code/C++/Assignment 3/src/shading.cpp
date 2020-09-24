#include "shading.h"
DISABLE_WARNINGS_PUSH()
#include <glm/geometric.hpp>
#include <glm/vec3.hpp>
DISABLE_WARNINGS_POP()
#include <iostream>

// For debugging purposes or variable changes (e.g., modify the toon threshold as done below).
// Please notice that some keys are already in use!
void yourKeyboardFunction(unsigned char key, ShadingData& shadingData)
{
    std::cout << "Key not used so far, so executing your code!" << std::endl;

    //recolor the mesh
    switch (key) {
    case 't':
        shadingData.toonSpecularThreshold -= 0.001f;
        break;
    case 'T':
        shadingData.toonSpecularThreshold += 0.001f;
        break;
    case 'd':
        shadingData.toonDiscretize = std::max(1, shadingData.toonDiscretize - 1);
        break;
    case 'D':
        shadingData.toonDiscretize += 1;
        break;
    }

    std::cout << "ToonSpecular" << shadingData.toonSpecularThreshold << std::endl;
    std::cout << "Toon Discretization levels" << shadingData.toonDiscretize << std::endl;
}

// Debug function.
glm::vec3 debugColor(const ShadingData& shadingData, const glm::vec3& vertexPos, const glm::vec3& normal, const glm::vec3& lightPos, const glm::vec3& cameraPos)
{
    // This function you can use in any way you like!
    // E.g., for debugging purposes!
    return normal;
    // or:
    //return shadingData.Kd;
}

// Standard lambertian shading: Kd * dot(N,L), clamped to zero when negative. Where L is the light vector.
glm::vec3 diffuseOnly(const ShadingData& shadingData, const glm::vec3& vertexPos, const glm::vec3& normal, const glm::vec3& lightPos)
{
    return glm::vec3(0, 0, 1);
}

// Phong (!) Shading Specularity (http://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_shading_model)
// Follow the course, only calculate Ks pow(dot(V,R),shininess), where V is the view vector and R is the Reflection vector of the light (like in pool billard computed from the LightPos, vertexPos and normal).
// When computing specularities like this, verify that the light is on the right side of the surface, with respect to the normal
// E.g., for a plane, the light source below the plane cannot cast light on the top, hence, there can also not be any specularity.
glm::vec3 phongSpecularOnly(const ShadingData& shadingData, const glm::vec3& vertexPos, const glm::vec3& normal, const glm::vec3& lightPos, const glm::vec3& cameraPos)
{
    return glm::vec3(0, 1, 0);
}

// Blinn-Phong Shading Specularity (http://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_shading_model)
// Be careful!!! The pseudo code does some additional modifications to the formula seen in the course.
// Follow the course version and calculate ONLY Ks * pow(dot(N,H), shininess). The definition of H is given on the page above and in the course.
// The same test as before should be used.
glm::vec3 blinnPhongSpecularOnly(const ShadingData& shadingData, const glm::vec3& vertexPos, const glm::vec3& normal, const glm::vec3& lightPos, const glm::vec3& cameraPos)
{
    return glm::vec3(0, 0, 1);
}

// Diffuse Toon Shading.
// Use the variable ToonDiscretize.
// Normal diffuse shading has values between 0 and Kd (the diffuse coefficient).
// In toon shading, these values are discretized.
// This means, there are N (ToonDiscretize) uniform intervals between 0 and Kd - in this example, we assume a single color channel, you should use the values from Kd.
// Let c(0)=0, c(1) ...c(N), c(N+1)=Kd be the boundary values of these intervals.
// For a value v in [c(i), c(i+1)), the function should return (c(i)+c(i+1))/2.
// For v=Kd, return (c(N)+c(N+1))/2, else 0.
glm::vec3 toonShadingNoSpecular(const ShadingData& shadingData, const glm::vec3& vertexPos, const glm::vec3& normal, const glm::vec3& lightPos)
{
    return glm::vec3(0.5f, 0.5f, 0.0f);
}

// Specular Toon shading.
// The goal is to add white highlights. If the Blinn-Phong Specularity (without multiplying by Ks!) has a value larger or equal to ToonSpecularThreshold,
//  then return white (vec3(1)), else return black.
glm::vec3 toonShadingOnlySpecular(const ShadingData& shadingData, const glm::vec3& vertexPos, const glm::vec3& normal, const glm::vec3& lightPos, const glm::vec3& cameraPos)
{
    return glm::vec3(0, 0, 1);
}