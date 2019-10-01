#pragma once
#include "Vecteur.cpp"
#include "Albedo.h"
#include "Couleur.h"

class Sphere
{
public:
	Sphere();
	Sphere(Vec3<float> c, float r, Albedo albe, Couleur col);
	Sphere(Vec3<float> c, float r, Albedo albe);
	Vec3<float> centre;
	float rayon;
	Albedo albedo;
	Couleur color;
};

