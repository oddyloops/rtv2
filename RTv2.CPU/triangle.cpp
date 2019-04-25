#include "geometry_helpers.h"


bool geometry_helpers::intersect_triangle(int geom_index, texture_map<vector3>& normal_map, const ray& r, intersection& intersect, vector3 vertices[], vector<texture<vector3, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>>& db_texture)
{
	vector3 true_normal = math_util::normalize(math_util::cross((vertices[2] - vertices[0]), (vertices[1] - vertices[0])));
	bool intersected = false;
	float dist = 0;
	if (ray_plane_intersection(r, vertices[0], true_normal, dist))
	{
		if (dist > 0 && dist < intersect._dist)
		{
			vector3 pt = r.get_origin() + dist * r.get_dir();
			//check if point is in triangle
			//using barycentric coordinates
			vector3 v2v0 = vertices[2] - vertices[0];
			vector3 v1v0 = vertices[1] - vertices[0];
			vector3 v1v2 = vertices[1] - vertices[2];
			vector3 pv0 = pt - vertices[0];
			vector3 pv1 = pt - vertices[1];
			vector3 pv2 = pt - vertices[2];
			float triangle_area = math_util::magnitude(math_util::cross(v2v0, v1v0));
			float u_area = math_util::magnitude(math_util::cross(pv0, v1v0));
			float v_area = math_util::magnitude(math_util::cross(v2v0, pv0));
			float w_area = math_util::magnitude(math_util::cross(v1v2, pv2));

			intersected = (u_area + v_area + w_area) <= triangle_area;
			if(intersected)
			{
				//within triangle
				intersect._geom_index = geom_index;
				intersect._dist = dist;
				intersect._point = pt;
				intersect._u = u_area / triangle_area;
				intersect._v = v_area / triangle_area;
				intersect._normal = normal_map.get_texel(intersect, db_texture);

			}
			

		
		}
		//else negative dist means ray intersects behind the camera so that doesn't count
	}
	return intersected;
}