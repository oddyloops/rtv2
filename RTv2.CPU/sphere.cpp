#include "geometry_helpers.h"

vector2 geometry_helpers::get_sphere_uv(vector3 pt, vector3 center, float radius, vector3 vertical_axis)
{
	float v = (1 + (math_util::dot(pt - center, vertical_axis) / radius)) * 0.5f;
	vector3 n = math_util::normalize(pt - center);
	float u = atan2(n.x, n.z) / (2 * PI) + 0.5;
	vector2 uv;
	uv.x = u;
	uv.y = v;
	return uv;
}


bool geometry_helpers::intersect_sphere(int geom_index, texture_map<vector3>& normal_map, const ray& r, intersection& intersect, vector3 center, float radius, vector3 vertical_axis, vector<texture<vector3, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>>& db_texture)
{
	vector3 l = center - r.get_origin();
	float tca = math_util::dot(l, r.get_dir());
	bool intersects = false;
	if (tca > 0)
	{
		float d = sqrtf(math_util::magnitude_sq(l) - tca * tca);
		if (d <= radius)
		{
			float thc = sqrtf(radius * radius - d * d);
			float dist1 = tca - thc;
			if (dist1 > 0)
			{
				
				//only need dist1 being the closer intersection point
				if (dist1 < intersect._dist)
				{
					vector3 pt = r.get_origin() + dist1 * r.get_dir();
					intersects = true;
					intersect._dist = dist1;
					intersect._point = pt;
					vector2 uv = get_sphere_uv(pt, center, radius, vertical_axis);
					intersect._u = uv.x;
					intersect._v = uv.y;
					intersect._normal = normal_map.get_is_mapped() ? normal_map.get_texel(intersect, db_texture)
						: math_util::normalize(pt - center);
				}
			}
		}
	}
	return intersects;
}