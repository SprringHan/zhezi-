#pragma once
#include "Atlas.h"
#include "util.h"
#include <functional>
#include "Atlas.h"
class Animation
{
public:
	Animation() = default;
	~Animation() = default;
	void reset() {
		pass_time = 0;
		idx_frame = 0;
	}
	void set_callback(function<void()>) {
		this->callback = callback;
	}
	void set_interval(int inv) {
		interval=inv;
	}
	void set_atlas(Atlas* atlas) {
		this->atlas = atlas;
	}
	void draw(int x, int y) {
		putimagealpha(x, y, atlas->get_image(idx_frame));
	}
	void on_update(int delta) {
		if (paused) return;
		pass_time += delta;
		if (pass_time >= interval) {
			if (!is_end()){
				idx_frame = (idx_frame + 1) % (atlas->getsize());
			}
			pass_time -= interval;
		}
		
	}
	void pause() {
		paused = true;
	}
	void resume() {
		paused = false;
	}
	void set_loop(bool flag) {
		is_loop = flag;
	}
	int get_idx_frame() {
		return idx_frame;
	}
	IMAGE* get_frame() {
		return atlas->get_image(idx_frame);
	}
	bool is_end() {
		if (is_loop) return false;
		return idx_frame == atlas->getsize() - 1;
	}
private:
	bool is_loop;
	bool paused = false;;
	int interval;
	int pass_time;
	int idx_frame;
	function<void()> callback;
	Atlas* atlas;
};

