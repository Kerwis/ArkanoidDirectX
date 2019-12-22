#pragma once
#include "PlayerControl.h"
#include "PlayerBoard.h"
#include "Utiles.h"

class NetworkControl : public PlayerControl
{
public:
	NetworkControl(std::shared_ptr<BoardInfo> pi);
	~NetworkControl() = default;
	NetworkControl(const NetworkControl&) = delete;
	NetworkControl& operator=(const NetworkControl&) = delete;

	void UpdatePositionAndSpeed(Vector2* position, Vector2* speed, float* maxSpeed, float dt) noexcept;
	void UpdateBall(Vector2* position, Vector2 speed, float dt) noexcept;
	bool Local() noexcept;
private:
	std::shared_ptr<BoardInfo> pi;
};
