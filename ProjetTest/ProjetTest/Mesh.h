#pragma once
#include "Object.h"
#include "Vecteur.cpp"
#include <vector>

class Mesh : public Object
{
public:
	Mesh();
	Mesh(string chemin);
	std::vector<Vec3<float>> sommets;
	std::vector<int> triangles;
	Intersect intersect(Rayon R);
	Vec3<float> getNormal(Vec3<float> point);
};

