#pragma once
#include "MoveableBox.h"
#include "Keyboard.h"

class Player : public MoveableBox
{
public:
	Player(Graphics& gfx, std::shared_ptr<Keyboard> input);
	~Player()=default;
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
	
	void Update(float dt) noexcept override;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;

	void CheckBounce(Vector2 bounds);
	Vector2 GetPos();
	float GetSize();
private:
	float size = 5;

	std::shared_ptr<Keyboard> kbd;
};