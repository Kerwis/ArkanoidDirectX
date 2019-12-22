#pragma once
#include "MoveableBox.h"
#include "Player.h"

class Ball : public MoveableBox
{
public:
	Ball(Vector2* pos, Vector2 targetSpeed, Vector2 targetSize, std::shared_ptr<PlayerControl> input, Graphics& gfx);
	~Ball()=default;	
	Ball(const Ball&) = delete;
	Ball& operator=(const Ball&) = delete;

	void CheckBounce(Player& player, Vector2 wall);
	void Update(float dt) noexcept override;
	void BounceUp();
	void BounceDown();
	void BounceLeft();
	void BounceRight();
private:
	Vector2 startPos;
	std::shared_ptr<PlayerControl> control;
};
