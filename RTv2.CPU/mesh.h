#ifndef MESH_H
#define MESH_H

#include <vector>
#include "vector3.h"
#include "intersection.h"
#include "ray.h"
#include "indexable.h"
#include "vector2.h"

using namespace std;

namespace RTv2
{
	namespace objects
	{

		struct mesh_triangle
		{
			vector3 _vertices[3];

			bool intersects(ray r, intersection& intersect);

			vector3 get_normal();
		};


		class mesh : public indexable
		{
			vector<vector<mesh_triangle>> _octets;
			
			vector3 _min;
			vector3 _max;

			int _material_index;

			mesh();

			mesh(vector<mesh_triangle> body);

			mesh(vector<mesh_triangle> body, float transform_matrix[4][4]);

			void set_material_index(int material_index);

			int get_material_index() const;

			void get_min() const;

			void get_max() const;

			vector2 get_uv_at_point(vector3 _point);

			bool intersects(ray r, intersection& intersect, int except_index);

			vector3 get_normal_at_intersect(intersection& intersect);
		};
	}
}
#endif
