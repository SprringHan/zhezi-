#pragma once
#include "Scene.h"
extern IMAGE image_upgrade_background;
extern IMAGE image_died_sign;
extern int score;
class UpgradeScene:public Scene
{
public:
	UpgradeScene() {};
	~UpgradeScene() {};
	void on_enter() {};
	void on_exit() {};
	void on_update(int delta) {};
	void on_input(const ExMessage& msg) {
		if (msg.message == WM_KEYUP) {
			exit(0);
		}
	};
	void on_draw(Camera camera) {
		putimagealpha(0, 0, &image_upgrade_background);
		putimagealpha(150, 300, &image_died_sign);
		settextstyle(60, 0, L"IPix");
		TCHAR str[200];
		_stprintf_s(str, L"×îÖÕµÃ·Ö£º%d", score);
		outtextxy(350, 250, str);
	};
};

