#include "util.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "UpgradeScene.h"
#include "Block.h"
#include "SceneManager.h"
#include "Atlas.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define BLOCK_LEFT 200
#define BLOCK_RIGHT 1100
#define BLOCK_UP 100
#define BLOCK_DOWN 550
#define BLOCK_SIZE 113
using namespace std;
int FPS=60;
Scene* menu_scene;
Scene* game_scene;
Scene* upgrade_scene;
SceneManager scenemanager;

IMAGE image_menu_background;
IMAGE image_game_background;
IMAGE image_upgrade_background;

IMAGE image_zhezi_idle;
IMAGE image_zhezi_die;
IMAGE image_died_sign;

Atlas atlas_paimon_facing_left;
Atlas atlas_pig_facing_right;
Atlas atlas_pig_facing_left;
Atlas atlas_sunflower_facing_right;
Atlas atlas_sunflower_facing_left;
Atlas atlas_peashooter_facing_right;
Atlas atlas_peashooter_facing_left;

Camera camera;
Block blocks[10][10];
vector<Bullet*> bullets;
int score = 0;

void filp_atlas(Atlas* from, Atlas* to) {
	to->clear();
	for (int i = 0; i < from->getsize(); i++) {
		IMAGE temp_img;
		filp_image(from->get_image(i), &temp_img);
		to->add_image(temp_img);
	}
}

void load_resources() {

	AddFontResourceEx(_T("resources/IPix.ttf"), FR_PRIVATE, NULL);

	atlas_paimon_facing_left.loadimages(L"./resources/paimon_left_%d.png",6);
	atlas_pig_facing_left.loadimages(L"./resources/enemy_left_%d.png", 6);
	atlas_pig_facing_right.loadimages(L"./resources/enemy_right_%d.png", 6);
	atlas_peashooter_facing_left.loadimages(L"./resources/peashooter_idle_%d.png", 9);
	filp_atlas(&atlas_peashooter_facing_right, &atlas_peashooter_facing_left);
	atlas_sunflower_facing_left.loadimages(L"./resources/sunflower_idle_%d.png", 8);
	filp_atlas(&atlas_sunflower_facing_right, &atlas_sunflower_facing_left);

	loadimage(&image_zhezi_die, L"./resources/zhezi_die.jpg");
	loadimage(&image_zhezi_idle, L"./resources/zhezi_idle.jpg");
	loadimage(&image_menu_background, L"./resources/menu_background.png");
	loadimage(&image_game_background, L"./resources/game_background.png");
	loadimage(&image_upgrade_background, L"./resources/upgrade_background.png");
	loadimage(&image_died_sign, L"./resources/died_sign.jpg");
}

int main() {
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT,EX_SHOWCONSOLE);
	load_resources();
	menu_scene = new MenuScene;
	game_scene = new GameScene;
	upgrade_scene = new UpgradeScene;
	for (int i = 0; i < 4; i ++) {
		for (int j = 0; j < 4; j ++) {
			blocks[i][j].set_size(BLOCK_LEFT + i * BLOCK_SIZE, BLOCK_UP + j * BLOCK_SIZE, BLOCK_LEFT + (i + 1) * BLOCK_SIZE, BLOCK_UP + (j + 1) * BLOCK_SIZE);
			blocks[i][j].set_color(BLACK);
		}
	}
	for (int i = 4; i < 8; i++) {
		for (int j = 0; j < 4; j++) {
			blocks[i][j].set_size(BLOCK_LEFT + i * BLOCK_SIZE, BLOCK_UP + j * BLOCK_SIZE, BLOCK_LEFT + (i + 1) * BLOCK_SIZE, BLOCK_UP + (j + 1) * BLOCK_SIZE);
			blocks[i][j].set_color(RGB(50,50,50));
		}
	}
	scenemanager.set_current_scene(menu_scene);
	scenemanager.on_enter();
	BeginBatchDraw();
	while (1) {
		DWORD start_time = GetTickCount();
		ExMessage msg;
		while (peekmessage(&msg)) {
			scenemanager.on_input(msg);
		}
		static DWORD last_run_time = GetTickCount();
		DWORD now_run_time = GetTickCount();
		DWORD delta_run_time = now_run_time - last_run_time;
		scenemanager.on_update(delta_run_time);
		last_run_time = now_run_time;
		cleardevice();
		scenemanager.on_draw(camera);
		FlushBatchDraw();
		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;
		if (delta_time <= 1000 / FPS) {
			Sleep(1000 / FPS - delta_time);
		}
	}
	EndBatchDraw();
	return 0;
}
