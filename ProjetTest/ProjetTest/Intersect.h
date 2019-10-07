#pragma once
#include <optional>
#include "Vecteur.cpp";

class Intersect
{
public:
	Intersect();
	std::optional<float> t;
	Vec3<float> normal;
};

