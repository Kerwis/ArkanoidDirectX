#pragma once

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