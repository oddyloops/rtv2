#include "database.h"

bool _enable_soft_shadow = true;

camera _db_camera;

vector<geometry> _db_geometries;
vector<material> _db_materials;
vector<light> _db_lights;

vector<texture<vector3, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>> _db_vector_textures;
vector<texture<float, MAX_TEXTURE_HEIGHT, MAX_TEXTURE_WIDTH>> _db_scalar_textures;