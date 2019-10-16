// Vecteur.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#pragma once
#include <iostream>
#include <cmath>

#include <iostream>
#include <fstream>
using namespace std;

template <typename T>
struct Vec3 {
	T x, y, z;
};
 
template <typename T>
bool operator==(const Vec3<T>& a, const Vec3<T>& b) {
	return a.x == b.x && a.y == b.y && a.z == b.z;
}

template <typename T>
Vec3<T> operator+(const Vec3<T>& a, const Vec3<T>& b) {
	return Vec3<T>{ a.x + b.x, a.y + b.y, a.z + b.z };
}

template <typename T>
Vec3<T> operator*(const Vec3<T>& a, const Vec3<T>& b) {
	return Vec3<T>{ a.x * b.x, a.y * b.y, a.z * b.z };
}

template <typename T>
Vec3<T> operator*(const float a, const Vec3<T>& b) {
	return Vec3<T>{ a * b.x, a * b.y, a * b.z };
}

template <typename T>
Vec3<T> operator/(const Vec3<T>& a, const Vec3<T>& b) {
	return Vec3<T>{ a.x / b.x, a.y / b.y, a.z / b.z };
}

template <typename T>
Vec3<T> operator/(const Vec3<T>& a, const float b) {
	return Vec3<T>{ a.x / b, a.y / b, a.z / b };
}

template <typename T>
Vec3<T> operator/(const float a, const Vec3<T>& b) {
	return Vec3<T>{ a/b.x, a/b.y, a/b.z};
}

template <typename T>
Vec3<T> operator-(const Vec3<T>& a, const Vec3<T>& b) {
	return Vec3<T>{ a.x - b.x, a.y - b.y, a.z - b.z };
}

template <typename T>
float dot(const Vec3<T>& a, const Vec3<T>& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

template <typename T>
Vec3<T> cross(const Vec3<T>& a, const Vec3<T>& b) {
	//return a.x * b.x + a.y * b.y + a.z * b.z;
	T uv1 = a.y * b.z - b.y * a.z;
	T uv2 = b.x * a.z - a.x * b.z;
	T uv3 = a.x * b.y - b.x * a.y;

	return Vec3<T>{uv1, uv2, uv3};
}

template <typename T>
float norm_squared(const Vec3<T>& v) {
	return dot(v, v);
}

template <typename T>
float norm(Vec3<T>& v) {
	return std::sqrt(norm_squared(v));
}

template <typename T>
Vec3<T> add(const Vec3<T>& a, const Vec3<T>& b) {
	return Vec3{ a.x + b.x, a.y + b.y, a.z + b.z };
}

template<typename T>
void normalize(Vec3<T>& a) {
	float norme = norm(a);
	a.x = a.x / norme;
	a.y = a.y / norme;
	a.z = a.z / norme;
}

/*int main() {
	ofstream monFlux("Tab.txt");
	//monFlux << "hello"<<endl;

	Vec3<float> origin = Vec3<float>{ 0.f,0.f,0.f};
	Vec3<float> currentPos = Vec3<float>{ 0.f,0.f,20000.f };
	Vec3<float> V0 = Vec3<float>{ 40.f,0.f,0.f };
	float currentTime = 0.f;
	float maxTime = 60.f;
	float deltaT = 0.05f;
	float gravite = 9.84f;
	float masse = 80.f;
	float Constant = (masse * gravite)/(70*70); //C = mg/50²
	float vitesseVent = - 20.f;
	Vec3<float> repere = Vec3<float>{ 1.f,1.f,1.f };

	//Version de base avec des equations parametrique
	/*while (currentTime < maxTime) {
		Vec3<float> acceleration = Vec3<float>{ 0.f, 0.f, -gravite * repere.z};
		Vec3<float> vitesse = currentTime * acceleration + V0;
		Vec3<float> position = (currentTime*currentTime*acceleration)/2 + currentTime*V0 + origin;

		monFlux << currentTime << "\t" << position.x << "\t" << position.y << "\t" << position.z << endl;

		currentTime += deltaT; //on avance dans le temps
	}


	//Version ameliore avec des recursif
	Vec3<float> vitesse = V0;
	while (currentTime < maxTime) {
		monFlux << currentTime << "\t" << currentPos.x << "\t" << currentPos.y << "\t" << currentPos.z << endl;

		//Vec3<float> acceleration = Vec3<float>{ 0.f, 0.f, -gravite * repere.z};
		Vec3<float> acceleration = Vec3<float>{ 0.f, 0.f, -gravite * repere.z } - (norm(vitesse) * (Constant * vitesse))/masse; //utilisation des frottements
		vitesse = vitesse + deltaT*acceleration;
		currentPos = currentPos + deltaT*vitesse;
		currentPos.x +=deltaT*vitesseVent;//le vent

		currentTime += deltaT; //on avance dans le temps
	}
}*/
