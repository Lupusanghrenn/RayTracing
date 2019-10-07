#pragma once
#include "RayTracing.h"
#include "PPM.h"
#include <iostream> 
#include <algorithm> 
#include <vector>
#include <random>

float tailleCube = 30.f;
std::default_random_engine generator;
std::uniform_real_distribution<float> distribution(-tailleCube / 2.f, tailleCube / 2.f);
std::uniform_real_distribution<float> distribution01(0.f, 1.f);
int nbRayonRandom = 100;
std::vector<Sphere> tabSphere;
std::vector<Lumiere> tabLumiere;
int nbMaxVecteurIndirect = 1;

Vec3<float> RayTracing::kesseKisePazeOBouDutRaillon(Rayon ray, int profondeur) {
	if (profondeur > 5) {
		//std::cout <<"profondeur max"; probleme avec la profondeur --> intersect ?
		return Vec3<float>{0.f, 0.f, 0.f};
	}
	Intersect bestResult;
	int indexClosest = -1;
	for (int index = 0; index < tabSphere.size(); index++) {
		Intersect res = tabSphere[index].intersect(ray);
		float value = res.t.value_or(-1.f);
		if (value > 0.f && (value < bestResult.t.value_or(-1) || bestResult.t.value_or(-1) < 0.f)) {
			bestResult = res;
			indexClosest = index;
		}
	}

	if (bestResult.t.value_or(-1) >= 0.f) {
		//lancer de rayon jusqu a la lumiere
		float t = bestResult.t.value_or(-1);
		Vec3<float> impact = ray.origin + t * ray.direction;//position du point d intersection

		//si jamais on est sur une sphere qui reflete
		if (tabSphere[indexClosest].albedo.albedo == 1.f) {
			/*Vec3<float> normale = impact - tabSphere[indexClosest].position;
			normalize(normale);*/
			Vec3<float> normale = bestResult.normal;
			impact = impact + 0.01 * normale;//on �vit� l'acn�e
			Vec3<float> moinsI = Vec3<float>{-ray.direction.x,-ray.direction.y ,-ray.direction.z };
			Vec3<float> reflectDirection=dot(moinsI,normale)* 2 * normale;//R = 2*N*(-I.N)+I
			normalize(reflectDirection);
			Rayon reflect = Rayon(impact, reflectDirection);
			return kesseKisePazeOBouDutRaillon(reflect,profondeur+1);
		}

		//lumieres indirecte
		Vec3<float> indirectLight = Vec3<float>{ 0.f, 0.f, 0.f };

		for (int nbVecteurIndirect = 0; nbVecteurIndirect < nbMaxVecteurIndirect; nbVecteurIndirect++) {
			/*float random1 = distribution01(generator);
			float random2 = distribution01(generator);

			float phi = 2 * std::_Pi * random1;
			float theta = std::acos(random2);

			float x = std::cos(2 * std::_Pi * random1) * std::sqrt((1 - random2) * (1 - random2));
			float x = std::sin(2 * std::_Pi * random1) * std::sqrt((1 - random2) * (1 - random2));
			float z = random2;*/

			//ok on fait le meme rayon que si on faisait du mirroir pour faire les lumi�res on fera les projections en h�misphere 

			/*Vec3<float> normale = impact - tabSphere[indexClosest].position;
			normalize(normale);*/
			Vec3<float> normale = bestResult.normal;
			impact = impact + 0.01 * normale;//on �vit� l'acn�e
			Vec3<float> moinsI = Vec3<float>{ -ray.direction.x,-ray.direction.y ,-ray.direction.z };
			Vec3<float> reflectDirection = dot(moinsI, normale) * 2 * normale + ray.direction;//R = 2*N*(-I.N)+I
			normalize(reflectDirection);
			Rayon reflect = Rayon(impact, reflectDirection);
			indirectLight = indirectLight + kesseKisePazeOBouDutRaillon(reflect,profondeur+1);
		}

		//lumiere surfacique
		Vec3<float> finalLight = Vec3<float>{ 0.f, 0.f, 0.f };

		for (int indexLight = 0; indexLight < tabLumiere.size(); indexLight++) {

			for (int iLampe = 0; iLampe < nbRayonRandom; iLampe++) {
				float randomx = distribution(generator);  // generates number in the range 1..6 ;
				float randomy = distribution(generator);  // generates number in the range 1..6 ;
				float randomz = distribution(generator);
				Vec3<float> posLampeSurf = tabLumiere[indexLight].position;
				posLampeSurf.x += randomx;
				posLampeSurf.y += randomy;
				posLampeSurf.z += randomz;
				Vec3<float> directionL = posLampeSurf - impact;
				normalize(directionL);
				impact = impact + 0.01 * directionL;
				Rayon shadowRay(impact, directionL);

				Intersect bestResult2;
				Vec3<float> light = (posLampeSurf - impact);

				for (int index = 0; index < tabSphere.size(); index++) {

					Intersect res2 = tabSphere[index].intersect(shadowRay);
					float res2Value = res2.t.value_or(-1.f);
					if (bestResult2.t.value_or(-1) == -1.f) {
						bestResult2 = res2;
					}
					if (res2Value < bestResult2.t.value_or(-1) && res2Value >= 0.f) {
						bestResult2 = res2;
					}
				}
				if (bestResult2.t.value_or(-1) < 0.f || bestResult2.t.value_or(-1) > norm(light)) {
					//On as pas de sphere qui gene notre oeil
					float norme = norm(light);
					/*Vec3<float> normal = impact - tabSphere[indexClosest].position;
					normalize(normal);*/
					Vec3<float> normal = bestResult2.normal;
					float diffuse = 1.f / (norme * norme) * (dot(normal, shadowRay.direction));
					if (diffuse < 0) {
						diffuse = 0;
					}
					float lumSurfFactor = 1.f / nbRayonRandom;//on diminue selon le nombre de point de la lumiere surfacique

					finalLight = finalLight + (lumSurfFactor * diffuse * (float)tabLumiere[indexLight].intensity * tabLumiere[indexLight].color);
				}
			}
		}
		//finalLight = tabSphere[indexClosest].albedo.albedo * finalLight;
		finalLight = finalLight * tabSphere[indexClosest].color.color;
		return finalLight +0.1f * indirectLight;

	}
	else {
		return Vec3<float>{0.f, 0.f, 0.f};
	}
}

void RayTracing::draw600600() {
	//On cree une image de 600 par 600 avec trace de rayon
	int nH = 600, nW = 600;
	Sphere S(Vec3<float>{100.f, 300.f, 250.f}, 100.f, Albedo(1.f));
	Sphere S2(Vec3<float>{100.f, 100.f, 300.f}, 50.f, Albedo(0.5f));
	Sphere S3(Vec3<float>{500.f, 500.f, 100.f}, 30.f, Albedo(0.5f));
	Lumiere L(Vec3<float>{300.f, 300.f, 100.f}, 0.7f, 0.7f, 0.7f, 30000000);
	Lumiere L2(Vec3<float>{500.f, 100.f, 100.f}, 0.1f, 0.1f, 0.9f, 30000000);

	//tabSphere.push_back(S);
	tabSphere.push_back(S2);
	tabSphere.push_back(S3);
	tabLumiere.push_back(L);
	//tabLumiere.push_back(L2);
	//cornellBox
	float R = 30000.f;
	tabSphere.push_back(Sphere(Vec3<float>{300.f, 300.f, R + 500.f}, R, Albedo(), Couleur(1.f, 0.f, 0.f)));//fond
	tabSphere.push_back(Sphere(Vec3<float>{300.f, 300.f, -R +00.f}, R, Albedo(), Couleur(0.1f, 0.1f, 0.1f)));//devant
	tabSphere.push_back(Sphere(Vec3<float>{300.f, R + 600.f, 0.f}, R, Albedo(), Couleur(0.f, 1.f, 0.f)));//droite
	tabSphere.push_back(Sphere(Vec3<float>{300.f, -R, 0.f}, R, Albedo(), Couleur(1.f, 0.f, 1.f)));//gauche
	tabSphere.push_back(Sphere(Vec3<float>{R + 600.f, 300.f, 0.f}, R, Albedo(), Couleur(0.f, 1.f, 1.f)));//bas
	tabSphere.push_back(Sphere(Vec3<float>{-R, 300.f, 0.f}, R, Albedo(), Couleur(1.f, 1.f, 0.f)));//haut	

	//Camera ortho
	Vec3<float> pointCamera = Vec3<float>{ 300.f, 300.f, -450.f };

	//remplissage du tableau de pixel
	PPM ppm(nH, nW, 255);

	#pragma omp parallel for
	for (int i = 0; i < nH; i++)
	{
		for (int j = 0; j < nW; j++)
		{
			//camera ortho
			Vec3<float> directionRayon = Vec3<float>{ (float)i, (float)j, 0.f } -pointCamera;
			normalize(directionRayon);
			Rayon ray(Vec3<float>{(float)i, (float)j, 0.f}, directionRayon);
			Vec3<float> finalLight = RayTracing::kesseKisePazeOBouDutRaillon(ray, 0);
			ppm.pixelMatrix[i][j] = Vector3<int>(std::clamp((int)finalLight.x, 0, 255), std::clamp((int)finalLight.y, 0, 255), std::clamp((int)finalLight.z, 0, 255));
			 
		}
	}

	//Creation de l image
	//boucle de convertion
	std::cout << "Generation du fichier";
	ppm.save("image.ppm");

}

