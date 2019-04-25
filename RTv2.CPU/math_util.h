#ifndef MATH_H
#define MATH_H

#include "vector2.h"
#include "vector3.h"

class math_util
{

public:

	static float rand_range(float from, float to);

	static float magnitude_sq(vector2 v2);

	static float magnitude(vector2 v2);

	static vector2 normalize(vector2 v2);

	static float dot(vector2 v1, vector2 v2);

	static float magnitude_sq(vector3 v3);

	static float magnitude(vector3 v3);

	static vector3 normalize(vector3 v3);

	static float dot(vector3 v1, vector3 v2);

	static vector3 cross(vector3 v1, vector3 v2);

};

#endif