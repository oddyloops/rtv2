#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "typedefs.h"
#include "vector2.h"
#include "vector3.h"
#include "texture_map.h"
#include "indexable.h"
#include "ray.h"
#include "intersection.h"



namespace RTv2
{
	namespace objects
	{

		class geometry : public indexable
		{
		private:

			vector3 _vertices[4]; //maximum of 3 vertices for any shape (rectangle) 

			vector3 _min;
			vector3 _max;

			texture_map<vector3> _normal; 

			vector3 _u_vec; //for rectangles
			vector3 _v_vec; //for rectangles

			vector3 _center; //for spheres, cones, and cylinders
			float _radius; //for spheres
			vector3 _vertical_axis; //for spheres, cones, and cylinders

			float _height; //for cones and cylinders
			float _flat_radius; //for cylinders

			int _material_index; //database index for material

			float _absorption_coeff; //for particle volumes

			float _scatter_coeff; //for particle volumes



		

		public:
			byte _geom_code; //geometry type

			geometry(byte geom_code);

			void set_geom_code(byte geom_code);

			void set_material_index(int index);

			void set_volume_coefficients(float absorption_coeff, float scatter_coeff);

			void set_normal(texture_map<vector3> normal);

			void set_vertices(vector3 vertices[4]);

			void set_center(vector3 center);

			void set_radius(float radius);
			
			void set_vertical_axis(vector3 vertical_axis);

			void set_flat_radius(float flat_radius);

			void set_height(float height);

			int get_material_index() const;

			float get_absorption_coefficient() const;

			float get_scatter_coefficient() const;

			vector3 get_normal_at_intersect(intersection& intersect);

			float get_radius() const;

			float get_flat_radius() const;

			float get_height() const;

			vector3 get_center() const;

			vector3 get_vertical_axis() const;

			bool intersects(ray r, intersection& intersect, int except_index);

			vector2 get_uv_at_point(vector3 _point);

			vector3 get_max() const; //for bounding box

			vector3 get_min() const; //for bounding box
		};
	}
}


#endif