#pragma once
#include "Rayon.h"
#include "Sphere.h"
#include "Lumiere.h"
#include <optional>

class RayTracing
{
public:
	static std::optional<float> intersect(Rayon R, Sphere S);
	static void draw600600();
};

