#pragma once
#include "Vecteur.h"
#include "Albedo.h"
#include "Couleur.h"
#include "Box.h"
#include "Object.h"
#include "Intersect.h"

class Sphere : public Object
{
public:
	Sphere();
	Sphere(Vec3<float> c, float r, Albedo albe, Couleur col);
    Intersect intersect(Rayon R);
	Sphere(Vec3<float> c, float r, Albedo albe);
	float rayon;
	Box* creeBoxAPartirObject();
};

