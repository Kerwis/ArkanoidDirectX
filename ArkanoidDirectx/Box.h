#pragma once
#include "Drawable.h"
#include "Utiles.h"

class Box : public Drawable
{
public:
	Box(Graphics& gfx);
	void Update(float dt) noexcept override;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;

	Vector2 GetPos();
	Vector2 GetSize();
protected:
	Vector2* pposition;
	Vector2 size = { 1, 1 };
private:
	Vector2 position = { 0,0 };
};