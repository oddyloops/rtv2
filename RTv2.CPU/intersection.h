#ifndef  INTERSECTION_H
#define INTERSECTION_H

#include <cfloat>
#include "vector3.h"
#include "constants.h"


struct intersection
{
	vector3 _point;
	float _u;
	float _v;
	float _dist = FLT_MAX;
	vector3 _normal; //normal at intersection point
	int _geom_index = UNINIT;
	int mesh_index = UNINIT;


};

#endif // ! INTERSECTION_H
