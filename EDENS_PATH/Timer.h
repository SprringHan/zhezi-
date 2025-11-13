#pragma once
#include<functional>
#include<iostream>
class Timer
{
public:
	Timer() = default;
	~Timer() = default;
	void set_callback(std::function<void()> callback) {
		this->callback = callback;
	}
	void restart() {
		shotted = 0;
		pass_time = 0;
	}
	void set_interval(int inv) {
		interval = inv;
	}
	void set_one_shot(bool flag) {
		one_shot = flag;
	}
	double get_rest_part() {
		if (one_shot && shotted) return 0;
		else return 1.0* pass_time/(1.0*interval);
	}
	void pause() {
		paused = true;
	}
	void resume() {
		paused = false;
	}
	void on_update(int delta) {
		if (paused) return;
		pass_time += delta;
		if (pass_time >= interval) {
			if (!(one_shot) || (one_shot && !shotted) && callback ) {
				callback();
			}
			shotted = true;
			pass_time -= interval;
		}
	}
public:
	bool one_shot;
	bool shotted=0;
	int pass_time=0;
	int interval=1;
	bool paused = false;
	std::function<void()> callback;
};

