#ifndef DATABASE_H
#define DATABASE_H
#include <vector>
#include "vector3.h"
#include "geometry.h"
#include "material.h"
#include "light.h"
#include "texture.h"
#include "constants.h"

using namespace std;
using namespace RTv2::objects;

bool _enable_soft_shadow = true; 

vector<geometry> _db_geometries;
vector<material> _db_materials;
vector<light> _lights;

vector<texture<vector3,MAX_TEXTURE_HEIGHT,MAX_TEXTURE_WIDTH>> _db_vector_textures;
vector<texture<float, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>> _db_scalar_textures;






#endif