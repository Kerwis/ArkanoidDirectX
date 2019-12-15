#include "Player.h"

Player::Player(Graphics& gfx, std::shared_ptr<Keyboard> input)
	: MoveableBox(gfx), kbd(input)
{
	position = { 0,-20 };
	speed = { 15,0 };
}

void Player::Update(float dt) noexcept
{
	if (kbd->KeyIsPressed(0x41))
	{
		position.x -= dt * speed.x;
	}
	if (kbd->KeyIsPressed(0x44))
	{
		position.x += dt * speed.x;
	}
	if (kbd->KeyIsPressed(0x57))
	{
		speed.x += 1;
	}
	if (kbd->KeyIsPressed(0x53))
	{
		speed.x -= 1;
	}
}

DirectX::XMMATRIX Player::GetTransformXM() const noexcept
{
	return DirectX::XMMatrixScaling(size, 1, 2) * DirectX::XMMatrixTranslation(position.x, position.y, 40.0f);
}

void Player::CheckBounce(Vector2 bounds)
{
	position.x = std::clamp(position.x, -bounds.x, bounds.x);
}

Vector2 Player::GetPos()
{
	return position;
}

float Player::GetSize()
{
	return size;
}
