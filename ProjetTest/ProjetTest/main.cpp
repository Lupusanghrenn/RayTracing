#pragma once
#include "Rayon.h"
#include "RayTracing.h"
#include "Sphere.h"

int main() {
	Rayon R(Vec3<float>{0.f, 0.f, 0.f}, Vec3<float>{1.f, 0.f, 0.f});
	Sphere S(Vec3<float>{4.f, 0.f, 0.f}, 3.f);
	/*if (auto res = raytracing::intersect(r, s).value_or(-1.f)) {
		cout << res;
	}*/
	RayTracing::draw600600();
}