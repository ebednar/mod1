#include "water.h"
#include "Shader.h"
#include "glad.h"
#include <iostream>

Water::~Water()
{
	delete[] water_map;
	delete[] vertices;
}

void	Water::init(Landscape *land)
{
	this->land = land;
	map_size = land->map_size;
	water_map = new water_point[map_size * map_size];
	for (int i = 0; i < map_size * map_size; ++i)
	{
		water_map[i].x = land->map[i].x;
		water_map[i].z = land->map[i].z;
	}
}

void	Water::vertex_buffer()
{
	vertices = new float[(map_size - 1) * (map_size - 1) * 3 * 2 * 3];
	int k = 0;
	for (int y = 0; y < map_size - 1; ++y)
	{
		for (int x = 0; x < map_size - 1; ++x)
		{

			vertices[k + 0] = water_map[y * map_size + x].x;
			vertices[k + 1] = water_map[y * map_size + x].level;
			vertices[k + 2] = water_map[y * map_size + x].z;
			vertices[k + 3] = water_map[y * map_size + x + 1].x;
			vertices[k + 4] = water_map[y * map_size + x + 1].level;
			vertices[k + 5] = water_map[y * map_size + x + 1].z;
			vertices[k + 6] = water_map[(y + 1) * map_size + x + 1].x;
			vertices[k + 7] = water_map[(y ) * map_size + x ].level;
			vertices[k + 8] = water_map[(y + 1) * map_size + x + 1].z;
			vertices[k + 9] = water_map[y * map_size + x].x;
			vertices[k + 10] = water_map[y * map_size + x].level;
			vertices[k + 11] = water_map[y * map_size + x].z;
			vertices[k + 12] = water_map[(y + 1) * map_size + x].x;
			vertices[k + 13] = water_map[(y ) * map_size + x].level;
			vertices[k + 14] = water_map[(y + 1) * map_size + x].z;
			vertices[k + 15] = water_map[(y + 1) * map_size + x + 1].x;
			vertices[k + 16] = water_map[(y ) * map_size + x ].level;
			vertices[k + 17] = water_map[(y + 1) * map_size + x + 1].z;
			k += 18;
		}
	}
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, (map_size - 1) * (map_size - 1) * 3 * 2 * 3 * sizeof(float), vertices, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void	Water::set_shader(const char* vPath, const char* fSPath)
{
	create_shader(&shader_id, vPath, fSPath);
}

void	Water::raise()
{
	for (int y = 0; y < map_size; ++y)
	{
		for (int x = 0; x < map_size; ++x)
		{
			if (x == 0 /*|| x == 1 || y == 1*/ ||  y == 0 || x == map_size - 2 || y == map_size - 2)
				water_map[y * map_size + x].level += step;
		}
	}
	//std::cout << "water level" << water_map[0].level << std::endl;
}

void	Water::flow()
{
	for (int y = 0; y < map_size; ++y)
	{
		for (int x = 0; x < map_size; ++x)
		{
			if (x < map_size - 1 && water_map[y * map_size + x + 1].level < water_map[y * map_size + x].level - step
				&& water_map[y * map_size + x].level > land->map[y * map_size + x + 1].y)
			{
				water_map[y * map_size + x].level -= step;
				water_map[y * map_size + x + 1].level += step;
			}
			if (x > 0 && water_map[y * map_size + x - 1].level < water_map[y * map_size + x].level - step
				&& water_map[y * map_size + x].level > land->map[y * map_size + x - 1].y)
			{
				water_map[y * map_size + x].level -= step;
				water_map[y * map_size + x - 1].level += step;
			}
			if (y < map_size - 1 && water_map[(y + 1) * map_size + x].level < water_map[y * map_size + x].level - step
				&& water_map[y * map_size + x].level > land->map[(y + 1) * map_size + x].y)
			{
				water_map[y * map_size + x].level -= step;
				water_map[(y + 1) * map_size + x].level += step;
			}
			if (y > 0 && water_map[(y - 1) * map_size + x].level < water_map[y * map_size + x].level - step
				&& water_map[y * map_size + x].level > land->map[(y - 1) * map_size + x].y)
			{
				water_map[y * map_size + x].level -= step;
				water_map[(y - 1) * map_size + x].level += step;
			}
		}
	}
}
