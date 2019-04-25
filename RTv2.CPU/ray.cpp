#include "ray.h"
#include "math_util.h"

ray::ray()
{

}

ray::ray(vector3 origin, vector3 dir) : _origin(origin)
{
	_dir = math_util::normalize(dir);
}

void ray::set_origin(vector3 origin)
{
	_origin = origin;
}

void ray::set_direction(vector3 direction)
{
	_dir = math_util::normalize(direction);
}

vector3 ray::get_origin() const
{
	return _origin;
}

vector3 ray::get_dir() const
{
	return _dir;
}

ray ray::create_from_origin_and_at(vector3 origin, vector3 at)
{
	return ray(origin, math_util::normalize(at - origin));
}