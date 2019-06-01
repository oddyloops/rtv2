// RTv2.Playground.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>

#include "../RTv2.CPU/entry.h"


using namespace RTv2::renderer;

void rt_cpu_tester()
{
	/* textures */
	//vector textures
	vector<texture<vector3, 1080, 1920>> vec_textures;
	texture<vector3, 1080, 1920> vec_tex1;
	vec_tex1.set_texel(0, 0, vector3(0.5, 0.5, 1));
	vec_tex1.set_texel(0, 1, vector3(1, 0.5, 0.5));
	vec_tex1.set_texel(1, 0, vector3(0.5, 1, 0.5));
	vec_tex1.set_texel(1, 1, vector3(1, 1, 1));
	vec_textures.push_back(vec_tex1);
	//scalar textures
	vector<texture<float, 1080, 1920>> scalar_textures;


	/*materials*/
	vector<material> materials;
	//diffuse
	material mat1;
	mat1.set_ambient_color(texture_map<vector3>(vector3(0.1, 0.1, 0.1)));
	texture_map<vector3> diffuse_color = texture_map<vector3>(map_codes::plain);
	diffuse_color.set_single_texel(texel(0, 0, 0, 1, 1));
	mat1.set_diffuse_color(diffuse_color);
	mat1.set_index(0);
	materials.push_back(mat1);


	/*geometries*/
	vector<geometry> geometries;
	//rectangles
	geometry rect1 = geometry(geom_codes::rectangle);
	vector3 vertices[] = { vector3(-0.5,-0.5,-0.5),vector3(0.5,0.5,-0.5),vector3(0.5,0.5,0.5),vector3(-0.5,-0.5,0.5) };
	rect1.set_vertices(vertices);
	rect1.set_index(0);
	rect1.set_material_index(0);
	geometries.push_back(rect1);

	/*meshes*/
	vector<mesh> meshes;

	/*lights*/
	vector<light> lights;
	//directional light
	light dir1 = light(light_code::directional);
	dir1.set_color(vector3(1, 1, 1));
	dir1.set_direction(vector3(1, -1, 0));
	lights.push_back(dir1);

	/*camera*/
	camera cam = camera(vector3(-5, 5, 5), vector3(0, 0, 0), vector3(0, 1, 0), 35, 2, 1920, 1080, false);

	//run
	auto results = entry::render(geometries, meshes, lights, materials, 1, cam, vector3(0, 0, 0), vec_textures, scalar_textures, true);

	
}


int main()
{
	

	



}

