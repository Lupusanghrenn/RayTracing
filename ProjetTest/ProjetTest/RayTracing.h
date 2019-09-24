#pragma once
#include "Rayon.h"
#include "Sphere.h"
#include "Lumiere.h"
#include <optional>
#include <vector>

class RayTracing
{
public:
	static std::optional<float> intersect(Rayon R, Sphere S);
	static void draw600600();
	static void recursiviteRay(std::vector<Sphere> tabSphere, std::vector<Lumiere> tabLumiere, Rayon ray);
};

