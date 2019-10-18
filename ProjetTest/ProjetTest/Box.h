#pragma once
#include "Vecteur.h"
#include "Object.h"
#include <vector>
#include <algorithm>
#include <functional>

class Box
{
public:
	Box(Vec3<float> pMin, Vec3<float> pMax);
	//Box(Box* b1, Box* b2);//Union
	Vec3<float> pointMin, pointMax; // on peut creer notre box juste avec ces deux points --> la position sera le point min
	std::vector<Box*> childrens;
	Object* child;
	Intersect intersect(Rayon R);
	Box* creeBoxAPartirObject();
	Box* unionBox(Box* box2);
	std::optional<float> intersectBox(Rayon r);
	std::optional<float> intersectBox2(Rayon r);
	static Box* boxEnglobante(std::vector<Box*> boxes);
};

