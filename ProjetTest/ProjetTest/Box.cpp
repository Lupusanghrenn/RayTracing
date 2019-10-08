#include "Box.h"

Box::Box() {
	pointMin = Vec3<float>{ 0,0,0 };
	pointMax = Vec3<float>{ 1,1,1 };
	position = pointMin;
	albedo = Albedo();
	color = Couleur();
}

Box::Box(Vec3<float> pMin, Vec3<float> pMax) {
	pointMin = pMin;
	pointMax = pMax;
	position = pointMin;
	albedo = Albedo();
	color = Couleur();
}

Intersect Box::intersect(Rayon R) {
	Intersect result;

	float tmin = (pointMin.x - R.origin.x) / R.direction.x;
	float tmax = (pointMax.x - R.origin.x) / R.direction.x;

	if (tmin > tmax) swap(tmin, tmax);

	float tymin = (pointMin.y - R.origin.y) / R.direction.y;
	float tymax = (pointMax.y - R.origin.y) / R.direction.y;

	if (tymin > tymax) swap(tymin, tymax);

	if ((tmin > tymax) || (tymin > tmax)) {
		result.t = std::nullopt;
		return result;
	}
		

	if (tymin > tmin)
		tmin = tymin;

	if (tymax < tmax)
		tmax = tymax;

	float tzmin = (pointMin.z - R.origin.z) / R.direction.z;
	float tzmax = (pointMax.z - R.origin.z) / R.direction.z;

	if (tzmin > tzmax) swap(tzmin, tzmax);

	if ((tmin > tzmax) || (tzmin > tmax)) {
		result.t = std::nullopt;
		return result;
	}		

	if (tzmin > tmin)
		tmin = tzmin;

	if (tzmax < tmax)
		tmax = tzmax;

	//return true;
	result.t = tmin;//a test
	return result;
}

Box Box::unionBox(Box box2) {
	return Box();
}
