
#include <math.h>
#include "camera.h"
#include "math_util.h"
#include "constants.h"


using namespace RTv2::objects;

camera::camera()
{

}

camera::camera(vector3 eye, vector3 look_at, vector3 up, float field_of_view, float focus, int resX, int resY, bool is_ortho)
{
	//convert fov to radians
	field_of_view /= PI;

	_eye = eye;
	_view_dir = math_util::normalize(look_at - eye);
	_side_vec = math_util::cross(_view_dir, up);
	_up_vec = math_util::cross(_side_vec, _view_dir);
	_resX = resX;
	_resY = resY;
	_is_ortho = is_ortho;
	
	vector3 img_center = eye + focus * _view_dir;
	float img_height =2 * focus * tanf(0.5f * field_of_view);
	float img_width = ((float)_resX / _resY) * img_height;
	_img_origin = img_center + (0.5f * img_height * _up_vec) - (0.5f * img_width * _side_vec);

	_pixel_width = _resX / img_width;
	_pixel_height = _resY / img_height;
}


vector3 camera::get_eye() const
{
	return _eye;
}

vector3 camera::get_view_dir() const
{
	return _view_dir;
}

vector3 camera::get_up_vec() const
{
	return _up_vec;
}

vector3 camera::get_side_vec() const
{
	return _side_vec;
}

vector3 camera::get_img_origin() const
{
	return _img_origin;
}

int camera::get_resX() const
{
	return _resX;
}

int camera::get_resY() const
{
	return _resY;
}

float camera::get_pixel_width() const
{
	return _pixel_width;
}

float camera::get_pixel_height() const
{
	return _pixel_height;
}


bool camera::get_is_ortho() const
{
	return _is_ortho;
}