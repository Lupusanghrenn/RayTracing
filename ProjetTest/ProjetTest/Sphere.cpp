#include "Sphere.h"
Sphere::Sphere(Vec3<float> c, float r, Albedo albe) {
	position = c;
	rayon = r;
	this->albedo = albe;
	color = Couleur();
}

//retourne la valeur de la sphere normalise
Vec3<float> Sphere::getNormal(Vec3<float> point)
{
	Vec3<float> normal = point - this->position;
	normalize(normal);
	return normal;
}

Sphere::Sphere() {
	this->position = Vec3<float>{ 0.f, 0.f, 0.f };
	this->rayon = 10.f;
	this->albedo = Albedo();
	this->color = Couleur();
}

Sphere::Sphere(Vec3<float> c, float r, Albedo albe, Couleur col)
{
	position = c;
	rayon = r;
	this->albedo = albe;
	color = col;
}

std::optional<float> Sphere::intersect(Rayon R) {
	float a = 1.f;
	float b = 2 * (dot(R.origin, R.direction) - dot(position, R.direction));
	float c = dot(R.origin, R.origin) + dot(position, position) - 2 * dot(position, R.origin) - rayon * rayon;
	float delta = b * b - 4 * a * c;

	if (delta > 0) {
		float sol1 = (-b - std::sqrt(delta)) / (2 * a);
		float sol2 = (-b + std::sqrt(delta)) / (2 * a);

		if (sol1 >= 0.f) {
			return sol1;
		}
		else if (sol2 >= 0.f) {
			return sol2;
		}
		else {
			//t=sol2;
			//return sol2 > 0.f;
			return std::nullopt;
		}
	}
	else if (delta == 0) {
		float sol = (-b / 2 * a);
		return sol;
	}
	else {
		return std::nullopt;
	}
}
