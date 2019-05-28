#include "texture_projector.h"
#include "geometry_helpers.h"
texture_projector::texture_projector()
{

}

texture_projector::texture_projector(vector3 vertices[4])
{
	for (int i = 0; i < 4; i++)
	{
		_vertices[i] = vertices[i];
	}
	_u_vec = math_util::normalize(_vertices[3] - _vertices[0]);
	_v_vec = math_util::normalize(_vertices[1] - _vertices[0]);
	_normal = math_util::cross(_u_vec,_v_vec);
}


bool texture_projector::intersect(ray r, intersection& intersect)
{
	
	bool intersected = false;
	float dist = 0;
	if (geometry_helpers::ray_plane_intersection(r, _vertices[0], _normal, dist))
	{
		if (dist > 0)
		{
			vector3 pt = r.get_origin() + dist * r.get_dir();
			//check if point is in rectangle
			vector3 pt_vec = math_util::normalize(pt - _vertices[0]);

			intersected = math_util::dot(pt_vec, _u_vec) > 0 && math_util::dot(pt_vec, _v_vec) > 0;
			if (intersected)
			{
				intersect._point = pt;
				
				vector2 uv = geometry_helpers::get_rectangle_uv(pt, _vertices[0], _u_vec, _v_vec);
				intersect._u = uv.x;
				intersect._v = uv.y;
				intersect._normal =_normal;
				intersect._dist = dist;
			}
		}
		//else negative dist means ray intersects behind the camera so that doesn't count
	}
	return intersected;
}
