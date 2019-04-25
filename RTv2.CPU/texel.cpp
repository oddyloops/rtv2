#include "texel.h"
#include "constants.h"

texel::texel()
{
	_map_index = UNINIT;
}

texel::texel(int map_index, int map_x_offset, int map_y_offset, int map_width, int map_height) : _map_index(map_index), _map_x_offset(map_x_offset),
_map_y_offset(map_y_offset), _map_width(map_width), _map_height(map_height)
{

}