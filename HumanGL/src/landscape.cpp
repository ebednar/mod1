#include "landscape.h"
#include "glad.h"
#include <fstream>
#include <iostream>

Landscape::Landscape()
{
	map_size = 10;
	map = new float[map_size * map_size];
	for (int i = 0; i < map_size * map_size; ++i)
		map[i] = 0.0f;
}

Landscape::~Landscape()
{
	delete[] map;
}

void	Landscape::load_map(std::string path)
{
	std::ifstream	file;

	file.open(path);
	if (not file.is_open())
	{
		std::cout << "map file not found" << std::endl;
		return;
	}
	std::string line;
	while (std::getline(file, line))
	{
		glm::vec3 vert;
		if (sscanf(line.c_str(), "%f %f %f", &vert.x, &vert.y, &vert.z) != 3)
		{
			std::cout << "map file corrupted" << std::endl;
			return;
		}
		displacements.push_back(vert);
	}
}

void	Landscape::build_heights()
{
	int length = displacements.size();

	for (int x = 1; x < map_size - 1; ++x)
	{
		for (int y = 1; y < map_size - 1; ++y)
		{
			for (int i = 0; i < length; ++i)
			{
				float dist = (x - displacements[i].x) * (x - displacements[i].x) + (y - displacements[i].y) * (y - displacements[i].y);
				float height = displacements[i].z / (1 + dist);
				if (map[y * map_size + x] < height)
					map[y * map_size + x] = height;
			}
		}
	}

	for (int x = 0; x < map_size; ++x)
	{
		for (int y = 0; y < map_size; ++y)
		{
			std::cout << map[y * map_size + x] << " ";
		}
		std::cout << "\n";
	}
		
}

void	Landscape::vertex_buffer()
{
	float *vertices = new float[(map_size - 1) * (map_size - 1) * 3 * 2 ];


	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, 8 * ind_number * sizeof(float), vertices, GL_STATIC_DRAW);
	delete[] vertices;
}
