#pragma once
#include "Vector2.h"
#include "Timer.h"
class Camera
{
public:
	Camera() {
		timer.set_callback([&]() {
			pos = shake_pos;
			is_shaking = false;
			});
		timer.set_one_shot(true);
	}
	~Camera() {};
	const Vector2& get_position()const{
		return pos;
	}
	void reset() {
		pos.x = 0;
		pos.y = 0;
	}
	void shake(int strength, int duration) {
		if (is_shaking) {
			pos = shake_pos;
		}
		is_shaking = true;
		timer.set_interval(duration);
		shake_strength = strength;

		shake_pos = pos;
		timer.restart();
	}
	void on_update(int delta) {
		timer.on_update(delta);
		if (is_shaking) {
			pos.x = shake_pos.x + (rand() % 101 - 50) / 50.0 * (shake_strength);
			pos.y = shake_pos.y + (rand() % 101 - 50) / 50.0 * (shake_strength);
		}
	}
public:
	Vector2 shake_pos;
	Vector2 pos;
	bool is_shaking=false;
	int shake_strength;
	Timer timer;
};

