#ifndef TEXEL_H
#define TEXEL_H

struct  texel
{
	int _map_index = -1; //its texel buffer index
	int _map_x_offset = -1;//its texel buffer x (horizontal) offset
	int _map_y_offset = -1;//its texel buffer y (vertical) offset
	int _map_width = -1; //its texels column width
	int _map_height = -1; //its texels row height

	texel();

	texel(int map_index, int map_x_offset, int map_y_offset, int map_width, int map_height);

};
#endif