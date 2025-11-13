#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include<iostream>

using namespace std;
extern SceneManager scenemanager;
extern IMAGE image_menu_background;
extern IMAGE image_zhezi;
class MenuScene: public Scene
{
public:
	MenuScene() {};
	~MenuScene() {};
	void on_enter() {
	};
	void on_exit() {};
	void on_update(int delta) {
		cout << delta<<endl;
	};
	void on_input(const ExMessage& msg) {
		if (msg.message == WM_KEYUP) {
			scenemanager.switch_to(SceneManager::SceneType::Game);
		}
	};
	void on_draw(Camera camera) {
		putimagealpha(0, 0, &image_menu_background);
	};
private:
};

