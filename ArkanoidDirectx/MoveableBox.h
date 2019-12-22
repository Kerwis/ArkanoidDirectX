#pragma once
#include "Box.h"
#include "Utiles.h"

class MoveableBox : public Box
{
public:
	MoveableBox(Graphics& gfx);
	~MoveableBox() = default;
	MoveableBox(const MoveableBox&) = delete;
	MoveableBox& operator=(const MoveableBox&) = delete;

protected:
	// speed (delta/s)
	Vector2 speed = { 0,0 };
};