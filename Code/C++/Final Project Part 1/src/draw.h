#pragma once
#include "mesh.h"
#include "ray.h"
#include "scene.h"

void drawShape(const Mesh& mesh);
void drawShape(const Sphere& sphere);
void drawShape(const AxisAlignedBox& box);

void drawScene(const Scene& scene);

void drawRay(const Ray& ray);
