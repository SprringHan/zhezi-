#pragma once
#include "Scene.h"
extern Scene* menu_scene;
extern Scene* game_scene;
extern Scene* upgrade_scene;
class SceneManager
{
public:
	enum class SceneType{
		Menu,
		Game,
		Upgrade
	};
public:
	SceneManager() {};
	~SceneManager() {};
	void set_current_scene(Scene* scene) {
		current_scene = scene;
	}
	void switch_to(SceneType scenetype) {
		current_scene->on_exit();
		switch (scenetype) {
		case SceneType::Game:
			current_scene = game_scene;
			break;
		case SceneType::Menu:
			current_scene = menu_scene;
			break;
		case SceneType::Upgrade:
			current_scene = upgrade_scene;
			break;
		}
		current_scene->on_enter();
	};
	void on_exit() {
		current_scene->on_exit();
	}
	void on_enter() {
		current_scene->on_enter();
	}
	void on_draw(Camera camera) {
		current_scene->on_draw(camera);
	}
	void on_update(int delta) {
		current_scene->on_update(delta);
	}
	void on_input(const ExMessage& msg) {
		current_scene->on_input(msg);
	}
private:
	Scene* current_scene;
};

