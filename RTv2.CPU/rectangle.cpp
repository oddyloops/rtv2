
#include "geometry_helpers.h"
#include "math_util.h"
#include "constants.h"


vector2 geometry_helpers::get_rectangle_uv(vector3 pt, vector3 vertex0, vector3 u_vec, vector3 v_vec)
{
	vector3 pt_vec = math_util::normalize(pt - vertex0);
	vector2 uv;
	uv.x = math_util::dot(pt_vec, u_vec);
	uv.y = math_util::dot(pt_vec, v_vec);
	return uv;
}


bool geometry_helpers::intersect_rectangle(int geom_index, texture_map<vector3>& normal_map, const ray& r, intersection& intersect, vector3 vertices[], vector<texture<vector3, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>>& db_texture)
{
	vector3 true_normal = math_util::normalize(math_util::cross((vertices[3] - vertices[0]), (vertices[1] - vertices[0])));
	bool intersected = false;
	float dist = 0;
	if (ray_plane_intersection(r, vertices[0], true_normal, dist))
	{
		if (dist > 0 && dist <  intersect._dist)
		{
			vector3 pt = r.get_origin() + dist * r.get_dir();
			//check if point is in rectangle
			vector3 u_vec = math_util::normalize(vertices[3] - vertices[0]);
			vector3 v_vec = math_util::normalize(vertices[1] - vertices[0]);
			vector3 pt_vec = math_util::normalize(pt - vertices[0]);

			intersected = math_util::dot(pt_vec, u_vec) > 0 && math_util::dot(pt_vec, v_vec) > 0;
			if (intersected)
			{
				intersect._point = pt;
				intersect._geom_index = geom_index;
				vector2 uv = get_rectangle_uv(pt, vertices[0], u_vec, v_vec);
				intersect._u = uv.x;
				intersect._v = uv.y;
				intersect._normal = normal_map.get_texel(intersect, db_texture);
				intersect._dist = dist;
			}
		}
		//else negative dist means ray intersects behind the camera so that doesn't count
	}
	return intersected;
}