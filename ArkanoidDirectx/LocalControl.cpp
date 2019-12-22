#include "LocalControl.h"

LocalControl::LocalControl(std::shared_ptr<Keyboard> input)
	:kbd(input)
{
}

void LocalControl::UpdatePositionAndSpeed(Vector2* position, Vector2* speed, float* maxSpeed, float dt) noexcept
{
	if (kbd->KeyIsPressed(0x41))
	{
		speed->x = -*maxSpeed;
		position->x += speed->x * dt;
	}
	else if (kbd->KeyIsPressed(0x44))
	{
		speed->x = *maxSpeed;
		position->x += speed->x * dt;
	}
	else
	{
		speed->x = 0;
	}
	if (kbd->KeyIsPressed(0x57))
	{
		*maxSpeed += 1;
	}
	if (kbd->KeyIsPressed(0x53))
	{
		*maxSpeed -= 1;
	}
}

void LocalControl::UpdateBall(Vector2* position, Vector2 speed, float dt) noexcept
{
	*position += speed * dt;
}

bool LocalControl::Local() noexcept
{
	return true;
}

