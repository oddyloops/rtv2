#include "geometry_helpers.h"

bool geometry_helpers::intersect_cone(int geom_index, texture_map<vector3>& normal_map, const ray& r, intersection& intersect, vector3 center, float radius, vector3 vertical_axis, vector<texture<vector3, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>>& db_texture)
{
	float distances[3] = { -1,-1,-1 }; //( bottom, curve 1 , curve 2)

	vector3 pt;
	

	//bottom
	if (ray_plane_intersection(r, center, -1 * vertical_axis, distances[1]))
	{
		pt = r.get_origin() + distances[1] * r.get_dir();
		if (!inside_circle(pt, center, radius))
		{
			//reset distance to default
			distances[1] = -1;
		}
	}

	//https://mrl.nyu.edu/~dzorin/rendering/lectures/lecture3/lecture3-6pp.pdf

	//curves
	//get quadratic coefficients
	vector3 delta_p = r.get_origin() - center;
	float a = math_util::magnitude_sq(r.get_dir() - (math_util::dot(r.get_dir(), vertical_axis) * vertical_axis));
	float b = 2 * math_util::dot(r.get_dir() - (math_util::dot(r.get_dir(), vertical_axis) * vertical_axis),
		delta_p - math_util::dot(delta_p, vertical_axis) * vertical_axis);
	float c = math_util::magnitude_sq(delta_p - (math_util::dot(delta_p, vertical_axis) * vertical_axis)) - (radius * radius);

	if (a > 0)
	{
		float root = b * b - 4 * a * c;
		if (root >= 0)
		{
			root = sqrtf(root);
			float x1 = (root - b) / (2 * a);
			float x2 = (root + b) / (2 * a);

			/*check if intersection points on the curved infinite cylinder
			are within bounds of the actual cylinder segment*/
			vector3 temp_pt = r.get_origin() + x1 * r.get_dir();
			float project = math_util::dot(temp_pt - center, vertical_axis);
			if (project < 0 && project > height)
			{
				//out of bounds
				x1 = -1;
			}

			temp_pt = r.get_origin() + x2 * r.get_dir();
			project = math_util::dot(temp_pt - center, vertical_axis);
			if (project < 0 && project > height)
			{
				//out of bounds
				x2 = -1;
			}

			if (x1 > 0)
			{
				if (x2 > 0)
				{
					distances[2] = std::min(x1, x2);
					distances[3] = std::max(x1, x2);
				}
				else
				{
					distances[2] = x1;
				}
			}
			else
			{
				if (x2 > 0)
				{
					distances[2] = x2;
				}
			}

		}
	}

	float dist = FLT_MAX; //set to minimum intersection point
	int distIndex = -1;
	for (int i = 0; i < 4; i++)
	{
		if (distances[i] >= 0 && distances[i] < dist)
		{
			dist = distances[i];
			distIndex = i;
		}
	}

	if (fabsf(dist - FLT_MAX) > FLT_EPSILON)
	{
		//there was an intersection
		pt = r.get_origin() + dist * r.get_dir();
		if (dist < intersect._dist)
		{
			intersect._dist = dist;
			intersect._geom_index = geom_index;
			intersect._point = pt;
			vector3 true_normal;
			//compute normal
			if (distIndex == 0)
			{
				//top intersection
				true_normal = vertical_axis;
			}
			else if (distIndex == 1)
			{
				//bottom intersection
				true_normal = -1 * vertical_axis;
			}
			else
			{
				//curved surface
				vector3 start_pt = center + math_util::dot(pt - center, vertical_axis) * vertical_axis;
				true_normal = math_util::normalize(pt - start_pt);
			}

			vector2 uv = get_cylinder_uv(pt, center, radius, vertical_axis, true_normal, height);
			intersect._u = uv.x;
			intersect._v = uv.y;
			intersect._normal = normal_map.get_is_mapped() ? normal_map.get_texel(intersect, db_texture)
				: true_normal;

			return true;
		}
	}

	return false;
}