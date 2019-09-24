#pragma once
#include "Vecteur.cpp";

class Lumiere
{
public:
	Lumiere(Vec3<float> p, float red, float green, float blue, int i);
	Lumiere();
	Vec3<float> position;
	float r, g, b;
	Vec3<float> color;
	int intensity;
};

