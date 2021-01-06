#include "sandbox.h"
#include <fstream>
#include <iostream>
#include <vector>


void Sandbox::place_ent(Engine* eng)
{
	eng->landscape.load_map("map.mod1");
	eng->landscape.build_heights();
	eng->landscape.vertex_buffer();
	eng->landscape.set_shader("res/shaders/land_vertex.glsl", "res/shaders/land_fragment.glsl");
	eng->water.init(&eng->landscape);
	eng->water.vertex_buffer();
	eng->water.set_shader("res/shaders/water_vertex.glsl", "res/shaders/water_fragment.glsl");
}
