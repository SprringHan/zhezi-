#pragma once
#include<cmath>
class Vector2
{
public:
	Vector2() {};
	Vector2(float x, float y) :x(x), y(y) {};
	inline Vector2 operator+(const Vector2& v)const {
		return { x + v.x,y + v.y };
	}
	inline Vector2 operator-(const Vector2& v)const {
		return { x - v.x,y - v.y };
	}

	inline Vector2 operator*(const float& v)const {
		return { x * v,y * v };
	}
	inline Vector2 operator/(const float& v)const {
		return { x / v,y / v };
	}
	float lenth() {
		return sqrt((x * x) + (y * y));
	}
	inline Vector2 normalize() {
		float len = lenth();
		if (len == 0) {
			return { 0,0 };
		}
		else {
			return Vector2(x / len, y / len);
		}
		
	}
public:
	float x, y;
};

