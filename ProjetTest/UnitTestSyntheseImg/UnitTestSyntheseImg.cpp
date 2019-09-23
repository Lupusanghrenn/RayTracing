#pragma once
#include "pch.h"
#include "CppUnitTest.h"
#include "..//ProjetTest/RayTracing.cpp"
#include "..//ProjetTest/Sphere.cpp"
#include "..//ProjetTest/Rayon.cpp"
#include "..//ProjetTest/Lumiere.cpp"
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
			Sphere S(Vec3<float>{4.f, 0.f, 0.f}, 3.f);
			if (auto res = RayTracing::intersect(R, S).value_or(-1.f)) {
				Assert::AreEqual(1.f, res);
			}
		}

		TEST_METHOD(TestIntersect2) {
			Rayon R(Vec3<float>{0.f, 0.f, 0.f}, Vec3<float>{-1.f, 0.f, 0.f});
			Sphere S(Vec3<float>{-4.f, 0.f, 0.f}, 3.f);
			if (auto res = RayTracing::intersect(R, S).value_or(-1.f)) {
				Assert::AreEqual(1.f, res);
			}
		}

		TEST_METHOD(TestIntersect3) {
			Rayon R(Vec3<float>{0.f, 0.f, 0.f}, Vec3<float>{1.f, 0.f, 0.f});
			Sphere S(Vec3<float>{4.f, 3.f, 0.f}, 3.f);
			if (auto res = RayTracing::intersect(R, S).value_or(-1.f)) {
				Assert::AreEqual(4.f, res);
			}
		}
	};
}
