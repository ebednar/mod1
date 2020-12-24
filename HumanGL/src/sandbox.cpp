#include "sandbox.h"
#include <fstream>
#include <iostream>
#include <vector>


void Sandbox::place_ent(Engine* eng)
{
	eng->landscape.load_map("map.mod1");
	eng->landscape.build_heights();
}
