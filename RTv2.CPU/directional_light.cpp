#include "light_helpers.h"
#include "ray.h"
#include "database.h"

vector3 light_helpers::get_directional_light_color(const vector3& direction, const vector3& color, const intersection& intersect, vector<geometry>& db_geometries)
{
	ray light_ray = ray(intersect._point, (-1) * direction);

	float mult = 0;
	if (_enable_soft_shadow)
	{
		mult = shadow_super_sampling(light_ray, db_geometries);
	}
	else
	{
		mult = single_shadow(light_ray, db_geometries) ? 0 : 1;
	}

	return mult * color;
	
}