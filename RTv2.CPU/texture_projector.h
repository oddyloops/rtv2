#ifndef TEXTURE_PROJECTOR_H
#define TEXTURE_PROJECTOR_H

#include "vector3.h"
#include "vector2.h"
#include "ray.h"
#include "intersection.h"

class texture_projector
{
	vector3 _vertices[4];

	texture_projector();

	texture_projector(vector3 vertices[4]);

	bool intersect(ray r, intersection& intersect);

};

#endif