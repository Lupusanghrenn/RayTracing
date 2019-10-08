#pragma once
#include <optional>
#include "Vecteur.cpp"

class Object;

class Intersect
{
public:
	std::optional<float> t;
	Vec3<float> normal;
	Object* object;
};

