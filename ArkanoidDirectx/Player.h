#pragma once
#include "Box.h"
#include "Keyboard.h"

class Player : public Box
{
public:
	Player(Graphics& gfx, std::shared_ptr<Keyboard> input);
	~Player()=default;
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
	
	void Update(float dt) noexcept override;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;

	Vector2 GetPos();
	float GetSize();
private:
	// positional
	float x = 0;
	float y = -20.0f;

	// speed (delta/s)
	float speed = 25;
	float size = 5;

	std::shared_ptr<Keyboard> kbd;
};