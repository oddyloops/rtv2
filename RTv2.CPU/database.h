#ifndef DATABASE_H
#define DATABASE_H
#include <vector>
#include "vector3.h"
#include "geometry.h"
#include "material.h"
#include "light.h"
#include "camera.h"
#include "texture.h"
#include "constants.h"

using namespace std;
using namespace RTv2::objects;

extern bool _enable_soft_shadow; 

extern camera _db_camera;

extern vector<geometry> _db_geometries;
extern vector<material> _db_materials;
extern vector<light> _db_lights;

extern vector<texture<vector3,MAX_TEXTURE_HEIGHT,MAX_TEXTURE_WIDTH>> _db_vector_textures;
extern vector<texture<float, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>> _db_scalar_textures;






#endif