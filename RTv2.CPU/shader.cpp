#include "shader.h"
#include "geometry.h"
#include "light.h"
#include "material.h"
#include "database.h"
#include "visibility.h"

using namespace RTv2::renderer;


vector3 shader::shade_helper(intersection intersect)
{
	geometry& geom = _db_geometries[intersect._geom_index];
	material& mat = _db_materials[geom.get_material_index()];

	vector3 color = vector3(0, 0, 0);

	vector3 ambience = mat.get_ambient_color(intersect, _db_vector_textures);
	vector3 diffuse = mat.get_diffuse_color(intersect, _db_vector_textures);

	vector3 inv_cam_dir = -1 * _db_camera.get_view_dir();
	for (light light_source : _db_lights)
	{
		vector3 light_color = light_source.get_color(intersect, _db_geometries);
		vector3 inv_light_dir = -1 * light_source.get_direction(intersect._point);
		color = color + (light_color * ambience + light_color * diffuse * math_util::dot(intersect._normal, inv_light_dir));


		if (mat.get_is_specular())
		{
			vector3 halfway_vec =0.5f * (inv_cam_dir + inv_light_dir);

			color = color + (light_color * mat.get_specular_color(intersect, _db_vector_textures) * powf(math_util::dot(
				intersect._normal, halfway_vec), mat.get_specularity(intersect, _db_scalar_textures)));
		}

	}

}



void shader::shade(intersection& intersect, vector3& color,  vector3& depth_map)
{


	float depth = 1 - (intersect._dist / FAR_PLANE);
	depth_map.x = depth;
	depth_map.y = depth;
	depth_map.z = depth;

	color = shade_helper(intersect);

	geometry& geom = _db_geometries[intersect._geom_index];
	material& mat = _db_materials[geom.get_material_index()];

	if (mat.get_is_reflective_refractive())
	{
		vector3 reflect_color;
		vector3 inverted_cam_dir = -1 * _db_camera.get_view_dir();
		vector3 reflected_dir = 2 * math_util::dot(intersect._normal, inverted_cam_dir) * intersect._normal - inverted_cam_dir;
		ray r = ray(intersect._point, reflected_dir);
		intersection reflect_int;

		if (visibility::is_visible(r, reflect_int, geom.get_index()))
		{
			reflect_color = shade_helper(reflect_int);
		}

		float reflectivity = mat.get_reflectivity(intersect, _db_scalar_textures);
		float transparency = mat.get_transparency(intersect, _db_scalar_textures);
		float refractive_index = mat.get_refractive_index(intersect, _db_scalar_textures);
		color = (1 - reflectivity - transparency) * color;
		color = color + reflectivity * reflect_color;

		vector3 refract_color = vector3(0, 0, 0);
		float cos_theta_in = math_util::dot(intersect._normal, inverted_cam_dir);
		float sin_theta_in = sqrtf(1 - powf(cos_theta_in, 2));
		float sin_theta_out = sin_theta_in / refractive_index;
		float cos_theta_out = sqrtf(1 - powf(sin_theta_out, 2));

		float inv_refractive_index = 1 / refractive_index;

		vector3 refract_dir = -1 * ((inv_refractive_index * inverted_cam_dir) - (cos_theta_out - (inv_refractive_index * cos_theta_in)) * intersect._normal);
		r = ray(intersect._point, refract_dir);
		intersection refract_int;

		if (visibility::is_visible(r, refract_int, geom.get_index()))
		{
			refract_color = shade_helper(refract_int);
		}

		color = color + transparency * refract_color;
	}
		

}