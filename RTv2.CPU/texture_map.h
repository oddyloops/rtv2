#ifndef TEXTURE_MAP_H
#define TEXTURE_MAP_H
#include <vector>
#include <math.h>
#include "typedefs.h"
#include "map_codes.h"
#include "vector2.h"
#include "texel.h"
#include "texture.h"
#include "texture_projector.h"
#include "math_util.h"
#include "constants.h"
#include "ray.h"


template<typename T>
struct texture_map
{
private:
	bool _is_mapped; //a flag for determining if texture mapping is enabled for this value
	bool _is_null;
	

	bool _is_projection; //used for projection texture mapping
	vector3 _projection_orig; //origin of texture projection
	texture_projector _projector; //texture projector


	byte _map_code; //texture map type, (check map_codes.h for details)

	texel _texels[2]; //texel array for two different colors for wavy and checkered maps (only use the first element for plain)

	int _check_x_dim; //for checkered maps (how many checkered rows)
	int _check_y_dim; //for checkered maps (how many checkered columns)

	vector2 _wave_direction; //direction of texture wave for wavy map code

	bool _texel_cached = false;
	T _cached_texel; //used for caching texel values for maps that contain only one texel to avoid re-calculation

public:

	texture_map();

	texture_map(byte map_code);

	texture_map(T unmapped_texel);

	//for projection texture maps
	texture_map( vector3 projection_orig, vector3 projection_at, vector3 projection_up, float projection_focus, float projection_fov, float projection_aspect_ratio);

	void set_check_dims(int check_x, int check_y);

	void set_wave_direction(vector2 wave_direction);

	void set_single_texel(texel texel);

	void set_two_texels(texel texel1, texel texel2); //for wavy and checkered texels

	bool get_is_mapped() const;

	T get_texel(intersection& intersect, std::vector<texture<T, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>>& db_texture);

	bool get_is_null() const;
};




template<typename T>
texture_map<T>::texture_map() : _is_null(true)
{

}

template<typename T>
texture_map<T>::texture_map(T unmapped_texel) : _is_null(false), _is_mapped(false), _cached_texel(unmapped_texel), _texel_cached(true)
{

}

template<typename T>
texture_map<T>::texture_map(byte map_code) : _map_code(map_code), _is_null(false), _is_projection(false), _is_mapped(true)
{

}

template<typename T>
bool texture_map<T>::get_is_null() const
{
	return _is_null;
}

template<typename T>
texture_map<T>::texture_map( vector3 projection_orig, vector3 projection_at, vector3 projection_up, float projection_focus, float projection_fov, float projection_aspect_ratio)
	: _projection_orig(projection_orig), _is_null(false), _is_projection(true), _is_mapped(true)
{
	//convert fov to radians
	projection_fov /= PI;
	_map_code = map_codes::plain; //always plain for projection texture mapping
	projection_up = math_util::normalize(projection_up);
	vector3 projection_dir = math_util::normalize(projection_at - _projection_orig);
	vector3 projection_side = math_util::cross(projection_dir, projection_up);
	projection_up = math_util::cross(projection_side, projection_dir);

	float projection_height = 2 * tanf(0.5f * projection_fov) * projection_focus;
	float projection_width = projection_aspect_ratio * projection_height;

	//bottom left
	vector3 projector_origin = (_projection_orig + projection_focus * projection_dir) - (0.5f * projection_width * projection_side) - (0.5f * projection_height * projection_up);
	vector3 vertices[4];
	vertices[0] = projection_orig;
	vertices[1] = projection_orig + projection_height * projection_up;
	vertices[2] = vertices[1] + projection_width * projection_side;
	vertices[3] = vertices[2] - projection_height * projection_up;
	_projector = texture_projector(vertices);

}

template<typename T>
void texture_map<T>::set_check_dims(int check_x, int check_y)
{
	_check_x_dim = check_x;
	_check_y_dim = check_y;
}

template<typename T>
void texture_map<T>::set_wave_direction(vector2 wave_direction)
{
	_wave_direction = math_util::normalize(wave_direction);
}

template<typename T>
void texture_map<T>::set_single_texel(texel texel)
{
	_texels[0] = texel;

}

template<typename T>
void texture_map<T>::set_two_texels(texel texel1, texel texel2)
{
	_texels[0] = texel1;
	_texels[1] = texel2;
}




template<typename T>
T texture_map<T>::get_texel(intersection& intersect, std::vector<texture<T, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>>& db_texture)
{
	if (!_is_mapped)
	{
		return _cached_texel;
	}

	int x_index = -1;
	int y_index = -1;
	int texel_index = 0;
	if (_map_code == map_codes::plain && _texels[0]._map_width == 1 && _texels[0]._map_height == 1)
	{
		//should be cached
		if (!_texel_cached)
		{
			_cached_texel = db_texture[_texels[0]._map_index].get_texel(_texels[0]._map_x_offset, _texels[0]._map_y_offset);
			_texel_cached = true;
		}
		return _cached_texel;
	}
	else if(_is_projection) //projection texture map
	{
		ray r = ray::create_from_origin_and_at(intersect._point, _projection_orig);
		intersection project_int;
		if (_projector.intersect(r, project_int))
		{
			x_index = (int)(1 - project_int._u *_texels[texel_index]._map_height); //1 - to switch origin to top left for texture mapping
			y_index = (int)(project_int._v *_texels[texel_index]._map_width);
		}
	}
	else
	{
		//uv- projection
		
		float u = 1 - intersect._u; //1 - to switch origin to top left for texture mapping
		float v = intersect._v;
		if (_map_code == map_codes::plain)
		{
			x_index = (int)( u *_texels[texel_index]._map_height);
			y_index = (int)(v *_texels[texel_index]._map_width);
		}
		else if (_map_code == map_codes::checkered)
		{
			bool x_even = (((int)(u * _check_x_dim)) & 1) == 0;
			bool y_even = (((int)(v * _check_y_dim)) & 1) == 0;

			if (x_even)
			{
				texel_index = (y_even) ? 0 : 1;
			}
			else
			{
				texel_index = (y_even) ? 1 : 0;
			}

			x_index = (int)(u *_texels[texel_index]._map_height);
			y_index = (int)(v *_texels[texel_index]._map_width);
		}
		else
		{
			//wavy
			vector2 uv_vec;
			uv_vec.x = intersect._u; //bottom-left origin for projection of uv-vector
			uv_vec.y = v;
			//project normalized uv vec onto wave direction to get gradient section which is between 0 and 1
			float grad_sec = math_util::dot(math_util::normalize(uv_vec), _wave_direction);

			x_index = (int)(u *_texels[0]._map_height);
			y_index = (int)(v *_texels[1]._map_width);

			T tx1 = db_texture[_texels[0]._map_index].get_texel(_texels[0]._map_x_offset
				+ x_index, _texels[0]._map_y_offset + y_index);

			x_index = (int)(u *_texels[1]._map_height);
			y_index = (int)(v *_texels[1]._map_width);

			T tx2 = db_texture[_texels[1]._map_index].get_texel(_texels[1]._map_x_offset
				+ x_index, _texels[1]._map_y_offset + y_index);

			return (grad_sec * tx1) + ((1 - grad_sec) * tx2);
			
		}

		if (_map_code != map_codes::wavy)
		{
			//return texel for checkered and plain
			return db_texture[_texels[texel_index]._map_index].get_texel(_texels[texel_index]._map_x_offset
				+ x_index, _texels[texel_index]._map_y_offset + y_index);
		}

	}
	
}

template<typename T>
bool texture_map<T>::get_is_mapped() const
{
	return _is_mapped;
}
#endif