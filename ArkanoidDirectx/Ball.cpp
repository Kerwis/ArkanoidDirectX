#include "Ball.h"

Ball::Ball(Vector2* pos, Vector2 targetSpeed, Vector2 targetSize, std::shared_ptr<PlayerControl> input, Graphics& gfx)
	:control(input),  MoveableBox(gfx)
{
	size = targetSize;
	speed = targetSpeed;
	pposition = pos;
	startPos = *pos;
}

void Ball::CheckBounce(Player& player, Vector2 wall)
{
	if (!(control->Local()))
		return;
	Vector2 pos = player.GetPos();
	Vector2 pSize = player.GetSize();
	Vector2 podSpeed = player.GetSpeed();

	//Pod surface
	if (pos.y + pSize.y >= pposition->y - size.y && pos.y - pSize.y < pposition->y + size.y// y pos
		&& pposition->x + size.x > pos.x - pSize.x && pposition->x - size.x < pos.x + pSize.x)// x pos
	{
		pposition->y = pos.y + pSize.y + size.y;
		BounceUp();
		//cool
		speed.x += podSpeed.x * 0.1f;
	}

	//Wall
	if (pposition->x - size.x < -wall.x)
	{
		BounceRight();
	}
	if (pposition->x + size.x > wall.x)
	{
		BounceLeft();
	}
	if (pposition->y < wall.y)
	{
		*pposition = startPos;
	}
	if (pposition->y + size.y > -0.75f)
	{
		BounceDown();
	}
}

void Ball::Update(float dt) noexcept
{
	control->UpdateBall(pposition, speed, dt);
}

void Ball::BounceUp()
{
	if (speed.y < 0)
	{
		speed.y *= -1;
	}
}

void Ball::BounceDown()
{
	if (speed.y > 0)
	{
		speed.y *= -1;
	}
}

void Ball::BounceLeft()
{
	if (speed.x > 0)
	{
		speed.x *= -1;
	}
}

void Ball::BounceRight()
{
	if (speed.x < 0)
	{
		speed.x *= -1;
	}
}
