#ifndef  RAY_H
#define RAY_H

#include "vector3.h"

class ray
{
private: 
	vector3 _origin;
	vector3 _dir;
public:
	ray();

	ray(vector3 origin, vector3 dir);

	void set_origin(vector3 origin);

	void set_direction(vector3 dir);

	vector3 get_origin() const;

	vector3 get_dir() const;

	static ray create_from_origin_and_at(vector3 origin, vector3 at);
};
#endif // ! RAY_H
