#pragma once
#include "scene.h"

// NOTE(Mathijs): return true if something is hit, returns false otherwise.
// Only find hits if they are closer than t stored in the ray and the intersection
// is on the correct side of the origin (the new t >= 0).
bool intersectRayWithScene(const Scene& scene, Ray& ray);

bool intersectRayWithPlane(const Plane& plane, Ray& ray);

// Returns true if the point p is inside the triangle spanned by v0, v1, v2 with normal n.
bool pointInTriangle(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& n, const glm::vec3& p);

Plane trianglePlane(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2);

bool intersectRayWithTriangle(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, Ray& ray);
bool intersectRayWithShape(const Mesh& mesh, Ray& ray);
bool intersectRayWithShape(const Sphere& sphere, Ray& ray);
bool intersectRayWithShape(const AxisAlignedBox& box, Ray& ray);
