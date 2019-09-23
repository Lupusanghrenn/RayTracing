#pragma once
#include "Vecteur.cpp"

class Rayon
{
public:
	Rayon(Vec3<float> o, Vec3<float> d);
	Vec3<float> origin;
	Vec3<float> direction;
};

