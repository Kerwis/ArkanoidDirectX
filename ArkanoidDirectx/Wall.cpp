#include "Wall.h"

Wall::Wall(Vector2 position, Vector2 targetSize, Graphics& gfx)
	:Box(gfx)
{
	pos = position;
	pposition = &pos;
	size = targetSize;
}

DirectX::XMMATRIX Wall::GetTransformXM() const noexcept
{
	return DirectX::XMMatrixScaling(size.x, size.y, 1) * Box::GetTransformXM();
}