#pragma once
#include "Object.h"
#include "Vecteur.cpp"
#include <vector>

class Mesh : public Object
{
public:
	Mesh();
	Mesh(string chemin);
	std::vector<Vec3<float>> vertices;
	std::vector<Vec3<float>> normales;
	std::vector<int> triangles;
	Intersect intersect(Rayon R);
};

