#pragma once
#include "Box.h"
#include "Rayon.h"
#include "Sphere.h"
#include "Lumiere.h"
#include <optional>
#include <vector>

class RayTracing
{
public:
	static void draw600600();
	static Vec3<float> kesseKisePazeOBouDutRaillon(Rayon ray, int profondeur);
};

