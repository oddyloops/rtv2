#include "geometry_helpers.h"


bool geometry_helpers::intersect_cylinder(int geom_index, texture_map<vector3>& normal_map, const ray& r, intersection& intersect, vector3 top_center, vector3 bottom_center, float top_radius, float bottom_radius, vector3 vertical_axis, vector<texture<vector3, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>>& db_texture)
{
	//check for intersection on the flat surfaces
	float distances[4] = { -1,-1,-1,-1 }; //( , curve 1, curve 2, top, bottom)
	
	vector3 pt;
	//top
	if (ray_plane_intersection(r, top_center, vertical_axis, distances[2]))
	{
		pt = r.get_origin() + distances[2] * r.get_dir();
		if (!inside_circle(pt, top_center, top_radius))
		{
			//reset distance to default
			distances[2] = -1;
		}
	}

	if (ray_plane_intersection(r, bottom_center, -1 * vertical_axis, distances[3]))
	{
		pt = r.get_origin() + distances[3] * r.get_dir();
		if (!inside_circle(pt, bottom_center, bottom_radius))
		{
			//reset distance to default
			distances[3] = -1;
		}
	}

}