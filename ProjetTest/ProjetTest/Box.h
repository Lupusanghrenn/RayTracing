#pragma once
#include "Vecteur.cpp"
#include "Object.h"

class Box : Object
{
public:
	Box();
	Box(Vec3<float> pMin, Vec3<float> pMax);
	Vec3<float> pointMin, pointMax; // on peut creer notre box juste avec ces deux points --> la position sera le point min
	Intersect intersect(Rayon R);
	Box unionBox(Box box2);
};

