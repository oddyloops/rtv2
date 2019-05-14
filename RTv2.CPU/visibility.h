#ifndef VISIBILITY_H
#define VISIBILITY_H

#include "vector3.h"
#include "ray.h"
#include "intersection.h"

namespace RTv2
{
	namespace renderer
	{

		class visibility
		{
		public:
			static bool is_visible(ray r, intersection& intersect, int except_index);
		};
	}
}

#endif