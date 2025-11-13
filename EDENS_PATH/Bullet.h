#pragma once
#include<easyx.h>
#include "Camera.h"
#include "Block.h"
extern Camera camera;
extern Block blocks[10][10];
class Bullet
{
public:
	Bullet(int x, int y, int damage, double speed, Vector2 dir,bool is_zhezi) {
		pos.x = x;
		pos.y = y;
		this->speed = speed;
		this->damage = damage;
		this->dir = dir.normalize();
		now_block = find_block();
		this->is_zhezi = is_zhezi;
	}
	~Bullet() {
		if (now_block != nullptr) {
			now_block->off_attact(damage, is_zhezi);
		}
	};
	Block* find_block() {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 4; j++) {
				POINT start_point = blocks[i][j].get_start_point();
				POINT end_point = POINT{ blocks[i][j].get_start_point().x + blocks[i][j].get_width(),blocks[i][j].get_start_point().y + blocks[i][j].get_width() };
				//cout << "start_point=" << start_point.x << " " << start_point.y << endl;
				//cout << "end_point=" << end_point.x << " " << end_point.y << endl;
				if(pos.y>=start_point.x&&pos.x>=start_point.y&&pos.y<=end_point.x&&pos.x<=end_point.y){
					return &blocks[i][j];
				}
			}
		}
		return nullptr;
	}
	POINT get_position() {
		return pos;
	}
	void on_update(int delta) {
		pos.x += dir.x * speed;
		pos.y += dir.y * speed;
		
		if (find_block() != now_block) {
			if (now_block != nullptr) {
				now_block->off_attact(damage, is_zhezi);
			}
			if (find_block() != nullptr) {
				now_block = find_block();
				now_block->on_attact(damage, is_zhezi);
			}else {
				now_block = nullptr;
			}
			
		}
		
	}
	virtual void on_draw(Camera camera) {
	};
protected:
	Block* now_block=nullptr;
	POINT pos;
	int damage;
	Vector2 dir;
	double speed;
	int is_zhezi;
};

