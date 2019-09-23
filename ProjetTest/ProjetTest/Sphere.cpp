#include "Sphere.h"
Sphere::Sphere(Vec3<float> c, float r) {
	centre = c;
	rayon = r;
}

Sphere::Sphere() {
	this->centre = Vec3<float>{ 0.f, 0.f, 0.f };
	this->rayon = 10.f;
}