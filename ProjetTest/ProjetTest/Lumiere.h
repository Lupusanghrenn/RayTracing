#pragma once
#include "Vecteur.cpp";

class Lumiere
{
public:
	Lumiere(Vec3<float> p, float red, float green, float blue);
	Lumiere();
	Vec3<float> position;
	float r, g, b;
};

