#include "visibility.h"
#include "database.h"


using namespace RTv2::renderer;

bool visibility::is_visible(ray r, intersection& intersect, int except_index)
{
	bool visible = false;
	for (geometry geom : _db_geometries)
	{
		visible |= geom.intersects(r, intersect, except_index);
	}
	return visible;
}