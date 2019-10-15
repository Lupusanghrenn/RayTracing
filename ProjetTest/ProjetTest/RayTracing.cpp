#pragma once
#include "RayTracing.h"
#include "PPM.h"
#include <iostream> 
#include <algorithm> 
#include <vector>
#include <random>
#include <chrono> 
using namespace std::chrono;

typedef shared_ptr<Object> PObject;

float tailleCube = 30.f;
std::default_random_engine generator;
std::uniform_real_distribution<float> distribution(-tailleCube / 2.f, tailleCube / 2.f);
std::uniform_real_distribution<float> distribution01(0.f, 1.f);
int nbRayonRandom = 30;
std::vector<Object*> tabSphere;
std::vector<Lumiere> tabLumiere;
std::vector<Box*> boundingBoxes;
int nbMaxVecteurIndirect = 2;
int nbSphereRandom = 10;

Intersect closestSphereFromBox(std::vector<Box*> bBox, Rayon R) {
	Intersect bestResult;
	bestResult.t = 1000000.f;
	for (int indexBox = 0; indexBox < bBox.size(); indexBox++) {
		Intersect tmpResult;
		if (bBox[indexBox]->childrens.size() > 0) {
			tmpResult = closestSphereFromBox(bBox[indexBox]->childrens,R);
		}
		else {
			tmpResult = bBox[indexBox]->child->intersect(R);
		}	
		float value = tmpResult.t.value_or(-1);
		if (value > 0.f && (value < bestResult.t.value_or(-1) || bestResult.t.value_or(-1) < 0.f)) {
			bestResult = tmpResult;
		}
	}
	return bestResult;
}

Vec3<float> RayTracing::kesseKisePazeOBouDutRaillon(Rayon ray, int profondeur) {
	if (profondeur > 3) {
		//std::cout <<"profondeur max"; probleme avec la profondeur --> intersect ?
		return Vec3<float>{0.f, 0.f, 0.f};
	}
	Intersect bestResult;
	//int indexClosest = -1;

	bestResult = closestSphereFromBox(boundingBoxes, ray);
	
	/*for (int index = 0; index < tabSphere.size(); index++) {
		Intersect res = tabSphere[index]->intersect(ray);
		float value = res.t.value_or(-1.f);
		if (value > 0.f && (value < bestResult.t.value_or(-1) || bestResult.t.value_or(-1) < 0.f)) {
			bestResult = res;
			indexClosest = index;
		}
	}*/
	

	if (bestResult.t.value_or(-1) >= 0.f) {
		//lancer de rayon jusqu a la lumiere
		float t = bestResult.t.value_or(-1);
		Vec3<float> impact = ray.origin + t * ray.direction;//position du point d intersection

		//si jamais on est sur une sphere qui reflete
		if (bestResult.object->albedo.albedo == 1.f) {
			//Vec3<float> normale = impact - tabSphere[indexClosest].position;
			//normalize(normale);
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

			//random 
			Vec3<float> rayonRandom = bestResult.normal;
			Vec3<float> randomTweak = Vec3<float>{ distribution01(generator),distribution01(generator),distribution01(generator) };
			rayonRandom = rayonRandom + randomTweak;
			normalize(rayonRandom);
			impact = impact + 0.03 * rayonRandom;//on �vit� l'acn�e
			Rayon reflect = Rayon(impact, rayonRandom);
			indirectLight = indirectLight + kesseKisePazeOBouDutRaillon(reflect, profondeur + 1);
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
			//Vec3<float> normale = bestResult.normal;
			//impact = impact + 0.01 * normale;//on �vit� l'acn�e
			//Vec3<float> moinsI = Vec3<float>{ -ray.direction.x,-ray.direction.y ,-ray.direction.z };
			//Vec3<float> reflectDirection = dot(moinsI, normale) * 2 * normale + ray.direction;//R = 2*N*(-I.N)+I
			//normalize(reflectDirection);
			//Rayon reflect = Rayon(impact, reflectDirection);
			//indirectLight = indirectLight + 0.2f * kesseKisePazeOBouDutRaillon(reflect,profondeur+1);
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

				Intersect bestResult2 = closestSphereFromBox(boundingBoxes, shadowRay);
				Vec3<float> light = (posLampeSurf - impact);

				/*for (int index = 0; index < tabSphere.size(); index++) {

					Intersect res2 = tabSphere[index]->intersect(shadowRay);
					float res2Value = res2.t.value_or(-1.f);
					if (bestResult2.t.value_or(-1) == -1.f) {
						bestResult2 = res2;
					}
					if (res2Value < bestResult2.t.value_or(-1) && res2Value >= 0.f) {
						bestResult2 = res2;
					}
				}*/
				if (bestResult2.t.value_or(-1) < 0.f || bestResult2.t.value_or(-1) > norm(light)) {
					//On as pas de sphere qui gene notre oeil
					float norme = norm(light);
					Vec3<float> normal = bestResult.normal;
					//std::cout << bestResult2.normal.x<<" "<<bestResult2.normal.y<< endl;
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
		finalLight = finalLight * bestResult.object->color.color;
		return finalLight +0.03f * indirectLight;

	}
	else {
		return Vec3<float>{0.f, 0.f, 0.f};
	}
}

void RayTracing::draw600600() {
	//On cree une image de 600 par 600 avec trace de rayon
	int nH = 600, nW = 600;
	Sphere S = Sphere(Vec3<float>{100.f, 300.f, 250.f}, 20.f, Albedo(1.f));
	Sphere S2 =Sphere(Vec3<float>{100.f, 100.f, 300.f}, 50.f, Albedo(0.5f));
	Sphere S3 =Sphere(Vec3<float>{500.f, 500.f, 100.f}, 30.f, Albedo(0.5f));
	Lumiere L(Vec3<float>{300.f, 300.f, 100.f}, 0.7f, 0.7f, 0.7f, 30000000);
	Lumiere L2(Vec3<float>{500.f, 100.f, 100.f}, 0.1f, 0.1f, 0.9f, 30000000);


	tabLumiere.push_back(L);
	//tabLumiere.push_back(L2);
	//cornellBox
	float R = 30000.f;
	tabSphere.push_back(new Sphere(Vec3<float>{300.f, 300.f, R + 500.f}, R, Albedo(), Couleur(1.f, 0.f, 0.f)));//fond
	tabSphere.push_back(new Sphere(Vec3<float>{300.f, 300.f, -R +00.f}, R, Albedo(), Couleur(0.1f, 0.1f, 0.1f)));//devant
	tabSphere.push_back(new Sphere(Vec3<float>{300.f, R + 600.f, 0.f}, R, Albedo(), Couleur(0.f, 1.f, 0.f)));//droite
	tabSphere.push_back(new Sphere(Vec3<float>{300.f, -R, 0.f}, R, Albedo(), Couleur(1.f, 0.f, 1.f)));//gauche
	tabSphere.push_back(new Sphere(Vec3<float>{R + 600.f, 300.f, 0.f}, R, Albedo(), Couleur(0.f, 1.f, 1.f)));//bas
	tabSphere.push_back(new Sphere(Vec3<float>{-R, 300.f, 0.f}, R, Albedo(), Couleur(1.f, 1.f, 0.f)));//haut	
	tabSphere.push_back(&S);
	tabSphere.push_back(&S2);
	tabSphere.push_back(&S3);

	//on ajoute plein de sphere de test
	for (int nbSphere = 0; nbSphere < nbSphereRandom; nbSphere++) {
		Vec3<float> vecTmp = Vec3<float>{ (distribution01(generator) * 500.f) , (distribution01(generator) * 500.f), (distribution01(generator) * 500.f)};
		tabSphere.push_back(new Sphere(vecTmp, 10.f, Albedo(0.5f)));
	}
	//Camera ortho
	Vec3<float> pointCamera = Vec3<float>{ 300.f, 300.f, -450.f };

	//remplissage du tableau de pixel
	PPM ppm(nH, nW, 255);
	
	//bounding box
	//creation d une box pour chaque objet
	for (int a = 0; a < 6; a++) {
		boundingBoxes.push_back(tabSphere[a]->creeBoxAPartirObject());
	}

	std::vector<Box*> boxHorsCornell;

	for (int b = 6; b < tabSphere.size(); b++) {
		boxHorsCornell.push_back(tabSphere[b]->creeBoxAPartirObject());
	}
	//creation de box manuelle
	/*Box* superBox = tabSphere[6]->creeBoxAPartirObject()->unionBox(tabSphere[7]->creeBoxAPartirObject());
	superBox = superBox->unionBox(tabSphere[8]->creeBoxAPartirObject());
	boundingBoxes.push_back(superBox);*/
	//maintenant faut faire ca en recurisif
	auto startBox = high_resolution_clock::now();
	Box* gigaBox = Box::boxEnglobante(boxHorsCornell);
	auto stopBox = high_resolution_clock::now();
	boundingBoxes.push_back(gigaBox);
	auto durationBox = duration_cast<microseconds>(stopBox - startBox);
	cout << "Duration Box : " << durationBox.count()<<"ms" << endl;	

	std::cout << "PROGRESS ###" << std::endl;

	auto startFor = high_resolution_clock::now();
	//boucle principale
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
		if (i % 60 == 0) {
			std::cout << "#";
		}
	}
	auto stopFor = high_resolution_clock::now();
	auto durationFor = duration_cast<seconds>(stopFor - startFor);
	long long sec = durationFor.count();

	//60 seconds in a minute
	long long min = sec / 60;
	sec = sec % 60;

	cout << "##\nDuration For : " << min << "min : "<< sec<<" sec" << endl;

	cout << "Duration Total : " << durationFor.count()<<" sec : " << durationBox.count() << "ms" << endl;

	//Creation de l image
	//boucle de convertion
	std::cout << "\nGeneration du fichier";
	ppm.save("image.ppm");

}

