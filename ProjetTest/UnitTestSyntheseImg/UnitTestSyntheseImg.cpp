#pragma once
#include "pch.h"
#include "CppUnitTest.h"
#include "..//ProjetTest/Sphere.cpp"
#include "..//ProjetTest/Rayon.cpp"
#include "..//ProjetTest/Lumiere.cpp"
#include "..//ProjetTest/Vecteur.cpp"
#include "..//ProjetTest/Intersect.cpp"
#include "..//ProjetTest/Albedo.cpp"
#include "..//ProjetTest/Couleur.cpp"
#include <optional>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestSyntheseImg
{
	TEST_CLASS(UnitTestSyntheseImg)
	{
	public:
		TEST_METHOD(TestIntersect1)
		{
			Rayon R(Vec3<float>{0.f, 0.f, 0.f}, Vec3<float>{1.f, 0.f, 0.f});
			Sphere S(Vec3<float>{4.f, 0.f, 0.f}, 3.f,Albedo());
			if (auto res = S.intersect(R).t.value_or(-1.f)) {
				auto normal = S.intersect(R).normal;
				
				Assert::AreEqual(1.f, res);
				Assert::AreEqual(true,Vec3<float>{-1, 0, 0}==normal);
				
			}
		}

		TEST_METHOD(TestIntersect2) {
			Rayon R(Vec3<float>{0.f, 0.f, 0.f}, Vec3<float>{-1.f, 0.f, 0.f});
			Sphere S(Vec3<float>{-4.f, 0.f, 0.f}, 3.f,Albedo());
			if (auto res = S.intersect(R).t.value_or(-1.f)) {
				Assert::AreEqual(1.f, res);
				auto normal = S.intersect(R).normal;
				Assert::AreEqual(true, Vec3<float>{1, 0, 0} == normal);
			}
		}

		TEST_METHOD(TestIntersect3) {
			Rayon R(Vec3<float>{0.f, 0.f, 0.f}, Vec3<float>{1.f, 0.f, 0.f});
			Sphere S(Vec3<float>{4.f, 3.f, 0.f}, 3.f,Albedo());
			if (auto res = S.intersect(R).t.value_or(-1.f)) {
				Assert::AreEqual(4.f, res);
				auto normal = S.intersect(R).normal;
				Assert::AreEqual(true, Vec3<float>{0, -1, 0} == normal);
			}
		}
	};
}
