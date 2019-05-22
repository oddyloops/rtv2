#ifndef ENTRY_H
#define ENTRY_H

#include <vector>
#include "vector3.h"
#include "camera.h"
#include "geometry.h"
#include "light.h"
#include "material.h"
#include "mesh.h"



using namespace std;
using namespace RTv2::objects;

namespace RTv2
{
	namespace renderer
	{

		class entry
		{
		private:
			template<typename T>
			static void copy_vector(const vector<T>& from, vector<T>& to);
		public:
			static vector<vector<vector3>> render(vector<geometry>& geometries, vector<mesh>& meshes, vector<light>& lights, vector<material>& materials, int samples_per_pix, camera cam, vector3 bg,
				vector<texture<vector3, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>>& vector_textures, vector<texture<float, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>>& scalar_textures,
				bool enable_soft_shadow);
		};
	}
}
#endif