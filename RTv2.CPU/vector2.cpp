#include "vector2.h"


vector2::vector2()
{

}

vector2::vector2(float a, float b) : x(a), y(b)
{

}

vector2 operator + (vector2 v1, vector2 v2)
{
	vector2 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	return result;

}

vector2 operator - (vector2 v1, vector2 v2)
{
	vector2 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	return result;
}

vector2 operator * (float num, vector2 v)
{
	vector2 result;
	result.x = num * v.x;
	result.y = num * v.y;
	return result;
}

vector2 operator * (int num, vector2 v)
{
	vector2 result;
	result.x = num * v.x;
	result.y = num * v.y;
	return result;
}