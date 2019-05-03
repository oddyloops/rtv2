#include "geometry_helpers.h"
#include <algorithm>

vector2 geometry_helpers::get_cylinder_uv(vector3 pt, vector3 center, float radius, vector3 vertical_axis, vector3 true_normal, float height)
{
	vector3 delta_pt = pt - center;
	float u = 0;
	float v = 0;

	vector3 x_axis = vector3(1, 0, 0);
	vector3 z_axis = vector3(0, 0, 1);

	vector3 x_horizon = math_util::cross(vertical_axis, z_axis);
	vector3 z_horizon = math_util::cross(x_axis, vertical_axis);

	float x_projection = 0;
	float z_projection = 0;
	
	//tracing a line from the bottom center along the outer surface to the top center
	float total_texture_height = 2 * radius + height;
	
	//determine if point is on the curved or flat surface
	float project = math_util::dot(true_normal, vertical_axis);
	if ((project - 0) < FLT_EPSILON)
	{
		//normal perpendicular to the axis means it is on curved surface
		x_projection = math_util::dot(delta_pt, x_horizon);
		z_projection = math_util::dot(delta_pt, z_horizon);
		
		u = atan2(x_projection, z_projection) / (2 * PI) + 0.5;
		float curve_vert_start = radius / total_texture_height;
		float curve_vert_span = height / total_texture_height;
		float curve_pt_fract = math_util::dot(delta_pt, vertical_axis) / height;
		v = curve_vert_start + curve_pt_fract * curve_vert_span;
	}
	else
	{
		//check if top or bottom
		project = math_util::dot(delta_pt, vertical_axis);
		float flat_vert_span = radius / total_texture_height;
		if ((project - 0) < FLT_EPSILON)
		{
			//perpendicular to the axis means bottom
			x_projection = math_util::dot(delta_pt, x_horizon);
			z_projection = math_util::dot(delta_pt, z_horizon);
			
			u = atan2(x_projection, z_projection) / (2 * PI) + 0.5;
			v = (math_util::magnitude(delta_pt) / radius) * flat_vert_span;
		}
		else
		{
			vector3 top_center = center + height * vertical_axis;
			delta_pt = pt - top_center;

			x_projection = math_util::dot(delta_pt, x_horizon);
			z_projection = math_util::dot(delta_pt, z_horizon);

			u = atan2(x_projection, z_projection) / (2 * PI) + 0.5;
			float start_pt = flat_vert_span + height / total_texture_height;
			v = start_pt + (math_util::magnitude(delta_pt) / radius) * flat_vert_span;
		}
	}

	vector2 uv = vector2(u, v);
	return uv;
}

bool geometry_helpers::intersect_cylinder(int geom_index, texture_map<vector3>& normal_map, const ray& r, intersection& intersect, vector3 center, float radius, vector3 vertical_axis, float height, vector<texture<vector3, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>>& db_texture)
{
	//check for intersection on the flat surfaces
	float distances[4] = { -1,-1,-1,-1 }; //( top, bottom, curve 1 , curve 2)
	
	vector3 pt;
	//top
	if (ray_plane_intersection(r, center, vertical_axis, distances[0]))
	{
		pt = r.get_origin() + distances[0] * r.get_dir();
		if (!inside_circle(pt, center, radius))
		{
			//reset distance to default
			distances[0] = -1;
		}
	}

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
			if (project < 0 || project > height)
			{
				//out of bounds
				x1 = -1;
			}

			temp_pt = r.get_origin() + x2 * r.get_dir();
			project = math_util::dot(temp_pt - center, vertical_axis);
			if (project < 0 || project > height)
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