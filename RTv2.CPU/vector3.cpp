#include "vector3.h"

vector3::vector3() {

}

vector3::vector3(float a, float b, float c) : x(a), y(b), z(c)
{

}

vector3 operator + (vector3 v1, vector3 v2)
{
	vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

vector3 operator - (vector3 v1, vector3 v2)
{
	vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}

vector3 operator * (float num, vector3 v)
{
	vector3 result;
	result.x = num * v.x;
	result.y = num * v.y;
	result.z = num * v.z;
	return result;

}

vector3 operator * (int num, vector3 v)
{
	vector3 result;
	result.x = num * v.x;
	result.y = num * v.y;
	result.z = num * v.z;
	return result;
}