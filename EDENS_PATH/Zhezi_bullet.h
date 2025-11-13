#pragma once
#include "Bullet.h"
class Zhezi_bullet : public Bullet
{
public:
	Zhezi_bullet(int x, int y, int damage,double speed,Vector2 dir) :Bullet(x, y, damage, speed, dir, true) {};
	~Zhezi_bullet() {};
	void on_draw(Camera camera) {
		circle(pos.x - BULLETSIZE / 2, pos.y - BULLETSIZE / 2, BULLETSIZE);
	}
private:
	const int BULLETSIZE = 5;
};

