#include "light_helpers.h"

vector3 light_helpers::get_spot_light_color(const vector3& origin, const vector3 & direction, const vector3& color, const intersection& intersect, vector<geometry>& db_geometries, bool has_range,
	float max_range, float drop_off_fract, float central_fov, float outer_fov, float drop_off_const)
{
	vector3 temp_color;
	temp_color.x = 0;
	temp_color.y = 0;
	temp_color.z = 0;
	vector3 light_dir = math_util::normalize(intersect._point - origin);
	float cos_theta_dir = math_util::dot(light_dir, direction);
	float outer_cos = cosf(0.5f * outer_fov);
	if (cos_theta_dir > outer_cos)
	{//within the spot light range
		temp_color = get_point_light_color(origin, color, intersect, db_geometries, has_range, max_range, drop_off_fract);
		float inner_cos = cosf(0.5f * central_fov);

		if (cos_theta_dir < inner_cos)
		{
			//outside the full penumbra (compute drop off)
			float drop_off = powf((cos_theta_dir - outer_cos) / (inner_cos - outer_cos), drop_off_const);
			temp_color = drop_off * temp_color;
		}
	}
	return temp_color;

	


}