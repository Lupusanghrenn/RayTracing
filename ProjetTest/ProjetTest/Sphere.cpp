#include "Sphere.h"
Sphere::Sphere(Vec3<float> c, float r, Albedo albe) {
	position = c;
	rayon = r;
	this->albedo = albe;
	color = Couleur();
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

Intersect Sphere::intersect(Rayon R) {
	Intersect result = Intersect();
	float a = 1.f;
	float b = 2 * (dot(R.origin, R.direction) - dot(position, R.direction));
	float c = dot(R.origin, R.origin) + dot(position, position) - 2 * dot(position, R.origin) - rayon * rayon;
	float delta = b * b - 4 * a * c;

	if (delta > 0) {
		float sol1 = (-b - std::sqrt(delta)) / (2 * a);
		float sol2 = (-b + std::sqrt(delta)) / (2 * a);

		if (sol1 >= 0.f) {
			result.t= sol1;
		}
		else if (sol2 >= 0.f) {
			result.t= sol2;
		}
		else {
			//t=sol2;
			//return sol2 > 0.f;
			result.t= std::nullopt;
		}
	}
	else if (delta == 0) {
		float sol = (-b / 2 * a);
		result.t= sol;
	}
	else {
		result.t= std::nullopt;
	}

	//normale
	float monT = result.t.value_or(-1);
	Vec3<float> arrive = R.origin + monT * R.direction;
	Vec3<float> normal = (arrive - this->position);
	normalize(normal);
	result.normal = normal;

	return result;
}
