#pragma once
#include "Vecteur.cpp"

class Sphere
{
public:
	Sphere();
	Sphere(Vec3<float> c, float r);
	Vec3<float> centre;
	float rayon;
};

