#include "Plate.h"
#include <math.h>

Plate::Plate(Graphics& gfx, Vector2 pos)
	: Box(gfx)
{
	*pposition = pos;
}

bool Plate::CheckHit(Ball& ball)
{
	Vector2 ballSize = { 1,1 };
	Vector2 pos = ball.GetPos();
	if (pos.y + ballSize.y >= pposition->y - size.y && pos.y - ballSize.y <= pposition->y + size.y// y pos
		&& pos.x - ballSize.x <= pposition->x + size.x && pos.x + ballSize.x >= pposition->x - size.x)// x pos
	{
		// check if we hit top/bottom/left/Right		
		float bottom = abs((pos.y + ballSize.y) - (pposition->y - size.y));
		float top = abs((pos.y - ballSize.y) - (pposition->y + size.y));
		float left = abs((pos.x + ballSize.x) - (pposition->x - size.x));
		float right = abs((pos.x - ballSize.x) - (pposition->x + size.x));
		if (bottom < top && bottom < left && bottom < right)
		{
			ball.BounceDown();
			return true;
		}
		if (top < left && top < right)
		{
			ball.BounceUp();
			return true;
		}
		if (left < right)
		{
			ball.BounceLeft();
			return true;
		}
		ball.BounceRight();
		return true;
	}
	return false;
}
