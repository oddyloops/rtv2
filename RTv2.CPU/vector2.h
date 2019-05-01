#ifndef VECTOR2_H
#define VECTOR2_H


struct vector2
{
	float x;
	float y;

	vector2();

	vector2(float a, float b);
};

vector2 operator + (vector2 v1, vector2 v2);

vector2 operator - (vector2 v1, vector2 v2);

vector2 operator * (float num, vector2 v);

vector2 operator * (int num, vector2 v);

#endif