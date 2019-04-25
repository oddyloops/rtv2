#ifndef MATERIAL_H
#define MATERIAL_H

#include <vector>
#include "indexable.h"
#include "vector3.h"
#include "texture.h"
#include "texture_map.h"
#include "intersection.h"
#include "constants.h"


namespace RTv2
{
	namespace objects
	{

		class material : public indexable
		{
		private:
			texture_map<vector3> _ambient_color;
			texture_map<vector3> _diffuse_color;
			texture_map<vector3> _specular_color;
			texture_map<float> _specularity;
			texture_map<float> _refractive_index;
			texture_map<float> _reflectivity;
			texture_map<float> _transparency;

		public:
			material();

			void set_ambient_color(texture_map<vector3> ambient_color);

			void set_diffuse_color(texture_map<vector3> diffuse_color);

			void set_specular_color(texture_map<vector3> specular_color);

			void set_specularity(texture_map<float> specularity);

			void set_refractive_index(texture_map<float> refractive_index);

			void set_reflectivity(texture_map<float> reflectivity);

			void set_transparency(texture_map<float> transparency);

			vector3 get_ambient_color(intersection& intersect, std::vector<texture<vector3,MAX_TEXTURE_HEIGHT,MAX_TEXTURE_WIDTH>>& db_texture);

			vector3 get_diffuse_color(intersection& intersect, std::vector<texture<vector3, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>>& db_texturee);

			vector3 get_specular_color(intersection& intersect, std::vector<texture<vector3, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>>& db_texture);

			float get_specularity(intersection& intersect, std::vector<texture<float, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>>& db_texture);

			float get_refractive_index(intersection& intersect, std::vector<texture<float, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>>& db_texture);

			float get_reflectivity(intersection& intersect, std::vector<texture<float, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>>& db_texture);

			float get_transparency(intersection& intersect, std::vector<texture<float, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>>& db_texture);

		};
	}
}

#endif