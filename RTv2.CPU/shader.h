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
		private:
			static vector3 shade_helper(intersection intersect);
		public:
			static void shade(intersection& intersect, vector3& color,  vector3& depth_map);
		};
	}
}

#endif