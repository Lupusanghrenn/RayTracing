#include "Box.h"

Box::Box(Vec3<float> pMin, Vec3<float> pMax) {
	pointMin = pMin;
	pointMax = pMax;
}

//Box::Box(Box* b1, Box* b2)
//{
//	Vec3<float> pMin = b1->pointMin;
//	if (pMin.x > b2->pointMin.x) {
//		pMin.x = b2->pointMin.x;
//	}
//	if (pMin.y > b2->pointMin.y) {
//		pMin.y = b2->pointMin.y;
//	}
//	if (pMin.z > b2->pointMin.z) {
//		pMin.z = b2->pointMin.z;
//	}
//
//	Vec3<float> pMax = b1->pointMax;
//	if (pMax.x > b2->pointMax.x) {
//		pMax.x = b2->pointMax.x;
//	}
//	if (pMax.y > b2->pointMax.y) {
//		pMax.y = b2->pointMax.y;
//	}
//	if (pMax.z > b2->pointMax.z) {
//		pMax.z = b2->pointMax.z;
//	}
//
//	Box* b = new Box(pMin, pMax);
//	b->childrens.push_back(b1);
//	b->childrens.push_back(b2);
//}

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
		std::vector<Box*> sorted;

		//sort
		//meilleur axe
		float tailleX = pMax.x - pMin.x;
		float tailleY = pMax.y - pMin.y;
		float tailleZ = pMax.z - pMin.z;

		if (tailleX > tailleY && tailleX > tailleZ) {
			//sort selon l axe X
			int taille = boxes.size();
			for (int indexSort = 0; indexSort < taille; indexSort++) {
				Box* min = boxes[0];
				int indexBoxMin = 0;
				for (int indexMin = 1; indexMin < boxes.size(); indexMin++) {
					if (min->pointMin.x > boxes[indexMin]->pointMin.x) {
						min = boxes[indexMin];
						indexBoxMin = indexMin;
					}
				}
				boxes.erase(boxes.begin()+indexBoxMin);
				sorted.push_back(min);
			}
		}else if (tailleY > tailleX && tailleY > tailleZ) {
			//sort selon l axe y
			int taille = boxes.size();
			for (int indexSort = 0; indexSort < taille; indexSort++) {
				Box* min = boxes[0];
				int indexBoxMin = 0;
				for (int indexMin = 1; indexMin < boxes.size(); indexMin++) {
					if (min->pointMin.y > boxes[indexMin]->pointMin.y) {
						min = boxes[indexMin];
						indexBoxMin = indexMin;
					}
				}
				boxes.erase(boxes.begin() + indexBoxMin);
				sorted.push_back(min);
			}
		} else {
			//sort selon l axe Z
			int taille = boxes.size();
			for (int indexSort = 0; indexSort < taille; indexSort++) {
				Box* min = boxes[0];
				int indexBoxMin = 0;
				for (int indexMin = 1; indexMin < boxes.size(); indexMin++) {
					if (min->pointMin.z > boxes[indexMin]->pointMin.z) {
						min = boxes[indexMin];
						indexBoxMin = indexMin;
					}
				}
				boxes.erase(boxes.begin() + indexBoxMin);
				sorted.push_back(min);
			}
		}

		for (int indGauche = 0; indGauche < sorted.size() / 2; indGauche++) {
			vecGauche.push_back(sorted[indGauche]);
		}

		for (int indDroite = vecGauche.size(); indDroite < sorted.size(); indDroite++) {
			vecDroite.push_back(sorted[indDroite]);
		}

		//recursivite
		if (vecGauche.size() > 0) {
			b->childrens.push_back(boxEnglobante(vecGauche));
		}
		b->childrens.push_back(boxEnglobante(vecDroite));		
	}
	return b;
}
