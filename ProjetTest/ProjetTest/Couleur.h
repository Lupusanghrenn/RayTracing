#pragma once
#include "Vecteur.h"

class Couleur
{
public:
	Couleur();
	Couleur(float red, float green, float blue);
	Vec3<float> color;
	float r, g, b;
};

