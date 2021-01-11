#pragma once
#include "scene.h"
#include "camera.h"
#include "skybox.h"
#include "Animator.h"
#include "landscape.h"
#include "water.h"

class Render
{
public:
	Entity *player;
public:
	void	init();
	void	draw_scene(Animator * animator, Scene* scene, Camera* cam);
	void	draw_skybox(Skybox *skybox, Camera* cam);
	void	draw_landscape(Scene* scene, Landscape* landscape, Camera *cam);
	void	draw_water(Water* water, Camera *cam);
	std::string	animation_key;
private:
	mat4	projection;
	glm::mat4	ortProjection;

};
