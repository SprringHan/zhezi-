#pragma once
#include "Block.h"
#include <easyx.h>
#include "util.h"
#include "Animation.h"
extern Block blocks[10][10];
extern Camera camera;
class Charactor
{
public:
public:
	Charactor() {
		hurt_shelter.set_interval(300);
		hurt_shelter.set_one_shot(true);
		hurt_shelter.set_callback([&]() {
			can_be_hurt = true;
			});
		moving_timer.set_interval(200);
		moving_timer.set_one_shot(true);
		moving_timer.set_callback([&]() {
			is_moving = false;
			});
	};
	~Charactor() {};
	void into_block() {
		last_pos = pos;
		pos = &blocks[now_block.x][now_block.y];
		if(last_pos!=nullptr)
			last_pos->leave();
		pos->occupy();
		//cout << pos->get_width() << " " << pos->get_height() << endl;
	}
	void set_block(int i,int j) {
		now_block = { i,j };
		cout << "NO" << endl;
		into_block();
	}
	void set_health(int health) {
		this->health = health;
	}
	virtual void on_update() {};
	void move(char dir,int l,int r) {
		bool begin_moving = false;
		switch (dir) {
		case 'l':
			if (now_block.x > l && blocks[now_block.x - 1][now_block.y].free()) now_block.x--, begin_moving = true;
			break;
		case 'r':
			if (now_block.x < r&& blocks[now_block.x + 1][now_block.y].free()) now_block.x++, begin_moving = true;
			break;
		case 'u':
			if (now_block.y > 0 && blocks[now_block.x][now_block.y - 1].free()) now_block.y--, begin_moving = true;
			break;
		case 'd':
			if (now_block.y < 3 && blocks[now_block.x][now_block.y + 1].free()) now_block.y++, begin_moving = true;
			break;
		}
		if (begin_moving) {
			into_block();
			is_moving = true;
			moving_timer.restart();
		}
	}
protected:
	Block* last_pos=nullptr;
	Block* pos=nullptr;
	POINT now_block;
	Timer moving_timer;
	Timer hurt_shelter;
	bool is_moving=false;
	bool died = false;
	bool can_be_hurt=true;
	int health;
	int max_health;
	int width, height;
};

