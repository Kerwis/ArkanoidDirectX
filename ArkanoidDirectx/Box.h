#pragma once
#include "Drawable.h"

struct Vector2
{
	float x;
	float y;
};

class Box : public Drawable
{
public:
	Box(Graphics& gfx);
	void Update(float dt) noexcept override;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;
private:
};