#pragma once
#include "Utiles.h"
#include "Box.h"

class Wall : public Box
{
public:
	Wall(Vector2 position, Vector2 targetSize, Graphics& gfx);
	~Wall() = default;

	DirectX::XMMATRIX GetTransformXM() const noexcept;
private:
	Vector2 pos;
};