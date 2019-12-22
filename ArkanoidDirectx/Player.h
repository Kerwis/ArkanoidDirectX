#pragma once
#include <algorithm>
#include "MoveableBox.h"
#include "PlayerControl.h"

class Player : public MoveableBox
{
public:

	Player(Vector2* ppos, Graphics& gfx, std::shared_ptr<PlayerControl> input);
	~Player()=default;
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
	
	void Update(float dt) noexcept override;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;

	void CheckBounce(Vector2 bounds);
	Vector2 GetSpeed();
private:
	float maxSpeed = 15;
	std::shared_ptr<PlayerControl> control;
};