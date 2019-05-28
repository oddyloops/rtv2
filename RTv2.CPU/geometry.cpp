#include "geometry.h"
#include "geom_codes.h"
#include "geometry_helpers.h"
#include "database.h"

using namespace RTv2::objects;

geometry::geometry(byte geom_code) : _geom_code(geom_code)
{

}

void geometry::set_geom_code(byte geom_code)
{
	_geom_code = geom_code;
}

void geometry::set_material_index(int mat_index)
{
	_material_index = mat_index;
}

void geometry::set_volume_coefficients(float absorption_coeff, float scatter_coeff)
{
	_is_volume = true;
	_absorption_coeff = absorption_coeff;
	_scatter_coeff = scatter_coeff;
}

void geometry::set_normal(texture_map<vector3> normal)
{
	_normal = normal;
}

void geometry::set_vertices(vector3 vertices[4])
{
	for (int i = 0; i < 4; i++)
	{
		_vertices[i] = vertices[i];
	}
}

void geometry::set_center(vector3 center)
{
	_center = center;
}

void geometry::set_radius(float radius)
{
	_radius = radius;
}

void geometry::set_vertical_axis(vector3 vertical_axis)
{
	_vertical_axis = vertical_axis;
}

void geometry::set_height(float height)
{
	_height = height;
}

int geometry::get_material_index() const
{
	return _material_index;
}

float geometry::get_absorption_coefficient() const
{
	return _absorption_coeff;
}

float geometry::get_scatter_coefficient() const
{
	return _scatter_coeff;
}

bool geometry::get_is_volume() const
{
	return _is_volume;
}

float geometry::get_radius() const
{
	return _radius;
}

float geometry::get_theta()
{
	if (_theta < 0)
	{
		//hasn't been computed
		_theta = atanf(_radius / _height);
	}
	return _theta;
}

float geometry::get_height() const
{
	return _height;
}

vector3 geometry::get_center() const
{
	return _center;
}

vector3 geometry::get_vertical_axis() const
{
	return _vertical_axis;
}

bool geometry::intersects(ray r, intersection& intersect, int except_index)
{
	bool intersects = false;
	switch (_geom_code)
	{
	case geom_codes::rectangle:
		intersects = geometry_helpers::intersect_rectangle(_index, _normal, r, intersect, _vertices, _db_vector_textures);
		break;
	case geom_codes::sphere:
		intersects = geometry_helpers::intersect_sphere(_index, _normal, r, intersect, _center, _radius, _vertical_axis, _db_vector_textures);
		break;
	case geom_codes::triangle:
		intersects = geometry_helpers::intersect_triangle(_index, _normal, r, intersect, _vertices, _db_vector_textures);
		break;
	case geom_codes::cylinder:
		intersects = geometry_helpers::intersect_cylinder(_index, _normal, r, intersect, _center, _radius, _vertical_axis, _height, _db_vector_textures);
		break;
	case geom_codes::cone:
		intersects = geometry_helpers::intersect_cone(_index, _normal, r, intersect, _center, _radius, _vertical_axis, _height,get_theta(),_db_vector_textures);
		break;
	}

	
	if (intersects && _is_volume)
	{
		//start volumetric intersection implementation
	}
	return intersects;
}

vector2 geometry::get_uv_at_point(vector3 _point)
{
	vector2 uv;
	vector3 true_normal;
	vector3 delta_pt;
	float project;
	switch (_geom_code)
	{
	case geom_codes::rectangle:
		uv = geometry_helpers::get_rectangle_uv(_point, _vertices[0], math_util::normalize(_vertices[3] - _vertices[0]), math_util::normalize(_vertices[1] - _vertices[0]));
		break;
	case geom_codes::sphere:
		uv = geometry_helpers::get_sphere_uv(_point, _center, _radius, _vertical_axis);
		break;
	case geom_codes::triangle:
		uv = geometry_helpers::get_triangle_uv(_point, _vertices);
		break;
	case geom_codes::cylinder:
		
		delta_pt = _point - _center;
		project = math_util::dot(delta_pt, _vertical_axis);
		if ((project - _height) < FLT_EPSILON)
		{
			//projection of delta pt is less than the height of the cylinder (curved surface)
			vector3 start_pt = _center + project * _vertical_axis;
			true_normal = math_util::normalize(_point - start_pt);
		}
		else
		{
			//check if top or bottom
			if ((project - 0) < FLT_EPSILON)
			{
				//perpendicular to the axis means bottom
				true_normal = -1 * _vertical_axis;
			}
			else
			{
				true_normal = _vertical_axis;
			}
		}
		uv = geometry_helpers::get_cylinder_uv(_point, _center, _radius, _vertical_axis, true_normal, _height);
		break;
	case geom_codes::cone:
		delta_pt = _point - _center;
		project = math_util::dot(delta_pt, _vertical_axis);
		if ((project - _height) < FLT_EPSILON)
		{
			//projection of delta pt is less than the height of the cone (curved surface)
			vector3 apex = _center + _height * _vertical_axis;
			float dist_apex = math_util::magnitude(apex - _point);
			float dist_apex_axis = dist_apex * cosf(get_theta());
			float dist_center_axis = _height - dist_apex_axis;
			vector3 start_pt = _center + dist_center_axis * _vertical_axis;
			true_normal = math_util::normalize(_point - start_pt);
		}
		else
		{
			true_normal = -1 * _vertical_axis;
		}
		uv = geometry_helpers::get_cone_uv(_point, _center, _radius, _vertical_axis, true_normal, _height);
		break;
	}
	return uv;
}