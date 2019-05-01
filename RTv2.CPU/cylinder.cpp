#include "geometry_helpers.h"


bool geometry_helpers::intersect_cylinder(int geom_index, texture_map<vector3>& normal_map, const ray& r, intersection& intersect, vector3 center, float radius, vector3 vertical_axis, vector<texture<vector3, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>>& db_texture)
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

}