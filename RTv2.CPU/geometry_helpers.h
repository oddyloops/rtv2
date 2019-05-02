#ifndef GEOMETRY_HELPERS
#define GEOMETRY_HELPERS

#include <vector>

#include "vector3.h"
#include "intersection.h"
#include "ray.h"
#include "texture.h"
#include "math_util.h"
#include "texture_map.h"

using namespace std;

class geometry_helpers
{
private:
	static bool ray_plane_intersection(const ray& r, vector3 v, vector3 n, float& dist)
	{
		//formula for intersection distance t in a plane =( [v(0) - ray_orig].n)/(ray_dir.n)
		float denom = math_util::dot(r.get_dir(), n);
		if (denom > FLT_EPSILON)
		{
			dist = math_util::dot((v - r.get_origin()), n) / denom;
			return true;
		}
		//else perpendicular to normal means they never intersect or they intersect at infinite points
		return false;
	}

	static bool inside_circle(vector3 pt, vector3 center, float radius)
	{
		return (radius * radius) >= (math_util::magnitude_sq(pt - center));
	}

public:
	static vector2 get_rectangle_uv(vector3 pt, vector3 vertex0, vector3 u_vec, vector3 v_vec);

	static vector2 get_sphere_uv(vector3 pt, vector3 center, float radius, vector3 vertical_axis);

	static vector2 get_cylinder_uv(vector3 pt, vector3 center, float radius, vector3 vertical_axis, vector3 true_normal, float height);

	static bool intersect_rectangle(int geom_index, texture_map<vector3>& normal_map,const ray& r, intersection& intersect, vector3 vertices[], vector<texture<vector3, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>>& db_texture);

	static bool intersect_triangle(int geom_index, texture_map<vector3>& normal_map, const ray& r, intersection& intersect, vector3 vertices[], vector<texture<vector3, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>>& db_texture);

	static bool intersect_sphere(int geom_index, texture_map<vector3>& normal_map, const ray& r, intersection& intersect, vector3 center, float radius, vector3 vertical_axis, vector<texture<vector3, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>>& db_texture);

	static bool intersect_cylinder(int geom_index, texture_map<vector3>& normal_map, const ray& r, intersection& intersect, vector3 center, float radius,  vector3 vertical_axis, float height, vector<texture<vector3, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>>& db_texture);

};
#endif