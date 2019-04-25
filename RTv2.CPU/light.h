#ifndef LIGHT_H
#define LIGHT_H
#include <vector>

#include "geometry.h"
#include "typedefs.h"
#include "vector3.h"
#include "intersection.h"

using namespace std;

namespace RTv2
{
	namespace objects
	{
		class light
		{
		private:
			byte _light_code;

			bool _has_range; //a flag to determine if light's range and drop-off will be used

			vector3 _color;
			vector3 _origin; //for point and spot light
			vector3 _direction; //for directional and spot light
			
			//does not apply to directional light since it has no orign
			float _max_range; //maximum distance light travels
			float _drop_off_fract; //fraction of the range in which light intensity fades out

			//spot light
			float _central_fov;
			float _outer_fov;
			float _drop_off_const;




		public:

			light();

			light(byte light_code);

			light(byte light_code, float max_range, float drop_off_fract);

			void set_color(vector3 color);

			void set_origin(vector3 origin);

			void set_direction(vector3 direction);

			void set_central_fov(float fov);

			void set_outer_fov(float fov);

			void set_drop_off_const(float dro_off);

			vector3 get_color() const;

			vector3 get_origin() const;

			vector3 get_direction() const;

			float get_central_fov() const;

			float get_outer_fov() const;

			float get_drop_off_const() const;

			vector3 get_color(const intersection& intersect,vector<geometry>& db_geometries) const;


		};
	}
}
#endif