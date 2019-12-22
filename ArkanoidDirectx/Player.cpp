#include "Player.h"

Player::Player(Vector2* ppos, Graphics& gfx, std::shared_ptr<PlayerControl> input)
	: MoveableBox(gfx), control(input)
{
	pposition = ppos;
	size = { 5, 1 };
}

void Player::Update(float dt) noexcept
{
	control->UpdatePositionAndSpeed(pposition, &speed, &maxSpeed, dt);
	//position.x += dt * speed.x;
}

DirectX::XMMATRIX Player::GetTransformXM() const noexcept
{
	return DirectX::XMMatrixScaling(size.x, size.y, 2) * Box::GetTransformXM();
}

void Player::CheckBounce(Vector2 bounds)
{
	pposition->x = std::clamp(pposition->x, -bounds.x + size.x, bounds.x - size.x);
}

Vector2 Player::GetSpeed()
{
	return speed;
}
