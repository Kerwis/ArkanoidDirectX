#include "Player.h"

Player::Player(Graphics& gfx, std::shared_ptr<Keyboard> input)
	: Box(gfx), kbd(input)
{
}

void Player::Update(float dt) noexcept
{
	if (kbd->KeyIsPressed(0x41))
	{
		x -= dt * speed;
		x = std::clamp(x, -30.0f, 30.0f);
	}
	if (kbd->KeyIsPressed(0x44))
	{
		x += dt * speed;
		x = std::clamp(x, -30.0f, 30.0f);
	}
	if (kbd->KeyIsPressed(0x57))
	{
		speed += 1;
	}
	if (kbd->KeyIsPressed(0x53))
	{
		speed -= 1;
	}
}

DirectX::XMMATRIX Player::GetTransformXM() const noexcept
{
	return DirectX::XMMatrixScaling(size, 1, 2) * DirectX::XMMatrixTranslation(x, y, 40.0f);
}

Vector2 Player::GetPos()
{
	return Vector2{ x,y };
}

float Player::GetSize()
{
	return size;
}
