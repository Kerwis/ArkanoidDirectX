#pragma once
#include "Box.h"

class Ball : public Box
{
public:
	Ball(Graphics& gfx);
	~Ball()=default;	
	Ball(const Ball&) = delete;
	Ball& operator=(const Ball&) = delete;

	void CheckBounce(Vector2 pos, float size);
	void Update(float dt) noexcept override;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;

private:
	// positional
	float x = 0;
	float y = -20.0f;

	// speed (delta/s)
	float speed = 15;
};
