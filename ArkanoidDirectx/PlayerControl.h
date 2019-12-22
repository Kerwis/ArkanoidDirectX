#pragma once
#include "Utiles.h"

class PlayerControl
{
public:
	virtual void UpdatePositionAndSpeed(Vector2* position, Vector2* speed, float* maxSpeed, float dt) noexcept = 0;
	virtual void UpdateBall(Vector2* position, Vector2 speed, float dt) noexcept = 0;	
	virtual bool Local() noexcept = 0;
};