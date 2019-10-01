#include "Couleur.h"

Couleur::Couleur(float red, float green, float blue)
{
	r = red;
	g = green;
	b = blue;
	color = Vec3<float>{ red, green, blue };
}

Couleur::Couleur()
{
	r = 1.f;
	g = 1.f;
	b = 1.f;
	color = Vec3<float>{ 1.f, 1.f, 1.f };
}
