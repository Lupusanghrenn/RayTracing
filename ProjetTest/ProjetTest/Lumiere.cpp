#include "Lumiere.h"

Lumiere::Lumiere(Vec3<float> p, float red, float green, float blue, int i) {
	position = p;
	r = red;
	g = green;
	b = blue;
	color = Vec3<float>{ r, g, b };
	intensity = i;
}

Lumiere::Lumiere() {
	position = Vec3<float>{0.f, 0.f, 0.f};
	r = 255;
	g = 255;
	b = 255;
	color = Vec3<float>{ r, g, b };
	intensity = 1000;
}
