#include "light_helpers.h"

vector3 light_helpers::get_point_light_color(const vector3& origin, const vector3& color, const intersection& intersect, vector<geometry>& db_geometries, bool has_range,
	float max_range, float drop_off_fract)
{
	ray light_ray = ray::create_from_origin_and_at(intersect._point, origin);
	float mult = 0;
	if (_enable_soft_shadow)
	{
		mult = shadow_super_sampling(light_ray, db_geometries);
	}
	else
	{
		mult = single_shadow(light_ray, db_geometries) ? 0 : 1;
	}

	if (has_range)
	{
		float dist = math_util::magnitude(origin - intersect._point);
		if (dist > ((1 - drop_off_fract) * max_range))
		{
			//use linear drop off function for performance reasons
			float max_drop = drop_off_fract * max_range;
			mult *= ((max_range - dist) / max_drop);
		}
	}

	return mult * color;
}