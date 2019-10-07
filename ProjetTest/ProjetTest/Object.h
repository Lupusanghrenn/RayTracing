#pragma once
#include "Vecteur.cpp"
#include <optional>
#include "Rayon.h"
#include "Albedo.h"
#include "Couleur.h"

class Object
{
public:
	Vec3<float> position;
	Albedo albedo;
	Couleur color;
	virtual std::optional<float> intersect(Rayon R) = 0;

};

