#ifndef LIGHT_HELPERS
#define LIGHT_HELPERS

#include <vector>

#include "vector3.h"
#include "geometry.h"
#include "intersection.h"
#include "database.h"
#include "math_util.h"

using namespace std;
using namespace RTv2::objects;

class light_helpers
{

private:
	static float shadow_super_sampling(const ray& r, vector<geometry>& db_geometries)
	{
		intersection shadow_int;
		float light_sum = 0;
		ray light_sample = r;
		vector3 origin = r.get_origin();
		float rnd = math_util::rand_range(-0.1, 0.1);
		const int SAMPLE_SIZE = 5;
		for (int i = 0; i < SAMPLE_SIZE; i++)
		{
			vector3 origin_sample;
			origin_sample.x = origin.x + rnd;
			origin_sample.y = origin.y + rnd;
			origin_sample.z = origin.z + rnd;
			light_sample.set_origin(origin_sample);
			bool intersected = false;
			for (size_t j = 0; j < db_geometries.size() && !intersected; j++)
			{
				intersected = db_geometries[j].intersects(light_sample, shadow_int, db_geometries[j].get_index());
			}

			if (!intersected)
			{
				light_sum += 1;
			}
		}

		return light_sum / SAMPLE_SIZE;

	}

	static bool single_shadow(const ray& r, vector<geometry>& db_geometries)
	{
		intersection shadow_int;
		bool intersected = false;
		for (size_t j = 0; j < db_geometries.size() && !intersected; j++)
		{
			intersected = db_geometries[j].intersects(r, shadow_int, db_geometries[j].get_index());
		}
		return intersected;
	}
public:

	static vector3 get_directional_light_color(const vector3& direction, const vector3& color, const intersection& intersect, vector<geometry>& db_geometries);

	static vector3 get_point_light_color(const vector3& origin, const vector3& color, const intersection& intersect, vector<geometry>& db_geometries,bool has_range,
		float max_range, float drop_off_fract);

	static vector3 get_spot_light_color(const vector3& origin, const vector3& direction,const vector3& color, const intersection& intersect, vector<geometry>& db_geometries, bool has_range,
		float max_range, float drop_off_fract, float central_fov, float outer_fov, float drop_off_const);

};

#endif