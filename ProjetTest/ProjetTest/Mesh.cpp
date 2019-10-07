#include "Mesh.h"

Mesh::Mesh()
{
	position = Vec3<float>{ 0.f, 0.f, 0.f };
	this->color = Couleur();
	this->albedo = Albedo();
}

Mesh::Mesh(string chemin)
{
	//récupération du code avec Unity
	//TODO
}

std::optional<float> Mesh::intersect(Rayon R)
{
	//TODO
	return std::optional<float>();
}

Vec3<float> Mesh::getNormal(Vec3<float> point)
{
	return Vec3<float>();
}
