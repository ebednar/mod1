#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "render.h"
#include "events.h"

class Engine {
public:
	Camera						cam;
	Animator 					animator;
	Scene						scene;
	Controls					controls;
	Skybox						skybox;
	Landscape					landscape;
	Water						water;
	Rain						rain;
	Entity						*player;
	std::vector<Model *>		models;
	bool						free_cam;
	bool						close_eng;
	static double				delta_time;
public:
			~Engine();
	void	init_engine(int width, int height);
	void	run_engine();
	void	add_model(Model *mod);
	void	add_entity(Entity *ent);
	void	set_player(Entity *ent);
	void	add_light_source(glm::vec3 l_pos, glm::vec3 color);
private:
	GLFWwindow				*window;
	Render					rend;
	double					old_time = 0.0;
	double					timer = 0.0;
	int						fps = 0;
};
