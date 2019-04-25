#ifndef CAMERA_H
#define CAMERA_H

#include "vector3.h"

namespace RTv2
{
	namespace objects
	{

		class camera
		{
		private:
			vector3 _eye;
			vector3 _view_dir;
			vector3 _up_vec;
			vector3 _side_vec;
			vector3 _img_origin;
			int _resX;
			int _resY;


			float _pixel_width;
			float _pixel_height;
		
			
			bool _is_ortho; //orthographic projection

			

		public:

			camera();

			camera(vector3 eye, vector3 look_at, vector3 up, float field_of_view, float focus, int resX, int resY, bool is_ortho);

			vector3 get_eye() const;

			vector3 get_view_dir() const;

			vector3 get_up_vec() const;
			
			vector3 get_side_vec() const;

			vector3 get_img_origin() const;

			int get_resX() const;

			int get_resY() const;

			float get_pixel_width() const;

			float get_pixel_height() const;

			bool get_is_ortho() const;



		};
	}
}

#endif 
