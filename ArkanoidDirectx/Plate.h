#pragma once
#include "Box.h"
#include "Utiles.h"
#include "Ball.h"

class Plate :public Box
{
public:
	Plate(Graphics& gfx, Vector2 pos, int index);
	~Plate() = default;

	bool CheckHit(Ball& player);
	int GetIndex();
private:
	Vector2 size = { 1, 1 };
	int id;
};