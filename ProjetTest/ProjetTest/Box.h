#pragma once
#include "Vecteur.cpp"
#include "Object.h"
#include <vector>

class Box
{
public:
	Box();
	Box(Vec3<float> pMin, Vec3<float> pMax);
	Vec3<float> pointMin, pointMax; // on peut creer notre box juste avec ces deux points --> la position sera le point min
	std::vector<Box> childrens;
	Object* child;
	Intersect intersect(Rayon R);
	Box creeBoxAPartirObject();
	Box unionBox(Box box2);
};

