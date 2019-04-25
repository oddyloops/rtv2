#ifndef SHADER_H
#define SHADER_H

#include "vector3.h"
#include "intersection.h"

namespace RTv2
{
	namespace renderer
	{
		class shader
		{
			static void shade(intersection& intersect, vector3& color, vector3& visible_map, vector3& depth_map);
		};
	}
}

#endif