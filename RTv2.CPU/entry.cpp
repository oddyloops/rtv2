#include "entry.h"
#include "database.h"
#include "visibility.h"
#include "shader.h"

using namespace RTv2::renderer;

template<typename T>
void entry::copy_vector(const vector<T>& from, vector<T>& to)
{
	for (int i = 0; i < from.size(); i++)
	{
		to.push_back(from[i]);
	}
}


vector<vector<vector3>> entry::render(vector<geometry>& geometries, vector<mesh>& meshes, vector<light>& lights, vector<material>& materials, int samples_per_pix, camera cam, vector3 bg,
	vector<texture<vector3, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>>& vector_textures, vector<texture<float, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>>& scalar_textures, bool enable_soft_shadow)
{
	copy_vector(geometries, _db_geometries);
	copy_vector(materials, _db_materials);
	copy_vector(lights, _db_lights);
	copy_vector(vector_textures, _db_vector_textures);
	copy_vector(scalar_textures, _db_scalar_textures);
	
	_db_camera = cam;
	_enable_soft_shadow = enable_soft_shadow;

	int rows = cam.get_resY();
	int columns = cam.get_resX();

	vector<vector3> image(rows * columns);
	vector<vector3> visible_map(rows * columns);
	vector<vector3> depth_map(rows * columns);
	
	float sample_quotient = 1.0f / samples_per_pix;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			vector3 pixel_pos = cam.get_img_origin() + cam.get_pixel_width() * cam.get_side_vec() - cam.get_pixel_height() * cam.get_up_vec();
			float rnd = math_util::rand_range(-0.1, 0.1);
			vector3 color = vector3(0,0,0);
			vector3 depth = vector3(0, 0, 0);
			bool visible = false;
			for (int k = 0; k < samples_per_pix; k++)
			{
				//random super sampling for now
				vector3 adjusted(pixel_pos.x + math_util::rand_range(-1, 1) * _db_camera.get_pixel_width(),
					pixel_pos.y + math_util::rand_range(-1, 1) * _db_camera.get_pixel_width(),
					pixel_pos.z + math_util::rand_range(-1, 1) * _db_camera.get_pixel_width()
				);
				intersection intersect;
				ray r;
				if (cam.get_is_ortho())
				{
					r = ray(adjusted, cam.get_view_dir());
				}
				else 
				{
					r = ray::create_from_origin_and_at(cam.get_eye(), adjusted);
				}


				bool intersected = visibility::is_visible(r, intersect, UNINIT);
				if (intersected)
				{
					visible = true;
					vector3 temp_color;
					vector3 temp_visible_map;
					vector3 temp_depth_map;
					shader::shade(intersect, temp_color, temp_depth_map);
					color = color + temp_color;
					depth = depth + temp_depth_map;

				}
				else
				{
					color = bg;
				}
			}
			color = sample_quotient * color;
			depth = sample_quotient * depth;
			if (visible)
			{
				visible_map.push_back(vector3(1, 1, 1));
			}
			else 
			{
				visible_map.push_back(vector3(0, 0, 0));
			}
			image.push_back(color);
			depth_map.push_back(depth);
			

			
		}
	}
	vector<vector<vector3>> result(3);
	result.push_back(image);
	result.push_back(visible_map);
	result.push_back(depth_map);

	return result;

}