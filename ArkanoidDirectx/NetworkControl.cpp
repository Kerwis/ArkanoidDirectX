#include "NetworkControl.h"

NetworkControl::NetworkControl(std::shared_ptr<BoardInfo> pi)
	:pi(pi)
{
}

void NetworkControl::UpdatePositionAndSpeed(Vector2* position, Vector2* speed, float* maxSpeed, float dt) noexcept
{
	*position = pi->playerPosition;
}

void NetworkControl::UpdateBall(Vector2* position, Vector2 speed, float dt) noexcept
{
	*position = pi->ballPosition;
}

bool NetworkControl::Local() noexcept
{
	return false;
}
