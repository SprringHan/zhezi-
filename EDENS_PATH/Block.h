#pragma once
#include "Timer.h"
#include "util.h"
#include "Camera.h"
#include<easyx.h>
class Block
{
public:
	Block() {
		breaking.set_one_shot(true);
		breaking.set_callback([&]() {
			be_breaked = false;
			});
		off_attact_timer.set_one_shot(true);
		off_attact_timer.set_interval(200);
		off_attact_timer.set_callback([&]() {
			enemy_damage = 0;
			//cout << 111111 << endl;
			});
	};
	~Block() {};
	void breaked(int during) {
		be_breaked = true;
		breaking.set_interval(during);
		breaking.restart();
	}
	void occupy() {
		be_occupied = true;
	}
	void leave() {
		be_occupied = false;
	}
	bool free() {
		return !be_occupied && !be_breaked;
	}
	void on_prepare() {
		prepare_attact = true;
	}
	void off_prepare() {
		prepare_attact = false;
	}
	void on_attact(int damage,bool is_zhezi) {
		if (is_zhezi) zhezi_damage = damage;
		else { enemy_damage = damage; off_attact_timer.restart();};
	}
	void off_attact(int damage,bool is_zhezi) {
		if (is_zhezi) zhezi_damage = max(zhezi_damage - damage, 0);
		else enemy_damage = max(enemy_damage - damage, 0);
	}
	void set_size(int l, int u, int r, int d) {
		left = l;
		up = u;
		right = r;
		down = d;
	}
	void on_update(int delta) {
		breaking.on_update(delta);
		off_attact_timer.on_update(delta);
		if (enemy_damage == 0) be_attacted = false;
		else be_attacted=true;
	}
	void set_color(COLORREF color) {
		this->color = color;
	}
	int get_zhezi_damage() {
		return zhezi_damage;
	}
	POINT get_start_point() {
		return POINT{ up, left };
	}
	int get_height() {
		return down - up;
	}
	int get_width() {
		return right - left;
	}
	void break_bullet() {
		bullet_be_break = true;
	}
	void return_bullet() {
		bullet_be_break = false;
	}
	bool bullet_status() {
		return bullet_be_break;
	}
	bool is_break() {
		return be_breaked;
	}
	int is_attact() {
		return enemy_damage;
	}
	void on_draw(Camera camera) {
		setlinecolor(WHITE);
		if (be_attacted) {
			setfillcolor(RGB(175,175,175));
			fillrectangle(left - camera.pos.x, up - camera.pos.x, right - camera.pos.x, down - camera.pos.y);
		}
		else if(prepare_attact){
			setfillcolor(RGB(220, 220, 220));
			fillrectangle(left - camera.pos.x, up - camera.pos.x, right - camera.pos.x, down - camera.pos.y);
		}else{
			setfillcolor(color);
			fillrectangle(left - camera.pos.x, up - camera.pos.x, right - camera.pos.x, down - camera.pos.y);
		}
		if (be_breaked) {
			line(left, up, right, down);
			line(right, up, left, down);
		}
		rectangle(left - camera.pos.x, up - camera.pos.y, right - camera.pos.x, down - camera.pos.y);
	}
private:
	Timer breaking;
	Timer off_attact_timer;
	bool prepare_attact=false;
	bool be_breaked=false;
	bool be_attacted = false;
	bool be_occupied = false;
	bool bullet_be_break;
	int zhezi_damage=0;
	int enemy_damage=0;
	int left, up, down, right;
	COLORREF color;

};

