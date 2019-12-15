#include "Ball.h"

Ball::Ball(Graphics& gfx)
	: MoveableBox(gfx)
{
	speed = { 0,-5 };
}

void Ball::CheckBounce(Vector2 pos, float size, Vector2 wall)
{
	//Deck surface
	if (std::abs(pos.y+1-position.y) < 0.05 // y pos
		&& position.x > pos.x - size && position.x < pos.x + size)// x pos
	{
		speed.y *= -1;
	}

	//Wall
	if (position.x < -wall.x || position.x > wall.x)
	{
		speed.x * -1;
	}
	if (position.y < -wall.y)
	{
		position.y = 0;
	}
	if (position.y > 1)
	{
		speed.y *= -1;
	}
}

void Ball::Update(float dt) noexcept
{
	position += speed * dt;
}

DirectX::XMMATRIX Ball::GetTransformXM() const noexcept
{
	return DirectX::XMMatrixTranslation(position.x, position.y, 40.0f);
}