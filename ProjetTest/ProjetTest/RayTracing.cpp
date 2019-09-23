#pragma once
#include "RayTracing.h"
#include "PPM.h"
#include <iostream> 
#include <algorithm> 

std::optional<float> RayTracing::intersect(Rayon R, Sphere S) {
	float a = 1.f;
	float b = 2 * (dot(R.origin, R.direction) - dot(S.centre, R.direction));
	float c = dot(R.origin, R.origin) + dot(S.centre, S.centre) - 2 * dot(S.centre, R.origin) - S.rayon * S.rayon;
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

void RayTracing::draw600600() {
	//On cree une image de 600 par 600 avec trace de rayon
	int nH = 600, nW = 600, nbSphere = 3, nbLumiere=2;
	Sphere tabSphere[3];
	Lumiere tabLumiere[2];
	Sphere S(Vec3<float>{300.f, 300.f, 250.f},150.f);
	Sphere S2(Vec3<float>{100.f, 100.f, 300.f}, 50.f);
	Sphere S3(Vec3<float>{500.f, 500.f, 100.f}, 30.f);
	Lumiere L(Vec3<float>{0.f, 0.f, 100.f}, 227.f, 27.f, 27.f);
	Lumiere L2(Vec3<float>{500.f, 0.f, 100.f}, 27.f, 27.f, 227.f);
	tabSphere[0] = S;
	tabSphere[1] = S2;
	tabSphere[2] = S3;
	tabLumiere[0] = L;
	tabLumiere[1] = L2;

	//remplissage du tableau de pixel
	PPM ppm(nH, nW, 255);
	for (int i = 0; i < nH; i++)
	{
		for (int j = 0; j < nW; j++)
		{
			Rayon R(Vec3<float>{(float)i, (float)j, 0.f}, Vec3<float>{0.f, 0.f, 1.f});
			float t = -1.f;
			int indexClosest = -1;
			for (int index = 0; index < nbSphere; index++) {
				auto res = RayTracing::intersect(R, tabSphere[index]);
				float value = res.value_or(-1.f);
				if (value>0.f && (value<t || t<0.f)) {
					t = value;
					indexClosest = index;
				}
			}

			if (t>=0.f) {
				//lancer de rayon jusqu a la lumiere
				Vec3<float> impact = R.origin + t * R.direction;//position du point d intersection
				int nbImpact = 0;
				for (int indexLight = 0; indexLight < nbLumiere; indexLight++) {
					Vec3<float> directionL = tabLumiere[indexLight].position - impact;
					normalize(directionL);
					impact = impact + 0.01 * directionL;
					Rayon reflect(impact, directionL);

					float bestResult = -1.f;
					Vec3<float> light = (tabLumiere[indexLight].position - impact);

					for (int index = 0; index < nbSphere; index++) {
						//if (index != indexClosest) {
							//pour pas tester sur lui meme

						auto res2 = RayTracing::intersect(reflect, tabSphere[index]);
						float res2Value = res2.value_or(-1.f);
						if (res2Value > bestResult && res2Value > -1.f) {
							bestResult = res2Value;
						}
						//}
					}
					if (bestResult >= 0.f && nbImpact==0) {
						//ombre --> plus tard
						//ppm.pixelMatrix[i][j] = Vector3<int>(5, 5, 5);
					}
					else {
						//norm(light)
						nbImpact++;
						float norme = norm(light);
						float div = 1000000 / (norme * norme);
						//cout << div;
						int valeur = 255 - div;
						Vec3<float> normal = impact - tabSphere[indexClosest].centre;
						normalize(normal);
						float test = (dot(normal, reflect.direction));
						//cout << test;
						valeur = valeur * test;//couleur = 1/d² * (dot(-normal,ray))
						valeur = std::clamp(valeur, 0, 255);
						float valeur01 = valeur / 255.f;
						//cout << valeur01;
						Vector3<int> finalLight = Vector3<int>(ppm.pixelMatrix[i][j].x + valeur01 * tabLumiere[indexLight].r, ppm.pixelMatrix[i][j].y + valeur01 * tabLumiere[indexLight].g, ppm.pixelMatrix[i][j].z + valeur01 * tabLumiere[indexLight].b);
						ppm.pixelMatrix[i][j] = finalLight;
						//ppm.pixelMatrix[i][j] = Vector3<int>(valeur, valeur, valeur);
					}
				}

				if (nbImpact == 0) {
					//shadow
					Lumiere closestLight = tabLumiere[0];
					for (int indexLight = 1; indexLight < nbLumiere; indexLight++) {
						Vec3<float> bestLight = closestLight.position - impact;
						Vec3<float> tmpLight = tabLumiere[indexLight].position - impact;
						if (norm(bestLight) > norm(tmpLight)) {
							closestLight = tabLumiere[indexLight];
						}
					}
					float coeffDiff = 0.1;
					ppm.pixelMatrix[i][j] = Vector3<int>(closestLight.r*coeffDiff, closestLight.g * coeffDiff, closestLight.b * coeffDiff);
				}
				//Vec3<float> directionL = L.position - impact;
				//impact = impact + 0.0001 * directionL;
				//normalize(directionL);
				//Rayon reflect(impact, directionL);

				//float bestResult = -1.f;
				//Vec3<float> light = (L.position - impact);

				//for (int index = 0; index < nbSphere; index++) {
				//	//if (index != indexClosest) {
				//		//pour pas tester sur lui meme

				//		auto res2 = RayTracing::intersect(reflect, tabSphere[index]);
				//		float res2Value = res2.value_or(-1.f);
				//		if (res2Value>bestResult && res2Value>-1.f) {
				//			bestResult = res2Value;
				//		}
				//	//}
				//}
				
			}
			else {
				ppm.pixelMatrix[i][j] = Vector3<int>(0, 0, 0);
			}				
		}
	}

	//Creation de l image
	//boucle de convertion
	ppm.save("image.ppm");
	
}

