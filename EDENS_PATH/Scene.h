#pragma once
#include<easyx.h>
#include<vector>
#include "Animation.h"
#include "Timer.h"
#include "Camera.h"
class Scene
{
public:
	Scene() {};
	~Scene() {};
	virtual void on_exit() {};
	virtual void on_enter() {};
	virtual void on_input(const ExMessage& msg) {};
	virtual void on_update(int delta) {};
	virtual void on_draw(Camera camera) {};
};

