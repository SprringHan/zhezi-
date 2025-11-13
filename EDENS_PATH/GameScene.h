#pragma once
#include "Scene.h"
#include "Block.h"
#include "Zhezi.h"
#include "Pig.h"

extern IMAGE image_game_background;
extern Block blocks[10][10];
extern vector<Pig*> pigs;
extern vector<Bullet*> bullets;
extern int score;
class GameScene :public Scene
{
public:
	GameScene() {};
	~GameScene() {};
	void on_enter() {
		zhezi.reset();
		for (int i = 0; i < 3; i++) {
			int x = randint(4, 7);
			int y = randint(0, 3);
			while (!blocks[x][y].free()) x = randint(4, 7), y = randint(0, 3);
			pigs.push_back(new Pig(x,y));
		}
		generate_enemy.set_one_shot(false);
		generate_enemy.set_interval(generate_interval);
		generate_enemy.set_callback([&]() {
			for (int i = 0; i < 3; i++) {
				int x = randint(4, 7);
				int y = randint(0, 3);
				while (!blocks[x][y].free()) x = randint(4, 7), y = randint(0, 3);
				pigs.push_back(new Pig(x, y));
				generate_interval -= 100;
				generate_enemy.set_interval(generate_interval);
			}
			});
	};
	void on_exit() {
		for (auto p : pigs) {
			delete p;
		}
	};
	void on_update(int delta) {
		generate_enemy.on_update(delta);
		for (auto p : bullets) {
			p->on_update(delta);
		}
		for (int i = 0; i < bullets.size(); i++) {
			POINT bp = bullets[i]->get_position();
			if (bp.x < 0 || bp.x>1280 || bp.y < 0 || bp.y>720) {
				swap(bullets[i], bullets[bullets.size() - 1]);
				delete bullets[bullets.size() - 1];
				bullets.pop_back();
				continue;
			}
			if (bullets[i]->find_block()!=nullptr&&bullets[i]->find_block()->bullet_status()) {
				bullets[i]->find_block()->return_bullet();
				swap(bullets[i], bullets[bullets.size() - 1]);
				delete bullets[bullets.size() - 1];
				bullets.pop_back();
			}
		}
		zhezi.on_update(delta);
		for (auto p : pigs) {
			p->on_update(delta);
		}
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 4; j++) {
				blocks[i][j].on_update(delta);
			}
		}
		for (int i = 0; i < pigs.size(); i++) {
			if (pigs[i]->is_die()) {
				swap(pigs[i], pigs[pigs.size() - 1]);
				delete pigs[pigs.size() - 1];
				pigs.pop_back();
			}
		}
		if (zhezi.is_die()) {
			scenemanager.switch_to(SceneManager::SceneType::Upgrade);
		}
	};
	void on_input(const ExMessage& msg) {
		zhezi.on_input(msg);
	};
	void on_draw(Camera camera) {
		putimagealpha(0, 0, &image_game_background);
		TCHAR str[200];
		_stprintf_s(str, L"·ÖÊýÎª£º%d", score);
		outtextxy(10, 10, str);
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 4; j++) {
				blocks[i][j].on_draw(camera);
			}
		}
		zhezi.on_draw(camera);
		for (auto p : pigs) {
			p->on_draw(camera);
		}
		for (auto p : bullets) {
			p->on_draw(camera);
		}
	};
private:
	vector<Pig*> pigs;
	Zhezi zhezi;
	Timer generate_enemy;
	int generate_interval=10000;
};

