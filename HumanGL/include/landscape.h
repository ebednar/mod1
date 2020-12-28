#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <string>

class Landscape
{
public:
	std::vector<glm::vec3>	displacements;
	float					*map;
	int						map_size;
	unsigned int			vbo;
	unsigned int			vao;
	unsigned int			ibo;
	int						shader_id;
public:
	Landscape();
	~Landscape();
	void	load_map(std::string path);
	void	build_heights();
	void	vertex_buffer();
	void	set_shader(const char* vPath, const char* fSPath);
private:
};