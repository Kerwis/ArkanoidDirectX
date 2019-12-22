#pragma once

#include <memory>
#include "PlayerControl.h"
#include "Keyboard.h"
#include "Utiles.h"

class LocalControl : public PlayerControl
{
public:
	LocalControl(std::shared_ptr<Keyboard> input);
	~LocalControl() = default;
	LocalControl(const LocalControl&) = delete;
	LocalControl& operator=(const LocalControl&) = delete;
	void UpdatePositionAndSpeed(Vector2* position, Vector2* speed, float* maxSpeed, float dt) noexcept;
	void UpdateBall(Vector2* position, Vector2 speed, float dt) noexcept;
	bool Local() noexcept;
private:
	std::shared_ptr<Keyboard> kbd;
};