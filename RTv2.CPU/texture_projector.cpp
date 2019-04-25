#include "texture_projector.h"

texture_projector::texture_projector()
{

}

texture_projector::texture_projector(vector3 vertices[4])
{
	for (int i = 0; i < 4; i++)
	{
		_vertices[i] = vertices[i];
	}
}


bool texture_projector::intersect(ray r, intersection& intersect)
{
	return false;// implement after rectangle
}
