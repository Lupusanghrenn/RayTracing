#include "Box.h"

Box::Box(Vec3<float> pMin, Vec3<float> pMax) {
	pointMin = pMin;
	pointMax = pMax;
}

Intersect Box::intersect(Rayon R) {
	Intersect result;
	/*result.t = intersectBox2(R);
	return result;*/

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

float max(float t1, float t2) {
	if (t1 >= t2) {
		return t1;
	}
	return t2;
}

float min(float t1, float t2) {
	if (t1 <= t2) {
		return t1;
	}
	return t2;
}

std::optional<float> Box::intersectBox2(Rayon r)
{
	float tmin, tmax, tymin, tymax, tzmin, tzmax;
	Vec3<float> bounds[] = { pointMin, pointMax };

	Vec3<float> invdir = 1.f / r.direction;
	int sign[3];
	sign[0] = (invdir.x < 0);
	sign[1] = (invdir.y < 0);
	sign[2] = (invdir.z < 0);

	tmin = (bounds[sign[0]].x - r.origin.x) * invdir.x;
	tmax = (bounds[1 - sign[0]].x - r.origin.x) * invdir.x;
	tymin = (bounds[sign[1]].y - r.origin.y) * invdir.y;
	tymax = (bounds[1 - sign[1]].y - r.origin.y) * invdir.y;

	if ((tmin > tymax) || (tymin > tmax))
		return std::nullopt;
	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;

	tzmin = (bounds[sign[2]].z - r.origin.z) * invdir.z;
	tzmax = (bounds[1 - sign[2]].z - r.origin.z) * invdir.z;

	if ((tmin > tzmax) || (tzmin > tmax))
		return std::nullopt;
	if (tzmin > tmin)
		tmin = tzmin;
	if (tzmax < tmax)
		tmax = tzmax;

	return tmin;
}

std::optional<float> Box::intersectBox(Rayon r) {
	Vec3<float> dir = 1.0/ r.direction;

	// lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
	// r.org is origin of ray
	float t1 = (pointMin.x - r.origin.x) * dir.x;
	float t2 = (pointMax.x - r.origin.x) * dir.x;
	float t3 = (pointMin.y - r.origin.y) * dir.y;
	float t4 = (pointMax.y - r.origin.y) * dir.y;
	float t5 = (pointMin.z - r.origin.z) * dir.z;
	float t6 = (pointMax.z - r.origin.z) * dir.z;

	float tmin = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
	float tmax = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
	if (tmax < 0)
	{
		return std::nullopt;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
	{
		return std::nullopt;
	}
	return tmin;
}

Box* Box::creeBoxAPartirObject()
{
	return this;
}

Box* Box::unionBox(Box* box2) {
	//on recupere les x,y et z min de chaque box
	Vec3<float> pMin = this->pointMin;
	if (pMin.x > box2->pointMin.x) {
		pMin.x = box2->pointMin.x;
	}
	if (pMin.y > box2->pointMin.y) {
		pMin.y = box2->pointMin.y;
	}
	if (pMin.z > box2->pointMin.z) {
		pMin.z = box2->pointMin.z;
	}

	Vec3<float> pMax = this->pointMax;
	if (pMax.x > box2->pointMax.x) {
		pMax.x = box2->pointMax.x;
	}
	if (pMax.y > box2->pointMax.y) {
		pMax.y = box2->pointMax.y;
	}
	if (pMax.z > box2->pointMax.z) {
		pMax.z = box2->pointMax.z;
	}

	Box* b = new Box(pMin, pMax);
	b->childrens.push_back(this);
	b->childrens.push_back(box2);
	
	return b;
}

struct {
	bool operator()(Box* a, Box* b) const
	{
		return a->pointMax.x < b->pointMax.x;
	}
} customLessX;

struct {
	bool operator()(Box* a, Box* b) const
	{
		return a->pointMax.y < b->pointMax.y;
	}
} customLessY;

struct {
	bool operator()(Box* a, Box* b) const
	{
		return a->pointMax.z < b->pointMax.z;
	}
} customLessZ;

Box* Box::boxEnglobante(std::vector<Box*> boxes)
{
	Vec3<float> pMin = boxes[0]->pointMin;
	Vec3<float> pMax = boxes[0]->pointMax;

	for (int i = 1; i < boxes.size(); i++) {
		if (pMin.x > boxes[i]->pointMin.x) {
			pMin.x = boxes[i]->pointMin.x;
		}
		if (pMin.y > boxes[i]->pointMin.y) {
			pMin.y = boxes[i]->pointMin.y;
		}
		if (pMin.z > boxes[i]->pointMin.z) {
			pMin.z = boxes[i]->pointMin.z;
		}

		if (pMax.x < boxes[i]->pointMax.x) {
			pMax.x = boxes[i]->pointMax.x;
		}
		if (pMax.y < boxes[i]->pointMax.y) {
			pMax.y = boxes[i]->pointMax.y;
		}
		if (pMax.z < boxes[i]->pointMax.z) {
			pMax.z = boxes[i]->pointMax.z;
		}
	}

	Box* b = new Box(pMin, pMax);
	//maintenant on fait les test pour savoir si enfant ou non
	if (boxes.size() == 1) {
		return boxes[0];
	}
	else {
		//on fera le sort plus tard
		std::vector<Box*> vecGauche;
		std::vector<Box*> vecDroite;

		//sort
		//meilleur axe
		float tailleX = pMax.x - pMin.x;
		float tailleY = pMax.y - pMin.y;
		float tailleZ = pMax.z - pMin.z;

		if (tailleX > tailleY && tailleX > tailleZ) {
			//sort selon l axe X
			std::sort(boxes.begin(), boxes.end(), customLessX);

		}else if (tailleY > tailleX && tailleY > tailleZ) {
			//sort selon l axe y
			std::sort(boxes.begin(), boxes.end(), customLessY);

		} else {
			//sort selon l axe Z
			std::sort(boxes.begin(), boxes.end(), customLessZ);
		}

		for (int indGauche = 0; indGauche < boxes.size() / 2; indGauche++) {
			vecGauche.push_back(boxes[indGauche]);
		}

		for (int indDroite = vecGauche.size(); indDroite < boxes.size(); indDroite++) {
			vecDroite.push_back(boxes[indDroite]);
		}

		//recursivite
		b->childrens.push_back(boxEnglobante(vecGauche));
		b->childrens.push_back(boxEnglobante(vecDroite));		
	}
	return b;
}
