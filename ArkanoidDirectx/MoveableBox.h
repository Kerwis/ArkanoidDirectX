#pragma once
#include "Box.h"

struct Vector2
{
	float x;
	float y;
	Vector2 operator* (float const& obj)
	{
		Vector2 ret = { x,y };
		ret.x *= obj;
		ret.y *= obj;
		return ret;
	}
	Vector2 operator+ (Vector2 const& obj)
	{
		Vector2 ret;
		ret.x = this->x + obj.x;
		ret.y = this->y + obj.y;
		return ret;
	}
	Vector2& operator += (Vector2 const& obj)
	{
		this->x += obj.x;
		this->y += obj.y;
		return *this;
	}
};

class MoveableBox : public Box
{
public:
	MoveableBox(Graphics& gfx);
	~MoveableBox() = default;
	MoveableBox(const MoveableBox&) = delete;
	MoveableBox& operator=(const MoveableBox&) = delete;

protected:
	// positional
	Vector2 position = { 0,0 };

	// speed (delta/s)
	Vector2 speed = { 0,0 };
};