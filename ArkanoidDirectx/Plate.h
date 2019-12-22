#pragma once
#include "Box.h"
#include "Utiles.h"
#include "Ball.h"

class Plate :public Box
{
public:
	Plate(Graphics& gfx, Vector2 pos);
	~Plate() = default;

	bool CheckHit(Ball& player);
private:
	Vector2 size = { 1, 1 };
};