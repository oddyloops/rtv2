#ifndef  VECTOR3_H
#define VECTOR3_H




struct vector3
{

	float x;
	float y;
	float z;

};


vector3 operator + (vector3 v1, vector3 v2);

vector3 operator - (vector3 v1, vector3 v2);

vector3 operator * (float num, vector3 v);

vector3 operator * (int num, vector3 v);


#endif 
