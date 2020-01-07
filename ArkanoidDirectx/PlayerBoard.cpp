#include "PlayerBoard.h"

PlayerBoard::PlayerBoard(std::shared_ptr<BoardInfo> playerInfo, float rotation, Graphics& gfx, std::shared_ptr<PlayerControl> input, int boardWidth, int boardHeight)
	: width(boardWidth), height(boardHeight)
{
	myInfo = playerInfo;
	myInfo->localControl = input->Local();
	InitElements(rotation, gfx, input);
}

void PlayerBoard::InitElements(float rotation, Graphics& gfx, std::shared_ptr<PlayerControl> input)
{
	myInfo->playerPosition = { 0, -32 * rotation };
	myInfo->ballPosition = { 0, -18 * rotation };
	Vector2 ballSpeed = { 0,-15 * rotation };
	Vector2 ballSize = { 1,1 };
	Vector2 wallpos = { -bounds.x - 1, 0 };
	Vector2 wallsize = { 1,-bounds.y };
	wallU = std::make_unique<Wall>(Vector2{ 0,0 }, Vector2{ bounds.x, 1 }, gfx);
	wallL = std::make_unique<Wall>(wallpos, wallsize, gfx);
	wallpos.x *= -1;
	wallR = std::make_unique<Wall>(wallpos, wallsize, gfx);
	bounds.y *= rotation;
	player = std::make_unique<Player>(&(myInfo->playerPosition), gfx, input);
	ball = std::make_unique<Ball>(&(myInfo->ballPosition), ballSpeed, ballSize, input, gfx);

	for (int j = width / -2; j < width / 2; j++)
	{
		for (int i = 0; i < height; i++)
		{
			Vector2 pos = { (j + 0.5f) * 3, (i + 1) * -2.5f * (float)rotation };
			plates.push_back(std::make_unique<Plate>(gfx, pos, (j + 10) * height + i));
			myInfo->plates[j + 10].set(i);
		}
	}
	myInfo->ready = true;
}

Score PlayerBoard::Update(float dt) noexcept
{
	player->Update(dt);
	player->CheckBounce(bounds);
	ball->Update(dt);
	ball->CheckBounce(*player, bounds);

	if (myInfo->localControl)
	{
		int i = 0;
		for (auto& p : plates)
		{
			if (p->CheckHit(*ball))
			{
				myInfo->plates[p->GetIndex() / height].set(p->GetIndex() % height, FALSE);
				plates.erase(plates.begin() + i);
				if (plates.empty())
				{
					return Score{ true, true };
					break;
				}
				break;
			}
			i++;
		}
	}
	else
	{
		int i = 0;
		for (auto& p : plates)
		{
			if (!myInfo->plates[p->GetIndex() / height].test(p->GetIndex() % height))
			{
				plates.erase(plates.begin() + i);
				if (plates.empty())
				{
					return Score{ true, false };
					break;
				}
				break;
			}
			i++;
		}
	}
	return Score{ false,false };
}

void PlayerBoard::Draw(Graphics& gfx) const noexcept
{
	wallU->Draw(gfx);
	wallL->Draw(gfx);
	wallR->Draw(gfx);
	player->Draw(gfx);
	ball->Draw(gfx);
	for (auto& p : plates)
	{
		p->Draw(gfx);
	}
}

bool PlayerBoard::IsBlock()
{
	return myInfo->lock;
}
