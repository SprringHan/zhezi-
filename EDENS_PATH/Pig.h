#pragma once
#include "Charactor.h"
extern Atlas atlas_pig_facing_left;
extern int score;
class Pig:public Charactor
{
public:
	Pig(int l, int r):Charactor(){
		width = 90;
		height = 90;
		pig_damage = 50;
		prepareing_attact.set_interval(1000);
		prepareing_attact.set_one_shot(true);
		prepareing_attact.set_callback([&]() {
			attact();
			});
		prepareing_attact.pause();
		attact_timer.set_one_shot(true);
		attact_timer.set_interval(rand()%3000+5000);
		attact_timer.set_callback([&]() {
			can_attact = true;
			});
		now_pig.set_atlas(&atlas_pig_facing_left);
		now_pig.set_loop(true);
		now_pig.set_interval(45);
		move_timer.set_one_shot(false);
		move_timer.set_interval(750);
		move_timer.set_callback([&]() {
			switch (randint(1, 4)) {
			case 1:
				move('l', 4, 7);
				break;
			case 2:
				move('r', 4, 7);
				break;
			case 3:
				move('u', 4, 7);
				break;
			case 4:
				move('d', 4, 7);
				break;
			}
			});
		set_health(100);
		max_health = health;
		now_block = { l,r };
		into_block();
	};
	~Pig() {};
	void on_update(int delta) {
		attact_timer.on_update(delta);
		now_pig.on_update(delta);
		move_timer.on_update(delta);
		moving_timer.on_update(delta);
		hurt_shelter.on_update(delta);
		prepareing_attact.on_update(delta);
		if (can_be_hurt && pos->get_zhezi_damage() > 0) {
			hurt(pos->get_zhezi_damage());
		}
		if (can_attact) {
			prepare_attact();
		}
	};
	void prepare_attact() {
		can_attact = false;
		now_block.x -= 4;
		into_block();
		prepareing_attact.resume();
		attact_timer.restart();
		now_pig.pause();
		pos->on_prepare();
		move_timer.pause();
		is_moving = true;
		moving_timer.restart();
		moving_timer.set_interval(600);
		prepareing_attact.restart();
	}
	void attact() {
		pos->off_prepare();
		if (now_block.x == 0) {
			for (int i = 0; i < 4; i++) {
				blocks[i][now_block.y].on_attact(pig_damage, false);
				blocks[i][now_block.y].breaked(3000);
			}
		}
		else {
			if (now_block.y > 0) blocks[now_block.x-1][now_block.y - 1].on_attact(pig_damage, false);
			if (now_block.y < 4) blocks[now_block.x-1][now_block.y + 1].on_attact(pig_damage, false);
			blocks[now_block.x-1][now_block.y].on_attact(pig_damage, false);
		}
		pos->on_attact(pig_damage, false);
		now_pig.resume();
		move_timer.resume();
		moving_timer.set_interval(200);
		is_moving = true;
		moving_timer.restart();
		attact_place = pos;
		now_block.x += 4;
		into_block();
	}
	bool is_die() {
		return died;
	}
	void hurt(int damage) {
		if (can_be_hurt) {
			health -= damage;
		}
		can_be_hurt = false;
		hurt_shelter.restart();
		pos->break_bullet();
		if (health <= 0) {
			die();
		}
	}
	void die() {
		score += 10;
		pos->off_attact(pig_damage, false);
		pos->off_prepare();
		pos->leave();
		died = true;
	}
	void on_draw(Camera camera) {
		int pos_y = pos->get_start_point().x + pos->get_width() / 2 - width / 2;
		int pos_x = pos->get_start_point().y + pos->get_height() / 2 - height / 2;
		int last_pos_x, last_pos_y;
		int m_pos_x, m_pos_y;
		if (!is_moving) {
			now_pig.draw(pos_x, pos_y);
		}
		else {
			last_pos_y = last_pos->get_start_point().x + last_pos->get_width() / 2 - width / 2;
			last_pos_x = last_pos->get_start_point().y + last_pos->get_height() / 2 - height / 2;
			m_pos_x = last_pos_x + (pos_x - last_pos_x) * moving_timer.get_rest_part();
			m_pos_y = last_pos_y + (pos_y - last_pos_y) * moving_timer.get_rest_part();
			now_pig.draw(m_pos_x, m_pos_y);
		}
		TCHAR buffer[30];
		_stprintf_s(buffer, L"HP:%d", health);
		LPCTSTR HP_SHOW = buffer;
		int health_width = textwidth(HP_SHOW);
		int health_height = textheight(HP_SHOW);
		int health_x, health_y;
		if (!is_moving) {
			health_x = pos_x + (width - health_width) / 2;
			health_y = pos_y + height - health_height / 2;
		}
		else {
			health_x = m_pos_x + (width - health_width) / 2;
			health_y = m_pos_y + height - health_height / 2;
		}
		
		setbkmode(0);
		settextstyle(20, 0, L"IPix");
		settextcolor(RED);
		outtextxy(health_x, health_y, HP_SHOW);
		
	}
private:
	Timer move_timer;
	Timer attact_timer;
	Timer prepareing_attact;
	int pig_damage;
	Animation now_pig;
	Block* attact_place;
	bool can_attact = false;
	bool is_attacting = false;
};

