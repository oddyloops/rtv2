#include "light.h"
#include "math_util.h"
#include "light_codes.h"
#include "light_helpers.h"
#include "constants.h"

using namespace RTv2::objects;

light::light()
{

}

light::light(byte light_code) : _light_code(light_code), _has_range(false)
{
	_color.x = 1;
	_color.y = 1;
	_color.z = 1; //white by default
}

light::light(byte light_code, float max_range, float drop_off_fract) : _light_code(light_code), _has_range(true),
_max_range(max_range), _drop_off_fract(drop_off_fract)
{
	_color.x = 1;
	_color.y = 1;
	_color.z = 1; //white by default
}

void light::set_color(vector3 color)
{
	_color = color;
}

void light::set_direction(vector3 direction)
{
	_direction = math_util::normalize(direction);
}

void light::set_origin(vector3 origin)
{
	_origin = origin;
}

void light::set_central_fov(float fov)
{
	_central_fov = fov /PI;
}

void light::set_outer_fov(float fov)
{
	_outer_fov = fov / PI;
}

void light::set_drop_off_const(float drop_off)
{
	_drop_off_const = drop_off;
}

vector3 light::get_color() const
{
	return _color;
}

vector3 light::get_direction() const
{
	return _direction;
}

vector3 light::get_direction(vector3 pt)
{
	if (_light_code == light_code::directional) 
	{
		return _direction;
	}
	else
	{
		return light_helpers::get_light_dir_from_origin(pt, _origin);
	}
}


vector3 light::get_origin() const
{
	return _origin;
}

float light::get_central_fov() const
{
	return _central_fov;
}

float light::get_outer_fov() const
{
	return _outer_fov;
}

float light::get_drop_off_const() const
{
	return _drop_off_const;
}

vector3 light::get_color(const intersection& intersect, vector<geometry>& db_geometries) const
{
	switch (_light_code)
	{
	case light_code::directional:
		return light_helpers::get_directional_light_color(_direction, _color, intersect, db_geometries);
	case light_code::point:
		return light_helpers::get_point_light_color(_origin, _color, intersect, db_geometries, _has_range, _max_range, _drop_off_fract);
	default:
		break;
	}
}