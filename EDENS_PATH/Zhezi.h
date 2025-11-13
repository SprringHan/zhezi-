#pragma once
#include "Charactor.h"
#include "Zhezi_bullet.h"
extern IMAGE image_zhezi_idle;
extern IMAGE image_zhezi_die;
extern vector<Bullet*> bullets;
class Zhezi: public Charactor
{
public:
	Zhezi() :Charactor(){
		width = 90;
		height = 90;
		can_attact = true;
		now_zhezi = &image_zhezi_idle;
		attact_interval.set_interval(750);
		attact_interval.set_one_shot(true);
		attact_interval.set_callback([&]() {
			can_attact = true;
			});
		recover_timer.set_interval(200);
		recover_timer.set_one_shot(true);
		recover_timer.set_callback([&]() {
			now_zhezi = &image_zhezi_idle;
			});
	}
	void reset() {
		set_health(1000);
		now_block = { 2,2 };
		into_block();
	}
	void attact() {
		if (can_attact) {
			int bullet_posx = pos->get_start_point().y + (pos->get_height() + height) / 2;
			int bullet_posy = pos->get_start_point().x + pos->get_width() / 2 ;
			bullets.push_back(new Zhezi_bullet(bullet_posx, bullet_posy, 25, 30, Vector2(1, 0)));
			can_attact = false;
			attact_interval.restart();
		}
	}
	void hurt(int damage) {
		if (can_be_hurt) {
			health -= damage;
		}
		can_be_hurt = false;
		now_zhezi = &image_zhezi_die;
		hurt_shelter.restart();
		recover_timer.restart();
		pos->break_bullet();
		if (health <= 0) {
			die();
		}
	}
	void die() {
		died = true;
	}
	void on_input(const ExMessage& msg) {
		if (msg.message == WM_KEYDOWN) {
			switch (msg.vkcode) {
			case 0x57:
				if (multi_move||is_moving) break;
				multi_move = true;
				move('u', 0, 3);
			case 0x41:
				if (multi_move || is_moving) break;
				multi_move = true;
				move('l', 0, 3);
				break;
			case 0x53:
				if (multi_move || is_moving) break;
				multi_move = true;
				move('d', 0, 3);
				break;
			case 0x44:
				if (multi_move || is_moving) break;
				multi_move = true;
				move('r', 0, 3);
				break;
			}
		}
		if (msg.message == WM_KEYUP) {
			multi_move = false;
		}
		if (msg.message == WM_LBUTTONUP) {
			attact();
		}
	}
	void on_update(int delta) {
		moving_timer.on_update(delta);
		attact_interval.on_update(delta);
		hurt_shelter.on_update(delta);
		recover_timer.on_update(delta);
		if (pos->is_attact()) {
			hurt(pos->is_attact());
		}
	}
	void on_draw(Camera camera) {
		int pos_y = pos->get_start_point().x + pos->get_width() / 2 - width / 2;
		int pos_x = pos->get_start_point().y + pos->get_height() / 2 - height / 2;
		int last_pos_y;
		int last_pos_x;
		int m_pos_x;
		int m_pos_y;
		if (!is_moving) {
			putimagealpha(pos_x, pos_y, now_zhezi);
		}
		else {
			last_pos_y = last_pos->get_start_point().x + last_pos->get_width() / 2 - width / 2;
			last_pos_x = last_pos->get_start_point().y + last_pos->get_height() / 2 - height / 2;
			m_pos_x = last_pos_x + (pos_x - last_pos_x) * moving_timer.get_rest_part();
			m_pos_y = last_pos_y + (pos_y - last_pos_y) * moving_timer.get_rest_part();
			putimagealpha(m_pos_x, m_pos_y, now_zhezi);
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
		settextcolor(GREEN);
		outtextxy(health_x, health_y, HP_SHOW);
	}
	int is_die() {
		return died;
	}
private:
	int exp;
	bool multi_move=false;
	bool can_attact=true;
	IMAGE* now_zhezi;
	Timer attact_interval;
	Timer recover_timer;
};

