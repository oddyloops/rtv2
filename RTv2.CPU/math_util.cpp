#include "math_util.h"
#include <math.h>
#include <time.h>
#include <cstdlib>

float math_util::rand_range(float from, float to)
{
	srand(time(0));
	float random = ((float)rand()) / INT_MAX;
	return from + (random * (to - from));
}

float math_util::magnitude_sq(vector2 v2)
{
	return v2.x * v2.x + v2.y * v2.y;
}

float math_util::magnitude(vector2 v2)
{
	return sqrtf(magnitude_sq(v2));
}

vector2 math_util::normalize(vector2 v2)
{
	vector2 norm;
	float size = magnitude(v2);
	norm.x = v2.x / size;
	norm.y = v2.y / size;
	return norm;
}

float math_util::dot(vector2 v1, vector2 v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

float math_util::magnitude_sq(vector3 v3)
{
	return v3.x * v3.x + v3.y * v3.y + v3.z * v3.z;
}

float math_util::magnitude(vector3 v3)
{
	return sqrtf(magnitude_sq(v3));
}

vector3 math_util::normalize(vector3 v3)
{
	vector3 norm;
	float size = magnitude(v3);
	norm.x = v3.x / size;
	norm.y = v3.y / size;
	norm.z = v3.z / size;
	return norm;
}

float math_util::dot(vector3 v1, vector3 v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vector3 math_util::cross(vector3 v1, vector3 v2)
{
	vector3 result;
	result.x = (v1.y * v2.z) - (v1.z * v2.y);
	result.y = -((v1.x * v2.z) - (v1.z * v2.x));
	result.z = (v1.x * v2.y) - (v1.y * v2.x);
	return result;
}