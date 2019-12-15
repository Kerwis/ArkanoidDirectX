#pragma once
#include "MoveableBox.h"

class Ball : public MoveableBox
{
public:
	Ball(Graphics& gfx);
	~Ball()=default;	
	Ball(const Ball&) = delete;
	Ball& operator=(const Ball&) = delete;

	void CheckBounce(Vector2 pos, float size, Vector2 wall);
	void Update(float dt) noexcept override;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;

private:

};
