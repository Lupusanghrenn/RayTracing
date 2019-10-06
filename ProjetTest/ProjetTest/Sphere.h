#pragma once
#include "Vecteur.cpp"
#include "Albedo.h"
#include "Couleur.h"
#include "Object.h"

class Sphere : public Object
{
public:
	Sphere();
	Sphere(Vec3<float> c, float r, Albedo albe, Couleur col);
	std::optional<float> intersect(Rayon R);
	Sphere(Vec3<float> c, float r, Albedo albe);
	Vec3<float> getNormal(Vec3<float> point);
	float rayon;
};

