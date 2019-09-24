#pragma once
#include "RayTracing.h"
#include "PPM.h"
#include <iostream> 
#include <algorithm> 
#include <vector>

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

void RayTracing::recursiviteRay(std::vector<Sphere> tabSphere, std::vector<Lumiere> tabLumiere, Rayon ray) {
	// on renvoie float t ou directement la couleur ?
}

void RayTracing::draw600600() {
	//On cree une image de 600 par 600 avec trace de rayon
	int nH = 600, nW = 600;
	std::vector<Sphere> tabSphere;
	std::vector<Lumiere> tabLumiere;
	Sphere S(Vec3<float>{300.f, 300.f, 250.f},150.f);
	Sphere S2(Vec3<float>{100.f, 100.f, 300.f}, 50.f);
	Sphere S3(Vec3<float>{500.f, 500.f, 100.f}, 30.f);
	Lumiere L(Vec3<float>{0.f, 0.f, 100.f}, 0.9f, 0.1f, 0.1f,	 30000000);
	Lumiere L2(Vec3<float>{500.f, 0.f, 100.f}, 0.1f, 0.1f, 0.9f, 30000000);
	int tailleCube = 30;
	int nbRayonRandom=100;
	tabSphere.push_back(S);
	tabSphere.push_back(S2);
	tabSphere.push_back(S3);
	tabLumiere.push_back(L);
	tabLumiere.push_back(L2);

	//remplissage du tableau de pixel
	PPM ppm(nH, nW, 255);

	#pragma omp parallel for
	for (int i = 0; i < nH; i++)
	{
		
		for (int j = 0; j < nW; j++)
		{
			Rayon R(Vec3<float>{(float)i, (float)j, 0.f}, Vec3<float>{0.f, 0.f, 1.f});
			float t = -1.f;
			int indexClosest = -1;
			for (int index = 0; index < tabSphere.size(); index++) {
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

				for (int indexLight = 0; indexLight < tabLumiere.size(); indexLight++) {

					//lumiere surfacique
					Vec3<float> finalLight = Vec3<float>{ 0.f, 0.f, 0.f };
					for (int iLampe = 0; iLampe < nbRayonRandom; iLampe++) {
						float randomx = std::rand() % tailleCube - tailleCube / 2;
						float randomy = std::rand() % tailleCube - tailleCube / 2;
						float randomz = std::rand() % tailleCube - tailleCube / 2;
						Vec3<float> posLampeSurf = tabLumiere[indexLight].position;
						posLampeSurf.x += randomx;
						posLampeSurf.y += randomy;
						posLampeSurf.z += randomz;
						Vec3<float> directionL = posLampeSurf - impact;
						normalize(directionL);
						impact = impact + 0.01 * directionL;
						Rayon reflect(impact, directionL);

						float bestResult = -1.f;
						Vec3<float> light = (posLampeSurf - impact);

						for (int index = 0; index < tabSphere.size(); index++) {

							auto res2 = RayTracing::intersect(reflect, tabSphere[index]);
							float res2Value = res2.value_or(-1.f);
							if (res2Value > bestResult && res2Value > -1.f) {
								bestResult = res2Value;
							}
						}
						if (bestResult < 0.f) {
							//On as pas de sphere qui gene notre oeil
							float norme = norm(light);
							Vec3<float> normal = impact - tabSphere[indexClosest].centre;
							normalize(normal);
							float diffuse = 1.f / (norme * norme) * (dot(normal, reflect.direction));
							if (diffuse < 0) {
								diffuse = 0;
							}
							float lumSurfFactor = 1.f/nbRayonRandom;//on diminue selon le nombre de point de la lumiere surfacique
						
							finalLight = finalLight + (lumSurfFactor * diffuse * (float)tabLumiere[indexLight].intensity * tabLumiere[indexLight].color);
						}
					}
					Vector3<int> pixelMat = Vector3<int>(std::clamp(ppm.pixelMatrix[i][j].x + (int)finalLight.x, 0, 255), std::clamp(ppm.pixelMatrix[i][j].y + (int)finalLight.y, 0, 255), std::clamp(ppm.pixelMatrix[i][j].z + (int)finalLight.z, 0, 255));
					ppm.pixelMatrix[i][j] = pixelMat;
				}		
			}
			else {
				ppm.pixelMatrix[i][j] = Vector3<int>(0, 0, 0);
			}				
		}
	}

	//Creation de l image
	//boucle de convertion
	std::cout << "Generation du fichier";
	ppm.save("image.ppm");
	
}

