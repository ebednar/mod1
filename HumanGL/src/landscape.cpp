#include "landscape.h"
#include "Shader.h"
#include "glad.h"
#include <fstream>
#include <iostream>

Landscape::Landscape()
{
	map_size = 50;
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
				float height = displacements[i].z - dist * dist;
				if (dist == 0)
					height = displacements[i].z;
				if (map[y * map_size + x] < height)
					map[y * map_size + x] = height;
			}
		}
	}

	/*for (int x = 0; x < map_size; ++x)
	{
		for (int y = 0; y < map_size; ++y)
		{
			std::cout << map[y * map_size + x] << " ";
		}
		std::cout << "\n";
	}*/		
}

void	Landscape::vertex_buffer()
{
	float *vertices = new float[(map_size - 1) * (map_size - 1) * 3 * 2 * 3];
	int k = 0;
	for (int y = 0; y < map_size - 1; ++y)
	{
		for (int x = 0; x < map_size - 1; ++x)
		{
			vertices[k + 0] = x;
			vertices[k + 1] = map[y * map_size + x];
			vertices[k + 2] = y;
			vertices[k + 3] = x + 1;
			vertices[k + 4] = map[y * map_size + x + 1];
			vertices[k + 5] = y;
			vertices[k + 6] = x + 1;
			vertices[k + 7] = map[(y + 1) * map_size + x + 1];
			vertices[k + 8] = y + 1;
			vertices[k + 9] = x;
			vertices[k + 10] = map[y * map_size + x];
			vertices[k + 11] = y;
			vertices[k + 12] = x;
			vertices[k + 13] = map[(y + 1) * map_size + x];
			vertices[k + 14] = y + 1;
			vertices[k + 15] = x + 1;
			vertices[k + 16] = map[(y + 1) * map_size + x + 1];
			vertices[k + 17] = y + 1;
			k += 18;
		}
	}

	/*for (int i = 0; i < k; ++i)
		vertices[i] /= 5;*/

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, (map_size - 1) * (map_size - 1) * 3 * 2 * 3 * sizeof(float), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	delete[] vertices;
}

void Landscape::set_shader(const char* vPath, const char* fSPath)
{
	create_shader(&shader_id, vPath, fSPath);
}
