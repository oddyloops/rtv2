#include "material.h"

using namespace RTv2::objects;

material::material()
{

}

void material::set_ambient_color(texture_map<vector3> ambient_color)
{
	_ambient_color = ambient_color;
}

void material::set_diffuse_color(texture_map<vector3> diffuse_color)
{
	_diffuse_color = diffuse_color;
}

void material::set_specular_color(texture_map<vector3> specular_color)
{
	_specular_color = specular_color;
}

void material::set_specularity(texture_map<float> specularity)
{
	_specularity = specularity;
}

void material::set_refractive_index(texture_map<float> refractive_index)
{
	_refractive_index = refractive_index;
}

void material::set_reflectivity(texture_map<float> reflectivity)
{
	_reflectivity = reflectivity;
}

void material::set_transparency(texture_map<float> transparency)
{
	_transparency = transparency;
}

bool material::get_is_specular()
{
	return !_specularity.get_is_null();
}

bool material::get_is_reflective()
{
	return !_reflectivity.get_is_null();
}

bool material::get_is_refractive()
{
	return !_refractive_index.get_is_null();
}

vector3 material::get_ambient_color(intersection& intersect, std::vector<texture<vector3, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>>& db_texture)
{
	return _ambient_color.get_texel(intersect, db_texture);
}

vector3 material::get_diffuse_color(intersection& intersect, std::vector<texture<vector3, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>>& db_texture)
{
	return _diffuse_color.get_texel(intersect, db_texture);
}


vector3 material::get_specular_color(intersection& intersect, std::vector<texture<vector3, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>>& db_texture)
{
	return _specular_color.get_texel(intersect, db_texture);
}

float material::get_specularity(intersection& intersect, std::vector<texture<float, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>>& db_texture)
{
	return _specularity.get_texel(intersect, db_texture);
}

float material::get_refractive_index(intersection& intersect, std::vector<texture<float, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>>& db_texture)
{
	return _refractive_index.get_texel(intersect, db_texture);
}

float material::get_reflectivity(intersection& intersect, std::vector<texture<float, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>>& db_texture)
{
	return _reflectivity.get_texel(intersect, db_texture);
}

float material::get_transparency(intersection& intersect, std::vector<texture<float, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>>& db_texture)
{
	return _transparency.get_texel(intersect, db_texture);
}