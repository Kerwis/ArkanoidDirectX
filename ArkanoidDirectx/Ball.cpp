#include "Ball.h"

Ball::Ball(Graphics& gfx)
	: Box(gfx)
{

}

void Ball::CheckBounce(Vector2 pos, float size)
{
	//Deck surface
	if (std::abs(pos.y+1-y) < 0.05 // y pos
		&& x > pos.x - size && x < pos.x + size)// x pos
	{
		speed *= -1;
	}
}

void Ball::Update(float dt) noexcept
{
	y -= dt * speed;
	if (y < -25)
	{
		y = 0;
	}
	if (y > 1)
	{
		speed *= -1;
	}
}

DirectX::XMMATRIX Ball::GetTransformXM() const noexcept
{
	return DirectX::XMMatrixTranslation(x, y, 40.0f);
}