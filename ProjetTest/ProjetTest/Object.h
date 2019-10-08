#pragma once
#include "Vecteur.cpp"
#include <optional>
#include "Rayon.h"
#include "Albedo.h"
#include "Couleur.h"
#include "Intersect.h"

class Box;

class Object
{
public:
	Vec3<float> position;
	Albedo albedo;
	Couleur color;
	virtual Intersect intersect(Rayon R) = 0;
	virtual Box creeBoxAPartirObject() = 0;
	
};

